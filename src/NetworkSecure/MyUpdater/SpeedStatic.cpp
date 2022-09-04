// SpeedStatic.cpp : implementation file
//

#include "stdafx.h"
#include "myupdater.h"
#include "SpeedStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpeedStatic

CSpeedStatic::CSpeedStatic()
{
}

CSpeedStatic::~CSpeedStatic()
{
}


BEGIN_MESSAGE_MAP(CSpeedStatic, CStatic)
	//{{AFX_MSG_MAP(CSpeedStatic)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpeedStatic message handlers

void CSpeedStatic::ShowSpeed(CString str)
{
	m_str = str;
	Draw();
}


void CSpeedStatic::Draw(void)
{
	CClientDC dc(this); // device context for painting
	
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
	::SetTextColor(hdc, RGB(0, 0, 0));
	
	GetTextExtentPoint(hdc, m_str.GetBuffer(0), m_str.GetLength(), &sz);
	
	TextOut(hdc, 0, 0, m_str.GetBuffer(0), m_str.GetLength());
	
	BitBlt(dc.m_hDC, 0, 0, rectClient.Width(), rectClient.Height(), hdc, 0, 0, SRCCOPY);
	
	DeleteDC(hdc);
	DeleteObject(bitmap);
	DeleteObject(font);
}

void CSpeedStatic::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	

	Draw();
	// Do not call CStatic::OnPaint() for painting messages
}
