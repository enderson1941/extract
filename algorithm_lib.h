#pragma once
#include "stdafx.h"

//namespace
using namespace std;
using namespace cv;
using namespace aruco;

//struct
struct posi_paramter
{
	BOOL					op_sgn = FALSE;
	BOOL					init_sgn = FALSE;
	Mat						R_t;
	Mat						tmp_;
	Mat						res_img;
	Point						r_points[4];
	FileStorage			fs;
	vector<Vec3d>		rvecs, tvecs;
	CString					tmp_msg;
};

struct calib_paramter
{
	int										calibrationFlags = 0;
	int										frame_id = 0;//
	int										frame_cnt = 50;//
	int										dictionaryId = 8;
	float									aspectRatio = 1;
	float									squareLength = 40;
	float									markerLength = 30;
	bool									refindStrategy = false;
	bool									calibed = true;
	string								camera_index;//
	CvSize								calib_board = CvSize(5, 7);

	// collect data from each frame
	vector<vector<int>>			allIds;
	vector<Mat>						allImgs;
	Mat									calib_img;
	Mat									res_img;
	VideoCapture						cam_cap;
	Size									imgSize;
	Mat									cameraMatrix, distCoeffs;
	Mat									currentCharucoCorners, currentCharucoIds;
	vector<int>						markerIds;
	vector<vector<Point2f>>	markerCorners, rejectedCandidates;
	vector<vector<vector<Point2f>>>		allCorners;
	Ptr<aruco::Dictionary>						calib_dict;
	Ptr<aruco::DetectorParameters>		detectorParams;
	Ptr<aruco::CharucoBoard>				charucoboard;

	//estimate
	Mat									rvecs, tvecs;
	Mat									Hw, Vw;
	Mat									tmp;

	// system
	BOOL								op_sgn = FALSE;//
	BOOL								init_sgn = FALSE;//
	BOOL								calib_sgn = FALSE;//
	string								outputFile = "..\\default_camera.xml";//
	CString								wrn_msg[4];//
};

//function

calib_paramter camera_calib_init(string& cam_index, int& frame_cnt, CvSize& calib_board, float& marker_length, float& square_length);

calib_paramter camera_calib(Mat calib_frame);

BOOL detect_markers_(Mat in_img, int mode_ = 0, int cam_id = 0);

BOOL readDetectorParameters(string detect_param, cv::Ptr<DetectorParameters> &params);

BOOL calib_calculate();

BOOL saveCameraParams(const string &filename, Size imageSize, float aspectRatio, int flags, const Mat &cameraMatrix, const Mat &distCoeffs, double totalAvgErr);

posi_paramter posi_detect_init(Mat top_img, Mat scan_img);

posi_paramter posi_detect(Mat in_img, Mat inspect_img = Mat(1280, 720, CV_32FC1, Scalar(255)), BOOL save_op = FALSE);

//