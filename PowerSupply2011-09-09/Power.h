// Power.h: interface for the CPower class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POWER_H__18CCC890_F95B_4CC6_8A0B_C968E987F66B__INCLUDED_)
#define AFX_POWER_H__18CCC890_F95B_4CC6_8A0B_C968E987F66B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Power.h"
#include "mscomm.h"

class CPower  
{
public:
	CMSComm *m_pCom;
	CByteArray tdata;
	BYTE rxdata[100];
	BOOL bFlag_AllowRelease;
public:
	BYTE RecvMsg(BYTE *rxdata);
	void ReleasePower();
	void PowerOn(int HWordL,int LWordH,int LWordL);
	void StartRemoteControl();
	void InitialMsg();
	void InitialCom();
	CPower();
	virtual ~CPower();

};

#endif // !defined(AFX_POWER_H__18CCC890_F95B_4CC6_8A0B_C968E987F66B__INCLUDED_)
