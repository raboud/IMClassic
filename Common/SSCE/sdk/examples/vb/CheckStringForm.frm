VERSION 5.00
Begin VB.Form CheckStringForm 
   BackColor       =   &H00FFFFFF&
   Caption         =   "CheckStringForm.frm"
   ClientHeight    =   4575
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   9060
   LinkTopic       =   "Form1"
   ScaleHeight     =   4575
   ScaleWidth      =   9060
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton closeBtn 
      Caption         =   "Close"
      Height          =   375
      Left            =   7680
      TabIndex        =   5
      Top             =   3960
      Width           =   1215
   End
   Begin VB.CommandButton checkSpellingBtn 
      Caption         =   "Check Spelling"
      Height          =   375
      Left            =   3563
      TabIndex        =   4
      Top             =   3600
      Width           =   1935
   End
   Begin VB.TextBox Text1 
      Height          =   1335
      Left            =   240
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   3
      Text            =   "CheckStringForm.frx":0000
      Top             =   2160
      Width           =   8655
   End
   Begin VB.Label Label3 
      BackColor       =   &H00FFFFFF&
      Caption         =   "Click the Check Spelling button to check the text entered below. You can also edit the text box to add your own text."
      Height          =   495
      Left            =   360
      TabIndex        =   2
      Top             =   1560
      Width           =   8415
   End
   Begin VB.Label Label2 
      BackColor       =   &H00C0E0FF&
      Caption         =   $"CheckStringForm.frx":012B
      Height          =   615
      Left            =   323
      TabIndex        =   1
      Top             =   840
      Width           =   8415
   End
   Begin VB.Label Label1 
      BackColor       =   &H00FFFFFF&
      Caption         =   "Interactively check spelling of Strings"
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
      Top             =   120
      Width           =   8775
   End
End
Attribute VB_Name = "CheckStringForm"
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
    Dim result As Integer
    Dim text As String
    Dim textLen As Long
    Dim textSz As Long
    Dim growth As Long

    ' Get the contents of the text box into a string.
    text = Text1.text

    ' textLen is the actual number of characters in the string.
    textLen = Len(text)

    ' Add some extra space to allow room for growth.
    growth = textLen / 5
    If (growth < 100) Then
        growth = 100
    End If
    text = text + String$(growth, " ")

    ' textSz is the total capacity of the string.
    textSz = Len(text)

    ' Check the spelling.
    result = SSCEVB_CheckBlockDlg(Me.hWnd, text, textLen, textSz, True)

    If (result >= 0) Then
        ' The return value from SSCEVB_CheckBlockDlg is the number of
        ' characters now in the string (following corrections made by
        ' the user).
        text = Left$(text, result)
        
        ' Put the correct string back into the text box.
        Text1.text = text
    End If
End Sub

Private Sub closeBtn_Click()
    Me.Hide
End Sub

