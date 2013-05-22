//DdeServerM.h文件
#include "stdafx.h"
#include "ddeml.h"
#define WM_DDEREQUEST		 WM_USER+1
#define WM_DDEPOKE			 WM_USER+2
#define WM_DDECONNECT		 WM_USER+3
#define WM_DDEDISCONNECT	 WM_USER+4
CString strItem[300],strData[300];
HSZ hszSvr,hszTopic,hszItem[300];
int ItemCount=0,Index=-1;DWORD idInst=0;
HWND m_hMainWnd;

//DDE回调函数，用于处理DDE通信事件
HDDEDATA CALLBACK DdeCallback(   
								  UINT   uType,           //   Transaction   type.   
								  UINT   uFmt,             //   Clipboard   data   format.   
								  HCONV   hconv,         //   Handle   to   the   conversation.   
								  HSZ   Topic,               //   Handle   to   a   string.   
								  HSZ   Item,               //   Handle   to   a   string.   
								  HDDEDATA   hdata,   //   Handle   to   a   global   memory   object.   
								  DWORD   dwData1,     //   Transaction-specific   data.   
								  DWORD   dwData2)     //   Transaction-specific   data.   
{  
	int i;CString sData;
	char tmp[255]; 
	if(Topic!=hszTopic)return 0;
	try
	{	
		switch(uType) 
		{ 
		case XTYP_ADVSTART:return ((HDDEDATA)TRUE);
		case XTYP_CONNECT:SendMessage(m_hMainWnd,WM_DDECONNECT,0,0);
			return ((HDDEDATA)TRUE); //// 请求连接 允许 WM_DDECONNECT
		case XTYP_DISCONNECT:SendMessage(m_hMainWnd,WM_DDEDISCONNECT,0,0);
			return ((HDDEDATA)TRUE); //// 请求连接 允许WM_DDEDISCONNECT
		case XTYP_POKE: // 有数据到来 
			DdeGetData(hdata,LPBYTE(tmp),255,NULL);
			sData.Format("%s",tmp);sData.TrimLeft();sData.TrimRight();
			for(i=0;i<ItemCount;i++)
			{
				if(Item==hszItem[i])
				{
					strData[i]=sData;
					Index=i;
				}
			}
			SendMessage(m_hMainWnd,WM_DDEPOKE,0,0);
			return ((HDDEDATA)DDE_FACK); // 回执 
		case XTYP_ADVREQ:  
		case XTYP_REQUEST: // 数据请求 
			SendMessage(m_hMainWnd,WM_DDEREQUEST,0,0);
			for(i=0;i<ItemCount;i++)
			{
				if(Item==hszItem[i])
				{
					sData=strData[i];
					Index=i;
				}
			}
			return DdeCreateDataHandle(idInst,(LPBYTE)(LPCTSTR)sData,255,NULL,Item,CF_TEXT,NULL);
		default:return 0;
		} 	
	}
	catch(...)
	{
		//AfxMessageBox("DDE回调函数失败!");
		return ((HDDEDATA)DDE_FACK);
	}
	return   0;   
}

void RegisterDdeServer(LPCTSTR szApp,LPCTSTR szTopic)
{
	//注册DDE服务器
	DdeInitialize(&idInst,(PFNCALLBACK)DdeCallback,CBF_FAIL_EXECUTES|CBF_SKIP_ALLNOTIFICATIONS|MF_ERRORS,NULL);
	//建立应用程序名、主题和项目等标识的句柄
	hszSvr=DdeCreateStringHandle(idInst,szApp,0);
	hszTopic=DdeCreateStringHandle(idInst,szTopic,0);
	for(int i=0;i<ItemCount;i++)
	{
		hszItem[i]=DdeCreateStringHandle(idInst,strItem[i],0);
	}
	//在操作系统中注册该DDE服务
	DdeNameService(idInst,hszSvr,0L,DNS_REGISTER);
}