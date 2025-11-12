#include <opencv2/opencv.hpp>
#include <cstdio>

using namespace std;
using namespace cv;

#define OUTPUT_VIDEO true

// Apply Canny Edge Detection
void applyEdgeDetection(const Mat &frame, Mat &output) {
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
	// Parameters: low threshold = 50, high threshold = 150
	Canny(gray, output, 50, 150);
}

int main(int argc, const char** argv) {
	
	// Check arguments
	if (argc < 2) {
		printf("Usage: %s <video_file> [output_file]\n", argv[0]);
		printf("Example: %s input_videos/sample_video.mp4 outputs/03_edge_detection/output_sequential.avi\n", argv[0]);
		return 0;
	}
	
	// Set output path
	string outputPath = (argc >= 3) ? argv[2] : "outputs/03_edge_detection/edge_detection_sequential.avi";
	
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
	
	// Setup video output (grayscale output for edge detection)
	VideoWriter outputVideo;
	if (OUTPUT_VIDEO) {
		outputVideo.open(outputPath, 
		                 VideoWriter::fourcc('M', 'J', 'P', 'G'),
		                 fps, Size(width, height), false);  // false = grayscale
		if (!outputVideo.isOpened()) {
			printf("Error: Cannot create output video file\n");
			return -1;
		}
	}
	
	printf("Processing video (Sequential Edge Detection)...\n");
	
	double Total = getTickCount();
	int processedFrames = 0;
	Mat frame, edges;
	
	// Process video frame by frame
	while (true) {
		captureVideo >> frame;
		if (frame.empty()) break;
		
		// Apply edge detection
		applyEdgeDetection(frame, edges);
		
		// Write output
		if (OUTPUT_VIDEO) {
			outputVideo << edges;
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
	printf("Edge Detection - Sequential\n");
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
