
// extract_exampleDlg.h : header file
//

#pragma once
#include "opencv2/opencv_modules.hpp"
#include "opencv2/core/ocl.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/core/core.hpp"
#include "xfeatures2d.hpp"
#include "Image_Process_dll.h"
#include "Machine_vision.h"
#include "algorithm"


#pragma once
//using namespace tesseract;
using namespace std;
using namespace cv;

// CextractexampleDlg dialog
class CextractexampleDlg : public CDialog
{
// Construction
public:
	CextractexampleDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXTRACT_EXAMPLE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	
	int								count_ = 0;
	int								minHessian_ = 400;
	double						match_ = 2.0f;
	double						resu;
	char*						img_nme;

	vector<CString>		file_nme;
	CString						err_msg;
	CString						tmp_;
	CButton						btn_sted;
	CButton						btn_fdch;
	CButton						btn_flch;
	CButton						btn_shot;
	CSliderCtrl					fact_sld;
	CSliderCtrl					match_sld;
	CSliderCtrl					focus_sld;
	CComboBox				cam_sel;
	CEdit							info_;
	Rect							set_roi;
	BOOL						st_sgn = FALSE;
	BOOL						func_code = FALSE;
	BOOL						sgn_fun = FALSE;
	BOOL						cam_selsgn = FALSE;
	BOOL						trs_fun = FALSE;

	VideoCapture				capture;
	Mat							cap_frame;
	//
	Mat							tpl_;
	Mat							res_;
	Mat							ori;
	Mat							src;
	//
	SYSTEMTIME				st;
	CString						strDate;

	typedef struct feature_exc
	{
		int							cnt_ = 0;
		int							bias_x = 0;
		int							bias_y = 0;
		double					prs_time = 0;
		double					angle_ = 0.0f;
		Point						center_;
		Mat						out_res;
		Mat						map1;
		Mat						map2;
		Mat						homography;
		BOOL					op_sgn;
		CString					msg_;
		CString					err_msg;
	};
	feature_exc f_exc;

	afx_msg void OnBnClickedstedbtn();
	afx_msg void OnBnClickedfolderchoose();
	afx_msg void OnBnClickedfilechoose();
	afx_msg void OnNMCustomdrawfactSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawmatchSlider2(NMHDR *pNMHDR, LRESULT *pResult);
	void SearchFiles(CString strMusicFolder);
	void disp_image(UINT disp_ID, Mat dsp_img, CWnd* pt);
	void disp_image(UINT disp_ID, Mat dsp_img, CWnd* pt, CRect rect_);
	void perspective_to_maps(const cv::Mat &perspective_mat, const cv::Size &img_size, cv::Mat &map1, cv::Mat &map2);
	virtual void OnOK();
	
	double getRotateAngle(double x1, double y1, double x2, double y2);

	Mat Feature_match(Mat tpl_img, Mat src_img, int factor, const float nn_match_ratio, int i_index, int id_);
	feature_exc Feature_SIFT(Mat tpl_img, Mat src_img, int minHessian, double factor, int tgt_num = 1);

	img_inspect img_insp;
	img_inspect Multi_r_(Mat tpl_img, Mat src_img, Mat ori_img, double valve, int tgt_num, int mode, int min_dist, int angle_, double angle_pre, double scale_m, double scale_pre, cv::Rect roi_, int id_ = 0);
	Point getNextMinLoc(Mat result, Point minLoc, Point maxLoc, double maxVaule, double minValue, int templatW, int templatH, double valve, int mode, int min_dist, int tmp_id = 0);

	afx_msg void OnBnClickedshot();
	afx_msg void OnCbnSelchangecamsel();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnNMCustomdrawfocus(NMHDR *pNMHDR, LRESULT *pResult);
};

class t_ime
{
private:
	int minutes;
	int hours;
public:
	void Time();
	void Time(int h, int m = 0);
	void Reset(int h = 0, int m = 0);
	t_ime &operator+(const t_ime & t);//const;
	void Show() const;
};

template <typename T>
class beta 
{
private:
	template <typename V> // nested template class member
	class hold
	{
		private:
			V val;
		public:
			hold(V v = 0) : val(v) {}
			void show() const { cout << val << endl; }
			V Value() const { return val; }
	};
	hold<T> q; // template object
	hold<int> n; // template object
public:
    beta(T t, int i) : q(t), n(i) {}
	template<typename U> // template method
	U blab(U u, T t) { return (n.Value() + q.Value()) * u / t; }
	void Show() const { q.show(); n.show();}
};