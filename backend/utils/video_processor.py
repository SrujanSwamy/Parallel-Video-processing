import subprocess
import os
import threading
from utils.parser import parse_execution_output

# Try to import opencv for video conversion
try:
    import cv2
    OPENCV_AVAILABLE = True
except ImportError:
    OPENCV_AVAILABLE = False
    print("Warning: OpenCV not available for video conversion")

# Map frontend feature names to backend directory names
FEATURE_MAP = {
    'grayscale': '01_grayscale',
    'gaussian_blur': '02_gaussian_blur',
    'edge_detection': '03_edge_detection',
    'white_balance': '04_white_balance',
    'histogram_equalization': '05_histogram_equalization',
    'frame_sharpening': '06_frame_sharpening',
    'scene_detection': '07_scene_detection',
    'background_subtraction': '08_background_subtraction',
    'brightness_contrast': '09_brightness_contrast',
    'motion_blur_reduction': '10_motion_blur_reduction',
    'contrast_enhancement': '11_contrast_enhancement',
    'lightup': '12_lightup'
}

class VideoProcessor:
    def __init__(self, project_root, socketio=None):
        self.project_root = project_root
        self.socketio = socketio
        self.jobs = {}  # Store job status
    
    def convert_avi_to_mp4(self, avi_path):
        """Convert AVI to MP4 for browser compatibility using FFmpeg"""
        if not os.path.exists(avi_path):
            print(f"[Convert] AVI file not found: {avi_path}")
            return avi_path
        
        try:
            mp4_path = avi_path.replace('.avi', '.mp4')
            
            # Check if MP4 already exists and is valid
            if os.path.exists(mp4_path) and os.path.getsize(mp4_path) > 0:
                print(f"[Convert] MP4 already exists: {mp4_path}")
                return mp4_path
            
            print(f"[Convert] Converting {avi_path} to {mp4_path}")
            
            # Try FFmpeg first (best quality and compatibility)
            try:
                result = subprocess.run([
                    'ffmpeg', '-y', '-i', avi_path,
                    '-c:v', 'libx264', '-preset', 'fast',
                    '-crf', '23', '-c:a', 'aac', '-b:a', '128k',
                    mp4_path
                ], capture_output=True, text=True, timeout=300)
                
                if result.returncode == 0 and os.path.exists(mp4_path):
                    print(f"[Convert] FFmpeg conversion successful")
                    return mp4_path
                else:
                    print(f"[Convert] FFmpeg failed: {result.stderr[:200]}")
            except FileNotFoundError:
                print(f"[Convert] FFmpeg not found, trying OpenCV...")
            except Exception as e:
                print(f"[Convert] FFmpeg error: {e}")
            
            # Fallback to OpenCV
            if not OPENCV_AVAILABLE:
                print(f"[Convert] OpenCV not available, using AVI")
                return avi_path
            
            cap = cv2.VideoCapture(avi_path)
            if not cap.isOpened():
                print(f"[Convert] Failed to open AVI file")
                return avi_path
            
            fps = int(cap.get(cv2.CAP_PROP_FPS))
            width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
            height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
            
            # Try H.264 codec first (better browser support)
            for codec in ['avc1', 'h264', 'H264', 'mp4v']:
                try:
                    fourcc = cv2.VideoWriter_fourcc(*codec)
                    out = cv2.VideoWriter(mp4_path, fourcc, fps, (width, height))
                    
                    if out.isOpened():
                        print(f"[Convert] Using codec: {codec}")
                        frame_count = 0
                        cap.set(cv2.CAP_PROP_POS_FRAMES, 0)  # Reset to start
                        
                        while True:
                            ret, frame = cap.read()
                            if not ret:
                                break
                            out.write(frame)
                            frame_count += 1
                        
                        out.release()
                        cap.release()
                        
                        # Ensure file is fully written to disk
                        import time
                        time.sleep(0.1)  # Small delay to ensure file is flushed
                        
                        if os.path.exists(mp4_path) and os.path.getsize(mp4_path) > 0:
                            print(f"[Convert] Converted {frame_count} frames with {codec}")
                            print(f"[Convert] Output file size: {os.path.getsize(mp4_path)} bytes")
                            return mp4_path
                        break
                except Exception as e:
                    print(f"[Convert] Codec {codec} failed: {e}")
                    continue
            
            cap.release()
            print(f"[Convert] All conversion methods failed, using AVI")
            return avi_path
                
        except Exception as e:
            print(f"[Convert] Error converting AVI to MP4: {e}")
            import traceback
            print(traceback.format_exc())
            return avi_path
    
    def emit_progress(self, job_id, message, progress):
        """Emit progress update via WebSocket"""
        if self.socketio:
            self.socketio.emit('progress', {
                'job_id': job_id,
                'message': message,
                'progress': progress
            })
    
    def run_executable(self, exe_path, args, timeout=600):
        """Execute a program directly (not through PowerShell)"""
        try:
            result = subprocess.run(
                [exe_path] + args,
                cwd=self.project_root,
                capture_output=True,
                text=True,
                timeout=timeout
            )
            return result.stdout, result.stderr, result.returncode
        except subprocess.TimeoutExpired:
            return None, f"Execution timeout after {timeout} seconds", 1
        except Exception as e:
            return None, str(e), 1
    
    def run_powershell_command(self, command, cwd=None):
        """Execute PowerShell command and return output"""
        try:
            result = subprocess.run(
                ['powershell', '-ExecutionPolicy', 'Bypass', '-Command', command],
                cwd=cwd or self.project_root,
                capture_output=True,
                text=True,
                timeout=600  # 10 minute timeout
            )
            return result.stdout, result.stderr, result.returncode
        except subprocess.TimeoutExpired:
            return None, "Command timeout after 10 minutes", 1
        except Exception as e:
            return None, str(e), 1
    
    def compile_programs(self, job_id, feature):
        """Compile all three versions of the program"""
        print(f"[Compile] Starting compilation for {feature}")
        self.emit_progress(job_id, 'Compiling sequential version...', 10)
        
        feature_key = feature.lower().replace(' ', '_')
        print(f"[Compile] Feature key: {feature_key}")
        
        # Compile sequential
        cmd = f".\\compile.ps1 -Program {feature_key}_sequential"
        print(f"[Compile] Running command: {cmd}")
        stdout, stderr, code = self.run_powershell_command(cmd)
        print(f"[Compile] Sequential - Exit code: {code}")
        if code != 0:
            print(f"[Compile] Sequential FAILED - stderr: {stderr}")
            raise Exception(f"Sequential compilation failed: {stderr}")
        
        self.emit_progress(job_id, 'Compiling pthread version...', 20)
        
        # Compile pthread
        cmd = f".\\compile.ps1 -Program {feature_key}_pthread"
        stdout, stderr, code = self.run_powershell_command(cmd)
        if code != 0:
            raise Exception(f"Pthread compilation failed: {stderr}")
        
        self.emit_progress(job_id, 'Compiling OpenMP version...', 30)
        
        # Compile OpenMP
        cmd = f".\\compile.ps1 -Program {feature_key}_openmp"
        stdout, stderr, code = self.run_powershell_command(cmd)
        if code != 0:
            raise Exception(f"OpenMP compilation failed: {stderr}")
        
        self.emit_progress(job_id, 'Compilation complete!', 35)
    
    def run_sequential(self, job_id, feature, input_video, output_path):
        """Run sequential version"""
        self.emit_progress(job_id, 'Running sequential version...', 40)
        
        feature_key = feature.lower().replace(' ', '_')
        exe_path = os.path.join(self.project_root, 'build', f'{feature_key}_sequential.exe')
        
        print(f"[Sequential] Executing: {exe_path}")
        print(f"[Sequential] Input: {input_video}")
        print(f"[Sequential] Output: {output_path}")
        
        stdout, stderr, code = self.run_executable(exe_path, [input_video, output_path])
        
        print(f"[Sequential] Exit code: {code}")
        print(f"[Sequential] STDOUT:\n{stdout}")
        print(f"[Sequential] STDERR:\n{stderr}")
        
        if code != 0:
            print(f"[Sequential] FAILED - stderr: {stderr}")
            raise Exception(f"Sequential execution failed: {stderr}")
        
        print(f"[Sequential] Success - parsing output...")
        result = parse_execution_output(stdout + stderr)
        print(f"[Sequential] Parsed metrics: {result}")
        self.emit_progress(job_id, 'Sequential version complete!', 55)
        return result
    
    def run_pthread(self, job_id, feature, input_video, output_path, num_threads):
        """Run pthread version"""
        self.emit_progress(job_id, f'Running pthread version ({num_threads} threads)...', 60)
        
        feature_key = feature.lower().replace(' ', '_')
        exe_path = os.path.join(self.project_root, 'build', f'{feature_key}_pthread.exe')
        
        print(f"[Pthread] Executing: {exe_path}")
        print(f"[Pthread] Threads: {num_threads}")
        
        stdout, stderr, code = self.run_executable(exe_path, [input_video, str(num_threads), output_path])
        
        print(f"[Pthread] Exit code: {code}")
        print(f"[Pthread] STDOUT:\n{stdout}")
        print(f"[Pthread] STDERR:\n{stderr}")
        
        if code != 0:
            print(f"[Pthread] FAILED - stderr: {stderr}")
            raise Exception(f"Pthread execution failed: {stderr}")
        
        print(f"[Pthread] Success - parsing output...")
        result = parse_execution_output(stdout + stderr)
        print(f"[Pthread] Parsed metrics: {result}")
        self.emit_progress(job_id, 'Pthread version complete!', 75)
        return result
    
    def run_openmp(self, job_id, feature, input_video, output_path, num_threads):
        """Run OpenMP version"""
        self.emit_progress(job_id, f'Running OpenMP version ({num_threads} threads)...', 80)
        
        feature_key = feature.lower().replace(' ', '_')
        exe_path = os.path.join(self.project_root, 'build', f'{feature_key}_openmp.exe')
        
        print(f"[OpenMP] Executing: {exe_path}")
        print(f"[OpenMP] Threads: {num_threads}")
        
        stdout, stderr, code = self.run_executable(exe_path, [input_video, str(num_threads), output_path])
        
        print(f"[OpenMP] Exit code: {code}")
        print(f"[OpenMP] STDOUT:\n{stdout}")
        print(f"[OpenMP] STDERR:\n{stderr}")
        
        if code != 0:
            print(f"[OpenMP] FAILED - stderr: {stderr}")
            raise Exception(f"OpenMP execution failed: {stderr}")
        
        print(f"[OpenMP] Success - parsing output...")
        result = parse_execution_output(stdout + stderr)
        print(f"[OpenMP] Parsed metrics: {result}")
        self.emit_progress(job_id, 'OpenMP version complete!', 95)
        return result
    
    def process_video_async(self, job_id, feature, input_video, output_dir, pthread_threads, openmp_threads):
        """Process video with all three methods in background thread"""
        print(f"[VideoProcessor] Starting async processing for job {job_id}")
        print(f"[VideoProcessor] Feature: {feature}, Input: {input_video}")
        print(f"[VideoProcessor] Threads - Pthread: {pthread_threads}, OpenMP: {openmp_threads}")
        try:
            self.jobs[job_id] = {
                'status': 'processing',
                'progress': 0,
                'message': 'Starting...',
                'error': None
            }
            print(f"[VideoProcessor] Job {job_id} initialized in jobs dict")
            
            # Create output directory
            os.makedirs(output_dir, exist_ok=True)
            
            # Define output paths
            feature_key = feature.lower().replace(' ', '_')
            
            # Check if this is scene detection (outputs .txt instead of .avi)
            is_scene_detection = 'scene' in feature.lower()
            file_ext = '.txt' if is_scene_detection else '.avi'
            
            seq_output = os.path.join(output_dir, f'{feature_key}_sequential{file_ext}')
            pthread_output = os.path.join(output_dir, f'{feature_key}_pthread{file_ext}')
            openmp_output = os.path.join(output_dir, f'{feature_key}_openmp{file_ext}')
            
            print(f"[VideoProcessor] Output format: {file_ext}")
            
            # Compile programs
            print(f"[VideoProcessor] Starting compilation...")
            self.compile_programs(job_id, feature)
            print(f"[VideoProcessor] Compilation complete")
            
            # Run sequential
            print(f"[VideoProcessor] Running sequential...")
            seq_metrics = self.run_sequential(job_id, feature, input_video, seq_output)
            print(f"[VideoProcessor] Sequential complete: {seq_metrics}")
            
            # Run pthread
            print(f"[VideoProcessor] Running pthread...")
            pthread_metrics = self.run_pthread(job_id, feature, input_video, pthread_output, pthread_threads)
            print(f"[VideoProcessor] Pthread complete: {pthread_metrics}")
            
            # Run OpenMP
            print(f"[VideoProcessor] Running OpenMP...")
            openmp_metrics = self.run_openmp(job_id, feature, input_video, openmp_output, openmp_threads)
            print(f"[VideoProcessor] OpenMP complete: {openmp_metrics}")
            
            # Convert AVI files to MP4 for browser compatibility (skip for scene detection)
            if is_scene_detection:
                print(f"[VideoProcessor] Scene detection outputs text files, skipping video conversion")
                seq_output_final = seq_output
                pthread_output_final = pthread_output
                openmp_output_final = openmp_output
            else:
                print(f"[VideoProcessor] Converting videos to MP4...")
                self.emit_progress(job_id, 'Converting videos to MP4...', 96)
                seq_output_final = self.convert_avi_to_mp4(seq_output)
                pthread_output_final = self.convert_avi_to_mp4(pthread_output)
                openmp_output_final = self.convert_avi_to_mp4(openmp_output)
                print(f"[VideoProcessor] Conversion complete")
            
            # Update job status
            self.jobs[job_id] = {
                'status': 'completed',
                'progress': 100,
                'message': 'Processing complete!',
                'error': None,
                'feature': feature,  # Store the feature name
                'metrics': {
                    'sequential': seq_metrics,
                    'pthread': pthread_metrics,
                    'openmp': openmp_metrics
                },
                'videos': {
                    'sequential': seq_output_final if os.path.exists(seq_output_final) else None,
                    'pthread': pthread_output_final if os.path.exists(pthread_output_final) else None,
                    'openmp': openmp_output_final if os.path.exists(openmp_output_final) else None
                },
                'config': {
                    'pthread_threads': pthread_threads,
                    'openmp_threads': openmp_threads
                }
            }
            
            self.emit_progress(job_id, 'All processing complete!', 100)
            
        except Exception as e:
            print(f"[VideoProcessor] ERROR in job {job_id}: {str(e)}")
            print(f"[VideoProcessor] Exception type: {type(e).__name__}")
            import traceback
            print(f"[VideoProcessor] Traceback:\n{traceback.format_exc()}")
            self.jobs[job_id] = {
                'status': 'failed',
                'progress': 0,
                'message': 'Processing failed',
                'error': str(e)
            }
            self.emit_progress(job_id, f'Error: {str(e)}', 0)
    
    def process_video(self, job_id, feature, input_video, output_dir, pthread_threads, openmp_threads):
        """Start video processing in background thread"""
        thread = threading.Thread(
            target=self.process_video_async,
            args=(job_id, feature, input_video, output_dir, pthread_threads, openmp_threads)
        )
        thread.daemon = True
        thread.start()
    
    def get_job_status(self, job_id):
        """Get current job status"""
        return self.jobs.get(job_id, {
            'status': 'not_found',
            'message': 'Job not found'
        })
