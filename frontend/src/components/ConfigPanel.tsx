import React from 'react';
import { Feature } from '../services/api';

interface ConfigPanelProps {
  features: Feature[];
  selectedFeature: string;
  onFeatureChange: (feature: string) => void;
  openmptThreads: number;
  onOpenmpThreadsChange: (threads: number) => void;
  pthreadThreads: number;
  onPthreadThreadsChange: (threads: number) => void;
  onProcess: () => void;
  disabled?: boolean;
  processing?: boolean;
}

const ConfigPanel: React.FC<ConfigPanelProps> = ({
  features,
  selectedFeature,
  onFeatureChange,
  openmptThreads,
  onOpenmpThreadsChange,
  pthreadThreads,
  onPthreadThreadsChange,
  onProcess,
  disabled = false,
  processing = false,
}) => {
  // Function to get display name for features
  const getDisplayName = (featureName: string): string => {
    if (featureName === 'Motion Blur Reduction') {
      return 'Motion Blur';
    }
    return featureName;
  };

  return (
    <div className="bg-white rounded-lg shadow-md p-6">
      <h2 className="text-xl font-semibold text-gray-800 mb-4 flex items-center">
        <span className="mr-2">⚙️</span>
        Processing Configuration
      </h2>

      <div className="space-y-4">
        {/* Feature Selection */}
        <div>
          <label htmlFor="feature-select" className="block text-sm font-medium text-gray-700 mb-2">
            Select Feature
          </label>
          <select
            id="feature-select"
            value={selectedFeature}
            onChange={(e) => onFeatureChange(e.target.value)}
            disabled={disabled || processing}
            className="w-full px-4 py-2 border border-gray-300 rounded-lg focus:ring-2 focus:ring-blue-500 focus:border-blue-500 disabled:bg-gray-100 disabled:cursor-not-allowed"
          >
            <option value="">-- Select a feature --</option>
            {features.map((feature) => (
              <option key={feature.id} value={feature.id}>
                {getDisplayName(feature.name)}
              </option>
            ))}
          </select>
        </div>

        {/* Thread Configuration */}
        <div className="grid grid-cols-1 md:grid-cols-2 gap-4">
          {/* OpenMP Threads */}
          <div>
            <label htmlFor="openmp-threads" className="block text-sm font-medium text-gray-700 mb-2">
              OpenMP Threads
            </label>
            <input
              type="number"
              id="openmp-threads"
              min="1"
              max="16"
              value={openmptThreads}
              onChange={(e) => onOpenmpThreadsChange(parseInt(e.target.value) || 1)}
              disabled={disabled || processing}
              className="w-full px-4 py-2 border border-gray-300 rounded-lg focus:ring-2 focus:ring-blue-500 focus:border-blue-500 disabled:bg-gray-100 disabled:cursor-not-allowed"
            />
            <p className="text-xs text-gray-500 mt-1">Range: 1-16 threads</p>
          </div>

          {/* Pthread Threads */}
          <div>
            <label htmlFor="pthread-threads" className="block text-sm font-medium text-gray-700 mb-2">
              Pthread Threads
            </label>
            <input
              type="number"
              id="pthread-threads"
              min="1"
              max="16"
              value={pthreadThreads}
              onChange={(e) => onPthreadThreadsChange(parseInt(e.target.value) || 1)}
              disabled={disabled || processing}
              className="w-full px-4 py-2 border border-gray-300 rounded-lg focus:ring-2 focus:ring-blue-500 focus:border-blue-500 disabled:bg-gray-100 disabled:cursor-not-allowed"
            />
            <p className="text-xs text-gray-500 mt-1">Range: 1-16 threads</p>
          </div>
        </div>

        {/* Process Button */}
        <button
          onClick={onProcess}
          disabled={disabled || processing || !selectedFeature}
          className="w-full bg-gradient-to-r from-blue-600 to-purple-600 hover:from-blue-700 hover:to-purple-700 text-white font-semibold py-3 px-6 rounded-lg transition-all transform hover:scale-[1.02] disabled:opacity-50 disabled:cursor-not-allowed disabled:transform-none flex items-center justify-center space-x-2"
        >
          {processing ? (
            <>
              <div className="animate-spin rounded-full h-5 w-5 border-t-2 border-b-2 border-white"></div>
              <span>Processing...</span>
            </>
          ) : (
            <>
              <span>▶️</span>
              <span>Process Video</span>
            </>
          )}
        </button>
      </div>
    </div>
  );
};

export default ConfigPanel;
