#pragma once
#include "afxdialogex.h"


// SettingDlg dialog

class SettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SettingDlg)

public:
	SettingDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~SettingDlg();

	void LoadConfiguration();
	bool CheckConfiguration();
	bool SaveConfiguration();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editScanInterval;
	CButton m_checkBoxPlaySound;
	CEdit m_editSoundFile;
	CButton m_buttonBrowseSoundFile;
	CButton m_checkBoxUseProxy;
	CEdit m_editProxyAddress;
	CEdit m_editProxyPort;
	afx_msg void OnBnClickedButtonSaveChange();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCheckUseProxy();
	afx_msg void OnBnClickedCheckPlaySound();
	afx_msg void OnBnClickedButtonCancel();
};
