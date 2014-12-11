VERSION 5.00
Begin VB.Form CheckTextInCodeForm 
   BackColor       =   &H00FFFFFF&
   Caption         =   "CheckTextInCodeForm.frm"
   ClientHeight    =   5712
   ClientLeft      =   60
   ClientTop       =   348
   ClientWidth     =   9216
   LinkTopic       =   "Form1"
   ScaleHeight     =   5712
   ScaleWidth      =   9216
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton checkTextBoxBtn 
      Caption         =   "Check Spelling"
      Height          =   375
      Left            =   7320
      TabIndex        =   7
      Top             =   3240
      Width           =   1575
   End
   Begin VB.TextBox Text2 
      Height          =   975
      Left            =   120
      Locked          =   -1  'True
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   6
      Top             =   3960
      Width           =   8895
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Close"
      Height          =   375
      Left            =   8040
      TabIndex        =   4
      Top             =   5160
      Width           =   1095
   End
   Begin VB.TextBox Text1 
      Height          =   1455
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   3
      Text            =   "CheckTextInCodeForm.frx":0000
      Top             =   2160
      Width           =   7095
   End
   Begin VB.Label Label5 
      BackColor       =   &H00FFFFFF&
      Caption         =   "Misspelled words:"
      Height          =   255
      Left            =   120
      TabIndex        =   5
      Top             =   3720
      Width           =   1575
   End
   Begin VB.Label Label3 
      BackColor       =   &H00FFFFFF&
      Caption         =   $"CheckTextInCodeForm.frx":02EC
      Height          =   615
      Left            =   120
      TabIndex        =   2
      Top             =   1440
      Width           =   8895
   End
   Begin VB.Label Label2 
      BackColor       =   &H00C0E0FF&
      Caption         =   $"CheckTextInCodeForm.frx":03DA
      Height          =   615
      Left            =   120
      TabIndex        =   1
      Top             =   720
      Width           =   8895
   End
   Begin VB.Label Label1 
      BackColor       =   &H00FFFFFF&
      Caption         =   "Check spelling of strings in code without user interaction"
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
Attribute VB_Name = "CheckTextInCodeForm"
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

' Check the spelling of text entered in Text1 without interacting
' with the user. Display any misspelled words and suggestions in
' Text2.
Private Sub checkTextBoxBtn_Click()
    Dim text As String
    Dim textLen As Long
    Dim word As String
    Dim otherWord As String
    Dim suggestions(16) As String
    Dim scores(16) As Integer
    Dim s As String
    Dim i As Integer
    Dim result As Integer
    Dim cursor As Long

    ' Get the text from Text1.
    text = Text1.text

    ' textLen is the number of characters in the string.
    textLen = Len(text)

    ' Keep checking until all the text has been checked.
    cursor = 0
    Do
        result = SSCEVB_CheckString(SSCEVB_GetSid, text, cursor, word, otherWord)
        
        If (result And SSCE_MISSPELLED_WORD_RSLT) Then
            ' We found a misspelled word. Get some suggestions for it.
            Call SSCEVB_Suggest(SSCEVB_GetSid, word, 50, suggestions, scores, 16)
            
            s = word & ": "
            For i = 0 To 16 - 1
                If (suggestions(i) <> "") Then
                    If (i > 0) Then
                        s = s & ", "
                    End If
                    s = s & suggestions(i)
                End If
            Next
            
            ' Add the misspelled word and suggestions to the "Misspelled words" box.
            Text2.SelText = s & vbCrLf & vbCrLf
        End If

        ' Advance to the next word. This is necessary or SSCEVB_CheckString
        ' will keep reporting the same word.
        cursor = cursor + Len(word)
    Loop Until (result = SSCE_END_OF_BLOCK_RSLT)
End Sub

Private Sub Command1_Click()
    Me.Hide
End Sub
