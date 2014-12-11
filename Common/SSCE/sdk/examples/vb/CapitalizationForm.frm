VERSION 5.00
Begin VB.Form CapitalizationForm 
   BackColor       =   &H00FFFFFF&
   Caption         =   "CapitalizationForm.frm"
   ClientHeight    =   5355
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   9315
   LinkTopic       =   "Form1"
   ScaleHeight     =   5355
   ScaleWidth      =   9315
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton closeBtn 
      Caption         =   "Close"
      Height          =   375
      Left            =   7920
      TabIndex        =   5
      Top             =   4800
      Width           =   1095
   End
   Begin VB.CommandButton startBtn 
      Caption         =   "Start"
      Height          =   495
      Left            =   4050
      TabIndex        =   4
      Top             =   3480
      Width           =   1215
   End
   Begin VB.TextBox Text1 
      Height          =   1575
      HideSelection   =   0   'False
      Left            =   360
      MultiLine       =   -1  'True
      TabIndex        =   3
      Text            =   "CapitalizationForm.frx":0000
      Top             =   1800
      Width           =   8535
   End
   Begin VB.Label Label3 
      BackColor       =   &H00FFFFFF&
      Caption         =   "Click the Start button to automatically correct the misspelled words in the text box below."
      Height          =   495
      Left            =   120
      TabIndex        =   2
      Top             =   1080
      Width           =   8895
   End
   Begin VB.Label Label2 
      BackColor       =   &H00C0E0FF&
      Caption         =   "Sentry is case-sensitive, which means it can detect words that aren't capitalized when they should be."
      Height          =   615
      Left            =   120
      TabIndex        =   1
      Top             =   480
      Width           =   8895
   End
   Begin VB.Label Label1 
      BackColor       =   &H00FFFFFF&
      Caption         =   "Detect capitalization errors"
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
Attribute VB_Name = "CapitalizationForm"
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

Private Sub closeBtn_Click()
    Me.Hide
End Sub

Private Sub startBtn_Click()
    Call SSCEVB_CheckCtrlDlg(Me.hWnd, Text1.hWnd, False)
End Sub
