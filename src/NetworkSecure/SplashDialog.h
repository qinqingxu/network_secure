#pragma once
#include "afxdialogex.h"


// SplashDialog dialog

class SplashDialog : public CDialog
{
	DECLARE_DYNAMIC(SplashDialog)

public:
	SplashDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~SplashDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SPLASH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg LRESULT OnNcHitTest(CPoint point);
};
