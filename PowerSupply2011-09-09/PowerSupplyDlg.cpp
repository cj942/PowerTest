// PowerSupplyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PowerSupply.h"
#include "PowerSupplyDlg.h"
#include <commdlg.h>
#include "DdeServerM.h"
#include "excel9.h"
#include <comdef.h>
#include "SerialsInputDialog.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString strLoginName,strLoginPassword,strSerirals;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

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
////////DDE���Ա���
extern CString strItem[300];//���ע��ı�����	
extern CString strData[300];//��ű���ֵ
extern int ItemCount;//��ű�������
extern HWND m_hMainWnd;//��������ھ��
extern int Index;//�����������
/////////////////////////////////////////////////////////////////////////////
// CPowerSupplyDlg dialog

CPowerSupplyDlg::CPowerSupplyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPowerSupplyDlg::IDD, pParent)
{
	/////////����ִ��///////
	Step=0;
	m_Error=0;
	nCount=1;
	/////////�����////////
	m_RateRes=1000;
	m_RateResA=1000;
	////////����///////////
	m_LightRes=1000;
	m_LightResA=1000;
	//////////���ѹֵ�벨����ѹֵ///////
	m_RateVoltage=0;
	m_UpperVoltage=0;
	m_LowVoltage=0;
	m_OverVoltage=0;
	/////////�����ѹֵ///////////////
	m_OutputVoltage=0;
	m_OutputVoltageA=0;
	//{{AFX_DATA_INIT(CPowerSupplyDlg)
	m_CurrentRes = 0;
	m_CurrentVoltage = 0;
	m_ModolName="";
	m_ModolSerial=strSerirals;
	m_UserName=strLoginName;
	m_OverCurrentResult="�ϸ�";
	m_RateLoadResult="�ϸ�";
	m_VoltageWaveResult="�ϸ�";
	m_NoLoadResult="�ϸ�";
	bFlag_OverCurrent=FALSE;
	bFlag_UnderVoltage=FALSE;
	bFlag_OverVoltage=FALSE;
	m_CurrentResA = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPowerSupplyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPowerSupplyDlg)
	DDX_Control(pDX, IDC_COMBO1, m_Combo);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Control(pDX, IDC_PROGRESS, m_Progress);
	DDX_Control(pDX, IDC_STATIC_RESONA, m_Bmp_ResOnA);
	DDX_Control(pDX, IDC_STATIC_REMOTERESA, m_Bmp_ResRemoteA);
	DDX_Control(pDX, IDC_STATIC_RESON, m_Bmp_ResOn);
	DDX_Control(pDX, IDC_STATIC_POWERONLAMP, m_Bmp_PowerOn);
	DDX_Control(pDX, IDC_STATIC_REMOTERES, m_Bmp_ResRemote);
	DDX_Control(pDX, IDC_STATIC_STATREMOTE, m_Bmp_PowerRemote);
	DDX_Control(pDX, IDC_MSCOMM1, m_PowerCom);
	DDX_Control(pDX, IDC_MSCOMMRES, m_ComForRes);
	DDX_Text(pDX, IDC_EDIT_CURRENTRES, m_CurrentRes);
	DDV_MinMaxInt(pDX, m_CurrentRes, 0, 5000);
	DDX_Text(pDX, IDC_EDIT_CURRENTVOLTAGE, m_CurrentVoltage);
	DDV_MinMaxInt(pDX, m_CurrentVoltage, 0, 150);
	DDX_Control(pDX, IDC_MSCOMM2, m_ResAnotherCom);
	DDX_Text(pDX, IDC_EDIT_CURRENTRESA, m_CurrentResA);
	DDV_MinMaxInt(pDX, m_CurrentResA, 0, 3000);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPowerSupplyDlg, CDialog)
	//{{AFX_MSG_MAP(CPowerSupplyDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDM_ABOUT, OnAbout)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_QUIT, OnBtnQuit)
	ON_COMMAND(IDM_SETTING, OnSetting)
	ON_COMMAND(IDM_REMOTECONN, OnRemoteconn)
	ON_BN_CLICKED(IDC_BTN_STOP, OnBtnStop)
	ON_BN_CLICKED(IDC_BTN_START, OnBtnStart)
	ON_COMMAND(IDM_OVERCURRENT_TEST, OnOvercurrentTest)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTNTEMP, OnBtntemp)
	ON_COMMAND(IDM_INPUTSERIALS, OnInputserials)
	ON_COMMAND(IDM_OUTPUT_OVERVOLTAGE, OnOutputOvervoltage)
	ON_COMMAND(IDM_NOLOAD, OnNoload)
	ON_COMMAND(IDM_UNDERVOLTAGE, OnUndervoltage)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_COMMAND(IDM_OVERVOLTAGE, OnOvervoltage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPowerSupplyDlg message handlers

BOOL CPowerSupplyDlg::OnInitDialog()
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
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

///////////��ʼ����������///////////////////
	bmp_start.LoadBitmap(IDB_BMP_START);
	bmp_stop.LoadBitmap(IDB_BMP_STOP);
	GetDlgItem(IDC_BTN_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_TEMPTEST)->EnableWindow(FALSE);
//////////// DDE��̬����////////////////
	m_hMainWnd=this->m_hWnd;//����ǰ�Ĵ��ھ����ֵ��DDE�еĴ��ھ��
	ItemCount=1;//DDE��������ע��ı�������
	strItem[0]="PowerSupply";//����������
	RegisterDdeServer(LPCTSTR("PowerSupply"),LPCTSTR("PowerSupplyTopic"));
	//��ȡ������ϰ�װ�Ĵ���
	CStringArray PortList;
	FindCommPort(&PortList);
	if(PortList.GetSize()<=0)
	{
		return FALSE;
	}
	int m_PortID1,m_PortID2;
	m_PortID1=atoi(PortList.GetAt(1).Mid(3));
	m_PortID2=atoi(PortList.GetAt(2).Mid(3));
///////////////��õ����COM�˿ں�////////////////////////////////////
	m_Power.m_pCom=&m_PowerCom;
	m_Power.InitialCom();
	m_Power.StartRemoteControl();
/////��һ�����ص�Զ�̿���////////////////////
	m_Res.m_pCom=&m_ComForRes;
	m_Res.InitialCom(m_PortID1);
	m_Res.StartRemoteControl();
////////�ڶ������ص�Զ�̿���////////
	m_ResA.m_pCom=&m_ResAnotherCom;
	m_ResA.InitialCom(m_PortID2);
	m_ResA.StartRemoteControl();
//////////////////////////////////////////////////////////////////////////
	SetLampeOn_Off();
/////////////////////////////////////
	IntialStatusBar();
	DWORD nFileCount = 0; 
	CString str="F:\\IniConfigFile";
	FindFileName(str,&nFileCount);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPowerSupplyDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPowerSupplyDlg::OnPaint() 
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
HCURSOR CPowerSupplyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPowerSupplyDlg::OnAbout() 
{
	// TODO: Add your command handler code here
	CAboutDlg AboutDlg;
	AboutDlg.DoModal();
}

void CPowerSupplyDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default

	PostQuitMessage(0);
	CDialog::OnClose();
}

void CPowerSupplyDlg::OnBtnQuit() 
{
	// TODO: Add your control notification handler code here
	m_Power.ReleasePower();
	m_Res.ReleaseRes();
	m_ResA.ReleaseRes();
		for(int i=0;i<100;i++)
	{
		m_Res.rxdata[i]=0x00;
		m_Power.rxdata[i]=0x00;
	}
	m_Power.m_pCom->SetPortOpen(FALSE);
	m_Res.m_pCom->SetPortOpen(FALSE);
	m_ResA.m_pCom->SetPortOpen(FALSE);
	PostQuitMessage(0);
	CDialog::OnClose();
}

BEGIN_EVENTSINK_MAP(CPowerSupplyDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CPowerSupplyDlg)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()



void CPowerSupplyDlg::OnSetting() //�������ļ�����
{
	// TODO: Add your command handler code here
		OPENFILENAME ofn;
		
		ZeroMemory(&ofn,sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.lpstrFile = szFile;
		ofn.lpstrFile[0] = TEXT('\0');
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = TEXT("INI\0*.INI\0ALL\0*.*\0");
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.hwndOwner = m_hWnd;
		ofn.Flags = OFN_EXPLORER |OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		if (GetOpenFileName(&ofn))
		{
			TCHAR* pLastSlash=strrchr(szFile,'\\');
			CString str=pLastSlash+1;
			m_strModelName=str.Left(str.Find("."));
			SetDlgItemText(IDC_EDIT_MODELNAME,m_strModelName);
		}

		/////////��ȡ���ݽ��///////////////////////////
		m_RateVoltage=atoi(ReadFromIniFile("RateVoltage"));
		m_RateRes=atoi(ReadFromIniFile("RateRes"));
		m_RateResA=atoi(ReadFromIniFile("RateResA"));
		m_LightRes=atoi(ReadFromIniFile("LightLoad"));
		m_LightResA=atoi(ReadFromIniFile("LightLoadA"));
		m_UpperVoltage=atoi(ReadFromIniFile("UpperVoltage"));
		m_LowVoltage=atoi(ReadFromIniFile("LowerVoltage"));
		m_OutputVoltage=atof(ReadFromIniFile("OutputVoltage"));
        m_OutputVoltageA=atof(ReadFromIniFile("OutputVoltageA"));
		m_UnderVoltage=atoi(ReadFromIniFile("UnderVoltage"));
		m_CurrentVoltage=m_RateVoltage;
		m_CurrentRes=m_RateRes;
		m_CurrentResA=m_RateResA;
		/////////COMBOBOX�е�������EDITһ��
		CString strtemp,strEdit;
		int index;
		GetDlgItemText(IDC_EDIT_MODELNAME,strEdit);
		for(int p=0;p<m_Combo.GetCount();p++)
		{
			m_Combo.GetLBText(p,strtemp);
			if(lstrcmp(strEdit,strtemp)==0)
			{
			//	MessageBox("find");
				index=p;
			}

		}
		if(index>=0)
		{
			m_Combo.SetCurSel(index);
		}
		else
		{
			m_Combo.SetCurSel(-1);
		}
		
	  
		UpdateData(FALSE);
		
}

CString CPowerSupplyDlg::ReadFromIniFile(CString keyName)
{
	TCHAR TempVal[50];CString str;
	GetPrivateProfileString(m_strModelName,keyName,"",TempVal,500,szFile);
	str.Format("%s",TempVal);str.TrimRight();
	return str;
}	



void CPowerSupplyDlg::OnRemoteconn() //�˵����ϵġ�Զ�̿��ƴ�����ť��
{
	// TODO: Add your command handler code here	
	m_Power.StartRemoteControl();
	Sleep(10);
	m_Res.StartRemoteControl();
	Sleep(10);
	m_ResA.StartRemoteControl();
	SetLampeOn_Off();

}

void CPowerSupplyDlg::OnBtnStop() 
{
	// TODO: Add your control notification handler code here
	m_StatusBar.SetPaneText(1,"ֹͣ");
	m_Progress.SetPos(0);
	GetDlgItem(IDC_COMBO1)->EnableWindow();
	/////��ʱ���Ĺ���״̬///////
	KillTimer(0);
	Step=0;
	nCount=1;
	UpdateData(TRUE);
	m_CurrentRes = m_RateRes;
	m_CurrentVoltage = m_RateVoltage;
	m_CurrentResA = m_RateResA;
	UpdateData(FALSE);
	GetDlgItem(IDC_BTN_STOP)->EnableWindow(FALSE);
	m_Power.ReleasePower();
	m_Res.ReleaseRes();
	m_ResA.ReleaseRes();
	m_Power.StartRemoteControl();
	m_Res.StartRemoteControl();
	m_ResA.StartRemoteControl();
	if(0x80==m_Power.rxdata[3])
	{
		m_Power.rxdata[3]=0x00;
	}
	if(0x80==m_Res.rxdata[3])
	{
		m_Res.rxdata[3]=0x00;
	}
	if(0x80==m_ResA.rxdata[3])
	{
		m_ResA.rxdata[3]=0x00;
	}
	GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
	SetDlgItemText(IDC_EDIT_RESULTFROMRES1,"");
	SetDlgItemText(IDC_EDIT_RESULTFROMRES2,"");
	PowerON_ResON_Lamp();
	Sleep(10);
}

void CPowerSupplyDlg::OnBtnStart() 
{
	// TODO: Add your control notification handler code here
	m_Error=0;
	int ref=MessageBox("��ȷ���Ƿ�ѡ������ȷ�������ļ�","��ʾ",MB_YESNO|MB_ICONINFORMATION);
	if(IDNO==ref)
	{
		return;
	}
	GetDlgItem(IDC_COMBO1)->EnableWindow(FALSE);
	m_List.ResetContent();
	nCount=1;
		for(int i=0;i<100;i++)
	{
		m_Res.rxdata[i]=0x00;
		m_Power.rxdata[i]=0x00;
		m_ResA.rxdata[i]=0x00;
	}
	GetDlgItem(IDC_BTN_START)->EnableWindow(FALSE);
	int tempLoad=m_CurrentRes,tempLoadA=m_CurrentResA;
	if(0==tempLoad&&0==tempLoadA)
	{
		MessageBox("����,��ѡ�������ļ����ٵ�����л��߼�������ļ�","������ʾ",MB_OK|MB_ICONERROR);
		GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
		return;
	}
	SetTimer(0,4000,NULL);
   

}

void CPowerSupplyDlg::SetLampeOn_Off()//�ñ�־��Ӧ��ָʾ�ƶ���80H�����ж�
{
	if(0x80==m_Power.rxdata[3])
	{
		m_Bmp_PowerRemote.SetBitmap((HBITMAP)bmp_start);	
	}
	else 
	{
		m_Bmp_PowerRemote.SetBitmap((HBITMAP)bmp_stop);
		m_Bmp_PowerOn.SetBitmap((HBITMAP)bmp_stop);
		
	}
	if (0x80==m_Res.rxdata[3])
	{
		m_Bmp_ResRemote.SetBitmap((HBITMAP)bmp_start);
	}
	else
	{
		m_Bmp_ResRemote.SetBitmap((HBITMAP)bmp_stop);
		m_Bmp_ResOn.SetBitmap((HBITMAP)bmp_stop);
	}
	if(0x80==m_ResA.rxdata[3])
	{
		m_Bmp_ResRemoteA.SetBitmap((HBITMAP)bmp_start);
	}
	else
	{
		m_Bmp_ResRemoteA.SetBitmap((HBITMAP)bmp_stop);
	}
	if(0x80==m_Res.rxdata[3]&&0x80==m_Power.rxdata[3])
	{
		GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
	}
	for(int i=0;i<100;i++)
	{
		m_Res.rxdata[i]=0x00;
		m_Power.rxdata[i]=0x00;
		m_ResA.rxdata[i]=0x00;
	}
}

void CPowerSupplyDlg::PowerON_ResON_Lamp()//��PowerON��־��Ӧ��ָʾ�ƶ���80H�����ж�
{
	///////�����ť��ʼ������ָʾ��ָ����ɫ
	if(0x80==m_Power.rxdata[3])
	{
		m_Bmp_PowerOn.SetBitmap((HBITMAP)bmp_start);
	}
	else
	{
		m_Bmp_PowerOn.SetBitmap((HBITMAP)bmp_stop);
	}
	if(0x80==m_Res.rxdata[3]||0x90==m_Res.rxdata[3])
	{
		m_Bmp_ResOn.SetBitmap((HBITMAP)bmp_start);
	}
	else
	{
		m_Bmp_ResOn.SetBitmap((HBITMAP)bmp_stop);
	}

	if(0x80==m_ResA.rxdata[3]||0x90==m_ResA.rxdata[3])
	{
		m_Bmp_ResOnA.SetBitmap((HBITMAP)bmp_start);
	}
	else
	{
		m_Bmp_ResOnA.SetBitmap((HBITMAP)bmp_stop);
	}
//////////////////////////////////////////////////////////////////
	Sleep(100);
}

//DEL void CPowerSupplyDlg::OnBtnTemptest() //
//DEL {
//DEL 	// TODO: Add your control notification handler code here
//DEL }

void CPowerSupplyDlg::FindCommPort(CStringArray *PortList)
{
	HKEY   hKey; 
	int PortNum=0;
	if(   ::RegOpenKeyEx(   HKEY_LOCAL_MACHINE,   
		"Hardware\\DeviceMap\\SerialComm",   
		NULL,   
		KEY_READ,   
		&hKey)   ==   ERROR_SUCCESS)   //   �򿪴���ע���   
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
				&dwSize   )   ==   ERROR_NO_MORE_ITEMS   )   //   ö�ٴ���   
				break;   
			PortList->Add(commName);
			i++;   
		}    
		RegCloseKey(hKey);   
	}  
}




void CPowerSupplyDlg::RatedLoadTest()
{
	
		int tempLoad=m_CurrentRes,tempLoadA=m_CurrentResA;
		{
				int LowWordL=(tempLoad*1000)&(0x0000ff);
				int LowWordH=(tempLoad*1000)&(0x00ff00);
				LowWordH=LowWordH/(0x100);
				int HighWordL=(tempLoad*1000)&(0x00ff0000);
				HighWordL=HighWordL/(0x10000);
				m_Res.ResOn(HighWordL,LowWordH,LowWordL);
				Sleep(100);
		}
		if(m_CurrentResA==0)
		{
			m_ResA.ResOn(00,00,250&(0x0000ff));
			Sleep(100);

		}
		else
		{

				int LowWordL=(tempLoadA*1000)&(0x0000ff);
				int LowWordH=(tempLoadA*1000)&(0x00ff00);
				LowWordH=LowWordH/(0x100);
				int HighWordL=(tempLoadA*1000)&(0x00ff0000);
				HighWordL=HighWordL/(0x10000);
				m_ResA.ResOn(HighWordL,LowWordH,LowWordL);
				Sleep(10);
		}

}

void CPowerSupplyDlg::NoloadTest()
{	
	int tempPower=m_CurrentVoltage;

	GetDlgItem(IDC_BTN_STOP)->EnableWindow(TRUE);
	if(tempPower<50)
	{	
		int LowWordL=(tempPower*1000)&(0x0000ff);
		int LowWordH=(tempPower*1000)&(0x00ff00);
		LowWordH=LowWordH/(0x100);
		m_Power.PowerOn(0,LowWordH,LowWordL);
	}
	else if(tempPower>50)
	{
//		m_Power.PowerOn(0,0xC3,0x50);
//		Sleep(5000);
		int LowWordL=(tempPower*1000)&(0x0000ff);
		int LowWordH=(tempPower*1000)&(0x00ff00);
		LowWordH=LowWordH/(0x100);
		int HighWordL=(tempPower*1000)&(0x00ff0000);
		HighWordL=HighWordL/(0x10000);
		m_Power.PowerOn(HighWordL,LowWordH,LowWordL); 
	}
}

void CPowerSupplyDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	/////////////���ز���/////////////////
	if(0==Step)
	{	
		m_StatusBar.SetPaneText(1,"���ز���");
		NoloadTest();
		PowerON_ResON_Lamp();
		DisplayOutputVoltage();
		Step++;
		return;
	}
	if(1==Step)
	{
		m_Progress.SetPos(16);
		NomalTestJudge();
		Step++;
		return;
	}
	if(2==Step)/////8�����ж��ѹ����
	{	
		
		///////////////////����ز���////////////
		m_StatusBar.SetPaneText(1,"����ز���");
		RatedLoadTest();
		PowerON_ResON_Lamp();
		DisplayOutputVoltage();
		Step++;
		return;
	}
	
	////////////////��ѹ��������/////////////
	if(0!=m_UpperVoltage)
	{
		if(3==Step)
		{
			m_Progress.SetPos(32);
			m_StatusBar.SetPaneText(1,"��ѹ��������");
			NomalTestJudge();
			OnVoltageUpperWave();
			DisplayOutputVoltage();
			NoloadTest();
			Step++;
			return;
		}
		if(4==Step)
		{
			NomalTestJudge();
			Step++;
			return;	
		}
		if(5==Step)
		{
			
			OnVoltageLowerWave();
			DisplayOutputVoltage();
			NoloadTest();
			Step++;
			return;
		}
		if(6==Step)
		{	
			m_Progress.SetPos(50);
			NomalTestJudge();
			Step++;
			return;	
		}
	}
	///////////////�������Ի����ز���//////////////////
		if (7==Step)
		{
			m_Progress.SetPos(60);

			if(1000==m_LightRes||1000==m_LightResA)
			{
				bFlag_OverCurrent=FALSE;
				Step++;
				return;
			}
			else
			{
				bFlag_OverCurrent=TRUE;
				m_StatusBar.SetPaneText(1,"��������");	
				OverCurrentTest();
				DisplayOutputVoltage();
				UpdateData(TRUE);
				//NomalTestJudge();
				Step++;
				return;
			}
		
		}
		if(8==Step)
		{
			
			m_Progress.SetPos(80);
			//NomalTestJudge();
			Step++;
			return;
		}
		

	/////////////Ƿѹ����״̬//////////////////////////
	if(9==Step)
	{
		NomalTestJudge();
		m_StatusBar.SetPaneText(1,"Ƿѹ��������");
		UnderVoltage();
		DisplayOutputVoltage();
		Step++;
		return;
	}
	if(10==Step)
	{		
			nCount=6;
			NomalTestJudge();
			m_Progress.SetPos(100);
			Step++;
			return;
	}
///////////////��ѹ����//////////////////////////////
	if(11==Step)
	{
		if(0==m_OverVoltage)
			{
				bFlag_OverVoltage=FALSE;
				Step++;
				return;
			}
			else
			{
				bFlag_OverVoltage=TRUE;
				m_StatusBar.SetPaneText(1,"��ѹ����");
				OverVoltage();
				DisplayOutputVoltage();
				Step++;
				return;
			}
	}
	if(12==Step)
	{
	//	m_Progress.SetPos(100);
		NomalTestJudge();
		Step++;
		return;
	}
////////////////////////////////////////////
	if(13==Step)
	{
		OnBtntemp();
	}
	if(Step<14)
	{
		Step++;
	}
	else
	{
		Step=0;
		KillTimer(0);
		OnBtnStop();
		MSGBOXPARAMS   msgBox; 
		msgBox.cbSize   =   sizeof(MSGBOXPARAMS); 
		msgBox.dwStyle   =   MB_USERICON; 
		msgBox.hInstance   =   AfxGetApp()-> m_hInstance; 
		msgBox.hwndOwner   =   m_hWnd; 
		msgBox.lpszCaption   =   "���Խ��"; 
		msgBox.lpszIcon   =   MAKEINTRESOURCE(IDI_ICON2); 
		msgBox.lpszText   =   "����������ͨ��������PASS��"; 
		if(0==m_Error)
		{
			MessageBoxIndirect(&msgBox);
		}
		else
		{
			CString str,strExpression;
			str.Format("%d",m_Error);
			strExpression="��"+str+"�������ѣ�����ģ�飡";
			MessageBox(strExpression,"���Խ��",MB_OK|MB_ICONERROR);
			m_Error=0;
		}
	}
	CDialog::OnTimer(nIDEvent);
}


void CPowerSupplyDlg::OnVoltageUpperWave()
{
	UpdateData(TRUE);
	m_CurrentVoltage=m_UpperVoltage;
	UpdateData(FALSE);
}

void CPowerSupplyDlg::OnVoltageLowerWave()
{
	UpdateData(TRUE);
	m_CurrentVoltage=m_LowVoltage;
	UpdateData(FALSE);
}

void CPowerSupplyDlg::OverCurrentTest()
{
	UpdateData(TRUE);
	m_CurrentVoltage=m_RateVoltage;
	m_CurrentRes=m_LightRes;
	m_CurrentResA=m_LightResA;
	UpdateData(FALSE);
	NoloadTest();
	RatedLoadTest();
}

CString CPowerSupplyDlg::GetCurrentPath()
{
	char path[MAX_PATH];CString str,strpath;
	::GetModuleFileName(NULL,path,MAX_PATH);
	str=path;
	int nPos=str.ReverseFind('\\');
	strpath=str.Left(nPos);
	return strpath;
}

BOOL CPowerSupplyDlg::ExportToExcel(CString dFile)
{
	
		//////Excel�������
	_Application app;    
	Workbooks books;
	_Workbook book;
	Worksheets sheets;
	_Worksheet sheet;
	Range range_all,range,Rcell;
	Range TempRge,BomRge,ItemRge;
	Range iCell;
	LPDISPATCH lpDisp;    
	COleVariant vResult;
	COleVariant
        covTrue((short)TRUE),
        covFalse((short)FALSE),
        covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);    
	
	//����Excel 2000������(����Excel)
	if(!app.CreateDispatch("Excel.Application")) 
	{
		AfxMessageBox("�޷�����Excel������!");
		return FALSE;
	}
	app.SetDisplayAlerts(FALSE);	//����ʾ������ʾ��
	app.SetVisible(FALSE);          //ʹExcel�ɼ�
	app.SetUserControl(FALSE);      //���������û�����Excel
	UpdateData(TRUE);

		//��EXCEL�ļ�
		books.AttachDispatch(app.GetWorkbooks());
		lpDisp = books.Open(dFile,      
			covOptional, covOptional, covOptional, covOptional, covOptional,
			covOptional, covOptional, covOptional, covOptional, covOptional,
			covOptional, covOptional );
		//�õ�Workbook
		book.AttachDispatch(lpDisp);
		//�õ�Worksheets 
		sheets.AttachDispatch(book.GetWorksheets());
		//�õ�Worksheet
		sheet.AttachDispatch(sheets.GetItem(COleVariant("�����¼��")));
		range.AttachDispatch(sheet.GetCells());
		CTime time=CTime::GetCurrentTime();
		CString m_Time=time.Format("%Y-%m-%d");
		////////��д���������ʱ��/////////////////////////////////////////////////////////
		range.SetItem(_variant_t((long)10),_variant_t((long)7),_variant_t(m_UserName));
		range.SetItem(_variant_t((long)12),_variant_t((long)7),_variant_t(m_UserName));
		range.SetItem(_variant_t((long)14),_variant_t((long)7),_variant_t(m_UserName));
		range.SetItem(_variant_t((long)16),_variant_t((long)7),_variant_t(m_UserName));
		range.SetItem(_variant_t((long)26),_variant_t((long)7),_variant_t(m_UserName));
		range.SetItem(_variant_t((long)28),_variant_t((long)7),_variant_t(m_UserName));
		range.SetItem(_variant_t((long)30),_variant_t((long)7),_variant_t(m_UserName));
		range.SetItem(_variant_t((long)32),_variant_t((long)7),_variant_t(m_UserName));
		for(long i=10;i<=32;i=i+2)
		{
			range.SetItem(_variant_t((long)i),_variant_t((long)8),_variant_t(m_Time));
		}
		//range.SetItem(_variant_t((long)10),_variant_t((long)8),_variant_t(m_Time));
	    ///////��д�̶�������////////
		range.SetItem(_variant_t((long)3),_variant_t((long)3),_variant_t(m_ModolName+"��Դģ������¼��"));
		range.SetItem(_variant_t((long)5),_variant_t((long)7),_variant_t(m_ModolName));
		range.SetItem(_variant_t((long)6),_variant_t((long)3),_variant_t(m_ModolSerial));
		range.SetItem(_variant_t((long)5),_variant_t((long)3),_variant_t(m_ModolName+"��Դģ��"));
		range.SetItem(_variant_t((long)7),_variant_t((long)3),_variant_t("��Դ����ͨ���͹�װ"));
		range.SetItem(_variant_t((long)8),_variant_t((long)3),_variant_t("��Դģ�����ƽ̨���"));
		range.SetItem(_variant_t((long)8),_variant_t((long)7),_variant_t("V1.0"));
		////////���ս��//////////////////////////
		range.SetItem(_variant_t((long)10),_variant_t((long)6),_variant_t(m_NoLoadResult));
		range.SetItem(_variant_t((long)26),_variant_t((long)6),_variant_t(m_NoLoadResult));

		range.SetItem(_variant_t((long)12),_variant_t((long)6),_variant_t(m_RateLoadResult));
		range.SetItem(_variant_t((long)28),_variant_t((long)6),_variant_t(m_RateLoadResult));
		
	    range.SetItem(_variant_t((long)14),_variant_t((long)6),_variant_t(m_VoltageWaveResult));
		range.SetItem(_variant_t((long)30),_variant_t((long)6),_variant_t(m_VoltageWaveResult));

	    range.SetItem(_variant_t((long)16),_variant_t((long)6),_variant_t(m_OverCurrentResult));
		range.SetItem(_variant_t((long)32),_variant_t((long)6),_variant_t(m_OverCurrentResult));
		//////////////////////////////////////////
		range.DetachDispatch();sheet.DetachDispatch();		
		book.Save();
		books.Close();
		books.ReleaseDispatch();
		app.Quit();
     	return TRUE;
}

void CPowerSupplyDlg::OnBtntemp() //���EXCEL�ĵ�
{
	// TODO: Add your control notification handler code here
	m_ModolSerial=strSerirals;
	m_ModolName=m_strModelName;
	m_CurrentPath=GetCurrentPath();
	CString sFile=m_CurrentPath+"\\�����¼��ģ��.xls";
	CString dFile="E:\\report\\"+m_ModolName+" "+"�����¼��"+m_ModolSerial+".xls";
	CopyFile(sFile,dFile,FALSE);
	ExportToExcel(dFile);
}

void CPowerSupplyDlg::NomalTestJudge()
{
	TCHAR str[256],strA[256];
	ZeroMemory(str,sizeof(str)/sizeof(TCHAR));
	ZeroMemory(strA,sizeof(strA)/sizeof(TCHAR));
	m_Res.ReadVoltageFromRES(str);
	m_ResA.ReadVoltageFromRES(strA);
	UpdateData();
	SetDlgItemText(IDC_EDIT_RESULTFROMRES1,str);
	SetDlgItemText(IDC_EDIT_RESULTFROMRES2,strA);
	UpdateData(FALSE);	

	double Voltage=atof(str)-m_OutputVoltage;
	double Precision=m_OutputVoltage*0.05;
	double VoltageA=atof(strA)-m_OutputVoltageA;
	double PrecisionA=m_OutputVoltageA*0.05;
	if(0==PrecisionA)////���ֻʹ��һ·���Ӹ��صĻ���������ֵ��Ϊ1
	{
		PrecisionA=1;
	}	
    MSGBOXPARAMS   msgBox; 
	msgBox.cbSize   =   sizeof(MSGBOXPARAMS); 
	msgBox.dwStyle   =   MB_USERICON; 
	msgBox.hInstance   =   AfxGetApp()-> m_hInstance; 
	msgBox.hwndOwner   =   m_hWnd; 
	msgBox.lpszCaption   =   "���Խ��"; 
	msgBox.lpszIcon   =   MAKEINTRESOURCE(IDI_ICON2); 
	msgBox.lpszText   =   "����������ͨ��������PASS��"; 
	int ref;///////LISTBOX��ǰѡ�е���
	if((Voltage<Precision&&Voltage>-Precision)&&((VoltageA<PrecisionA&&VoltageA>-PrecisionA))&&nCount<5)
	{
		
		switch(nCount)
		{
		case 1:
			ref=m_List.InsertString(-1,"���ز���ͨ��");
		break;
		case 2:
			ref=m_List.InsertString(-1,"����ز���ͨ��");
		break;
		case 3:
			ref=m_List.InsertString(-1,"��ѹ�ϸ���������ͨ��");
		break;
		case 4:
			ref=m_List.InsertString(-1,"��ѹ�¸���������ͨ��");
		break;
		}
		m_List.SetCurSel(ref);
	}
	else
	{
		
		switch(nCount)
		{
			case 1: 
				ref=m_List.InsertString(-1,"���ز��Բ�ͨ��");
				m_List.SetCurSel(ref);
				m_NoLoadResult="���ϸ�";
				m_Error++;
				MessageBox("���ز��������������ݲ����Ͼ���Ҫ�󣡣���FAIL��","���Խ��",MB_OK|MB_ICONERROR);
			break;
			case 2: 
				ref=m_List.InsertString(-1,"����ز��Բ�ͨ��");
				m_List.SetCurSel(ref);
				m_RateLoadResult="���ϸ�";
				m_Error++;
				MessageBox("��������������ݲ����Ͼ���Ҫ�󣡣���FAIL��","���Խ��",MB_OK|MB_ICONERROR);
			break;
			case 3: 
				ref=m_List.InsertString(-1,"��ѹ�ϸ��������Բ�ͨ��");
				m_List.SetCurSel(ref);
				m_VoltageWaveResult="���ϸ�";
				m_Error++;
				MessageBox("��ѹ�ϸ��������������ݲ����Ͼ���Ҫ�󣡣���FAIL��","���Խ��",MB_OK|MB_ICONERROR);
			break;
			case 4:  
				ref=m_List.InsertString(-1,"��ѹ�¸��������Բ�ͨ��");
				m_List.SetCurSel(ref);
				m_VoltageWaveResult="���ϸ�";
				m_Error++;
			    MessageBox("��ѹ�¸��������������ݲ����Ͼ���Ҫ�󣡣���FAIL��","���Խ��",MB_OK|MB_ICONERROR);
			break;
			case 5: 
				if(TRUE==bFlag_OverCurrent)
				{
						if(1<atof(str)&&atof(strA)>1)
						{
							 m_OverCurrentResult="���ϸ�";	
							 m_Error++;
							 ref=m_List.InsertString(-1,"�������Բ�ͨ��");
							  m_List.SetCurSel(ref);
							 MessageBox("�����������������ݲ����Ͼ���Ҫ�󣡣���FAIL��","���Խ��",MB_OK|MB_ICONERROR);
						}
							else
						{
							ref=m_List.InsertString(-1,"��������ͨ��");
							m_List.SetCurSel(ref);
						}	
				}
				nCount=5;
			break;
			case 6:  
				if(1<atof(str)||atof(strA)>1)
					{
						 m_OverCurrentResult="���ϸ�";	
						 m_Error++;
						 ref=m_List.InsertString(-1,"Ƿѹ���Բ�ͨ��");
					     m_List.SetCurSel(ref);
						 MessageBox("Ƿѹ�������������ݲ����Ͼ���Ҫ�󣡣���FAIL��","���Խ��",MB_OK|MB_ICONERROR);
					}
				else
				{
					ref=m_List.InsertString(-1,"Ƿѹ��������ͨ��");
					m_List.SetCurSel(ref);
				}
			break;
			case 7:
				{
					if(TRUE==bFlag_OverVoltage)
					{
						if(1<atof(str)&&atof(strA)>1)
						{
							 m_OverCurrentResult="���ϸ�";	
							 m_Error++;
							 ref=m_List.InsertString(-1,"��ѹ���Բ�ͨ��");
							  m_List.SetCurSel(ref);
							 MessageBox("��ѹ�������������ݲ����Ͼ���Ҫ�󣡣���FAIL��","���Խ��",MB_OK|MB_ICONERROR);
						}
						else
						{
							ref=m_List.InsertString(-1,"��ѹ����ͨ��");
							m_List.SetCurSel(ref);
						}	
					}	
				}
			break;
			default: nCount=1;
			break;
		}
	}
	nCount++;
}



void CPowerSupplyDlg::DisplayOutputVoltage()
{
	TCHAR str[256],strA[256];
	ZeroMemory(str,sizeof(str)/sizeof(TCHAR));
	ZeroMemory(strA,sizeof(strA)/sizeof(TCHAR));
	m_Res.ReadVoltageFromRES(str);
	m_ResA.ReadVoltageFromRES(strA);
	UpdateData();
	SetDlgItemText(IDC_EDIT_RESULTFROMRES1,str);
	SetDlgItemText(IDC_EDIT_RESULTFROMRES2,strA);
	UpdateData(FALSE);
}

void CPowerSupplyDlg::OnInputserials() 
{
	// TODO: Add your command handler code here
	CSerialsInputDialog dialog;
	dialog.DoModal();
}

void CPowerSupplyDlg::UnderVoltage()
{
	UpdateData(TRUE);
	m_CurrentVoltage=m_UnderVoltage;
	m_CurrentRes=m_RateRes;
	m_CurrentResA=m_RateResA;
	UpdateData(FALSE);
	NoloadTest();
	RatedLoadTest();
}

//////���⹦�������////////////////////
void CPowerSupplyDlg::OnOvercurrentTest() 
{
	// TODO: Add your command handler code here
		if(0==m_CurrentVoltage)
	{
		MessageBox("����ѡ��һ�������ļ����ٽ������������","��ʾ",MB_ICONINFORMATION|MB_OK);
		return;
	}
	GetDlgItem(IDC_BTN_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_STOP)->EnableWindow(TRUE);
	OverCurrentTest();
	GetDlgItem(IDC_BTN_TEMPTEST)->EnableWindow(TRUE);
	Sleep(1000);
	PowerON_ResON_Lamp();
	TCHAR str[256],strA[256];
	ZeroMemory(str,sizeof(str)/sizeof(TCHAR));
	ZeroMemory(strA,sizeof(strA)/sizeof(TCHAR));
	m_Res.ReadVoltageFromRES(str);
	m_ResA.ReadVoltageFromRES(strA);
	DisplayOutputVoltage();
	MessageBox("��������״̬�Ѿ������ã�","״̬��ʾ",MB_OK|MB_ICONINFORMATION);
}

void CPowerSupplyDlg::OnOutputOvervoltage() 
{
	// TODO: Add your command handler code here
	if(0==m_CurrentVoltage)
	{
		MessageBox("����ѡ��һ�������ļ����ٽ������������","��ʾ",MB_ICONINFORMATION|MB_OK);
		return;
	}
	GetDlgItem(IDC_BTN_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_STOP)->EnableWindow(TRUE);
	UpdateData(TRUE);
	m_CurrentVoltage=m_RateVoltage;
	m_CurrentRes=m_RateRes;
	m_CurrentResA=m_RateResA;
	UpdateData(FALSE);
	GetDlgItem(IDC_BTN_TEMPTEST)->EnableWindow(TRUE);
	NoloadTest();
	RatedLoadTest();
	Sleep(1000);
	PowerON_ResON_Lamp();
	TCHAR str[256],strA[256];
	ZeroMemory(str,sizeof(str)/sizeof(TCHAR));
	ZeroMemory(strA,sizeof(strA)/sizeof(TCHAR));
	m_Res.ReadVoltageFromRES(str);
	m_ResA.ReadVoltageFromRES(strA);
	DisplayOutputVoltage();
	MessageBox("�����ѹ����״̬�Ѿ������ã�","״̬��ʾ",MB_OK|MB_ICONINFORMATION);

}

void CPowerSupplyDlg::OnNoload() 
{
	// TODO: Add your command handler code here
	if(0==m_CurrentVoltage)
	{
		MessageBox("����ѡ��һ�������ļ����ٽ������������","��ʾ",MB_ICONINFORMATION|MB_OK);
		return;
	}
	GetDlgItem(IDC_BTN_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_STOP)->EnableWindow(TRUE);
	UpdateData(TRUE);
	m_CurrentVoltage=m_RateVoltage;
	m_CurrentRes=m_RateRes;
	m_CurrentResA=m_RateResA;
	UpdateData(FALSE);
	GetDlgItem(IDC_BTN_TEMPTEST)->EnableWindow(TRUE);
	NoloadTest();
	Sleep(1000);
	PowerON_ResON_Lamp();
	MessageBox("���ز���״̬�Ѿ������ã�","״̬��ʾ",MB_OK|MB_ICONINFORMATION);
}



void CPowerSupplyDlg::OnUndervoltage() 
{
	// TODO: Add your command handler code here
		if(0==m_CurrentVoltage)
	{
		MessageBox("����ѡ��һ�������ļ����ٽ������������","��ʾ",MB_ICONINFORMATION|MB_OK);
		return;
	}
	GetDlgItem(IDC_BTN_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_STOP)->EnableWindow(TRUE);
	UnderVoltage();
	GetDlgItem(IDC_BTN_TEMPTEST)->EnableWindow(TRUE);
	Sleep(1000);
	PowerON_ResON_Lamp();
	TCHAR str[256],strA[256];
	ZeroMemory(str,sizeof(str)/sizeof(TCHAR));
	ZeroMemory(strA,sizeof(strA)/sizeof(TCHAR));
	m_Res.ReadVoltageFromRES(str);
	m_ResA.ReadVoltageFromRES(strA);
	DisplayOutputVoltage();
	MessageBox("Ƿѹ����״̬�Ѿ������ã�","״̬��ʾ",MB_OK|MB_ICONINFORMATION);
}

void CPowerSupplyDlg::IntialStatusBar()
{
	UINT array[4]={0,0,0,0};
	m_StatusBar.Create(this);
	m_StatusBar.SetIndicators(array,sizeof(array)/sizeof(UINT));
	/////����ÿһ���Ŀ��
	CRect rect;
	GetClientRect(rect);
	m_StatusBar.SetPaneInfo(0,array[0],0,rect.Width()*0.1);
	m_StatusBar.SetPaneInfo(1,array[1],0,rect.Width()*0.2);
	m_StatusBar.SetPaneInfo(2,array[2],0,rect.Width()*0.1);
	m_StatusBar.SetPaneInfo(3,array[3],0,rect.Width()*0.6);
	/////������Ϣ////////
	m_StatusBar.SetPaneText(0,"��ǰ״̬");
	m_StatusBar.SetPaneText(1,"ֹͣ");
	m_StatusBar.SetPaneText(2,"��ǰ����");
	//////��ʾ/////////
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);
	///////���ý�����
	CRect m_Rect;
	m_StatusBar.GetItemRect(3,&m_Rect);
	m_Progress.SetParent(&m_StatusBar);
	m_Progress.MoveWindow(&m_Rect);
	m_Progress.ShowWindow(SW_SHOW);
	m_Progress.SetRange(0,100);
	m_Progress.SetPos(0);
	m_Progress.SetStep(13);
}
/////���ض����ļ����²����ļ���
DWORD CPowerSupplyDlg::FindFileName(CString strParentFilePath, DWORD *nCount)
{
	CFileFind cFile;   
			BOOL bDecide = FALSE;   
			WORD dMaxFileLen = 252; //�ļ�·�������255���ַ�   
			CFileStatus fileStatus; //�����ļ����Ա���   
			CString strPath;   
			WORD nLen = 0;   
  
			if(strParentFilePath.Right(1) != '\\')   
			{   
				strParentFilePath += "\\";   
			}   
			strParentFilePath += "*.*";   
			bDecide = cFile.FindFile(strParentFilePath);   
			while(bDecide)   
			{   
				bDecide = cFile.FindNextFile();   
				CString strFileRe = cFile.GetFileName();   
				if(!cFile.IsDirectory() && !cFile.IsDots()) //������Ͳ���ļ�   
				{  
					CString strtemp=cFile.GetFileTitle();
					m_Combo.InsertString(-1,strtemp);			
				}   		  
			}   
			cFile.Close(); //�ر��ļ�   
			return *nCount;   
}

void CPowerSupplyDlg::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	CString str,strtemp;
	int index=m_Combo.GetCurSel();
	m_Combo.GetLBText(index,str);
	
	UpdateData();
	m_strModelName=str;
	SetDlgItemText(IDC_EDIT_MODELNAME,str);
	UpdateData(FALSE);
	strtemp="F:\\IniConfigFile\\"+str+".ini";
	wsprintf(szFile,"%s",strtemp);	
	m_RateVoltage=atoi(ReadFromIniFile("RateVoltage"));
	m_RateRes=atoi(ReadFromIniFile("RateRes"));
	m_RateResA=atoi(ReadFromIniFile("RateResA"));
	m_LightRes=atoi(ReadFromIniFile("LightLoad"));
	m_LightResA=atoi(ReadFromIniFile("LightLoadA"));
	m_UpperVoltage=atoi(ReadFromIniFile("UpperVoltage"));
	m_LowVoltage=atoi(ReadFromIniFile("LowerVoltage"));
	m_OutputVoltage=atof(ReadFromIniFile("OutputVoltage"));
    m_OutputVoltageA=atof(ReadFromIniFile("OutputVoltageA"));
	m_UnderVoltage=atoi(ReadFromIniFile("UnderVoltage"));
	m_OverVoltage=atoi(ReadFromIniFile("OverVoltage"));
	m_CurrentVoltage=m_RateVoltage;
	m_CurrentRes=m_RateRes;
	m_CurrentResA=m_RateResA;
	UpdateData(FALSE);
}

void CPowerSupplyDlg::OnOvervoltage() 
{
	// TODO: Add your command handler code here
	if(0==m_CurrentVoltage)
	{
		MessageBox("����ѡ��һ�������ļ����ٽ������������","��ʾ",MB_ICONINFORMATION|MB_OK);
		return;
	}
	GetDlgItem(IDC_BTN_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_STOP)->EnableWindow(TRUE);
	OverVoltage();
	GetDlgItem(IDC_BTN_TEMPTEST)->EnableWindow(TRUE);
	Sleep(1000);
	PowerON_ResON_Lamp();
	TCHAR str[256],strA[256];
	ZeroMemory(str,sizeof(str)/sizeof(TCHAR));
	ZeroMemory(strA,sizeof(strA)/sizeof(TCHAR));
	m_Res.ReadVoltageFromRES(str);
	m_ResA.ReadVoltageFromRES(strA);
	DisplayOutputVoltage();
	MessageBox("��ѹ����״̬�Ѿ������ã�","״̬��ʾ",MB_OK|MB_ICONINFORMATION);
}

void CPowerSupplyDlg::OverVoltage()
{
	UpdateData(TRUE);
	m_CurrentVoltage=m_OverVoltage;
	m_CurrentRes=m_RateRes;
	m_CurrentResA=m_RateResA;
	UpdateData(FALSE);
	NoloadTest();
	RatedLoadTest();
}
