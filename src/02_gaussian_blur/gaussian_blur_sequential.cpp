#include <opencv2/opencv.hpp>
#include <cstdio>

using namespace std;
using namespace cv;

#define OUTPUT_VIDEO true

// Apply Gaussian Blur using OpenCV's optimized function
void applyGaussianBlur(const Mat &frame, Mat &output) {
	// Kernel size (must be odd): larger = more blur
	// Using 15x15 kernel with sigma 5.0 for strong blur effect
	GaussianBlur(frame, output, Size(15, 15), 5.0, 5.0);
}

int main(int argc, const char** argv) {
	
	// Check arguments
	if (argc < 2) {
		printf("Usage: %s <video_file> [output_file]\n", argv[0]);
		printf("Example: %s input_videos/sample_video.mp4 outputs/02_gaussian_blur/output_sequential.avi\n", argv[0]);
		return 0;
	}
	
	// Set output path
	string outputPath = (argc >= 3) ? argv[2] : "outputs/02_gaussian_blur/gaussian_blur_sequential.avi";
	
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
	
	printf("Processing video (Sequential)...\n");
	
	double Total = getTickCount();
	int processedFrames = 0;
	Mat frame, blurred;
	
	// Process video frame by frame
	while (true) {
		captureVideo >> frame;
		if (frame.empty()) break;
		
		// Apply Gaussian blur
		applyGaussianBlur(frame, blurred);
		
		// Write output
		if (OUTPUT_VIDEO) {
			outputVideo << blurred;
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
	printf("Gaussian Blur - Sequential\n");
	printf("========================================\n");
	printf("Processed frames: %d\n", processedFrames);
	printf("Execution time: %.3fs\n", Total / getTickFrequency());
	printf("Average FPS: %.2f\n", processedFrames / (Total / getTickFrequency()));
	printf("Output saved to: %s\n", outputPath.c_str());
	printf("========================================\n");
	
	// Release resources
	captureVideo.release();
	if (OUTPUT_VIDEO) {
		outputVideo.release();
	}
	
	return 0;
}
