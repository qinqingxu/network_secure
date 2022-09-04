// ColorStatic.cpp : implementation file
//

#include "stdafx.h"
#include "myupdater.h"
#include "ColorStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorStatic

CColorStatic::CColorStatic()
{
	m_bkColor = RGB(255, 255, 255);
	m_textColor = RGB(0, 0, 0);
	
}

CColorStatic::~CColorStatic()
{
}


BEGIN_MESSAGE_MAP(CColorStatic, CStatic)
	//{{AFX_MSG_MAP(CColorStatic)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorStatic message handlers


void CColorStatic::OnPaint() 
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
	lf.lfUnderline = false;
	lf.lfWeight = FW_DONTCARE;

	
	HDC hdc = CreateCompatibleDC(dc.m_hDC);
	HBITMAP bitmap = CreateCompatibleBitmap(dc.m_hDC, rectClient.Width(), rectClient.Height());
	HFONT font = CreateFontIndirect(&lf);
	
	SelectObject(hdc, bitmap);
	SelectObject(hdc, font);
	
	PatBlt(hdc, 0, 0, rectClient.Width(), rectClient.Height(), WHITENESS);
	
	SIZE sz;
	
	::SetBkMode(hdc, TRANSPARENT);
	::SetTextColor(hdc, m_textColor);
	
	GetTextExtentPoint(hdc, strText.GetBuffer(0), strText.GetLength(), &sz);
	
	TextOut(hdc, 0, 0, strText.GetBuffer(0), strText.GetLength());
	
	BitBlt(dc.m_hDC, 0, 0, rectClient.Width(), rectClient.Height(), hdc, 0, 0, SRCCOPY);
	
	DeleteDC(hdc);
	DeleteObject(bitmap);
	DeleteObject(font);

	// TODO: Add your message handler code here
	
	// Do not call CStatic::OnPaint() for painting messages
}


void CColorStatic::SetTextColor(COLORREF col)
{
	m_textColor = col;
	RedrawWindow();
}
