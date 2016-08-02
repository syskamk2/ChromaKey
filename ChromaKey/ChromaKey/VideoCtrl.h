#ifndef VIDEO_CTRL_H
#define VIDEO_CTRL_H

#define CAMERA_OPEN_ERROR (-1)
#define CAMERA_CAPTURE_ERROR (-2)

int cameraOpen(cv::VideoCapture& cap, 
               const int width = DEFAULT_WIDTH, 
               const int height = DEFAULT_HEIGHT);

int cameraCapture(cv::VideoCapture& cap, cv::Mat& mat);

int cameraTakePhoto(cv::VideoCapture& cap, cv::Mat& mat);
#endif