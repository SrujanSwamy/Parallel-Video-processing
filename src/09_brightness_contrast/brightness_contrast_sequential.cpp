#include <opencv2/opencv.hpp>
#include <cstdio>

using namespace std;
using namespace cv;

#define OUTPUT_VIDEO true

// Apply Brightness and Contrast adjustment
// Formula: new_pixel = alpha * original_pixel + beta
// alpha > 1: increase contrast, alpha < 1: decrease contrast
// beta > 0: increase brightness, beta < 0: decrease brightness
void applyBrightnessContrast(const Mat &frame, Mat &output) {
	double alpha = 1.5;  // Contrast control (1.5 = 50% more contrast)
	int beta = 50;       // Brightness control (+50 for noticeable brightness)
	
	// Apply the formula: output = alpha * input + beta
	frame.convertTo(output, -1, alpha, beta);
}

int main(int argc, const char** argv) {
	
	// Check arguments
	if (argc < 2) {
		printf("Usage: %s <video_file> [output_file]\n", argv[0]);
		printf("Example: %s input_videos/sample_video.mp4 outputs/09_brightness_contrast/output_sequential.avi\n", argv[0]);
		return 0;
	}
	
	// Set output path
	string outputPath = (argc >= 3) ? argv[2] : "outputs/09_brightness_contrast/brightness_contrast_sequential.avi";
	
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
	
	// Setup video output (color output)
	VideoWriter outputVideo;
	if (OUTPUT_VIDEO) {
		outputVideo.open(outputPath, 
		                 VideoWriter::fourcc('M', 'J', 'P', 'G'),
		                 fps, Size(width, height), true);  // true = color
		if (!outputVideo.isOpened()) {
			printf("Error: Cannot create output video file\n");
			return -1;
		}
	}
	
	printf("Processing video (Sequential Brightness/Contrast)...\n");
	
	double Total = getTickCount();
	int processedFrames = 0;
	Mat frame, adjusted;
	
	// Process video frame by frame
	while (true) {
		captureVideo >> frame;
		if (frame.empty()) break;
		
		// Apply brightness and contrast adjustment
		applyBrightnessContrast(frame, adjusted);
		
		// Write output
		if (OUTPUT_VIDEO) {
			outputVideo << adjusted;
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
	printf("Brightness/Contrast - Sequential\n");
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
