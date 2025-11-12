# Compile script for MSYS2 UCRT64 - Run from PowerShell
# Make sure you've installed: pacman -S mingw-w64-ucrt-x86_64-toolchain

param(
    [string]$Program = "grayscale_sequential"
)

Write-Host "`nCompiling $Program..." -ForegroundColor Cyan

# MSYS2 UCRT64 paths
$msys2Bin = "C:\msys64\ucrt64\bin"
$msys2Include = "C:\msys64\ucrt64\include\opencv4"
$msys2Lib = "C:\msys64\ucrt64\lib"

# Check if g++ from MSYS2 exists
$gppPath = "$msys2Bin\g++.exe"
if (-not (Test-Path $gppPath)) {
    Write-Host "ERROR: g++ not found in MSYS2 UCRT64!" -ForegroundColor Red
    Write-Host "`nPlease install the toolchain:" -ForegroundColor Yellow
    Write-Host "  1. Open 'MSYS2 UCRT64' terminal from Start menu" -ForegroundColor Gray
    Write-Host "  2. Run: pacman -S mingw-w64-ucrt-x86_64-toolchain" -ForegroundColor Gray
    Write-Host "  3. Press Enter to install all packages" -ForegroundColor Gray
    exit 1
}

# Check OpenCV
if (-not (Test-Path $msys2Include)) {
    Write-Host "ERROR: OpenCV not found!" -ForegroundColor Red
    Write-Host "Run in MSYS2 UCRT64: pacman -S mingw-w64-ucrt-x86_64-opencv" -ForegroundColor Yellow
    exit 1
}

# Source files
$sourceMap = @{
    # Grayscale
    "grayscale_sequential" = "src\01_grayscale\grayscale_sequential.cpp"
    "grayscale_openmp" = "src\01_grayscale\grayscale_openmp.cpp"
    "grayscale_pthread" = "src\01_grayscale\grayscale_pthread.cpp"
    # Gaussian Blur
    "gaussian_blur_sequential" = "src\02_gaussian_blur\gaussian_blur_sequential.cpp"
    "gaussian_blur_openmp" = "src\02_gaussian_blur\gaussian_blur_openmp.cpp"
    "gaussian_blur_pthread" = "src\02_gaussian_blur\gaussian_blur_pthread.cpp"
    # Edge Detection
    "edge_detection_sequential" = "src\03_edge_detection\edge_detection_sequential.cpp"
    "edge_detection_openmp" = "src\03_edge_detection\edge_detection_openmp.cpp"
    "edge_detection_pthread" = "src\03_edge_detection\edge_detection_pthread.cpp"
    # White Balance
    "white_balance_sequential" = "src\04_white_balance\white_balance_sequential.cpp"
    "white_balance_openmp" = "src\04_white_balance\white_balance_openmp.cpp"
    "white_balance_pthread" = "src\04_white_balance\white_balance_pthread.cpp"
    # Histogram Equalization
    "histogram_equalization_sequential" = "src\05_histogram_equalization\histogram_equalization_sequential.cpp"
    "histogram_equalization_openmp" = "src\05_histogram_equalization\histogram_equalization_openmp.cpp"
    "histogram_equalization_pthread" = "src\05_histogram_equalization\histogram_equalization_pthread.cpp"
    # Frame Sharpening
    "frame_sharpening_sequential" = "src\06_frame_sharpening\frame_sharpening_sequential.cpp"
    "frame_sharpening_openmp" = "src\06_frame_sharpening\frame_sharpening_openmp.cpp"
    "frame_sharpening_pthread" = "src\06_frame_sharpening\frame_sharpening_pthread.cpp"
    # Scene Detection
    "scene_detection_sequential" = "src\07_scene_detection\scene_detection_sequential.cpp"
    "scene_detection_openmp" = "src\07_scene_detection\scene_detection_openmp.cpp"
    "scene_detection_pthread" = "src\07_scene_detection\scene_detection_pthread.cpp"
    # Background Subtraction
    "background_subtraction_sequential" = "src\08_background_subtraction\background_subtraction_sequential.cpp"
    "background_subtraction_openmp" = "src\08_background_subtraction\background_subtraction_openmp.cpp"
    "background_subtraction_pthread" = "src\08_background_subtraction\background_subtraction_pthread.cpp"
    # Brightness/Contrast
    "brightness_contrast_sequential" = "src\09_brightness_contrast\brightness_contrast_sequential.cpp"
    "brightness_contrast_openmp" = "src\09_brightness_contrast\brightness_contrast_openmp.cpp"
    "brightness_contrast_pthread" = "src\09_brightness_contrast\brightness_contrast_pthread.cpp"
    # Motion Blur Reduction
    "motion_blur_reduction_sequential" = "src\10_motion_blur_reduction\motion_blur_reduction_sequential.cpp"
    "motion_blur_reduction_openmp" = "src\10_motion_blur_reduction\motion_blur_reduction_openmp.cpp"
    "motion_blur_reduction_pthread" = "src\10_motion_blur_reduction\motion_blur_reduction_pthread.cpp"
    # Contrast Enhancement
    "contrast_enhancement_sequential" = "src\11_contrast_enhancement\contrast_enhancement_sequential.cpp"
    "contrast_enhancement_openmp" = "src\11_contrast_enhancement\contrast_enhancement_openmp.cpp"
    "contrast_enhancement_pthread" = "src\11_contrast_enhancement\contrast_enhancement_pthread.cpp"
    # Lightup
    "lightup_sequential" = "src\12_lightup\lightup_sequential.cpp"
    "lightup_openmp" = "src\12_lightup\lightup_openmp.cpp"
    "lightup_pthread" = "src\12_lightup\lightup_pthread.cpp"
}

if (-not $sourceMap.ContainsKey($Program)) {
    Write-Host "Unknown program: $Program" -ForegroundColor Red
    exit 1
}

$source = $sourceMap[$Program]
$output = "build\$Program.exe"

# Create build directory
if (-not (Test-Path "build")) {
    New-Item -ItemType Directory -Path "build" | Out-Null
}

Write-Host "Source: $source" -ForegroundColor Gray
Write-Host "Using: $gppPath" -ForegroundColor Gray

# Find OpenCV libraries
$opencvLibs = @(
    "libopencv_core4100.dll.a",
    "libopencv_imgproc4100.dll.a",
    "libopencv_highgui4100.dll.a",
    "libopencv_videoio4100.dll.a",
    "libopencv_imgcodecs4100.dll.a",
    "libopencv_video4100.dll.a"
)

# Check version - libraries might have different version numbers
$coreLib = Get-ChildItem "$msys2Lib\libopencv_core*.dll.a" | Select-Object -First 1
if (-not $coreLib) {
    Write-Host "ERROR: OpenCV libraries not found in $msys2Lib" -ForegroundColor Red
    exit 1
}

# Extract version from library name (e.g., libopencv_core4100.dll.a -> 4100)
$libName = $coreLib.Name
if ($libName -match 'libopencv_core(\d+)\.dll\.a') {
    $version = $matches[1]
    Write-Host "OpenCV version: $version" -ForegroundColor Green
} else {
    $version = ""
}

# Build library list
$libs = @(
    "-lopencv_core$version",
    "-lopencv_imgproc$version",
    "-lopencv_highgui$version",
    "-lopencv_videoio$version",
    "-lopencv_imgcodecs$version",
    "-lopencv_video$version"
)

# Build arguments
$args = @(
    $source,
    "-o", $output,
    "-I$msys2Include",
    "-L$msys2Lib"
)
$args += $libs
$args += @("-std=c++14")

# Add OpenMP for openmp version
if ($Program -match "openmp") {
    $args += "-fopenmp"
}

Write-Host "`nCompiling..." -ForegroundColor Yellow

# Compile
$process = Start-Process -FilePath $gppPath -ArgumentList $args -NoNewWindow -Wait -PassThru

if ($process.ExitCode -eq 0) {
    Write-Host "`n[SUCCESS] Compilation completed!" -ForegroundColor Green
    Write-Host "`nOutput: $output" -ForegroundColor Cyan
    
    # Check if DLL path is in PATH
    if ($env:PATH -notlike "*$msys2Bin*") {
        Write-Host "`n[IMPORTANT] Add MSYS2 DLLs to PATH before running:" -ForegroundColor Yellow
        Write-Host '$env:PATH = "C:\msys64\ucrt64\bin;$env:PATH"' -ForegroundColor Gray
    }
    
    Write-Host "`nRun with:" -ForegroundColor Cyan
    if ($Program -match "pthread|openmp") {
        Write-Host "  .\$output VIDEO_FILE NUM_THREADS" -ForegroundColor White
        Write-Host "  Example: .\$output input_videos\sample.mp4 4" -ForegroundColor Gray
    } else {
        Write-Host "  .\$output VIDEO_FILE" -ForegroundColor White
        Write-Host "  Example: .\$output input_videos\sample.mp4" -ForegroundColor Gray
    }
} else {
    Write-Host "`n[FAILED] Compilation failed!" -ForegroundColor Red
    exit 1
}
