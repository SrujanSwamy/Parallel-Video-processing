import React, { useEffect, useState } from 'react';
import { getSceneDetectionResult, SceneDetectionResult } from '../services/api';

interface SceneDetectionResultsProps {
  jobId: string;
  inputVideoUrl: string | null;
}

interface SceneResults {
  sequential: string | null;
  pthread: string | null;
  openmp: string | null;
}

const SceneDetectionResults: React.FC<SceneDetectionResultsProps> = ({ jobId, inputVideoUrl }) => {
  const [sceneResults, setSceneResults] = useState<SceneResults>({
    sequential: null,
    pthread: null,
    openmp: null,
  });
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState<string | null>(null);

  useEffect(() => {
    const fetchSceneResults = async () => {
      setLoading(true);
      setError(null);
      
      try {
        const [seqResult, pthreadResult, openmpResult] = await Promise.all([
          getSceneDetectionResult(jobId, 'sequential').catch(() => null),
          getSceneDetectionResult(jobId, 'pthread').catch(() => null),
          getSceneDetectionResult(jobId, 'openmp').catch(() => null),
        ]);
        
        setSceneResults({
          sequential: seqResult?.content || null,
          pthread: pthreadResult?.content || null,
          openmp: openmpResult?.content || null,
        });
      } catch (err) {
        setError('Failed to load scene detection results');
        console.error('Error loading scene results:', err);
      } finally {
        setLoading(false);
      }
    };
    
    fetchSceneResults();
  }, [jobId]);

  if (loading) {
    return (
      <div className="bg-white rounded-lg shadow-md p-8 text-center">
        <div className="animate-spin rounded-full h-12 w-12 border-b-2 border-blue-600 mx-auto"></div>
        <p className="mt-4 text-gray-600">Loading scene detection results...</p>
      </div>
    );
  }

  if (error) {
    return (
      <div className="bg-red-50 border border-red-200 rounded-lg p-6">
        <p className="text-red-700">❌ {error}</p>
      </div>
    );
  }

  const parseSceneChanges = (content: string | null): Array<{ frame: number; timestamp: string }> => {
    if (!content) return [];
    const lines = content.trim().split('\n');
    const scenes: Array<{ frame: number; timestamp: string }> = [];
    
    // Parse the actual output format from scene detection
    // Format: Frame numbers appear after "Frame Number    Timestamp (s)" line
    let inDataSection = false;
    lines.forEach(line => {
      // Check if we've reached the data section
      if (line.includes('Frame Number') && line.includes('Timestamp')) {
        inDataSection = true;
        return;
      }
      
      // Skip separator lines
      if (line.includes('---') || line.includes('===')) {
        return;
      }
      
      // Parse frame numbers from the data section
      if (inDataSection) {
        const trimmed = line.trim();
        if (trimmed) {
          // Extract frame number and timestamp from lines like "129             4.300"
          const match = trimmed.match(/^(\d+)\s+([\d.]+)/);
          if (match) {
            scenes.push({
              frame: parseInt(match[1], 10),
              timestamp: match[2] + 's'
            });
          }
        }
      }
    });
    return scenes;
  };

  const seqFrames = parseSceneChanges(sceneResults.sequential);
  const pthreadFrames = parseSceneChanges(sceneResults.pthread);
  const openmpFrames = parseSceneChanges(sceneResults.openmp);

  // Construct full video URL
  const fullInputVideoUrl = inputVideoUrl ? 
    (inputVideoUrl.startsWith('http') ? inputVideoUrl : `http://localhost:5000${inputVideoUrl}`) 
    : null;

  return (
    <div className="space-y-6">
      {/* Input Video */}
      {fullInputVideoUrl && (
        <div className="bg-white rounded-lg shadow-md p-6">
          <h2 className="text-xl font-semibold mb-4 text-gray-800">📹 Input Video</h2>
          <div className="flex justify-center">
            <video 
              src={fullInputVideoUrl} 
              controls 
              className="max-w-full rounded-lg shadow-sm"
              style={{ maxHeight: '400px' }}
            >
              Your browser does not support the video tag.
            </video>
          </div>
        </div>
      )}

      {/* Scene Detection Results Grid */}
      <div className="grid grid-cols-1 md:grid-cols-3 gap-6">
        {/* Sequential Results */}
        <div className="bg-white rounded-lg shadow-md p-6">
          <h3 className="text-lg font-semibold mb-3 text-gray-800 flex items-center">
            <span className="text-2xl mr-2">🔄</span>
            Sequential
          </h3>
          <div className="bg-gray-50 rounded p-4 max-h-96 overflow-y-auto">
            {sceneResults.sequential ? (
              <>
                <p className="text-sm text-gray-700 font-medium mb-2">
                  Detected {seqFrames.length} scene change{seqFrames.length !== 1 ? 's' : ''}:
                </p>
                {seqFrames.length > 0 ? (
                  <ul className="space-y-2">
                    {seqFrames.map((scene, idx) => (
                      <li key={idx} className="text-sm text-gray-600">
                        <span className="font-medium">Frame {scene.frame}</span>
                        <span className="text-gray-500"> @ {scene.timestamp}</span>
                      </li>
                    ))}
                  </ul>
                ) : (
                  <p className="text-sm text-gray-500 italic">No scene changes detected</p>
                )}
              </>
            ) : (
              <p className="text-sm text-gray-500">No results available</p>
            )}
          </div>
        </div>

        {/* Pthread Results */}
        <div className="bg-white rounded-lg shadow-md p-6">
          <h3 className="text-lg font-semibold mb-3 text-gray-800 flex items-center">
            <span className="text-2xl mr-2">🧵</span>
            Pthread
          </h3>
          <div className="bg-gray-50 rounded p-4 max-h-96 overflow-y-auto">
            {sceneResults.pthread ? (
              <>
                <p className="text-sm text-gray-700 font-medium mb-2">
                  Detected {pthreadFrames.length} scene change{pthreadFrames.length !== 1 ? 's' : ''}:
                </p>
                {pthreadFrames.length > 0 ? (
                  <ul className="space-y-2">
                    {pthreadFrames.map((scene, idx) => (
                      <li key={idx} className="text-sm text-gray-600">
                        <span className="font-medium">Frame {scene.frame}</span>
                        <span className="text-gray-500"> @ {scene.timestamp}</span>
                      </li>
                    ))}
                  </ul>
                ) : (
                  <p className="text-sm text-gray-500 italic">No scene changes detected</p>
                )}
              </>
            ) : (
              <p className="text-sm text-gray-500">No results available</p>
            )}
          </div>
        </div>

        {/* OpenMP Results */}
        <div className="bg-white rounded-lg shadow-md p-6">
          <h3 className="text-lg font-semibold mb-3 text-gray-800 flex items-center">
            <span className="text-2xl mr-2">⚡</span>
            OpenMP
          </h3>
          <div className="bg-gray-50 rounded p-4 max-h-96 overflow-y-auto">
            {sceneResults.openmp ? (
              <>
                <p className="text-sm text-gray-700 font-medium mb-2">
                  Detected {openmpFrames.length} scene change{openmpFrames.length !== 1 ? 's' : ''}:
                </p>
                {openmpFrames.length > 0 ? (
                  <ul className="space-y-2">
                    {openmpFrames.map((scene, idx) => (
                      <li key={idx} className="text-sm text-gray-600">
                        <span className="font-medium">Frame {scene.frame}</span>
                        <span className="text-gray-500"> @ {scene.timestamp}</span>
                      </li>
                    ))}
                  </ul>
                ) : (
                  <p className="text-sm text-gray-500 italic">No scene changes detected</p>
                )}
              </>
            ) : (
              <p className="text-sm text-gray-500">No results available</p>
            )}
          </div>
        </div>
      </div>

      {/* Raw Results (Collapsible) */}
      <details className="bg-white rounded-lg shadow-md p-6">
        <summary className="text-lg font-semibold text-gray-800 cursor-pointer hover:text-blue-600">
          📄 Raw Output (Click to expand)
        </summary>
        <div className="mt-4 space-y-4">
          <div>
            <h4 className="font-medium text-gray-700 mb-2">Sequential:</h4>
            <pre className="bg-gray-50 rounded p-3 text-xs overflow-x-auto whitespace-pre-wrap">
              {sceneResults.sequential || 'No output'}
            </pre>
          </div>
          <div>
            <h4 className="font-medium text-gray-700 mb-2">Pthread:</h4>
            <pre className="bg-gray-50 rounded p-3 text-xs overflow-x-auto whitespace-pre-wrap">
              {sceneResults.pthread || 'No output'}
            </pre>
          </div>
          <div>
            <h4 className="font-medium text-gray-700 mb-2">OpenMP:</h4>
            <pre className="bg-gray-50 rounded p-3 text-xs overflow-x-auto whitespace-pre-wrap">
              {sceneResults.openmp || 'No output'}
            </pre>
          </div>
        </div>
      </details>
    </div>
  );
};

export default SceneDetectionResults;
