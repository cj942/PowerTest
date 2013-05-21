// IT6832Dlg.h : header file
//
//{{AFX_INCLUDES()
#include "mscomm.h"
//}}AFX_INCLUDES

#if !defined(AFX_IT6832DLG_H__17314AD9_7DF5_497E_89BF_81A9319BE03A__INCLUDED_)
#define AFX_IT6832DLG_H__17314AD9_7DF5_497E_89BF_81A9319BE03A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CIT6832Dlg dialog

class CIT6832Dlg : public CDialog
{
// Construction
public:
	int m_Delay;
	int m_VoltStep;
	CString m_CurrentPath;
	CString GetCurrentPath();
	CString ReadFromInifile(CString KeyName);
	CBitmap bmp_start,bmp_stop;
	CString m_MaxCurrent;
	CString m_MaxVol;
	void SetOutputVol(BYTE Commend,CString sVol);
	void SetOutpSate(BOOL state);
	CByteArray SendDate;	
	void SetMode(BOOL rmt);
	int m_InitStap;
	BOOL OpenSerialPort(CString strPortName);
	void FindCommPort(CStringArray *PortList);
	CIT6832Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CIT6832Dlg)
	enum { IDD = IDD_IT6832_DIALOG };
	CStatic	m_outp_bmp;
	CStatic	m_port_bmp;
	CComboBox	m_PortCombo;
	CString	m_strPort;
	CMSComm	m_msComm;
	CString	m_strVol;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIT6832Dlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CIT6832Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOnCommMscomm();
	afx_msg void OnBtnOpenCloseCom();
	afx_msg void OnBtnSendVolt();
	afx_msg void OnBtnVoltUp();
	afx_msg void OnBtnVoltDown();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnCancel();
	DECLARE_EVENTSINK_MAP()
	afx_msg void OnDdeRequest();//////////////////////
	afx_msg void OnDdePoke();//////////////////////
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IT6832DLG_H__17314AD9_7DF5_497E_89BF_81A9319BE03A__INCLUDED_)
