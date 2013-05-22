; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPowerSupplyDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "powersupply.h"
LastPage=0
CDK=Y

ClassCount=5
Class1=CLogin
Class2=CPowerSupplyApp
Class3=CAboutDlg
Class4=CPowerSupplyDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDD_POWERSUPPLY_DIALOG
Resource3=IDD_LOGIN
Resource4=IDD_DIALOG_INPUTSERIALS
Class5=CSerialsInputDialog
Resource5=IDR_MENU1

[CLS:CLogin]
Type=0
BaseClass=CDialog
HeaderFile=Login.h
ImplementationFile=Login.cpp
LastObject=CLogin
Filter=D
VirtualFilter=dWC

[CLS:CPowerSupplyApp]
Type=0
BaseClass=CWinApp
HeaderFile=PowerSupply.h
ImplementationFile=PowerSupply.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=PowerSupplyDlg.cpp
ImplementationFile=PowerSupplyDlg.cpp
LastObject=CAboutDlg

[CLS:CPowerSupplyDlg]
Type=0
BaseClass=CDialog
HeaderFile=PowerSupplyDlg.h
ImplementationFile=PowerSupplyDlg.cpp
LastObject=CPowerSupplyDlg
Filter=D
VirtualFilter=dWC

[DLG:IDD_LOGIN]
Type=1
Class=CLogin
ControlCount=8
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_LOGINNAME,edit,1350631552
Control3=IDC_EDIT_LOGINPASSWORD,edit,1350631584
Control4=IDOK,button,1342242817
Control5=IDCANCEL,button,1342242816
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT_SNNUMBER,edit,1350631552
Control8=IDC_STATIC,static,1342308352

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_POWERSUPPLY_DIALOG]
Type=1
Class=CPowerSupplyDlg
ControlCount=44
Control1=IDC_BTN_QUIT,button,1342242816
Control2=IDC_EDIT_MODELNAME,edit,1484849280
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STATIC_STATREMOTE,static,1342177294
Control8=IDC_STATIC_REMOTERES,static,1342177294
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STATIC_POWERONLAMP,static,1342177294
Control13=IDC_STATIC_RESON,static,1342177294
Control14=IDC_STATIC,static,1342308352
Control15=IDC_EDIT_CURRENTVOLTAGE,edit,1484849280
Control16=IDC_BTN_START,button,1476460544
Control17=IDC_EDIT_CURRENTRES,edit,1484849280
Control18=IDC_STATIC,static,1342308352
Control19=IDC_BTN_STOP,button,1342242816
Control20=IDC_MSCOMM1,{648A5600-2C6E-101B-82B6-000000000014},1342242816
Control21=IDC_MSCOMMRES,{648A5600-2C6E-101B-82B6-000000000014},1342242816
Control22=IDC_MSCOMM2,{648A5600-2C6E-101B-82B6-000000000014},1342242816
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC_REMOTERESA,static,1342177294
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC_RESONA,static,1342177294
Control27=IDC_STATIC,static,1342308352
Control28=IDC_STATIC,static,1342308352
Control29=IDC_EDIT_CURRENTRESA,edit,1484849280
Control30=IDC_STATIC,static,1342308352
Control31=IDC_STATIC,static,1342308352
Control32=IDC_EDIT_RESULTFROMRES1,edit,1484849280
Control33=IDC_STATIC,static,1342308352
Control34=IDC_STATIC,static,1342308352
Control35=IDC_EDIT_RESULTFROMRES2,edit,1484849280
Control36=IDC_STATIC,static,1342308352
Control37=IDC_STATIC,static,1342308352
Control38=IDC_BTN_TEMPTEST,button,1073807360
Control39=IDC_BTNTEMP,button,1342242816
Control40=IDC_PROGRESS,msctls_progress32,1350565889
Control41=IDC_LIST,listbox,1352728835
Control42=IDC_STATIC,button,1342177287
Control43=IDC_COMBO1,combobox,1344340226
Control44=IDC_STATIC,static,1342308352

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=IDM_SETTING
Command2=IDM_INPUTSERIALS
Command3=IDM_REMOTECONN
Command4=IDM_OUTPUT_OVERVOLTAGE
Command5=IDM_OVERCURRENT_TEST
Command6=IDM_UNDERVOLTAGE
Command7=IDM_NOLOAD
Command8=IDM_OVERVOLTAGE
Command9=IDM_ABOUT
CommandCount=9

[DLG:IDD_DIALOG_INPUTSERIALS]
Type=1
Class=CSerialsInputDialog
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT_SERIAL,edit,1350631552
Control4=IDC_STATIC,static,1342308352

[CLS:CSerialsInputDialog]
Type=0
HeaderFile=SerialsInputDialog.h
ImplementationFile=SerialsInputDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=IDM_INPUTSERIALS
VirtualFilter=dWC

