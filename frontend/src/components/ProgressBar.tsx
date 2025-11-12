import React from 'react';

interface ProgressBarProps {
  progress: number;
  message: string;
  visible: boolean;
}

const ProgressBar: React.FC<ProgressBarProps> = ({ progress, message, visible }) => {
  if (!visible) return null;

  return (
    <div className="bg-white rounded-lg shadow-md p-6 fade-in">
      <h2 className="text-xl font-semibold text-gray-800 mb-4 flex items-center">
        <span className="mr-2">⚡</span>
        Processing Status
      </h2>

      <div className="space-y-3">
        <div className="flex justify-between items-center mb-2">
          <span className="text-sm font-medium text-gray-700">{message}</span>
          <span className="text-sm font-bold text-blue-600">{progress}%</span>
        </div>

        {/* Progress Bar */}
        <div className="w-full bg-gray-200 rounded-full h-4 overflow-hidden">
          <div
            className={`h-full transition-all duration-300 ease-out rounded-full ${
              progress < 100 ? 'progress-shimmer' : 'bg-green-500'
            }`}
            style={{ width: `${progress}%` }}
          ></div>
        </div>

        {/* Status Steps */}
        <div className="mt-4 grid grid-cols-2 md:grid-cols-4 gap-2 text-xs">
          <div className={`p-2 rounded ${progress >= 35 ? 'bg-green-100 text-green-700' : 'bg-gray-100 text-gray-500'}`}>
            ✓ Compilation
          </div>
          <div className={`p-2 rounded ${progress >= 55 ? 'bg-green-100 text-green-700' : progress >= 35 ? 'bg-blue-100 text-blue-700' : 'bg-gray-100 text-gray-500'}`}>
            {progress >= 55 ? '✓' : progress >= 35 ? '⏳' : '○'} Sequential
          </div>
          <div className={`p-2 rounded ${progress >= 75 ? 'bg-green-100 text-green-700' : progress >= 55 ? 'bg-blue-100 text-blue-700' : 'bg-gray-100 text-gray-500'}`}>
            {progress >= 75 ? '✓' : progress >= 55 ? '⏳' : '○'} Pthread
          </div>
          <div className={`p-2 rounded ${progress >= 100 ? 'bg-green-100 text-green-700' : progress >= 75 ? 'bg-blue-100 text-blue-700' : 'bg-gray-100 text-gray-500'}`}>
            {progress >= 100 ? '✓' : progress >= 75 ? '⏳' : '○'} OpenMP
          </div>
        </div>
      </div>
    </div>
  );
};

export default ProgressBar;
