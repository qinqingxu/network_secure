#pragma once
#include "afxdialogex.h"


// ISPWarningDlg dialog

class ISPWarningDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ISPWarningDlg)

public:
	ISPWarningDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ISPWarningDlg();

	CBrush m_bkBrush;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ISP_ALERT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
};
