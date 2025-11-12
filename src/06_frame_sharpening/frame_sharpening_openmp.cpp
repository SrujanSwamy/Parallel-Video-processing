#include <opencv2/opencv.hpp>
#include <cstdio>
#include <vector>
#include <omp.h>

using namespace std;
using namespace cv;

#define OUTPUT_VIDEO true
#define BATCH_SIZE 30

int threadNum;

// Apply Frame Sharpening using Unsharp Masking
inline void applySharpen(const Mat &frame, Mat &output) {
	Mat blurred;
	
	// Apply Gaussian blur
	GaussianBlur(frame, blurred, Size(5, 5), 1.0);
	
	// Unsharp mask formula: sharpened = original + amount * (original - blurred)
	// amount controls the strength of sharpening (1.5 is a good value)
	double amount = 1.5;
	addWeighted(frame, 1.0 + amount, blurred, -amount, 0, output);
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
	
	string outputPath = (argc >= 4) ? argv[3] : "outputs/06_frame_sharpening/frame_sharpening_openmp.avi";
	
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
	
	// Setup output (color)
	VideoWriter outputVideo;
	if (OUTPUT_VIDEO) {
		outputVideo.open(outputPath, VideoWriter::fourcc('M', 'J', 'P', 'G'),
		                 fps, Size(width, height), true);  // true = color
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
		vector<Mat> sharpenedBatch(batch.size());
		
		#pragma omp parallel for num_threads(threadNum) schedule(static)
		for (int i = 0; i < (int)batch.size(); ++i) {
			applySharpen(batch[i], sharpenedBatch[i]);
		}
		
		// Write frames
		if (OUTPUT_VIDEO) {
			for (auto &sharpenedFrame : sharpenedBatch) {
				outputVideo << sharpenedFrame;
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
	printf("Frame Sharpening - OpenMP\n");
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
