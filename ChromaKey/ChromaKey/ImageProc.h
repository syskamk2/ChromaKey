#ifndef IMAGE_PROC_H
#define IMAGE_PROC_H

int chromakeyProc(cv::VideoCapture& cap, const cv::Mat& bg, const cv::Mat& vbg);
int forceResize(const int width, const int height, cv::Mat& mat);
int makeGray(cv::Mat& src, cv::Mat& dst);
int takeNthChannel(const cv::Mat&src, cv::Mat& dst, const int n = 0);
int mergeNthChannel(const cv::Mat src[], cv::Mat& dst, const int n = DEFAULT_CHANNELS);
int makeDiffImg(const cv::Mat& src1, const cv::Mat& src2, cv::Mat& dst, const int thresh = SAD_BINARYTHRESH);
#endif