
// NetworkSecureDlg.h : header file
//

#pragma once
#include "Constant.h"
#include "ISPWarningDlg.h"
#include "SettingDlg.h"

// CNetworkSecureDlg dialog
class CNetworkSecureDlg : public CDialogEx
{
public:
	int GetNumVisibleLines(CRichEditCtrl* pCtrl);
	void AddLog(const char* csMsg, LogSeverity logSeverity); //New line + Timestamp
	void AppendLog(const char* csMsg, LogSeverity logSeverity); // Only content
	void CheckISP();
// Construction
public:
	CNetworkSecureDlg(CWnd* pParent = nullptr);	// standard constructor
	NOTIFYICONDATA m_nd;
	bool m_bStart;
	ISPWarningDlg* m_ISPDlg;
	SettingDlg* m_SettingDlg;
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NETWORKSECURE_DIALOG };
#endif
	
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;
	CBrush m_bkBrush;
	bool m_ISPPassed;
	CBitmap m_bitmapPassed;
	CBitmap m_bitmapFailed;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnTrayNotify(WPARAM, LPARAM);
	afx_msg LRESULT OnTaskCreate(WPARAM, LPARAM);
	bool ShowBalloonTip(LPCTSTR szMsg, LPCTSTR szTitle, DWORD dwInfoFlags = NIIF_INFO, UINT uTimeout = 2000);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnFileSetting();
	afx_msg void OnFileExit();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CRichEditCtrl m_richBox;
	CButton m_buttonStop;
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonStart();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CStatic m_static_isp;
	afx_msg void OnHelpViewhelp();
	afx_msg void OnHelpAboutnetworksecure();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};
