// MyUpdaterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyUpdater.h"
#include "MyUpdaterDlg.h"

#include "BindStatusCallback.h"
#include "IniClass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About


/////////////////////////////////////////////////////////////////////////////
// CMyUpdaterDlg dialog

CMyUpdaterDlg::CMyUpdaterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyUpdaterDlg::IDD, pParent)
{

	m_nCurrentStep = 0;///当前步骤
	
	m_nVersion = 0;
		
	m_strUpdateIni = "";

	//{{AFX_DATA_INIT(CMyUpdaterDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyUpdaterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyUpdaterDlg)
	DDX_Control(pDX, IDC_STATIC_TOTAL, m_static_total);
	DDX_Control(pDX, IDC_STATIC_SPEED, m_static_speed);
	DDX_Control(pDX, IDC_STATIC_DOWNLOADING, m_static_downloading);
	DDX_Control(pDX, IDC_PROGRESS2, m_proOneFile);
	DDX_Control(pDX, IDC_STATIC_PIC5, m_static_pic5);
	DDX_Control(pDX, IDC_STATIC_PIC4, m_static_pic4);
	DDX_Control(pDX, IDC_STATIC_PIC3, m_static_pic3);
	DDX_Control(pDX, IDC_STATIC_PIC2, m_static_pic2);
	DDX_Control(pDX, IDC_STATIC_PIC1, m_static_pic1);
	DDX_Control(pDX, IDC_STATIC_5, m_static_5);
	DDX_Control(pDX, IDC_STATIC_4, m_static_4);
	DDX_Control(pDX, IDC_STATIC_3, m_static_3);
	DDX_Control(pDX, IDC_STATIC_2, m_static_2);
	DDX_Control(pDX, IDC_STATIC_LOADING, m_static_loading);
	DDX_Control(pDX, IDC_STATIC_1, m_static_1);
	DDX_Control(pDX, IDC_STATIC_CANCEL, m_static_cancel);
	DDX_Control(pDX, IDC_STATIC_CONTRACT_US, m_static_contract_us);
	DDX_Control(pDX, IDC_PROGRESS1, m_pro);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyUpdaterDlg, CDialog)
	//{{AFX_MSG_MAP(CMyUpdaterDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_SYSCOMMAND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyUpdaterDlg message handlers

BOOL CMyUpdaterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	///读取动画资源
	if (m_static_loading.Load(MAKEINTRESOURCE(IDR_GIFTYPE_LOADING), LPCTSTR("GIFTYPE")))
	{
		CRect rect(0, 0, m_static_loading.GetSize().cx, m_static_loading.GetSize().cy);
		m_static_loading.GetPaintRect(&rect);
		m_static_loading.Draw();
	}

	m_static_pic1.ShowWindow(SW_HIDE);
	m_static_pic2.ShowWindow(SW_HIDE);
	m_static_pic3.ShowWindow(SW_HIDE);
	m_static_pic4.ShowWindow(SW_HIDE);
	m_static_pic5.ShowWindow(SW_HIDE);
	m_static_loading.ShowWindow(SW_HIDE);

	m_static_cancel.m_voidfunction = CancelUpdate;
	m_static_contract_us.m_voidfunction = ContractUS;

	if (!GetInputParam())
	{
		MessageBox("输入命令参数有误", g_strWindowTitle, MB_ICONERROR);

		EndDialog(100);

		return TRUE;
	}

	HANDLE hd = CreateThread(
		NULL,
		0,
		(LPTHREAD_START_ROUTINE)ThreadDownLoad,
		(LPVOID)this,
		0,
		NULL);

	if (hd == NULL)
	{
		MessageBox("开起下载线程失败\n请打开我们的网站,直接下载并安装最新程序", g_strWindowTitle, MB_ICONERROR);
		ShellExecute(NULL, "open", g_strContractUSWeb, NULL, NULL, SW_MAXIMIZE);

		EndDialog(-1);

		return TRUE;
	}
	else
	{
		CloseHandle(hd);
	}
	

	////设置单个文件
	m_proOneFile.SetRange(0, 100);
	m_proOneFile.SetPos(0);
	
	// Add "About..." menu item to system menu.

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyUpdaterDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyUpdaterDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMyUpdaterDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

BOOL CMyUpdaterDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class

	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
	{
		return true;
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}


bool CMyUpdaterDlg::GetInputParam(void)//得到命令行输入参数，如果参数正确返回true,否则返回false
{
	CString strCmdLine = AfxGetApp()->m_lpCmdLine;

	CString str;

	if (strCmdLine == "")
	{
		return false;
	}

	int nStart = 0;
	int nEnd = 0;

	int nLastEnd = 0;

	//找到第一个参数
	//--------------------------------------------------------------
	nStart = strCmdLine.Find('[', 0);

	if (nStart < 0)
	{
		return false;
	}

	nEnd = strCmdLine.Find(']', nStart);

	if (nEnd < 0)
	{
		return false;
	}

	str = strCmdLine.Mid(nStart + 1, nEnd - nStart - 1);

	if (str == "")
	{
		return false;
	}

	//得到版本号
	m_nVersion = atoi(str.GetBuffer(0));

	nLastEnd = nEnd;

	nStart = 0;



	//找到第二个参数
	nStart = strCmdLine.Find('[', nLastEnd);
	
	if (nStart < 0)
	{
		return false;
	}
	
	nEnd = strCmdLine.Find(']', nStart);
	
	if (nEnd < 0)
	{
		return false;
	}
	
	str = strCmdLine.Mid(nStart + 1, nEnd - nStart - 1);
	
	if (str == "")
	{
		return false;
	}
	else
	{
		//得到升级文件
		m_strUpdateIni = str;
	}

	nLastEnd = nEnd;
	
	nStart = 0;

	//找到第三个参数
	nStart = strCmdLine.Find('[', nLastEnd);
	
	if (nStart < 0)
	{
		return false;
	}
	
	nEnd = strCmdLine.Find(']', nStart);
	
	if (nEnd < 0)
	{
		return false;
	}
	
	str = strCmdLine.Mid(nStart + 1, nEnd - nStart - 1);
	
	if (str == "")
	{
		return false;
	}
	else
	{
		///得到应用程序的名字
		m_strAppName = str;
	}

	return true;
}

void CMyUpdaterDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	//CDialog::OnClose();
}


DWORD _stdcall CMyUpdaterDlg::ThreadDownLoad(LPVOID lp)//下载的线程
{
	CMyUpdaterDlg *p = (CMyUpdaterDlg *)lp;

	if (p == NULL)
	{
		return 0;
	}
	else
	{
		p->Work();
	}

	p->EndDialog(100);

	return 0;
}




void CMyUpdaterDlg::LoadingMove()
{
	CRect rect;

	switch(m_nCurrentStep)
	{
	case 0:
		{
			m_nCurrentStep++;
			m_static_1.SetTextColor(G_TEXT_COLOR_DOING);

			m_static_pic1.GetWindowRect(&rect);
			ScreenToClient(&rect);

			m_static_loading.MoveWindow(&rect);
			m_static_loading.ShowWindow(SW_SHOW);
		}
		break;
	case 1:
		{
			///finish
			m_static_pic1.ShowWindow(SW_SHOW);
			m_static_1.SetTextColor(G_TEXT_COLOR_DONE);

			m_nCurrentStep++;
			m_static_2.SetTextColor(G_TEXT_COLOR_DOING);
			
			m_static_pic2.GetWindowRect(&rect);
			ScreenToClient(&rect);
			
			m_static_loading.MoveWindow(&rect);
			m_static_loading.ShowWindow(SW_SHOW);
		}
		break;
	case 2:
		{
			///finish
			m_static_pic2.ShowWindow(SW_SHOW);
			m_static_2.SetTextColor(G_TEXT_COLOR_DONE);
			
			m_nCurrentStep++;
			m_static_3.SetTextColor(G_TEXT_COLOR_DOING);
			
			m_static_pic3.GetWindowRect(&rect);
			ScreenToClient(&rect);
			
			m_static_loading.MoveWindow(&rect);
			m_static_loading.ShowWindow(SW_SHOW);
		}
	    break;
	case 3:
		{
			///finish
			m_static_pic3.ShowWindow(SW_SHOW);
			m_static_3.SetTextColor(G_TEXT_COLOR_DONE);

			///让按钮停止工作
			m_static_cancel.m_bWorking = false;
			m_static_cancel.EnableWindow(false);
			m_static_cancel.RedrawWindow();
			
			m_nCurrentStep++;
			m_static_4.SetTextColor(G_TEXT_COLOR_DOING);
			
			m_static_pic4.GetWindowRect(&rect);
			ScreenToClient(&rect);
			
			m_static_loading.MoveWindow(&rect);
			m_static_loading.ShowWindow(SW_SHOW);
		}
	    break;
	case 4:
		{
			///finish
			m_static_pic4.ShowWindow(SW_SHOW);
			m_static_4.SetTextColor(G_TEXT_COLOR_DONE);
			
			m_nCurrentStep++;
			m_static_pic5.ShowWindow(SW_SHOW);
			m_static_5.SetTextColor(G_TEXT_COLOR_DONE);

			m_static_loading.ShowWindow(SW_HIDE);
		}
		break;
	default:
		MessageBox("升级程序内部发生错误\n请打开我们的网站,直接下载并安装最新程序", g_strWindowTitle, MB_ICONERROR);
		ShellExecute(NULL, "open", g_strContractUSWeb, NULL, NULL, SW_MAXIMIZE);
	    break;
	}

	RedrawWindow();
}


void CMyUpdaterDlg::ContractUS(void)
{
	ShellExecute(NULL, "open", g_strContractUSWeb, NULL, NULL, SW_MAXIMIZE);
}


void CMyUpdaterDlg::CancelUpdate(void)
{
	if (m_nCurrentStep > 3)
	{
		return;
	}
	else
	{
		EndDialog(100);
	}
}


///工作函数
void CMyUpdaterDlg::Work(void)
{
	char chTempPath[MAX_PATH];

	CString strPath;

	if (GetTempPath(MAX_PATH, chTempPath) == 0)
	{
		strPath = GetAppPath();

		strcpy(chTempPath, strPath.GetBuffer(0));
	}

	if(chTempPath[strlen(chTempPath) -1] != '\\')
	{
		strcat(chTempPath, "\\");
	}

	//生成临时目录
	strcat(chTempPath, "MyUpdaterDir\\");

	CString strCurrentDir = GetAppPath();

	//得到升级程序所在的目录
	CString strTmpDir = chTempPath;

	if (!MakeDir(chTempPath))
	{
		CString strTmp;
		strTmp.Format("生成临时下载目录 \"%s\" 失败,升级取消\n请打开我们的网站,直接下载并安装最新程序", chTempPath);

		MessageBox(chTempPath, g_strWindowTitle, MB_ICONERROR);
		ShellExecute(NULL, "open", g_strContractUSWeb, NULL, NULL, SW_MAXIMIZE);

		return;
	}

	strPath = chTempPath;
	strPath += "\\Update.ini";

	//第一步
	LoadingMove();
	//下载INI文件
	int ret = URLDownloadToFile(NULL, m_strUpdateIni, strPath, 0, NULL); 
	
	if (ret == S_OK) //如果下载成功 
	{

		//第二步
		LoadingMove();

		CIni ini;

		CString str;

		int nNewVersion = 0;

		//以下是读取四个版本信息的
		//--------------------------------------------------------------------------------
		if (!ini.ReadString("Version", "VersionID", str, strPath.GetBuffer(0)))
		{
			DeleteDir(chTempPath);

			MessageBox("升级信息有误,请与我们联系\n请打开我们的网站,直接下载并安装最新程序", g_strWindowTitle, MB_ICONERROR);
			ShellExecute(NULL, "open", g_strContractUSWeb, NULL, NULL, SW_MAXIMIZE);

			return;
		}

		nNewVersion = atoi(str.GetBuffer(0));

		if (nNewVersion <= m_nVersion)
		{
			DeleteDir(chTempPath);
			
			MessageBox("当前已经是最新版,不需要再升级了", g_strWindowTitle, MB_OK);

			
			return;
		}

		int nCount = 0;

		int i;

		//以下是读取要下载的文件的部分

		if (!ini.ReadString("AddFiles", "AddFilesLen", str, strPath.GetBuffer(0)))
		{
			DeleteDir(chTempPath);

			MessageBox("升级信息中无更新文件\n请打开我们的网站,直接下载并安装最新程序", g_strWindowTitle, MB_ICONERROR);
			ShellExecute(NULL, "open", g_strContractUSWeb, NULL, NULL, SW_MAXIMIZE);

			return;
		}

		//得到相下载的文件的个数
		nCount = atoi(str.GetBuffer(0));

		if (nCount <= 0)
		{
			DeleteDir(chTempPath);
			
			MessageBox("升级信息中更新文件的个数有误\n请打开我们的网站,直接下载并安装最新程序", g_strWindowTitle, MB_ICONERROR);
			ShellExecute(NULL, "open", g_strContractUSWeb, NULL, NULL, SW_MAXIMIZE);
			
			return;
		}

		//下载后的目标文件的集合
		CStringArray arrayStrDest;
		CStringArray arrayStrSrc;

		m_pro.SetRange(0, nCount);

		m_pro.SetPos(0);


		for (i = 1; i <= nCount; i++)
		{
			CString strUrl;
			CString strDest;

			CString strTmpRead;

			////////////////////////////////////////////////
			strTmpRead.Format("AddFilesSrc%d", i);

			if (!ini.ReadString("AddFiles", strTmpRead, strUrl, strPath.GetBuffer(0)))
			{
				DeleteDir(chTempPath);

				
				MessageBox("升级信息有误\n请打开我们的网站,直接下载并安装最新程序", g_strWindowTitle, MB_ICONERROR);
				ShellExecute(NULL, "open", g_strContractUSWeb, NULL, NULL, SW_MAXIMIZE);
				
				return;
			}

			arrayStrSrc.Add(strUrl);

			strTmpRead.Format("AddFilesDest%d", i);
			
			if (!ini.ReadString("AddFiles", strTmpRead, strDest, strPath.GetBuffer(0)))
			{
				DeleteDir(chTempPath);

				MessageBox("升级信息有误\n请打开我们的网站,直接下载并安装最新程序", g_strWindowTitle, MB_ICONERROR);
				ShellExecute(NULL, "open", g_strContractUSWeb, NULL, NULL, SW_MAXIMIZE);
				
				return;
			}

			arrayStrDest.Add(strDest);
			////////////////////////////////////////////////

		}

		///第三步，下载文件
		LoadingMove();

		for (i = 0; i < arrayStrSrc.GetSize(); i++)
		{
			CString strFormat;

			//总的进度条
			m_pro.SetPos(i);
			strFormat.Format("总进度: %d / %d", i + 1, arrayStrSrc.GetSize());
			m_static_total.SetWindowText(strFormat);


			if (!MakeDir(GetPathFromFileName(strTmpDir + arrayStrDest[i])))
			{
				DeleteDir(chTempPath);

				MessageBox("创建下载所需要的临时目录失败\n请打开我们的网站,直接下载并安装最新程序", g_strWindowTitle, MB_ICONERROR);
				ShellExecute(NULL, "open", g_strContractUSWeb, NULL, NULL, SW_MAXIMIZE);

				return;
			}

			///显示当前下载的文件
			
			strFormat.Format("当前正在下载: %s", GetFileNameFromPath(strTmpDir + arrayStrDest[i]));
			m_static_downloading.SetWindowText(strFormat);

			///回调函数
			CCallback callback;
			callback.SetDepend(&m_proOneFile, &m_static_speed);

			HRESULT   hr = URLDownloadToFile(NULL, arrayStrSrc[i], (strTmpDir + arrayStrDest[i]), 0, &callback);

			if (FAILED(hr) )
			{
				DeleteDir(chTempPath);

				strFormat.Format("文件 \"%s\" 下载失败\n请打开我们的网站,直接下载并安装最新程序", GetFileNameFromPath(strTmpDir + arrayStrDest[i]));
				MessageBox(strFormat, g_strWindowTitle, MB_ICONERROR);
				ShellExecute(NULL, "open", g_strContractUSWeb, NULL, NULL, SW_MAXIMIZE);
				return;
			}

			
		}

		//收尾工作
		m_proOneFile.SetPos(0);
		m_static_speed.SetWindowText("");
		m_static_downloading.SetWindowText("");

		///第四步，复制文件
		LoadingMove();
		
		for (i = 0; i < arrayStrDest.GetSize(); i++)
		{
			if (!MakeDir(GetPathFromFileName(strCurrentDir + arrayStrDest[i])))
			{
				DeleteDir(chTempPath);

				MessageBox("创建更新所需要的目标目录有误\n请打开我们的网站,直接下载并安装最新程序", g_strWindowTitle, MB_ICONERROR);
				ShellExecute(NULL, "open", g_strContractUSWeb, NULL, NULL, SW_MAXIMIZE);

				return;
			}
			CString strSrc = strTmpDir + arrayStrDest[i];
			CString strDest = strCurrentDir + arrayStrDest[i];
			bool bOk = CopyFile(strTmpDir + arrayStrDest[i], strCurrentDir + arrayStrDest[i], false);

			while (!bOk)
			{
				if (MessageBox("文件: \"" + strCurrentDir + arrayStrDest[i] + "\" 无法更新,请保证该文件没有被打开!", g_strWindowTitle, MB_RETRYCANCEL) == IDRETRY)
				{
					bOk = CopyFile(strTmpDir + arrayStrDest[i], strCurrentDir + arrayStrDest[i], false);
				}
				else
				{
					break;
				}
			}
		}
////第五步，完成
		LoadingMove();

		DeleteDir(chTempPath);

		MessageBox("升级完成", g_strWindowTitle, MB_OK);
		
		///升级后打开主程序
		ShellExecute(NULL, "open", m_strAppName, NULL, NULL, SW_SHOWNORMAL);
	}
	else
	{
		DeleteDir(chTempPath);

		MessageBox("升级文件下载失败\n请打开我们的网站,直接下载并安装最新程序", g_strWindowTitle, MB_ICONERROR);
		ShellExecute(NULL, "open", g_strContractUSWeb, NULL, NULL, SW_MAXIMIZE);

	}
}

void CMyUpdaterDlg::SetSpeedText(CString strText)
{
	m_static_speed.SetWindowText(strText);
}
