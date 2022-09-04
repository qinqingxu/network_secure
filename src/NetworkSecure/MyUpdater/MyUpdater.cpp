// MyUpdater.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MyUpdater.h"
#include "MyUpdaterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyUpdaterApp

BEGIN_MESSAGE_MAP(CMyUpdaterApp, CWinApp)
	//{{AFX_MSG_MAP(CMyUpdaterApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyUpdaterApp construction

CMyUpdaterApp::CMyUpdaterApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMyUpdaterApp object

CMyUpdaterApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMyUpdaterApp initialization

BOOL CMyUpdaterApp::InitInstance()
{
	Sleep(1000);
	//������Ƭѹ����ʦ����������
	
	/*HANDLE hdMutex = CreateMutex(NULL, TRUE, "19lou_auto_up_machine");

	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		MessageBox(NULL, "19¥�Զ������������������Ѿ�������,���ȹر���Ӧ�ĳ���,��ִ������", g_strWindowTitle, MB_ICONERROR);
		return false;
	}
	*/

	SetDialogBkColor(RGB(255, 255, 255));


	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CMyUpdaterDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	//ReleaseMutex(hdMutex);

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

