VERSION 5.00
Object = "{3B7C8863-D78F-101B-B9B5-04021C009402}#1.2#0"; "RICHTX32.OCX"
Begin VB.Form CheckTextBoxForm 
   BackColor       =   &H00FFFFFF&
   Caption         =   "CheckTextBoxForm.frm"
   ClientHeight    =   5505
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   9360
   LinkTopic       =   "Form1"
   ScaleHeight     =   5505
   ScaleWidth      =   9360
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton checkRichTextBoxBtn 
      Caption         =   "Check Spelling"
      Height          =   375
      Left            =   7440
      TabIndex        =   9
      Top             =   4440
      Width           =   1575
   End
   Begin RichTextLib.RichTextBox RichTextBox1 
      Height          =   1095
      Left            =   240
      TabIndex        =   7
      Top             =   3720
      Width           =   7095
      _ExtentX        =   12515
      _ExtentY        =   1931
      _Version        =   393217
      Enabled         =   -1  'True
      HideSelection   =   0   'False
      ScrollBars      =   2
      FileName        =   "alice.rtf"
      TextRTF         =   $"CheckTextBoxForm.frx":0000
   End
   Begin VB.CommandButton checkTextBoxBtn 
      Caption         =   "Check Spelling"
      Height          =   375
      Left            =   7440
      TabIndex        =   6
      Top             =   3000
      Width           =   1575
   End
   Begin VB.TextBox Text1 
      Height          =   975
      HideSelection   =   0   'False
      Left            =   240
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   4
      Text            =   "CheckTextBoxForm.frx":26E08
      Top             =   2400
      Width           =   7095
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Close"
      Height          =   375
      Left            =   7920
      TabIndex        =   0
      Top             =   4920
      Width           =   1095
   End
   Begin VB.Label Label5 
      BackColor       =   &H00FFFFFF&
      Caption         =   "Rich-text Box:"
      Height          =   255
      Left            =   240
      TabIndex        =   8
      Top             =   3480
      Width           =   1575
   End
   Begin VB.Label Label4 
      BackColor       =   &H00FFFFFF&
      Caption         =   "Text box:"
      Height          =   255
      Left            =   240
      TabIndex        =   5
      Top             =   2160
      Width           =   1455
   End
   Begin VB.Label Label3 
      BackColor       =   &H00FFFFFF&
      Caption         =   $"CheckTextBoxForm.frx":27066
      Height          =   615
      Left            =   240
      TabIndex        =   3
      Top             =   1440
      Width           =   8895
   End
   Begin VB.Label Label2 
      BackColor       =   &H00C0E0FF&
      Caption         =   $"CheckTextBoxForm.frx":270EE
      Height          =   615
      Left            =   240
      TabIndex        =   2
      Top             =   720
      Width           =   8895
   End
   Begin VB.Label Label1 
      BackColor       =   &H00FFFFFF&
      Caption         =   "Check spelling of text boxes and rich-text boxes interactively"
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
      TabIndex        =   1
      Top             =   120
      Width           =   9135
   End
End
Attribute VB_Name = "CheckTextBoxForm"
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

' Check the spelling of text in the rich-text box.
Private Sub checkRichTextBoxBtn_Click()
    Call SSCEVB_CheckCtrlDlg(Me.hWnd, RichTextBox1.hWnd, False)
End Sub

' Check the spelling of text in the text box.
Private Sub checkTextBoxBtn_Click()
    Call SSCEVB_CheckCtrlDlg(Me.hWnd, Text1.hWnd, False)
End Sub

Private Sub Command1_Click()
    Me.Hide
End Sub
