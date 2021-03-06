
// MFCApplication1Dlg.h: 头文件
//

#pragma once
#include "afxwin.h"
#include "OpencvHelper.h"
#include "AngleResult.h"

// CMFCApplication1Dlg 对话框
class CMFCApplication1Dlg : public CDialog
{
// 构造
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// 标准构造函数
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAIN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//自定义
	void ShowImage(Mat image);
	void ShowInfo(const char* str, int code);
	int strtodata(unsigned char *str, unsigned char *data, int len, int flag);
	int chartoint(unsigned char chr, unsigned char *cint);
	static UINT ReceiveThread(void *param);

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnchoose();
	// 图片显示
//	CStatic m_pic_control;
	afx_msg void OnBnClickedIsFromCamera();
	void AddText(CString message);
//	bool is_from_camera;
	afx_msg void OnBnClickedProceed();
	afx_msg void OnBnClickedBtnsave();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedQuit();
	CString m_status;
	BOOL m_is_from_camera;
	afx_msg void OnBnClickedBtnConectcan();
	//自定义变量
	int m_connect;
	int m_devtype;
	int m_cannum;
	DWORD m_devind;
	afx_msg void OnBnClickedBtnSend();
	afx_msg void OnBnClickedBtnCalibrate();
	afx_msg void OnBnClickedBtnHomography();
	afx_msg void OnBnClickedBtnrecord();
};
