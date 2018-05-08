
// extract_exampleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "extract_example.h"
#include "extract_exampleDlg.h"
#include "afxdialogex.h"
#include "iostream"
#include "CvvImage.h"
#include "vector"
#include "Strsafe.h"
#include "stdio.h"
#include "stdlib.h"
#include "iostream"
//#include "strngs.h"
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
//using namespace xfeatures2d;



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
	DDX_Control(pDX, IDC_shot, btn_shot);
	DDX_Control(pDX, IDC_camsel, cam_sel);
	DDX_Control(pDX, IDC_info, info_);
	DDX_Control(pDX, IDC_fact_SLIDER1, fact_sld);
	DDX_Control(pDX, IDC_match_SLIDER2, match_sld);
	DDX_Control(pDX, IDC_focus, focus_sld);
}

BEGIN_MESSAGE_MAP(CextractexampleDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_sted_btn, &CextractexampleDlg::OnBnClickedstedbtn)
	ON_BN_CLICKED(IDC_folder_choose, &CextractexampleDlg::OnBnClickedfolderchoose)
	ON_BN_CLICKED(IDC_file_choose, &CextractexampleDlg::OnBnClickedfilechoose)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_fact_SLIDER1, &CextractexampleDlg::OnNMCustomdrawfactSlider1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_match_SLIDER2, &CextractexampleDlg::OnNMCustomdrawmatchSlider2)
	ON_BN_CLICKED(IDC_shot, &CextractexampleDlg::OnBnClickedshot)
	ON_CBN_SELCHANGE(IDC_camsel, &CextractexampleDlg::OnCbnSelchangecamsel)
	ON_WM_TIMER()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_focus, &CextractexampleDlg::OnNMCustomdrawfocus)
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

	fact_sld.SetRange(1, 100);
	fact_sld.SetTicFreq(1);
	fact_sld.SetPos(5);
	match_sld.SetRange(100, 3500);
	match_sld.SetTicFreq(1);
	match_sld.SetPos(500);
	focus_sld.SetRange(1, 500);
	focus_sld.SetTicFreq(1);
	focus_sld.SetPos(10);

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
		info_.SetWindowText(L"");
		count_ = file_nme.size();


		USES_CONVERSION;
		img_nme = T2A(file_nme[0].GetBuffer(0));
		file_nme[0].ReleaseBuffer();
		tpl_ = imread("tpl1.bmp");
		src = imread(img_nme);

		f_exc = Feature_SIFT(tpl_, src, minHessian_, match_);
		if (f_exc.op_sgn)
		{
			res_ = f_exc.out_res;
			tmp_.Format(f_exc.msg_ + L"Found Object: %d\r\nProcess Time: %.2fs\r\n\r\n", f_exc.cnt_, f_exc.prs_time);
			info_.ReplaceSel(tmp_);
			imwrite("res0.bmp", res_);
			if (res_.data)
			{
				disp_image(IDC_pic, res_, extra_pt);
			}
		}
		else
		{
			tmp_ = f_exc.err_msg;
			MessageBox(tmp_);
		}

		//res_ = Feature_match(tpl_, src, factor_, match_, 0, 0);

		count_--;
		if (func_code && count_ == 0)
		{
			OnBnClickedstedbtn();//stop
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

//shot
void CextractexampleDlg::OnBnClickedshot()
{
	// TODO: Add your control notification handler code here
	capture >> cap_frame;
	imwrite("..\\shot.bmp", cap_frame);
	KillTimer(0);
	cap_frame = NULL;
	disp_image(IDC_pic, cap_frame, extra_pt);
	cam_selsgn = FALSE;
	btn_shot.EnableWindow(FALSE);
	/*int box[] = { 0,0,0,0,0,0,0,0,0,0 };
	for (int a = 1; a < 667; a++)
	{
		for (int b = 0; b < 10; b++)
		{
			if (a!=box[b])
			{

			}
		}

	}*/

}

//camera select
void CextractexampleDlg::OnCbnSelchangecamsel()
{
	// TODO: Add your control notification handler code here
	int index_ = cam_sel.GetCurSel();
	capture.open(index_);
	capture.set(CAP_PROP_FRAME_WIDTH, 1920);//640
	capture.set(CAP_PROP_FRAME_HEIGHT, 1080);//360
	SetTimer(0, 50, NULL);
	cam_sel.SetCurSel(-1);
	cam_selsgn = TRUE;
	btn_shot.EnableWindow(TRUE);
}

//folder choose
void CextractexampleDlg::OnBnClickedfolderchoose()
{
	// TODO: Add your control notification handler code here
	//选择输出路径  
	info_.SetWindowText(L"");
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
		sgn_fun = FALSE;
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
			sgn_fun = TRUE;
			info_.SetWindowText(L"");
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

	strMusicFolder += _T("*.bmp");
	CString tmp_cstr;
	BOOL res = ff.FindFile(strMusicFolder);
	file_nme.clear();
	while (res)
	{
		res = ff.FindNextFile();
		if (!ff.IsDirectory() && !ff.IsDots())
		{
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
	if (count_ == 0)
	{
		MessageBox(L"No Next Image !");
		if (func_code)
		{
			OnBnClickedstedbtn();//stop
		}
	}
	else
	{
		USES_CONVERSION;
		img_nme = T2A(file_nme[count_].GetBuffer(0));
		file_nme[count_].ReleaseBuffer();
		src = imread(img_nme);

		f_exc = Feature_SIFT(tpl_, src, minHessian_, match_);
		if (f_exc.op_sgn)
		{
			res_ = f_exc.out_res;
			tmp_.Format(f_exc.msg_ + L"Found Object: %d\r\nProcess Time: %.2fs\r\n\r\n", f_exc.cnt_, f_exc.prs_time);
			info_.ReplaceSel(tmp_);
			imwrite("res0.bmp", res_);
			if (res_.data)
			{
				disp_image(IDC_pic, res_, extra_pt);
			}
		}
		else
		{
			tmp_ = f_exc.err_msg;
			MessageBox(tmp_);
		}
		count_--;
	}
	//CDialog::OnOK();
}

//factor
void CextractexampleDlg::OnNMCustomdrawfactSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	double match = 2.0f;
	int cur_sel = fact_sld.GetPos();
	match = cur_sel / 10.00f;
	match_ = match;
	*pResult = 0;
}

//match
void CextractexampleDlg::OnNMCustomdrawmatchSlider2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	int cur_sel = match_sld.GetPos();
	minHessian_ = cur_sel;
	*pResult = 0;
}

//focus
void CextractexampleDlg::OnNMCustomdrawfocus(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	int cur_sel = focus_sld.GetPos();
	capture.set(CAP_PROP_FOCUS, cur_sel);
	*pResult = 0;
}

/* 	Function Zone  */

Mat CextractexampleDlg::Feature_match(Mat tpl_img, Mat src_img, int factor, const float nn_match_ratio, int i_index, int id_)
{
	const float inlier_threshold = 12.5f; // Distance threshold to identify inliers  2.5f
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

	FileStorage fs("homography.xml", FileStorage::WRITE);
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

		if (dist < inlier_threshold)// factor * min_dist
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
		/*imshow("test1", img1);
		imshow("test2", img2);
		imshow("tests", res);*/
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

CextractexampleDlg::feature_exc CextractexampleDlg::Feature_SIFT(Mat tpl_img, Mat src_img, int minHessian, double factor)
{
	int		h = 0;
	int		cnt_tmp = 0;
	int		watch_timer = 0;
	float	minDistance = 400;
	float	maxDistance = 0;

	Mat		src;
	Mat		tpl_;
	Mat		H;//homegraphy
	Mat		description1;
	Mat		description2;
	Mat		image1;
	Mat		image2;
	Mat		mask = Mat(src.size(), CV_8UC1, Scalar(255, 255, 255));

	Rect	boundRect;
	BOOL	op_sgn = FALSE;
	CString tmp_msg;
	clock_t startTime, endTime;

	//-- Localize the object
	std::vector<Point2f>  obj;
	std::vector<Point2f>  scene;
	std::vector<Point2f>  obj_corners(4);
	std::vector<Point2f>  scene_corners(4);
	std::vector<DMatch>   matches;
	std::vector<DMatch>   goodMatches;
	std::vector<KeyPoint> keypoints_1, keypoints_2;
	std::vector<Point2f>::iterator it_s;
	std::vector<Point2f>::iterator it_o;

	src = src_img.clone();
	tpl_ = tpl_img.clone();

	if (!tpl_.data || !src.data)
	{
		tmp_msg.Format(L"Source Image ERROR.\r\n");
		f_exc.err_msg = tmp_msg;
		f_exc.op_sgn = FALSE;
		return f_exc;
	}

	//grayscale
	if (tpl_.channels() != 1)
	{
		cvtColor(tpl_, image1, CV_BGR2GRAY);
	}
	if (src.channels() != 1)
	{
		cvtColor(src, image2, CV_BGR2GRAY);
	}

	startTime = clock();

	Ptr<xfeatures2d::SIFT> detector = xfeatures2d::SIFT::create(minHessian);
	Ptr<DescriptorMatcher> descriptor_matcher = DescriptorMatcher::create("BruteForce");
	//-- Get the corners from template
	obj_corners[0] = cvPoint(0, 0);
	obj_corners[1] = cvPoint(tpl_.cols, 0);
	obj_corners[2] = cvPoint(tpl_.cols, tpl_.rows);
	obj_corners[3] = cvPoint(0, tpl_.rows);
	Mat key1, key2;
	//step1 detect and compute features
	detector->detectAndCompute(image1, cv::noArray(), keypoints_1, description1);
	detector->detectAndCompute(image2, cv::noArray(), keypoints_2, description2);
	//step2 match features
	descriptor_matcher->match(description1, description2, matches);
	matches.shrink_to_fit();
	//step3 min-max distance
	for (int i = 0; i < matches.size(); i++)
	{
		if (matches[i].distance < minDistance)
			minDistance = matches[i].distance;
		if (matches[i].distance > maxDistance)
			maxDistance = matches[i].distance;
	}
	if (minDistance > (float)80)//65
	{
		tmp_msg.Format(L"Matching Distance too High.\r\nReference Value: %f", minDistance);
		f_exc.err_msg = tmp_msg;
		f_exc.op_sgn = FALSE;
		return f_exc;
	}
	tmp_msg.Format(L"SIFT Feature Matching Algorithm\r\n\r\nminDistance: %.2f\r\nmaxDistance: %.2f\r\n", minDistance, maxDistance);
	f_exc.msg_ = tmp_msg;
	//step4 goodmatches
	for (int i = 0; i < matches.size(); i++)
	{
		if (matches[i].distance < factor * minDistance)
		{
			goodMatches.push_back(matches[i]);
			obj.push_back(keypoints_1[goodMatches[h].queryIdx].pt);
			scene.push_back(keypoints_2[goodMatches[h].trainIdx].pt);
			h++;
		}
	}
	h = 0;
	goodMatches.shrink_to_fit();
	if (goodMatches.size() < 10)
	{
		tmp_msg.Format(L"No Matching Results Or Fewer Features.\r\n");
		f_exc.err_msg = tmp_msg;
		f_exc.op_sgn = FALSE;
		return f_exc;
	}
	else
	{
		//step5 locate target
		while (scene.size() > 5 && watch_timer < 4)
		{
			watch_timer++;
			//Homegraphy
			H = findHomography(obj, scene, CV_RANSAC);
			if (!H.data)
			{
				tmp_msg.Format(L"Homegraphy Matrix Error.\r\n");
				f_exc.err_msg = tmp_msg;
				f_exc.op_sgn = FALSE;
				return f_exc;
			}
			FileStorage fs("..//homography.xml", FileStorage::WRITE);
			fs << "homography" << H;
			fs.release();
			perspectiveTransform(obj_corners, scene_corners, H);
			boundRect = boundingRect(scene_corners);
			it_s = scene.begin();
			it_o = obj.begin();
			if (boundRect.area() > 99000 || boundRect.area() < 100)
			{
				continue;
			}
			//-- Draw lines between the corners (the mapped object in the scene - image_2 )
			line(src, scene_corners[0], scene_corners[1], Scalar(0, 255, 0), 4);
			line(src, scene_corners[1], scene_corners[2], Scalar(0, 255, 0), 4);
			line(src, scene_corners[2], scene_corners[3], Scalar(0, 255, 0), 4);
			line(src, scene_corners[3], scene_corners[0], Scalar(0, 255, 0), 4);
			for (it_s = scene.begin(); it_s != scene.end();)
			{
				op_sgn = boundRect.contains(*it_s);
				if (op_sgn)
				{
					it_s = scene.erase(it_s);
					it_o = obj.erase(it_o);
				}
				else
				{
					if (it_o != obj.end())
					{
						it_o++;
						it_s++;
					}
				}
			}
			cnt_tmp++;
		}
		//drawMatches 
		Mat dstImg3;
		drawMatches(tpl_, keypoints_1, src, keypoints_2, goodMatches, dstImg3, Scalar(255, 0, 0), Scalar(0, 255, 0));
		imwrite("res1.bmp", dstImg3);
		watch_timer = 0;
		f_exc.cnt_ = cnt_tmp;
		obj.clear();
		scene.clear();
		goodMatches.clear();
		matches.clear();
	}
	f_exc.out_res = src;
	f_exc.op_sgn = TRUE;
	endTime = clock();
	f_exc.prs_time = (double)(endTime - startTime) / CLOCKS_PER_SEC;
	return f_exc;

#pragma region Additional
	/*
	//detector->detect(image1, keypoints_1);
	//detector->detect(image2, keypoints_2);

	//-- Draw keypoints
	//Mat img_keypoints_1; Mat img_keypoints_2;
	////drawKeypoints(image1, keypoints_1, img_keypoints_1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	////drawKeypoints(image2, keypoints_2, img_keypoints_2, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	//detector->compute(image1, keypoints_1, description1);//注意原图和特征点要对应，不要写错  
	//detector->compute(image2, keypoints_2, description2);

	//drawMatches 
	Mat dstImg3;
	drawMatches(tpl_, keypoints_1, src, keypoints_2, goodMatches, dstImg3, Scalar(255, 0, 0), Scalar(0, 255, 0));
	imwrite("res1.bmp", dstImg3);
	for (int i = 0; i < goodMatches.size(); i++)
	{
	//-- Get the keypoints from the good matches
	obj.push_back(keypoints_1[goodMatches[i].queryIdx].pt);
	scene.push_back(keypoints_2[goodMatches[i].trainIdx].pt);
	}

	line(src, scene_corners[0] + Point2f(tpl_.cols, 0), scene_corners[1] + Point2f(tpl_.cols, 0), Scalar(0, 255, 0), 4);
	line(src, scene_corners[1] + Point2f(tpl_.cols, 0), scene_corners[2] + Point2f(tpl_.cols, 0), Scalar(0, 255, 0), 4);
	line(src, scene_corners[2] + Point2f(tpl_.cols, 0), scene_corners[3] + Point2f(tpl_.cols, 0), Scalar(0, 255, 0), 4);
	line(src, scene_corners[3] + Point2f(tpl_.cols, 0), scene_corners[0] + Point2f(tpl_.cols, 0), Scalar(0, 255, 0), 4);

	//cv::rectangle(src, boundRect, Scalar(0, 0, 0), -1, 8, 0);//mask

	for (int h = 0; h < scene.size(); h++)
	{
	circle(src, scene[h], 6, Scalar(0, 0, 255), -1, 8);
	}

	RotatedRect rect_= minAreaRect(scene_corners);

	*/
#pragma endregion
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

void CextractexampleDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent)
	{
	case 0:
	{
		capture >> cap_frame;
		if (cap_frame.data)
		{
			disp_image(IDC_pic, cap_frame, extra_pt);
		}

		break;
	}
	default:
		break;
	}
	CDialog::OnTimer(nIDEvent);
}


/* 	Function Zone  */
