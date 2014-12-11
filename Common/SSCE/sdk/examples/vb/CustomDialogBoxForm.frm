VERSION 5.00
Begin VB.Form CustomDialogBoxForm 
   BackColor       =   &H00FFFFFF&
   Caption         =   "CustomDialogBoxForm, SpellingDialogForm"
   ClientHeight    =   5172
   ClientLeft      =   60
   ClientTop       =   348
   ClientWidth     =   9300
   LinkTopic       =   "Form1"
   ScaleHeight     =   5172
   ScaleWidth      =   9300
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton closeBtn 
      Caption         =   "Close"
      Height          =   375
      Left            =   8040
      TabIndex        =   5
      Top             =   4680
      Width           =   1095
   End
   Begin VB.CommandButton checkSpellingBtn 
      Caption         =   "Check Spelling"
      Height          =   375
      Left            =   3863
      TabIndex        =   4
      Top             =   3840
      Width           =   1575
   End
   Begin VB.TextBox Text1 
      Height          =   1455
      HideSelection   =   0   'False
      Left            =   240
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   3
      Text            =   "CustomDialogBoxForm.frx":0000
      Top             =   2280
      Width           =   8895
   End
   Begin VB.Label Label3 
      BackColor       =   &H00FFFFFF&
      Caption         =   "To run the example, enter some text in the text area and click the Check Spelling button."
      Height          =   615
      Left            =   240
      TabIndex        =   2
      Top             =   1440
      Width           =   8895
   End
   Begin VB.Label Label2 
      BackColor       =   &H00C0E0FF&
      Caption         =   $"CustomDialogBoxForm.frx":02CF
      Height          =   615
      Left            =   240
      TabIndex        =   1
      Top             =   720
      Width           =   8895
   End
   Begin VB.Label Label1 
      BackColor       =   &H00FFFFFF&
      Caption         =   "Check spelling using a custom dialog box"
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
Attribute VB_Name = "CustomDialogBoxForm"
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
    ' Use SpellingDialogForm to check the spelling of the text box.
    Load SpellingDialogForm
    If (SpellingDialogForm.Start(Text1)) Then
        SpellingDialogForm.Show vbModal
    End If
    Unload SpellingDialogForm
End Sub

Private Sub closeBtn_Click()
    Me.Hide
End Sub
