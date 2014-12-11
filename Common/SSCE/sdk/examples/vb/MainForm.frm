VERSION 5.00
Begin VB.Form MainForm 
   BackColor       =   &H00FFFFFF&
   Caption         =   "MainForm.frm"
   ClientHeight    =   5880
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   9555
   LinkTopic       =   "Form1"
   ScaleHeight     =   5880
   ScaleWidth      =   9555
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton CloseBtn 
      Caption         =   "Close"
      Height          =   375
      Left            =   7200
      TabIndex        =   15
      Top             =   5280
      Width           =   1095
   End
   Begin VB.CommandButton featureBtn 
      Caption         =   "Doubled words"
      Height          =   495
      Index           =   11
      Left            =   3030
      TabIndex        =   14
      Top             =   3960
      Width           =   1695
   End
   Begin VB.CommandButton featureBtn 
      Caption         =   "Suggestions"
      Height          =   495
      Index           =   10
      Left            =   1230
      TabIndex        =   13
      Top             =   3960
      Width           =   1695
   End
   Begin VB.CommandButton featureBtn 
      Caption         =   "Capitalization"
      Height          =   495
      Index           =   9
      Left            =   6630
      TabIndex        =   12
      Top             =   3960
      Width           =   1695
   End
   Begin VB.CommandButton featureBtn 
      Caption         =   "Check HTML"
      Height          =   495
      Index           =   8
      Left            =   6630
      TabIndex        =   11
      Top             =   3360
      Width           =   1695
   End
   Begin VB.CommandButton featureBtn 
      Caption         =   "Check 3rd Party"
      Height          =   495
      Index           =   7
      Left            =   4830
      TabIndex        =   10
      Top             =   3360
      Width           =   1695
   End
   Begin VB.CommandButton featureBtn 
      Caption         =   "Custom dialog box"
      Height          =   495
      Index           =   6
      Left            =   3030
      TabIndex        =   9
      Top             =   3360
      Width           =   1695
   End
   Begin VB.CommandButton featureBtn 
      Caption         =   "Performance Test"
      Height          =   495
      Index           =   5
      Left            =   1230
      TabIndex        =   8
      Top             =   3360
      Width           =   1695
   End
   Begin VB.CommandButton featureBtn 
      Caption         =   "Auto correct"
      Height          =   495
      Index           =   4
      Left            =   4830
      TabIndex        =   7
      Top             =   3960
      Width           =   1695
   End
   Begin VB.CommandButton featureBtn 
      Caption         =   "Check text in code"
      Height          =   495
      Index           =   3
      Left            =   6630
      TabIndex        =   6
      Top             =   2760
      Width           =   1695
   End
   Begin VB.CommandButton featureBtn 
      Caption         =   "Check string"
      Height          =   495
      Index           =   2
      Left            =   4830
      TabIndex        =   5
      Top             =   2760
      Width           =   1695
   End
   Begin VB.CommandButton featureBtn 
      Caption         =   "Check background"
      Height          =   495
      Index           =   1
      Left            =   3030
      TabIndex        =   4
      Top             =   2760
      Width           =   1695
   End
   Begin VB.CommandButton featureBtn 
      Caption         =   "Check text box"
      Height          =   495
      Index           =   0
      Left            =   1230
      TabIndex        =   3
      Top             =   2760
      Width           =   1695
   End
   Begin VB.Label Label3 
      BackColor       =   &H00FFFFFF&
      Caption         =   $"MainForm.frx":0000
      Height          =   735
      Left            =   1110
      TabIndex        =   2
      Top             =   1800
      Width           =   7335
   End
   Begin VB.Label Label2 
      BackColor       =   &H00C0E0FF&
      Caption         =   $"MainForm.frx":0091
      Height          =   615
      Left            =   1110
      TabIndex        =   1
      Top             =   1080
      Width           =   7335
      WordWrap        =   -1  'True
   End
   Begin VB.Label Label1 
      BackColor       =   &H00FFFFFF&
      Caption         =   "Sentry Spelling Checker Engine"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   20.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Left            =   240
      TabIndex        =   0
      Top             =   120
      Width           =   9135
   End
   Begin VB.Image Image1 
      Height          =   600
      Left            =   120
      Picture         =   "MainForm.frx":0124
      Top             =   5040
      Width           =   2865
   End
End
Attribute VB_Name = "MainForm"
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

' Set this constant to your Sentry license key, provided by
' Wintertree Software.
Private Const SENTRY_LICENSE_KEY = 0

' The actual license key
Private LicenseKey As Long

Private Sub closeBtn_Click()
    Unload Me
End Sub

Private Sub featureBtn_Click(Index As Integer)
    ' Make sure we have a valid license key or the examples won't work.
    If (LicenseKey = 0) Then
        LicenseKeyForm.Show vbModal
        LicenseKey = LicenseKeyForm.LicenseKey
        Unload LicenseKeyForm
    End If
    If (LicenseKey <> 0) Then
        SSCEVB_SetKey (LicenseKey)
    End If
    
    Select Case Index
    Case 0: CheckTextBoxForm.Show vbModal
    Case 1: CheckBackgroundForm.Show vbModal
    Case 2: CheckStringForm.Show vbModal
    Case 3: CheckTextInCodeForm.Show vbModal
    Case 4: AutoCorrectForm.Show vbModal
    Case 5: PerformanceTestForm.Show vbModal
    Case 6: CustomDialogBoxForm.Show vbModal
    Case 7: Check3rdPartyForm.Show vbModal
    Case 8: CheckHTMLForm.Show vbModal
    Case 9: CapitalizationForm.Show vbModal
    Case 10: SuggestionsForm.Show vbModal
    Case 11: DoubledWordsForm.Show vbModal
    End Select
End Sub

Private Sub Form_Load()
    
    ' Make sure we have a license key.
    LicenseKey = SENTRY_LICENSE_KEY
End Sub

