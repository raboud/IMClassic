; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSQLEditDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ado sample.h"
LastPage=0

ClassCount=9
Class1=CADOSampleApp
Class2=CAboutDlg
Class3=CADOSampleDoc
Class4=CADOSampleView
Class5=CChildFrame
Class6=CConnectDlg
Class7=CMainFrame
Class8=MyCug
Class9=CSQLEditDlg

ResourceCount=5
Resource1=IDR_ADOSampleTYPE
Resource2=IDD_CONNECT_DLG
Resource3=IDR_MAINFRAME
Resource4=IDD_ABOUTBOX
Resource5=IDD_SQLEDIT_DLG

[CLS:CADOSampleApp]
Type=0
BaseClass=CWinApp
HeaderFile=ADO Sample.h
ImplementationFile=ADO Sample.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=ADO Sample.cpp
ImplementationFile=ADO Sample.cpp

[CLS:CADOSampleDoc]
Type=0
BaseClass=CDocument
HeaderFile=ADO SampleDoc.h
ImplementationFile=ADO SampleDoc.cpp

[CLS:CADOSampleView]
Type=0
BaseClass=CView
HeaderFile=ADO SampleView.h
ImplementationFile=ADO SampleView.cpp
Filter=C
VirtualFilter=VWC

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp

[CLS:CConnectDlg]
Type=0
BaseClass=CDialog
HeaderFile=ConnectDlg.h
ImplementationFile=ConnectDlg.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:MyCug]
Type=0
BaseClass=CUGCtrl
HeaderFile=MyCUG.h
ImplementationFile=MyCUG.cpp

[CLS:CSQLEditDlg]
Type=0
BaseClass=CDialog
HeaderFile=SqlEditDlg.h
ImplementationFile=SqlEditDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=CSQLEditDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CONNECT_DLG]
Type=1
Class=CConnectDlg
ControlCount=9
Control1=IDC_RADIO1,button,1342308361
Control2=IDC_RADIO2,button,1342177289
Control3=IDC_BROWSE,button,1342242816
Control4=IDC_DNS_EDIT,edit,1352733700
Control5=IDC_SQL_EDIT,edit,1352728580
Control6=IDOK,button,1342242817
Control7=IDCANCEL,button,1342242816
Control8=IDC_STATIC,button,1342177287
Control9=IDC_STATIC,button,1342177287

[DLG:IDD_SQLEDIT_DLG]
Type=1
Class=CSQLEditDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_SQL_STR,edit,1352733700

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_CLOSE
Command3=ID_REFRESH_DATA
Command4=ID_SHOW_SQL
Command5=ID_ADD_TABLE
Command6=ID_APPEND_ROW
Command7=ID_DELETE_RECORD
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_MRU_FILE1
Command3=ID_APP_EXIT
Command4=ID_VIEW_TOOLBAR
Command5=ID_VIEW_STATUS_BAR
Command6=ID_APP_ABOUT
CommandCount=6

[MNU:IDR_ADOSampleTYPE]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_CLOSE
Command3=ID_FILE_MRU_FILE1
Command4=ID_APP_EXIT
Command5=ID_VIEW_TOOLBAR
Command6=ID_VIEW_STATUS_BAR
Command7=ID_WINDOW_NEW
Command8=ID_WINDOW_CASCADE
Command9=ID_WINDOW_TILE_HORZ
Command10=ID_WINDOW_ARRANGE
Command11=ID_APP_ABOUT
CommandCount=11

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

