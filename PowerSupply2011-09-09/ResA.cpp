// ResA.cpp: implementation of the CResA class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ResA.h"
#include "mscomm.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CResA::CResA()
{
	ZeroMemory(rxdata,sizeof(BYTE));
}

CResA::~CResA()
{

}
void CResA::InitalMsg()
{
	m_pCom->SetInputMode(1); //�Զ����Ʒ�ʽ��д����  
	tdata.SetSize(26);  
	for(int i=0;i<26;i++)
	{
		tdata.SetAt(i,0x00);//��26������ȫ����0
	}
}

void CResA::InitialCom(int Com_Port)
{
		if(m_pCom->GetPortOpen())
	{
		m_pCom->SetCommPort(FALSE);
	}
		else
	{
		m_pCom->SetCommPort(TRUE);
	}
    ///////����COM3�ڳ���
	m_pCom->SetCommPort(8);
	if(!m_pCom->GetPortOpen())
	{
		m_pCom->SetPortOpen(TRUE);
	}
	else
	{
		AfxMessageBox("com3��δ�����򿪣�");
		return;
	}
	m_pCom->SetSettings("9600,n,8,1");
	m_pCom->SetRThreshold(26);
	m_pCom->SetInputLen(0); 
	m_pCom->GetInput();
}

void CResA::StartRemoteControl()
{
	m_pCom->GetInput();
	InitalMsg();
	tdata.SetAt(0,0xaa);
	tdata.SetAt(1,0x01);
	tdata.SetAt(2,0x20);
	tdata.SetAt(3,0x01);
	int Sum=0;
	for(int i=0;i<25;i++)
	{
		Sum+=tdata.GetAt(i);
	}
	Sum&=0x0ff;
	tdata.SetAt(25,Sum);
	m_pCom->SetOutput(COleVariant(tdata));
	Sleep(100);
	RecvMsg(rxdata);
	InitalMsg();
	m_pCom->GetInput();
	tdata.SetAt(0,0xaa);
	tdata.SetAt(1,0x01);
	tdata.SetAt(2,0x28);
	tdata.SetAt(3,0x03);
    tdata.SetAt(25,0xd6);
    m_pCom->SetOutput(COleVariant(tdata));
}

void CResA::ResOn(int HWordL,int LWordH,int LWordL)
{

	InitalMsg();
	m_pCom->GetInput();
	tdata.SetAt(0,0xaa);
	tdata.SetAt(1,0x01);
	tdata.SetAt(2,0x21);
	tdata.SetAt(3,0x01);
	tdata.SetAt(25,0xcd);
	m_pCom->SetOutput(COleVariant(tdata));
	Sleep(100);
	InitalMsg();
	tdata.SetAt(0,0xaa);
	tdata.SetAt(1,0x01);
	tdata.SetAt(2,0x30);
	tdata.SetAt(3,LWordL);
	tdata.SetAt(4,LWordH);
	tdata.SetAt(5,HWordL);
	int Sum=0;
	for(int i=0;i<25;i++)
	{
		Sum+=tdata.GetAt(i);
	}
	Sum&=0x0ff;
	tdata.SetAt(25,Sum);
	m_pCom->SetOutput(COleVariant(tdata));
	Sleep(100);
	RecvMsg(rxdata);
}

void CResA::ReleaseRes()
{
	
	InitalMsg();
	m_pCom->GetInput();
	tdata.SetAt(0,0xaa);
	tdata.SetAt(1,0x01);
	tdata.SetAt(2,0x21);
	tdata.SetAt(3,0x00);
	tdata.SetAt(4,0x00);
	tdata.SetAt(25,0xcc);
	m_pCom->SetOutput(COleVariant(tdata));
	Sleep(100);
	InitalMsg();
	m_pCom->GetInput();
	tdata.SetAt(0,0xaa);
	tdata.SetAt(1,0x01);
	tdata.SetAt(2,0x20);
	tdata.SetAt(3,0x00);
	tdata.SetAt(25,0xcb);
	m_pCom->SetOutput(COleVariant(tdata));
	Sleep(100);
	RecvMsg(rxdata);

}



void CResA::Test()
{	
	InitalMsg();
	m_pCom->GetInput();
	tdata.SetAt(0,0xaa);
	tdata.SetAt(1,0x01);
	tdata.SetAt(2,0x2A);
	tdata.SetAt(3,0xB8);
	tdata.SetAt(4,0x0B);
	int Sum=0;
	for(int i=0;i<25;i++)
	{
		Sum+=tdata.GetAt(i);
	}
	Sum&=0x0ff;
	tdata.SetAt(25,Sum);
	m_pCom->SetOutput(COleVariant(tdata));
}

BYTE CResA::RecvMsg(BYTE *rxdata)//���Է���80h����������rxdata
{
	for(int i=0;i<100;i++)
	{
		rxdata[i]=0x00;
		rxdata[i]=0x00;
	}
	VARIANT variant_inp;
	COleSafeArray safearray_inp;
	LONG len;
	LONG k;CString str;
	ZeroMemory(rxdata,sizeof(BYTE));
	CString strtemp;
	static int TryTimes=0;//����͵ĳ��Դ���
	//***ʹ������ת����ʽʱһ��Ҫ�����ڿؼ���InPutMode��������Ϊ1 - Binary**********//		
	variant_inp=m_pCom->GetInput();   //��������
	safearray_inp=variant_inp;           //VARIANT�ͱ���ת��ΪColeSafeArray�ͱ���
	len=safearray_inp.GetOneDimSize(); //�õ���Ч���ݳ���
	//TRACE("\r\n�յ����ݣ�����:%d",len);
	for(k=0;k<len;k++)
	{
		safearray_inp.GetElement(&k,rxdata+k);//ת��ΪBYTE������
	}
	return rxdata[3];
}

void CResA::ReadVoltageFromRES(TCHAR* str)
{
	InitalMsg();
	m_pCom->GetInput();
	tdata.SetAt(0,0xaa);
	tdata.SetAt(1,0x01);
	tdata.SetAt(2,0x5F);
	tdata.SetAt(3,0x00);
	tdata.SetAt(4,0x00);
	int Sum=0;
	for(int i=0;i<25;i++)
	{
		Sum+=tdata.GetAt(i);
	}
	Sum&=0x0ff;
	tdata.SetAt(25,Sum);
	m_pCom->SetOutput(COleVariant(tdata));
	Sleep(100);
	
	
	for(int k=0;k<100;k++)
	{
		rxdata[k]=0x00;
	}
	RecvMsg(rxdata);
	double Result=rxdata[3]+rxdata[4]*0x100;
	Result=Result/1000;
	ZeroMemory(str,sizeof(str)/sizeof(TCHAR));
	sprintf(str,"%0.3f",Result);
}