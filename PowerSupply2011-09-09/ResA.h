// ResA.h: interface for the CResA class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESA_H__2F0A9687_3F8F_43F1_ADA3_52D33FACD77E__INCLUDED_)
#define AFX_RESA_H__2F0A9687_3F8F_43F1_ADA3_52D33FACD77E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CMSComm;
class CResA  //负载2用新类表示，地址为要加入0x01
{
public:

	void Test();
	void ReleaseRes();
	void ResOn(int HWordL,int LWordH,int LWordL);
	void ReadVoltageFromRES(TCHAR* str);
	void StartRemoteControl();
	void InitialCom(int Com_Port);
	BYTE RecvMsg(BYTE *rxdata);
	CMSComm *m_pCom;
	CByteArray tdata;
	BYTE rxdata[100];
	void InitalMsg();
	CResA();
	virtual ~CResA();
};

#endif // !defined(AFX_RESA_H__2F0A9687_3F8F_43F1_ADA3_52D33FACD77E__INCLUDED_)
