#if !defined(AFX_COLORSTATIC_H__2C81EA41_5CB2_4507_B671_3AD5FDDD9183__INCLUDED_)
#define AFX_COLORSTATIC_H__2C81EA41_5CB2_4507_B671_3AD5FDDD9183__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorStatic window

class CColorStatic : public CStatic
{
// Construction
public:
	CColorStatic();

	void SetTextColor(COLORREF col);

	COLORREF m_textColor;
	COLORREF m_bkColor;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CColorStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorStatic)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORSTATIC_H__2C81EA41_5CB2_4507_B671_3AD5FDDD9183__INCLUDED_)
