// Power.cpp: implementation of the CPower class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Power.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPower::CPower()
{
	ZeroMemory(rxdata,sizeof(BYTE));
	bFlag_AllowRelease=FALSE;
}

CPower::~CPower()
{

}

void CPower::InitialCom()
{
	if(m_pCom->GetPortOpen())
	{
		m_pCom->SetCommPort(FALSE);
	}
	else
	{
		m_pCom->SetCommPort(TRUE);
	}
    ///////����COM1�ڳ���
	m_pCom->SetCommPort(1);
	if(!m_pCom->GetPortOpen())
	{
		m_pCom->SetPortOpen(TRUE);
	}
	else
	{
		AfxMessageBox("com1��δ�����򿪣�");
		return;
	}
	m_pCom->SetSettings("9600,n,8,1");
	m_pCom->SetRThreshold(26);
	m_pCom->SetInputLen(0);
	m_pCom->GetInput();

	
}

void CPower::InitialMsg()
{
	m_pCom->SetInputMode(1); //�Զ����Ʒ�ʽ��д����  
	tdata.SetSize(26);  
	for(int i=0;i<26;i++)
	{
		tdata.SetAt(i,0x00);//��26������ȫ����0
	}
}

void CPower::StartRemoteControl()
{
	bFlag_AllowRelease=TRUE;
	InitialMsg();
	m_pCom->GetInput();
	tdata.SetAt(0,0xaa);
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
}



void CPower::PowerOn(int HWordL,int LWordH,int LWordL)
{
		
	InitialMsg();
	m_pCom->GetInput();
	tdata.SetAt(0,0xaa);
	tdata.SetAt(2,0x21);
	tdata.SetAt(3,0x01);
	tdata.SetAt(4,0x00);
	tdata.SetAt(25,0xcc);
	m_pCom->SetOutput(COleVariant(tdata));
	Sleep(100);
	tdata.SetAt(0,0xaa);
	tdata.SetAt(2,0x23);
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
	InitialMsg();
	Sleep(100);
	RecvMsg(rxdata);
}



void CPower::ReleasePower()
{
	if(1==bFlag_AllowRelease)
	{
		InitialMsg();
		m_pCom->GetInput();
		tdata.SetAt(0,0xaa);
		tdata.SetAt(2,0x21);
		tdata.SetAt(3,0x00);
		tdata.SetAt(4,0x00);
		tdata.SetAt(25,0xcb);
		m_pCom->SetOutput(COleVariant(tdata));
	}
	
	Sleep(100);
	tdata.SetAt(0,0xaa);
	tdata.SetAt(2,0x20);
	tdata.SetAt(3,0x00);
	tdata.SetAt(25,0xca);
	m_pCom->SetOutput(COleVariant(tdata));
	Sleep(100);
	RecvMsg(rxdata);
}



BYTE CPower::RecvMsg(BYTE *rxdata)//���Է���80h����������rxdata
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
