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

	m_nCurrentStep = 0;///��ǰ����
	
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

	///��ȡ������Դ
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
		MessageBox("���������������", g_strWindowTitle, MB_ICONERROR);

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
		MessageBox("���������߳�ʧ��\n������ǵ���վ,ֱ�����ز���װ���³���", g_strWindowTitle, MB_ICONERROR);
		ShellExecute(NULL, "open", g_strContractUSWeb, NULL, NULL, SW_MAXIMIZE);

		EndDialog(-1);

		return TRUE;
	}
	else
	{
		CloseHandle(hd);
	}
	

	////���õ����ļ�
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


bool CMyUpdaterDlg::GetInputParam(void)//�õ�������������������������ȷ����true,���򷵻�false
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

	//�ҵ���һ������
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

	//�õ��汾��
	m_nVersion = atoi(str.GetBuffer(0));

	nLastEnd = nEnd;

	nStart = 0;



	//�ҵ��ڶ�������
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
		//�õ������ļ�
		m_strUpdateIni = str;
	}

	nLastEnd = nEnd;
	
	nStart = 0;

	//�ҵ�����������
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
		///�õ�Ӧ�ó��������
		m_strAppName = str;
	}

	return true;
}

void CMyUpdaterDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	//CDialog::OnClose();
}


DWORD _stdcall CMyUpdaterDlg::ThreadDownLoad(LPVOID lp)//���ص��߳�
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

			///�ð�ťֹͣ����
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
		MessageBox("���������ڲ���������\n������ǵ���վ,ֱ�����ز���װ���³���", g_strWindowTitle, MB_ICONERROR);
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


///��������
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

	//������ʱĿ¼
	strcat(chTempPath, "MyUpdaterDir\\");

	CString strCurrentDir = GetAppPath();

	//�õ������������ڵ�Ŀ¼
	CString strTmpDir = chTempPath;

	if (!MakeDir(chTempPath))
	{
		CString strTmp;
		strTmp.Format("������ʱ����Ŀ¼ \"%s\" ʧ��,����ȡ��\n������ǵ���վ,ֱ�����ز���װ���³���", chTempPath);

		MessageBox(chTempPath, g_strWindowTitle, MB_ICONERROR);
		ShellExecute(NULL, "open", g_strContractUSWeb, NULL, NULL, SW_MAXIMIZE);

		return;
	}

	strPath = chTempPath;
	strPath += "\\Update.ini";

	//��һ��
	LoadingMove();
	//����INI�ļ�
	int ret = URLDownloadToFile(NULL, m_strUpdateIni, strPath, 0, NULL); 
	
	if (ret == S_OK) //������سɹ� 
	{

		//�ڶ���
		LoadingMove();

		CIni ini;

		CString str;

		int nNewVersion = 0;

		//�����Ƕ�ȡ�ĸ��汾��Ϣ��
		//--------------------------------------------------------------------------------
		if (!ini.ReadString("Version", "VersionID", str, strPath.GetBuffer(0)))
		{
			DeleteDir(chTempPath);

			MessageBox("������Ϣ����,����������ϵ\n������ǵ���վ,ֱ�����ز���װ���³���", g_strWindowTitle, MB_ICONERROR);
			ShellExecute(NULL, "open", g_strContractUSWeb, NULL, NULL, SW_MAXIMIZE);

			return;
		}

		nNewVersion = atoi(str.GetBuffer(0));

		if (nNewVersion <= m_nVersion)
		{
			DeleteDir(chTempPath);
			
			MessageBox("��ǰ�Ѿ������°�,����Ҫ��������", g_strWindowTitle, MB_OK);

			
			return;
		}

		int nCount = 0;

		int i;

		//�����Ƕ�ȡҪ���ص��ļ��Ĳ���

		if (!ini.ReadString("AddFiles", "AddFilesLen", str, strPath.GetBuffer(0)))
		{
			DeleteDir(chTempPath);

			MessageBox("������Ϣ���޸����ļ�\n������ǵ���վ,ֱ�����ز���װ���³���", g_strWindowTitle, MB_ICONERROR);
			ShellExecute(NULL, "open", g_strContractUSWeb, NULL, NULL, SW_MAXIMIZE);

			return;
		}

		//�õ������ص��ļ��ĸ���
		nCount = atoi(str.GetBuffer(0));

		if (nCount <= 0)
		{
			DeleteDir(chTempPath);
			
			MessageBox("������Ϣ�и����ļ��ĸ�������\n������ǵ���վ,ֱ�����ز���װ���³���", g_strWindowTitle, MB_ICONERROR);
			ShellExecute(NULL, "open", g_strContractUSWeb, NULL, NULL, SW_MAXIMIZE);
			
			return;
		}

		//���غ��Ŀ���ļ��ļ���
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

				
				MessageBox("������Ϣ����\n������ǵ���վ,ֱ�����ز���װ���³���", g_strWindowTitle, MB_ICONERROR);
				ShellExecute(NULL, "open", g_strContractUSWeb, NULL, NULL, SW_MAXIMIZE);
				
				return;
			}

			arrayStrSrc.Add(strUrl);

			strTmpRead.Format("AddFilesDest%d", i);
			
			if (!ini.ReadString("AddFiles", strTmpRead, strDest, strPath.GetBuffer(0)))
			{
				DeleteDir(chTempPath);

				MessageBox("������Ϣ����\n������ǵ���վ,ֱ�����ز���װ���³���", g_strWindowTitle, MB_ICONERROR);
				ShellExecute(NULL, "open", g_strContractUSWeb, NULL, NULL, SW_MAXIMIZE);
				
				return;
			}

			arrayStrDest.Add(strDest);
			////////////////////////////////////////////////

		}

		///�������������ļ�
		LoadingMove();

		for (i = 0; i < arrayStrSrc.GetSize(); i++)
		{
			CString strFormat;

			//�ܵĽ�����
			m_pro.SetPos(i);
			strFormat.Format("�ܽ���: %d / %d", i + 1, arrayStrSrc.GetSize());
			m_static_total.SetWindowText(strFormat);


			if (!MakeDir(GetPathFromFileName(strTmpDir + arrayStrDest[i])))
			{
				DeleteDir(chTempPath);

				MessageBox("������������Ҫ����ʱĿ¼ʧ��\n������ǵ���վ,ֱ�����ز���װ���³���", g_strWindowTitle, MB_ICONERROR);
				ShellExecute(NULL, "open", g_strContractUSWeb, NULL, NULL, SW_MAXIMIZE);

				return;
			}

			///��ʾ��ǰ���ص��ļ�
			
			strFormat.Format("��ǰ��������: %s", GetFileNameFromPath(strTmpDir + arrayStrDest[i]));
			m_static_downloading.SetWindowText(strFormat);

			///�ص�����
			CCallback callback;
			callback.SetDepend(&m_proOneFile, &m_static_speed);

			HRESULT   hr = URLDownloadToFile(NULL, arrayStrSrc[i], (strTmpDir + arrayStrDest[i]), 0, &callback);

			if (FAILED(hr) )
			{
				DeleteDir(chTempPath);

				strFormat.Format("�ļ� \"%s\" ����ʧ��\n������ǵ���վ,ֱ�����ز���װ���³���", GetFileNameFromPath(strTmpDir + arrayStrDest[i]));
				MessageBox(strFormat, g_strWindowTitle, MB_ICONERROR);
				ShellExecute(NULL, "open", g_strContractUSWeb, NULL, NULL, SW_MAXIMIZE);
				return;
			}

			
		}

		//��β����
		m_proOneFile.SetPos(0);
		m_static_speed.SetWindowText("");
		m_static_downloading.SetWindowText("");

		///���Ĳ��������ļ�
		LoadingMove();
		
		for (i = 0; i < arrayStrDest.GetSize(); i++)
		{
			if (!MakeDir(GetPathFromFileName(strCurrentDir + arrayStrDest[i])))
			{
				DeleteDir(chTempPath);

				MessageBox("������������Ҫ��Ŀ��Ŀ¼����\n������ǵ���վ,ֱ�����ز���װ���³���", g_strWindowTitle, MB_ICONERROR);
				ShellExecute(NULL, "open", g_strContractUSWeb, NULL, NULL, SW_MAXIMIZE);

				return;
			}
			CString strSrc = strTmpDir + arrayStrDest[i];
			CString strDest = strCurrentDir + arrayStrDest[i];
			bool bOk = CopyFile(strTmpDir + arrayStrDest[i], strCurrentDir + arrayStrDest[i], false);

			while (!bOk)
			{
				if (MessageBox("�ļ�: \"" + strCurrentDir + arrayStrDest[i] + "\" �޷�����,�뱣֤���ļ�û�б���!", g_strWindowTitle, MB_RETRYCANCEL) == IDRETRY)
				{
					bOk = CopyFile(strTmpDir + arrayStrDest[i], strCurrentDir + arrayStrDest[i], false);
				}
				else
				{
					break;
				}
			}
		}
////���岽�����
		LoadingMove();

		DeleteDir(chTempPath);

		MessageBox("�������", g_strWindowTitle, MB_OK);
		
		///�������������
		ShellExecute(NULL, "open", m_strAppName, NULL, NULL, SW_SHOWNORMAL);
	}
	else
	{
		DeleteDir(chTempPath);

		MessageBox("�����ļ�����ʧ��\n������ǵ���վ,ֱ�����ز���װ���³���", g_strWindowTitle, MB_ICONERROR);
		ShellExecute(NULL, "open", g_strContractUSWeb, NULL, NULL, SW_MAXIMIZE);

	}
}

void CMyUpdaterDlg::SetSpeedText(CString strText)
{
	m_static_speed.SetWindowText(strText);
}
