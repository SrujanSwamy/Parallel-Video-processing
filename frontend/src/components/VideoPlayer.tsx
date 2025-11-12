import React, { useState, useRef } from 'react';

interface VideoPlayerProps {
  title: string;
  videoUrl: string | null;
  label?: string;
}

const VideoPlayer: React.FC<VideoPlayerProps> = ({ title, videoUrl, label }) => {
  const [isPlaying, setIsPlaying] = useState(false);
  const [error, setError] = useState<string | null>(null);
  const videoRef = useRef<HTMLVideoElement>(null);

  // Ensure video URL includes the API base URL
  const fullVideoUrl = videoUrl ? 
    (videoUrl.startsWith('http') ? videoUrl : `http://localhost:5000${videoUrl}`) 
    : null;

  const handleError = () => {
    setError('Failed to load video');
    console.error('Video load error:', title, fullVideoUrl);
  };

  const togglePlay = () => {
    if (videoRef.current) {
      if (isPlaying) {
        videoRef.current.pause();
      } else {
        videoRef.current.play();
      }
      setIsPlaying(!isPlaying);
    }
  };

  if (!videoUrl) {
    return (
      <div className="bg-gray-100 rounded-lg p-4">
        <h3 className="text-sm font-semibold text-gray-700 mb-2">{title}</h3>
        <div className="aspect-video bg-gray-200 rounded flex items-center justify-center">
          <span className="text-gray-400">No video available</span>
        </div>
      </div>
    );
  }

  return (
    <div className="bg-white rounded-lg shadow-md p-4">
      <div className="flex items-center justify-between mb-2">
        <h3 className="text-sm font-semibold text-gray-800">{title}</h3>
        {label && (
          <span className="text-xs px-2 py-1 bg-blue-100 text-blue-700 rounded-full">
            {label}
          </span>
        )}
      </div>
      
      <div className="relative group">
        {error ? (
          <div className="w-full aspect-video bg-red-100 rounded flex items-center justify-center text-red-600">
            <div className="text-center">
              <p className="font-semibold">❌ {error}</p>
              <p className="text-sm mt-2">URL: {fullVideoUrl}</p>
            </div>
          </div>
        ) : (
          <video
            ref={videoRef}
            src={fullVideoUrl || ''}
            className="w-full aspect-video bg-black rounded"
            controls
            onPlay={() => setIsPlaying(true)}
            onPause={() => setIsPlaying(false)}
            onError={handleError}
            onLoadedData={() => console.log('Video loaded:', title)}
          />
        )}
      </div>
    </div>
  );
};

export default VideoPlayer;
