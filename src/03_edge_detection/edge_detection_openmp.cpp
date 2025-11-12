#include <opencv2/opencv.hpp>
#include <cstdio>
#include <vector>
#include <omp.h>

using namespace std;
using namespace cv;

#define OUTPUT_VIDEO true
#define BATCH_SIZE 30

int threadNum;

// Apply Canny Edge Detection
inline void applyEdgeDetection(const Mat &frame, Mat &output) {
	Mat gray;
	
	// Convert to grayscale if needed
	if (frame.channels() == 3) {
		cvtColor(frame, gray, COLOR_BGR2GRAY);
	} else {
		gray = frame;
	}
	
	// Apply Gaussian blur to reduce noise
	GaussianBlur(gray, gray, Size(5, 5), 1.5);
	
	// Apply Canny edge detection
	Canny(gray, output, 50, 150);
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
	
	string outputPath = (argc >= 4) ? argv[3] : "outputs/03_edge_detection/edge_detection_openmp.avi";
	
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
	
	// Setup output (grayscale)
	VideoWriter outputVideo;
	if (OUTPUT_VIDEO) {
		outputVideo.open(outputPath, VideoWriter::fourcc('M', 'J', 'P', 'G'),
		                 fps, Size(width, height), false);  // false = grayscale
		if (!outputVideo.isOpened()) {
			printf("Error: Cannot create output video file\n");
			return -1;
		}
	}
	
	printf("Processing video (OpenMP with %d threads)...\n", threadNum);
	
	double Total = omp_get_wtime();
	int processedFrames = 0;
	
	// Batch processing
	while (true) {
		vector<Mat> batch;
		batch.reserve(BATCH_SIZE);
		
		// Read a batch of frames
		for (int i = 0; i < BATCH_SIZE; ++i) {
			Mat frame;
			captureVideo >> frame;
			if (frame.empty()) break;
			batch.push_back(frame);
		}
		
		if (batch.empty()) break;
		
		// Process batch in parallel
		vector<Mat> edgeBatch(batch.size());
		
		#pragma omp parallel for num_threads(threadNum) schedule(static)
		for (int i = 0; i < (int)batch.size(); ++i) {
			applyEdgeDetection(batch[i], edgeBatch[i]);
		}
		
		// Write frames
		if (OUTPUT_VIDEO) {
			for (auto &edgeFrame : edgeBatch) {
				outputVideo << edgeFrame;
			}
		}
		
		processedFrames += batch.size();
		
		// Show progress
		if (processedFrames % 30 == 0) {
			printf("  Processed %d frames...\r", processedFrames);
			fflush(stdout);
		}
	}
	
	Total = omp_get_wtime() - Total;
	
	// Print results
	printf("\n\n");
	printf("========================================\n");
	printf("Edge Detection - OpenMP\n");
	printf("========================================\n");
	printf("Threads used: %d\n", threadNum);
	printf("Processed frames: %d\n", processedFrames);
	printf("Execution time: %.3fs\n", Total);
	printf("Average FPS: %.2f\n", processedFrames / Total);
	printf("Output saved to: %s\n", outputPath.c_str());
	printf("========================================\n");
	
	captureVideo.release();
	if (OUTPUT_VIDEO) {
		outputVideo.release();
	}
	
	return 0;
}
