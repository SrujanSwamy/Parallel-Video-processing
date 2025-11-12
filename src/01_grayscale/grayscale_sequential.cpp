#include <opencv2/opencv.hpp>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <ctime>

#define SHOW_INFO false
#define OUTPUT_VIDEO true

using namespace std;
using namespace cv;

VideoWriter setOutput(const VideoCapture &input, const string &outputPath) {
	// Get video properties
	Size S = Size((int)input.get(CAP_PROP_FRAME_WIDTH),
		          (int)input.get(CAP_PROP_FRAME_HEIGHT));
	
	double fps = input.get(CAP_PROP_FPS);
	
	// Create video writer
	VideoWriter output;
	output.open(outputPath, 
	            VideoWriter::fourcc('M', 'J', 'P', 'G'),
	            fps, S, false);  // false = grayscale output
	
	return output;
}

void convertToGrayscale(Mat &frame) {
	// Manual grayscale conversion using standard luminosity method
	// Gray = 0.299*R + 0.587*G + 0.114*B
	
	int rows = frame.rows;
	int cols = frame.cols;
	
	// Optimize for continuous memory
	if (frame.isContinuous()) {
		cols *= rows;
		rows = 1;
	}
	
	// Convert BGR to grayscale
	for (int i = 0; i < rows; ++i) {
		Vec3b *p = frame.ptr<Vec3b>(i);
		for (int j = 0; j < cols; ++j) {
			// OpenCV uses BGR format: p[j][0]=B, p[j][1]=G, p[j][2]=R
			int gray = (int)(0.114 * p[j][0] +   // Blue
			                 0.587 * p[j][1] +   // Green
			                 0.299 * p[j][2]);   // Red
			
			// Set all channels to gray value
			p[j][0] = p[j][1] = p[j][2] = gray;
		}
	}
}

int main(int argc, const char** argv) {
	
	// Check arguments
	if (argc < 2) {
		printf("Usage: %s <video_file> [output_file]\n", argv[0]);
		printf("Example: %s input_videos/sample_video.mp4 outputs/01_grayscale/output_sequential.avi\n", argv[0]);
		return 0;
	}
	
	// Set output path
	string outputPath = (argc >= 3) ? argv[2] : "outputs/01_grayscale/grayscale_sequential.avi";
	
	// Open video file
	VideoCapture captureVideo(argv[1]);
	if (!captureVideo.isOpened()) {
		printf("Error: Cannot open video file: %s\n", argv[1]);
		return -1;
	}
	
	// Get video information
	int frameCount = (int)captureVideo.get(CAP_PROP_FRAME_COUNT);
	int fps = (int)captureVideo.get(CAP_PROP_FPS);
	int width = (int)captureVideo.get(CAP_PROP_FRAME_WIDTH);
	int height = (int)captureVideo.get(CAP_PROP_FRAME_HEIGHT);
	
	if (SHOW_INFO) {
		printf("Video Information:\n");
		printf("  Frames: %d\n", frameCount);
		printf("  FPS: %d\n", fps);
		printf("  Resolution: %dx%d\n", width, height);
		printf("\n");
	}
	
	// Setup video output
	VideoWriter outputVideo;
	if (OUTPUT_VIDEO) {
		outputVideo = setOutput(captureVideo, outputPath);
		if (!outputVideo.isOpened()) {
			printf("Error: Cannot create output video file\n");
			return -1;
		}
	}
	
	// Timing variables
	double Calculate = 0, Input = 0, Output = 0;
	double Total = getTickCount(), Last;
	
	int processedFrames = 0;
	Mat frame;
	
	printf("Processing video (Sequential)...\n");
	
	// Process video frame by frame
	while (true) {
		// Time input
		Last = getTickCount();
		captureVideo >> frame;
		if (frame.empty()) break;
		Input += getTickCount() - Last;
		
		// Time processing
		Last = getTickCount();
		convertToGrayscale(frame);
		Calculate += getTickCount() - Last;
		
		// Time output
		if (OUTPUT_VIDEO) {
			Last = getTickCount();
			
			// Convert to grayscale for output
			Mat grayFrame;
			cvtColor(frame, grayFrame, COLOR_BGR2GRAY);
			outputVideo << grayFrame;
			
			Output += getTickCount() - Last;
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
	printf("Grayscale Conversion - Sequential\n");
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
