// SerialsInputDialog.cpp : implementation file
//

#include "stdafx.h"
#include "powersupply.h"
#include "SerialsInputDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSerialsInputDialog dialog

extern CString strSerirals;
CSerialsInputDialog::CSerialsInputDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSerialsInputDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSerialsInputDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSerialsInputDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSerialsInputDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSerialsInputDialog, CDialog)
	//{{AFX_MSG_MAP(CSerialsInputDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSerialsInputDialog message handlers

void CSerialsInputDialog::OnOK() 
{
	// TODO: Add extra validation here
	GetDlgItemText(IDC_EDIT_SERIAL,strSerirals);
	CDialog::OnOK();
}

