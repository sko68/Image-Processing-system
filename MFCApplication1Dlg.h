
// MFCApplication1Dlg.h: 头文件
//

#pragma once
#include <opencv2/core/core.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
#include<opencv2/highgui/highgui_c.h>
#include <opencv2/highgui/highgui.hpp>  
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;


// CMFCApplication1Dlg 对话框
class CMFCApplication1Dlg : public CDialogEx
{
	// 构造
public:
	CMFCApplication1Dlg(CWnd* pParent = nullptr);	// 标准构造函数


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


public:

	void LogTransform1(cv::Mat& src, cv::Mat& dst);

	// 实现
protected:
	HICON m_hIcon;
	CMenu menu;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedOpenpicture();

	void ShowImage(Mat image, int IDCNum);

	afx_msg void OnBnClickedClosepicture();

	boolean IsExistImage();

	afx_msg void OnSave();
	void Save(/*UINT ID*/);

	afx_msg void OnOpenfile();

	afx_msg void OnClose();

	afx_msg void OnLog();

	afx_msg void OnExponent();
	void ExpEnhance(Mat& imgage, Mat& dst, float r);

	afx_msg void OnReverse();
	void Reverse(Mat& image, Mat& dst);

	afx_msg void OnSegmented();
	void Segmented(Mat& image, Mat& dst);

	afx_msg void OnBoxfilter();
	afx_msg void OnBlur();
	afx_msg void OnGaussianblur();
	afx_msg void OnMedianblur();
	afx_msg void OnBilateralfilter();

	afx_msg void OnRoberts();
	void Roberts(Mat& image, Mat& dst);

	afx_msg void OnPrewitt();
	void Prewitt(Mat& image, Mat& dst);

	afx_msg void OnSobel();
	void Sobel(Mat& image, Mat& dst);

	afx_msg void OnLaplace();

	afx_msg void OnIdealLowPass();
	Mat ideal_low_pass_filter(Mat& src, float sigma);

	afx_msg void OnButterworthLowPass();
	Mat butterworth_low_paass_filter(Mat& src, float d0, int n);

	afx_msg void OnGaussianLowPass();
	Mat gaussian_low_pass_filter(Mat& src, float d0);

	afx_msg void OnIdealHighPass();
	Mat ideal_high_pass_filter(Mat& src, float sigma);

	afx_msg void OnButterworthHighPass();
	Mat butterworth_high_paass_filter(Mat& src, float d0, int n);

	afx_msg void OnGaussianHighPass();
	Mat gaussian_high_pass_filter(Mat& src, float d0);

	afx_msg void OnDrawhist();
	void Drawhist(Mat& src, Mat& dst);

	afx_msg void OnEqualizehist();
	void Equalizehist(Mat& src, Mat& dst);

};
