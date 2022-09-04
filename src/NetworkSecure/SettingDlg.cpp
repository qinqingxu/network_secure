// SettingDlg.cpp : implementation file
//

#include "pch.h"
#include "NetworkSecure.h"
#include "afxdialogex.h"
#include "SettingDlg.h"
#include "GlobalVariable.h"
#include "Constant.h"
#include <shlwapi.h>


#pragma comment(lib,"Shlwapi.lib")
// SettingDlg dialog

IMPLEMENT_DYNAMIC(SettingDlg, CDialogEx)

SettingDlg::SettingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SETTING, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif
}

SettingDlg::~SettingDlg()
{

}

void SettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_INTERVAL, m_editScanInterval);
	DDX_Control(pDX, IDC_CHECK_PLAY_SOUND, m_checkBoxPlaySound);
	DDX_Control(pDX, IDC_EDIT_SOUND_FILE, m_editSoundFile);
	DDX_Control(pDX, IDC_BUTTON_OPEN_SOUND_FILE, m_buttonBrowseSoundFile);
	DDX_Control(pDX, IDC_CHECK_USE_PROXY, m_checkBoxUseProxy);
	DDX_Control(pDX, IDC_EDIT_PROXY_ADDRESS, m_editProxyAddress);
	DDX_Control(pDX, IDC_EDIT_PROXY_PORT, m_editProxyPort);
}


BEGIN_MESSAGE_MAP(SettingDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_CHANGE, &SettingDlg::OnBnClickedButtonSaveChange)
	ON_BN_CLICKED(IDC_CHECK_USE_PROXY, &SettingDlg::OnBnClickedCheckUseProxy)
	ON_BN_CLICKED(IDC_CHECK_PLAY_SOUND, &SettingDlg::OnBnClickedCheckPlaySound)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &SettingDlg::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// SettingDlg message handlers


void SettingDlg::OnBnClickedButtonSaveChange()
{
	if (!SaveConfiguration())
	{
		return;
	}
	else
	{
		ShowWindow(SW_HIDE);
	}
	// TODO: Add your control notification handler code here
}

void SettingDlg::LoadConfiguration()
{
	CString str;

	//Scan Interval
	str.Format("%d", g_configurator.GetScanInterval());
	m_editScanInterval.SetWindowText(str);


	//Sound Player
	if (g_configurator.GetSoundInfo().m_playSound)
	{
		m_checkBoxPlaySound.SetCheck(1);
		m_editSoundFile.SetWindowText(g_configurator.GetSoundInfo().m_soundFile.c_str());
		m_editSoundFile.EnableWindow(true);
		m_buttonBrowseSoundFile.EnableWindow(true);
	}
	else
	{
		m_checkBoxPlaySound.SetCheck(0);
		m_editSoundFile.SetWindowText(g_configurator.GetSoundInfo().m_soundFile.c_str());
		m_editSoundFile.EnableWindow(false);
		m_buttonBrowseSoundFile.EnableWindow(false);
	}

	//Use proxy
	if (g_configurator.GetProxyInfo().m_useProxy)
	{
		m_checkBoxUseProxy.SetCheck(1);

		m_editProxyAddress.SetWindowText(g_configurator.GetProxyInfo().m_proxyAddress.c_str());
		m_editProxyAddress.EnableWindow(true);

		str.Format("%d", g_configurator.GetProxyInfo().m_porxyPort);
		m_editProxyPort.SetWindowText(str);
		m_editProxyPort.EnableWindow(true);
	}
	else
	{
		m_checkBoxUseProxy.SetCheck(0);

		m_editProxyAddress.SetWindowText(g_configurator.GetProxyInfo().m_proxyAddress.c_str());
		m_editProxyAddress.EnableWindow(false);

		str.Format("%d", g_configurator.GetProxyInfo().m_porxyPort);
		m_editProxyPort.SetWindowText(str);
		m_editProxyPort.EnableWindow(false);
	}

}
bool SettingDlg::CheckConfiguration()
{
	CString str;

	m_editScanInterval.GetWindowText(str);
	if (str.Trim() == "")
	{
		MessageBox("Invalid scan interval value", g_strWindowTitle, MB_ICONWARNING);
		return false;
	}

	int nInterval = atoi(str.GetBuffer(0));
	if (nInterval <= 0)
	{
		MessageBox("Invalid scan interval value", g_strWindowTitle, MB_ICONWARNING);
		return false;
	}
	//If the interval more than 1 hour, it is might cause too high risk.
	if (nInterval >= 60 * 60 * 1000)
	{
		MessageBox("Interval value is better to less than 1 hour", g_strWindowTitle, MB_ICONWARNING);
		return false;
	}
	//----------------------------------------------------------------------------------------------------------------------

	if (m_checkBoxPlaySound.GetCheck())
	{
		m_editSoundFile.GetWindowText(str);
		if (str.Trim() == "")
		{
			MessageBox("Invalid sound file value", g_strWindowTitle, MB_ICONWARNING);
			return false;
		}

		if (!PathFileExists(str))
		{
			MessageBox("Sound file does not existent", g_strWindowTitle, MB_ICONWARNING);
			return false;
		}
	}
	//----------------------------------------------------------------------------------------------------------------------

	if (m_checkBoxUseProxy.GetCheck())
	{
		m_editProxyAddress.GetWindowText(str);
		if (str.Trim() == "")
		{
			MessageBox("Invalid proxy address value", g_strWindowTitle, MB_ICONWARNING);
			return false;
		}

		m_editProxyPort.GetWindowText(str);
		int port = atoi(str.GetBuffer(0));
		if (port <= 0 || port >= 65535)
		{
			MessageBox("Invalid proxy port value", g_strWindowTitle, MB_ICONWARNING);
			return false;
		}
	}

	return true;
}
bool SettingDlg::SaveConfiguration()
{
	if (!CheckConfiguration())
	{
		return false;
	}

	CString str;

	m_editScanInterval.GetWindowText(str);
	int nInterval = atoi(str.GetBuffer(0));
	g_configurator.SetScanInterval(nInterval);
	//----------------------------------------------------------------------------------------------------------------------

	SoundInfo soundInfo;
	if (m_checkBoxPlaySound.GetCheck())
	{
		soundInfo.m_playSound = true;
	}
	else
	{
		soundInfo.m_playSound = false;
	}

	m_editSoundFile.GetWindowText(str);
	soundInfo.m_soundFile = str.Trim().GetBuffer(0);

	g_configurator.SetSoundInfo(soundInfo);
	//----------------------------------------------------------------------------------------------------------------------

	ProxyInfo proxyInfo;
	if (m_checkBoxUseProxy.GetCheck())
	{
		proxyInfo.m_useProxy = true;
	}
	else
	{
		proxyInfo.m_useProxy = false;
	}

	m_editProxyAddress.GetWindowText(str);
	proxyInfo.m_proxyAddress = str.Trim();


	m_editProxyPort.GetWindowText(str);
	proxyInfo.m_porxyPort = atoi(str.GetBuffer(0));

	g_configurator.SetProxyInfo(proxyInfo);


	if (!g_configurator.WriteJsonFile(G_JSON_CONFIG_FILE_NAME))
	{
		MessageBox(g_configurator.GetLastError(), g_strWindowTitle, MB_ICONERROR);
		return false;
	}

	return true;
}


BOOL SettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_SETTING));
	SetIcon(hIcon, FALSE);

	LoadConfiguration();
	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void SettingDlg::OnBnClickedCheckUseProxy()
{

	if (m_checkBoxUseProxy.GetCheck())
	{
		m_editProxyAddress.EnableWindow(true);
		m_editProxyPort.EnableWindow(true);
	}
	else
	{
		m_editProxyAddress.EnableWindow(false);
		m_editProxyPort.EnableWindow(false);
	}
	// TODO: Add your control notification handler code here
}


void SettingDlg::OnBnClickedCheckPlaySound()
{

	if (m_checkBoxPlaySound.GetCheck())
	{
		m_editSoundFile.EnableWindow(true);
		m_buttonBrowseSoundFile.EnableWindow(true);
	}
	else
	{
		m_editSoundFile.EnableWindow(false);
		m_buttonBrowseSoundFile.EnableWindow(false);
	}
	// TODO: Add your control notification handler code here
}


void SettingDlg::OnBnClickedButtonCancel()
{
	ShowWindow(SW_HIDE);
	// TODO: Add your control notification handler code here
}
