# Startup script for Parallel Video Processing Application
# This script starts both backend and frontend servers

Write-Host "=========================================" -ForegroundColor Cyan
Write-Host "  Parallel Video Processing Application  " -ForegroundColor Cyan
Write-Host "=========================================" -ForegroundColor Cyan
Write-Host ""

# Check if Python is installed
try {
    $pythonVersion = python --version 2>&1
    Write-Host "Python found: $pythonVersion" -ForegroundColor Green
} catch {
    Write-Host "Python not found! Please install Python 3.8+" -ForegroundColor Red
    exit 1
}

# Check if Node.js is installed
try {
    $nodeVersion = node --version 2>&1
    Write-Host "Node.js found: $nodeVersion" -ForegroundColor Green
} catch {
    Write-Host "Node.js not found! Please install Node.js 16+" -ForegroundColor Red
    exit 1
}

Write-Host ""
Write-Host "Starting servers..." -ForegroundColor Yellow
Write-Host ""

# Function to start backend
$backendScript = {
    Set-Location -Path $using:PSScriptRoot
    Set-Location -Path "backend"
    Write-Host "Starting Backend Server..." -ForegroundColor Cyan
    python app.py
}

# Function to start frontend
$frontendScript = {
    Set-Location -Path $using:PSScriptRoot
    Set-Location -Path "frontend"
    Write-Host "Starting Frontend Application..." -ForegroundColor Cyan
    npm start
}

# Start backend in new window
Write-Host "Starting Backend Server (Flask)..." -ForegroundColor Yellow
Start-Process powershell -ArgumentList "-NoExit", "-Command", "& {$backendScript}"

# Wait for backend to start
Write-Host "  Waiting for backend to initialize..." -ForegroundColor Gray
Start-Sleep -Seconds 3

# Start frontend in new window
Write-Host "Starting Frontend Application (React)..." -ForegroundColor Yellow
Start-Process powershell -ArgumentList "-NoExit", "-Command", "& {$frontendScript}"

Write-Host ""
Write-Host "=========================================" -ForegroundColor Green
Write-Host "  Servers Starting!                      " -ForegroundColor Green
Write-Host "=========================================" -ForegroundColor Green
Write-Host ""
Write-Host "Backend API:  http://localhost:5000" -ForegroundColor Cyan
Write-Host "Frontend App: http://localhost:3000" -ForegroundColor Cyan
Write-Host ""
Write-Host "Two new PowerShell windows have opened:" -ForegroundColor Yellow
Write-Host "  1. Backend Server (Flask)" -ForegroundColor White
Write-Host "  2. Frontend App (React)" -ForegroundColor White
Write-Host ""
Write-Host "To stop the servers:" -ForegroundColor Yellow
Write-Host "  - Close both PowerShell windows" -ForegroundColor White
Write-Host "  - Or press Ctrl+C in each window" -ForegroundColor White
Write-Host ""
Write-Host "Application will open automatically in your browser..." -ForegroundColor Green
Write-Host ""

# Wait a bit then open browser
Start-Sleep -Seconds 8
Start-Process "http://localhost:3000"

Write-Host "Application launched!" -ForegroundColor Green
Write-Host ""
Write-Host "Press any key to exit this window (servers will keep running)..."
$null = $Host.UI.RawUI.ReadKey('NoEcho,IncludeKeyDown')
