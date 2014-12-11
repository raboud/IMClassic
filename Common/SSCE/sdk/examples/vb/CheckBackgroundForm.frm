VERSION 5.00
Object = "{3B7C8863-D78F-101B-B9B5-04021C009402}#1.2#0"; "RICHTX32.OCX"
Begin VB.Form CheckBackgroundForm 
   BackColor       =   &H00FFFFFF&
   Caption         =   "CheckBackgroundForm.frm"
   ClientHeight    =   4905
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   9165
   LinkTopic       =   "Form1"
   ScaleHeight     =   4905
   ScaleWidth      =   9165
   StartUpPosition =   3  'Windows Default
   Begin RichTextLib.RichTextBox RichTextBox2 
      Height          =   855
      Left            =   240
      TabIndex        =   5
      Top             =   2880
      Width           =   8655
      _ExtentX        =   15266
      _ExtentY        =   1508
      _Version        =   393217
      Enabled         =   -1  'True
      ScrollBars      =   2
      TextRTF         =   $"CheckBackgroundForm.frx":0000
   End
   Begin RichTextLib.RichTextBox RichTextBox1 
      Height          =   855
      Left            =   240
      TabIndex        =   4
      Top             =   1920
      Width           =   8655
      _ExtentX        =   15266
      _ExtentY        =   1508
      _Version        =   393217
      Enabled         =   -1  'True
      ScrollBars      =   2
      TextRTF         =   $"CheckBackgroundForm.frx":0082
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Close"
      Height          =   375
      Left            =   7920
      TabIndex        =   0
      Top             =   4320
      Width           =   1095
   End
   Begin VB.Label Label3 
      BackColor       =   &H00FFFFFF&
      Caption         =   $"CheckBackgroundForm.frx":0104
      Height          =   495
      Left            =   360
      TabIndex        =   3
      Top             =   1320
      Width           =   8415
   End
   Begin VB.Label Label2 
      BackColor       =   &H00C0E0FF&
      Caption         =   $"CheckBackgroundForm.frx":01C1
      Height          =   615
      Left            =   360
      TabIndex        =   2
      Top             =   600
      Width           =   8415
   End
   Begin VB.Label Label1 
      BackColor       =   &H00FFFFFF&
      Caption         =   "Check spelling in rich-text boxes in the background"
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
      Left            =   240
      TabIndex        =   1
      Top             =   120
      Width           =   8775
   End
End
Attribute VB_Name = "CheckBackgroundForm"
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

Private Sub RichTextBox1_GotFocus()
    SSCEVB_CheckCtrlBackground (RichTextBox1.hWnd)
End Sub

Private Sub RichTextBox2_GotFocus()
    SSCEVB_CheckCtrlBackground (RichTextBox2.hWnd)
End Sub

