#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "Const.h"
#include "VideoCtrl.h"

int cameraOpen(cv::VideoCapture& cap, const int width, const int height)
{
  int ret = NO_ERROR;

  // �ݒ肵�Ă����f����Ă��Ȃ����������璍��
  cap.set(CV_CAP_PROP_FRAME_WIDTH, width);
  cap.set(CV_CAP_PROP_FRAME_HEIGHT, height);
  // �J�������I�[�v���ł������̊m�F
  if (!cap.isOpened())
  {
    ret = CAMERA_OPEN_ERROR;
  }

  return ret;
}

int cameraCapture(cv::VideoCapture& cap, cv::Mat& mat)
{
  int ret = NO_ERROR;
  cap >> mat;
  if (mat.data == NULL)
  {
    ret = CAMERA_CAPTURE_ERROR;
  }
  return ret;
}

int cameraTakePhoto(cv::VideoCapture& cap, cv::Mat& mat)
{
  int ret = NO_ERROR;
  char c = '\0';
  while ((ret = cameraCapture(cap, mat)) == NO_ERROR)
  {
    cv::imshow(DEFAULT_WINDOWNAME, mat);
    c = cv::waitKey(1000);
    if (c == 'c')
    {
      break;
    }
  }
  return ret;
}