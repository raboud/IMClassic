VERSION 5.00
Begin VB.Form LicenseKeyForm 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Enter license key"
   ClientHeight    =   3060
   ClientLeft      =   2835
   ClientTop       =   3480
   ClientWidth     =   3750
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1807.949
   ScaleMode       =   0  'User
   ScaleWidth      =   3521.047
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   390
      Left            =   495
      TabIndex        =   2
      Top             =   2460
      Width           =   1140
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   390
      Left            =   2100
      TabIndex        =   3
      Top             =   2460
      Width           =   1140
   End
   Begin VB.TextBox txtKey 
      Height          =   345
      IMEMode         =   3  'DISABLE
      Left            =   1290
      TabIndex        =   1
      Top             =   1965
      Width           =   2325
   End
   Begin VB.Label Label2 
      Caption         =   "To avoid seeing this message in future, set SENTRY_LICENSE_KEY in MainForm.frm to your license key."
      Height          =   735
      Left            =   120
      TabIndex        =   5
      Top             =   1080
      Width           =   3495
   End
   Begin VB.Label Label1 
      Caption         =   "Please enter your Sentry license key, provided by Wintertree Software. The demo will not run without the key."
      Height          =   855
      Left            =   120
      TabIndex        =   4
      Top             =   120
      Width           =   3495
   End
   Begin VB.Label lblLabels 
      Caption         =   "&License key:"
      Height          =   270
      Index           =   1
      Left            =   105
      TabIndex        =   0
      Top             =   1980
      Width           =   1080
   End
End
Attribute VB_Name = "LicenseKeyForm"
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

Public LicenseKey As Long

Private Sub cmdCancel_Click()
    Me.Hide
End Sub

Private Sub cmdOK_Click()
    LicenseKey = Val("&H" + txtKey.text)
    Me.Hide
End Sub
