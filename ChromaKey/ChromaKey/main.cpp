#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>

#include "Const.h"
#include "VideoCtrl.h"
#include "ImageCtrl.h"
#include "ImageProc.h"

const std::string VIRTUALBACKGROUND_FILEPATH = "./vBackGround.jpg";

int main()
{
  //�J�����p��
  cv::VideoCapture cap(0);
  unsigned int err = cameraOpen(cap);
  if (err != NO_ERROR)
  {
    return err;
  }
  //�\���p��
  err |= openWindow(CHROMAKEY_WINDOWNAME);
  err |= openWindow(CAPTURE_WINDOWNAME);
  err |= openWindow(BACKGROUND_WINDOWNAME);
  if (err != NO_ERROR)
  {
    return err;
  }
  //�w�i�擾
  const int width = static_cast<int>(cap.get(CV_CAP_PROP_FRAME_WIDTH));
  const int height = static_cast<int>(cap.get(CV_CAP_PROP_FRAME_HEIGHT));
  cv::Mat backGround(height, width, CV_8UC3);
  err |= cameraTakePhoto(cap, backGround, BACKGROUND_WINDOWNAME);

  //�����p�w�i�擾
  cv::Mat vBackGround;
  err |= openImgFile(VIRTUALBACKGROUND_FILEPATH, vBackGround);
  err |= forceResize(width, height, vBackGround);
  
  //�N���}�L�[����
  err |= chromakeyProc(cap, backGround, vBackGround);

  return err;
}

