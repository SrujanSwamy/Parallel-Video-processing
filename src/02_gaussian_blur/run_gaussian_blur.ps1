# Master script to run all Gaussian Blur video processing versions
# Compiles, runs all three versions, and shows performance comparison

param(
    [Parameter(Mandatory=$true)]
    [string]$VideoFile,
    
    [int]$NumThreads = 4
)

Write-Host "`n================================================================" -ForegroundColor Cyan
Write-Host "     GAUSSIAN BLUR VIDEO PROCESSING - PERFORMANCE ANALYSIS" -ForegroundColor Cyan
Write-Host "================================================================" -ForegroundColor Cyan

# Check if video file exists
if (-not (Test-Path $VideoFile)) {
    Write-Host "`nERROR: Video file not found: $VideoFile" -ForegroundColor Red
    exit 1
}

# Set paths
$rootDir = Split-Path -Parent (Split-Path -Parent $PSScriptRoot)
$outputDir = Join-Path $rootDir "outputs\02_gaussian_blur"
$buildDir = Join-Path $rootDir "build"

# Create output directory if it doesn't exist
if (-not (Test-Path $outputDir)) {
    New-Item -ItemType Directory -Path $outputDir -Force | Out-Null
    Write-Host "`nCreated output directory: $outputDir" -ForegroundColor Yellow
}

# Add MSYS2 to PATH for DLLs
$env:PATH = "C:\msys64\ucrt64\bin;$env:PATH"

Write-Host "`nVideo: $VideoFile" -ForegroundColor White
Write-Host "Threads for parallel versions: $NumThreads" -ForegroundColor White
Write-Host "Output directory: $outputDir`n" -ForegroundColor White

# Build all versions
Write-Host "----------------------------------------------------------------" -ForegroundColor DarkGray
Write-Host "STEP 1: Building all versions..." -ForegroundColor Yellow
Write-Host "----------------------------------------------------------------" -ForegroundColor DarkGray

Set-Location $rootDir

& "$rootDir\compile.ps1" -Program gaussian_blur_sequential
& "$rootDir\compile.ps1" -Program gaussian_blur_pthread
& "$rootDir\compile.ps1" -Program gaussian_blur_openmp

Write-Host "`nAll versions compiled successfully!`n" -ForegroundColor Green

# Run Sequential Version
Write-Host "----------------------------------------------------------------" -ForegroundColor DarkGray
Write-Host "STEP 2: Running SEQUENTIAL version..." -ForegroundColor Yellow
Write-Host "----------------------------------------------------------------" -ForegroundColor DarkGray

$seqOutput = & "$buildDir\gaussian_blur_sequential.exe" $VideoFile "$outputDir\gaussian_blur_sequential.avi" 2>&1
Write-Host $seqOutput

# Extract execution time
$seqTime = 0.0
$seqOutputStr = $seqOutput -join "`n"
if ($seqOutputStr -match "Execution time:\s+([\d.]+)s") {
    $seqTime = [double]$matches[1]
}

# Run Pthread Version
Write-Host "`n----------------------------------------------------------------" -ForegroundColor DarkGray
Write-Host "STEP 3: Running PTHREAD version ($NumThreads threads)..." -ForegroundColor Yellow
Write-Host "----------------------------------------------------------------" -ForegroundColor DarkGray

$pthreadOutput = & "$buildDir\gaussian_blur_pthread.exe" $VideoFile $NumThreads "$outputDir\gaussian_blur_pthread.avi" 2>&1
Write-Host $pthreadOutput

# Extract execution time
$pthreadTime = 0.0
$pthreadOutputStr = $pthreadOutput -join "`n"
if ($pthreadOutputStr -match "Execution time:\s+([\d.]+)s") {
    $pthreadTime = [double]$matches[1]
}

# Run OpenMP Version
Write-Host "`n----------------------------------------------------------------" -ForegroundColor DarkGray
Write-Host "STEP 4: Running OPENMP version ($NumThreads threads)..." -ForegroundColor Yellow
Write-Host "----------------------------------------------------------------" -ForegroundColor DarkGray

$openmpOutput = & "$buildDir\gaussian_blur_openmp.exe" $VideoFile $NumThreads "$outputDir\gaussian_blur_openmp.avi" 2>&1
Write-Host $openmpOutput

# Extract execution time
$openmpTime = 0.0
$openmpOutputStr = $openmpOutput -join "`n"
if ($openmpOutputStr -match "Execution time:\s+([\d.]+)s") {
    $openmpTime = [double]$matches[1]
}

# Calculate speedups
$pthreadSpeedup = if ($pthreadTime -gt 0) { $seqTime / $pthreadTime } else { 0 }
$openmpSpeedup = if ($openmpTime -gt 0) { $seqTime / $openmpTime } else { 0 }

# Display Performance Summary
Write-Host "`n================================================================" -ForegroundColor Cyan
Write-Host "              PERFORMANCE COMPARISON SUMMARY" -ForegroundColor Cyan
Write-Host "================================================================" -ForegroundColor Cyan

Write-Host "`n----------------------------------------------------------------" -ForegroundColor White
Write-Host " Version          Time (s)    Speedup    Efficiency" -ForegroundColor White
Write-Host "----------------------------------------------------------------" -ForegroundColor White

$seqLine = " Sequential       {0,-10:F3}  {1,-9}  {2,-13}" -f $seqTime, "1.00x", "-"
$pthreadLine = " Pthread ({0})      {1,-10:F3}  {2,-9:F2}x  {3,-13:F2}%" -f $NumThreads, $pthreadTime, $pthreadSpeedup, ($pthreadSpeedup/$NumThreads*100)
$openmpLine = " OpenMP ({0})       {1,-10:F3}  {2,-9:F2}x  {3,-13:F2}%" -f $NumThreads, $openmpTime, $openmpSpeedup, ($openmpSpeedup/$NumThreads*100)

Write-Host $seqLine -ForegroundColor Gray
Write-Host $pthreadLine -ForegroundColor Green
Write-Host $openmpLine -ForegroundColor Green
Write-Host "----------------------------------------------------------------" -ForegroundColor White

Write-Host "`nOutput files saved in: $outputDir" -ForegroundColor Cyan
Write-Host "   - gaussian_blur_sequential.avi" -ForegroundColor Gray
Write-Host "   - gaussian_blur_pthread.avi" -ForegroundColor Gray
Write-Host "   - gaussian_blur_openmp.avi" -ForegroundColor Gray

Write-Host "`nAll tests completed successfully!`n" -ForegroundColor Green
