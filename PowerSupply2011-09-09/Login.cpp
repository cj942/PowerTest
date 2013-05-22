// Login.cpp : implementation file
//

#include "stdafx.h"
#include "PowerSupply.h"
#include "Login.h"
#include "PowerSupplyDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString strLoginName,strLoginPassword,strSerirals;
/////////////////////////////////////////////////////////////////////////////
// CLogin dialog


CLogin::CLogin(CWnd* pParent /*=NULL*/)
	: CDialog(CLogin::IDD, pParent)
{

	//{{AFX_DATA_INIT(CLogin)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogin)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLogin, CDialog)
	//{{AFX_MSG_MAP(CLogin)
	ON_BN_CLICKED(IDOK, OnLoadProcess)
	ON_EN_CHANGE(IDC_EDIT_LOGINNAME, OnChangeEditLoginname)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogin message handlers

void CLogin::OnLoadProcess() 
{
	// TODO: Add your control notification handler code here
	GetDlgItemText(IDC_EDIT_LOGINNAME,strLoginName);
	GetDlgItemText(IDC_EDIT_LOGINPASSWORD,strLoginPassword);
	GetDlgItemText(IDC_EDIT_SNNUMBER,strSerirals);

       if(0==lstrcmp(strLoginPassword,""))
	   {
			CWnd   *   old=GetActiveWindow();   
			ShowWindow(SW_HIDE);
			CPowerSupplyDlg MainDlg;
			MainDlg.DoModal();
	   }
	   else
	   {
		   MessageBox("密码错误！请询问管理员");
	   }
	
}

void CLogin::OnChangeEditLoginname() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}
