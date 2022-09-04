//////////////////////////////////////////////////////////////////////
//
// Written by Michael Dunn (mdunn at inreach dot com).  Copyright and all
// that stuff.  Use however you like but give me credit where it's due.  I'll
// know if you don't. bwa ha ha ha ha!
// 
// Release history:
//   December 24, 1999: Version 1.0.  First release.
//
//////////////////////////////////////////////////////////////////////

// BindStatusCallback.cpp: implementation of the CBindStatusCallback class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyUpdater.h"
#include "MyUpdaterDlg.h"
#include "BindStatusCallback.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCallback::CCallback()
{
	m_pPro = NULL;
	
	m_pSpeedText = NULL;

	///上一次的时间
	m_nLastTime = 0;
	
	///上一次的进度
	m_nLastPro = 0;
// 
// 	m_pDlg = NULL;
}

CCallback::~CCallback()
{
}


HRESULT CCallback::OnStartBinding(
						  /* [in] */ DWORD dwReserved,
						  /* [in] */ IBinding __RPC_FAR *pib)
{
	if (m_nLastTime == 0)
	{
		m_nLastTime = GetTickCount();
	}
	return E_NOTIMPL;
}

HRESULT CCallback::OnProgress ( ULONG ulProgress,   ULONG ulProgressMax,
                                ULONG ulStatusCode, LPCWSTR wszStatusText )
{
// Local variables are declared static so they don't have to be reallocated on
// the stack every time.  This is safe in this app since I know I'll only have
// one thread downloading.
	static CString strText;

	static DWORD dwThisTime = 0;

	static float fSpeed = 0.0;

	dwThisTime = GetTickCount();

	if (ulProgress == 0 || ulProgress <= m_nLastPro)
	{
		fSpeed = 0.0f;
	}
	else
	{

		float fTimeInter = (float(dwThisTime - m_nLastTime) / 1000.0f);

		if (fTimeInter <= 0.000f)
		{
			fTimeInter = 1.0;
		}

		//fSpeed = (float(ulProgress - m_nLastPro) / 1024.0f) / fTimeInter;
		fSpeed = (float(ulProgress) / 1024.0f) / fTimeInter;
	}

    UNREFERENCED_PARAMETER(ulStatusCode);

	strText.Format("当前进度: %s / %s 下载速度: %.2f KB/S", GetFileSize(ulProgress), GetFileSize(ulProgressMax), fSpeed);
// 	strText.Format("当前进度: %s / %s", GetFileSize(ulProgress), GetFileSize(ulProgressMax));
// 	
// 	if (m_pDlg != NULL)
// 	{
// 		m_pDlg->SetSpeedText(strText);
// 	}
	if (m_pSpeedText != NULL)
	{
		m_pSpeedText->ShowSpeed(strText);
	}

	if (m_pPro != NULL)
	{
		if (0 != ulProgressMax)
		{
			m_pPro->SetPos(int(100.0 * ulProgress / ulProgressMax));
		}
		else
		{
			m_pPro->SetPos(0);
		}
	}

// 	/获取最新的时间及进度
 		//m_nLastTime = GetTickCount();
// 	
 		//m_nLastPro = ulProgress;
	
    return S_OK;
}


void CCallback::SetDepend(CProgressCtrl *pPro,  CSpeedStatic *pSpeedText/*, CMyUpdaterDlg *pDlg*/)
{
	m_pPro = pPro;

	m_pSpeedText = pSpeedText;

//	m_pDlg = pDlg;
}