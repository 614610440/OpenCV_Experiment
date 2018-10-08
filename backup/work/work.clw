; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CWorkDoc
LastTemplate=CButton
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "work.h"
LastPage=0

ClassCount=6
Class1=CWorkApp
Class2=CWorkDoc
Class3=CWorkView
Class4=CMainFrame

ResourceCount=2
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Class6=meni
Resource2=IDD_ABOUTBOX

[CLS:CWorkApp]
Type=0
HeaderFile=work.h
ImplementationFile=work.cpp
Filter=N
LastObject=CWorkApp

[CLS:CWorkDoc]
Type=0
HeaderFile=workDoc.h
ImplementationFile=workDoc.cpp
Filter=N
LastObject=CWorkDoc
BaseClass=CDocument
VirtualFilter=DC

[CLS:CWorkView]
Type=0
HeaderFile=workView.h
ImplementationFile=workView.cpp
Filter=C
LastObject=ID_MENUITEM32771


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=SEFMENTALPROVESS1
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=work.cpp
ImplementationFile=work.cpp
Filter=D
LastObject=ID_MENUITEM32771

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=SEFMENTALPROVESS1
CommandCount=1

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
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

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[CLS:meni]
Type=0
HeaderFile=meni.h
ImplementationFile=meni.cpp
BaseClass=CButton
Filter=W

