VERSION 5.00
Begin VB.Form SuggestionsForm 
   BackColor       =   &H00FFFFFF&
   Caption         =   "SuggestionsForm.frm"
   ClientHeight    =   5565
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   9330
   LinkTopic       =   "Form1"
   ScaleHeight     =   5565
   ScaleWidth      =   9330
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton closeBtn 
      Caption         =   "Close"
      Height          =   375
      Left            =   7920
      TabIndex        =   11
      Top             =   5040
      Width           =   1215
   End
   Begin VB.ListBox suggestionsList 
      Height          =   2205
      Left            =   4560
      TabIndex        =   9
      Top             =   2520
      Width           =   3375
   End
   Begin VB.CommandButton suggestBtn 
      Caption         =   "Suggest"
      Height          =   375
      Left            =   1680
      TabIndex        =   8
      Top             =   4560
      Width           =   1215
   End
   Begin VB.TextBox depthText 
      Height          =   375
      Left            =   1800
      TabIndex        =   7
      Text            =   "50"
      Top             =   4080
      Width           =   2295
   End
   Begin VB.CheckBox typographicalCheck 
      BackColor       =   &H00FFFFFF&
      Caption         =   "Use Typographical matching"
      Height          =   375
      Left            =   240
      TabIndex        =   5
      Top             =   3600
      Value           =   1  'Checked
      Width           =   3615
   End
   Begin VB.CheckBox phoneticCheck 
      BackColor       =   &H00FFFFFF&
      Caption         =   "Use Phonetic matching"
      Height          =   375
      Left            =   240
      TabIndex        =   4
      Top             =   3240
      Width           =   3615
   End
   Begin VB.TextBox wordText 
      Height          =   375
      Left            =   1800
      TabIndex        =   3
      Top             =   2760
      Width           =   2295
   End
   Begin VB.Label Label5 
      BackColor       =   &H00FFFFFF&
      Caption         =   "Enter a word and click the Suggest button to look up suggestions. "
      Height          =   375
      Left            =   240
      TabIndex        =   10
      Top             =   2040
      Width           =   8895
   End
   Begin VB.Label Label4 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00FFFFFF&
      Caption         =   "Depth (1-100):"
      Height          =   255
      Left            =   240
      TabIndex        =   6
      Top             =   4080
      Width           =   1455
   End
   Begin VB.Label Label3 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00FFFFFF&
      Caption         =   "Word:"
      Height          =   255
      Left            =   240
      TabIndex        =   2
      Top             =   2880
      Width           =   1455
   End
   Begin VB.Label Label2 
      BackColor       =   &H00C0E0FF&
      Caption         =   $"SuggestionsForm.frx":0000
      Height          =   1455
      Left            =   240
      TabIndex        =   1
      Top             =   600
      Width           =   8895
   End
   Begin VB.Label Label1 
      BackColor       =   &H00FFFFFF&
      Caption         =   "Intelligent Suggestions for Misspelled Words"
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
Attribute VB_Name = "SuggestionsForm"
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

Private Sub suggestBtn_Click()
    Dim typo As Boolean
    Dim phonetic As Boolean
    Dim optVal As Long
    Dim suggestions(16) As String
    Dim scores(16) As Integer
    Dim i As Integer
    
    ' Set the options requested in the check boxes.
    optVal = 0
    phonetic = False
    If (phoneticCheck.Value = 1) Then
        optVal = 1
        phonetic = True
    End If
    Call SSCEVB_SetOption(SSCEVB_GetSid, SSCE_SUGGEST_PHONETIC_OPT, optVal)
    
    optVal = 0
    typo = False
    If (typographicalCheck.Value = 1) Then
        optVal = 1
        typo = True
    End If
    
    ' Make sure one of the suggestion algorithms was selected, or
    ' no suggestions will be displayed.
    If ((Not typo) And (Not phonetic)) Then
        typo = True
        optVal = 1
        typographicalCheck.Value = 1
    End If
    Call SSCEVB_SetOption(SSCEVB_GetSid, SSCE_SUGGEST_TYPOGRAPHICAL_OPT, optVal)
    
    ' Get the suggestions using the parameters entered by the user.
    Call SSCEVB_Suggest(SSCEVB_GetSid, wordText.text, Val(depthText.text), _
      suggestions, scores, 16)

    ' Display the suggestions in the list box.
    suggestionsList.Clear
    For i = 0 To 16
        If (suggestions(i) <> "") Then
            suggestionsList.AddItem (suggestions(i))
        End If
    Next
End Sub
