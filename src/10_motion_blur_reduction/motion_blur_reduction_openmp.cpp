#include <opencv2/opencv.hpp>
#include <cstdio>
#include <vector>
#include <deque>
#include <omp.h>

using namespace std;
using namespace cv;

#define OUTPUT_VIDEO true
#define TEMPORAL_WINDOW 3

int threadNum;

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
	
	string outputPath = (argc >= 4) ? argv[3] : "outputs/10_motion_blur_reduction/motion_blur_reduction_openmp.avi";
	
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
	
	// Temporal buffer - must be sequential
	deque<Mat> temporalBuffer;
	Mat frame;
	
	// Set OpenMP threads
	omp_set_num_threads(threadNum);
	
	// Process frames sequentially (temporal dependency)
	while (true) {
		captureVideo >> frame;
		if (frame.empty()) break;
		
		// Add frame to temporal buffer
		temporalBuffer.push_back(frame.clone());
		
		// Keep only TEMPORAL_WINDOW frames
		if (temporalBuffer.size() > TEMPORAL_WINDOW) {
			temporalBuffer.pop_front();
		}
		
		// Temporal averaging using efficient approach
		Mat output = Mat::zeros(frame.rows, frame.cols, CV_32FC3);
		double weight = 1.0 / temporalBuffer.size();
		
		// Sum all frames in temporal window (parallelize this)
		for (const auto &tempFrame : temporalBuffer) {
			Mat floatFrame;
			tempFrame.convertTo(floatFrame, CV_32FC3);
			
			#pragma omp parallel for collapse(2) schedule(static)
			for (int i = 0; i < frame.rows; ++i) {
				for (int j = 0; j < frame.cols; ++j) {
					output.at<Vec3f>(i, j) += floatFrame.at<Vec3f>(i, j) * weight;
				}
			}
		}
		
		// Convert back to 8-bit
		Mat finalOutput;
		output.convertTo(finalOutput, CV_8UC3);
		
		// Write frame
		if (OUTPUT_VIDEO) {
			outputVideo << finalOutput;
		}
		
		processedFrames++;
		
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
	printf("Motion Blur Reduction - OpenMP\n");
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