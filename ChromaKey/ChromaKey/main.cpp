#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>

#include "Const.h"
#include "VideoCtrl.h"
#include "ViewCtrl.h"
int main()
{
  cv::VideoCapture cap(0);
  int err = cameraOpen(cap);
  if (err != NO_ERROR)
  {
    return err;
  }
  err = openWindow();
  if (err != NO_ERROR)
  {
    return err;
  }

  cv::Mat backGround(DEFAULT_HEIGHT, DEFAULT_WIDTH, CV_8UC3);
  cameraTakePhoto(cap, backGround);

  return 0;
}

