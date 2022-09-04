
// NetworkSecure.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CNetworkSecureApp:
// See NetworkSecure.cpp for the implementation of this class
//

class CNetworkSecureApp : public CWinApp
{
public:
	CNetworkSecureApp();
	bool InitConfiguration();
// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
		afx_msg void OnHelpAboutnetworksecure();
};

extern CNetworkSecureApp theApp;
