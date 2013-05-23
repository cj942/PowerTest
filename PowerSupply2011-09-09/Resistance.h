// Resistance.h: interface for the CResistance class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESISTANCE_H__0CE19DDB_A3F3_41DF_AA0B_00F18ECEAC1B__INCLUDED_)
#define AFX_RESISTANCE_H__0CE19DDB_A3F3_41DF_AA0B_00F18ECEAC1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include "mscomm.h"
#include "Resistance.h"
class CMSComm;
class CResistance  
{
public:
	void ReadVoltageFromRES(TCHAR* str);
	void SetRes();
	void Test();
	void ReleaseRes();
	void ResOn(int HWordL,int LWordH,int LWordL);
	void StartRemoteControl();
	void InitialCom(int Com_Port);
	BYTE RecvMsg(BYTE *rxdata);
	CMSComm *m_pCom;
	CByteArray tdata;
	BYTE rxdata[100];
	void InitalMsg();
	CResistance();
	virtual ~CResistance();

};

#endif // !defined(AFX_RESISTANCE_H__0CE19DDB_A3F3_41DF_AA0B_00F18ECEAC1B__INCLUDED_)
