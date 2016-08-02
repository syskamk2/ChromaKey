#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>

#include "Const.h"
#include "ImageCtrl.h"
using namespace std;

int openWindow(const string windowName)
{
  cv::namedWindow(windowName, CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
  return NO_ERROR;
}

int showNoWait(const std::string windowName, const cv::Mat& mat)
{
  cv::imshow(windowName, mat);
  return NO_ERROR;
}

int showAndGetKey(const std::string windowName, const cv::Mat& mat, const int wait)
{
  showNoWait(windowName, mat);
  return cv::waitKey(wait);
}

int openImgFile(const std::string fileName, cv::Mat& mat)
{
  int ret = NO_ERROR;
  mat = cv::imread(fileName);
  if (mat.data == NULL)
  {
    ret = IMG_OPEN_ERROR;
  }
  return ret;
}

