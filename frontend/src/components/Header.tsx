import React from 'react';

const Header: React.FC = () => {
  return (
    <header className="bg-gradient-to-r from-blue-600 to-purple-600 text-white shadow-lg">
      <div className="container mx-auto px-6 py-6">
        <div className="flex items-center justify-between">
          <div className="flex items-center space-x-4">
            <div className="text-4xl">🎥</div>
            <div>
              <h1 className="text-3xl font-bold">Parallel Video Processing</h1>
              <p className="text-blue-100 text-sm mt-1">
                Compare Sequential, Pthread, and OpenMP implementations
              </p>
            </div>
          </div>
          <div className="hidden md:flex items-center space-x-4">
            <div className="bg-white/20 px-4 py-2 rounded-lg backdrop-blur-sm">
              <span className="text-xs font-semibold">12 Features</span>
            </div>
            <div className="bg-white/20 px-4 py-2 rounded-lg backdrop-blur-sm">
              <span className="text-xs font-semibold">Real-time Processing</span>
            </div>
          </div>
        </div>
      </div>
    </header>
  );
};

export default Header;
