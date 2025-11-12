#include <opencv2/opencv.hpp>
#include <cstdio>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <atomic>
#include <map>
#include <algorithm>

using namespace std;
using namespace cv;

// Multi-metric scene detection thresholds
#define HIST_THRESHOLD 0.70      // Histogram correlation threshold
#define EDGE_THRESHOLD 0.30      // Edge difference threshold
#define PIXEL_THRESHOLD 25.0     // Mean pixel difference threshold
#define MIN_SCENE_GAP 15         // Minimum frames between scene changes
#define BATCH_SIZE 10

struct FramePair {
	Mat frame1;
	Mat frame2;
	int frameNumber;
};

struct ComparisonResult {
	int frameNumber;
	double score;
	bool isSceneChange;
};

// Thread-safe queue template
template<typename T>
class ThreadSafeQueue {
private:
	queue<T> q;
	mutex mtx;
	condition_variable cv;
	bool finished = false;
	
public:
	void push(T item) {
		lock_guard<mutex> lock(mtx);
		q.push(move(item));
		cv.notify_one();
	}
	
	bool pop(T &item) {
		unique_lock<mutex> lock(mtx);
		cv.wait(lock, [this] { return !q.empty() || finished; });
		if (q.empty()) return false;
		item = move(q.front());
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
ThreadSafeQueue<vector<FramePair>> inputQueue;
ThreadSafeQueue<vector<ComparisonResult>> resultQueue;
atomic<int> framesProcessed(0);

// Calculate histogram correlation
double calculateHistogramCorrelation(const Mat &frame1, const Mat &frame2) {
	Mat hsv1, hsv2;
	cvtColor(frame1, hsv1, COLOR_BGR2HSV);
	cvtColor(frame2, hsv2, COLOR_BGR2HSV);
	
	int h_bins = 50, s_bins = 60;
	int histSize[] = {h_bins, s_bins};
	float h_ranges[] = {0, 180};
	float s_ranges[] = {0, 256};
	const float* ranges[] = {h_ranges, s_ranges};
	int channels[] = {0, 1};
	
	Mat hist1, hist2;
	calcHist(&hsv1, 1, channels, Mat(), hist1, 2, histSize, ranges, true, false);
	calcHist(&hsv2, 1, channels, Mat(), hist2, 2, histSize, ranges, true, false);
	
	normalize(hist1, hist1, 0, 1, NORM_MINMAX);
	normalize(hist2, hist2, 0, 1, NORM_MINMAX);
	
	return compareHist(hist1, hist2, HISTCMP_CORREL);
}

// Calculate edge-based difference
double calculateEdgeDifference(const Mat &frame1, const Mat &frame2) {
	Mat gray1, gray2, edges1, edges2;
	cvtColor(frame1, gray1, COLOR_BGR2GRAY);
	cvtColor(frame2, gray2, COLOR_BGR2GRAY);
	
	Canny(gray1, edges1, 50, 150);
	Canny(gray2, edges2, 50, 150);
	
	Mat diff;
	absdiff(edges1, edges2, diff);
	
	return (double)countNonZero(diff) / (frame1.rows * frame1.cols);
}

// Calculate mean pixel difference
double calculatePixelDifference(const Mat &frame1, const Mat &frame2) {
	Mat diff;
	absdiff(frame1, frame2, diff);
	
	Scalar meanDiff = mean(diff);
	return (meanDiff[0] + meanDiff[1] + meanDiff[2]) / 3.0;
}

// Improved scene detection using multiple metrics
bool isSceneChange(const Mat &prevFrame, const Mat &currFrame, double &score) {
	double histCorr = calculateHistogramCorrelation(prevFrame, currFrame);
	double edgeDiff = calculateEdgeDifference(prevFrame, currFrame);
	double pixelDiff = calculatePixelDifference(prevFrame, currFrame);
	
	bool histChange = (histCorr < HIST_THRESHOLD);
	bool edgeChange = (edgeDiff > EDGE_THRESHOLD);
	bool pixelChange = (pixelDiff > PIXEL_THRESHOLD);
	
	score = 0.0;
	if (histChange) score += 40.0 * (1.0 - histCorr);
	if (edgeChange) score += 30.0 * edgeDiff;
	if (pixelChange) score += 30.0 * (pixelDiff / 100.0);
	
	int agreementCount = (histChange ? 1 : 0) + (edgeChange ? 1 : 0) + (pixelChange ? 1 : 0);
	bool strongSignal = (histCorr < 0.50) || (edgeDiff > 0.50) || (pixelDiff > 50.0);
	
	return (agreementCount >= 2) || strongSignal;
}

// Worker thread
void processingWorker(int tid) {
	vector<FramePair> batch;
	
	while (inputQueue.pop(batch)) {
		vector<ComparisonResult> results;
		
		for (auto &pair : batch) {
			double score = 0.0;
			bool isChange = isSceneChange(pair.frame1, pair.frame2, score);
			results.push_back({pair.frameNumber, score, isChange});
			framesProcessed++;
		}
		
		resultQueue.push(move(results));
	}
}

int main(int argc, const char** argv) {
	
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
	
	string outputPath = (argc >= 4) ? argv[3] : "outputs/07_scene_detection/scene_detection_pthread.txt";
	
	VideoCapture captureVideo(argv[1]);
	if (!captureVideo.isOpened()) {
		printf("Error: Cannot open video file: %s\n", argv[1]);
		return -1;
	}
	
	int frameCount = (int)captureVideo.get(CAP_PROP_FRAME_COUNT);
	double fps = captureVideo.get(CAP_PROP_FPS);
	
	printf("Processing video (Pthread with %d threads)...\n", threadNum);
	printf("Total frames: %d, FPS: %.2f\n", frameCount, fps);
	
	double Total = getTickCount();
	
	// Start worker threads
	vector<thread> workers;
	for (int i = 0; i < threadNum; ++i) {
		workers.emplace_back(processingWorker, i);
	}
	
	// Reading thread
	thread readerThread([&]() {
		Mat prevFrame, currFrame;
		int frameNumber = 0;
		
		captureVideo >> prevFrame;
		if (prevFrame.empty()) return;
		frameNumber++;
		
		vector<FramePair> batch;
		batch.reserve(BATCH_SIZE);
		
		while (true) {
			captureVideo >> currFrame;
			if (currFrame.empty()) break;
			
			frameNumber++;
			
			FramePair pair;
			pair.frame1 = prevFrame.clone();
			pair.frame2 = currFrame.clone();
			pair.frameNumber = frameNumber;
			batch.push_back(pair);
			
			if (batch.size() >= BATCH_SIZE) {
				inputQueue.push(move(batch));
				batch.clear();
				batch.reserve(BATCH_SIZE);
			}
			
			prevFrame = currFrame.clone();
		}
		
		if (!batch.empty()) {
			inputQueue.push(move(batch));
		}
		
		inputQueue.setFinished();
	});
	
	// Collector thread
	vector<pair<int, double>> sceneChanges;
	vector<double> sceneScores;
	int lastSceneFrame = -MIN_SCENE_GAP;
	mutex sceneMutex;
	
	thread collectorThread([&]() {
		vector<ComparisonResult> results;
		
		while (resultQueue.pop(results)) {
			for (auto &res : results) {
				if (res.isSceneChange) {
					lock_guard<mutex> lock(sceneMutex);
					// Avoid detecting same scene change multiple times
					if (res.frameNumber - lastSceneFrame >= MIN_SCENE_GAP) {
						double timestamp = res.frameNumber / fps;
						sceneChanges.push_back(make_pair(res.frameNumber, timestamp));
						sceneScores.push_back(res.score);
						lastSceneFrame = res.frameNumber;
						printf("  Scene change at frame %d (score: %.1f)\n", res.frameNumber, res.score);
					}
				}
				
				int processed = framesProcessed.load();
				if (processed % 30 == 0) {
					printf("  Processed %d frames...\r", processed);
					fflush(stdout);
				}
			}
		}
	});
	
	// Wait for threads
	readerThread.join();
	for (auto &worker : workers) {
		worker.join();
	}
	resultQueue.setFinished();
	collectorThread.join();
	
	Total = getTickCount() - Total;
	
	int totalFrames = framesProcessed.load();
	
	// Sort scene changes by frame number
	sort(sceneChanges.begin(), sceneChanges.end());
	
	// Write results
	FILE *outFile = fopen(outputPath.c_str(), "w");
	if (outFile) {
		fprintf(outFile, "Scene Detection Results (Improved Multi-Metric)\n");
		fprintf(outFile, "================================================\n");
		fprintf(outFile, "Video: %s\n", argv[1]);
		fprintf(outFile, "Total frames: %d\n", totalFrames);
		fprintf(outFile, "FPS: %.2f\n", fps);
		fprintf(outFile, "Detection Method: Histogram + Edge + Pixel Analysis\n");
		fprintf(outFile, "Thresholds: Hist=%.2f, Edge=%.2f, Pixel=%.1f\n", HIST_THRESHOLD, EDGE_THRESHOLD, PIXEL_THRESHOLD);
		fprintf(outFile, "Detected scene changes: %d\n\n", (int)sceneChanges.size());
		
		fprintf(outFile, "Frame Number    Timestamp (s)    Confidence\n");
		fprintf(outFile, "------------------------------------------------\n");
		for (size_t i = 0; i < sceneChanges.size(); i++) {
			fprintf(outFile, "%-15d %-16.3f %.1f%%\n", 
				sceneChanges[i].first, 
				sceneChanges[i].second, 
				min(sceneScores[i], 100.0));
		}
		fclose(outFile);
	}
	
	// Print results
	printf("\n\n");
	printf("========================================\n");
	printf("Scene Detection - Pthread (Improved)\n");
	printf("========================================\n");
	printf("Processed frames: %d\n", totalFrames);
	printf("Detected scene changes: %d\n", (int)sceneChanges.size());
	printf("Threads used: %d\n", threadNum);
	printf("Detection: Multi-metric (Histogram + Edge + Pixel)\n");
	printf("Execution time: %.3fs\n", Total / getTickFrequency());
	printf("Average FPS: %.2f\n", totalFrames / (Total / getTickFrequency()));
	printf("Output saved to: %s\n", outputPath.c_str());
	printf("========================================\n");
	
	captureVideo.release();
	
	return 0;
}
