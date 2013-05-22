#if !defined(AFX_SERIALSINPUTDIALOG_H__23614489_793A_41B8_9441_F47B4B63A8E0__INCLUDED_)
#define AFX_SERIALSINPUTDIALOG_H__23614489_793A_41B8_9441_F47B4B63A8E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SerialsInputDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSerialsInputDialog dialog

class CSerialsInputDialog : public CDialog
{
// Construction
public:
	CSerialsInputDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSerialsInputDialog)
	enum { IDD = IDD_DIALOG_INPUTSERIALS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSerialsInputDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSerialsInputDialog)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERIALSINPUTDIALOG_H__23614489_793A_41B8_9441_F47B4B63A8E0__INCLUDED_)
