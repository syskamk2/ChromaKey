#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <string>
#include <vector>

#include "Const.h"
#include "VideoCtrl.h"
#include "ImageCtrl.h"
#include "ImageProc.h"

int chromakeyProc(cv::VideoCapture& cap, const cv::Mat& bg, const cv::Mat& vbg)
{
  int ret = NO_ERROR;
  const int width = bg.cols;
  const int height = bg.rows;
  cv::Mat frame;
  cv::Mat frameSplit;
  cv::Mat frameHSV;
  cv::Mat bgHSV;
  cv::Mat bgSplit[DEFAULT_CHANNELS];
  cv::Mat maskImg(height, width, CV_8UC1);
  cv::Mat maskImgs[DEFAULT_CHANNELS];
  cv::Mat maskImg3ch;
  cv::Mat maskImg3chInv;
  cv::Mat vbgMask;
  cv::Mat frameMask;
  cv::Mat diff[DEFAULT_CHANNELS];
  cv::Mat chrom;

  int binThresh = 2;
  openTrackBar(TRACKBAR_NAME, binThresh);

  cv::cvtColor(bg, bgHSV, CV_BGR2YCrCb);
  //背景画像のチャンネル分解
  for (int i = 0; i < DEFAULT_CHANNELS; ++i)
  {
    takeNthChannel(bgHSV, bgSplit[i], i);
  }
  char c = '\0';
  //カメラからの入力をクロマキー合成
  while ((ret = cameraCapture(cap, frame)) == NO_ERROR && c != 'c')
  {
    maskImg = cv::Mat::zeros(cv::Size(width, height), CV_8UC1);
    cv::cvtColor(frame, frameHSV, CV_BGR2YCrCb);
    
    int useChannel = CHANNEL_Y;
    
    takeNthChannel(frameHSV, frameSplit, useChannel);
    makeDiffImg(frameSplit, bgSplit[useChannel], diff[useChannel], binThresh);
    cv::bitwise_or(maskImg, diff[useChannel], maskImg);
    
    for (int i = 0; i < DEFAULT_CHANNELS; ++i)
    {
      maskImgs[i] = maskImg;
    }
    mergeNthChannel(maskImgs, maskImg3ch);

    cv::morphologyEx(maskImg3ch, maskImg3ch, cv::MORPH_OPEN,
                     cv::Mat(), cv::Point(-1, -1), IMG_MORPH_NUM);
    cv::medianBlur(maskImg3ch, maskImg3ch, 5);

    //仮想背景用マスク
    cv::bitwise_not(maskImg3ch, maskImg3chInv);
    cv::bitwise_and(maskImg3chInv, vbg, vbgMask);
    //前景
    cv::bitwise_and(maskImg3ch, frame, frameMask);
    
    //合成
    cv::bitwise_or(vbgMask, frameMask, chrom);

    //表示
    showNoWait(CAPTURE_WINDOWNAME, diff[useChannel]);//frame
    showNoWait(DEBUG_WINDOWNAME, maskImg3ch);//maskImg3ch
    c = showAndGetKey(CHROMAKEY_WINDOWNAME, chrom);//chrom
  }

  return ret;
}

int mergeNthChannel(const cv::Mat src[], cv::Mat& dst, int n)
{
  int ret = NO_ERROR;

  std::vector<cv::Mat> chs;
  for (int i = 0; i < n; ++i)
  {
    if (&src[i] == NULL || src[i].data == NULL)
    {
      ret = IMG_MERGE_ERROR;
      break;
    }
    chs.push_back(src[i]);
  }
  if (ret == NO_ERROR)
  {
      cv::merge(chs, dst);
  }
  
  return ret;
}

int takeNthChannel(const cv::Mat&src, cv::Mat& dst, const int n)
{
  int ret = NO_ERROR;

  std::vector<cv::Mat> chs;
  cv::split(src, chs);
  
  if (n >= 0 && n < src.channels())
  {
    dst = chs[n];
  }
  else
  {
    ret |= IMG_SPLIT_ERROR;
  }
  return ret;
}
//src1, src2 and dst must be 1ch
static int makeDiffImg(const cv::Mat& src1, const cv::Mat& src2, cv::Mat& dst, const int thresh)
{
  cv::Mat sad = cv::abs(src1 - src2);
  
  if (thresh <= 0)
  {
    cv::threshold(sad, dst, 0, UCHAR_MAX, cv::THRESH_BINARY | cv::THRESH_OTSU);
  }
  else
  {
    cv::threshold(sad, dst, thresh, UCHAR_MAX, cv::THRESH_BINARY);
  }
  return NO_ERROR;
}

int forceResize(const int width, const int height, cv::Mat& mat)
{
  cv::resize(mat, mat, cv::Size(width, height));
  return NO_ERROR;
}

int makeGray(cv::Mat& src, cv::Mat& dst)
{
  cv::cvtColor(src, dst, cv::COLOR_BGR2GRAY);
  return NO_ERROR;
}

