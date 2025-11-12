import React from 'react';
import VideoPlayer from './VideoPlayer';

interface VideoComparisonProps {
  inputVideoUrl: string | null;
  sequentialVideoUrl: string | null;
  pthreadVideoUrl: string | null;
  openmpVideoUrl: string | null;
}

const VideoComparison: React.FC<VideoComparisonProps> = ({
  inputVideoUrl,
  sequentialVideoUrl,
  pthreadVideoUrl,
  openmpVideoUrl,
}) => {
  return (
    <div className="bg-white rounded-lg shadow-md p-6">
      <h2 className="text-xl font-semibold text-gray-800 mb-4 flex items-center">
        <span className="mr-2">📺</span>
        Video Comparison
      </h2>

      <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-4 gap-4">
        <VideoPlayer
          title="Input Video"
          videoUrl={inputVideoUrl}
          label="Original"
        />
        
        <VideoPlayer
          title="Sequential"
          videoUrl={sequentialVideoUrl}
          label="Single Thread"
        />
        
        <VideoPlayer
          title="Pthread"
          videoUrl={pthreadVideoUrl}
          label="Multi-threaded"
        />
        
        <VideoPlayer
          title="OpenMP"
          videoUrl={openmpVideoUrl}
          label="Parallel"
        />
      </div>
    </div>
  );
};

export default VideoComparison;
