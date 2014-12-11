VERSION 5.00
Begin VB.Form AutoCorrectForm 
   BackColor       =   &H00FFFFFF&
   Caption         =   "AutoCorrectForm.frm"
   ClientHeight    =   5475
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   9345
   LinkTopic       =   "Form1"
   ScaleHeight     =   5475
   ScaleWidth      =   9345
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton closeBtn 
      Caption         =   "Close"
      Height          =   375
      Left            =   8040
      TabIndex        =   5
      Top             =   4920
      Width           =   1095
   End
   Begin VB.CommandButton startBtn 
      Caption         =   "Start"
      Height          =   495
      Left            =   4065
      TabIndex        =   4
      Top             =   4200
      Width           =   1215
   End
   Begin VB.TextBox Text1 
      Height          =   1695
      Left            =   465
      MultiLine       =   -1  'True
      TabIndex        =   3
      Text            =   "AutoCorrectForm.frx":0000
      Top             =   2280
      Width           =   8415
   End
   Begin VB.Label Label3 
      BackColor       =   &H00FFFFFF&
      Caption         =   "Click the Start button to automatically correct the misspelled words in the text box below."
      Height          =   495
      Left            =   585
      TabIndex        =   2
      Top             =   1560
      Width           =   8175
   End
   Begin VB.Label Label2 
      BackColor       =   &H00C0E0FF&
      Caption         =   $"AutoCorrectForm.frx":00B0
      Height          =   615
      Left            =   525
      TabIndex        =   1
      Top             =   720
      Width           =   8295
   End
   Begin VB.Label Label1 
      BackColor       =   &H00FFFFFF&
      Caption         =   "Auto-correct misspelled words"
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
      Width           =   9135
   End
End
Attribute VB_Name = "AutoCorrectForm"
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
    ' Make sure "correct.tlx" is open, otherwise the demo won't run.
    If (SSCEVB_GetLexId("correct.tlx") < 0) Then
        ' Ask the user to load it.
        MsgBox "The 'correct.tlx' dictionary file is not open. When the " & _
          "Dictionary dialog box opens, click the Add File button to open " & _
          "'correct.tlx'"
        Call SSCEVB_EditLexDlg(Me.hWnd)
    End If

    ' Make sure Auto Correct is enabled.
    Call SSCEVB_SetAutoCorrect(True)

    ' Check the text. This will auto-correct the words without displaying
    ' the spelling dialog.
    Call SSCEVB_CheckCtrlDlg(Me.hWnd, Text1.hWnd, False)
End Sub
