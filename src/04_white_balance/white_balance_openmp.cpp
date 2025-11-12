#include <opencv2/opencv.hpp>
#include <cstdio>
#include <cmath>
#include <vector>
#include <omp.h>

using namespace std;
using namespace cv;

#define OUTPUT_VIDEO true
#define BATCH_SIZE 30

int threadNum;

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

	string outputPath = (argc >= 4) ? argv[3] : "outputs/04_white_balance/white_balance_openmp.avi";

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

	// Process in batches
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
		#pragma omp parallel for num_threads(threadNum) schedule(static)
		for (int i = 0; i < (int)batch.size(); ++i) {
			whiteBalance(batch[i]);
		}

		// Write frames
		if (OUTPUT_VIDEO) {
			for (auto &frame : batch) {
				outputVideo << frame;
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
	printf("White Balance - OpenMP\n");
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
