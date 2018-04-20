
// extract_exampleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "extract_example.h"
#include "extract_exampleDlg.h"
#include "afxdialogex.h"
#include "iostream"
#include "CvvImage.h"
#include "vector"
//#include "strngs.h"
#include "Strsafe.h"
//#include "baseapi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CextractexampleDlg* extra_pt;

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


// CextractexampleDlg dialog
using namespace std;
using namespace cv;


CextractexampleDlg::CextractexampleDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_EXTRACT_EXAMPLE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CextractexampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_sted_btn, btn_sted);
	DDX_Control(pDX, IDC_folder_choose, btn_fdch);
	DDX_Control(pDX, IDC_file_choose, btn_flch);
	DDX_Control(pDX, IDC_info, info_);
}

BEGIN_MESSAGE_MAP(CextractexampleDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_sted_btn, &CextractexampleDlg::OnBnClickedstedbtn)
	ON_BN_CLICKED(IDC_folder_choose, &CextractexampleDlg::OnBnClickedfolderchoose)
	ON_BN_CLICKED(IDC_file_choose, &CextractexampleDlg::OnBnClickedfilechoose)
END_MESSAGE_MAP()


// CextractexampleDlg message handlers

BOOL CextractexampleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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
	extra_pt = this;
	file_nme.clear();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CextractexampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CextractexampleDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CextractexampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//start-stop
void CextractexampleDlg::OnBnClickedstedbtn()
{
	// TODO: Add your control notification handler code here
	if (!func_code)//->start
	{
		func_code = TRUE;
		st_sgn = TRUE;
		btn_sted.SetWindowText(L"Stop");
		btn_fdch.EnableWindow(FALSE);
		btn_flch.EnableWindow(FALSE);
		//
		Mat tpl_;
		Mat res_;
		Mat src;
		USES_CONVERSION;
		img_nme = T2A(file_nme[0].GetBuffer(0));
		file_nme[0].ReleaseBuffer();
		tpl_ = imread("tpl.bmp");
		src = imread(img_nme);
		res_ = Feature_match(tpl_, src, 20, 0.45f, 0, 0);
		if (res_.data)
		{
			disp_image(IDC_pic, res_, extra_pt);
		}
	}
	else//->stop
	{
		func_code = FALSE;
		st_sgn = FALSE;
		btn_sted.SetWindowText(L"Start");
		btn_fdch.EnableWindow(TRUE);
		btn_flch.EnableWindow(TRUE);
	}
}

//folder choose
void CextractexampleDlg::OnBnClickedfolderchoose()
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
		SearchFiles(szDir);
		btn_sted.EnableWindow(TRUE);
	}
	
}

//file choose
void CextractexampleDlg::OnBnClickedfilechoose()
{
	// TODO: Add your control notification handler code here
	CString szFileName;
	CString szCount;
	POSITION pos;
	int nCount = 0; //文件数量  
					//输入文件  
	CFileDialog InFile(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT, _T("bmp|*.bmp|所有文件(*.*)|*.*||"));
	InFile.m_ofn.nMaxFile = 10000;//文件上限  
	InFile.m_ofn.lpstrFile = (LPWSTR)malloc(InFile.m_ofn.nMaxFile * sizeof(TCHAR));
	memset(InFile.m_ofn.lpstrFile, 0, InFile.m_ofn.nMaxFile);
	file_nme.clear();
	//按了OK按钮，开始获取文件列表  
	if (InFile.DoModal() == IDOK)
	{
		pos = InFile.GetStartPosition();
		while (pos)
		{
			szFileName = InFile.GetNextPathName(pos);
			//这里szFileName就是文件路径  
			//做点什么事情，比如添加到列表框  
			file_nme.push_back(szFileName);
			btn_sted.EnableWindow(TRUE);
			Mat test_img;
			
			USES_CONVERSION;
			img_nme = T2A(szFileName.GetBuffer(0));
			szFileName.ReleaseBuffer();
			test_img = imread(img_nme);
			if (test_img.data)
			{
				disp_image(IDC_pic, test_img, extra_pt);
			}
			else
			{
				info_.ReplaceSel(L"Warning, input image not Valid.\r\n");
			}
			file_nme.shrink_to_fit();
		}
	}
	//释放空间  
	free(InFile.m_ofn.lpstrFile);
}

//search
void CextractexampleDlg::SearchFiles(CString strMusicFolder)
{
	CFileFind ff;

	strMusicFolder += _T("\\");

	strMusicFolder += _T("*.*");
	CString tmp_cstr;
	BOOL res = ff.FindFile(strMusicFolder);
	file_nme.clear();
	while (res)
	{
		res = ff.FindNextFile();
		if (!ff.IsDirectory() && !ff.IsDots())
		{
			//AfxMessageBox(ff.GetFilePath());
			tmp_cstr = ff.GetFilePath();
			file_nme.push_back(tmp_cstr);
			tmp_cstr = ff.GetFileName();
			info_.ReplaceSel(tmp_cstr + L"\r\n");
		}
	}
	file_nme.shrink_to_fit();
	ff.Close();
}

//Next Inspect Image
void CextractexampleDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::OnOK();
}

/* 

	Function Zone 

*/

Mat CextractexampleDlg::Feature_match(Mat tpl_img, Mat src_img, int factor, const float nn_match_ratio, int i_index, int id_)
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
	if (good_matches.size() < 0)
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
		imshow("test1", img1);
		imshow("test2", img2);
		imshow("tests", res);
		USES_CONVERSION;
		CString tmp_nme;
		char* dst_;
		tmp_nme.Format(L"..//res%d.jpg", i_index);
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

void CextractexampleDlg::disp_image(UINT disp_ID, Mat dsp_img, CWnd* pt)
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

void CextractexampleDlg::disp_image(UINT disp_ID, Mat dsp_img, CWnd* pt, CRect rect_)
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


