VERSION 5.00
Begin VB.Form DoubledWordsForm 
   BackColor       =   &H00FFFFFF&
   Caption         =   "DoubledWordsForm.frm"
   ClientHeight    =   5445
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   9285
   LinkTopic       =   "Form1"
   ScaleHeight     =   5445
   ScaleWidth      =   9285
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command1 
      Caption         =   "Close"
      Height          =   375
      Left            =   7920
      TabIndex        =   5
      Top             =   4920
      Width           =   1095
   End
   Begin VB.CommandButton startBtn 
      Caption         =   "Start"
      Height          =   495
      Left            =   3960
      TabIndex        =   4
      Top             =   4080
      Width           =   1215
   End
   Begin VB.TextBox Text1 
      Height          =   1575
      HideSelection   =   0   'False
      Left            =   360
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   3
      Text            =   "DoubledWordsForm.frx":0000
      Top             =   2280
      Width           =   8415
   End
   Begin VB.Label Label3 
      BackColor       =   &H00FFFFFF&
      Caption         =   "Click the Start button to detect and correct doubled words in the text appearing in the text box."
      Height          =   615
      Left            =   240
      TabIndex        =   2
      Top             =   1440
      Width           =   8895
   End
   Begin VB.Label Label2 
      BackColor       =   &H00C0E0FF&
      Caption         =   $"DoubledWordsForm.frx":02D1
      Height          =   615
      Left            =   240
      TabIndex        =   1
      Top             =   720
      Width           =   8895
   End
   Begin VB.Label Label1 
      BackColor       =   &H00FFFFFF&
      Caption         =   "Detect doubled words"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
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
      Width           =   9015
   End
End
Attribute VB_Name = "DoubledWordsForm"
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

Private Sub Command1_Click()
    Me.Hide
End Sub

Private Sub startBtn_Click()
    ' Make sure doubled-word detection is enabled.
    Call SSCEVB_SetOption(SSCE_GetSid, SSCE_REPORT_DOUBLED_WORD_OPT, 1)
    
    ' Check the text to detect the doubled words.
    Call SSCEVB_CheckCtrlDlg(Me.hWnd, Text1.hWnd, False)
End Sub
