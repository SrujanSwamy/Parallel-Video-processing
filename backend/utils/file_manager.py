import os
import uuid
import shutil
from werkzeug.utils import secure_filename

ALLOWED_EXTENSIONS = {'mp4', 'avi', 'mov', 'mkv', 'wmv'}

def allowed_file(filename):
    """Check if file extension is allowed"""
    return '.' in filename and filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

def generate_job_id():
    """Generate unique job ID"""
    return str(uuid.uuid4())

def save_uploaded_file(file, upload_folder):
    """Save uploaded file and return job info"""
    if not file or file.filename == '':
        raise ValueError("No file provided")
    
    if not allowed_file(file.filename):
        raise ValueError(f"File type not allowed. Supported: {', '.join(ALLOWED_EXTENSIONS)}")
    
    # Generate job ID and secure filename
    job_id = generate_job_id()
    filename = secure_filename(file.filename)
    file_extension = filename.rsplit('.', 1)[1].lower()
    
    # Create job-specific directory
    job_dir = os.path.join(upload_folder, job_id)
    os.makedirs(job_dir, exist_ok=True)
    
    # Save file
    saved_filename = f"input.{file_extension}"
    file_path = os.path.join(job_dir, saved_filename)
    file.save(file_path)
    
    return {
        'job_id': job_id,
        'filename': filename,
        'file_path': file_path,
        'size': os.path.getsize(file_path)
    }

def cleanup_job_files(job_id, upload_folder, output_folder):
    """Clean up files for a specific job"""
    try:
        # Clean upload directory
        job_upload_dir = os.path.join(upload_folder, job_id)
        if os.path.exists(job_upload_dir):
            shutil.rmtree(job_upload_dir)
        
        # Clean output directory
        job_output_dir = os.path.join(output_folder, job_id)
        if os.path.exists(job_output_dir):
            shutil.rmtree(job_output_dir)
    except Exception as e:
        print(f"Error cleaning up job {job_id}: {e}")

def get_video_info(file_path):
    """Get video metadata using OpenCV"""
    try:
        import cv2
        if not hasattr(cv2, 'VideoCapture'):
            print("Warning: cv2.VideoCapture not available, skipping video info extraction")
            return None
            
        cap = cv2.VideoCapture(file_path)
        
        if not cap.isOpened():
            return None
        
        info = {
            'width': int(cap.get(cv2.CAP_PROP_FRAME_WIDTH)),
            'height': int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT)),
            'fps': cap.get(cv2.CAP_PROP_FPS),
            'frame_count': int(cap.get(cv2.CAP_PROP_FRAME_COUNT)),
            'duration': int(cap.get(cv2.CAP_PROP_FRAME_COUNT)) / cap.get(cv2.CAP_PROP_FPS) if cap.get(cv2.CAP_PROP_FPS) > 0 else 0
        }
        
        cap.release()
        return info
    except Exception as e:
        print(f"Error getting video info: {e}")
        return None
