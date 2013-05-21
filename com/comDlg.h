// comDlg.h : header file
//
//{{AFX_INCLUDES()
#include "mscomm.h"
//}}AFX_INCLUDES

#if !defined(AFX_COMDLG_H__9FC47340_5C48_40CD_A0B6_1EFBFBE19ECC__INCLUDED_)
#define AFX_COMDLG_H__9FC47340_5C48_40CD_A0B6_1EFBFBE19ECC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CComDlg dialog

class CComDlg : public CDialog
{
// Construction
public:
	CBitmap bmp_stop;
	CBitmap bmp_start;
	CString m_MaxCurrent;
	INT m_VoltStep;
	INT m_Delay;
	BOOL m_PowerInit;
	CString GetCurrentPath();
	CString m_CurrentPath;
	CString ReadFromInifile(CString KeyName);
	CString m_MaxVol;
	
	int m_InitStap;
	void SetOutputVol(BYTE Commend,CString sVol);
	void SetOutpSate(BOOL state);
	void SetMode(BOOL rmt);
	CByteArray SendData;
	BOOL OpenSerialPort(CString strPortName);
	void FindCommPort(CStringArray* PortList);
	CComDlg(CWnd* pParent = NULL);	// standard constructor


// Dialog Data
	//{{AFX_DATA(CComDlg)
	enum { IDD = IDD_COM_DIALOG };
	CStatic	m_port_bmp;
	CStatic	m_outp_bmp;
	CComboBox	m_PortCombo;
	CString	m_strPort;
	CMSComm	m_msComm;
	CString	m_strVol;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CComDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonPower();
	afx_msg void OnBtnOpenCloseCom();
	afx_msg void OnOnCommMscomm();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBtnUp();
	afx_msg void OnBtnDown();
	afx_msg void OnDdeRequest();//////////////////////
	afx_msg void OnDdePoke();//////////////////////
	afx_msg void OnBtnExit();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMDLG_H__9FC47340_5C48_40CD_A0B6_1EFBFBE19ECC__INCLUDED_)
