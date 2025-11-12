from flask import Flask, request, jsonify, send_file, make_response
from flask_cors import CORS
from flask_socketio import SocketIO
import os
import sys

# Add utils to path
sys.path.append(os.path.dirname(__file__))

from utils.file_manager import save_uploaded_file, cleanup_job_files, get_video_info
from utils.video_processor import VideoProcessor
from utils.parser import generate_performance_summary

app = Flask(__name__)
CORS(app, resources={r"/api/*": {"origins": "*"}})

# Initialize SocketIO with simpler configuration
socketio = SocketIO(
    app, 
    cors_allowed_origins="*",
    async_mode='threading',
    logger=False,
    engineio_logger=False
)

# Configuration
PROJECT_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
UPLOAD_FOLDER = os.path.join(os.path.dirname(__file__), 'uploads')
OUTPUT_FOLDER = os.path.join(os.path.dirname(__file__), 'temp_outputs')

app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER
app.config['OUTPUT_FOLDER'] = OUTPUT_FOLDER
app.config['MAX_CONTENT_LENGTH'] = 500 * 1024 * 1024  # 500MB max file size

# Initialize video processor
video_processor = VideoProcessor(PROJECT_ROOT, socketio)

# Available features
FEATURES = [
    {'id': 'grayscale', 'name': 'Grayscale Conversion'},
    {'id': 'gaussian_blur', 'name': 'Gaussian Blur'},
    {'id': 'edge_detection', 'name': 'Edge Detection'},
    {'id': 'white_balance', 'name': 'White Balance'},
    {'id': 'histogram_equalization', 'name': 'Histogram Equalization'},
    {'id': 'frame_sharpening', 'name': 'Frame Sharpening'},
    {'id': 'scene_detection', 'name': 'Scene Detection'},
    {'id': 'background_subtraction', 'name': 'Background Subtraction'},
    {'id': 'brightness_contrast', 'name': 'Brightness/Contrast'},
    {'id': 'motion_blur_reduction', 'name': 'Motion Blur Reduction'},
    {'id': 'contrast_enhancement', 'name': 'Contrast Enhancement'},
    {'id': 'lightup', 'name': 'Lightup'}
]

@app.route('/api/health', methods=['GET'])
def health_check():
    """Health check endpoint"""
    return jsonify({
        'status': 'ok',
        'message': 'Parallel Video Processing API is running'
    })

@app.route('/api/features', methods=['GET'])
def get_features():
    """Get list of available features"""
    return jsonify({
        'features': FEATURES
    })

@app.route('/api/upload', methods=['POST'])
def upload_video():
    """Upload video file"""
    try:
        if 'video' not in request.files:
            return jsonify({'error': 'No video file provided'}), 400
        
        file = request.files['video']
        
        # Save file and get job info
        file_info = save_uploaded_file(file, UPLOAD_FOLDER)
        
        # Get video metadata
        video_info = get_video_info(file_info['file_path'])
        
        response = {
            'job_id': file_info['job_id'],
            'filename': file_info['filename'],
            'size': file_info['size'],
            'video_info': video_info
        }
        
        return jsonify(response), 200
    
    except ValueError as e:
        return jsonify({'error': str(e)}), 400
    except Exception as e:
        return jsonify({'error': f'Upload failed: {str(e)}'}), 500

@app.route('/api/process', methods=['POST'])
def process_video():
    """Start video processing"""
    try:
        data = request.get_json()
        print(f"Processing request received: {data}")
        
        # Validate required fields
        required_fields = ['job_id', 'feature', 'openmp_threads', 'pthread_threads']
        for field in required_fields:
            if field not in data:
                return jsonify({'error': f'Missing required field: {field}'}), 400
        
        job_id = data['job_id']
        feature = data['feature']
        openmp_threads = int(data['openmp_threads'])
        pthread_threads = int(data['pthread_threads'])
        
        # Validate feature
        feature_ids = [f['id'] for f in FEATURES]
        if feature not in feature_ids:
            return jsonify({'error': f'Invalid feature: {feature}'}), 400
        
        # Validate thread counts
        if not (1 <= openmp_threads <= 16):
            return jsonify({'error': 'OpenMP threads must be between 1 and 16'}), 400
        if not (1 <= pthread_threads <= 16):
            return jsonify({'error': 'Pthread threads must be between 1 and 16'}), 400
        
        # Get input video path
        input_video = os.path.join(UPLOAD_FOLDER, job_id, 'input.*')
        # Find the actual file
        import glob
        input_files = glob.glob(input_video)
        if not input_files:
            return jsonify({'error': 'Input video not found'}), 404
        input_video = input_files[0]
        
        # Create output directory
        output_dir = os.path.join(OUTPUT_FOLDER, job_id)
        
        print(f"=== STARTING VIDEO PROCESSING ===")
        print(f"Job ID: {job_id}")
        print(f"Feature: {feature}")
        print(f"Input Video: {input_video}")
        print(f"Output Dir: {output_dir}")
        print(f"Threads - Pthread: {pthread_threads}, OpenMP: {openmp_threads}")
        print(f"=================================")
        
        # Start processing
        video_processor.process_video(
            job_id, 
            feature, 
            input_video, 
            output_dir,
            pthread_threads,
            openmp_threads
        )
        
        print(f"[API] process_video() called successfully for job {job_id}")
        
        return jsonify({
            'job_id': job_id,
            'status': 'processing',
            'message': 'Video processing started'
        }), 200
    
    except Exception as e:
        return jsonify({'error': f'Processing failed: {str(e)}'}), 500

@app.route('/api/status/<job_id>', methods=['GET'])
def get_status(job_id):
    """Get job status"""
    print(f"Status check for job: {job_id}")
    status = video_processor.get_job_status(job_id)
    print(f"Job status: {status}")
    return jsonify(status)

@app.route('/api/results/<job_id>', methods=['GET'])
def get_results(job_id):
    """Get processing results"""
    try:
        status = video_processor.get_job_status(job_id)
        
        if status['status'] == 'not_found':
            return jsonify({'error': 'Job not found'}), 404
        
        if status['status'] != 'completed':
            return jsonify({
                'status': status['status'],
                'message': status.get('message', 'Processing not complete')
            }), 200
        
        # Get input video path
        input_video = os.path.join(UPLOAD_FOLDER, job_id, 'input.*')
        import glob
        input_files = glob.glob(input_video)
        input_path = input_files[0] if input_files else None
        
        # Generate performance summary
        metrics = status.get('metrics', {})
        config = status.get('config', {})
        
        summary = generate_performance_summary(
            metrics.get('sequential', {}),
            metrics.get('pthread', {}),
            metrics.get('openmp', {}),
            config.get('pthread_threads', 4),
            config.get('openmp_threads', 4)
        )
        
        # Build video URLs
        videos = status.get('videos', {})
        feature = status.get('feature', '')
        
        # Check if this is scene detection (no video output, only text)
        is_scene_detection = 'scene' in feature.lower() if feature else False
        
        video_urls = {
            'input': f'/api/video/{job_id}/input' if input_path else None,
            'sequential': f'/api/video/{job_id}/sequential' if videos.get('sequential') and not is_scene_detection else None,
            'pthread': f'/api/video/{job_id}/pthread' if videos.get('pthread') and not is_scene_detection else None,
            'openmp': f'/api/video/{job_id}/openmp' if videos.get('openmp') and not is_scene_detection else None
        }
        
        # Add scene detection results if applicable
        scene_results = None
        if is_scene_detection:
            scene_results = {
                'sequential': f'/api/scene/{job_id}/sequential' if videos.get('sequential') else None,
                'pthread': f'/api/scene/{job_id}/pthread' if videos.get('pthread') else None,
                'openmp': f'/api/scene/{job_id}/openmp' if videos.get('openmp') else None
            }
        
        return jsonify({
            'status': 'completed',
            'feature': feature,
            'is_scene_detection': is_scene_detection,
            'metrics': summary,
            'videos': video_urls,
            'scene_results': scene_results,
            'raw_metrics': metrics
        }), 200
    
    except Exception as e:
        return jsonify({'error': f'Failed to get results: {str(e)}'}), 500

@app.route('/api/video/<job_id>/<video_type>', methods=['GET'])
def stream_video(job_id, video_type):
    """Stream video file"""
    try:
        print(f"[Video Stream] Request for job {job_id}, type: {video_type}")
        
        if video_type == 'input':
            # Find input video
            input_pattern = os.path.join(UPLOAD_FOLDER, job_id, 'input.*')
            import glob
            files = glob.glob(input_pattern)
            print(f"[Video Stream] Input pattern: {input_pattern}")
            print(f"[Video Stream] Found files: {files}")
            if not files:
                return jsonify({'error': 'Video not found'}), 404
            video_path = files[0]
        else:
            # Look for processed video directly on disk
            # First try to get the feature from job status
            status = video_processor.get_job_status(job_id)
            feature = status.get('feature', None)
            
            output_dir = os.path.join(OUTPUT_FOLDER, job_id)
            
            if feature:
                # We know the feature, look for specific files
                feature_key = feature.lower().replace(' ', '_')
                mp4_path = os.path.join(output_dir, f'{feature_key}_{video_type}.mp4')
                avi_path = os.path.join(output_dir, f'{feature_key}_{video_type}.avi')
                
                print(f"[Video Stream] Feature: {feature}")
                print(f"[Video Stream] Looking for: {mp4_path}")
                
                if os.path.exists(mp4_path):
                    video_path = mp4_path
                elif os.path.exists(avi_path):
                    video_path = avi_path
                else:
                    print(f"[Video Stream] File not found")
                    return jsonify({'error': 'Video not found'}), 404
            else:
                # Feature unknown, search for any matching file
                import glob
                mp4_files = glob.glob(os.path.join(output_dir, f'*_{video_type}.mp4'))
                avi_files = glob.glob(os.path.join(output_dir, f'*_{video_type}.avi'))
                
                print(f"[Video Stream] Looking in: {output_dir}")
                print(f"[Video Stream] MP4 files: {mp4_files}")
                print(f"[Video Stream] AVI files: {avi_files}")
                
                # Prefer MP4 over AVI, and take the first match
                if mp4_files:
                    video_path = mp4_files[0]
                elif avi_files:
                    video_path = avi_files[0]
                else:
                    print(f"[Video Stream] No video files found for {video_type}")
                    return jsonify({'error': 'Video not found'}), 404
        
        print(f"[Video Stream] Sending file: {video_path}")
        print(f"[Video Stream] File exists: {os.path.exists(video_path)}")
        print(f"[Video Stream] File size: {os.path.getsize(video_path) if os.path.exists(video_path) else 'N/A'}")
        
        # Verify file is not empty or corrupted
        if os.path.exists(video_path):
            file_size = os.path.getsize(video_path)
            if file_size == 0:
                print(f"[Video Stream] ERROR: File is empty!")
                return jsonify({'error': 'Video file is empty'}), 500
            if file_size < 1000:  # Suspiciously small video file
                print(f"[Video Stream] WARNING: File is very small ({file_size} bytes)")
        
        # Determine MIME type based on file extension
        if video_path.endswith('.mp4'):
            mimetype = 'video/mp4'
        elif video_path.endswith('.avi'):
            mimetype = 'video/x-msvideo'
        else:
            mimetype = 'video/mp4'  # Default to mp4
        
        print(f"[Video Stream] MIME type: {mimetype}")
        
        # Try to send the file with conditional response disabled for problematic files
        try:
            # Check if browser is requesting a range
            range_header = request.headers.get('Range', None)
            print(f"[Video Stream] Range header: {range_header}")
            
            # If there's a range request issue, send without range support
            response = send_file(
                video_path, 
                mimetype=mimetype, 
                as_attachment=False,
                conditional=True,
                download_name=None
            )
            return response
        except Exception as send_error:
            print(f"[Video Stream] send_file error: {send_error}")
            # If range request fails, try sending entire file without range support
            try:
                print(f"[Video Stream] Retrying without conditional response...")
                with open(video_path, 'rb') as f:
                    video_data = f.read()
                response = make_response(video_data)
                response.headers['Content-Type'] = mimetype
                response.headers['Content-Length'] = len(video_data)
                response.headers['Accept-Ranges'] = 'none'  # Disable range requests
                return response
            except Exception as fallback_error:
                print(f"[Video Stream] Fallback also failed: {fallback_error}")
                import traceback
                print(traceback.format_exc())
                return jsonify({'error': 'Failed to stream video'}), 500
    
    except Exception as e:
        print(f"[Video Stream] ERROR: {e}")
        import traceback
        print(traceback.format_exc())
        return jsonify({'error': f'Failed to stream video: {str(e)}'}), 500

@app.route('/api/scene/<job_id>/<scene_type>', methods=['GET'])
def get_scene_results(job_id, scene_type):
    """Get scene detection text results"""
    try:
        print(f"[Scene Results] Request for job {job_id}, type: {scene_type}")
        
        # Get the feature from job status
        status = video_processor.get_job_status(job_id)
        feature = status.get('feature', 'scene_detection')
        feature_key = feature.lower().replace(' ', '_')
        
        output_dir = os.path.join(OUTPUT_FOLDER, job_id)
        
        # Look for text file
        txt_path = os.path.join(output_dir, f'{feature_key}_{scene_type}.txt')
        
        print(f"[Scene Results] Looking for: {txt_path}")
        
        if not os.path.exists(txt_path):
            # Try generic search
            import glob
            txt_files = glob.glob(os.path.join(output_dir, f'*_{scene_type}.txt'))
            print(f"[Scene Results] Found files: {txt_files}")
            if txt_files:
                txt_path = txt_files[0]
            else:
                return jsonify({'error': 'Scene detection results not found'}), 404
        
        # Read and return the text file content
        with open(txt_path, 'r') as f:
            content = f.read()
        
        print(f"[Scene Results] Sending {len(content)} bytes")
        return jsonify({
            'content': content,
            'type': scene_type
        }), 200
    
    except Exception as e:
        print(f"[Scene Results] ERROR: {e}")
        import traceback
        print(traceback.format_exc())
        return jsonify({'error': f'Failed to get scene results: {str(e)}'}), 500

@app.route('/api/cleanup/<job_id>', methods=['DELETE'])
def cleanup_job(job_id):
    """Clean up job files"""
    try:
        cleanup_job_files(job_id, UPLOAD_FOLDER, OUTPUT_FOLDER)
        return jsonify({'message': 'Job files cleaned up successfully'}), 200
    except Exception as e:
        return jsonify({'error': f'Cleanup failed: {str(e)}'}), 500

@socketio.on('connect')
def handle_connect():
    """Handle client connection"""
    print('Client connected')

@socketio.on('disconnect')
def handle_disconnect():
    """Handle client disconnection"""
    print('Client disconnected')

if __name__ == '__main__':
    # Ensure directories exist
    os.makedirs(UPLOAD_FOLDER, exist_ok=True)
    os.makedirs(OUTPUT_FOLDER, exist_ok=True)
    
    print("=" * 60)
    print("🎥 Parallel Video Processing API Server")
    print("=" * 60)
    print(f"Project Root: {PROJECT_ROOT}")
    print(f"Upload Folder: {UPLOAD_FOLDER}")
    print(f"Output Folder: {OUTPUT_FOLDER}")
    print(f"Available Features: {len(FEATURES)}")
    print("=" * 60)
    print("Server starting on http://localhost:5000")
    print("=" * 60)
    
    socketio.run(app, debug=True, host='0.0.0.0', port=5000, allow_unsafe_werkzeug=True)
