#ifndef VIDEO_CTRL_H
#define VIDEO_CTRL_H

int cameraOpen(cv::VideoCapture& cap, 
               const int width = DEFAULT_WIDTH, 
               const int height = DEFAULT_HEIGHT);

int cameraCapture(cv::VideoCapture& cap, cv::Mat& mat);

int cameraTakePhoto(cv::VideoCapture& cap, cv::Mat& mat,
                    std::string windowName = DEFAULT_WINDOWNAME);
#endif