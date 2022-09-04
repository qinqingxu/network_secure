#if !defined(AFX_SPEEDSTATIC_H__9B5F8212_FC7F_4FE5_A74B_EE0535092B4D__INCLUDED_)
#define AFX_SPEEDSTATIC_H__9B5F8212_FC7F_4FE5_A74B_EE0535092B4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SpeedStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSpeedStatic window

class CSpeedStatic : public CStatic
{
// Construction
public:
	CSpeedStatic();

	void ShowSpeed(CString str);


	///text to show
	CString m_str;

	void Draw(void);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpeedStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSpeedStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSpeedStatic)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPEEDSTATIC_H__9B5F8212_FC7F_4FE5_A74B_EE0535092B4D__INCLUDED_)
