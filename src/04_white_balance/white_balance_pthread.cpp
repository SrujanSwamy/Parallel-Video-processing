#include <opencv2/opencv.hpp>
#include <cstdio>
#include <cmath>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <atomic>
#include <map>

using namespace std;
using namespace cv;

#define OUTPUT_VIDEO true
#define BATCH_SIZE 10

struct FrameBatch {
	vector<Mat> frames;
	int startIndex;
};

// Thread-safe queue
class BatchQueue {
private:
	queue<FrameBatch> q;
	mutex mtx;
	condition_variable cv;
	bool finished = false;

public:
	void push(FrameBatch batch) {
		lock_guard<mutex> lock(mtx);
		q.push(move(batch));
		cv.notify_one();
	}

	bool pop(FrameBatch &batch) {
		unique_lock<mutex> lock(mtx);
		cv.wait(lock, [this] { return !q.empty() || finished; });
		if (q.empty()) return false;
		batch = move(q.front());
		q.pop();
		return true;
	}

	void setFinished() {
		lock_guard<mutex> lock(mtx);
		finished = true;
		cv.notify_all();
	}

	bool isFinished() {
		lock_guard<mutex> lock(mtx);
		return finished && q.empty();
	}
};

int threadNum;
BatchQueue inputQueue, processedQueue;
atomic<int> framesProcessed(0);

void whiteBalance(Mat &img) {
	if (img.empty()) return;

	int rows = img.rows;
	int cols = img.cols;
	int picSz = rows * cols;

	int bSum = 0, gSum = 0, rSum = 0;
	int avg[3], base;

	if (img.isContinuous()) {
		cols *= rows;
		rows = 1;
	}

	// Calculate average for each channel
	for (int i = 0; i < rows; ++i) {
		Vec3b *p = img.ptr<Vec3b>(i);
		for (int j = 0; j < cols; ++j) {
			bSum += p[j][0];
			gSum += p[j][1];
			rSum += p[j][2];
		}
	}

	avg[0] = (double)bSum / picSz;
	avg[1] = (double)gSum / picSz;
	avg[2] = (double)rSum / picSz;

	// Use green channel as base (gray world assumption)
	base = avg[1];

	// Create lookup tables for color correction
	int tableB[256], tableG[256], tableR[256];
	for (int i = 0; i < 256; ++i) {
		tableB[i] = min(255, (int)(base * i / avg[0]));
		tableG[i] = min(255, (int)(base * i / avg[1]));
		tableR[i] = min(255, (int)(base * i / avg[2]));
	}

	// Apply white balance correction
	for (int i = 0; i < rows; ++i) {
		Vec3b *p = img.ptr<Vec3b>(i);
		for (int j = 0; j < cols; ++j) {
			p[j][0] = tableB[p[j][0]];
			p[j][1] = tableG[p[j][1]];
			p[j][2] = tableR[p[j][2]];
		}
	}
}

// Worker thread: processes batches of frames
void processingWorker(int tid) {
	FrameBatch batch;

	while (inputQueue.pop(batch)) {
		// Process all frames in batch
		for (auto &frame : batch.frames) {
			whiteBalance(frame);
			framesProcessed++;
		}

		// Send to output queue
		processedQueue.push(move(batch));
	}
}

int main(int argc, const char** argv) {
	
	// Check arguments
	if (argc < 2) {
		printf("Usage: %s <video_file> <num_threads> [output_file]\n", argv[0]);
		return 0;
	}

	if (argc < 3) {
		printf("Error: Please specify number of threads\n");
		return 0;
	}

	threadNum = atoi(argv[2]);
	if (threadNum < 1) threadNum = 1;

	string outputPath = (argc >= 4) ? argv[3] : "outputs/04_white_balance/white_balance_pthread.avi";

	// Open video
	VideoCapture captureVideo(argv[1]);
	if (!captureVideo.isOpened()) {
		printf("Error: Cannot open video file: %s\n", argv[1]);
		return -1;
	}

	int frameCount = (int)captureVideo.get(CAP_PROP_FRAME_COUNT);
	double fps = captureVideo.get(CAP_PROP_FPS);
	int width = (int)captureVideo.get(CAP_PROP_FRAME_WIDTH);
	int height = (int)captureVideo.get(CAP_PROP_FRAME_HEIGHT);

	// Setup output
	VideoWriter outputVideo;
	if (OUTPUT_VIDEO) {
		outputVideo.open(outputPath, VideoWriter::fourcc('M', 'J', 'P', 'G'),
		                 fps, Size(width, height), true);
		if (!outputVideo.isOpened()) {
			printf("Error: Cannot create output video file\n");
			return -1;
		}
	}

	printf("Processing video (Pthread with %d threads)...\n", threadNum);

	double Total = getTickCount();

	// Start worker threads
	vector<thread> workers;
	for (int i = 0; i < threadNum; ++i) {
		workers.emplace_back(processingWorker, i);
	}

	// Reading thread
	thread readerThread([&]() {
		int batchIndex = 0;
		while (true) {
			FrameBatch batch;
			batch.startIndex = batchIndex * BATCH_SIZE;
			batch.frames.reserve(BATCH_SIZE);

			for (int i = 0; i < BATCH_SIZE; ++i) {
				Mat frame;
				captureVideo >> frame;
				if (frame.empty()) break;
				batch.frames.push_back(frame.clone());
			}

			if (batch.frames.empty()) break;

			inputQueue.push(move(batch));
			batchIndex++;
		}

		inputQueue.setFinished();
	});

	// Writing thread
	thread writerThread([&]() {
		int expectedBatch = 0;
		map<int, FrameBatch> outOfOrderBatches;

		while (!processedQueue.isFinished()) {
			FrameBatch batch;
			if (!processedQueue.pop(batch)) continue;

			int batchIndex = batch.startIndex / BATCH_SIZE;

			if (batchIndex != expectedBatch) {
				outOfOrderBatches[batchIndex] = move(batch);
				continue;
			}

			// Write this batch
			for (auto &frame : batch.frames) {
				outputVideo << frame;
			}
			expectedBatch++;

			// Write queued batches
			while (outOfOrderBatches.count(expectedBatch)) {
				auto &nextBatch = outOfOrderBatches[expectedBatch];
				for (auto &frame : nextBatch.frames) {
					outputVideo << frame;
				}
				outOfOrderBatches.erase(expectedBatch);
				expectedBatch++;
			}

			// Show progress
			int processed = framesProcessed.load();
			if (processed % 30 == 0) {
				printf("  Processed %d frames...\r", processed);
				fflush(stdout);
			}
		}
	});

	// Wait for all threads
	readerThread.join();
	for (auto &worker : workers) {
		worker.join();
	}
	processedQueue.setFinished();
	writerThread.join();

	Total = getTickCount() - Total;

	int totalFrames = framesProcessed.load();

	// Print results
	printf("\n\n");
	printf("========================================\n");
	printf("White Balance - Pthread\n");
	printf("========================================\n");
	printf("Threads used: %d\n", threadNum);
	printf("Processed frames: %d\n", totalFrames);
	printf("Execution time: %.3fs\n", Total / getTickFrequency());
	printf("Average FPS: %.2f\n", totalFrames / (Total / getTickFrequency()));
	printf("Output saved to: %s\n", outputPath.c_str());
	printf("========================================\n");

	captureVideo.release();
	if (OUTPUT_VIDEO) {
		outputVideo.release();
	}

	return 0;
}
