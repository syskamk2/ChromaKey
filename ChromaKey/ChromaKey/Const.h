#ifndef CONST_H
#define CONST_H

#define DEFAULT_WIDTH (320)
#define DEFAULT_HEIGHT (240)

#define DEFAULT_CHANNELS (3)


#define NO_ERROR              (0x00000000)
#define CAMERA_OPEN_ERROR     (0x00000001)
#define CAMERA_CAPTURE_ERROR  (0x00000002)
#define IMG_OPEN_ERROR        (0x00000010)
#define IMG_SPLIT_ERROR       (0x00000020)
#define IMG_MERGE_ERROR       (0x00000040)

#define IMG_MORPH_NUM (1)
#define MAX_RETRY_COUNT (10)
#define RETRY_WAIT_MSEC (200)

#define SHOW_WAIT_MSEC  (150)

#define SAD_BINARYTHRESH (-1)

#define CHANNEL_Cr (2)
#define CHANNEL_Cb (1)
#define CHANNEL_Y (0)

const std::string DEFAULT_WINDOWNAME = "Default";
const std::string CAPTURE_WINDOWNAME = "Capture";
const std::string BACKGROUND_WINDOWNAME = "BackGround";
const std::string CHROMAKEY_WINDOWNAME = "ChromaKey";
const std::string DEBUG_WINDOWNAME = "Debug";
const std::string TRACKBAR_NAME = "Trackbar";
#endif