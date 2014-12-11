; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSerialApp
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "oxsercom.h"
LastPage=0

ClassCount=7
Class1=CMainFrame
Class2=CSendView
Class3=CSerialApp
Class4=CSerialDoc
Class5=CSerialView
Class6=CTimeoutDlg
Class7=CTransferDlg

ResourceCount=1
Resource1=IDD_COMMSETUP

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=\Ultimate ToolBox\Samples\communication\Serial\MainFrame.h
ImplementationFile=\Ultimate ToolBox\Samples\communication\Serial\MainFrame.cpp
LastObject=CMainFrame

[CLS:CSendView]
Type=0
BaseClass=CEditView
HeaderFile=\Ultimate ToolBox\Samples\communication\Serial\SendView.h
ImplementationFile=\Ultimate ToolBox\Samples\communication\Serial\SendView.cpp

[CLS:CSerialApp]
Type=0
BaseClass=CWinApp
HeaderFile=\Ultimate ToolBox\Samples\communication\Serial\Serial.h
ImplementationFile=\Ultimate ToolBox\Samples\communication\Serial\Serial.cpp
Filter=N
VirtualFilter=AC
LastObject=CSerialApp

[CLS:CSerialDoc]
Type=0
BaseClass=CDocument
HeaderFile=\Ultimate ToolBox\Samples\communication\Serial\SerialDoc.h
ImplementationFile=\Ultimate ToolBox\Samples\communication\Serial\SerialDoc.cpp

[CLS:CSerialView]
Type=0
BaseClass=CEditView
HeaderFile=\Ultimate ToolBox\Samples\communication\Serial\SerialView.h
ImplementationFile=\Ultimate ToolBox\Samples\communication\Serial\SerialView.cpp

[CLS:CTimeoutDlg]
Type=0
BaseClass=CDialog
HeaderFile=\Ultimate ToolBox\Samples\communication\Serial\TimeoutDlg.h
ImplementationFile=\Ultimate ToolBox\Samples\communication\Serial\TimeoutDlg.cpp

[CLS:CTransferDlg]
Type=0
BaseClass=CDialog
HeaderFile=\Ultimate ToolBox\Samples\communication\Serial\TransferDlg.h
ImplementationFile=\Ultimate ToolBox\Samples\communication\Serial\TransferDlg.cpp

[DLG:IDD_TIMEOUT]
Type=1
Class=CTimeoutDlg

[DLG:IDD_TRANSFER]
Type=1
Class=CTransferDlg

[DLG:IDD_COMMSETUP]
Type=1
Class=?
ControlCount=14
Control1=65535,static,1342308352
Control2=IDC_PORT,combobox,1344340483
Control3=65535,static,1342177280
Control4=IDC_BAUDRATE,combobox,1344340483
Control5=65535,static,1342177280
Control6=IDC_DATABIT,combobox,1344340483
Control7=65535,static,1342177280
Control8=IDC_PARITY,combobox,1344340483
Control9=65535,static,1342177280
Control10=IDC_STOPBIT,combobox,1344340483
Control11=IDOK,button,1342242817
Control12=IDCANCEL,button,1342242816
Control13=65535,static,1342177280
Control14=IDC_FLOWCONTROL,combobox,1344340483

