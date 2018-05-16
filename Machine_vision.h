// Machine_vision.h : Machine_vision DLL µÄÖ÷Í·ÎÄ¼ş
//

#pragma once

#ifndef __AFXWIN_H__
	#error "ÔÚ°E¬´ËÎÄ¼şÖ®Ç°°E¬¡°stdafx.h¡±ÒÔÉú³É PCH ÎÄ¼ş"
#endif

#include "resource.h"		// Ö÷·ûºÅ
#include "iostream"
#include "string"
#include "stdio.h"
#include "afxwin.h"
#include "stdlib.h"
#include "sstream"
#include "math.h"
#include "vector"

// CMachine_visionApp
// ÓĞ¹Ø´ËÀàÊµÏÖµÄĞÅÏ¢£¬ÇEÎÔÄ Machine_vision.cpp
//

class CMachine_visionApp : public CWinApp
{
public:
	CMachine_visionApp();

// ÖØĞ´
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

struct img_inspect
{
	cv::Mat out_img[10];
	cv::Mat tmp_res[10];
	cv::Point out_loc[10];
	BOOL op_stat[10];
	BOOL multi_sgn;
	BOOL inspect_stat[10];
	CString rmks_;
	CString out_text;
	CString err_msg_[50];
	CString fn_res[100];
	CString trs_mess[100];
	int cur_tplcnt[10];
	int err_cnt[10];
	int b_value;
	int g_value;
	int r_value;
	int iLowB;
	int iLowG;
	int iLowR;
	int iHighB;
	int iHighG;
	int iHighR;
	int mmn = 0;
	int fn_cnt_[10];
	int cr_factor;
	int contour_sz[100];
	double valve[10];
	double angle_[10];
	double resu_[10];
	double cur_scale[10];
	double prs_time[10];
	//std::vector<int> contour_sz;
};

img_inspect Grysc_template(cv::Mat tpl_img, cv::Mat src_img, double valve, int id_ = 0);

img_inspect Grysc_template_(cv::Mat tpl_img, cv::Mat src_img, cv::Mat ori_img, double valve, int mode, int id_ = 0);

img_inspect Grysc_template_r(cv::Mat tpl_img, cv::Mat src_img, cv::Mat ori_img, double valve, int mode, cv::Rect roi_, int id_ = 0);

img_inspect _Grysc_template(cv::Mat tpl_img, cv::Mat src_img, double valve, int mode, int id_ = 0);

img_inspect Rotation_based(cv::Mat tpl_img, cv::Mat src_img, double bd_ang, double valve, int id_ = 0);

img_inspect Multi_targetbased(cv::Mat tpl_img, cv::Mat src_img, double valve, int tgt_num, int mode, int id_ = 0);

img_inspect Multi_targetbased_(cv::Mat tpl_img, cv::Mat src_img, cv::Mat ori_img, double valve, int tgt_num, int mode, int min_dist, int id_ = 0);

img_inspect Multi_r(cv::Mat tpl_img, cv::Mat src_img, cv::Mat ori_img, double valve, int tgt_num, int mode, int min_dist, cv::Rect roi_, int id_ = 0);

img_inspect Multi_r_(cv::Mat tpl_img, cv::Mat src_img, cv::Mat ori_img, double valve, int tgt_num, int mode, int min_dist, int angle_, double angle_pre, double scale_m, double scale_pre, cv::Rect roi_, int id_ = 0);

img_inspect Scale_based(cv::Mat tpl_img, cv::Mat src_img, double scale_, double valve, int id_ = 0);

cv::Point getNextMinLoc(cv::Mat result, cv::Point minLoc, cv::Point maxLoc, double maxVaule, double minValue, int templatW, int templatH, double valve, int mode, int min_dist, int tmp_id = 0);

img_inspect Color_parameter(cv::Mat in_img, cv::Rect ins_rect, int factor, int id_ = 0);

img_inspect Color_inspect(cv::Mat in_img, int b_val_a, int g_val_a, int r_val_a, int factor, int id_ = 0);

img_inspect OCR_extract(cv::Mat in_img, const char* lang_op, int id_ = 0);

img_inspect Feature_match(cv::Mat tpl_img, cv::Mat src_img, int factor, const float nn_match_ratio, int i_index, int id_ = 0);

img_inspect Cr_inspect_(cv::Mat src_img, cv::Vec<int, 3> tgt_color, int dist, int pro_num, int ctr_min, int ctr_max, cv::Rect ins_rect, int id_ = 0);

img_inspect getSizeContours(std::vector<std::vector<cv::Point>> &contours, cv::Mat in_img, int cmin, int cmax, cv::Rect ins_rect, int id_ = 0);