// IT6832Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "IT6832.h"
#include "IT6832Dlg.h"
#include "DdeServerM.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
extern CString strItem[300];//存放注册的变量名	
extern CString strData[300];//存放变量值
extern int ItemCount;//存放变量个数
extern HWND m_hMainWnd;//存放主窗口句柄
extern int Index;//存放数据索引


class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIT6832Dlg dialog

CIT6832Dlg::CIT6832Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIT6832Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIT6832Dlg)
	m_strPort = _T("");
	m_strVol = _T("0");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIT6832Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIT6832Dlg)
	DDX_Control(pDX, IDC_STATIC_STOP, m_outp_bmp);
	DDX_Control(pDX, IDC_STATIC_START, m_port_bmp);
	DDX_Control(pDX, IDC_COMBO_PORT, m_PortCombo);
	DDX_CBString(pDX, IDC_COMBO_PORT, m_strPort);
	DDX_Control(pDX, IDC_MSCOMM, m_msComm);
	DDX_Text(pDX, IDC_EDIT_VOLT, m_strVol);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIT6832Dlg, CDialog)
	//{{AFX_MSG_MAP(CIT6832Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPEN_CLOSE_COM, OnBtnOpenCloseCom)
	ON_BN_CLICKED(IDC_BTN_SEND_VOLT, OnBtnSendVolt)
	ON_BN_CLICKED(IDC_BTN_VOLT_UP, OnBtnVoltUp)
	ON_BN_CLICKED(IDC_BTN_VOLT_DOWN, OnBtnVoltDown)
	ON_WM_TIMER()
	ON_MESSAGE(WM_DDEREQUEST,OnDdeRequest)//////////////////////////////////
	ON_MESSAGE(WM_DDEPOKE,OnDdePoke)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIT6832Dlg message handlers

BOOL CIT6832Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	m_CurrentPath=GetCurrentPath();
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	bmp_stop.LoadBitmap(IDB_BITMAP_STOP);
	bmp_start.LoadBitmap(IDB_BITMAP_START);
	
	// TODO: Add extra initialization here
	m_hMainWnd=this->m_hWnd;//将当前的窗口句柄赋值给DDE中的窗口句柄
	/***************************************************************/
	/**********************注册DDE服务器****************************/
	/*******服务器名称：IT6832Control*******/
	/*********话题名称：IT6832Topic *******/
	/***************************************************************/
	ItemCount=1;//DDE服务器中注册的变量个数
	strItem[0]="IT6832_Voltage";//操作命令码
	RegisterDdeServer(LPCTSTR("IT6832Control"),LPCTSTR("IT6832Topic"));
	
	
	//获取计算机上安装的串口
	CStringArray PortList;
	FindCommPort(&PortList);
	if(PortList.GetSize()<=0)
		return FALSE;
	for (int i=0;i<PortList.GetSize();i++)//将获取的串口添加到串口号列表框中
		if (m_PortCombo.FindString(0,PortList.GetAt(i))==CB_ERR)
			m_PortCombo.AddString(PortList.GetAt(i));
		m_strPort=ReadFromInifile("PortID");
		m_MaxVol=ReadFromInifile("MaxVol");
		m_MaxCurrent=ReadFromInifile("Current");
		m_Delay=atoi(ReadFromInifile("Delay"));
		m_VoltStep=atoi(ReadFromInifile("VoltStep"));
		UpdateData(FALSE);
		
		return TRUE;  // return TRUE  unless you set the focus to a control
}

void CIT6832Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CIT6832Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CIT6832Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


///////////////////////////////////////////////////
void CIT6832Dlg::FindCommPort(CStringArray *PortList)
{
	HKEY   hKey; 
	int PortNum=0;
	if(   ::RegOpenKeyEx(   HKEY_LOCAL_MACHINE,   
		"Hardware\\DeviceMap\\SerialComm",   
		NULL,   
		KEY_READ,   
		&hKey)   ==   ERROR_SUCCESS)   //   打开串口注册表   
	{   
		int   i=0;   
		char   portName[256],commName[256];   
		DWORD   dwLong,dwSize;   
		
		while(1)   
		{   
			dwLong   =   dwSize   =   sizeof(portName);   
			if(   ::RegEnumValue(   hKey,   
				i,   
				portName,   
				&dwLong,   
				NULL,   
				NULL,   
				(PUCHAR)commName,   
				&dwSize   )   ==   ERROR_NO_MORE_ITEMS   )   //   枚举串口   
				break;   
			PortList->Add(commName);
			i++;   
		}    
		RegCloseKey(hKey);   
	}  
}
///////////////////////////////////////////////////////////////配置串口波特率、校验、数据位、停止位等
BOOL CIT6832Dlg::OpenSerialPort(CString strPortName)
{
	int m_PortID;
	m_PortID=atoi(strPortName.Right(strPortName.GetLength()-3));
	//*********一定要选中串口控件硬件属性页中的DTR有效选项*************//
	if(m_msComm.GetPortOpen())
		m_msComm.SetPortOpen(FALSE);
	m_msComm.SetCommPort(m_PortID);   //选择串口
	if( !m_msComm.GetPortOpen())
		m_msComm.SetPortOpen(TRUE);//打开串口
	else 
	{
		CString strInfo;
		strInfo="串口"+strPortName+"打开失败!";
		AfxMessageBox(strInfo);
		return FALSE;
	}
	
	m_msComm.SetSettings("9600,N,8,1"); //波特率,校验,数据位,停止位
	m_msComm.SetInputMode(1);
	m_msComm.SetRThreshold(26); 
	//参数1表示每当串口接收缓冲区中有多于或等于1个字符时将引发一个接收数据的OnComm事件
	m_msComm.SetInputLen(0);  //设置当前接收区数据长度为0
	m_msComm.GetInput();//先预读缓冲区以清除残留数据
	return TRUE;
}

BEGIN_EVENTSINK_MAP(CIT6832Dlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CIT6832Dlg)
	ON_EVENT(CIT6832Dlg, IDC_MSCOMM, 1 /* OnComm */, OnOnCommMscomm, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

/////////////////////////////////////////////串口控件配置程序
void CIT6832Dlg::OnOnCommMscomm() 
{
	// TODO: Add your control notification handler code here
	VARIANT variant_inp;
	COleSafeArray safearray_inp;
	LONG len;
	LONG k;CString str;
	BYTE rxdata[0x20000]; //设置BYTE数组 An 8-bit integerthat is not signed.
	CString strtemp;
	static int TryTimes=0;//命令发送的尝试次数
	if(m_msComm.GetCommEvent()==2)     //事件值为2表示接收缓冲区内有字符
	{
		//***使用这种转换方式时一定要将串口控件的InPutMode属性设置为1 - Binary**********//		
		variant_inp=m_msComm.GetInput();   //读缓冲区
		safearray_inp=variant_inp;           //VARIANT型变量转换为ColeSafeArray型变量
		len=safearray_inp.GetOneDimSize(); //得到有效数据长度
		for(k=0;k<len;k++)
			safearray_inp.GetElement(&k,rxdata+k);//转换为BYTE型数组
		if (rxdata[3]==0x80)   //回读指令，判定rxdata数组中的第四位是否为80H
		{
			m_InitStap++;
			if(m_InitStap==1)
				m_port_bmp.SetBitmap(HBITMAP(bmp_start));//设置电源远控模式成功
			if(m_InitStap==2)
				m_outp_bmp.SetBitmap(HBITMAP(bmp_start));//设置电源输出成功
		}
		else
		{
			if(m_InitStap==1)
				m_port_bmp.SetBitmap(HBITMAP(bmp_stop));  //停止图标
			if(m_InitStap==2)
				m_outp_bmp.SetBitmap(HBITMAP(bmp_stop));  //停止图标
			
		}
		
		if(m_InitStap==0)
			SetMode(true);//设置电源远控模式
		else if(m_InitStap==1)
			SetOutpSate(true);//设置电源输出ON
		else if(m_InitStap==2)
			SetOutputVol(0x23,"0");//设置电源初始输出电压为0
		else if(m_InitStap==3)
			SetOutputVol(0x22,m_MaxVol);//设置电源电压上限,上限值在配置文件中
		else if (m_InitStap==4) 		
			SetOutputVol(0x24,m_MaxCurrent);//设置电源最大输出电流,上限值在配置文件中
	}
}

void CIT6832Dlg::OnBtnOpenCloseCom() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_InitStap=0;
	if (!m_msComm.GetPortOpen())
	{
		OpenSerialPort(m_strPort);     //打开串口
		GetDlgItem(IDC_BTN_OPEN_CLOSE_COM)->SetWindowText("关闭串口");
		GetDlgItem(IDC_COMBO_PORT)->EnableWindow(false);
		SetMode(true);                 //设置电源模式为1：远程操作模式
	}
	else
	{
		GetDlgItem(IDC_COMBO_PORT)->EnableWindow(true);
		KillTimer(1);
		GetDlgItem(IDC_BTN_VOLT_UP)->SetWindowText("电压上升");
		GetDlgItem(IDC_BTN_VOLT_DOWN)->EnableWindow(true);
		KillTimer(2);
		GetDlgItem(IDC_BTN_VOLT_DOWN)->SetWindowText("电压下降");
		GetDlgItem(IDC_BTN_VOLT_UP)->EnableWindow(true);
		
		m_msComm.SetPortOpen(FALSE);
		GetDlgItem(IDC_BTN_OPEN_CLOSE_COM)->SetWindowText("打开串口");
		m_port_bmp.SetBitmap(HBITMAP(bmp_stop));   //停止图标
		m_outp_bmp.SetBitmap(HBITMAP(bmp_stop));   //停止图标
	}	

}
//////////////////////////////////////////////////////设置电源为远程操作模式（20H）
void CIT6832Dlg::SetMode(BOOL rmt)
{
	SendDate.SetSize(26);
	for (int i=0;i<26;i++)   //将26个命令字节初始化为0
	{
		SendDate.SetAt(i,0x00);
	}
		SendDate.SetAt(0,0xaa);  
	SendDate.SetAt(2,0x20);
	if (rmt)
	{
		SendDate.SetAt(3,0x01);
		SendDate.SetAt(25,0xcb);
	}	
	else
	{
		SendDate.SetAt(3,0x00);
		SendDate.SetAt(25,0xca);
	}

	m_msComm.SetOutput(COleVariant(SendDate));
}
//////////////////////////////////////////////////////设置电源输出状态（21H）
void CIT6832Dlg::SetOutpSate(BOOL state)
{
	SendDate.SetSize(26);
	for (int i=0;i<26;i++)   //将26个命令字节初始化为0
	{
		SendDate.SetAt(i,0x00);
	}
	SendDate.SetAt(0,0xaa);  
	SendDate.SetAt(2,0x21);
	if (state)
	{
		SendDate.SetAt(3,0x01);
		SendDate.SetAt(25,0xcc);
	}	
	else
	{
		SendDate.SetAt(3,0x00);
		SendDate.SetAt(25,0xcb);
	}
	
	m_msComm.SetOutput(COleVariant(SendDate));
}
////////////////////////////////////////////设置电源输出电压、电压上限、最大输出电流（23H、22H、24H）
void CIT6832Dlg::SetOutputVol(BYTE Commend, CString sVol)
{
	SendDate.SetSize(26);
	for (int i=0;i<26;i++)   //将26个命令字节初始化为0
	{
		SendDate.SetAt(i,0x00);
	}
	SendDate.SetAt(0,0xaa);  
	SendDate.SetAt(2,Commend);
	int ivol=atoi(sVol);
	SendDate.SetAt(3,BYTE(ivol%256));
	ivol=ivol/256;
	SendDate.SetAt(4,BYTE(ivol%256));
	ivol=ivol/256;
	SendDate.SetAt(5,BYTE(ivol%256));
	ivol=ivol/256;
	SendDate.SetAt(6,BYTE(ivol%256));
	BYTE he=0;
	for (int j=0;j<25;j++)
	{
		he=he+SendDate.GetAt(j);
	}
	SendDate.SetAt(25,BYTE(he));
	m_msComm.SetOutput(COleVariant(SendDate));
}

///////////////////////////////////////////////////////////读取配置文件
CString CIT6832Dlg::ReadFromInifile(CString KeyName)
{
	char TempVal[50];CString str;
	GetPrivateProfileString("IT6832",KeyName,"",TempVal,50,m_CurrentPath+"\\IT6832.ini");
	str.Format("%s",TempVal);str.TrimRight();
	return str;
}

CString CIT6832Dlg::GetCurrentPath()
{
	//获取应用程序的当前路径
	char path[MAX_PATH];CString str,strpath;
	::GetModuleFileName(NULL,path,MAX_PATH);
	str=path;
	int nPos=str.ReverseFind('\\');
	strpath=str.Left(nPos);
	return strpath;
}

////////////////////////////////////////////////////////发送电源输出的电压指令
void CIT6832Dlg::OnBtnSendVolt() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_msComm.GetPortOpen()) 
	{
		SetOutputVol(0x23,m_strVol);
		m_msComm.SetInputLen(0);  //设置当前接收区数据长度为0
		m_msComm.GetInput();//先预读缓冲区以清除残留数据
	}
	else 
	{
		MessageBox("请先打开串口！","提示",MB_ICONINFORMATION|MB_OK);
	}
}
///////////////////////////////////////////////////////////输出电压以volStep的步进上升
void CIT6832Dlg::OnBtnVoltUp() 
{
	// TODO: Add your control notification handler code here
	CString str;
	GetDlgItem(IDC_BTN_VOLT_UP)->GetWindowText(str);
	if (!m_msComm.GetPortOpen()) 
	{
		MessageBox("请先打开串口!","提示",MB_ICONINFORMATION|MB_OK);
	}
	else if (m_msComm.GetPortOpen()) 
	{
		if (str=="电压上升")
		{
			SetTimer(1,m_Delay,NULL);
			GetDlgItem(IDC_BTN_VOLT_UP)->SetWindowText("停止");
			GetDlgItem(IDC_BTN_VOLT_DOWN)->EnableWindow(false);
		}
		else
		{
			KillTimer(1);
			GetDlgItem(IDC_BTN_VOLT_UP)->SetWindowText("电压上升");
			GetDlgItem(IDC_BTN_VOLT_DOWN)->EnableWindow(true);
		}
	}

}
///////////////////////////////////////////////////////////输出电压以volStep的步进下降
void CIT6832Dlg::OnBtnVoltDown() 
{
	// TODO: Add your control notification handler code here
	CString str;
	GetDlgItem(IDC_BTN_VOLT_DOWN)->GetWindowText(str);
	if (!m_msComm.GetPortOpen()) 
	{
		MessageBox("请先打开串口!","提示",MB_ICONINFORMATION|MB_OK);
	}
	else 
	{
		if (str=="电压下降")
		{
			SetTimer(2,m_Delay,NULL);
			GetDlgItem(IDC_BTN_VOLT_DOWN)->SetWindowText("停止");
			GetDlgItem(IDC_BTN_VOLT_UP)->EnableWindow(false);
		}
		else
		{
			KillTimer(2);
			GetDlgItem(IDC_BTN_VOLT_DOWN)->SetWindowText("电压下降");
			GetDlgItem(IDC_BTN_VOLT_UP)->EnableWindow(true);
		}
	}
}

void CIT6832Dlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	// TODO: Add your message handler code here and/or call default
 	UpdateData(TRUE);
 	int i=atoi(m_strVol);
 	int j=atoi(m_MaxVol);
 	if(nIDEvent==1)
 	{
 		i+=m_VoltStep;
 		if(i>j)
 		{
 			i=j;
 			KillTimer(1);
 			GetDlgItem(IDC_BTN_VOLT_UP)->SetWindowText("电压上升");
 			GetDlgItem(IDC_BTN_VOLT_DOWN)->EnableWindow(true);
 		}
 	}
 	else
 	{
 		i-=m_VoltStep;
		if (i<0)
 		{
 			i=0;KillTimer(2);
 			GetDlgItem(IDC_BTN_VOLT_DOWN)->SetWindowText("电压下降");
			GetDlgItem(IDC_BTN_VOLT_UP)->EnableWindow(true);
 		}
 	}
 	m_strVol.Format("%d",i);
 	UpdateData(FALSE);
 	SetOutputVol(0x23,m_strVol);
 //	if(i>140000)KillTimer(1);
	CDialog::OnTimer(nIDEvent);
}

void CIT6832Dlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	if (!m_msComm.GetPortOpen()) 
	{
		CDialog::OnCancel();
	}
	else if (m_msComm.GetPortOpen()) 
	{
		SetOutputVol(0x23,"0");//设置电源电压为0
		SetOutpSate(FALSE);//设置电源输出
		Sleep(100);
		CDialog::OnCancel();
	}
}

//接收到DDE客户端的数据请求
void CIT6832Dlg::OnDdeRequest()
{
	UpdateData(TRUE);
/*	switch(Index)
	{
	case 0:break;
	case 1:strData[1]=m_SendData;break;
	case 2:strData[2]=m_MeasureData;break;
	case 3:strData[3]=m_hzRange;break;
	case 4:strData[4]=m_Temperature;break;
	case 5:strData[5].Format("%d",m_Range);break;
	case 6:break;
	case 7:strData[7].Format("%d",m_isAlwaysMeasure);break;
	case 8:strData[8]=JY_Send_OK;break;
	default:break;
	}	*/
}

//DDE客户端发来数据
void CIT6832Dlg::OnDdePoke()
{
	UpdateData(TRUE);
	m_strVol=strData[0];
	UpdateData(FALSE);
	SetOutputVol(0x23,m_strVol);
}



BOOL CIT6832Dlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN)
	{
		if(pMsg->wParam==VK_RETURN)
			return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}
