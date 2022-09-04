// ISPWarningDlg.cpp : implementation file
//

#include "pch.h"
#include "NetworkSecure.h"
#include "afxdialogex.h"
#include "ISPWarningDlg.h"


// ISPWarningDlg dialog

IMPLEMENT_DYNAMIC(ISPWarningDlg, CDialogEx)

ISPWarningDlg::ISPWarningDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ISP_ALERT, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif
}

ISPWarningDlg::~ISPWarningDlg()
{
}

void ISPWarningDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ISPWarningDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ISPWarningDlg::OnBnClickedOk)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// ISPWarningDlg message handlers


void ISPWarningDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


HBRUSH ISPWarningDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	if (nCtlColor == CTLCOLOR_DLG ||
		nCtlColor == CTLCOLOR_BTN ||
		nCtlColor == CTLCOLOR_STATIC)
	{
		return m_bkBrush;
	}
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}


BOOL ISPWarningDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_bkBrush.CreateSolidBrush(RGB(255, 255, 255));

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
