import re

def parse_execution_output(output_text):
    """
    Parse C++ program output to extract execution time and other metrics
    
    Expected output format:
    "Execution time: 2.345s"
    "Processing 1000 frames"
    etc.
    """
    metrics = {
        'execution_time': None,
        'frames_processed': None,
        'fps': None,
        'success': False,
        'error': None
    }
    
    try:
        # Extract execution time (format: "Execution time: X.XXXs")
        time_match = re.search(r'Execution time:\s+([\d.]+)s', output_text)
        if time_match:
            metrics['execution_time'] = float(time_match.group(1))
            metrics['success'] = True
        
        # Extract frames processed
        frames_match = re.search(r'Processing (\d+) frames', output_text)
        if frames_match:
            metrics['frames_processed'] = int(frames_match.group(1))
        
        # Extract processed frames count (alternative format)
        processed_match = re.search(r'Processed (\d+) frames', output_text)
        if processed_match:
            metrics['frames_processed'] = int(processed_match.group(1))
        
        # Calculate FPS if we have both time and frames
        if metrics['execution_time'] and metrics['frames_processed']:
            metrics['fps'] = round(metrics['frames_processed'] / metrics['execution_time'], 2)
        
        # Check for errors
        if 'error' in output_text.lower() or 'failed' in output_text.lower():
            error_match = re.search(r'[Ee]rror:?\s*(.+?)(?:\n|$)', output_text)
            if error_match:
                metrics['error'] = error_match.group(1).strip()
                metrics['success'] = False
    
    except Exception as e:
        metrics['error'] = f"Parsing error: {str(e)}"
        metrics['success'] = False
    
    return metrics

def calculate_speedup(sequential_time, parallel_time):
    """Calculate speedup factor"""
    if sequential_time and parallel_time and parallel_time > 0:
        return round(sequential_time / parallel_time, 2)
    return None

def calculate_efficiency(speedup, num_threads):
    """Calculate parallel efficiency as percentage"""
    if speedup and num_threads and num_threads > 0:
        return round((speedup / num_threads) * 100, 2)
    return None

def generate_performance_summary(sequential_metrics, pthread_metrics, openmp_metrics, pthread_threads, openmp_threads):
    """Generate comprehensive performance comparison"""
    
    seq_time = sequential_metrics.get('execution_time')
    pthread_time = pthread_metrics.get('execution_time')
    openmp_time = openmp_metrics.get('execution_time')
    
    summary = {
        'sequential': {
            'time': seq_time,
            'fps': sequential_metrics.get('fps'),
            'frames': sequential_metrics.get('frames_processed'),
            'speedup': 1.0,
            'efficiency': 100.0
        },
        'pthread': {
            'time': pthread_time,
            'fps': pthread_metrics.get('fps'),
            'frames': pthread_metrics.get('frames_processed'),
            'threads': pthread_threads,
            'speedup': calculate_speedup(seq_time, pthread_time),
            'efficiency': calculate_efficiency(calculate_speedup(seq_time, pthread_time), pthread_threads)
        },
        'openmp': {
            'time': openmp_time,
            'fps': openmp_metrics.get('fps'),
            'frames': openmp_metrics.get('frames_processed'),
            'threads': openmp_threads,
            'speedup': calculate_speedup(seq_time, openmp_time),
            'efficiency': calculate_efficiency(calculate_speedup(seq_time, openmp_time), openmp_threads)
        }
    }
    
    return summary
