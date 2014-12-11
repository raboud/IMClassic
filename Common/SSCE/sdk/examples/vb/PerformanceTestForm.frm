VERSION 5.00
Object = "{3B7C8863-D78F-101B-B9B5-04021C009402}#1.2#0"; "RICHTX32.OCX"
Begin VB.Form PerformanceTestForm 
   BackColor       =   &H00FFFFFF&
   Caption         =   "PerformanceTestForm.frm"
   ClientHeight    =   5370
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   9180
   LinkTopic       =   "Form1"
   ScaleHeight     =   5370
   ScaleWidth      =   9180
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command1 
      Caption         =   "Close"
      Height          =   375
      Left            =   7920
      TabIndex        =   6
      Top             =   4920
      Width           =   1095
   End
   Begin VB.CommandButton startBtn 
      Caption         =   "Start"
      Height          =   375
      Left            =   3600
      TabIndex        =   5
      Top             =   3960
      Width           =   1575
   End
   Begin RichTextLib.RichTextBox RichTextBox1 
      Height          =   1935
      Left            =   120
      TabIndex        =   3
      Top             =   1920
      Width           =   8895
      _ExtentX        =   15690
      _ExtentY        =   3413
      _Version        =   393217
      ScrollBars      =   2
      FileName        =   "D:\Wintree\Projects\ssce\examples\vb\VBExample\alice.rtf"
      TextRTF         =   $"PerformanceTestForm.frx":0000
   End
   Begin VB.Label resultsLbl 
      Height          =   255
      Left            =   743
      TabIndex        =   4
      Top             =   4440
      Width           =   7695
   End
   Begin VB.Label Label3 
      BackColor       =   &H00FFFFFF&
      Caption         =   $"PerformanceTestForm.frx":26E08
      Height          =   615
      Left            =   120
      TabIndex        =   2
      Top             =   1200
      Width           =   8895
   End
   Begin VB.Label Label2 
      BackColor       =   &H00C0E0FF&
      Caption         =   $"PerformanceTestForm.frx":26F2F
      Height          =   615
      Left            =   120
      TabIndex        =   1
      Top             =   600
      Width           =   8895
   End
   Begin VB.Label Label1 
      BackColor       =   &H00FFFFFF&
      Caption         =   "How fast is Sentry?"
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
      Top             =   120
      Width           =   8895
   End
End
Attribute VB_Name = "PerformanceTestForm"
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

Private Sub startBtn_Click()
    Dim text As String
    Dim textLen As Long
    Dim word As String
    Dim otherWord As String
    Dim blkId As Integer
    Dim numMisspelledWords As Long
    Dim i As Integer
    Dim result As Integer
    Dim totalTime As Single
    Dim startTime As Single
    Dim endTime As Single
    Dim wordCount As Long

    resultsLbl.Caption = ""

    ' Get the text from RichTextBox1.
    text = RichTextBox1.text

    ' textLen is the number of characters in the string.
    textLen = Len(text)

    ' Open a block to check the text. Checking text using CheckBlock
    ' is faster in VB than CheckString, probably because VB makes a
    ' new copy of the string on each call.
    blkId = SSCEVB_OpenBlock(SSCE_GetSid, text, textLen, textLen, True)
    If (blkId < 0) Then
        MsgBox "SSCEVB_OpenBlock returned " & str(blkId)
        Exit Sub
    End If
    
    ' Keep checking until all the text has been checked.
    numMisspelledWords = 0
    totalTime = 0
    Do
        startTime = Timer
        result = SSCEVB_CheckBlock(SSCEVB_GetSid, blkId, word, otherWord)
        endTime = Timer
        totalTime = totalTime + (endTime - startTime)
 
        If ((result And SSCE_MISSPELLED_WORD_RSLT) <> 0) Then
            numMisspelledWords = numMisspelledWords + 1
        End If

        ' Advance to the next word. This is necessary or SSCEVB_CheckBlock
        ' will keep reporting the same word.
        Call SSCEVB_NextBlockWord(SSCEVB_GetSid, blkId)
    Loop Until (result = SSCE_END_OF_BLOCK_RSLT)

    ' Count the number of words in the text.
    Call SSCEVB_GetBlockInfo(SSCEVB_GetSid, blkId, 0&, 0&, 0&, wordCount)
    
    ' Make sure we don't divide by 0.
    If (totalTime = 0) Then
        totalTime = 0.001
    End If
    resultsLbl.Caption = wordCount & " words. " & _
      numMisspelledWords & " misspelled words. " & _
      Round(totalTime, 2) & " seconds. " & _
      Round(wordCount / totalTime) & " words per second."
    
    Call SSCEVB_CloseBlock(SSCEVB_GetSid, blkId)
End Sub
