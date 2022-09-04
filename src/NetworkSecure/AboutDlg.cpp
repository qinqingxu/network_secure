// AboutDlg.cpp : implementation file
//

#include "pch.h"
#include "NetworkSecure.h"
#include "afxdialogex.h"
#include "AboutDlg.h"
#include "Constant.h"

// AboutDlg dialog

IMPLEMENT_DYNAMIC(AboutDlg, CDialogEx)

AboutDlg::AboutDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ABOUT, pParent)
{

}

AboutDlg::~AboutDlg()
{
}

void AboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AboutDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &AboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// AboutDlg message handlers


void AboutDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


BOOL AboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	GetDlgItem(IDC_STATIC_VERSION)->SetWindowText(G_VERSION);
	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
