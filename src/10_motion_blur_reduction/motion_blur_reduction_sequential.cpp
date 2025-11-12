#include <opencv2/opencv.hpp>
#include <cstdio>
#include <deque>

using namespace std;
using namespace cv;

#define OUTPUT_VIDEO true
#define TEMPORAL_WINDOW 3  // Number of frames to average

void reduceMotionBlur(const deque<Mat> &frameWindow, Mat &output) {
	if (frameWindow.empty()) return;
	
	int rows = frameWindow[0].rows;
	int cols = frameWindow[0].cols;
	int channels = frameWindow[0].channels();
	
	output = Mat::zeros(rows, cols, frameWindow[0].type());
	
	// Temporal averaging across frames
	for (const auto &frame : frameWindow) {
		output += frame / (double)frameWindow.size();
	}
}

int main(int argc, const char** argv) {
	
	// Check arguments
	if (argc < 2) {
		printf("Usage: %s <video_file> [output_file]\n", argv[0]);
		printf("Example: %s input_videos/sample_video.mp4 outputs/10_motion_blur_reduction/output_sequential.avi\n", argv[0]);
		return 0;
	}
	
	// Set output path
	string outputPath = (argc >= 3) ? argv[2] : "outputs/10_motion_blur_reduction/motion_blur_reduction_sequential.avi";
	
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
	
	printf("Processing video (Sequential Motion Blur Reduction)...\n");
	
	double Total = getTickCount();
	int processedFrames = 0;
	Mat frame, output;
	deque<Mat> frameWindow;
	
	// Process video frame by frame
	while (true) {
		captureVideo >> frame;
		if (frame.empty()) break;
		
		// Add frame to temporal window
		frameWindow.push_back(frame.clone());
		if (frameWindow.size() > TEMPORAL_WINDOW) {
			frameWindow.pop_front();
		}
		
		// Apply motion blur reduction (temporal averaging)
		reduceMotionBlur(frameWindow, output);
		
		// Write output
		if (OUTPUT_VIDEO) {
			outputVideo << output;
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
	printf("Motion Blur - Sequential\n");
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
