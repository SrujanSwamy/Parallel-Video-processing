param(
    [Parameter(Mandatory=$true)]
    [string]$VideoFile,
    
    [Parameter(Mandatory=$true)]
    [int]$NumThreads
)

# Script directory
$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$rootDir = Split-Path -Parent (Split-Path -Parent $scriptDir)

# Change to root directory
Push-Location $rootDir

Write-Host "================================================================" -ForegroundColor Cyan
Write-Host "      HISTOGRAM EQUALIZATION - PERFORMANCE COMPARISON" -ForegroundColor Cyan
Write-Host "================================================================" -ForegroundColor Cyan
Write-Host ""

# Create output directory if it doesn't exist
$outputDir = "outputs\05_histogram_equalization"
if (-not (Test-Path $outputDir)) {
    New-Item -ItemType Directory -Path $outputDir -Force | Out-Null
}

# Arrays to store results
$versions = @("Sequential", "Pthread", "OpenMP")
$times = @()

# ============================================================================
# 1. SEQUENTIAL VERSION
# ============================================================================
Write-Host ">>> Building Sequential version..." -ForegroundColor Yellow
& .\compile.ps1 -Program histogram_equalization_sequential

Write-Host "`n>>> Running Sequential version..." -ForegroundColor Green
$output = & .\build\histogram_equalization_sequential.exe $VideoFile 2>&1 | Out-String
Write-Host $output

# Extract execution time
if ($output -match "Execution time: ([\d.]+)s") {
    $times += [double]$Matches[1]
    Write-Host "Sequential Time: $($Matches[1])s" -ForegroundColor Cyan
} else {
    Write-Host "Error: Could not extract execution time from sequential output" -ForegroundColor Red
    Pop-Location
    exit 1
}

# ============================================================================
# 2. PTHREAD VERSION
# ============================================================================
Write-Host "`n>>> Building Pthread version..." -ForegroundColor Yellow
& .\compile.ps1 -Program histogram_equalization_pthread

Write-Host "`n>>> Running Pthread version with $NumThreads threads..." -ForegroundColor Green
$output = & .\build\histogram_equalization_pthread.exe $VideoFile $NumThreads 2>&1 | Out-String
Write-Host $output

# Extract execution time
if ($output -match "Execution time: ([\d.]+)s") {
    $times += [double]$Matches[1]
    Write-Host "Pthread Time: $($Matches[1])s" -ForegroundColor Cyan
} else {
    Write-Host "Error: Could not extract execution time from pthread output" -ForegroundColor Red
    Pop-Location
    exit 1
}

# ============================================================================
# 3. OPENMP VERSION
# ============================================================================
Write-Host "`n>>> Building OpenMP version..." -ForegroundColor Yellow
& .\compile.ps1 -Program histogram_equalization_openmp

Write-Host "`n>>> Running OpenMP version with $NumThreads threads..." -ForegroundColor Green
$output = & .\build\histogram_equalization_openmp.exe $VideoFile $NumThreads 2>&1 | Out-String
Write-Host $output

# Extract execution time
if ($output -match "Execution time: ([\d.]+)s") {
    $times += [double]$Matches[1]
    Write-Host "OpenMP Time: $($Matches[1])s" -ForegroundColor Cyan
} else {
    Write-Host "Error: Could not extract execution time from openmp output" -ForegroundColor Red
    Pop-Location
    exit 1
}

# ============================================================================
# PERFORMANCE COMPARISON
# ============================================================================
Write-Host "`n"
Write-Host "================================================================" -ForegroundColor Cyan
Write-Host "              PERFORMANCE COMPARISON SUMMARY" -ForegroundColor Cyan
Write-Host "================================================================" -ForegroundColor Cyan
Write-Host ""

$seqTime = $times[0]
$pthreadTime = $times[1]
$openmpTime = $times[2]

# Calculate speedups
$pthreadSpeedup = $seqTime / $pthreadTime
$openmpSpeedup = $seqTime / $openmpTime

# Calculate efficiency (speedup / number of threads * 100)
$pthreadEfficiency = ($pthreadSpeedup / $NumThreads) * 100
$openmpEfficiency = ($openmpSpeedup / $NumThreads) * 100

Write-Host "----------------------------------------------------------------" -ForegroundColor Gray
Write-Host " Version          Time (s)    Speedup    Efficiency" -ForegroundColor White
Write-Host "----------------------------------------------------------------" -ForegroundColor Gray
Write-Host (" Sequential       {0,-11:F3} {1,-10} -" -f $seqTime, "1.00x") -ForegroundColor White
Write-Host (" Pthread ({0})      {1,-11:F3} {2,-6:F2} x  {3,-12:F2} %" -f $NumThreads, $pthreadTime, $pthreadSpeedup, $pthreadEfficiency) -ForegroundColor Green
Write-Host (" OpenMP ({0})       {1,-11:F3} {2,-6:F2} x  {3,-12:F2} %" -f $NumThreads, $openmpTime, $openmpSpeedup, $openmpEfficiency) -ForegroundColor Green
Write-Host "----------------------------------------------------------------" -ForegroundColor Gray
Write-Host ""

# Output file locations
Write-Host "Output videos saved to:" -ForegroundColor Cyan
Write-Host "  - $outputDir\histogram_equalization_sequential.avi" -ForegroundColor White
Write-Host "  - $outputDir\histogram_equalization_pthread.avi" -ForegroundColor White
Write-Host "  - $outputDir\histogram_equalization_openmp.avi" -ForegroundColor White
Write-Host ""

Pop-Location
