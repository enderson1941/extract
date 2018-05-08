
// extract_exampleDlg.h : header file
//

#pragma once
#include <vector>
#include "opencv2/stitching/detail/exposure_compensate.hpp"
#include "opencv2/opencv_modules.hpp"
#include "opencv2/core/ocl.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/core/core.hpp"
#include "xfeatures2d.hpp"
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
	
	int		count_ = 0;
	int		minHessian_ = 400;
	double	match_ = 2.0f;
	double	resu;
	char*	img_nme;

	vector<CString> file_nme;
	CString err_msg;
	CString tmp_;
	CButton btn_sted;
	CButton btn_fdch;
	CButton btn_flch;
	CButton btn_shot;
	CSliderCtrl fact_sld;
	CSliderCtrl match_sld;
	CSliderCtrl focus_sld;
	CComboBox	cam_sel;
	CEdit	info_;
	BOOL	st_sgn = FALSE;
	BOOL	func_code = FALSE;
	BOOL	sgn_fun = FALSE;
	BOOL	cam_selsgn = FALSE;

	VideoCapture capture;
	Mat		cap_frame;
	//
	Mat		tpl_;
	Mat		res_;
	Mat		src;

	typedef struct feature_exc
	{
		int		cnt_ = 0;
		double	prs_time = 0;

		Mat		out_res;
		BOOL	op_sgn;
		CString msg_;
		CString err_msg;

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
	virtual void OnOK();

	Mat Feature_match(Mat tpl_img, Mat src_img, int factor, const float nn_match_ratio, int i_index, int id_);
	feature_exc Feature_SIFT(Mat tpl_img, Mat src_img, int minHessian, double factor);

	afx_msg void OnBnClickedshot();
	afx_msg void OnCbnSelchangecamsel();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnNMCustomdrawfocus(NMHDR *pNMHDR, LRESULT *pResult);
};


