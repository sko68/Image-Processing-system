
// MFCApplication1Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"



Mat image;
Mat outImage;
CString strFileName;
TCHAR szFilter[] = _T("jpg file(*.jpg)|*.jpg|bmp file(*.bmp)|*.bmp|所有文件(*.*)|*.*||");  //文件格式过滤


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMFCApplication1Dlg 对话框



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OpenPicture, &CMFCApplication1Dlg::OnBnClickedOpenpicture)
	ON_BN_CLICKED(IDC_ClosePicture, &CMFCApplication1Dlg::OnBnClickedClosepicture)
	ON_COMMAND(ID_OpenFile, &CMFCApplication1Dlg::OnOpenfile)
	ON_COMMAND(ID_Close, &CMFCApplication1Dlg::OnClose)
	ON_COMMAND(ID_Log, &CMFCApplication1Dlg::OnLog)
	ON_COMMAND(ID_Exponent, &CMFCApplication1Dlg::OnExponent)
	ON_COMMAND(ID_Reverse, &CMFCApplication1Dlg::OnReverse)
	ON_COMMAND(ID_Segmented, &CMFCApplication1Dlg::OnSegmented)
	ON_COMMAND(ID_BoxFilter, &CMFCApplication1Dlg::OnBoxfilter)
	ON_COMMAND(ID_Blur, &CMFCApplication1Dlg::OnBlur)
	ON_COMMAND(ID_GaussianBlur, &CMFCApplication1Dlg::OnGaussianblur)
	ON_COMMAND(ID_MedianBlur, &CMFCApplication1Dlg::OnMedianblur)
	ON_COMMAND(ID_BilateralFilter, &CMFCApplication1Dlg::OnBilateralfilter)
	ON_COMMAND(ID_Roberts, &CMFCApplication1Dlg::OnRoberts)
	ON_COMMAND(ID_Prewitt, &CMFCApplication1Dlg::OnPrewitt)
	ON_COMMAND(ID_Sobel, &CMFCApplication1Dlg::OnSobel)
	ON_COMMAND(ID_Laplace, &CMFCApplication1Dlg::OnLaplace)
	ON_COMMAND(ID_Ideal_Low_Pass, &CMFCApplication1Dlg::OnIdealLowPass)
	ON_COMMAND(ID_Butterworth_Low_Pass, &CMFCApplication1Dlg::OnButterworthLowPass)
	ON_COMMAND(ID_Gaussian_Low_Pass, &CMFCApplication1Dlg::OnGaussianLowPass)
	ON_COMMAND(ID_Ideal_high_pass, &CMFCApplication1Dlg::OnIdealHighPass)
	ON_COMMAND(ID_Butterworth_High_Pass, &CMFCApplication1Dlg::OnButterworthHighPass)
	ON_COMMAND(ID_Gaussian_High_Pass, &CMFCApplication1Dlg::OnGaussianHighPass)
	ON_COMMAND(ID_DrawHist, &CMFCApplication1Dlg::OnDrawhist)
	ON_COMMAND(ID_EqualizeHist, &CMFCApplication1Dlg::OnEqualizehist)
	ON_COMMAND(ID_Save, &CMFCApplication1Dlg::OnSave)
END_MESSAGE_MAP()

// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	menu.LoadMenu(IDR_MENU1);  //IDR_MENU1为菜单栏ID号
	SetMenu(&menu);

	//设置窗体的位置和宽高

	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);
	SetWindowPos(NULL, cx - 2060, cy - 1260, 1680, 1050, SWP_NOACTIVATE);

	//设置控件的位置及大小
	CWnd* pWnd;
	pWnd = GetDlgItem(IDC_ShowPicture);
	pWnd->SetWindowPos(NULL, 20, 50, 800, 600, SWP_NOZORDER);
	pWnd = GetDlgItem(IDC_ShowPicture2);
	pWnd->SetWindowPos(NULL, 850, 50, 800, 600, SWP_NOZORDER);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCApplication1Dlg::OnOpenfile()
{
	// TODO: 在此添加命令处理程序代码
	OnBnClickedOpenpicture();
}


void CMFCApplication1Dlg::OnClose()
{
	// TODO: 在此添加命令处理程序代码
	AfxGetMainWnd()->SendMessage(WM_CLOSE);
}

void CMFCApplication1Dlg::OnBnClickedOpenpicture()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(true, _T("jpg"), _T(".jpg"), OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY, szFilter, this);
	dlg.m_ofn.lpstrTitle = _T("Open Image");// 打开文件对话框的标题名
	if (!dlg.DoModal() == IDOK)
		return;
	CString strFileName = dlg.GetPathName();

	CFileStatus status;
	if (!CFile::GetStatus(strFileName, status))
	{
		MessageBox("您未选择新图片或图片不存在", "提示", MB_OK);
		return;
	}

	string srcFileName = strFileName.GetBuffer(0);
	image = imread(srcFileName);

	ShowImage(image, IDC_ShowPicture);

}

void CMFCApplication1Dlg::ShowImage(Mat image, int IDCNum)
{
	int height = image.rows;   //获取读入图片的尺寸
	int width = image.cols;
	Mat dest;
	CRect rect;    //定义矩形类

	GetDlgItem(IDCNum)->GetClientRect(&rect);

	destroyWindow("View");             //每次显示之前都销毁一下当前窗口，避免点击第二次不能显示
	GetDlgItem(IDCNum)->ShowWindow(FALSE);    //清空当前控件中的内容，避免重新嵌入时发生重叠
	GetDlgItem(IDCNum)->ShowWindow(TRUE);

	namedWindow("View", WINDOW_AUTOSIZE);      //创建一个OpenCV窗口，显示图片
	HWND hWnd = (HWND)cvGetWindowHandle("View");      //将创建的窗口嵌入到picture控件中
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(IDCNum)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);

	if (!image.empty())
	{
		if (width <= rect.Width() && height <= rect.Width()) //图片如果图片的尺寸不大于控件的尺寸，不进行缩放
		{
			rect = CRect(rect.TopLeft(), CSize(width, height));
			imshow("View", image);
		}
		else
		{
			//按比例缩放到Picture控件表示的矩形区域
			float xScale = (float)rect.Width() / (float)width;
			float yScale = (float)rect.Height() / (float)height;
			float ScaleIndex = (xScale <= yScale ? xScale : yScale);    //求缩放系数
			int newWidth = width * ScaleIndex;  //计算缩放后的尺寸
			int newHight = height * ScaleIndex;
			resize(image, dest, Size(newWidth, newHight));   //  缩放图片
			imshow("View", dest);    //显示缩放后的图片

		}
	}
}
void CMFCApplication1Dlg::OnSave()
{
	// TODO: 在此添加命令处理程序代码
	if (outImage.empty())
	{
		CString str;
		str.SetString(_T("还没有图片可保存哦!"));
		MessageBox(str);
		return;
	}
	Save();
}

void CMFCApplication1Dlg::Save(/*UINT ID*/)
{
	// 构造保存文件对话框    
	CFileDialog fileDlg(FALSE, _T("jpg"), _T(".jpg"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	fileDlg.m_ofn.lpstrTitle = _T("保存");  //保存对话窗口标题名
	CString picturePath;
	if (IDOK == fileDlg.DoModal())  //按下确认键
	{
		picturePath = fileDlg.GetPathName();  //文件路径
	}

	string outFileName = picturePath.GetBuffer(0);
	imwrite(outFileName, outImage);
}

void CMFCApplication1Dlg::OnBnClickedClosepicture()
{
	// TODO: 在此添加控件通知处理程序代码	
	if (IsExistImage()) {

		destroyAllWindows();
		image = image.empty();
		GetDlgItem(IDC_ShowPicture)->ShowWindow(FALSE);
		GetDlgItem(IDC_ShowPicture)->ShowWindow(TRUE);
		GetDlgItem(IDC_ShowPicture2)->ShowWindow(FALSE);
		GetDlgItem(IDC_ShowPicture2)->ShowWindow(TRUE);
	}
}

boolean CMFCApplication1Dlg::IsExistImage()
{
	if (image.empty())  //判断是否加载成功
	{
		CString str;
		str.SetString(_T("未打开图片"));
		MessageBox(str);
		return false;
	}
	return true;
}


void CMFCApplication1Dlg::LogTransform1(Mat& src, Mat& dst)
{
	dst.create(image.size(), CV_32FC3);
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			for (int k = 0; k < image.channels(); k++) {
				dst.at<Vec3f>(i, j)[k] = log(1 + image.at<Vec3b>(i, j)[k]);
			}
		}
	}
	//归一化到0~255    
	normalize(dst, dst, 0, 255, CV_MINMAX);//转换成8bit图像显示    
	convertScaleAbs(dst, dst);
}

void CMFCApplication1Dlg::OnLog()
{
	// TODO: 在此添加命令处理程序代码
	if (IsExistImage()) {
		LogTransform1(image, outImage);
		ShowImage(outImage, IDC_ShowPicture2);
	}
}

void CMFCApplication1Dlg::OnExponent()  //幂律（伽马）变换
{
	// TODO: 在此添加命令处理程序代码
	if (IsExistImage()) {
		Mat dest;
		ExpEnhance(image, dest, 4);
		ShowImage(dest, IDC_ShowPicture2);
	}
}

void CMFCApplication1Dlg::ExpEnhance(Mat& image, Mat& dst, float r)
{
	dst.create(image.size(), CV_32FC3);
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			for (int k = 0; k < image.channels(); k++) {
				dst.at<Vec3f>(i, j)[k] = pow(image.at<Vec3b>(i, j)[k], r);
			}
		}
	}
	//归一化到0~255
	normalize(dst, dst, 0, 255, CV_MINMAX);//转换成8bit图像显示    
	convertScaleAbs(dst, dst);
}

void CMFCApplication1Dlg::OnReverse()  //图像反转
{
	// TODO: 在此添加命令处理程序代码
	if (IsExistImage()) {
		Reverse(image, outImage);
		ShowImage(outImage, IDC_ShowPicture2);
	}
}

void CMFCApplication1Dlg::Reverse(Mat& image, Mat& dst) {
	dst.create(image.size(), CV_32FC3);
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			for (int k = 0; k < image.channels(); k++) {
				dst.at<Vec3f>(i, j)[k] = 255 - image.at<Vec3b>(i, j)[k];
			}
		}
	}
	//归一化到0~255    
	normalize(dst, dst, 0, 255, CV_MINMAX);//转换成8bit图像显示   
	convertScaleAbs(dst, dst);
}

void CMFCApplication1Dlg::OnSegmented()     //分段线性变换
{
	// TODO: 在此添加命令处理程序代码
	if (IsExistImage()) {
		Segmented(image, outImage);
		ShowImage(outImage, IDC_ShowPicture2);
	}
}

void CMFCApplication1Dlg::Segmented(Mat& image, Mat& dst) {
	dst.create(image.size(), CV_32FC3);
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			for (int k = 0; k < image.channels(); k++) {
				float temp = image.at<Vec3b>(i, j)[k];
				if (temp < 50)
					dst.at<Vec3f>(i, j)[k] = image.at<Vec3b>(i, j)[k] * 0.5;
				else if (50 <= temp && temp < 150)
					dst.at<Vec3f>(i, j)[k] = image.at<Vec3b>(i, j)[k] * 3.6 - 310;
				else
					dst.at<Vec3f>(i, j)[k] = image.at<Vec3b>(i, j)[k] * 0.238 - 194;
			}
		}
	}
	//归一化到0~255    
	normalize(dst, dst, 0, 255, CV_MINMAX);//转换成8bit图像显示   
	convertScaleAbs(dst, dst);
}

void CMFCApplication1Dlg::OnBoxfilter()      //方框滤波
{
	// TODO: 在此添加命令处理程序代码
	if (IsExistImage()) {
		boxFilter(image, outImage, -1, Size(7, 7));
		ShowImage(outImage, IDC_ShowPicture2);
	}
}

void CMFCApplication1Dlg::OnBlur()     //均值滤波
{
	// TODO: 在此添加命令处理程序代码
	if (IsExistImage()) {
		blur(image, outImage, Size(7, 7));
		ShowImage(outImage, IDC_ShowPicture2);
	}
}

void CMFCApplication1Dlg::OnGaussianblur()     //高斯滤波
{
	// TODO: 在此添加命令处理程序代码
	if (IsExistImage()) {
		GaussianBlur(image, outImage, Size(7, 7), 0, 0);
		ShowImage(outImage, IDC_ShowPicture2);
	}
}

void CMFCApplication1Dlg::OnMedianblur()  //中值滤波
{
	// TODO: 在此添加命令处理程序代码
	if (IsExistImage()) {
		medianBlur(image, outImage, 7);
		ShowImage(outImage, IDC_ShowPicture2);
	}
}


void CMFCApplication1Dlg::OnBilateralfilter()    //双边滤波
{
	// TODO: 在此添加命令处理程序代码
	if (IsExistImage()) {
		bilateralFilter(image, outImage, 25, 25 * 2, 25 / 2);
		ShowImage(outImage, IDC_ShowPicture2);
	}
}


void CMFCApplication1Dlg::OnRoberts()
{
	// TODO: 在此添加命令处理程序代码
	if (IsExistImage()) {
		Roberts(image, outImage);
		ShowImage(outImage, IDC_ShowPicture2);
	}
}

void CMFCApplication1Dlg::Roberts(Mat& image, Mat& dst) {
	dst = image.clone();
	dst.create(image.size(), CV_32FC3);
	for (int i = 0; i < image.rows - 1; i++) {
		for (int j = 0; j < image.cols - 1; j++) {
			for (int k = 0; k < image.channels(); k++) {
				dst.at<Vec3f>(i, j)[k] = fabs(image.at<Vec3b>(i, j)[k] - image.at<Vec3b>(i + 1, j + 1)[k]) + fabs(image.at<Vec3b>(i, j + 1)[k] - image.at<Vec3b>(i + 1, j)[k]);
			}
		}
	}
	//归一化到0~255    
	//normalize(dst, dst, 0, 255, CV_MINMAX);//转换成8bit图像显示
	convertScaleAbs(dst, dst);
}


void CMFCApplication1Dlg::OnPrewitt()
{
	// TODO: 在此添加命令处理程序代码
	if (IsExistImage()) {
		Prewitt(image, outImage);
		ShowImage(outImage, IDC_ShowPicture2);
	}
}

void CMFCApplication1Dlg::Prewitt(Mat& image, Mat& dst) {
	dst = image.clone();
	Mat dstx = image.clone();
	Mat dsty = image.clone();
	dst.create(image.size(), CV_32FC3);
	for (int i = 1; i < image.rows - 1; i++) {
		for (int j = 1; j < image.cols - 1; j++) {
			for (int k = 0; k < image.channels(); k++) {
				//fabs(image_gray.at<uchar>(i + 1, j - 1) + 2 * image_gray.at<uchar>(i + 1, j) + image_gray.at<uchar>(i + 1, j +1) -image_gray.at<uchar>(i - 1, j - 1) - 2 * image_gray.at<uchar>(i - 1, j) - image_gray.at<uchar>(i - 1, j + 1)));
				dstx.at<Vec3b>(i, j)[k] = fabs((image.at<Vec3b>(i - 1, j - 1)[k] + image.at<Vec3b>(i - 1, j)[k] + image.at<Vec3b>(i - 1, j + 1)[k]) - (image.at<Vec3b>(i + 1, j - 1)[k] + image.at<Vec3b>(i + 1, j)[k] + image.at<Vec3b>(i + 1, j + 1)[k]));
				dsty.at<Vec3b>(i, j)[k] = fabs((image.at<Vec3b>(i - 1, j + 1)[k] + image.at<Vec3b>(i, j + 1)[k] + image.at<Vec3b>(i + 1, j + 1)[k]) - (image.at<Vec3b>(i - 1, j - 1)[k] + image.at<Vec3b>(i, j - 1)[k] + image.at<Vec3b>(i + 1, j - 1)[k]));
				dst.at<Vec3f>(i, j)[k] = max((dstx.at<Vec3b>(i, j)[k]), dsty.at<Vec3b>(i, j)[k]);
			}
		}
	}

	//归一化到0~255    
	//normalize(dst, dst, 0, 255, CV_MINMAX);//转换成8bit图像显示
	convertScaleAbs(dst, dst);
}


void CMFCApplication1Dlg::OnSobel()
{
	// TODO: 在此添加命令处理程序代码
	if (IsExistImage()) {
		Sobel(image, outImage);
		ShowImage(outImage, IDC_ShowPicture2);
	}
}

void CMFCApplication1Dlg::Sobel(Mat& image, Mat& dst) {
	dst = image.clone();
	Mat dstx = image.clone();
	Mat dsty = image.clone();
	dst.create(image.size(), CV_32FC3);
	for (int i = 1; i < image.rows - 1; i++) {
		for (int j = 1; j < image.cols - 1; j++) {
			for (int k = 0; k < image.channels(); k++) {
				//fabs(image_gray.at<uchar>(i + 1, j - 1) + 2 * image_gray.at<uchar>(i + 1, j) + image_gray.at<uchar>(i + 1, j +1) -image_gray.at<uchar>(i - 1, j - 1) - 2 * image_gray.at<uchar>(i - 1, j) - image_gray.at<uchar>(i - 1, j + 1)));
				dstx.at<Vec3b>(i, j)[k] = fabs(image.at<Vec3b>(i + 1, j - 1)[k] + 2 * image.at<Vec3b>(i + 1, j)[k] + image.at<Vec3b>(i + 1, j + 1)[k] - image.at<Vec3b>(i - 1, j - 1)[k] - 2 * image.at<Vec3b>(i - 1, j)[k] - image.at<Vec3b>(i - 1, j + 1)[k]);
				dsty.at<Vec3b>(i, j)[k] = fabs(image.at<Vec3b>(i - 1, j + 1)[k] + 2 * image.at<Vec3b>(i, j + 1)[k] + image.at<Vec3b>(i + 1, j + 1)[k] - image.at<Vec3b>(i - 1, j - 1)[k] - 2 * image.at<Vec3b>(i, j - 1)[k] - image.at<Vec3b>(i + 1, j - 1)[k]);
				dst.at<Vec3f>(i, j)[k] = dstx.at<Vec3b>(i, j)[k] + dsty.at<Vec3b>(i, j)[k];
			}
		}
	}

	//归一化到0~255    
	//normalize(dst, dst, 0, 255, CV_MINMAX);//转换成8bit图像显示
	convertScaleAbs(dst, dst);
}


void CMFCApplication1Dlg::OnLaplace()
{
	// TODO: 在此添加命令处理程序代码
	if (IsExistImage()) {
		GaussianBlur(image, image, Size(3, 3), 0, 0);
		//cvtColor(image, image, CV_BGR2GRAY);
		Laplacian(image, outImage, CV_16S, 3, 1, 0);
		convertScaleAbs(outImage, outImage);
		ShowImage(outImage, IDC_ShowPicture2);
	}
}

void CMFCApplication1Dlg::OnIdealLowPass()       //理想低通
{
	// TODO: 在此添加命令处理程序代码
	if (IsExistImage()) {
		if (1 != image.channels())
			cvtColor(image, image, COLOR_BGR2GRAY);
		outImage = ideal_low_pass_filter(image, 30);
		outImage = outImage(Rect(0, 0, image.cols, image.rows));
		ShowImage(outImage, IDC_ShowPicture2);
	}
}



void CMFCApplication1Dlg::OnButterworthLowPass()   //巴特沃斯低通
{
	// TODO: 在此添加命令处理程序代码
	if (IsExistImage()) {
		if (1 != image.channels())
			cvtColor(image, image, COLOR_BGR2GRAY);
		outImage = butterworth_low_paass_filter(image, 30, 2);
		outImage = outImage(cv::Rect(0, 0, image.cols, image.rows));
		ShowImage(outImage, IDC_ShowPicture2);
	}
}

void CMFCApplication1Dlg::OnGaussianLowPass()  //高斯低通
{
	// TODO: 在此添加命令处理程序代码
	if (IsExistImage()) {
		if (1 != image.channels())
			cvtColor(image, image, COLOR_BGR2GRAY);
		outImage = gaussian_low_pass_filter(image, 30);
		outImage = outImage(cv::Rect(0, 0, image.cols, image.rows));
		ShowImage(outImage, IDC_ShowPicture2);
	}
}


void CMFCApplication1Dlg::OnIdealHighPass()   //理想高通
{
	// TODO: 在此添加命令处理程序代码
	if (IsExistImage()) {
		if (1 != image.channels())
			cvtColor(image, image, COLOR_BGR2GRAY);
		outImage = ideal_high_pass_filter(image, 80);
		outImage = outImage(cv::Rect(0, 0, image.cols, image.rows));
		ShowImage(outImage, IDC_ShowPicture2);
	}
}


void CMFCApplication1Dlg::OnButterworthHighPass()  //巴特沃斯高通
{
	// TODO: 在此添加命令处理程序代码
	if (IsExistImage()) {
		if (1 != image.channels())
			cvtColor(image, image, COLOR_BGR2GRAY);
		outImage = butterworth_high_paass_filter(image, 80, 2);
		outImage = outImage(cv::Rect(0, 0, image.cols, image.rows));
		ShowImage(outImage, IDC_ShowPicture2);
	}
}


void CMFCApplication1Dlg::OnGaussianHighPass()   //高斯高通
{
	// TODO: 在此添加命令处理程序代码
	if (IsExistImage()) {
		if (1 != image.channels())
			cvtColor(image, image, COLOR_BGR2GRAY);
		outImage = gaussian_high_pass_filter(image, 80);
		outImage = outImage(cv::Rect(0, 0, image.cols, image.rows));
		ShowImage(outImage, IDC_ShowPicture2);
	}
}

cv::Mat image_make_border(cv::Mat& src)
{
	int w = getOptimalDFTSize(src.cols);
	int h = getOptimalDFTSize(src.rows);
	Mat padded;
	copyMakeBorder(src, padded, 0, h - src.rows, 0, w - src.cols, BORDER_CONSTANT, Scalar::all(0));
	padded.convertTo(padded, CV_32FC1);
	return padded;
}

//频率域滤波
Mat frequency_filter(Mat& scr, Mat& blur)
{
	//***********************DFT*******************
	Mat plane[] = { scr, Mat::zeros(scr.size() , CV_32FC1) }; //创建通道，存储dft后的实部与虚部（CV_32F，必须为单通道数）
	Mat complexIm;
	merge(plane, 2, complexIm);//合并通道 （把两个矩阵合并为一个2通道的Mat类容器）
	dft(complexIm, complexIm);//进行傅立叶变换，结果保存在自身

	//***************中心化********************
	split(complexIm, plane);//分离通道（数组分离）
//    plane[0] = plane[0](Rect(0, 0, plane[0].cols & -2, plane[0].rows & -2));//这里为什么&上-2具体查看opencv文档
//    其实是为了把行和列变成偶数 -2的二进制是11111111.......10 最后一位是0
	int cx = plane[0].cols / 2; int cy = plane[0].rows / 2;//以下的操作是移动图像  (零频移到中心)
	Mat part1_r(plane[0], Rect(0, 0, cx, cy));  //元素坐标表示为(cx,cy)
	Mat part2_r(plane[0], Rect(cx, 0, cx, cy));
	Mat part3_r(plane[0], Rect(0, cy, cx, cy));
	Mat part4_r(plane[0], Rect(cx, cy, cx, cy));

	Mat temp;
	part1_r.copyTo(temp);  //左上与右下交换位置(实部)
	part4_r.copyTo(part1_r);
	temp.copyTo(part4_r);

	part2_r.copyTo(temp);  //右上与左下交换位置(实部)
	part3_r.copyTo(part2_r);
	temp.copyTo(part3_r);

	Mat part1_i(plane[1], Rect(0, 0, cx, cy));  //元素坐标(cx,cy)
	Mat part2_i(plane[1], Rect(cx, 0, cx, cy));
	Mat part3_i(plane[1], Rect(0, cy, cx, cy));
	Mat part4_i(plane[1], Rect(cx, cy, cx, cy));

	part1_i.copyTo(temp);  //左上与右下交换位置(虚部)
	part4_i.copyTo(part1_i);
	temp.copyTo(part4_i);

	part2_i.copyTo(temp);  //右上与左下交换位置(虚部)
	part3_i.copyTo(part2_i);
	temp.copyTo(part3_i);

	//*****************滤波器函数与DFT结果的乘积****************
	Mat blur_r, blur_i, BLUR;
	multiply(plane[0], blur, blur_r); //滤波（实部与滤波器模板对应元素相乘）
	multiply(plane[1], blur, blur_i);//滤波（虚部与滤波器模板对应元素相乘）
	Mat plane1[] = { blur_r, blur_i };
	merge(plane1, 2, BLUR);//实部与虚部合并

	  //*********************得到原图频谱图***********************************
	magnitude(plane[0], plane[1], plane[0]);//获取幅度图像，0通道为实部通道，1为虚部，因为二维傅立叶变换结果是复数
	plane[0] += Scalar::all(1);  //傅立叶变换后的图片不好分析，进行对数处理，结果比较好看
	log(plane[0], plane[0]);    // float型的灰度空间为[0，1])
	normalize(plane[0], plane[0], 1, 0, CV_MINMAX);  //归一化便于显示

	idft(BLUR, BLUR);    //idft结果也为复数
	split(BLUR, plane);//分离通道，主要获取通道
	magnitude(plane[0], plane[1], plane[0]);  //求幅值(模)
	normalize(plane[0], plane[0], 1, 0, CV_MINMAX);  //归一化便于显示
	return plane[0];//返回参数
}

//*****************理想低通滤波器***********************
Mat ideal_low_kernel(Mat& scr, float sigma)
{
	Mat ideal_low_pass(scr.size(), CV_32FC1); //，CV_32FC1
	float d0 = sigma;//半径D0越小，模糊越大；半径D0越大，模糊越小
	for (int i = 0; i < scr.rows; i++) {
		for (int j = 0; j < scr.cols; j++) {
			double d = sqrt(pow((i - scr.rows / 2), 2) + pow((j - scr.cols / 2), 2));//分子,计算pow必须为float型
			if (d <= d0) {
				ideal_low_pass.at<float>(i, j) = 1;
			}
			else {
				ideal_low_pass.at<float>(i, j) = 0;
			}
		}
	}
	string name = "理想低通滤波器d0=" + std::to_string(sigma);
	imshow(name, ideal_low_pass);
	return ideal_low_pass;
}

//理想低通滤波器
Mat CMFCApplication1Dlg::ideal_low_pass_filter(Mat& src, float sigma)
{

	Mat padded = image_make_border(src);
	Mat ideal_kernel = ideal_low_kernel(padded, sigma);
	Mat result = frequency_filter(padded, ideal_kernel);
	return result;
}


Mat butterworth_low_kernel(Mat& scr, float sigma, int n)
{
	Mat butterworth_low_pass(scr.size(), CV_32FC1); //，CV_32FC1
	double D0 = sigma;//半径D0越小，模糊越大；半径D0越大，模糊越小
	for (int i = 0; i < scr.rows; i++) {
		for (int j = 0; j < scr.cols; j++) {
			double d = sqrt(pow((i - scr.rows / 2), 2) + pow((j - scr.cols / 2), 2));//分子,计算pow必须为float型
			butterworth_low_pass.at<float>(i, j) = 1.0 / (1 + pow(d / D0, 2 * n));
		}
	}

	string name = "巴特沃斯低通滤波器d0=" + std::to_string(sigma) + "n=" + std::to_string(n);
	imshow(name, butterworth_low_pass);
	return butterworth_low_pass;
}

//巴特沃斯低通滤波器
Mat CMFCApplication1Dlg::butterworth_low_paass_filter(Mat& src, float d0, int n)
{
	//H = 1 / (1+(D/D0)^2n)    n表示巴特沃斯滤波器的次数
	//阶数n=1 无振铃和负值    阶数n=2 轻微振铃和负值  阶数n=5 明显振铃和负值   阶数n=20 与ILPF相似
	Mat padded = image_make_border(src);
	Mat butterworth_kernel = butterworth_low_kernel(padded, d0, n);
	Mat result = frequency_filter(padded, butterworth_kernel);
	return result;
}

Mat gaussian_low_pass_kernel(Mat scr, float sigma)
{
	Mat gaussianBlur(scr.size(), CV_32FC1); //，CV_32FC1
	float d0 = 2 * sigma * sigma;//高斯函数参数，越小，频率高斯滤波器越窄，滤除高频成分越多，图像就越平滑
	for (int i = 0; i < scr.rows; i++) {
		for (int j = 0; j < scr.cols; j++) {
			float d = pow(float(i - scr.rows / 2), 2) + pow(float(j - scr.cols / 2), 2);//分子,计算pow必须为float型
			gaussianBlur.at<float>(i, j) = expf(-d / d0);//expf为以e为底求幂（必须为float型）
		}
	}
	//    Mat show = gaussianBlur.clone();
	//    //归一化到[0,255]供显示
	//    normalize(show, show, 0, 255, NORM_MINMAX);
	//    //转化成CV_8U型
	//    show.convertTo(show, CV_8U);
	//    std::string pic_name = "gaussi" + std::to_string((int)sigma) + ".jpg";
	//    imwrite( pic_name, show);

	imshow("高斯低通滤波器", gaussianBlur);
	return gaussianBlur;
}

//高斯低通
Mat CMFCApplication1Dlg::gaussian_low_pass_filter(Mat& src, float d0)
{
	Mat padded = image_make_border(src);
	Mat gaussian_kernel = gaussian_low_pass_kernel(padded, d0);//理想低通滤波器
	Mat result = frequency_filter(padded, gaussian_kernel);
	return result;
}

Mat ideal_high_kernel(Mat& scr, float sigma)
{
	Mat ideal_high_pass(scr.size(), CV_32FC1); //，CV_32FC1
	float d0 = sigma;//半径D0越小，模糊越大；半径D0越大，模糊越小
	for (int i = 0; i < scr.rows; i++) {
		for (int j = 0; j < scr.cols; j++) {
			double d = sqrt(pow((i - scr.rows / 2), 2) + pow((j - scr.cols / 2), 2));//分子,计算pow必须为float型
			if (d <= d0) {
				ideal_high_pass.at<float>(i, j) = 0;
			}
			else {
				ideal_high_pass.at<float>(i, j) = 1;
			}
		}
	}
	string name = "理想高通滤波器d0=" + std::to_string(sigma);
	imshow(name, ideal_high_pass);
	return ideal_high_pass;
}

//理想高通滤波器
Mat CMFCApplication1Dlg::ideal_high_pass_filter(Mat& src, float sigma)
{
	Mat padded = image_make_border(src);
	Mat ideal_kernel = ideal_high_kernel(padded, sigma);
	Mat result = frequency_filter(padded, ideal_kernel);
	return result;
}

Mat butterworth_high_kernel(Mat& scr, float sigma, int n)
{
	Mat butterworth_low_pass(scr.size(), CV_32FC1); //，CV_32FC1
	double D0 = sigma;//半径D0越小，模糊越大；半径D0越大，模糊越小
	for (int i = 0; i < scr.rows; i++) {
		for (int j = 0; j < scr.cols; j++) {
			double d = sqrt(pow((i - scr.rows / 2), 2) + pow((j - scr.cols / 2), 2));//分子,计算pow必须为float型
			butterworth_low_pass.at<float>(i, j) = 1.0 / (1 + pow(D0 / d, 2 * n));
		}
	}

	string name = "巴特沃斯高通滤波器d0=" + std::to_string(sigma) + "n=" + std::to_string(n);
	imshow(name, butterworth_low_pass);
	return butterworth_low_pass;
}

//巴特沃斯高通滤波器
Mat CMFCApplication1Dlg::butterworth_high_paass_filter(Mat& src, float d0, int n)
{
	//H = 1 / (1+(D0/D)^2n)    n表示巴特沃斯滤波器的次数
	Mat padded = image_make_border(src);
	Mat butterworth_kernel = butterworth_high_kernel(padded, d0, n);
	Mat result = frequency_filter(padded, butterworth_kernel);
	return result;
}

Mat gaussian_high_pass_kernel(Mat scr, float sigma)
{
	Mat gaussianBlur(scr.size(), CV_32FC1); //，CV_32FC1
	float d0 = 2 * sigma * sigma;
	for (int i = 0; i < scr.rows; i++) {
		for (int j = 0; j < scr.cols; j++) {
			float d = pow(float(i - scr.rows / 2), 2) + pow(float(j - scr.cols / 2), 2);//分子,计算pow必须为float型
			gaussianBlur.at<float>(i, j) = 1 - expf(-d / d0);
		}
	}
	imshow("高斯高通滤波器", gaussianBlur);
	return gaussianBlur;
}

//高斯高通
Mat CMFCApplication1Dlg::gaussian_high_pass_filter(Mat& src, float d0)
{
	Mat padded = image_make_border(src);
	Mat gaussian_kernel = gaussian_high_pass_kernel(padded, d0);//理想低通滤波器
	Mat result = frequency_filter(padded, gaussian_kernel);
	return result;
}


void CMFCApplication1Dlg::OnDrawhist()
{
	// TODO: 在此添加命令处理程序代码
	if (IsExistImage()) {
		Mat srcHist;
		Drawhist(image, srcHist);
		namedWindow("srcHist", CV_WINDOW_AUTOSIZE);
		imshow("srcHist", srcHist);
	}

}


void CMFCApplication1Dlg::OnEqualizehist()
{
	// TODO: 在此添加命令处理程序代码
	Mat dstHist;
	Equalizehist(image, outImage);
	Drawhist(outImage, dstHist);
	namedWindow("dstHist", CV_WINDOW_AUTOSIZE);
	imshow("dstHist", dstHist);
	ShowImage(outImage, IDC_ShowPicture2);

}

void CMFCApplication1Dlg::Drawhist(Mat& src, Mat& dst)
{
	//namedWindow("output", CV_WINDOW_AUTOSIZE);
	//步骤一：分通道显示
	vector<Mat>bgr_planes;
	split(src, bgr_planes);
	//split(// 把多通道图像分为多个单通道图像 const Mat &src, //输入图像 Mat* mvbegin）// 输出的通道图像数组

	//步骤二：计算直方图
	int histsize = 256;
	float range[] = { 0,256 };
	const float* histRanges = { range };
	Mat b_hist, g_hist, r_hist;
	calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histsize, &histRanges, true, false);
	calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histsize, &histRanges, true, false);
	calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histsize, &histRanges, true, false);


	//归一化
	int hist_h = 500;//直方图的图像的高
	int hist_w = 512; //直方图的图像的宽
	int bin_w = hist_w / histsize;//直方图的等级
	Mat histImage(hist_w, hist_h, CV_8UC3, Scalar(0, 0, 0));//绘制直方图显示的图像
	normalize(b_hist, b_hist, 0, hist_h, NORM_MINMAX, -1, Mat());//归一化
	normalize(g_hist, g_hist, 0, hist_h, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, hist_h, NORM_MINMAX, -1, Mat());

	//步骤三：绘制直方图（render histogram chart）
	for (int i = 1; i < histsize; i++)
	{
		//绘制蓝色分量直方图
		line(histImage, Point((i - 1) * bin_w, hist_h - cvRound(b_hist.at<float>(i - 1))), Point((i)*bin_w, hist_h - cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0), 2, CV_AA);
		//绘制绿色分量直方图
		line(histImage, Point((i - 1) * bin_w, hist_h - cvRound(g_hist.at<float>(i - 1))), Point((i)*bin_w, hist_h - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0), 2, CV_AA);
		//绘制红色分量直方图
		line(histImage, Point((i - 1) * bin_w, hist_h - cvRound(r_hist.at<float>(i - 1))), Point((i)*bin_w, hist_h - cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255), 2, CV_AA);
	}
	dst = histImage;
	//imshow("output", histImage);
}

void CMFCApplication1Dlg::Equalizehist(Mat& src, Mat& dst)
{
	vector<Mat>channels;
	split(src, channels);

	Mat blue, green, red;
	blue = channels.at(0);
	green = channels.at(1);
	red = channels.at(2);
	//分别对BGR通道做直方图均衡化
	equalizeHist(blue, blue);
	equalizeHist(green, green);
	equalizeHist(red, red);
	//合并通道
	merge(channels, dst);

}


