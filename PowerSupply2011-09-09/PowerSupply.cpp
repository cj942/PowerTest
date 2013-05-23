// PowerSupply.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "PowerSupply.h"
#include "PowerSupplyDlg.h"
#include "Login.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CPowerSupplyApp

BEGIN_MESSAGE_MAP(CPowerSupplyApp, CWinApp)
	//{{AFX_MSG_MAP(CPowerSupplyApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPowerSupplyApp construction

CPowerSupplyApp::CPowerSupplyApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPowerSupplyApp object

CPowerSupplyApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPowerSupplyApp initialization

BOOL CPowerSupplyApp::InitInstance()
{
	AfxEnableControlContainer();
	if (CoInitialize(NULL)!=0) 
	{ 
		AfxMessageBox("��ʼ��COM֧�ֿ�ʧ��!"); 
		exit(1); 
	}
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	//CPowerSupplyDlg dlg;
	
	CLogin dlg;
    m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	  
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	return FALSE;
}