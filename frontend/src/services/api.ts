import axios from 'axios';

const API_BASE_URL = process.env.REACT_APP_API_URL || 'http://localhost:5000/api';

const api = axios.create({
  baseURL: API_BASE_URL,
  headers: {
    'Content-Type': 'application/json',
  },
});

export interface VideoInfo {
  width: number;
  height: number;
  fps: number;
  frame_count: number;
  duration: number;
}

export interface UploadResponse {
  job_id: string;
  filename: string;
  size: number;
  video_info: VideoInfo;
}

export interface Feature {
  id: string;
  name: string;
}

export interface ProcessRequest {
  job_id: string;
  feature: string;
  openmp_threads: number;
  pthread_threads: number;
}

export interface Metrics {
  time: number | null;
  fps: number | null;
  frames: number | null;
  speedup: number | null;
  efficiency: number | null;
  threads?: number;
}

export interface PerformanceSummary {
  sequential: Metrics;
  pthread: Metrics;
  openmp: Metrics;
}

export interface ResultsResponse {
  status: string;
  progress?: number;
  message?: string;
  error?: string | null;
  is_scene_detection?: boolean;
  metrics: PerformanceSummary;
  videos?: {
    input: string | null;
    sequential: string | null;
    pthread: string | null;
    openmp: string | null;
  };
  scene_results?: {
    sequential: string | null;
    pthread: string | null;
    openmp: string | null;
  };
  raw_metrics?: any;
}

export interface JobStatus {
  status: string;
  progress?: number;
  message?: string;
  error?: string | null;
}

// API methods
export const uploadVideo = async (file: File): Promise<UploadResponse> => {
  const formData = new FormData();
  formData.append('video', file);

  const response = await api.post<UploadResponse>('/upload', formData, {
    headers: {
      'Content-Type': 'multipart/form-data',
    },
  });

  return response.data;
};

export const getFeatures = async (): Promise<Feature[]> => {
  const response = await api.get<{ features: Feature[] }>('/features');
  return response.data.features;
};

export const processVideo = async (data: ProcessRequest): Promise<{ job_id: string; status: string; message: string }> => {
  const response = await api.post('/process', data);
  return response.data;
};

export const getJobStatus = async (jobId: string): Promise<JobStatus> => {
  const response = await api.get<JobStatus>(`/status/${jobId}`);
  return response.data;
};

export const getResults = async (jobId: string): Promise<ResultsResponse> => {
  const response = await api.get<ResultsResponse>(`/results/${jobId}`);
  return response.data;
};

export const getVideoUrl = (jobId: string, videoType: 'input' | 'sequential' | 'pthread' | 'openmp'): string => {
  return `${API_BASE_URL}/video/${jobId}/${videoType}`;
};

export interface SceneDetectionResult {
  content: string;
  type: string;
}

export const getSceneDetectionResult = async (jobId: string, sceneType: 'sequential' | 'pthread' | 'openmp'): Promise<SceneDetectionResult> => {
  const response = await api.get<SceneDetectionResult>(`/scene/${jobId}/${sceneType}`);
  return response.data;
};

export const cleanupJob = async (jobId: string): Promise<void> => {
  await api.delete(`/cleanup/${jobId}`);
};

export default api;
