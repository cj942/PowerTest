// PowerSupplyDlg.h : header file
//
//{{AFX_INCLUDES()
#include "Power.h"
#include "Resistance.h"
#include "ResA.h"

//}}AFX_INCLUDES

#if !defined(AFX_POWERSUPPLYDLG_H__E8A82CF9_A519_4216_B141_6E84AA3D4E40__INCLUDED_)
#define AFX_POWERSUPPLYDLG_H__E8A82CF9_A519_4216_B141_6E84AA3D4E40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////
// CPowerSupplyDlg dialog
class CMSComm;
class CPowerSupplyDlg : public CDialog
{
// Construction
public:
	void OverVoltage();
	DWORD FindFileName(CString strParentFilePath, DWORD *nCount);
	CStatusBar m_StatusBar;
	void IntialStatusBar();
	void UnderVoltage();
	int nCount;
	void DisplayOutputVoltage();
	void NomalTestJudge();
	BOOL ExportToExcel(CString dFile);
	CString GetCurrentPath();
	void OverCurrentTest();
	void OnVoltageLowerWave();
	void OnVoltageUpperWave();
	void NoloadTest();
	void RatedLoadTest();
	void PowerON_ResON_Lamp();
	void SetLampeOn_Off();
	void FindCommPort(CStringArray *PortList);
	//////配置文件变量
	int m_RateRes,m_RateResA;
	int m_RateVoltage;
	int m_LightRes,m_LightResA;
	int m_UpperVoltage,m_LowVoltage;
	int m_UnderVoltage;
	int m_OverVoltage;
	double m_OutputVoltage,m_OutputVoltageA;
	int Step;
	int m_Error;
	CString ReadFromIniFile(CString KeyName);
	CPower m_Power;
	CResistance m_Res;
	CResA m_ResA;
/////////////////////////EXCEL相关变量//////////////
	CString m_CurrentPath;
	CString m_ModolName;
	CString m_ModolSerial;
	CString m_UserName;

///////////结果判断字符串/////////////////////////////
	CString m_NoLoadResult;
	CString m_RateLoadResult;
	CString m_VoltageWaveResult;
	CString m_OverCurrentResult;
///////////////////////////////////////////////////////
	CPowerSupplyDlg(CWnd* pParent = NULL);	// standard constructor
	CBitmap bmp_start,bmp_stop;
	TCHAR szFile[MAX_PATH];
//////特殊项测试功能包括过流，欠压,过压测试//////////////////////////////
	BOOL bFlag_OverCurrent;
	BOOL bFlag_UnderVoltage;
	BOOL bFlag_OverVoltage;
	
//////////////////////////////////
// Dialog Data
	//{{AFX_DATA(CPowerSupplyDlg)
	enum { IDD = IDD_POWERSUPPLY_DIALOG };
	CComboBox	m_Combo;
	CListBox	m_List;
	CProgressCtrl	m_Progress;
	CStatic	m_Bmp_ResOnA;
	CStatic	m_Bmp_ResRemoteA;
	CStatic	m_Bmp_ResOn;
	CStatic	m_Bmp_PowerOn;
	CStatic	m_Bmp_ResRemote;
	CStatic	m_Bmp_PowerRemote;
	CMSComm	m_PowerCom;
	CMSComm	m_ComForRes;
	int		m_CurrentRes;
	int		m_CurrentVoltage;
	CString m_strModelName;
	CMSComm	m_ResAnotherCom;
	int		m_CurrentResA;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPowerSupplyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPowerSupplyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAbout();
	afx_msg void OnClose();
	afx_msg void OnBtnQuit();
	afx_msg void OnSetting();
	afx_msg void OnRemoteconn();
	afx_msg void OnBtnStop();
	afx_msg void OnBtnStart();
	afx_msg void OnOvercurrentTest();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBtntemp();
	afx_msg void OnInputserials();
	afx_msg void OnOutputOvervoltage();
	afx_msg void OnNoload();
	afx_msg void OnUndervoltage();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnOvervoltage();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POWERSUPPLYDLG_H__E8A82CF9_A519_4216_B141_6E84AA3D4E40__INCLUDED_)
