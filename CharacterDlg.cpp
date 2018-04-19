
// CharacterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "iostream"
#include "CvvImage.h"
#include "vector"
//#include "strngs.h"
#include "Strsafe.h"
//#include "baseapi.h"
#include "Character.h"
#include "CharacterDlg.h"
#include "afxdialogex.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//using namespace tesseract;
using namespace std;
using namespace cv;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCharacterDlg dialog

BEGIN_DHTML_EVENT_MAP(CCharacterDlg)
	DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
	DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)
END_DHTML_EVENT_MAP()


CCharacterDlg::CCharacterDlg(CWnd* pParent /*=nullptr*/)
	: CDHtmlDialog(IDD_CHARACTER_DIALOG, IDR_HTML_CHARACTER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCharacterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCharacterDlg, CDHtmlDialog)
	ON_WM_SYSCOMMAND()
	ON_STN_CLICKED(IDC_frame, &CCharacterDlg::OnStnClickedframe)
	ON_BN_CLICKED(IDC_btn3, &CCharacterDlg::OnBnClickedbtn3)
	ON_BN_CLICKED(IDC_btn4, &CCharacterDlg::OnBnClickedbtn4)
END_MESSAGE_MAP()


// CCharacterDlg message handlers

BOOL CCharacterDlg::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCharacterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDHtmlDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCharacterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDHtmlDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCharacterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HRESULT CCharacterDlg::OnButtonOK(IHTMLElement* /*pElement*/)
{
	OnOK();
	return S_OK;
}

HRESULT CCharacterDlg::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	OnCancel();
	return S_OK;
}


void CCharacterDlg::OnStnClickedframe()
{
	// TODO: Add your control notification handler code here
}


Mat CCharacterDlg::Feature_match(Mat tpl_img, Mat src_img, int factor, const float nn_match_ratio, int i_index, int id_)
{
	const float inlier_threshold = 85.8f; // Distance threshold to identify inliers  2.5f
										  //	const float nn_match_ratio = 0.8f;   // Nearest neighbor matching ratio
	Mat gene_img;
	Mat c_img1 = tpl_img.clone();
	Mat c_img2 = src_img.clone();
	if (!c_img1.data || !c_img2.data)
	{
		//img_insp.err_msg_[i_index] = L"图像源错误";
		//img_insp.inspect_stat[id_] = FALSE;
		gene_img = NULL;

		return gene_img;
	}
	Mat img1;
	cvtColor(c_img1, img1, CV_BGR2GRAY);
	Mat img2;
	cvtColor(c_img2, img2, CV_BGR2GRAY);
	/*Mat homography;
	FileStorage fs("..//H1to3p.xml", FileStorage::READ);
	fs.getFirstTopLevelNode() >> homography;*/
	vector<KeyPoint> kpts1, kpts2;
	Mat desc1, desc2;

	Ptr<AKAZE> akaze = AKAZE::create();
	akaze->detectAndCompute(img1, noArray(), kpts1, desc1);
	akaze->detectAndCompute(img2, noArray(), kpts2, desc2);

	BFMatcher matcher(NORM_HAMMING);
	vector< vector<DMatch> > nn_matches;
	matcher.knnMatch(desc1, desc2, nn_matches, 2);

	//-- Localize the object
	std::vector<Point2f> obj;
	std::vector<Point2f> scene;

	vector<KeyPoint> matched1, matched2, inliers1, inliers2;
	vector<DMatch> good_matches;
	if (nn_matches.size()<3)
	{
		gene_img = NULL;

		return gene_img;
	}
	for (size_t i = 0; i < nn_matches.size(); i++)
	{
		DMatch first = nn_matches[i][0];
		float dist1 = nn_matches[i][0].distance;
		float dist2 = nn_matches[i][1].distance;

		if (dist1 < nn_match_ratio * dist2)
		{
			matched1.push_back(kpts1[first.queryIdx]);
			matched2.push_back(kpts2[first.trainIdx]);
		}
		obj.push_back(kpts1[first.queryIdx].pt);
		scene.push_back(kpts2[first.trainIdx].pt);
	}

	Mat homography = findHomography(obj, scene, CV_RANSAC);

	FileStorage fs("..//homography.xml", FileStorage::WRITE);
	fs << "homography" << homography;
	fs.release();

	double max_dist = 0; double min_dist = 100;
	//-- Quick calculation of max and min distances between keypoints
	for (int i = 0; i < desc1.rows; i++)
	{
		double dist = nn_matches[i][0].distance;
		if (dist < min_dist) min_dist = dist;
		if (dist > max_dist) max_dist = dist;
	}
	resu = min_dist;

	for (unsigned i = 0; i < matched1.size(); i++)
	{
		Mat col = Mat::ones(3, 1, CV_64F);
		col.at<double>(0) = matched1[i].pt.x;
		col.at<double>(1) = matched1[i].pt.y;

		col = homography * col;
		col /= col.at<double>(2);
		double dist = sqrt(pow(col.at<double>(0) - matched2[i].pt.x, 2) + pow(col.at<double>(1) - matched2[i].pt.y, 2));

		if (dist < factor * min_dist)// inlier_threshold
		{
			int new_i = static_cast<int>(inliers1.size());
			inliers1.push_back(matched1[i]);
			inliers2.push_back(matched2[i]);
			good_matches.push_back(DMatch(new_i, new_i, 0));
		}
	}
	if (good_matches.size() < 2)
	{
		err_msg = L"匹配点数过少";
		gene_img = NULL;
		return gene_img;
	}
	else
	{
		for (int i = 0; i < good_matches.size(); i++)
		{
			//-- Get the keypoints from the good matches
			obj.push_back(kpts1[good_matches[i].queryIdx].pt);
			scene.push_back(kpts2[good_matches[i].trainIdx].pt);
		}
		homography = findHomography(obj, scene, CV_RANSAC);

		Mat res;
		drawMatches(img1, inliers1, img2, inliers2, good_matches, res);
		USES_CONVERSION;
		CString tmp_nme;
		char* dst_;
		tmp_nme.Format(L"..//MFC_capture//features//res%d.jpg", i_index);
		dst_ = T2A(tmp_nme.GetBuffer(0));
		tmp_nme.ReleaseBuffer();

		imwrite(dst_, res);

		//-- Get the corners from the image_1 ( the object to be "detected" )
		std::vector<Point2f> obj_corners(4);
		obj_corners[0] = cvPoint(0, 0); obj_corners[1] = cvPoint(img1.cols, 0);
		obj_corners[2] = cvPoint(img1.cols, img1.rows); obj_corners[3] = cvPoint(0, img1.rows);
		std::vector<Point2f> scene_corners(4);

		perspectiveTransform(obj_corners, scene_corners, homography);

		//-- Draw lines between the corners (the mapped object in the scene - image_2 )
		line(c_img2, scene_corners[0], scene_corners[1], Scalar(0, 255, 0), 4);
		line(c_img2, scene_corners[1], scene_corners[2], Scalar(0, 255, 0), 4);
		line(c_img2, scene_corners[2], scene_corners[3], Scalar(0, 255, 0), 4);
		line(c_img2, scene_corners[3], scene_corners[0], Scalar(0, 255, 0), 4);

		//-- Show detected matches
		gene_img = c_img2;
	}
	return gene_img;
}

void CCharacterDlg::disp_image(UINT disp_ID, Mat dsp_img, CWnd* pt)
{
	IplImage cpy;
	CvvImage cimg;
	CDC* _pDC;
	HDC hDC;
	CRect rect;
	_pDC = pt->GetDlgItem(disp_ID)->GetDC();		// 获得显示控件的 DC
	hDC = _pDC->GetSafeHdc();				// 获取 HDC(设备句柄) 来进行绘图操作
	pt->GetDlgItem(disp_ID)->GetClientRect(&rect);	// 获取控件尺寸位置
	cpy = dsp_img;
	cimg.CopyOf(&cpy);						// 复制图片
	cimg.DrawToHDC(hDC, &rect);				// 将图片绘制到显示控件的指定区域内
	pt->ReleaseDC(_pDC);
}

void CCharacterDlg::disp_image(UINT disp_ID, Mat dsp_img, CWnd* pt, CRect rect_)
{
	IplImage cpy;
	CvvImage cimg;
	CDC* _pDC;
	HDC hDC;
	CRect rect = rect_;
	_pDC = pt->GetDlgItem(disp_ID)->GetDC();		// 获得显示控件的 DC
	hDC = _pDC->GetSafeHdc();				// 获取 HDC(设备句柄) 来进行绘图操作
	cpy = dsp_img;
	cimg.CopyOf(&cpy);						// 复制图片
	cimg.DrawToHDC(hDC, &rect);				// 将图片绘制到显示控件的指定区域内
	pt->ReleaseDC(_pDC);
}

//choose folder
void CCharacterDlg::OnBnClickedbtn3()
{
	// TODO: Add your control notification handler code here
	//选择输出路径  
	TCHAR szDir[MAX_PATH];
	BROWSEINFO bi;
	ITEMIDLIST *pidl;
	bi.hwndOwner = this->m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szDir;//这个是输出缓冲区   
	bi.lpszTitle = _T("画像フォルダー："); //标题  
	bi.ulFlags = BIF_NEWDIALOGSTYLE;//使用新的界面,在win7中效果较好//BIF_RETURNONLYFSDIRS;   
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	pidl = SHBrowseForFolder(&bi);//弹出对话框   
	if (pidl == NULL)//点了取消，或者选择了无效的文件夹则返回NULL  
		return;

	if (SHGetPathFromIDList(pidl, szDir))
	{
		MessageBox(L"LOL");
	}
		
}

//choose file
void CCharacterDlg::OnBnClickedbtn4()
{
	// TODO: Add your control notification handler code here
	CString szFileName;
	CString szCount;
	POSITION pos;
	int i;
	int nCount = 0; //文件数量  
	//输入文件  
	CFileDialog InFile(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT, _T("某种格式|*.fmt|所有文件(*.*)|*.*||"));
	InFile.m_ofn.nMaxFile = 10000;//文件上限  
	InFile.m_ofn.lpstrFile = (LPWSTR)malloc(InFile.m_ofn.nMaxFile * sizeof(TCHAR));
	memset(InFile.m_ofn.lpstrFile, 0, InFile.m_ofn.nMaxFile);

	//按了OK按钮，开始获取文件列表  
	if (InFile.DoModal() == IDOK)
	{
		pos = InFile.GetStartPosition();
		while (pos)
		{
			szFileName = InFile.GetNextPathName(pos);
			//这里szFileName就是文件路径  
			//做点什么事情，比如添加到列表框  
		}
	}
	//释放空间  
	free(InFile.m_ofn.lpstrFile);
}
