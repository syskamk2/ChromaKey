#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "Const.h"
#include "ImageCtrl.h"
#include "VideoCtrl.h"

int cameraOpen(cv::VideoCapture& cap, const int width, const int height)
{
  int ret = NO_ERROR;

  // 設定しても反映されていないかもだから注意
  cap.set(CV_CAP_PROP_FRAME_WIDTH, width);
  cap.set(CV_CAP_PROP_FRAME_HEIGHT, height);
  cap.set(CV_CAP_PROP_FORMAT, CV_8UC3);
  // カメラがオープンできたかの確認
  if (!cap.isOpened())
  {
    ret = CAMERA_OPEN_ERROR;
  }

  return ret;
}

int cameraCapture(cv::VideoCapture& cap, cv::Mat& mat)
{
  int ret = NO_ERROR;
  if (!cap.isOpened())
  {
    ret = CAMERA_OPEN_ERROR;
  }
  mat.data = NULL;
  int retry = 0;
  cap >> mat;
  //カメラの準備出来ていないかも
  while (mat.data == NULL && retry < MAX_RETRY_COUNT)
  {
    cap >> mat;
    cv::waitKey(RETRY_WAIT_MSEC);
    retry++;
    std::cerr << "waiting a camera" << std::endl;
  }
  if (mat.data == NULL)
  {
    ret += CAMERA_CAPTURE_ERROR;
  }

  return ret;
}

int cameraTakePhoto(cv::VideoCapture& cap, cv::Mat& mat, std::string windowName)
{
  int ret = NO_ERROR;
  char c = '\0';
  while ((ret = cameraCapture(cap, mat)) == NO_ERROR)
  {
    c = showAndGetKey(windowName, mat);
    
    if (c == 'c')
    {
      break;
    }
  }
  return ret;
}