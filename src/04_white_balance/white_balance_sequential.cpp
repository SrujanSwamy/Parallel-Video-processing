#include <opencv2/opencv.hpp>
#include <cstdio>
#include <cmath>

using namespace std;
using namespace cv;

#define OUTPUT_VIDEO true

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
		printf("Usage: %s <video_file> [output_file]\n", argv[0]);
		printf("Example: %s input_videos/sample_video.mp4 outputs/04_white_balance/output_sequential.avi\n", argv[0]);
		return 0;
	}

	// Set output path
	string outputPath = (argc >= 3) ? argv[2] : "outputs/04_white_balance/white_balance_sequential.avi";

	// Open video file
	VideoCapture captureVideo(argv[1]);
	if (!captureVideo.isOpened()) {
		printf("Error: Cannot open video file: %s\n", argv[1]);
		return -1;
	}

	// Get video information
	int frameCount = (int)captureVideo.get(CAP_PROP_FRAME_COUNT);
	double fps = captureVideo.get(CAP_PROP_FPS);
	int width = (int)captureVideo.get(CAP_PROP_FRAME_WIDTH);
	int height = (int)captureVideo.get(CAP_PROP_FRAME_HEIGHT);

	// Setup video output
	VideoWriter outputVideo;
	if (OUTPUT_VIDEO) {
		outputVideo.open(outputPath, 
		                 VideoWriter::fourcc('M', 'J', 'P', 'G'),
		                 fps, Size(width, height), true);
		if (!outputVideo.isOpened()) {
			printf("Error: Cannot create output video file\n");
			return -1;
		}
	}

	printf("Processing video (Sequential White Balance)...\n");

	double Total = getTickCount();
	int processedFrames = 0;
	Mat frame;

	// Process video frame by frame
	while (true) {
		captureVideo >> frame;
		if (frame.empty()) break;

		// Apply white balance
		whiteBalance(frame);

		// Write output
		if (OUTPUT_VIDEO) {
			outputVideo << frame;
		}

		processedFrames++;

		// Show progress every 30 frames
		if (processedFrames % 30 == 0) {
			printf("  Processed %d frames...\r", processedFrames);
			fflush(stdout);
		}
	}

	Total = getTickCount() - Total;

	// Print results
	printf("\n\n");
	printf("========================================\n");
	printf("White Balance - Sequential\n");
	printf("========================================\n");
	printf("Processed frames: %d\n", processedFrames);
	printf("Execution time: %.3fs\n", Total / getTickFrequency());
	printf("Average FPS: %.2f\n", processedFrames / (Total / getTickFrequency()));
	printf("Output saved to: %s\n", outputPath.c_str());
	printf("========================================\n");

	captureVideo.release();
	if (OUTPUT_VIDEO) {
		outputVideo.release();
	}

	return 0;
}
