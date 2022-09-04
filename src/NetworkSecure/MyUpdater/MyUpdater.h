// MyUpdater.h : main header file for the MYUPDATER application
//

#if !defined(AFX_MYUPDATER_H__5636819E_DADE_4D8A_AB79_D865AA31D47F__INCLUDED_)
#define AFX_MYUPDATER_H__5636819E_DADE_4D8A_AB79_D865AA31D47F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyUpdaterApp:
// See MyUpdater.cpp for the implementation of this class
//

class CMyUpdaterApp : public CWinApp
{
public:
	CMyUpdaterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyUpdaterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMyUpdaterApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYUPDATER_H__5636819E_DADE_4D8A_AB79_D865AA31D47F__INCLUDED_)
