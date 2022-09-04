// SplashDialog.cpp : implementation file
//

#include "pch.h"
#include "NetworkSecure.h"
#include "afxdialogex.h"
#include "SplashDialog.h"
#include "Constant.h"
#include "HttpClient.h"

// SplashDialog dialog

IMPLEMENT_DYNAMIC(SplashDialog, CDialog)

SplashDialog::SplashDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_SPLASH, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

SplashDialog::~SplashDialog()
{
}

void SplashDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SplashDialog, CDialog)
	ON_BN_CLICKED(IDCANCEL, &SplashDialog::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &SplashDialog::OnBnClickedOk)
	ON_WM_TIMER()
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()


// SplashDialog message handlers


void SplashDialog::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	//CDialog::OnCancel();
}


void SplashDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialog::OnOK();
}


BOOL SplashDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	
	//Start the timer to trigger the upgrade check
	SetTimer(G_SPLASH_CLOSE_TIMER_ID, G_SPLASH_CLOSE_DURATION, NULL);
	// TODO:  Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void SplashDialog::OnTimer(UINT_PTR nIDEvent)
{
	
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == G_SPLASH_CLOSE_TIMER_ID)
	{
		KillTimer(G_SPLASH_CLOSE_TIMER_ID);
		EndDialog(G_DIALOG_CLOSE_SUCCESS);
	}
	CDialog::OnTimer(nIDEvent);
}


LRESULT SplashDialog::OnNcHitTest(CPoint point)
{
	LRESULT nHitTest = CDialog::OnNcHitTest(point);

	return (nHitTest == HTCLIENT) ? HTCAPTION : nHitTest;
}
