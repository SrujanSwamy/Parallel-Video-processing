#include <opencv2/opencv.hpp>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
using namespace cv;

// Multi-metric scene detection thresholds
#define HIST_THRESHOLD 0.70      // Histogram correlation threshold (lower = more sensitive)
#define EDGE_THRESHOLD 0.30      // Edge difference threshold (higher = more sensitive)
#define PIXEL_THRESHOLD 25.0     // Mean pixel difference threshold
#define MIN_SCENE_GAP 15         // Minimum frames between scene changes (avoid duplicates)

// Calculate histogram correlation between two frames
double calculateHistogramCorrelation(const Mat &frame1, const Mat &frame2) {
	Mat hsv1, hsv2;
	cvtColor(frame1, hsv1, COLOR_BGR2HSV);
	cvtColor(frame2, hsv2, COLOR_BGR2HSV);
	
	int h_bins = 50, s_bins = 60;
	int histSize[] = {h_bins, s_bins};
	float h_ranges[] = {0, 180};
	float s_ranges[] = {0, 256};
	const float* ranges[] = {h_ranges, s_ranges};
	int channels[] = {0, 1};
	
	Mat hist1, hist2;
	calcHist(&hsv1, 1, channels, Mat(), hist1, 2, histSize, ranges, true, false);
	calcHist(&hsv2, 1, channels, Mat(), hist2, 2, histSize, ranges, true, false);
	
	normalize(hist1, hist1, 0, 1, NORM_MINMAX);
	normalize(hist2, hist2, 0, 1, NORM_MINMAX);
	
	return compareHist(hist1, hist2, HISTCMP_CORREL);
}

// Calculate edge-based difference
double calculateEdgeDifference(const Mat &frame1, const Mat &frame2) {
	Mat gray1, gray2, edges1, edges2;
	cvtColor(frame1, gray1, COLOR_BGR2GRAY);
	cvtColor(frame2, gray2, COLOR_BGR2GRAY);
	
	// Apply Canny edge detection
	Canny(gray1, edges1, 50, 150);
	Canny(gray2, edges2, 50, 150);
	
	// Calculate difference in edge pixels
	Mat diff;
	absdiff(edges1, edges2, diff);
	
	// Return percentage of changed edge pixels
	return (double)countNonZero(diff) / (frame1.rows * frame1.cols);
}

// Calculate mean pixel difference
double calculatePixelDifference(const Mat &frame1, const Mat &frame2) {
	Mat diff;
	absdiff(frame1, frame2, diff);
	
	Scalar meanDiff = mean(diff);
	return (meanDiff[0] + meanDiff[1] + meanDiff[2]) / 3.0;
}

// Improved scene detection using multiple metrics
bool isSceneChange(const Mat &prevFrame, const Mat &currFrame, double &score) {
	// Calculate multiple metrics
	double histCorr = calculateHistogramCorrelation(prevFrame, currFrame);
	double edgeDiff = calculateEdgeDifference(prevFrame, currFrame);
	double pixelDiff = calculatePixelDifference(prevFrame, currFrame);
	
	// Combine metrics (weighted decision)
	bool histChange = (histCorr < HIST_THRESHOLD);
	bool edgeChange = (edgeDiff > EDGE_THRESHOLD);
	bool pixelChange = (pixelDiff > PIXEL_THRESHOLD);
	
	// Store combined score (0-100, higher = more likely scene change)
	score = 0.0;
	if (histChange) score += 40.0 * (1.0 - histCorr);
	if (edgeChange) score += 30.0 * edgeDiff;
	if (pixelChange) score += 30.0 * (pixelDiff / 100.0);
	
	// Scene change if at least 2 metrics agree OR very strong signal on any metric
	int agreementCount = (histChange ? 1 : 0) + (edgeChange ? 1 : 0) + (pixelChange ? 1 : 0);
	bool strongSignal = (histCorr < 0.50) || (edgeDiff > 0.50) || (pixelDiff > 50.0);
	
	return (agreementCount >= 2) || strongSignal;
}

int main(int argc, const char** argv) {
	
	// Check arguments
	if (argc < 2) {
		printf("Usage: %s <video_file> [output_file]\n", argv[0]);
		printf("Example: %s input_videos/sample_video.mp4 outputs/07_scene_detection/scenes_sequential.txt\n", argv[0]);
		return 0;
	}
	
	// Set output path
	string outputPath = (argc >= 3) ? argv[2] : "outputs/07_scene_detection/scene_detection_sequential.txt";
	
	// Open video file
	VideoCapture captureVideo(argv[1]);
	if (!captureVideo.isOpened()) {
		printf("Error: Cannot open video file: %s\n", argv[1]);
		return -1;
	}
	
	// Get video information
	int frameCount = (int)captureVideo.get(CAP_PROP_FRAME_COUNT);
	double fps = captureVideo.get(CAP_PROP_FPS);
	
	printf("Processing video (Sequential Scene Detection)...\n");
	printf("Total frames: %d, FPS: %.2f\n", frameCount, fps);
	
	double Total = getTickCount();
	
	vector<pair<int, double>> sceneChanges;  // frame number, timestamp
	vector<double> sceneScores;              // confidence scores
	Mat prevFrame, currFrame;
	int frameNumber = 0;
	int lastSceneFrame = -MIN_SCENE_GAP;  // Track last scene change
	
	// Read first frame
	captureVideo >> prevFrame;
	if (prevFrame.empty()) {
		printf("Error: Cannot read first frame\n");
		return -1;
	}
	frameNumber++;
	
	// Process video frame by frame
	while (true) {
		captureVideo >> currFrame;
		if (currFrame.empty()) break;
		
		frameNumber++;
		
		// Check for scene change using improved multi-metric detection
		double score = 0.0;
		if (isSceneChange(prevFrame, currFrame, score)) {
			// Avoid detecting same scene change multiple times
			if (frameNumber - lastSceneFrame >= MIN_SCENE_GAP) {
				double timestamp = frameNumber / fps;
				sceneChanges.push_back(make_pair(frameNumber, timestamp));
				sceneScores.push_back(score);
				lastSceneFrame = frameNumber;
				printf("  Scene change detected at frame %d (score: %.1f)\n", frameNumber, score);
			}
		}
		
		// Update previous frame
		prevFrame = currFrame.clone();
		
		// Show progress every 30 frames
		if (frameNumber % 30 == 0) {
			printf("  Processed %d frames...\r", frameNumber);
			fflush(stdout);
		}
	}
	
	Total = getTickCount() - Total;
	
	// Write results to file
	FILE *outFile = fopen(outputPath.c_str(), "w");
	if (outFile) {
		fprintf(outFile, "Scene Detection Results (Improved Multi-Metric)\n");
		fprintf(outFile, "================================================\n");
		fprintf(outFile, "Video: %s\n", argv[1]);
		fprintf(outFile, "Total frames: %d\n", frameNumber);
		fprintf(outFile, "FPS: %.2f\n", fps);
		fprintf(outFile, "Detection Method: Histogram + Edge + Pixel Analysis\n");
		fprintf(outFile, "Thresholds: Hist=%.2f, Edge=%.2f, Pixel=%.1f\n", HIST_THRESHOLD, EDGE_THRESHOLD, PIXEL_THRESHOLD);
		fprintf(outFile, "Detected scene changes: %d\n\n", (int)sceneChanges.size());
		
		fprintf(outFile, "Frame Number    Timestamp (s)    Confidence\n");
		fprintf(outFile, "------------------------------------------------\n");
		for (size_t i = 0; i < sceneChanges.size(); i++) {
			fprintf(outFile, "%-15d %-16.3f %.1f%%\n", 
				sceneChanges[i].first, 
				sceneChanges[i].second, 
				min(sceneScores[i], 100.0));
		}
		fclose(outFile);
	}
	
	// Print results
	printf("\n\n");
	printf("========================================\n");
	printf("Scene Detection - Sequential (Improved)\n");
	printf("========================================\n");
	printf("Processed frames: %d\n", frameNumber);
	printf("Detected scene changes: %d\n", (int)sceneChanges.size());
	printf("Detection: Multi-metric (Histogram + Edge + Pixel)\n");
	printf("Execution time: %.3fs\n", Total / getTickFrequency());
	printf("Average FPS: %.2f\n", frameNumber / (Total / getTickFrequency()));
	printf("Output saved to: %s\n", outputPath.c_str());
	printf("========================================\n");
	
	captureVideo.release();
	
	return 0;
}
