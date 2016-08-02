#ifndef VIEW_CTRL_H
#define VIEW_CTRL_H

int openWindow(const std::string windowName = DEFAULT_WINDOWNAME);
int showNoWait(const std::string windowName, const cv::Mat& mat);
int showAndGetKey(const std::string windowName, const cv::Mat& mat, const int wait = SHOW_WAIT_MSEC);
int openImgFile(const std::string fileName, cv::Mat& mat);


#endif