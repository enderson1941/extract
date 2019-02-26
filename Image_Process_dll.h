// Image_Process_dll.h : Image_Process_dll DLL µÄÖ÷Í·ÎÄ¼ş
//

#pragma once

#ifndef __AFXWIN_H__
	#error "ÔÚ°E¬´ËÎÄ¼şÖ®Ç°°E¬¡°stdafx.h¡±ÒÔÉú³É PCH ÎÄ¼ş"
#endif

#include "resource.h"		// Ö÷·ûºÅ
#include "CvvImage.h"
#include "iostream"
#include "string"
#include "stdio.h"
#include "stdlib.h"
#include "sstream"
#include "math.h"
#include "vector"
#include "opencv2\stitching\detail\exposure_compensate.hpp"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include "opencv2\imgcodecs.hpp"
#include "opencv2\core/core.hpp"
//#include "opencv2\contrib\contrib.hpp"

using namespace cv;
using namespace std;
using namespace detail;

// CImage_Process_dllApp
// ÓĞ¹Ø´ËÀàÊµÏÖµÄĞÅÏ¢£¬ÇEÎÔÄ Image_Process_dll.cpp
//

class CImage_Process_dllApp : public CWinApp
{
public:
	CImage_Process_dllApp();

// ÖØĞ´
public:
	virtual BOOL InitInstance();
	DECLARE_MESSAGE_MAP()
private:
};

struct img_pro
{
	Mat out_img[10];
	BOOL op_stat;
	CString file_name;
	CString out_data;
	char* chr_flenme;
};
//img_pro img_pro_srt;

img_pro Sharp_image(Mat in_img);

img_pro Normalize_image(Mat in_img);

img_pro Threshold_image_(Mat in_img, int mode, double thres_min, double thres_max);

img_pro Filter_image(Mat in_img, int mode, int valve);

img_pro Contrast_brightness(Mat in_img, double con_value, int bri_value);

img_pro Histogram_Eq(Mat in_img);

img_pro dilate_erode(Mat in_img, int mode_, int pro_value);

img_pro pre_process_(Mat in_img, int id_ = 0);

//dir 0_clock 1_anti
img_pro On_Rotation_(Mat in_img, int rot_dir, int mode_, double ang, int id_ = 0);

img_pro Image_crop(Mat in_img, Rect roi_);

img_pro Image_Stitch(int mode_, Mat op_img1, Mat op_img2);

img_pro Angle_calc(vector<cv::Point> pointVect);

Mat cr_process(Mat image); //main process

cv::Vec3b getTargetColor();

void setTargetColor_(cv::Vec3b color);

void setTargetColor(unsigned char red, unsigned char green, unsigned char blue);

int getColorDistanceThreshold();

void setColorDistanceThreshold(int distance);

Vec2i gettarget_grayvalue(Mat in_image, Rect in_rect);

int camera_retrive(int max_cam);

//img_pro Dir_Traverse(char* tmp_dir_nme, char* ext_);


