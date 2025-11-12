#include <opencv2/opencv.hpp>
#include <cstdio>
#include <algorithm>

using namespace std;
using namespace cv;

#define OUTPUT_VIDEO true

void lightUp(Mat &frame) {
	if (frame.empty()) return;

	int rows = frame.rows;
	int cols = frame.cols;

	// Create matrix to store intermediate values
	vector<vector<int>> mat(rows, vector<int>(cols));

	// Extract blue channel and apply brightening
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			mat[i][j] = frame.at<Vec3b>(i, j)[0] * 2 + 5;
		}
	}

	// Find max value
	int max_val = 0;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (mat[i][j] > max_val) {
				max_val = mat[i][j];
			}
		}
	}

	// Normalize to 255
	if (max_val > 0) {
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				frame.at<Vec3b>(i, j)[0] = (mat[i][j] * 255) / max_val;
			}
		}
	}
}

int main(int argc, const char** argv) {
	
	// Check arguments
	if (argc < 2) {
		printf("Usage: %s <video_file> [output_file]\n", argv[0]);
		printf("Example: %s input_videos/sample_video.mp4 outputs/12_lightup/output_sequential.avi\n", argv[0]);
		return 0;
	}

	// Set output path
	string outputPath = (argc >= 3) ? argv[2] : "outputs/12_lightup/lightup_sequential.avi";

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

	printf("Processing video (Sequential Lightup)...\n");

	double Total = getTickCount();
	int processedFrames = 0;
	Mat frame;

	// Process video frame by frame
	while (true) {
		captureVideo >> frame;
		if (frame.empty()) break;

		// Apply lightup
		lightUp(frame);

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
	printf("Lightup - Sequential\n");
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
