import React from 'react';
import { BarChart, Bar, XAxis, YAxis, CartesianGrid, Tooltip, Legend, ResponsiveContainer, LineChart, Line } from 'recharts';
import { Metrics } from '../services/api';

interface PerformanceChartProps {
  sequential: Metrics;
  pthread: Metrics;
  openmp: Metrics;
}

const PerformanceChart: React.FC<PerformanceChartProps> = ({ sequential, pthread, openmp }) => {
  const timeData = [
    {
      name: 'Sequential',
      time: sequential.time || 0,
      threads: 1,
    },
    {
      name: 'Pthread',
      time: pthread.time || 0,
      threads: pthread.threads || 0,
    },
    {
      name: 'OpenMP',
      time: openmp.time || 0,
      threads: openmp.threads || 0,
    },
  ];

  const speedupData = [
    {
      name: 'Sequential',
      speedup: sequential.speedup || 1,
      efficiency: sequential.efficiency || 100,
    },
    {
      name: 'Pthread',
      speedup: pthread.speedup || 0,
      efficiency: pthread.efficiency || 0,
    },
    {
      name: 'OpenMP',
      speedup: openmp.speedup || 0,
      efficiency: openmp.efficiency || 0,
    },
  ];

  return (
    <div className="bg-white rounded-lg shadow-md p-6">
      <h2 className="text-xl font-semibold text-gray-800 mb-4 flex items-center">
        <span className="mr-2">📈</span>
        Performance Visualization
      </h2>

      <div className="grid grid-cols-1 lg:grid-cols-2 gap-6">
        {/* Execution Time Chart */}
        <div>
          <h3 className="text-sm font-semibold text-gray-700 mb-3 text-center">
            Execution Time Comparison
          </h3>
          <ResponsiveContainer width="100%" height={250}>
            <BarChart data={timeData}>
              <CartesianGrid strokeDasharray="3 3" />
              <XAxis dataKey="name" />
              <YAxis label={{ value: 'Time (seconds)', angle: -90, position: 'insideLeft' }} />
              <Tooltip />
              <Legend />
              <Bar dataKey="time" fill="#3b82f6" name="Execution Time (s)" />
            </BarChart>
          </ResponsiveContainer>
        </div>

        {/* Speedup Chart */}
        <div>
          <h3 className="text-sm font-semibold text-gray-700 mb-3 text-center">
            Speedup & Efficiency
          </h3>
          <ResponsiveContainer width="100%" height={250}>
            <LineChart data={speedupData}>
              <CartesianGrid strokeDasharray="3 3" />
              <XAxis dataKey="name" />
              <YAxis 
                yAxisId="left"
                label={{ value: 'Speedup (x)', angle: -90, position: 'insideLeft' }}
              />
              <YAxis 
                yAxisId="right"
                orientation="right"
                label={{ value: 'Efficiency (%)', angle: 90, position: 'insideRight' }}
              />
              <Tooltip />
              <Legend />
              <Line 
                yAxisId="left"
                type="monotone" 
                dataKey="speedup" 
                stroke="#10b981" 
                strokeWidth={2}
                name="Speedup"
                dot={{ r: 5 }}
              />
              <Line 
                yAxisId="right"
                type="monotone" 
                dataKey="efficiency" 
                stroke="#8b5cf6" 
                strokeWidth={2}
                name="Efficiency (%)"
                dot={{ r: 5 }}
              />
            </LineChart>
          </ResponsiveContainer>
        </div>
      </div>

      {/* Summary Statistics */}
      <div className="mt-6 grid grid-cols-1 md:grid-cols-3 gap-4">
        <div className="bg-gradient-to-br from-blue-50 to-blue-100 p-4 rounded-lg">
          <div className="text-xs font-semibold text-blue-600 uppercase mb-1">Max Speedup</div>
          <div className="text-2xl font-bold text-blue-900">
            {Math.max(pthread.speedup || 0, openmp.speedup || 0).toFixed(2)}x
          </div>
        </div>
        <div className="bg-gradient-to-br from-green-50 to-green-100 p-4 rounded-lg">
          <div className="text-xs font-semibold text-green-600 uppercase mb-1">Time Saved</div>
          <div className="text-2xl font-bold text-green-900">
            {sequential.time && openmp.time 
              ? `${(sequential.time - openmp.time).toFixed(2)}s`
              : 'N/A'}
          </div>
        </div>
        <div className="bg-gradient-to-br from-purple-50 to-purple-100 p-4 rounded-lg">
          <div className="text-xs font-semibold text-purple-600 uppercase mb-1">Best Efficiency</div>
          <div className="text-2xl font-bold text-purple-900">
            {Math.max(pthread.efficiency || 0, openmp.efficiency || 0).toFixed(1)}%
          </div>
        </div>
      </div>
    </div>
  );
};

export default PerformanceChart;
