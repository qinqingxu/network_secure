// LinkStatic.cpp : implementation file
//

#include "stdafx.h"
#include "MyUpdater.h"
#include "LinkStatic.h"


///主窗口的类
#include "MyUpdaterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLinkStatic

CLinkStatic::CLinkStatic()
{
	m_bMouseOn = false;
	m_voidfunction = NULL;

	m_bWorking = true;
}

CLinkStatic::~CLinkStatic()
{
}


BEGIN_MESSAGE_MAP(CLinkStatic, CStatic)
	//{{AFX_MSG_MAP(CLinkStatic)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLinkStatic message handlers

void CLinkStatic::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	ModifyStyle(0,SS_NOTIFY);
	CStatic::PreSubclassWindow();
}

void CLinkStatic::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_voidfunction != NULL)
	{
		CMyUpdaterDlg *dlg = (CMyUpdaterDlg *)GetParent();
		if (dlg != NULL)
		{
			(dlg->*m_voidfunction)();
		}
	}
	CStatic::OnLButtonDown(nFlags, point);
}

void CLinkStatic::OnMouseMove(UINT nFlags, CPoint point) 
{

	if (!m_bMouseOn)
	{
		TRACKMOUSEEVENT tme;
		m_bMouseOn = true;
		tme.cbSize = sizeof(TRACKMOUSEEVENT);   
		tme.dwFlags = TME_LEAVE;   
		tme.hwndTrack = this->m_hWnd;   
		_TrackMouseEvent(&tme);
	}
	RedrawWindow();
	CStatic::OnMouseMove(nFlags, point);
}


LRESULT CLinkStatic::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{   
	m_bMouseOn = false;   
	
	RedrawWindow();
	
	return 0;
}

void CLinkStatic::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CString strText;
	GetWindowText(strText);

	CRect rectClient;
	GetWindowRect(&rectClient);

	LOGFONT lf;
	dc.GetCurrentFont()->GetLogFont(&lf);

	lf.lfCharSet = ANSI_CHARSET | DEFAULT_CHARSET;//字符集
	lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	lf.lfEscapement = 0;
	strcpy(lf.lfFaceName, "宋体");//字体名称
	lf.lfHeight = 12;//字体大小
	lf.lfItalic = 0;//是否斜体
	lf.lfOrientation = 0;
	lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
	lf.lfPitchAndFamily = DEFAULT_PITCH;
	lf.lfQuality = DEFAULT_QUALITY;
	lf.lfStrikeOut = 0;//中划线
	lf.lfUnderline = 0;//下划线
	lf.lfWeight = FW_DONTCARE;//字体粗 0-1000之间，400为正常，700为黑体
	lf.lfWidth = 0;//字体宽

	if (m_bMouseOn)
	{
		lf.lfUnderline = true;
		lf.lfWeight = FW_BOLD;
	}
	else
	{
		lf.lfUnderline = false;
		lf.lfWeight = FW_DONTCARE;
	}

	HDC hdc = CreateCompatibleDC(dc.m_hDC);
	HBITMAP bitmap = CreateCompatibleBitmap(dc.m_hDC, rectClient.Width(), rectClient.Height());
	HFONT font = CreateFontIndirect(&lf);

	SelectObject(hdc, bitmap);
	SelectObject(hdc, font);

	PatBlt(hdc, 0, 0, rectClient.Width(), rectClient.Height(), WHITENESS);

	SIZE sz;

	if (m_bWorking)
	{
		SetTextColor(hdc, G_TEXT_COLOR_BLUE);
	}
	else
	{
		SetTextColor(hdc, G_TEXT_COLOR_GRAY);
	}
	

	GetTextExtentPoint(hdc, strText.GetBuffer(0), strText.GetLength(), &sz);

	TextOut(hdc, (rectClient.Width() - sz.cx) / 2, (rectClient.Height() - sz.cy) / 2, strText.GetBuffer(0), strText.GetLength());

	BitBlt(dc.m_hDC, 0, 0, rectClient.Width(), rectClient.Height(), hdc, 0, 0, SRCCOPY);

	DeleteDC(hdc);
	DeleteObject(bitmap);
	DeleteObject(font);
}

BOOL CLinkStatic::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	::SetCursor(::LoadCursor(NULL, IDC_HAND));

	return true;
}
