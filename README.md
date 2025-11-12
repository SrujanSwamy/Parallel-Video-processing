# Parallel Video Processing System# Parallel Video Processing System# Parallel Video Processing System# Parallel Video Processing System# 🎥 Parallel Video Processing System



A full-stack web application for comparing parallel video processing performance using **Sequential**, **Pthread**, and **OpenMP** implementations across 12 different video processing algorithms.



## OverviewA full-stack application for parallel video processing using OpenMP, Pthreads, and Sequential implementations. Features a React frontend, Flask backend, and 12 different video processing algorithms implemented in C++.



This application demonstrates the performance benefits of parallel computing in video processing. Built with a React frontend, Flask backend, and C++ processing engines, it provides a comprehensive platform for analyzing and comparing different parallelization strategies on real video data.



**Key Highlights:**## FeaturesA full-stack application for parallel video processing using OpenMP, Pthreads, and Sequential implementations. Features a React frontend, Flask backend, and 12 different video processing algorithms implemented in C++.



- **12 Processing Algorithms**: Complete suite of image and video enhancement techniques

- **3 Implementation Types**: Sequential baseline, Pthread, and OpenMP parallel versions

- **Real-time Performance Analysis**: Automatic speedup calculations and efficiency metrics### Video Processing Algorithms

- **Modern Web Interface**: Responsive React dashboard with video comparison and graphs

- **Production-Ready**: RESTful API, automatic video format conversion, and error handling1. **Grayscale** - Convert videos to grayscale



## Features2. **Gaussian Blur** - Apply Gaussian blur filter## FeaturesA full-stack application for parallel video processing using OpenMP, Pthreads, and Sequential implementations. Features a React frontend, Flask backend, and 12 different video processing algorithms implemented in C++.A full-stack web application for comparing parallel video processing performance using **Sequential**, **Pthread**, and **OpenMP** implementations across 12 different image/video processing algorithms.



### Video Processing Algorithms3. **Edge Detection** - Detect edges using Canny algorithm



1. **Grayscale Conversion** - Convert color videos to grayscale4. **White Balance** - Automatic white balance correction

2. **Gaussian Blur** - Apply Gaussian smoothing filter

3. **Edge Detection** - Canny edge detection algorithm5. **Histogram Equalization** - Enhance image contrast

4. **White Balance** - Automatic color correction

5. **Histogram Equalization** - Contrast enhancement6. **Frame Sharpening** - Sharpen video frames### Video Processing Algorithms

6. **Frame Sharpening** - Enhance image sharpness

7. **Scene Detection** - Identify scene changes with confidence scores7. **Scene Detection** - Detect scene changes with confidence scores

8. **Background Subtraction** - Foreground object extraction

9. **Brightness/Contrast Adjustment** - Dynamic range modification8. **Background Subtraction** - Extract foreground objects1. **Grayscale** - Convert videos to grayscale

10. **Motion Blur** - Motion blur effect application

11. **Contrast Enhancement** - Local contrast improvement9. **Brightness/Contrast** - Adjust brightness and contrast

12. **Lightup** - Brighten underexposed videos

10. **Motion Blur** - Apply motion blur effect2. **Gaussian Blur** - Apply Gaussian blur filter##  Features##  Table of Contents

### Parallel Implementations

11. **Contrast Enhancement** - Enhance local contrast

Each algorithm is implemented in three ways:

12. **Lightup** - Brighten dark videos3. **Edge Detection** - Detect edges using Canny algorithm

- **Sequential** - Single-threaded baseline for performance comparison

- **Pthread** - Multi-threaded implementation using POSIX threads with manual thread management

- **OpenMP** - Multi-threaded implementation using OpenMP directives with automatic parallelization

### Parallel Implementations4. **White Balance** - Automatic white balance correction- [Features](#features)

### Performance Metrics

Each algorithm is implemented in three ways:

- **Execution Time** - Wall-clock time for each implementation

- **Speedup** - Sequential time divided by parallel time- **Sequential** - Single-threaded baseline implementation5. **Histogram Equalization** - Enhance image contrast

- **Frames Per Second (FPS)** - Processing throughput

- **Parallel Efficiency** - Speedup divided by number of threads- **Pthreads** - Multi-threaded using POSIX threads

- **Thread Utilization** - Resource usage analysis

- **OpenMP** - Multi-threaded using OpenMP directives6. **Frame Sharpening** - Sharpen video frames### Video Processing Algorithms- [Tech Stack](#tech-stack)

### User Experience



- **Video Upload** - Support for MP4 and AVI formats

- **Real-time Progress** - Live status updates during processing### Performance Metrics7. **Scene Detection** - Detect scene changes with confidence scores

- **Side-by-side Comparison** - View input and output videos simultaneously

- **Interactive Charts** - Visualize performance metrics with Recharts- Execution time for each implementation

- **Result Export** - Download processed videos and performance data

- Speedup calculations (Sequential time / Parallel time)8. **Background Subtraction** - Extract foreground objects1. **Grayscale** - Convert videos to grayscale- [Project Structure](#project-structure)

## Tech Stack

- Frames per second (FPS)

### Backend

- Parallel efficiency9. **Brightness/Contrast** - Adjust brightness and contrast

- **Python 3.11.9** - Core language

- **Flask 3.0.0** - Lightweight web framework- Thread utilization

- **Flask-CORS 4.0.0** - Cross-Origin Resource Sharing

- **OpenCV 4.10.0.84** - Video processing and format conversion10. **Motion Blur** - Apply motion blur effect2. **Gaussian Blur** - Apply Gaussian blur filter- [Prerequisites](#prerequisites)

- **RESTful API** - 9 endpoints for upload, processing, and results

## Prerequisites

### Frontend

11. **Contrast Enhancement** - Enhance local contrast

- **React 18.2.0** - UI framework

- **TypeScript** - Type-safe JavaScript### Backend Requirements

- **Tailwind CSS** - Utility-first styling

- **Axios** - HTTP client for API requests- Python 3.11.9 or higher12. **Lightup** - Brighten dark videos3. **Edge Detection** - Detect edges using Canny algorithm- [Installation](#installation)

- **Recharts** - Data visualization library

- **Vite** - Modern build tool- OpenCV 4.10.0.84



### C++ Processing Engine- Flask 3.0.0



- **g++ 13.2.0** - Compiler (MSYS2 UCRT64)- MSYS2 UCRT64 environment with g++ 13.2.0

- **OpenCV 4.x** - Computer vision library

- **OpenMP** - Parallel programming API### Parallel Implementations4. **White Balance** - Automatic white balance correction- [Usage](#usage)

- **pthread** - POSIX threads library

- **MJPEG/MP4** - Video codecs### Frontend Requirements



## Project Structure- Node.js 16.x or higherEach algorithm is implemented in three ways:



```- npm or yarn

parallel_analysis-master/

├── backend/                        # Flask API server- **Sequential** - Single-threaded baseline implementation5. **Histogram Equalization** - Enhance image contrast- [Processing Features](#processing-features)

│   ├── app.py                     # Main Flask application (9 endpoints)

│   ├── requirements.txt           # Python dependencies### C++ Compiler

│   └── utils/

│       ├── video_processor.py     # Video processing orchestration- g++ with OpenMP support- **Pthreads** - Multi-threaded using POSIX threads

│       ├── video_converter.py     # AVI to MP4 conversion

│       └── results_parser.py      # Parse C++ execution results- pthread library

│

├── frontend/                       # React web application- OpenCV 4.x development files- **OpenMP** - Multi-threaded using OpenMP directives6. **Frame Sharpening** - Sharpen video frames- [Performance Metrics](#performance-metrics)

│   ├── src/

│   │   ├── App.tsx                # Main component with state management

│   │   ├── types.ts               # TypeScript interfaces

│   │   └── components/## Installation

│   │       ├── ConfigPanel.tsx           # Upload and configuration

│   │       ├── ProcessingStatus.tsx      # Progress indicator

│   │       ├── VideoComparison.tsx       # Video players

│   │       ├── VideoPlayer.tsx           # Individual video player### 1. Clone the Repository### Performance Metrics7. **Scene Detection** - Detect scene changes with confidence scores- [Architecture](#architecture)

│   │       ├── PerformanceMetrics.tsx    # Metrics table

│   │       ├── SpeedupChart.tsx          # Bar chart visualization```bash

│   │       └── SceneDetectionResults.tsx # Text results display

│   ├── package.jsongit clone <repository-url>- Execution time for each implementation

│   └── tailwind.config.js

│cd parallel_analysis-master

├── src/                            # C++ source code (12 features)

│   ├── 01_grayscale/```- Speedup calculations (Sequential time / Parallel time)8. **Background Subtraction** - Extract foreground objects- [Contributing](#contributing)

│   │   ├── grayscale_sequential.cpp

│   │   ├── grayscale_pthread.cpp

│   │   ├── grayscale_openmp.cpp

│   │   └── run_grayscale.ps1### 2. Backend Setup- Frames per second (FPS)

│   ├── 02_gaussian_blur/

│   ├── 03_edge_detection/```bash

│   ├── 04_white_balance/

│   ├── 05_histogram_equalization/cd backend- Parallel efficiency9. **Brightness/Contrast** - Adjust brightness and contrast

│   ├── 06_frame_sharpening/

│   ├── 07_scene_detection/pip install -r requirements.txt

│   ├── 08_background_subtraction/

│   ├── 09_brightness_contrast/```- Thread utilization

│   ├── 10_motion_blur_reduction/

│   ├── 11_contrast_enhancement/

│   └── 12_lightup/

│**Required Python packages:**10. **Motion Blur** - Apply motion blur effect##  Features

├── build/                          # Compiled executables (36 files)

├── input_videos/                   # User uploads (ignored by git)- Flask==3.0.0

├── outputs/                        # Processed videos (ignored by git)

├── results/                        # Performance logs (ignored by git)- flask-cors==4.0.0## Prerequisites

│

├── compile.ps1                     # C++ compilation script- opencv-python==4.10.0.84

├── start-app.ps1                   # Application launcher

├── clean-repo.ps1                  # Cleanup utility11. **Contrast Enhancement** - Enhance local contrast

└── .gitignore                      # Git ignore rules

```### 3. Frontend Setup



## Setup and Installation```bash### Backend Requirements



### Prerequisitescd frontend



- **Python 3.11.9+** and pipnpm install- Python 3.11.9 or higher12. **Lightup** - Brighten dark videos- **12 Video Processing Algorithms**

- **Node.js 16+** and npm

- **MSYS2 UCRT64** environment (Windows)```

- **g++ 13.2.0+** with OpenMP support

- **OpenCV 4.x** development files- OpenCV 4.10.0.84



### 1. Clone the Repository**Key dependencies:**



```bash- React 18.2.0- Flask 3.0.0  - Grayscale Conversion

git clone https://github.com/SrujanSwamy/Parallel-Video-processing.git

cd parallel_analysis-master- TypeScript

```

- Tailwind CSS- MSYS2 UCRT64 environment with g++ 13.2.0

### 2. Backend Setup

- Axios for API calls

```bash

# Navigate to backend directory- Recharts for performance graphs### Parallel Implementations  - Gaussian Blur

cd backend



# Install Python dependencies

pip install -r requirements.txt### 4. Compile C++ Programs### Frontend Requirements



# Verify installationsFrom the root directory:

python -c "import flask; import cv2; print('Backend ready')"

``````powershell- Node.js 16.x or higherEach algorithm is implemented in three ways:  - Edge Detection (Sobel)



**Required Python packages:**.\compile.ps1

- Flask==3.0.0

- flask-cors==4.0.0```- npm or yarn

- opencv-python==4.10.0.84



### 3. Frontend Setup

This compiles all 36 C++ programs (12 features × 3 implementations) and places executables in the `build/` directory.- **Sequential** - Single-threaded baseline implementation  - White Balance

```bash

# Navigate to frontend directory

cd frontend

## Running the Application### C++ Compiler

# Install Node.js dependencies

npm install



# Verify installation### Quick Start (Recommended)- g++ with OpenMP support- **Pthreads** - Multi-threaded using POSIX threads  - Histogram Equalization

npm list react

```From the root directory:



**Key dependencies:**```powershell- pthread library

- React 18.2.0

- TypeScript.\start-app.ps1

- Tailwind CSS

- Axios```- OpenCV 4.x development files- **OpenMP** - Multi-threaded using OpenMP directives  - Frame Sharpening

- Recharts



### 4. Compile C++ Programs

This script:

From the root directory:

1. Starts the Flask backend on http://localhost:5000

```powershell

# Compile all 36 C++ programs (12 features × 3 implementations)2. Starts the React frontend on http://localhost:3000## Installation  - Scene Detection

.\compile.ps1

3. Opens your default browser automatically

# Executables will be placed in build/ directory

```



**Note:** Ensure MSYS2 UCRT64 is in your PATH:### Manual Start



```bash### 1. Clone the Repository### Performance Metrics  - Background Subtraction

# Install required packages

pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-opencv**Backend:**

```

```bash```bash

### 5. Running the Application

cd backend

#### Quick Start (Recommended)

python app.pygit clone <repository-url>- Execution time for each implementation  - Brightness/Contrast Adjustment

```powershell

# From root directory```

.\start-app.ps1

cd parallel_analysis-master

# This script will:

# 1. Start Flask backend on http://localhost:5000**Frontend:**

# 2. Start React frontend on http://localhost:3000

# 3. Open browser automatically```bash```- Speedup calculations (Sequential time / Parallel time)  - Motion Blur Reduction

```

cd frontend

#### Manual Start

npm start

**Terminal 1 - Backend:**

```bash```

cd backend

python app.py### 2. Backend Setup- Frames per second (FPS)  - Contrast Enhancement

# Backend API available at http://localhost:5000/api

```## Usage



**Terminal 2 - Frontend:**```bash

```bash

cd frontend1. **Upload Video**: Click "Choose Video" and select an MP4 or AVI file

npm start

# Frontend UI available at http://localhost:30002. **Select Feature**: Choose from the dropdown menu (e.g., Grayscale, Edge Detection)cd backend- Parallel efficiency  - Light Enhancement

```

3. **Set Thread Count**: Specify number of threads for Pthread/OpenMP (default: 4)

## Usage Guide

4. **Process**: Click "Process Video" to start processingpip install -r requirements.txt

### 1. Upload Video

5. **View Results**: 

1. Navigate to http://localhost:3000

2. Click **Choose Video** button   - Watch input and output videos side by side```- Thread utilization

3. Select MP4 or AVI file (max recommended: 100MB)

4. File uploads to backend `/api/upload` endpoint   - Compare Sequential, Pthread, and OpenMP performance



### 2. Configure Processing   - Analyze speedup graphs and metrics



1. **Select Feature** - Choose from dropdown (e.g., Grayscale, Edge Detection)

2. **Set Thread Count** - Specify threads for Pthread/OpenMP (default: 4, range: 1-16)

3. **Review Settings** - Confirm feature and thread configuration### Special Cases**Required Python packages:**- **Three Parallel Implementations**



### 3. Start Processing



1. Click **Process Video** button**Scene Detection**: Outputs frame numbers and timestamps of detected scene changes instead of a processed video.- Flask==3.0.0

2. Backend executes three implementations sequentially:

   - Sequential (baseline)

   - Pthread (with specified thread count)

   - OpenMP (with specified thread count)**Large Videos**: Processing time depends on video length and selected feature. Progress updates appear in real-time.- flask-cors==4.0.0##  Prerequisites  - Sequential (baseline)

3. Progress updates every 2 seconds via HTTP polling



### 4. View Results

## Project Structure- opencv-python==4.10.0.84

#### Video Comparison

- **Input Video** - Original uploaded video

- **Sequential Output** - Single-threaded result

- **Pthread Output** - Multi-threaded (Pthread) result```  - Pthread (POSIX threads)

- **OpenMP Output** - Multi-threaded (OpenMP) result

parallel_analysis-master/

#### Performance Metrics Table

| Metric | Sequential | Pthread | OpenMP |├── backend/                    # Flask API server### 3. Frontend Setup

|--------|-----------|---------|---------|

| Execution Time | Baseline | Reduced | Reduced |│   ├── app.py                 # Main Flask application (9 endpoints)

| Speedup | 1.00x | 2-4x | 2-4x |

| FPS | Baseline | Higher | Higher |│   ├── video_processor.py     # Video processing orchestration```bash### Backend Requirements  - OpenMP (Open Multi-Processing)

| Efficiency | N/A | 50-80% | 50-80% |

│   ├── video_converter.py     # AVI to MP4 conversion

#### Speedup Chart

- Bar chart comparing speedup values│   ├── results_parser.py      # Parse C++ execution resultscd frontend

- X-axis: Implementation type

- Y-axis: Speedup ratio│   └── requirements.txt



### 5. Special Case - Scene Detection├── frontend/                   # React web applicationnpm install- Python 3.11.9 or higher



Scene Detection outputs **text results** instead of processed video:│   ├── src/



- **Frame Numbers** - Detected scene change frames│   │   ├── App.tsx            # Main component with state management```

- **Timestamps** - Time position in video

- **Confidence Scores** - Detection confidence (0-100%)│   │   ├── components/        # React components

- **Metrics** - Histogram, edge, and pixel difference analysis

│   │   │   ├── ConfigPanel.tsx- OpenCV 4.10.0.84- **Web-Based Interface**

**Detection Thresholds:**

- Histogram Correlation: 0.70 (lower = more different)│   │   │   ├── ProcessingStatus.tsx

- Edge Difference: 0.30 (higher = more different)

- Pixel Difference: 25.0 (normalized)│   │   │   ├── VideoComparison.tsx**Key dependencies:**

- Minimum Scene Gap: 15 frames

│   │   │   ├── PerformanceMetrics.tsx

### 6. Cleanup

│   │   │   ├── SpeedupChart.tsx- React 18.2.0- Flask 3.0.0  - Upload videos

```powershell

# Remove all generated files│   │   │   └── SceneDetectionResults.tsx

.\clean-repo.ps1

│   │   └── types.ts           # TypeScript interfaces- TypeScript

# This removes:

# - Compiled executables (build/*.exe)│   └── package.json

# - Uploaded videos (input_videos/*.mp4)

# - Processed outputs (outputs/**/*.mp4)├── src/                        # C++ source code- Tailwind CSS- MSYS2 UCRT64 environment with g++ 13.2.0  - Select processing features

# - Performance logs (results/*.txt)

# - Python cache (__pycache__)│   ├── 01_grayscale/

```

│   ├── 02_gaussian_blur/- Axios for API calls

## API Endpoints

│   ├── 03_edge_detection/

### Backend API (Flask)

│   ├── 04_white_balance/- Recharts for performance graphs  - Configure thread counts

```

POST   /api/upload                              - Upload video file│   ├── 05_histogram_equalization/

POST   /api/process                             - Start video processing

GET    /api/status/<job_id>                     - Get processing status│   ├── 06_frame_sharpening/

GET    /api/results/<job_id>                    - Get performance metrics

GET    /api/video/<job_id>/<method>/<type>      - Stream processed video│   ├── 07_scene_detection/

GET    /api/scene/<job_id>/<scene_type>         - Get scene detection text

DELETE /api/cleanup/<job_id>                    - Cleanup job files│   ├── 08_background_subtraction/### 4. Compile C++ Programs### Frontend Requirements  - Real-time progress tracking

GET    /api/health                              - Health check

GET    /api/features                            - List available features│   ├── 09_brightness_contrast/

```

│   ├── 10_motion_blur_reduction/From the root directory:

**Example Request:**

│   ├── 11_contrast_enhancement/

```bash

# Upload video│   └── 12_lightup/```powershell- Node.js 16.x or higher  - Side-by-side video comparison

curl -X POST -F "video=@input.mp4" http://localhost:5000/api/upload

├── build/                      # Compiled C++ executables (36 files)

# Start processing

curl -X POST http://localhost:5000/api/process \├── input_videos/               # User-uploaded videos.\compile.ps1

  -H "Content-Type: application/json" \

  -d '{"job_id": "abc123", "feature": "Grayscale", "num_threads": 4}'├── outputs/                    # Processed video outputs



# Get results├── results/                    # Performance logs and graphs```- npm or yarn  - Performance metrics and graphs

curl http://localhost:5000/api/results/abc123

```├── compile.ps1                 # Compilation script



**Example Response:**├── start-app.ps1               # Application launcher



```json├── clean-repo.ps1              # Repository cleanup utility

{

  "sequential": {└── .gitignore                  # Git ignore rulesThis compiles all 36 C++ programs (12 features × 3 implementations) and places executables in the `build/` directory.

    "execution_time": 12.45,

    "fps": 24.5,```

    "output_video": "grayscale_sequential.mp4"

  },

  "pthread": {

    "execution_time": 4.23,## API Endpoints

    "fps": 72.1,

    "speedup": 2.94,## Running the Application### C++ Compiler- **Comprehensive Metrics**

    "efficiency": 73.5,

    "output_video": "grayscale_pthread.mp4"### Backend API (Flask)

  },

  "openmp": {- `POST /api/upload` - Upload video file

    "execution_time": 3.87,

    "fps": 78.8,- `POST /api/process` - Start video processing

    "speedup": 3.22,

    "efficiency": 80.5,- `GET /api/status/<job_id>` - Get processing status### Quick Start (Recommended)- g++ with OpenMP support  - Execution time

    "output_video": "grayscale_openmp.mp4"

  }- `GET /api/results/<job_id>` - Get performance metrics

}

```- `GET /api/video/<job_id>/<method>/<video_type>` - Stream videoFrom the root directory:



## Algorithm Details- `GET /api/scene/<job_id>/<scene_type>` - Get scene detection results



### Scene Detection Implementation- `DELETE /api/cleanup/<job_id>` - Cleanup job files```powershell- pthread library  - Frames per second (FPS)



**Multi-Metric Approach:**- `GET /api/health` - Health check endpoint



1. **Histogram Correlation** - Compares color distribution between consecutive frames using correlation coefficient.\start-app.ps1

2. **Edge Detection** - Analyzes structural changes using Canny edge detection and edge density comparison

3. **Pixel Difference** - Measures absolute pixel value changes frame-to-frame## Algorithm Details



**Implementation:**```- OpenCV 4.x development files  - Speedup calculation



```cpp### Scene Detection

// Pseudo-code for scene detection

for each frame i from 1 to N-1:Uses a multi-metric approach:

    hist_corr = compareHist(frame[i], frame[i+1], HISTCMP_CORREL)

    edge_diff = computeEdgeDifference(frame[i], frame[i+1])- **Histogram Correlation**: Compares color distribution between frames

    pixel_diff = computePixelDifference(frame[i], frame[i+1])

    - **Edge Detection**: Analyzes structural changes using Canny edge detectionThis script:  - Parallel efficiency

    if (hist_corr < 0.70 && edge_diff > 0.30 && pixel_diff > 25.0):

        if (i - last_scene_frame > 15):- **Pixel Difference**: Measures absolute pixel value changes

            mark_as_scene_change(i)

            confidence = calculate_confidence(hist_corr, edge_diff, pixel_diff)1. Starts the Flask backend on http://localhost:5000

```

Thresholds:

### Parallelization Strategies

- Histogram: 0.70 (lower = more different)2. Starts the React frontend on http://localhost:3000## 🔧 Installation  - Interactive performance charts

#### OpenMP Approach

- **Loop-level Parallelization** - `#pragma omp parallel for` on frame processing loops- Edge: 0.30 (higher = more different)

- **Dynamic Scheduling** - `schedule(dynamic)` for load balancing

- **Automatic Thread Management** - Runtime determines optimal thread distribution- Pixel: 25.0 (normalized difference)3. Opens your default browser automatically



```cpp- Minimum gap between scenes: 15 frames

#pragma omp parallel for schedule(dynamic)

for (int i = 0; i < total_frames; i++) {

    process_frame(frames[i]);

}Output includes frame number, timestamp, and confidence score.

```

### Manual Start

#### Pthread Approach

- **Frame-chunk Distribution** - Divide frames into equal chunks per thread### Performance Optimization

- **Manual Thread Creation** - Explicit `pthread_create()` and `pthread_join()`

- **Shared Memory** - Frame buffer shared between threads with synchronization- **OpenMP**: Loop-level parallelization with dynamic scheduling### 1. Clone the Repository## 🛠️ Tech Stack



```cpp- **Pthreads**: Frame-chunk distribution across threads

pthread_t threads[NUM_THREADS];

for (int i = 0; i < NUM_THREADS; i++) {- **Sequential**: Optimized baseline for comparison**Backend:**

    thread_data[i] = {start_frame, end_frame, frames};

    pthread_create(&threads[i], NULL, process_chunk, &thread_data[i]);

}

for (int i = 0; i < NUM_THREADS; i++) {## Maintenance```bash```bash

    pthread_join(threads[i], NULL);

}

```

### Clean Repositorycd backend

## Configuration

```powershell

### Thread Count Guidelines

.\clean-repo.ps1python app.pygit clone <repository-url>### Backend

- **Default**: 4 threads

- **Recommended**: Number of physical CPU cores```

- **Range**: 1-16 threads

- **Optimal**: Test different values for your hardware```



**Performance Notes:**Removes:

- Speedup is not linear due to overhead and memory bandwidth

- Efficiency decreases as thread count increases (Amdahl's Law)- Build artifacts (executables, object files)cd parallel_analysis-master- **Python 3.11+** - API server

- Hyper-threading may not provide additional benefit

- Temporary files and logs

### Video Format Support

- Generated videos in input_videos/ and outputs/**Frontend:**

| Format | Input | Processing | Output |

|--------|-------|-----------|---------|- Python cache files

| MP4 | ✓ | Converted to AVI | ✓ (mp4v codec) |

| AVI | ✓ | MJPEG codec | ✓ (converted to MP4) |- Node modules (optional)```bash```- **Flask 3.0** - Web framework

| MOV | ✗ | N/A | ✗ |

| MKV | ✗ | N/A | ✗ |



**Conversion Pipeline:**## Configurationcd frontend

1. User uploads MP4/AVI

2. C++ processes as AVI (MJPEG)

3. Python converts output to MP4 (mp4v)

4. Browser streams MP4 with range requests### Thread Countnpm start- **OpenCV 4.x** - Video processing



## Troubleshooting- Default: 4 threads



### PowerShell Execution Policy- Recommended: Number of CPU cores```



**Issue:** Scripts fail with "cannot be loaded because running scripts is disabled"- Range: 1-16 threads



**Solution:**### 2. Backend Setup- **C++17** - Parallel implementations

```powershell

Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser### Video Formats

```

- **Input**: MP4, AVI (MJPEG codec)## Usage

### Compilation Errors

- **Processing**: AVI intermediate format

**Issue:** `g++: command not found` or OpenCV headers missing

- **Output**: MP4 (mp4v codec) for browser compatibility```bash

**Solution (MSYS2 UCRT64):**

```bash

# Install compiler and OpenCV

pacman -S mingw-w64-ucrt-x86_64-gcc## Troubleshooting1. **Upload Video**: Click "Choose Video" and select an MP4 or AVI file

pacman -S mingw-w64-ucrt-x86_64-opencv



# Add to PATH (Windows)

setx PATH "%PATH%;C:\msys64\ucrt64\bin"### PowerShell Execution Policy2. **Select Feature**: Choose from the dropdown menu (e.g., Grayscale, Edge Detection)cd backend### Frontend

```

If scripts fail to run:

### Port Already in Use

```powershell3. **Set Thread Count**: Specify number of threads for Pthread/OpenMP (default: 4)

**Issue:** `Address already in use: Port 5000` or `Port 3000`

Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser

**Solution:**

```bash```4. **Process**: Click "Process Video" to start processingpip install -r requirements.txt- **React 18.2** - UI framework

# Find process using port (Windows)

netstat -ano | findstr :5000

taskkill /PID <PID> /F

### Compilation Errors5. **View Results**: 

# Change port in configuration

# Backend: Edit app.py (line: app.run(port=5000))Ensure MSYS2 UCRT64 is installed:

# Frontend: Edit package.json (add: "start": "vite --port 3001")

``````bash   - Watch input and output videos side by side```- **TypeScript** - Type safety



### Video Not Playing in Browserpacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-opencv



**Issue:** Video loads but doesn't play or shows black screen```   - Compare Sequential, Pthread, and OpenMP performance



**Solutions:**

1. **Check browser console** - Look for codec errors

2. **Verify MP4 conversion** - Ensure `outputs/*.mp4` files exist### Port Already in Use   - Analyze speedup graphs and metrics- **Tailwind CSS** - Styling

3. **Test video locally** - Open MP4 file in VLC/media player

4. **Browser compatibility** - Use Chrome/Edge (best support)Change ports in:

5. **Range request issues** - Check backend logs for 416 errors

- Backend: `app.py` (default 5000)

### Performance Issues

- Frontend: `package.json` (default 3000)

**Issue:** Processing is slower than expected or speedup < 2.0x

### Special Cases**Required Python packages:**- **Recharts** - Performance visualization

**Solutions:**

1. **Check CPU usage** - Ensure threads are utilizing cores### Video Not Playing

2. **Reduce video size** - Test with smaller resolution/duration

3. **Disable background apps** - Free up CPU resources- Ensure browser supports MP4 format

4. **Verify thread count** - Match to physical core count

5. **Check thermal throttling** - Monitor CPU temperature- Check browser console for errors



## Performance Analysis- Verify video file integrity**Scene Detection**: Outputs frame numbers and timestamps of detected scene changes instead of a processed video.- Flask==3.0.0- **Axios** - HTTP client



### Speedup Formula



```## Performance Analysis

Speedup = Sequential Execution Time / Parallel Execution Time

```



**Example:**The application automatically generates:**Large Videos**: Processing time depends on video length and selected feature. Progress updates appear in real-time.- flask-cors==4.0.0

- Sequential: 12.5 seconds

- Pthread (4 threads): 4.2 seconds- Execution time comparison charts

- Speedup: 12.5 / 4.2 = 2.98x

- Speedup calculations (Sequential vs Parallel)

### Efficiency Formula

- Parallel efficiency metrics

```

Efficiency = Speedup / Number of Threads × 100%- FPS (Frames Per Second) statistics## Project Structure- opencv-python==4.10.0.84### Build Tools

```



**Example:**

- Speedup: 2.98x**Speedup Formula**: `Speedup = Sequential Time / Parallel Time`

- Threads: 4

- Efficiency: 2.98 / 4 = 74.5%



### Amdahl's Law**Efficiency Formula**: `Efficiency = Speedup / Number of Threads````- **g++ (MSYS2)** - C++ compiler



```

Speedup_max = 1 / ((1 - P) + P/N)

```## Contributingparallel_analysis-master/



Where:

- P = Parallelizable portion of code (0.0 to 1.0)

- N = Number of threads1. Fork the repository├── backend/                    # Flask API server### 3. Frontend Setup- **OpenMP** - Parallel programming



**Implications:**2. Create a feature branch

- Even with infinite threads, speedup is limited by serial portion

- 90% parallel code (P=0.9) → max speedup = 10x3. Make your changes│   ├── app.py                 # Main Flask application (9 endpoints)

- 95% parallel code (P=0.95) → max speedup = 20x

4. Test thoroughly

## Contributing

5. Submit a pull request│   ├── video_processor.py     # Video processing orchestration```bash- **pthread** - POSIX threads

Contributions are welcome! Please follow these guidelines:



1. **Fork the repository**

2. **Create a feature branch** - `git checkout -b feature/new-algorithm`## License│   ├── video_converter.py     # AVI to MP4 conversion

3. **Commit changes** - `git commit -m "Add new algorithm"`

4. **Push to branch** - `git push origin feature/new-algorithm`

5. **Open Pull Request** - Describe changes and test results

This project is for educational purposes. Please ensure proper attribution when using or modifying the code.│   ├── results_parser.py      # Parse C++ execution resultscd frontend

**Development Guidelines:**

- Follow existing code style (C++ and Python)

- Add comments for complex logic

- Test all three implementations (Sequential, Pthread, OpenMP)## Additional Notes│   └── requirements.txt

- Update README if adding new features



## License

- All C++ programs write execution metrics to text files├── frontend/                   # React web applicationnpm install##  Project Structure

This project is for educational purposes as part of a Parallel and Distributed Computing course. Please ensure proper attribution when using or modifying the code.

- Backend automatically converts AVI outputs to MP4 for web compatibility

## Additional Notes

- Frontend polls backend every 2 seconds for status updates│   ├── src/

- All C++ programs write execution metrics to `.txt` files in the `outputs/` directory

- Backend automatically converts AVI outputs to MP4 for web browser compatibility- Scene detection outputs text results instead of video files

- Frontend polls backend every 2 seconds for status updates (no WebSocket required)

- Scene detection is the only feature that outputs text results instead of video- Performance metrics are calculated on the backend and displayed in real-time│   │   ├── App.tsx            # Main component with state management```

- Performance metrics are calculated on the backend using wall-clock time

- Video streaming uses HTTP range requests for efficient playback



## Acknowledgments## Support│   │   ├── components/        # React components



- OpenCV community for computer vision library

- OpenMP and pthread documentation

- React and Flask communitiesFor issues, bugs, or feature requests, please open an issue in the repository.│   │   │   ├── ConfigPanel.tsx```

- Course instructors and TAs



---

---│   │   │   ├── ProcessingStatus.tsx

**Built with:** React • TypeScript • Flask • OpenCV • OpenMP • Pthreads



**Developed for:** Parallel and Distributed Computing Course

**Built with**: React • TypeScript • Flask • OpenCV • OpenMP • Pthreads│   │   │   ├── VideoComparison.tsx**Key dependencies:**parallel_analysis-master/

**Author:** Srujan Swamy



**Repository:** [https://github.com/SrujanSwamy/Parallel-Video-processing](https://github.com/SrujanSwamy/Parallel-Video-processing)

**Developed for**: Parallel and Distributed Computing Course│   │   │   ├── PerformanceMetrics.tsx


│   │   │   ├── SpeedupChart.tsx- React 18.2.0├── backend/                 # Flask API server

│   │   │   └── SceneDetectionResults.tsx

│   │   └── types.ts           # TypeScript interfaces- TypeScript│   ├── app.py              # Main API endpoints

│   └── package.json

├── src/                        # C++ source code- Tailwind CSS│   ├── utils/              # Utility modules

│   ├── 01_grayscale/

│   ├── 02_gaussian_blur/- Axios for API calls│   │   ├── video_processor.py  # Video processing orchestrator

│   ├── 03_edge_detection/

│   ├── 04_white_balance/- Recharts for performance graphs│   │   ├── parser.py           # Output parser

│   ├── 05_histogram_equalization/

│   ├── 06_frame_sharpening/│   │   └── file_manager.py     # File operations

│   ├── 07_scene_detection/

│   ├── 08_background_subtraction/### 4. Compile C++ Programs│   ├── uploads/            # Uploaded videos (temp)

│   ├── 09_brightness_contrast/

│   ├── 10_motion_blur_reduction/From the root directory:│   └── temp_outputs/       # Processed videos (temp)

│   ├── 11_contrast_enhancement/

│   └── 12_lightup/```powershell├── frontend/               # React application

├── build/                      # Compiled C++ executables (36 files)

├── input_videos/               # User-uploaded videos.\compile.ps1│   ├── src/

├── outputs/                    # Processed video outputs

├── reference/                  # Original reference implementations```│   │   ├── components/     # React components

├── results/                    # Performance logs and graphs

├── compile.ps1                 # Compilation script│   │   ├── services/       # API client

├── start-app.ps1               # Application launcher

├── clean-repo.ps1              # Repository cleanup utilityThis compiles all 36 C++ programs (12 features × 3 implementations) and places executables in the `build/` directory.│   │   └── App.tsx         # Main app

└── .gitignore                  # Git ignore rules

```│   └── public/             # Static assets



## API Endpoints## 🚀 Running the Application├── src/                    # C++ implementations



### Backend API (Flask)│   ├── 01_grayscale/

- `POST /api/upload` - Upload video file

- `POST /api/process` - Start video processing### Quick Start (Recommended)│   ├── 02_gaussian_blur/

- `GET /api/status/<job_id>` - Get processing status

- `GET /api/results/<job_id>` - Get performance metricsFrom the root directory:│   ├── 03_edge_detection/

- `GET /api/video/<job_id>/<method>/<video_type>` - Stream video

- `GET /api/scene/<job_id>/<scene_type>` - Get scene detection results```powershell│   ├── 04_white_balance/

- `DELETE /api/cleanup/<job_id>` - Cleanup job files

- `GET /api/health` - Health check endpoint.\start-app.ps1│   ├── 05_histogram_equalization/



## Algorithm Details```│   ├── 06_frame_sharpening/



### Scene Detection│   ├── 07_scene_detection/

Uses a multi-metric approach:

- **Histogram Correlation**: Compares color distribution between framesThis script:│   ├── 08_background_subtraction/

- **Edge Detection**: Analyzes structural changes using Canny edge detection

- **Pixel Difference**: Measures absolute pixel value changes1. Starts the Flask backend on http://localhost:5000│   ├── 09_brightness_contrast/



Thresholds:2. Starts the React frontend on http://localhost:3000│   ├── 10_motion_blur_reduction/

- Histogram: 0.70 (lower = more different)

- Edge: 0.30 (higher = more different)3. Opens your default browser automatically│   ├── 11_contrast_enhancement/

- Pixel: 25.0 (normalized difference)

- Minimum gap between scenes: 15 frames│   └── 12_lightup/



Output includes frame number, timestamp, and confidence score.### Manual Start├── build/                  # Compiled executables



### Performance Optimization├── input_videos/           # Input test videos

- **OpenMP**: Loop-level parallelization with dynamic scheduling

- **Pthreads**: Frame-chunk distribution across threads**Backend:**├── outputs/                # Processing outputs

- **Sequential**: Optimized baseline for comparison

```bash├── compile.ps1             # Compilation script

## Maintenance

cd backend├── start-app.ps1           # Application launcher

### Clean Repository

```powershellpython app.py└── clean-repo.ps1          # Repository cleanup

.\clean-repo.ps1

`````````



Removes:

- Build artifacts (executables, object files)

- Temporary files and logs**Frontend:**##  Prerequisites

- Generated videos in input_videos/ and outputs/

- Python cache files```bash

- Node modules (optional)

cd frontend### Windows (Recommended)

## Configuration

npm start- **Python 3.11+**

### Thread Count

- Default: 4 threads```- **Node.js 16+**

- Recommended: Number of CPU cores

- Range: 1-16 threads- **MSYS2** with UCRT64 environment



### Video Formats## he Usage- **OpenCV 4.x** (with C++ development files)

- **Input**: MP4, AVI (MJPEG codec)

- **Processing**: AVI intermediate format- **Git** (for version control)

- **Output**: MP4 (mp4v codec) for browser compatibility

1. **Upload Video**: Click "Choose Video" and select an MP4 or AVI file

## Troubleshooting

2. **Select Feature**: Choose from the dropdown menu (e.g., Grayscale, Edge Detection)### Required Environment Variables

### PowerShell Execution Policy

If scripts fail to run:3. **Set Thread Count**: Specify number of threads for Pthread/OpenMP (default: 4)```powershell

```powershell

Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser4. **Process**: Click "Process Video" to start processing# Add to PATH:

```

5. **View Results**: C:\msys64\ucrt64\bin

### Compilation Errors

Ensure MSYS2 UCRT64 is installed:   - Watch input and output videos side by sideC:\opencv\build\x64\vc16\bin

```bash

pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-opencv   - Compare Sequential, Pthread, and OpenMP performance```

```

   - Analyze speedup graphs and metrics

### Port Already in Use

Change ports in:## 🚀 Installation

- Backend: `app.py` (default 5000)

- Frontend: `package.json` (default 3000)### Special Cases



### Video Not Playing### 1. Clone Repository

- Ensure browser supports MP4 format

- Check browser console for errors**Scene Detection**: Outputs frame numbers and timestamps of detected scene changes instead of a processed video.```bash

- Verify video file integrity

git clone <repository-url>

## Performance Analysis

**Large Videos**: Processing time depends on video length and selected feature. Progress updates appear in real-time.cd parallel_analysis-master

The application automatically generates:

- Execution time comparison charts```

- Speedup calculations (Sequential vs Parallel)

- Parallel efficiency metrics##  Project Structure

- FPS (Frames Per Second) statistics

### 2. Backend Setup

**Speedup Formula**: `Speedup = Sequential Time / Parallel Time`

``````bash

**Efficiency Formula**: `Efficiency = Speedup / Number of Threads`

parallel_analysis-master/cd backend

## Contributing

├── backend/                    # Flask API serverpip install -r requirements.txt

1. Fork the repository

2. Create a feature branch│   ├── app.py                 # Main Flask application (9 endpoints)```

3. Make your changes

4. Test thoroughly│   ├── video_processor.py     # Video processing orchestration

5. Submit a pull request

│   ├── video_converter.py     # AVI to MP4 conversion**requirements.txt:**

## License

│   ├── results_parser.py      # Parse C++ execution results```

This project is for educational purposes. Please ensure proper attribution when using or modifying the code.

│   └── requirements.txtFlask==3.0.0

## Additional Notes

├── frontend/                   # React web applicationFlask-CORS==4.0.0

- All C++ programs write execution metrics to text files

- Backend automatically converts AVI outputs to MP4 for web compatibility│   ├── src/opencv-python-headless==4.10.0.84

- Frontend polls backend every 2 seconds for status updates

- Scene detection outputs text results instead of video files│   │   ├── App.tsx            # Main component with state management```

- Performance metrics are calculated on the backend and displayed in real-time

│   │   ├── components/        # React components

## Support

│   │   │   ├── ConfigPanel.tsx### 3. Frontend Setup

For issues, bugs, or feature requests, please open an issue in the repository.

│   │   │   ├── ProcessingStatus.tsx```bash

---

│   │   │   ├── VideoComparison.tsxcd frontend

**Built with**: React • TypeScript • Flask • OpenCV • OpenMP • Pthreads

│   │   │   ├── PerformanceMetrics.tsxnpm install

**Developed for**: Parallel and Distributed Computing Course

│   │   │   ├── SpeedupChart.tsx```

│   │   │   └── SceneDetectionResults.tsx

│   │   └── types.ts           # TypeScript interfaces### 4. Compile C++ Programs

│   └── package.json```powershell

├── src/                        # C++ source code.\compile.ps1

│   ├── 01_grayscale/```

│   ├── 02_gaussian_blur/

│   ├── 03_edge_detection/This compiles all 36 C++ programs (12 features × 3 implementations).

│   ├── 04_white_balance/

│   ├── 05_histogram_equalization/## 💻 Usage

│   ├── 06_frame_sharpening/

│   ├── 07_scene_detection/### Quick Start

│   ├── 08_background_subtraction/```powershell

│   ├── 09_brightness_contrast/# Start both backend and frontend

│   ├── 10_motion_blur_reduction/.\start-app.ps1

│   ├── 11_contrast_enhancement/```

│   └── 12_lightup/

├── build/                      # Compiled C++ executables (36 files)Then open your browser to `http://localhost:3000`

├── input_videos/               # User-uploaded videos

├── outputs/                    # Processed video outputs### Manual Start

├── reference/                  # Original reference implementations

├── results/                    # Performance logs and graphs**Backend:**

├── compile.ps1                 # Compilation script```bash

├── start-app.ps1               # Application launchercd backend

├── clean-repo.ps1              # Repository cleanup utilitypython app.py

└── .gitignore                  # Git ignore rules```

```Server runs on `http://localhost:5000`



##  API Endpoints**Frontend:**

```bash

### Backend API (Flask)cd frontend

- `POST /api/upload` - Upload video filenpm start

- `POST /api/process` - Start video processing```

- `GET /api/status/<job_id>` - Get processing statusUI opens at `http://localhost:3000`

- `GET /api/results/<job_id>` - Get performance metrics

- `GET /api/video/<job_id>/<method>/<video_type>` - Stream video### Processing a Video

- `GET /api/scene/<job_id>/<scene_type>` - Get scene detection results

- `DELETE /api/cleanup/<job_id>` - Cleanup job files1. **Upload Video** - Click "Choose File" and select an MP4/AVI video

- `GET /api/health` - Health check endpoint2. **Select Feature** - Choose from 12 processing algorithms

3. **Configure Threads** - Set thread counts for Pthread/OpenMP (1-16)

##  Algorithm Details4. **Process** - Click "Process Video" button

5. **View Results** - Compare videos and analyze performance metrics

### Scene Detection

Uses a multi-metric approach:##  Processing Features

- **Histogram Correlation**: Compares color distribution between frames

- **Edge Detection**: Analyzes structural changes using Canny edge detection| Feature | Description | Output |

- **Pixel Difference**: Measures absolute pixel value changes|---------|-------------|--------|

| **Grayscale** | Convert color video to grayscale | Monochrome video |

Thresholds:| **Gaussian Blur** | Apply smoothing filter | Blurred video |

- Histogram: 0.70 (lower = more different)| **Edge Detection** | Sobel edge detection | Edge-highlighted video |

- Edge: 0.30 (higher = more different)| **White Balance** | Color correction | Balanced color video |

- Pixel: 25.0 (normalized difference)| **Histogram Equalization** | Enhance contrast | Enhanced video |

- Minimum gap between scenes: 15 frames| **Frame Sharpening** | Increase sharpness | Sharpened video |

| **Scene Detection** | Detect scene changes | Text file with frame numbers |

Output includes frame number, timestamp, and confidence score.| **Background Subtraction** | Isolate foreground | Foreground mask video |

| **Brightness/Contrast** | Adjust luminance | Adjusted video |

### Performance Optimization| **Motion Blur** | Reduce motion blur | Deblurred video |

- **OpenMP**: Loop-level parallelization with dynamic scheduling| **Contrast Enhancement** | Adaptive contrast | Enhanced video |

- **Pthreads**: Frame-chunk distribution across threads| **Light Enhancement** | Improve low-light | Brightened video |

- **Sequential**: Optimized baseline for comparison

##  Performance Metrics

##  Maintenance

The system calculates:

### Clean Repository

```powershell- **Execution Time** - Total processing time (seconds)

.\clean-repo.ps1- **FPS** - Frames processed per second

```- **Speedup** - `Sequential Time / Parallel Time`

- **Efficiency** - `(Speedup / Threads) × 100%`

Removes:

- Build artifacts (executables, object files)### Example Output

- Temporary files and logs```

- Generated videos in input_videos/ and outputs/Sequential:  10.50s  |  30 FPS  |  1.00x speedup  |  100% efficiency

- Python cache filesPthread (4): 3.20s   |  98 FPS  |  3.28x speedup  |  82% efficiency

- Node modules (optional)OpenMP (4):  2.85s   |  110 FPS |  3.68x speedup  |  92% efficiency

```

##  Configuration

## Architecture

### Thread Count

- Default: 4 threads### Backend Flow

- Recommended: Number of CPU cores```

- Range: 1-16 threadsUpload → Compile C++ → Execute (Sequential/Pthread/OpenMP) 

  → Parse Results → Convert AVI→MP4 → Return Metrics & Videos

### Video Formats```

- **Input**: MP4, AVI (MJPEG codec)

- **Processing**: AVI intermediate format### Frontend Flow

- **Output**: MP4 (mp4v codec) for browser compatibility```

Upload Video → Select Feature → Configure Threads 

## 🐛 Troubleshooting  → HTTP Polling → Display Results → Compare Videos

```

### PowerShell Execution Policy

If scripts fail to run:### API Endpoints

```powershell- `POST /api/upload` - Upload video file

Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser- `GET /api/features` - List available features

```- `POST /api/process` - Start processing job

- `GET /api/results/<job_id>` - Get processing results

### Compilation Errors- `GET /api/video/<job_id>/<type>` - Stream video file

Ensure MSYS2 UCRT64 is installed:- `GET /api/scene/<job_id>/<type>` - Get scene detection results

```bash

pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-opencv## 🧹 Repository Cleanup

```

Before committing to Git:

### Port Already in Use```powershell

Change ports in:.\clean-repo.ps1

- Backend: `app.py` (default 5000)```

- Frontend: `package.json` (default 3000)

This removes:

### Video Not Playing- Compiled executables (*.exe)

- Ensure browser supports MP4 format- Video files (inputs/outputs)

- Check browser console for errors- Temporary uploads

- Verify video file integrity- Python cache (__pycache__)

- Node build artifacts

## Performance Analysis- Log files


The application automatically generates:
- Execution time comparison charts
- Speedup calculations (Sequential vs Parallel)
- Parallel efficiency metrics
- FPS (Frames Per Second) statistics

**Speedup Formula**: `Speedup = Sequential Time / Parallel Time`

**Efficiency Formula**: `Efficiency = Speedup / Number of Threads`
