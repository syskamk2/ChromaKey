#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "Const.h"
#include "ImageCtrl.h"
#include "VideoCtrl.h"

int cameraOpen(cv::VideoCapture& cap, const int width, const int height)
{
  int ret = NO_ERROR;

  // �ݒ肵�Ă����f����Ă��Ȃ����������璍��
  cap.set(CV_CAP_PROP_FRAME_WIDTH, width);
  cap.set(CV_CAP_PROP_FRAME_HEIGHT, height);
  cap.set(CV_CAP_PROP_FORMAT, CV_8UC3);
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
  if (!cap.isOpened())
  {
    ret = CAMERA_OPEN_ERROR;
  }
  mat.data = NULL;
  int retry = 0;
  cap >> mat;
  //�J�����̏����o���Ă��Ȃ�����
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