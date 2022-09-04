
// NetworkSecure.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "NetworkSecure.h"
#include "NetworkSecureDlg.h"
#include "SplashDialog.h"
#include "GlobalVariable.h"
#include "PublicClasses.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNetworkSecureApp

BEGIN_MESSAGE_MAP(CNetworkSecureApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CNetworkSecureApp construction

CNetworkSecureApp::CNetworkSecureApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CNetworkSecureApp object

CNetworkSecureApp theApp;


bool CNetworkSecureApp::InitConfiguration()
{
	if (!g_configurator.ReadJsonFile(G_JSON_CONFIG_FILE_NAME))
	{
		AfxMessageBox(g_configurator.GetLastError());
		return false;
	}
	return true;
}

CString GetAppName()
{
	CString   sModFileName;
	CString   str1;
	GetModuleFileName(NULL, sModFileName.GetBuffer(MAX_PATH), MAX_PATH);
	sModFileName.ReleaseBuffer();
	return sModFileName;
}



//
//CString GetCurrentPath()
//{
//	TCHAR chPath[MAX_PATH];
//	GetModuleFileName(NULL, chPath, MAX_PATH);
//
//	for (int i = _tcslen(chPath); i >= 0; i--)
//	{
//		if (chPath[i] == _T('\\'))
//		{
//			chPath[i + 1] = _T('\0');
//			break;
//		}
//	}
//
//	return CString(chPath);
//}

BOOL CNetworkSecureApp::InitInstance()
{
	if (!InitConfiguration())
	{
		return FALSE;
	}


	AfxOleInit();
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxInitRichEdit2();
	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	//Show the Splash Dialog
	SplashDialog splashDlg;
	if (splashDlg.DoModal() == G_DIALOG_CLOSE_NEED_TO_UPGRADE)
	{
		ShellExecute(0, 0, "https://github.com/qinqingxu/network_secure", 0, 0, SW_SHOW);
		return TRUE;
	}


	CNetworkSecureDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
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
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}
	else if (nResponse == G_DIALOG_CLOSE_NEED_TO_UPGRADE)
	{
		//Todo
		//Add the upgrade related code here.
	}

	// Delete the shell manager created above.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}



void CNetworkSecureApp::OnHelpAboutnetworksecure()
{
	// TODO: Add your command handler code here
}
