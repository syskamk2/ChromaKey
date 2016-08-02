#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>

using namespace std;

int openWindow(const string windowName)
{
  cv::namedWindow(windowName, CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
  return 0;
}