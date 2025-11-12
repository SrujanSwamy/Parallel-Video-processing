# Frontend - Parallel Video Processing Dashboard

React + TypeScript frontend for the Parallel Video Processing project.

## Features

- 📤 **Video Upload** with drag-and-drop support
- ⚙️ **Configuration Panel** for feature selection and thread count
- ⚡ **Real-time Progress** tracking with WebSocket
- 📺 **Video Comparison** grid (4 videos side-by-side)
- 📊 **Performance Metrics** table with speedup calculations
- 📈 **Interactive Charts** for performance visualization
- 🎨 **Modern UI** with Tailwind CSS
- 📱 **Responsive Design** for desktop and tablets

## Installation

1. Install Node.js dependencies:
```bash
cd frontend
npm install
```

## Running the Application

### Development Mode

```bash
npm start
```

Open [http://localhost:3000](http://localhost:3000) to view in the browser.

### Production Build

```bash
npm run build
```

Builds the app for production to the `build` folder.

## Environment Variables

Create a `.env` file in the frontend directory:

```
REACT_APP_API_URL=http://localhost:5000/api
```

## Available Scripts

- `npm start` - Runs the app in development mode
- `npm build` - Builds the app for production
- `npm test` - Runs tests
- `npm eject` - Ejects from Create React App (irreversible)

## Project Structure

```
frontend/
├── public/
│   └── index.html
├── src/
│   ├── components/
│   │   ├── Header.tsx
│   │   ├── UploadSection.tsx
│   │   ├── ConfigPanel.tsx
│   │   ├── ProgressBar.tsx
│   │   ├── VideoPlayer.tsx
│   │   ├── VideoComparison.tsx
│   │   ├── MetricsTable.tsx
│   │   └── PerformanceChart.tsx
│   ├── services/
│   │   └── api.ts
│   ├── App.tsx
│   ├── index.tsx
│   └── index.css
├── package.json
├── tsconfig.json
├── tailwind.config.js
└── postcss.config.js
```

## Technologies Used

- **React 18** - UI library
- **TypeScript** - Type safety
- **Tailwind CSS** - Styling
- **Axios** - HTTP client
- **Socket.IO Client** - Real-time communication
- **Recharts** - Data visualization

## API Integration

The frontend communicates with the Flask backend API:

- Upload videos
- Process videos with selected feature
- Receive real-time progress updates via WebSocket
- Display results and metrics

## Browser Support

- Chrome (recommended)
- Firefox
- Edge
- Safari

## Troubleshooting

### CORS Issues
Make sure the backend Flask server has CORS enabled and is running on `http://localhost:5000`.

### WebSocket Connection Failed
Check that the Flask-SocketIO server is running and accessible.

### Video Playback Issues
Ensure videos are in supported formats (MP4, AVI, MOV).
