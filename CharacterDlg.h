
// CharacterDlg.h : header file
//
#include "opencv2/stitching/detail/exposure_compensate.hpp"
#include "opencv2/opencv_modules.hpp"
#include "opencv2/core/ocl.hpp"
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/features2d.hpp>
#include <opencv2/imgcodecs.hpp>
#include "opencv2/core/core.hpp"

#pragma once
//using namespace tesseract;
using namespace std;
using namespace cv;

// CCharacterDlg dialog
class CCharacterDlg : public CDHtmlDialog
{
// Construction
public:
	CCharacterDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHARACTER_DIALOG, IDH = IDR_HTML_CHARACTER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);

// Implementation
protected:
	HICON m_hIcon;
	double resu;
	CString err_msg;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
public:
	afx_msg void OnStnClickedframe();

	Mat Feature_match(Mat tpl_img, Mat src_img, int factor, const float nn_match_ratio, int i_index, int id_);
	void disp_image(UINT disp_ID, Mat dsp_img, CWnd* pt);
	void disp_image(UINT disp_ID, Mat dsp_img, CWnd* pt, CRect rect_);
	afx_msg void OnBnClickedbtn3();
	afx_msg void OnBnClickedbtn4();
};
