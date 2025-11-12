# Parallel Video Processing System# Parallel Video Processing System# Parallel Video Processing System# 🎥 Parallel Video Processing System



A full-stack application for parallel video processing using OpenMP, Pthreads, and Sequential implementations. Features a React frontend, Flask backend, and 12 different video processing algorithms implemented in C++.



## FeaturesA full-stack application for parallel video processing using OpenMP, Pthreads, and Sequential implementations. Features a React frontend, Flask backend, and 12 different video processing algorithms implemented in C++.



### Video Processing Algorithms

1. **Grayscale** - Convert videos to grayscale

2. **Gaussian Blur** - Apply Gaussian blur filter## FeaturesA full-stack application for parallel video processing using OpenMP, Pthreads, and Sequential implementations. Features a React frontend, Flask backend, and 12 different video processing algorithms implemented in C++.A full-stack web application for comparing parallel video processing performance using **Sequential**, **Pthread**, and **OpenMP** implementations across 12 different image/video processing algorithms.

3. **Edge Detection** - Detect edges using Canny algorithm

4. **White Balance** - Automatic white balance correction

5. **Histogram Equalization** - Enhance image contrast

6. **Frame Sharpening** - Sharpen video frames### Video Processing Algorithms

7. **Scene Detection** - Detect scene changes with confidence scores

8. **Background Subtraction** - Extract foreground objects1. **Grayscale** - Convert videos to grayscale

9. **Brightness/Contrast** - Adjust brightness and contrast

10. **Motion Blur** - Apply motion blur effect2. **Gaussian Blur** - Apply Gaussian blur filter##  Features##  Table of Contents

11. **Contrast Enhancement** - Enhance local contrast

12. **Lightup** - Brighten dark videos3. **Edge Detection** - Detect edges using Canny algorithm



### Parallel Implementations4. **White Balance** - Automatic white balance correction- [Features](#features)

Each algorithm is implemented in three ways:

- **Sequential** - Single-threaded baseline implementation5. **Histogram Equalization** - Enhance image contrast

- **Pthreads** - Multi-threaded using POSIX threads

- **OpenMP** - Multi-threaded using OpenMP directives6. **Frame Sharpening** - Sharpen video frames### Video Processing Algorithms- [Tech Stack](#tech-stack)



### Performance Metrics7. **Scene Detection** - Detect scene changes with confidence scores

- Execution time for each implementation

- Speedup calculations (Sequential time / Parallel time)8. **Background Subtraction** - Extract foreground objects1. **Grayscale** - Convert videos to grayscale- [Project Structure](#project-structure)

- Frames per second (FPS)

- Parallel efficiency9. **Brightness/Contrast** - Adjust brightness and contrast

- Thread utilization

10. **Motion Blur** - Apply motion blur effect2. **Gaussian Blur** - Apply Gaussian blur filter- [Prerequisites](#prerequisites)

## Prerequisites

11. **Contrast Enhancement** - Enhance local contrast

### Backend Requirements

- Python 3.11.9 or higher12. **Lightup** - Brighten dark videos3. **Edge Detection** - Detect edges using Canny algorithm- [Installation](#installation)

- OpenCV 4.10.0.84

- Flask 3.0.0

- MSYS2 UCRT64 environment with g++ 13.2.0

### Parallel Implementations4. **White Balance** - Automatic white balance correction- [Usage](#usage)

### Frontend Requirements

- Node.js 16.x or higherEach algorithm is implemented in three ways:

- npm or yarn

- **Sequential** - Single-threaded baseline implementation5. **Histogram Equalization** - Enhance image contrast- [Processing Features](#processing-features)

### C++ Compiler

- g++ with OpenMP support- **Pthreads** - Multi-threaded using POSIX threads

- pthread library

- OpenCV 4.x development files- **OpenMP** - Multi-threaded using OpenMP directives6. **Frame Sharpening** - Sharpen video frames- [Performance Metrics](#performance-metrics)



## Installation



### 1. Clone the Repository### Performance Metrics7. **Scene Detection** - Detect scene changes with confidence scores- [Architecture](#architecture)

```bash

git clone <repository-url>- Execution time for each implementation

cd parallel_analysis-master

```- Speedup calculations (Sequential time / Parallel time)8. **Background Subtraction** - Extract foreground objects- [Contributing](#contributing)



### 2. Backend Setup- Frames per second (FPS)

```bash

cd backend- Parallel efficiency9. **Brightness/Contrast** - Adjust brightness and contrast

pip install -r requirements.txt

```- Thread utilization



**Required Python packages:**10. **Motion Blur** - Apply motion blur effect##  Features

- Flask==3.0.0

- flask-cors==4.0.0## Prerequisites

- opencv-python==4.10.0.84

11. **Contrast Enhancement** - Enhance local contrast

### 3. Frontend Setup

```bash### Backend Requirements

cd frontend

npm install- Python 3.11.9 or higher12. **Lightup** - Brighten dark videos- **12 Video Processing Algorithms**

```

- OpenCV 4.10.0.84

**Key dependencies:**

- React 18.2.0- Flask 3.0.0  - Grayscale Conversion

- TypeScript

- Tailwind CSS- MSYS2 UCRT64 environment with g++ 13.2.0

- Axios for API calls

- Recharts for performance graphs### Parallel Implementations  - Gaussian Blur



### 4. Compile C++ Programs### Frontend Requirements

From the root directory:

```powershell- Node.js 16.x or higherEach algorithm is implemented in three ways:  - Edge Detection (Sobel)

.\compile.ps1

```- npm or yarn



This compiles all 36 C++ programs (12 features × 3 implementations) and places executables in the `build/` directory.- **Sequential** - Single-threaded baseline implementation  - White Balance



## Running the Application### C++ Compiler



### Quick Start (Recommended)- g++ with OpenMP support- **Pthreads** - Multi-threaded using POSIX threads  - Histogram Equalization

From the root directory:

```powershell- pthread library

.\start-app.ps1

```- OpenCV 4.x development files- **OpenMP** - Multi-threaded using OpenMP directives  - Frame Sharpening



This script:

1. Starts the Flask backend on http://localhost:5000

2. Starts the React frontend on http://localhost:3000## Installation  - Scene Detection

3. Opens your default browser automatically



### Manual Start

### 1. Clone the Repository### Performance Metrics  - Background Subtraction

**Backend:**

```bash```bash

cd backend

python app.pygit clone <repository-url>- Execution time for each implementation  - Brightness/Contrast Adjustment

```

cd parallel_analysis-master

**Frontend:**

```bash```- Speedup calculations (Sequential time / Parallel time)  - Motion Blur Reduction

cd frontend

npm start

```

### 2. Backend Setup- Frames per second (FPS)  - Contrast Enhancement

## Usage

```bash

1. **Upload Video**: Click "Choose Video" and select an MP4 or AVI file

2. **Select Feature**: Choose from the dropdown menu (e.g., Grayscale, Edge Detection)cd backend- Parallel efficiency  - Light Enhancement

3. **Set Thread Count**: Specify number of threads for Pthread/OpenMP (default: 4)

4. **Process**: Click "Process Video" to start processingpip install -r requirements.txt

5. **View Results**: 

   - Watch input and output videos side by side```- Thread utilization

   - Compare Sequential, Pthread, and OpenMP performance

   - Analyze speedup graphs and metrics



### Special Cases**Required Python packages:**- **Three Parallel Implementations**



**Scene Detection**: Outputs frame numbers and timestamps of detected scene changes instead of a processed video.- Flask==3.0.0



**Large Videos**: Processing time depends on video length and selected feature. Progress updates appear in real-time.- flask-cors==4.0.0##  Prerequisites  - Sequential (baseline)



## Project Structure- opencv-python==4.10.0.84



```  - Pthread (POSIX threads)

parallel_analysis-master/

├── backend/                    # Flask API server### 3. Frontend Setup

│   ├── app.py                 # Main Flask application (9 endpoints)

│   ├── video_processor.py     # Video processing orchestration```bash### Backend Requirements  - OpenMP (Open Multi-Processing)

│   ├── video_converter.py     # AVI to MP4 conversion

│   ├── results_parser.py      # Parse C++ execution resultscd frontend

│   └── requirements.txt

├── frontend/                   # React web applicationnpm install- Python 3.11.9 or higher

│   ├── src/

│   │   ├── App.tsx            # Main component with state management```

│   │   ├── components/        # React components

│   │   │   ├── ConfigPanel.tsx- OpenCV 4.10.0.84- **Web-Based Interface**

│   │   │   ├── ProcessingStatus.tsx

│   │   │   ├── VideoComparison.tsx**Key dependencies:**

│   │   │   ├── PerformanceMetrics.tsx

│   │   │   ├── SpeedupChart.tsx- React 18.2.0- Flask 3.0.0  - Upload videos

│   │   │   └── SceneDetectionResults.tsx

│   │   └── types.ts           # TypeScript interfaces- TypeScript

│   └── package.json

├── src/                        # C++ source code- Tailwind CSS- MSYS2 UCRT64 environment with g++ 13.2.0  - Select processing features

│   ├── 01_grayscale/

│   ├── 02_gaussian_blur/- Axios for API calls

│   ├── 03_edge_detection/

│   ├── 04_white_balance/- Recharts for performance graphs  - Configure thread counts

│   ├── 05_histogram_equalization/

│   ├── 06_frame_sharpening/

│   ├── 07_scene_detection/

│   ├── 08_background_subtraction/### 4. Compile C++ Programs### Frontend Requirements  - Real-time progress tracking

│   ├── 09_brightness_contrast/

│   ├── 10_motion_blur_reduction/From the root directory:

│   ├── 11_contrast_enhancement/

│   └── 12_lightup/```powershell- Node.js 16.x or higher  - Side-by-side video comparison

├── build/                      # Compiled C++ executables (36 files)

├── input_videos/               # User-uploaded videos.\compile.ps1

├── outputs/                    # Processed video outputs

├── results/                    # Performance logs and graphs```- npm or yarn  - Performance metrics and graphs

├── compile.ps1                 # Compilation script

├── start-app.ps1               # Application launcher

├── clean-repo.ps1              # Repository cleanup utility

└── .gitignore                  # Git ignore rulesThis compiles all 36 C++ programs (12 features × 3 implementations) and places executables in the `build/` directory.

```



## API Endpoints

## Running the Application### C++ Compiler- **Comprehensive Metrics**

### Backend API (Flask)

- `POST /api/upload` - Upload video file

- `POST /api/process` - Start video processing

- `GET /api/status/<job_id>` - Get processing status### Quick Start (Recommended)- g++ with OpenMP support  - Execution time

- `GET /api/results/<job_id>` - Get performance metrics

- `GET /api/video/<job_id>/<method>/<video_type>` - Stream videoFrom the root directory:

- `GET /api/scene/<job_id>/<scene_type>` - Get scene detection results

- `DELETE /api/cleanup/<job_id>` - Cleanup job files```powershell- pthread library  - Frames per second (FPS)

- `GET /api/health` - Health check endpoint

.\start-app.ps1

## Algorithm Details

```- OpenCV 4.x development files  - Speedup calculation

### Scene Detection

Uses a multi-metric approach:

- **Histogram Correlation**: Compares color distribution between frames

- **Edge Detection**: Analyzes structural changes using Canny edge detectionThis script:  - Parallel efficiency

- **Pixel Difference**: Measures absolute pixel value changes

1. Starts the Flask backend on http://localhost:5000

Thresholds:

- Histogram: 0.70 (lower = more different)2. Starts the React frontend on http://localhost:3000## 🔧 Installation  - Interactive performance charts

- Edge: 0.30 (higher = more different)

- Pixel: 25.0 (normalized difference)3. Opens your default browser automatically

- Minimum gap between scenes: 15 frames



Output includes frame number, timestamp, and confidence score.

### Manual Start

### Performance Optimization

- **OpenMP**: Loop-level parallelization with dynamic scheduling### 1. Clone the Repository## 🛠️ Tech Stack

- **Pthreads**: Frame-chunk distribution across threads

- **Sequential**: Optimized baseline for comparison**Backend:**



## Maintenance```bash```bash



### Clean Repositorycd backend

```powershell

.\clean-repo.ps1python app.pygit clone <repository-url>### Backend

```

```

Removes:

- Build artifacts (executables, object files)cd parallel_analysis-master- **Python 3.11+** - API server

- Temporary files and logs

- Generated videos in input_videos/ and outputs/**Frontend:**

- Python cache files

- Node modules (optional)```bash```- **Flask 3.0** - Web framework



## Configurationcd frontend



### Thread Countnpm start- **OpenCV 4.x** - Video processing

- Default: 4 threads

- Recommended: Number of CPU cores```

- Range: 1-16 threads

### 2. Backend Setup- **C++17** - Parallel implementations

### Video Formats

- **Input**: MP4, AVI (MJPEG codec)## Usage

- **Processing**: AVI intermediate format

- **Output**: MP4 (mp4v codec) for browser compatibility```bash



## Troubleshooting1. **Upload Video**: Click "Choose Video" and select an MP4 or AVI file



### PowerShell Execution Policy2. **Select Feature**: Choose from the dropdown menu (e.g., Grayscale, Edge Detection)cd backend### Frontend

If scripts fail to run:

```powershell3. **Set Thread Count**: Specify number of threads for Pthread/OpenMP (default: 4)

Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser

```4. **Process**: Click "Process Video" to start processingpip install -r requirements.txt- **React 18.2** - UI framework



### Compilation Errors5. **View Results**: 

Ensure MSYS2 UCRT64 is installed:

```bash   - Watch input and output videos side by side```- **TypeScript** - Type safety

pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-opencv

```   - Compare Sequential, Pthread, and OpenMP performance



### Port Already in Use   - Analyze speedup graphs and metrics- **Tailwind CSS** - Styling

Change ports in:

- Backend: `app.py` (default 5000)

- Frontend: `package.json` (default 3000)

### Special Cases**Required Python packages:**- **Recharts** - Performance visualization

### Video Not Playing

- Ensure browser supports MP4 format

- Check browser console for errors

- Verify video file integrity**Scene Detection**: Outputs frame numbers and timestamps of detected scene changes instead of a processed video.- Flask==3.0.0- **Axios** - HTTP client



## Performance Analysis



The application automatically generates:**Large Videos**: Processing time depends on video length and selected feature. Progress updates appear in real-time.- flask-cors==4.0.0

- Execution time comparison charts

- Speedup calculations (Sequential vs Parallel)

- Parallel efficiency metrics

- FPS (Frames Per Second) statistics## Project Structure- opencv-python==4.10.0.84### Build Tools



**Speedup Formula**: `Speedup = Sequential Time / Parallel Time`



**Efficiency Formula**: `Efficiency = Speedup / Number of Threads````- **g++ (MSYS2)** - C++ compiler



## Contributingparallel_analysis-master/



1. Fork the repository├── backend/                    # Flask API server### 3. Frontend Setup- **OpenMP** - Parallel programming

2. Create a feature branch

3. Make your changes│   ├── app.py                 # Main Flask application (9 endpoints)

4. Test thoroughly

5. Submit a pull request│   ├── video_processor.py     # Video processing orchestration```bash- **pthread** - POSIX threads



## License│   ├── video_converter.py     # AVI to MP4 conversion



This project is for educational purposes. Please ensure proper attribution when using or modifying the code.│   ├── results_parser.py      # Parse C++ execution resultscd frontend



## Additional Notes│   └── requirements.txt



- All C++ programs write execution metrics to text files├── frontend/                   # React web applicationnpm install##  Project Structure

- Backend automatically converts AVI outputs to MP4 for web compatibility

- Frontend polls backend every 2 seconds for status updates│   ├── src/

- Scene detection outputs text results instead of video files

- Performance metrics are calculated on the backend and displayed in real-time│   │   ├── App.tsx            # Main component with state management```



## Support│   │   ├── components/        # React components



For issues, bugs, or feature requests, please open an issue in the repository.│   │   │   ├── ConfigPanel.tsx```



---│   │   │   ├── ProcessingStatus.tsx



**Built with**: React • TypeScript • Flask • OpenCV • OpenMP • Pthreads│   │   │   ├── VideoComparison.tsx**Key dependencies:**parallel_analysis-master/



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
