#include <opencv2/opencv.hpp>
#include <cstdio>
#include <vector>
#include <deque>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <atomic>
#include <map>

using namespace std;
using namespace cv;

#define OUTPUT_VIDEO true
#define TEMPORAL_WINDOW 3

struct FrameData {
	Mat frame;
	int index;
};

// Thread-safe queue
template<typename T>
class ThreadSafeQueue {
private:
	queue<T> q;
	mutex mtx;
	condition_variable cv;
	bool finished = false;
	
public:
	void push(T data) {
		lock_guard<mutex> lock(mtx);
		q.push(move(data));
		cv.notify_one();
	}
	
	bool pop(T &data) {
		unique_lock<mutex> lock(mtx);
		cv.wait(lock, [this] { return !q.empty() || finished; });
		if (q.empty()) return false;
		data = move(q.front());
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
ThreadSafeQueue<FrameData> inputQueue;
ThreadSafeQueue<FrameData> outputQueue;
atomic<int> framesProcessed(0);

// Shared temporal buffer with frame mapping
mutex temporalMutex;
deque<Mat> temporalBuffer;
int currentFrameIndex = 0;
map<int, Mat> processedFrames;  // Store processed frames temporarily

// Worker threads: Process pixel averaging in parallel
void processingWorker(int tid) {
	while (true) {
		FrameData frameData;
		if (!inputQueue.pop(frameData)) break;
		
		Mat output;
		
		// Get frames to average (synchronized)
		{
			lock_guard<mutex> lock(temporalMutex);
			
			// Add current frame to temporal buffer
			temporalBuffer.push_back(frameData.frame.clone());
			
			// Keep only TEMPORAL_WINDOW frames
			if (temporalBuffer.size() > TEMPORAL_WINDOW) {
				temporalBuffer.pop_front();
			}
			
			// Apply temporal averaging using efficient OpenCV operations
			output = Mat::zeros(frameData.frame.rows, frameData.frame.cols, CV_32FC3);
			double weight = 1.0 / temporalBuffer.size();
			
			for (const auto &frame : temporalBuffer) {
				Mat temp;
				frame.convertTo(temp, CV_32FC3);
				output += temp * weight;
			}
			
			// Convert back to 8-bit
			output.convertTo(output, CV_8UC3);
		}
		
		// Send processed frame to output
		FrameData processedData;
		processedData.frame = output;
		processedData.index = frameData.index;
		outputQueue.push(processedData);
		
		framesProcessed++;
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
	
	string outputPath = (argc >= 4) ? argv[3] : "outputs/10_motion_blur_reduction/motion_blur_reduction_pthread.avi";
	
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
	
	printf("Processing video (Pthread)...\n");
	printf("Note: Temporal filtering is sequential - using 1 processing thread\n");
	
	double Total = (double)getTickCount();
	
	// Use only 1 worker for temporal processing (must be sequential)
	thread worker(processingWorker, 0);
	
	// Reading thread - reads frames and sends to queue
	thread readerThread([&]() {
		int frameIndex = 0;
		while (true) {
			Mat frame;
			captureVideo >> frame;
			if (frame.empty()) break;
			
			FrameData frameData;
			frameData.frame = frame.clone();
			frameData.index = frameIndex++;
			
			inputQueue.push(frameData);
		}
		
		inputQueue.setFinished();
	});
	
	// Writing thread - writes frames in correct order
	map<int, Mat> frameBuffer;
	int nextFrameToWrite = 0;
	mutex bufferMutex;
	
	thread writerThread([&]() {
		while (true) {
			FrameData frameData;
			if (!outputQueue.pop(frameData)) {
				if (outputQueue.isFinished()) break;
				continue;
			}
			
			{
				lock_guard<mutex> lock(bufferMutex);
				frameBuffer[frameData.index] = frameData.frame;
				
				// Write frames in order
				while (frameBuffer.find(nextFrameToWrite) != frameBuffer.end()) {
					if (OUTPUT_VIDEO) {
						outputVideo << frameBuffer[nextFrameToWrite];
					}
					
					// Show progress
					if ((nextFrameToWrite + 1) % 30 == 0) {
						printf("  Processed %d frames...\r", nextFrameToWrite + 1);
						fflush(stdout);
					}
					
					frameBuffer.erase(nextFrameToWrite);
					nextFrameToWrite++;
				}
			}
		}
	});
	
	// Wait for all threads
	readerThread.join();
	worker.join();
	outputQueue.setFinished();
	writerThread.join();
	
	Total = ((double)getTickCount() - Total) / getTickFrequency();
	
	int totalFrames = framesProcessed.load();
	
	// Print results
	printf("\n\n");
	printf("========================================\n");
	printf("Motion Blur Reduction - Pthread\n");
	printf("========================================\n");
	printf("Threads used: %d\n", threadNum);
	printf("Processed frames: %d\n", totalFrames);
	printf("Execution time: %.3fs\n", Total);
	printf("Average FPS: %.2f\n", totalFrames / Total);
	printf("Output saved to: %s\n", outputPath.c_str());
	printf("========================================\n");
	
	captureVideo.release();
	if (OUTPUT_VIDEO) {
		outputVideo.release();
	}
	
	return 0;
}