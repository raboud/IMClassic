VERSION 5.00
Object = "{3B7C8863-D78F-101B-B9B5-04021C009402}#1.2#0"; "RICHTX32.OCX"
Begin VB.Form Check3rdPartyForm 
   BackColor       =   &H00FFFFFF&
   Caption         =   "Check3rdPartyForm.frm"
   ClientHeight    =   5400
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   9300
   LinkTopic       =   "Form1"
   ScaleHeight     =   5400
   ScaleWidth      =   9300
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command1 
      Caption         =   "Close"
      Height          =   375
      Left            =   8040
      TabIndex        =   5
      Top             =   4920
      Width           =   1095
   End
   Begin VB.CommandButton checkTextBoxBtn 
      Caption         =   "Check Spelling"
      Height          =   375
      Left            =   3863
      TabIndex        =   4
      Top             =   4320
      Width           =   1575
   End
   Begin RichTextLib.RichTextBox RichTextBox1 
      Height          =   1935
      Left            =   120
      TabIndex        =   3
      Top             =   2280
      Width           =   9015
      _ExtentX        =   15901
      _ExtentY        =   3413
      _Version        =   393217
      Enabled         =   -1  'True
      HideSelection   =   0   'False
      ScrollBars      =   2
      FileName        =   "alice.rtf"
      TextRTF         =   $"Check3rdPartyForm.frx":0000
   End
   Begin VB.Label Label3 
      BackColor       =   &H00FFFFFF&
      Caption         =   "Click the Check Spelling button to start checking the text in the text box. You can also edit the text box to add your own text."
      Height          =   495
      Left            =   120
      TabIndex        =   2
      Top             =   1680
      Width           =   8895
   End
   Begin VB.Label Label2 
      BackColor       =   &H00C0E0FF&
      Caption         =   $"Check3rdPartyForm.frx":26E14
      Height          =   975
      Left            =   120
      TabIndex        =   1
      Top             =   600
      Width           =   8895
   End
   Begin VB.Label Label1 
      BackColor       =   &H00FFFFFF&
      Caption         =   "Check third-party text boxes and text controls"
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
Attribute VB_Name = "Check3rdPartyForm"
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

Private Sub checkTextBoxBtn_Click()
    Dim text As String
    Dim origLen As Long
    Dim word As String
    Dim otherWord As String
    Dim curWord As String
    Dim cursor As Long
    Dim rv As Integer
    Dim growth As Long
    
    ' Get the unformatted text from the control.
    text = RichTextBox1.text
    
    ' Allocate some extra space to allow room for growth.
    origLen = Len(text)
    growth = origLen / 5
    If (growth < 100) Then
        growth = 100
    End If
    text = text + Space$(growth)
    
    ' Check for spelling errors in the text.
    cursor = 0
    While (SSCEVB_CheckString(SSCEVB_GetSid, text, cursor, word, otherWord) <> _
      SSCE_END_OF_BLOCK_RSLT)
        ' A problem was encountered with a word in the text.
        ' Highlight the misspelled word in the text box. Use whatever
        ' properties and methods are appropriate to the 3rd-party control
        ' you are using.
        RichTextBox1.SelStart = cursor
        RichTextBox1.SelLength = Len(word)
        
        ' Check the current word using CheckBlockDlg. This will give the user
        ' a chance to correct the misspelling. It may also be corrected
        ' automatically.
        curWord = word + Space$(SSCE_MAX_WORD_SZ)
        rv = SSCEVB_CheckBlockDlg(Me.hWnd, curWord, Len(word), Len(curWord), False)
        If (rv = SSCE_CANCEL_ERR) Then
            ' User canceled.
            Exit Sub
        End If
        
        ' See if the word was changed.
        If (curWord <> word) Then
            ' Update the block.
            If (SSCEVB_ReplaceStringWord(SSCEVB_GetSid, text, cursor, curWord) >= 0) Then
                ' Update the rich-text box. The current word is selected,
                ' so all we have to do is replace the selected text.
                ' Use whatever properties or methods are appropriate to the
                ' 3rd-party control you are using.
                RichTextBox1.SelText = curWord
            End If
        End If
        
        ' Advance to the next word.
        cursor = cursor + Len(curWord)
    Wend
End Sub

Private Sub Command1_Click()
    Me.Hide
End Sub
