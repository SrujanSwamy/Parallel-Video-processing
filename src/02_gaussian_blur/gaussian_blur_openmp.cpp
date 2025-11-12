#include <opencv2/opencv.hpp>
#include <cstdio>
#include <vector>
#include <omp.h>

using namespace std;
using namespace cv;

#define OUTPUT_VIDEO true
#define BATCH_SIZE 30  // Increased batch size

int threadNum;

// Apply Gaussian Blur
inline void applyGaussianBlur(const Mat &frame, Mat &output) {
	// Using 15x15 kernel with sigma 5.0 for strong blur effect
	GaussianBlur(frame, output, Size(15, 15), 5.0, 5.0);
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
	
	string outputPath = (argc >= 4) ? argv[3] : "outputs/02_gaussian_blur/gaussian_blur_openmp.avi";
	
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
		
		// Process batch in parallel with static scheduling
		vector<Mat> blurredBatch(batch.size());
		
		#pragma omp parallel for num_threads(threadNum) schedule(static)
		for (int i = 0; i < (int)batch.size(); ++i) {
			applyGaussianBlur(batch[i], blurredBatch[i]);
		}
		
		// Write frames
		if (OUTPUT_VIDEO) {
			for (auto &blurredFrame : blurredBatch) {
				outputVideo << blurredFrame;
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
	printf("Gaussian Blur - OpenMP\n");
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
