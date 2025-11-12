#!/usr/bin/env python3
"""Convert existing AVI files to MP4"""
import os
import cv2
import glob

def convert_avi_to_mp4(avi_path):
    """Convert AVI to MP4"""
    if not os.path.exists(avi_path):
        print(f"File not found: {avi_path}")
        return None
    
    mp4_path = avi_path.replace('.avi', '.mp4')
    
    if os.path.exists(mp4_path):
        print(f"MP4 already exists: {mp4_path}")
        return mp4_path
    
    print(f"Converting: {avi_path}")
    
    try:
        cap = cv2.VideoCapture(avi_path)
        if not cap.isOpened():
            print(f"  ERROR: Cannot open {avi_path}")
            return None
        
        fps = int(cap.get(cv2.CAP_PROP_FPS))
        width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
        height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
        
        print(f"  Resolution: {width}x{height} @ {fps}fps")
        
        fourcc = cv2.VideoWriter_fourcc(*'mp4v')
        out = cv2.VideoWriter(mp4_path, fourcc, fps, (width, height))
        
        if not out.isOpened():
            print(f"  ERROR: Cannot create MP4 writer")
            cap.release()
            return None
        
        frame_count = 0
        while True:
            ret, frame = cap.read()
            if not ret:
                break
            out.write(frame)
            frame_count += 1
            if frame_count % 30 == 0:
                print(f"  Progress: {frame_count} frames")
        
        cap.release()
        out.release()
        
        print(f"  ✓ Converted {frame_count} frames")
        return mp4_path
    
    except Exception as e:
        print(f"  ERROR: {e}")
        return None

# Find all AVI files in temp_outputs
temp_outputs = os.path.join(os.path.dirname(__file__), 'temp_outputs')
print(f"Searching for AVI files in: {temp_outputs}\n")

avi_files = glob.glob(os.path.join(temp_outputs, '**', '*.avi'), recursive=True)

if not avi_files:
    print("No AVI files found!")
else:
    print(f"Found {len(avi_files)} AVI file(s):\n")
    for avi_file in avi_files:
        convert_avi_to_mp4(avi_file)
        print()

print("Done!")
