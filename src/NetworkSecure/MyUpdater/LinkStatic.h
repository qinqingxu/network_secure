#if !defined(AFX_LINKSTATIC_H__E26AF605_7594_49D4_9670_B332A3F385EF__INCLUDED_)
#define AFX_LINKSTATIC_H__E26AF605_7594_49D4_9670_B332A3F385EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LinkStatic.h : header file
//

//以下是主窗口的类
class CMyUpdaterDlg;
/////////////////////////////////////////////////////////////////////////////
// CLinkStatic window
//当按钮不能工作时文件颜色
#define G_TEXT_COLOR_GRAY RGB(128, 128, 128)

//当按钮不能工作时文件颜色
#define G_TEXT_COLOR_BLUE RGB(0, 0, 255)


#ifndef   IDC_HAND   
#define   IDC_HAND                         MAKEINTRESOURCE(32649)   //   from   winuser.h   
#endif   

typedef void (CMyUpdaterDlg::*VoidFunction)(void);

class CLinkStatic : public CStatic
{
// Construction
public:
	CLinkStatic();

	VoidFunction m_voidfunction;

	///是否在工作
	bool m_bWorking;
	////mouse is in control
	bool m_bMouseOn;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLinkStatic)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLinkStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CLinkStatic)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINKSTATIC_H__E26AF605_7594_49D4_9670_B332A3F385EF__INCLUDED_)
