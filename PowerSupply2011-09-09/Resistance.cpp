// Resistance.cpp: implementation of the CResistance class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Resistance.h"
#include "mscomm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CResistance::CResistance()
{
	ZeroMemory(rxdata,sizeof(BYTE));
}

CResistance::~CResistance()
{

}

void CResistance::InitalMsg()
{
	m_pCom->SetInputMode(1); //以二进制方式读写数据  
	tdata.SetSize(26);  
	for(int i=0;i<26;i++)
	{
		tdata.SetAt(i,0x00);//共26组数据全部清0
	}
}

void CResistance::InitialCom(int Com_Port)
{
	if(m_pCom->GetPortOpen())
	{
		m_pCom->SetCommPort(FALSE);
	}
	else
	{
		m_pCom->SetCommPort(TRUE);
	}
    ///////设置COM2口程序
	m_pCom->SetCommPort(7);
	if(!m_pCom->GetPortOpen())
	{
		m_pCom->SetPortOpen(TRUE);
	}
	else
	{
		AfxMessageBox("com2口未正常打开！");
		return;
	}
	m_pCom->SetSettings("9600,n,8,1");
	m_pCom->SetRThreshold(26);
	m_pCom->SetInputLen(0); 
	m_pCom->GetInput();
}

void CResistance::StartRemoteControl()
{
	m_pCom->GetInput();
	InitalMsg();
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
		m_pCom->GetInput();
	tdata.SetAt(0,0xaa);
	tdata.SetAt(2,0x28);
	tdata.SetAt(3,0x03);
    tdata.SetAt(25,0xd5);
    m_pCom->SetOutput(COleVariant(tdata));
}

void CResistance::ResOn(int HWordL,int LWordH,int LWordL)
{
	

	////////////////////////
	InitalMsg();
	m_pCom->GetInput();
	tdata.SetAt(0,0xaa);
	tdata.SetAt(2,0x21);
	tdata.SetAt(3,0x01);
	tdata.SetAt(25,0xcc);
	m_pCom->SetOutput(COleVariant(tdata));
	////////////////////////
	Sleep(100);
	///////////////////////// 
	InitalMsg();
	tdata.SetAt(0,0xaa);
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

void CResistance::ReleaseRes()
{
	
	InitalMsg();
	m_pCom->GetInput();
	tdata.SetAt(0,0xaa);
	tdata.SetAt(2,0x21);
	tdata.SetAt(3,0x00);
	tdata.SetAt(4,0x00);
	tdata.SetAt(25,0xcb);
	m_pCom->SetOutput(COleVariant(tdata));
	Sleep(100);
	InitalMsg();
	m_pCom->GetInput();
	tdata.SetAt(0,0xaa);
	tdata.SetAt(2,0x20);
	tdata.SetAt(3,0x00);
	tdata.SetAt(25,0xca);
	m_pCom->SetOutput(COleVariant(tdata));
	Sleep(100);
	RecvMsg(rxdata);

}



void CResistance::Test()
{	
	InitalMsg();
	m_pCom->GetInput();
	tdata.SetAt(0,0xaa);
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

BYTE CResistance::RecvMsg(BYTE *rxdata)//可以返回80h或者完整的rxdata
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
	static int TryTimes=0;//命令发送的尝试次数
	//***使用这种转换方式时一定要将串口控件的InPutMode属性设置为1 - Binary**********//		
	variant_inp=m_pCom->GetInput();   //读缓冲区
	safearray_inp=variant_inp;           //VARIANT型变量转换为ColeSafeArray型变量
	len=safearray_inp.GetOneDimSize(); //得到有效数据长度
	//TRACE("\r\n收到数据，长度:%d",len);
	for(k=0;k<len;k++)
	{
		safearray_inp.GetElement(&k,rxdata+k);//转换为BYTE型数组
	}
	return rxdata[3];
}

void CResistance::SetRes()
{

}

void CResistance::ReadVoltageFromRES(TCHAR* str)
{
	InitalMsg();
	m_pCom->GetInput();
	tdata.SetAt(0,0xaa);
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
	
	
	for(int k=0;k<26;k++)
	{
		rxdata[k]=0x00;
	}
	RecvMsg(rxdata);
	double Result=rxdata[3]+rxdata[4]*0x100;
	Result=Result/1000;
	ZeroMemory(str,sizeof(str)/sizeof(TCHAR));
	sprintf(str,"%0.3f",Result);
}
