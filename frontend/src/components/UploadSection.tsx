import React, { useCallback, useState } from 'react';

interface UploadSectionProps {
  onFileSelect: (file: File) => void;
  disabled?: boolean;
  uploading?: boolean;
}

const UploadSection: React.FC<UploadSectionProps> = ({ onFileSelect, disabled = false, uploading = false }) => {
  const [dragActive, setDragActive] = useState(false);
  const [selectedFileName, setSelectedFileName] = useState<string | null>(null);

  const handleDrag = useCallback((e: React.DragEvent) => {
    e.preventDefault();
    e.stopPropagation();
    if (e.type === 'dragenter' || e.type === 'dragover') {
      setDragActive(true);
    } else if (e.type === 'dragleave') {
      setDragActive(false);
    }
  }, []);

  const handleDrop = useCallback((e: React.DragEvent) => {
    e.preventDefault();
    e.stopPropagation();
    setDragActive(false);

    if (e.dataTransfer.files && e.dataTransfer.files[0]) {
      const file = e.dataTransfer.files[0];
      setSelectedFileName(file.name);
      onFileSelect(file);
    }
  }, [onFileSelect]);

  const handleChange = useCallback((e: React.ChangeEvent<HTMLInputElement>) => {
    if (e.target.files && e.target.files[0]) {
      const file = e.target.files[0];
      setSelectedFileName(file.name);
      onFileSelect(file);
    }
  }, [onFileSelect]);

  return (
    <div className="bg-white rounded-lg shadow-md p-6">
      <h2 className="text-xl font-semibold text-gray-800 mb-4 flex items-center">
        <span className="mr-2">📤</span>
        Upload Video
      </h2>
      
      <div
        className={`relative border-2 border-dashed rounded-lg p-8 text-center transition-all ${
          dragActive
            ? 'border-blue-500 bg-blue-50'
            : 'border-gray-300 hover:border-gray-400'
        } ${disabled ? 'opacity-50 cursor-not-allowed' : 'cursor-pointer'}`}
        onDragEnter={handleDrag}
        onDragLeave={handleDrag}
        onDragOver={handleDrag}
        onDrop={handleDrop}
      >
        <input
          type="file"
          id="video-upload"
          className="absolute inset-0 w-full h-full opacity-0 cursor-pointer"
          onChange={handleChange}
          accept="video/mp4,video/x-msvideo,video/quicktime,video/x-matroska"
          disabled={disabled || uploading}
        />
        
        <div className="pointer-events-none">
          {uploading ? (
            <>
              <div className="mx-auto w-16 h-16 mb-4">
                <div className="animate-spin rounded-full h-16 w-16 border-t-2 border-b-2 border-blue-500"></div>
              </div>
              <p className="text-gray-600 font-medium">Uploading...</p>
            </>
          ) : selectedFileName ? (
            <>
              <div className="text-5xl mb-4">✅</div>
              <p className="text-gray-700 font-medium mb-2">{selectedFileName}</p>
              <p className="text-sm text-gray-500">Click or drag to change file</p>
            </>
          ) : (
            <>
              <div className="text-5xl mb-4">🎬</div>
              <p className="text-gray-700 font-medium mb-2">
                Drag and drop your video here
              </p>
              <p className="text-sm text-gray-500 mb-4">
                or click to browse files
              </p>
              <p className="text-xs text-gray-400">
                Supported formats: MP4, AVI, MOV, MKV (Max 500MB)
              </p>
            </>
          )}
        </div>
      </div>
    </div>
  );
};

export default UploadSection;
