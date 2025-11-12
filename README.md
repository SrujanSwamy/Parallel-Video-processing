# Parallel Video Processing System

A full-stack web application to compare Sequential, Pthread, and OpenMP implementations of 12 video processing algorithms. Provides automated execution, performance measurement, and side‑by‑side output visualization via a React frontend, Flask backend, and C++/OpenCV engine.

## Table of Contents
1. [Overview](#overview)
2. [Key Features](#key-features)
3. [Algorithms Implemented](#algorithms-implemented)
4. [Parallel Implementations](#parallel-implementations)
5. [Performance Metrics](#performance-metrics)
6. [Tech Stack](#tech-stack)
7. [Project Structure](#project-structure)
8. [Setup & Installation](#setup--installation)
9. [Running the Application](#running-the-application)
10. [Usage Workflow](#usage-workflow)
11. [API Endpoints](#api-endpoints)
12. [Scene Detection Details](#scene-detection-details)
13. [Parallelization Strategies](#parallelization-strategies)
14. [Configuration](#configuration)
15. [Troubleshooting](#troubleshooting)
16. [Performance Analysis](#performance-analysis)
17. [Contributing](#contributing)
18. [License & Attribution](#license--attribution)

## Overview
The project demonstrates how parallel programming boosts throughput in typical video processing pipelines. The system automates:
- Compilation of all variants
- Sequential → Pthread → OpenMP execution order
- Timing and metric collection
- AVI → MP4 conversion for browser playback
- Web-based visualization of outputs and performance

## Key Features
- Unified web UI for upload, configuration, processing, and analysis
- 12 end‑to‑end processing pipelines (grayscale, blur, edges, enhancement, etc.)
- Real‑time progress polling (HTTP) and robust video streaming
- MP4 output for browser compatibility (range requests supported)
- Comparable metrics across implementations (time, speedup, FPS, efficiency)
- Clean separation: frontend (UI) / backend (orchestration) / C++ (compute)

## Algorithms Implemented
| # | Algorithm | Purpose |
|---|-----------|---------|
| 1 | Grayscale | Color → intensity conversion |
| 2 | Gaussian Blur | Denoising / smoothing |
| 3 | Edge Detection | Canny edge extractor |
| 4 | White Balance | Color cast correction |
| 5 | Histogram Equalization | Global contrast enhancement |
| 6 | Frame Sharpening | Detail enhancement |
| 7 | Scene Detection | Shot boundary detection (text output) |
| 8 | Background Subtraction | Foreground isolation |
| 9 | Brightness / Contrast | Dynamic range adjustment |
|10 | Motion Blur | Motion effect synthesis |
|11 | Contrast Enhancement | Local contrast improvement |
|12 | Lightup | Low‑light brightening |

## Parallel Implementations
- **Sequential**: Baseline, single thread
- **Pthread**: Manual partitioning and thread management
- **OpenMP**: Directive‑based parallel loops with dynamic scheduling

## Performance Metrics
| Metric | Description |
|--------|-------------|
| Execution Time (s) | Wall‑clock duration per implementation |
| Speedup | Sequential time / Parallel time |
| FPS | Frames processed per second |
| Parallel Efficiency | Speedup / Thread count |
| Threads Used | User‑specified for Pthread/OpenMP |

## Tech Stack
**Frontend**: React 18, TypeScript, Tailwind CSS, Axios, Recharts  
**Backend**: Python 3.11, Flask 3.0, OpenCV‑Python 4.10 (conversion, I/O)  
**C++ Engine**: g++ 13 (MSYS2 UCRT64), OpenCV C++, OpenMP, pthread  
**OS Target**: Windows (PowerShell scripts provided)

## Project Structure
```
parallel_analysis-master/
├── backend/
│   ├── app.py                 # Flask API (upload, process, status, results, video)
│   ├── requirements.txt       # Python dependencies
│   └── utils/
│       ├── video_processor.py # Orchestrates sequential/pthread/openmp runs
│       ├── video_converter.py # AVI → MP4 conversion
│       └── results_parser.py  # Metric extraction helpers
├── frontend/
│   ├── src/
│   │   ├── App.tsx            # Root component
│   │   ├── types.ts           # Shared TypeScript interfaces
│   │   └── components/        # Config, status, metrics, video, charts, scene results
│   ├── package.json
│   └── tailwind.config.js
├── src/                      # C++ source grouped by feature (3 files each)
│   ├── 01_grayscale/
│   ├── 02_gaussian_blur/
│   ├── ...
│   └── 12_lightup/
├── build/                    # Generated executables (.exe)            (gitignored)
├── input_videos/             # Uploaded originals                      (gitignored)
├── outputs/                  # Generated mp4/txt results               (gitignored)
├── results/                  # Performance logs                        (gitignored)
├── compile.ps1               # Build helper (bulk or targeted)
├── start-app.ps1             # Launch backend + frontend
├── clean-repo.ps1            # Remove generated artifacts
└── .gitignore
```

## Setup & Installation
### 1) Clone
```bash
git clone https://github.com/SrujanSwamy/Parallel-Video-processing.git
cd parallel_analysis-master
```
### 2) Backend
```bash
cd backend
pip install -r requirements.txt
python -c "import flask, cv2; print('Backend ready')"
```
### 3) Frontend
```bash
cd ../frontend
npm install
npm list react
```
### 4) C++ Environment (MSYS2 UCRT64)
```bash
pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-opencv
```
Ensure `C:\\msys64\\ucrt64\\bin` is on PATH.

### 5) Compile Binaries
From repository root:
```powershell
./compile.ps1
# Example targeted build:
# ./compile.ps1 -Program grayscale_sequential
```

## Running the Application
### Quick Start
```powershell
./start-app.ps1
```
Starts Flask (http://localhost:5000) and React (http://localhost:3000).

### Manual
```powershell
# Terminal 1
cd backend
python app.py

# Terminal 2
cd frontend
npm start
```

## Usage Workflow
1. Upload a video (MP4 or AVI).
2. Choose a feature and set thread count (for Pthread/OpenMP).
3. Click Process to run sequential → pthread → openmp.
4. Monitor progress; when finished, review output videos and metrics.
5. For Scene Detection, view textual scene change results (no processed video).
6. Optional: run `./clean-repo.ps1` to remove generated files.

## API Endpoints
```
POST   /api/upload                          Upload video
POST   /api/process                         Begin processing pipeline
GET    /api/status/<job_id>                 Status & progress
GET    /api/results/<job_id>                Metrics & artifact names
GET    /api/video/<job_id>/<method>/<type>  Stream (input|sequential|pthread|openmp)
GET    /api/scene/<job_id>/<scene_type>     Scene detection text output
GET    /api/features                        Enumerate selectable features
DELETE /api/cleanup/<job_id>                Remove job artifacts
GET    /api/health                          Health probe
```

### Sample Flow (curl)
```bash
# Upload
curl -F "video=@input.mp4" http://localhost:5000/api/upload

# Start
curl -H "Content-Type: application/json" \
  -d '{"job_id":"abc123","feature":"Grayscale","num_threads":8}' \
  http://localhost:5000/api/process

# Poll & Results
curl http://localhost:5000/api/status/abc123
curl http://localhost:5000/api/results/abc123
```

## Scene Detection Details
Decision based on three signals between consecutive frames:
- Histogram correlation (< 0.70)
- Edge difference (> 0.30)
- Pixel difference (> 25.0)
With a minimum gap of 15 frames between detections. Output is a `.txt` file with frame number, timestamp, and confidence.

## Parallelization Strategies
### OpenMP
- Loop‑level pragmas (`#pragma omp parallel for`)
- Dynamic scheduling for load balance

### Pthreads
- Manual frame‑chunk partitioning
- `pthread_create`/`pthread_join` synchronization

### Trade‑offs
| Aspect | Pthread | OpenMP |
|--------|---------|--------|
| Control | Fine‑grained | Higher‑level |
| Boilerplate | Higher | Lower |
| Tuning | Manual | Pragmas / env vars |
| Portability | POSIX | Compiler‑dependent |

## Configuration
| Parameter | Location | Notes |
|-----------|----------|-------|
| Thread count | Frontend form | Applies to Pthread & OpenMP |
| Feature | Frontend dropdown | Maps to executable name pattern |
| Input formats | Upload | MP4 / AVI accepted |
| Output | Backend converter | MP4 (mp4v) for browser playback |

## Troubleshooting
| Issue | Cause | Resolution |
|-------|-------|------------|
| Scripts blocked | PowerShell policy | `Set-ExecutionPolicy -Scope CurrentUser RemoteSigned` |
| Missing g++/OpenCV | MSYS2 not installed | Install via `pacman` and update PATH |
| Video not playing | MP4 missing or incompatible | Re-run; test file in a media player |
| Slow speedup | I/O bound or oversubscription | Reduce threads; smaller input |
| 416 range errors | Partial content requests | Backend has range fallback logic |

## Performance Analysis
Speedup = T_seq / T_parallel  
Efficiency = Speedup / Threads  
Amdahl upper bound = 1 / ((1 - P) + P / N)

Common bottlenecks: memory bandwidth at high thread counts, codec I/O during conversions.


