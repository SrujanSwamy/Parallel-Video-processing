# Clean Repository Script
# Removes all unnecessary files before committing to Git

Write-Host "============================================" -ForegroundColor Cyan
Write-Host "  Cleaning Parallel Video Processing Repo  " -ForegroundColor Cyan
Write-Host "============================================" -ForegroundColor Cyan
Write-Host ""

# Function to safely remove items
function Safe-Remove {
    param($Path, $Description)
    if (Test-Path $Path) {
        try {
            Remove-Item $Path -Recurse -Force -ErrorAction Stop
            Write-Host "[✓] Cleaned: $Description" -ForegroundColor Green
        } catch {
            Write-Host "[✗] Failed: $Description - $($_.Exception.Message)" -ForegroundColor Red
        }
    } else {
        Write-Host "[i] Skipped: $Description (not found)" -ForegroundColor Yellow
    }
}

Write-Host "Cleaning compiled executables..." -ForegroundColor White
Get-ChildItem -Path "build" -Filter "*.exe" -ErrorAction SilentlyContinue | Remove-Item -Force
Write-Host "[✓] Cleaned build/*.exe" -ForegroundColor Green

Write-Host "`nCleaning Python cache..." -ForegroundColor White
Get-ChildItem -Recurse -Directory -Filter "__pycache__" | Remove-Item -Recurse -Force -ErrorAction SilentlyContinue
Write-Host "[✓] Cleaned __pycache__ directories" -ForegroundColor Green

Write-Host "`nCleaning backend temporary files..." -ForegroundColor White
if (Test-Path "backend\uploads") {
    Get-ChildItem "backend\uploads" -Directory | Remove-Item -Recurse -Force -ErrorAction SilentlyContinue
    Write-Host "[✓] Cleaned backend/uploads" -ForegroundColor Green
}
if (Test-Path "backend\temp_outputs") {
    Get-ChildItem "backend\temp_outputs" -Directory | Remove-Item -Recurse -Force -ErrorAction SilentlyContinue
    Write-Host "[✓] Cleaned backend/temp_outputs" -ForegroundColor Green
}

Write-Host "`nCleaning video output files..." -ForegroundColor White
Get-ChildItem -Path "outputs" -Recurse -Include *.avi,*.mp4,*.txt -File | Remove-Item -Force -ErrorAction SilentlyContinue
Write-Host "[✓] Cleaned outputs/**/*.{avi,mp4,txt}" -ForegroundColor Green

Write-Host "`nCleaning input video files..." -ForegroundColor White
Get-ChildItem -Path "input_videos" -Include *.mp4,*.avi,*.mov,*.mkv -File | Remove-Item -Force -ErrorAction SilentlyContinue
Write-Host "[✓] Cleaned input_videos/*.{mp4,avi,mov,mkv}" -ForegroundColor Green

Write-Host "`nCleaning Node.js build artifacts..." -ForegroundColor White
if (Test-Path "frontend\build") {
    Remove-Item "frontend\build" -Recurse -Force -ErrorAction SilentlyContinue
    Write-Host "[✓] Cleaned frontend/build" -ForegroundColor Green
}

Write-Host "`nCleaning log files..." -ForegroundColor White
Get-ChildItem -Recurse -Include *.log -File | Remove-Item -Force -ErrorAction SilentlyContinue
Write-Host "[✓] Cleaned *.log files" -ForegroundColor Green

Write-Host "`n============================================" -ForegroundColor Cyan
Write-Host "  Repository Cleanup Complete!             " -ForegroundColor Cyan
Write-Host "============================================" -ForegroundColor Cyan
Write-Host ""
Write-Host "You can now safely commit to Git." -ForegroundColor Green
Write-Host "Run 'git status' to see what will be committed." -ForegroundColor Yellow
Write-Host ""
