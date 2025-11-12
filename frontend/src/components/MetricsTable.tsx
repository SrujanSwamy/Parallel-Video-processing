import React from 'react';
import { Metrics } from '../services/api';

interface MetricsTableProps {
  sequential: Metrics;
  pthread: Metrics;
  openmp: Metrics;
}

const MetricsTable: React.FC<MetricsTableProps> = ({ sequential, pthread, openmp }) => {
  const formatTime = (time: number | null) => time !== null ? `${time.toFixed(3)}s` : 'N/A';
  const formatSpeedup = (speedup: number | null) => speedup !== null ? `${speedup.toFixed(2)}x` : 'N/A';
  const formatEfficiency = (eff: number | null) => eff !== null ? `${eff.toFixed(1)}%` : 'N/A';
  const formatFPS = (fps: number | null) => fps !== null ? `${fps.toFixed(1)}` : 'N/A';

  return (
    <div className="bg-white rounded-lg shadow-md p-6">
      <h2 className="text-xl font-semibold text-gray-800 mb-4 flex items-center">
        <span className="mr-2">📊</span>
        Performance Metrics
      </h2>

      <div className="overflow-x-auto">
        <table className="w-full text-sm">
          <thead>
            <tr className="border-b-2 border-gray-200">
              <th className="text-left py-3 px-4 font-semibold text-gray-700">Method</th>
              <th className="text-center py-3 px-4 font-semibold text-gray-700">Threads</th>
              <th className="text-center py-3 px-4 font-semibold text-gray-700">Time</th>
              <th className="text-center py-3 px-4 font-semibold text-gray-700">FPS</th>
              <th className="text-center py-3 px-4 font-semibold text-gray-700">Speedup</th>
              <th className="text-center py-3 px-4 font-semibold text-gray-700">Efficiency</th>
            </tr>
          </thead>
          <tbody>
            {/* Sequential */}
            <tr className="border-b border-gray-100 hover:bg-gray-50">
              <td className="py-3 px-4 font-medium text-gray-800">Sequential</td>
              <td className="py-3 px-4 text-center text-gray-600">1</td>
              <td className="py-3 px-4 text-center font-mono text-gray-800">
                {formatTime(sequential.time)}
              </td>
              <td className="py-3 px-4 text-center text-gray-600">
                {formatFPS(sequential.fps)}
              </td>
              <td className="py-3 px-4 text-center">
                <span className="px-2 py-1 bg-gray-100 text-gray-700 rounded">
                  {formatSpeedup(sequential.speedup)}
                </span>
              </td>
              <td className="py-3 px-4 text-center text-gray-600">
                {formatEfficiency(sequential.efficiency)}
              </td>
            </tr>

            {/* Pthread */}
            <tr className="border-b border-gray-100 hover:bg-blue-50">
              <td className="py-3 px-4 font-medium text-gray-800">Pthread</td>
              <td className="py-3 px-4 text-center text-gray-600">{pthread.threads || 'N/A'}</td>
              <td className="py-3 px-4 text-center font-mono text-gray-800">
                {formatTime(pthread.time)}
              </td>
              <td className="py-3 px-4 text-center text-gray-600">
                {formatFPS(pthread.fps)}
              </td>
              <td className="py-3 px-4 text-center">
                <span className={`px-2 py-1 rounded font-semibold ${
                  pthread.speedup && pthread.speedup > 1 
                    ? 'bg-green-100 text-green-700' 
                    : 'bg-gray-100 text-gray-700'
                }`}>
                  {formatSpeedup(pthread.speedup)}
                </span>
              </td>
              <td className="py-3 px-4 text-center text-gray-600">
                {formatEfficiency(pthread.efficiency)}
              </td>
            </tr>

            {/* OpenMP */}
            <tr className="hover:bg-purple-50">
              <td className="py-3 px-4 font-medium text-gray-800">OpenMP</td>
              <td className="py-3 px-4 text-center text-gray-600">{openmp.threads || 'N/A'}</td>
              <td className="py-3 px-4 text-center font-mono text-gray-800">
                {formatTime(openmp.time)}
              </td>
              <td className="py-3 px-4 text-center text-gray-600">
                {formatFPS(openmp.fps)}
              </td>
              <td className="py-3 px-4 text-center">
                <span className={`px-2 py-1 rounded font-semibold ${
                  openmp.speedup && openmp.speedup > 1 
                    ? 'bg-green-100 text-green-700' 
                    : 'bg-gray-100 text-gray-700'
                }`}>
                  {formatSpeedup(openmp.speedup)}
                </span>
              </td>
              <td className="py-3 px-4 text-center text-gray-600">
                {formatEfficiency(openmp.efficiency)}
              </td>
            </tr>
          </tbody>
        </table>
      </div>

      {/* Best Performance Indicator */}
      <div className="mt-4 p-3 bg-blue-50 rounded-lg">
        <p className="text-sm text-gray-700">
          <span className="font-semibold">🏆 Best Performance:</span>{' '}
          {openmp.speedup && pthread.speedup && openmp.speedup > pthread.speedup 
            ? `OpenMP with ${formatSpeedup(openmp.speedup)} speedup`
            : `Pthread with ${formatSpeedup(pthread.speedup)} speedup`}
        </p>
      </div>
    </div>
  );
};

export default MetricsTable;
