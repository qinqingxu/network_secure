// MyUpdaterDlg.h : header file
//

#if !defined(AFX_MYUPDATERDLG_H__3094C2C7_EEB7_451E_97C2_D36157FB2838__INCLUDED_)
#define AFX_MYUPDATERDLG_H__3094C2C7_EEB7_451E_97C2_D36157FB2838__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LinkStatic.h"
#include "ColorStatic.h"
#include "PictureEx.h"
#include "SpeedStatic.h"
/////////////////////////////////////////////////////////////////////////////
// CMyUpdaterDlg dialog

class CMyUpdaterDlg : public CDialog
{
// Construction
public:
	CMyUpdaterDlg(CWnd* pParent = NULL);	// standard constructor

	void ContractUS(void);
	void CancelUpdate(void);

	void SetSpeedText(CString strText);


	static DWORD _stdcall ThreadDownLoad(LPVOID);//下载的线程

	///工作函数
	void Work(void);

	bool GetInputParam(void);//得到命令行输入参数，如果参数正确返回true,否则返回false

	int m_nCurrentStep;///当前步骤
	void LoadingMove();

	int m_nVersion;//当前版本号
	CString m_strUpdateIni;//升级文件
	CString m_strAppName;///升级后要启动的程序名
// Dialog Data
	//{{AFX_DATA(CMyUpdaterDlg)
	enum { IDD = IDD_MYUPDATER_DIALOG };
	CStatic	m_static_total;
	CSpeedStatic	m_static_speed;
	CStatic	m_static_downloading;
	CProgressCtrl	m_proOneFile;
	CStatic	m_static_pic5;
	CStatic	m_static_pic4;
	CStatic	m_static_pic3;
	CStatic	m_static_pic2;
	CStatic	m_static_pic1;
	CColorStatic	m_static_5;
	CColorStatic	m_static_4;
	CColorStatic	m_static_3;
	CColorStatic	m_static_2;
	CPictureEx	m_static_loading;
	CColorStatic	m_static_1;
	CLinkStatic	m_static_cancel;
	CLinkStatic	m_static_contract_us;
	CProgressCtrl	m_pro;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyUpdaterDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMyUpdaterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYUPDATERDLG_H__3094C2C7_EEB7_451E_97C2_D36157FB2838__INCLUDED_)
