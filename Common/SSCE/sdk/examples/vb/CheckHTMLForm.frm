VERSION 5.00
Begin VB.Form CheckHTMLForm 
   BackColor       =   &H00FFFFFF&
   Caption         =   "CheckHTMLForm.frm"
   ClientHeight    =   5745
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   9030
   LinkTopic       =   "Form1"
   ScaleHeight     =   5745
   ScaleWidth      =   9030
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton checkSpellingBtn 
      Caption         =   "Check Spelling"
      Height          =   375
      Left            =   3548
      TabIndex        =   5
      Top             =   4560
      Width           =   1935
   End
   Begin VB.CommandButton closeBtn 
      Caption         =   "Close"
      Height          =   375
      Left            =   7560
      TabIndex        =   4
      Top             =   5160
      Width           =   1215
   End
   Begin VB.TextBox Text1 
      Height          =   2535
      HideSelection   =   0   'False
      Left            =   360
      MultiLine       =   -1  'True
      TabIndex        =   3
      Text            =   "CheckHTMLForm.frx":0000
      Top             =   1920
      Width           =   8295
   End
   Begin VB.Label Label3 
      BackColor       =   &H00FFFFFF&
      Caption         =   "Click the Check Spelling button to check the HTML entered below. You can also edit the text box to add your own HTML text."
      Height          =   495
      Left            =   360
      TabIndex        =   2
      Top             =   1320
      Width           =   8415
   End
   Begin VB.Label Label2 
      BackColor       =   &H00C0E0FF&
      Caption         =   $"CheckHTMLForm.frx":0523
      Height          =   615
      Left            =   360
      TabIndex        =   1
      Top             =   600
      Width           =   8415
   End
   Begin VB.Label Label1 
      BackColor       =   &H00FFFFFF&
      Caption         =   "Check spelling of text in HTML"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   120
      TabIndex        =   0
      Top             =   0
      Width           =   8775
   End
End
Attribute VB_Name = "CheckHTMLForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' Sentry Spelling Checker Engine
' Visual Basic Example
'
' Copyright (c) 2000 Wintertree Software Inc.
' www.wintertree-software.com
'
' Use, duplication, and disclosure of this file is governed
' by a license agreement between Wintertree Software Inc. and
' the licensee.
'
' $Id$

Option Explicit

Private Sub checkSpellingBtn_Click()
    Dim rv
    
    ' Make sure the ignore HTML option is set.
    Call SSCEVB_SetOption(SSCEVB_GetSid, SSCE_IGNORE_HTML_MARKUPS_OPT, 1)
    
    rv = SSCEVB_CheckCtrlDlg(Me.hWnd, Text1.hWnd, False)
    If (rv < 0) Then
        MsgBox "CheckCtrlDlg returned " & rv
    End If
End Sub

Private Sub closeBtn_Click()
    Me.Hide
End Sub
