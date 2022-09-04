
// NetworkSecureDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "NetworkSecure.h"
#include "NetworkSecureDlg.h"
#include "afxdialogex.h"
#include "Constant.h"
#include "GlobalVariable.h"
#include "AboutDlg.h"
#include "HttpClient.h"
#include <Mmsystem.h>
#pragma comment(lib,"winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNetworkSecureDlg dialog
CNetworkSecureDlg::CNetworkSecureDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NETWORKSECURE_DIALOG, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNetworkSecureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT21, m_richBox);
}


BEGIN_MESSAGE_MAP(CNetworkSecureDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CNetworkSecureDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CNetworkSecureDlg::OnBnClickedOk)
	ON_COMMAND(ID_FILE_SETTING, &CNetworkSecureDlg::OnFileSetting)
	ON_COMMAND(ID_FILE_EXIT, &CNetworkSecureDlg::OnFileExit)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_MESSAGE(NOTIFYICON_TRY, OnTrayNotify)
	ON_REGISTERED_MESSAGE(WM_TASKBARCREATED, &CNetworkSecureDlg::OnTaskCreate)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CNetworkSecureDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_START, &CNetworkSecureDlg::OnBnClickedButtonStart)
	ON_COMMAND(ID_HELP_VIEWHELP, &CNetworkSecureDlg::OnHelpViewhelp)
	ON_COMMAND(ID_HELP_ABOUTNETWORKSECURE, &CNetworkSecureDlg::OnHelpAboutnetworksecure)
END_MESSAGE_MAP()



UINT ThreadAutoUpdate(LPVOID lp)
{
	CNetworkSecureDlg* pDlg = (CNetworkSecureDlg*)lp;
	string retHtml = "";
	string retError = "";
	if (HttpClient::GetHttpViaCURL((char*)G_VERSION_CHECK_URL, retHtml, retError))
	{
		CString newVersion = retHtml.c_str();
		newVersion.Replace("\r", "");
		newVersion.Replace("\n", "");
		newVersion.Trim();
		CString oldVersion = G_VERSION;

		if (newVersion > oldVersion)
		{
			if (pDlg->MessageBox("There is a new version for Network Secure, do you want to upgrade?", g_strWindowTitle, MB_ICONQUESTION | MB_YESNO) == IDYES)
			{
				ShellExecute(0, 0, "https://github.com/qinqingxu/network_secure", 0, 0, SW_SHOW);
			}
		}
	}

	return 0;
}


// CNetworkSecureDlg message handlers

BOOL CNetworkSecureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	
	// IDM_ABOUTBOX must be in the system command range.
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

	m_bkBrush.CreateSolidBrush(RGB(255, 255, 255));

	m_bitmapFailed.LoadBitmap(IDB_BITMAP_FAILED);
	m_bitmapPassed.LoadBitmap(IDB_BITMAP_PASSED);

	m_ISPDlg = new ISPWarningDlg(this);
	m_ISPDlg->Create(IDD_DIALOG_ISP_ALERT, this);

	m_SettingDlg = new SettingDlg(this);
	m_SettingDlg->Create(IDD_DIALOG_SETTING, this);


	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(false);


	m_bStart = false;
	m_ISPPassed = false;
	SetTimer(G_AUTOSTART_TIMER_ID, G_AUTOSTART_TIME, NULL);

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//Tray added
	m_nd.cbSize = sizeof(NOTIFYICONDATA);
	m_nd.hWnd = GetSafeHwnd();
	m_nd.uCallbackMessage = NOTIFYICON_TRY;
	m_nd.uID = IDR_MAINFRAME;
	m_nd.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nd.dwInfoFlags = NIIF_INFO;
	strcpy_s(m_nd.szTip, sizeof(m_nd.szTip) / sizeof(CHAR), "Launch");
	strcpy_s(m_nd.szInfoTitle, sizeof(m_nd.szInfoTitle) / sizeof(CHAR), "Network Secure");
	m_nd.uVersion = NOTIFYICON_VERSION;
	m_nd.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_SHOWTIP;
	Shell_NotifyIcon(NIM_ADD, &m_nd);
	ShowBalloonTip(g_strLaunch, g_strWindowTitle, NIIF_INFO);



	// Start up the upgrade thread, to check whether there is new version or not.
	AfxBeginThread(ThreadAutoUpdate, this);
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNetworkSecureDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		AboutDlg dlg;
		dlg.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

bool CNetworkSecureDlg::ShowBalloonTip(LPCTSTR szMsg, LPCTSTR szTitle, DWORD dwInfoFlags, UINT uTimeout)
{
	m_nd.cbSize = sizeof(NOTIFYICONDATA);
	m_nd.uTimeout = uTimeout;
	m_nd.dwInfoFlags = dwInfoFlags;
	m_nd.uFlags = NIF_INFO;
	m_nd.uVersion = NOTIFYICON_VERSION;
	_tcscpy_s(m_nd.szTip, sizeof(m_nd.szTip) / sizeof(TCHAR), szMsg);
	_tcscpy_s(m_nd.szInfoTitle, sizeof(m_nd.szInfoTitle) / sizeof(TCHAR), szTitle);
	Shell_NotifyIcon(NIM_MODIFY, &m_nd);

	return 0 != Shell_NotifyIcon(NIN_BALLOONSHOW, &m_nd);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNetworkSecureDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CNetworkSecureDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNetworkSecureDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnCancel();
}


void CNetworkSecureDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CNetworkSecureDlg::OnFileSetting()
{
	m_SettingDlg->LoadConfiguration();
	m_SettingDlg->ShowWindow(SW_SHOW);
}


void CNetworkSecureDlg::OnFileExit()
{
	PostMessage(WM_CLOSE, 0, 0);
}


void CNetworkSecureDlg::OnClose()
{
	if (MessageBox("Do you want to exit?", NULL, MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2) == IDYES)
	{
		Shell_NotifyIcon(NIM_DELETE, &m_nd);

		EndDialog(G_DIALOG_CLOSE_SUCCESS);
	}
	else
	{
		return;
	}

	CDialogEx::OnClose();
}

void CNetworkSecureDlg::CheckISP()
{
	if (g_ISPObserver.CheckISPValid(g_configurator.GetISPSearchInfo(), g_configurator.GetProxyInfo()))
	{
		if (!m_ISPPassed)
		{
			AddLog("ISP check done, it is connected with expected ISP network", LOG_SUCCESS);
			m_ISPPassed = true;
			m_ISPDlg->ShowWindow(SW_HIDE);
			((CStatic*)GetDlgItem(IDC_STATIC_ISP_ICON))->SetBitmap(m_bitmapPassed);
		}
	}
	else
	{
		CString str;
		str.Format("ISP check failed, the reason is: %s", g_ISPObserver.GetLastError().c_str());
		AddLog(str, LOG_WARNING);
		m_ISPPassed = false;
		m_ISPDlg->ShowWindow(SW_SHOW);
		m_ISPDlg->SetForegroundWindow();
		((CStatic*)GetDlgItem(IDC_STATIC_ISP_ICON))->SetBitmap(m_bitmapFailed);
		ShowBalloonTip(g_strISPWarning, g_strWindowTitle, NIIF_WARNING);

		if (g_configurator.GetSoundInfo().m_playSound)
		{
			PlaySound(g_configurator.GetSoundInfo().m_soundFile.c_str(), NULL, SND_FILENAME | SND_ASYNC);
		}

	}
}

LRESULT CNetworkSecureDlg::OnTrayNotify(WPARAM wParam, LPARAM lParam)
{
	UINT uMsg = (UINT)lParam;
	switch (uMsg)
	{
		case WM_LBUTTONDOWN:
		{
			this->ShowWindow(SW_SHOW);
			SetForegroundWindow();
			break;
		}
	
	}
	return TRUE;
}

void CNetworkSecureDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent)
	{
	case G_SCAN_TIMER_ID:
		KillTimer(G_SCAN_TIMER_ID);
		CheckISP();
		SetTimer(G_SCAN_TIMER_ID, g_configurator.GetScanInterval(), NULL);
		break;

	case G_AUTOSTART_TIMER_ID:
		KillTimer(G_AUTOSTART_TIMER_ID);
		AddLog("System initilizing.", LOG_INFO);
		OnBnClickedButtonStart();
		break;
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CNetworkSecureDlg::OnBnClickedButtonStart()
{
	SetTimer(G_SCAN_TIMER_ID, 500, NULL); //Once click the button to start the scan, we expected it can start the task immediately.
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(true);
	AddLog("Start scan task.", LOG_INFO);
	m_bStart = true;
	// TODO: Add your control notification handler code here
}


void CNetworkSecureDlg::OnBnClickedButtonStop()
{
	if (MessageBox("Do you want to stop the scan task?", NULL, MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2) == IDNO)
	{
		return;
	}

	KillTimer(G_SCAN_TIMER_ID);
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(false);
	AddLog("Scan task stopped.", LOG_INFO);
	m_bStart = false;
	// TODO: Add your control notification handler code here
}


HBRUSH CNetworkSecureDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_DLG ||
		nCtlColor == CTLCOLOR_BTN ||
		nCtlColor == CTLCOLOR_STATIC)
	{
		return m_bkBrush;
	}

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}


void CNetworkSecureDlg::AddLog(const char* csMsg, LogSeverity logSeverity) //New line + Timestamp
{
	SYSTEMTIME ti;
	GetLocalTime(&ti);

	CString strContent;
	strContent.Format("[%04d-%02d-%02d %02d:%02d:%02d]: %s\n",
		ti.wYear, ti.wMonth, ti.wDay,
		ti.wHour, ti.wMinute, ti.wSecond,
		csMsg);

	AppendLog(strContent, logSeverity);
}

void CNetworkSecureDlg::AppendLog(const char* csMsg, LogSeverity logSeverity)
{
	long nVisible = 0;
	long nInsertionPoint = 0;
	CHARFORMAT cf;
	m_richBox.GetSelectionCharFormat(cf);
	// Initialize character format structure
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask |= CFM_BOLD;
	cf.dwEffects &= ~CFE_AUTOCOLOR;
	cf.dwMask |= CFM_COLOR;
	switch (logSeverity)
	{
	case LOG_INFO:
		cf.crTextColor = COLOR_INFO;
		break;
	case LOG_WARNING:
		cf.crTextColor = COLOR_WARNING;
		break;
	case LOG_SUCCESS:
		cf.crTextColor = COLOR_SUCCESS;
		break;
	default:
		cf.crTextColor = COLOR_INFO;
		break;
	}
	cf.dwMask |= CFM_SIZE;
	cf.yHeight = 200;
	cf.dwMask |= CFM_FACE;
	_tcscpy_s(cf.szFaceName, _T("Calibri"));//设置字体
	// Set insertion point to end of text
	nInsertionPoint = m_richBox.GetWindowTextLength();
	m_richBox.SetSel(nInsertionPoint, -1);

	// Set the character format
	m_richBox.SetSelectionCharFormat(cf);

	m_richBox.ReplaceSel(csMsg);

	nVisible = GetNumVisibleLines(&m_richBox);


	if (&m_richBox != m_richBox.GetFocus())
	{
		m_richBox.LineScroll(INT_MAX);
		m_richBox.LineScroll(1 - nVisible);
	}
}


int CNetworkSecureDlg::GetNumVisibleLines(CRichEditCtrl* pCtrl)
{
	CRect rect;
	long nFirstChar, nLastChar;
	long nFirstLine, nLastLine;

	// Get client rect of rich edit control
	pCtrl->GetClientRect(rect);

	// Get character index close to upper left corner
	nFirstChar = pCtrl->CharFromPos(CPoint(0, 0));

	// Get character index close to lower right corner
	nLastChar = pCtrl->CharFromPos(CPoint(rect.right, rect.bottom));
	if (nLastChar < 0)
	{
		nLastChar = pCtrl->GetTextLength();
	}

	// Convert to lines
	nFirstLine = pCtrl->LineFromChar(nFirstChar);
	nLastLine = pCtrl->LineFromChar(nLastChar);

	return (nLastLine - nFirstLine);
}

void CNetworkSecureDlg::OnHelpViewhelp()
{
	ShellExecute(0, 0, "https://github.com/qinqingxu/network_secure", 0, 0, SW_SHOW);
}


void CNetworkSecureDlg::OnHelpAboutnetworksecure()
{
	// TODO: Add your command handler code here
	AboutDlg dlg;
	dlg.DoModal();
}


BOOL CNetworkSecureDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN &&
		pMsg->wParam == VK_ESCAPE)
	{
		PostMessage(WM_CLOSE, 0, 0);
		return true;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


LRESULT CNetworkSecureDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	if (message == WM_SYSCOMMAND)
	{
		if (wParam == SC_MINIMIZE)
		{
			m_nd.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_INFO;
			Shell_NotifyIcon(NIM_ADD, &m_nd);
			Shell_NotifyIcon(NIM_MODIFY, &m_nd);
			ShowWindow(SW_HIDE);
			return 0;
		}
	}

	return CDialogEx::WindowProc(message, wParam, lParam);
}

LRESULT CNetworkSecureDlg::OnTaskCreate(WPARAM wParam, LPARAM lParam)
{
	m_nd.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_INFO;
	Shell_NotifyIcon(NIM_ADD, &m_nd);

	return TRUE;
}