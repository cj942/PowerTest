// IT6832.h : main header file for the IT6832 application
//

#if !defined(AFX_IT6832_H__297FAA83_BABA_4637_8038_56A1FFEFBD9C__INCLUDED_)
#define AFX_IT6832_H__297FAA83_BABA_4637_8038_56A1FFEFBD9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CIT6832App:
// See IT6832.cpp for the implementation of this class
//

class CIT6832App : public CWinApp
{
public:
	CIT6832App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIT6832App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CIT6832App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IT6832_H__297FAA83_BABA_4637_8038_56A1FFEFBD9C__INCLUDED_)
