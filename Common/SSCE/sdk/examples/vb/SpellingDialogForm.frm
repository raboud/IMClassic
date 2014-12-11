VERSION 5.00
Begin VB.Form SpellingDialogForm 
   Caption         =   "Check Spelling"
   ClientHeight    =   2985
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   6015
   LinkTopic       =   "Form1"
   ScaleHeight     =   2985
   ScaleWidth      =   6015
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cancelBtn 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   120
      TabIndex        =   12
      Top             =   2520
      Width           =   1215
   End
   Begin VB.ListBox suggestionsList 
      Height          =   2010
      ItemData        =   "SpellingDialogForm.frx":0000
      Left            =   2160
      List            =   "SpellingDialogForm.frx":0002
      TabIndex        =   11
      Top             =   840
      Width           =   2415
   End
   Begin VB.TextBox changeToText 
      Height          =   285
      Left            =   2160
      TabIndex        =   9
      Top             =   480
      Width           =   2415
   End
   Begin VB.CommandButton addBtn 
      Caption         =   "&Add"
      Height          =   375
      Left            =   4680
      TabIndex        =   7
      Top             =   2520
      Width           =   1215
   End
   Begin VB.CommandButton suggestBtn 
      Caption         =   "&Suggest"
      Height          =   375
      Left            =   4680
      TabIndex        =   6
      Top             =   2040
      Width           =   1215
   End
   Begin VB.CommandButton changeAllBtn 
      Caption         =   "C&hange All"
      Height          =   375
      Left            =   4680
      TabIndex        =   5
      Top             =   1560
      Width           =   1215
   End
   Begin VB.CommandButton changeBtn 
      Caption         =   "&Change"
      Height          =   375
      Left            =   4680
      TabIndex        =   4
      Top             =   1080
      Width           =   1215
   End
   Begin VB.CommandButton ignoreAllBtn 
      Caption         =   "I&gnore All"
      Height          =   375
      Left            =   4680
      TabIndex        =   3
      Top             =   600
      Width           =   1215
   End
   Begin VB.CommandButton ignoreBtn 
      Caption         =   "&Ignore"
      Height          =   375
      Left            =   4680
      TabIndex        =   2
      Top             =   120
      Width           =   1215
   End
   Begin VB.TextBox problemText 
      Height          =   285
      Left            =   2160
      Locked          =   -1  'True
      TabIndex        =   1
      Top             =   120
      Width           =   2415
   End
   Begin VB.Label Label2 
      Alignment       =   1  'Right Justify
      Caption         =   "Suggestions:"
      Height          =   285
      Left            =   120
      TabIndex        =   10
      Top             =   840
      Width           =   1935
   End
   Begin VB.Label Label1 
      Alignment       =   1  'Right Justify
      Caption         =   "Change To:"
      Height          =   285
      Left            =   120
      TabIndex        =   8
      Top             =   480
      Width           =   1935
   End
   Begin VB.Label problemLbl 
      Alignment       =   1  'Right Justify
      Caption         =   "Not in dictionary:"
      Height          =   285
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   1935
   End
End
Attribute VB_Name = "SpellingDialogForm"
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

' Text box to check
Private checkTextBox As TextBox

' Contents of the text box
Private textBoxImage As String

' Cursor used to step through words in the text
Private cursor As Long

' Suggestion depth -- increased each time Suggest button is pressed.
Private suggestionDepth As Integer

' Start:
' Start checking the contents of a text box using the custom dialog box.
' The following protocol should be used to check spelling:
' 1) Load this form
' 2) Call the Start function.
' 3) If the Start function returns True, Show this form (vbModal)
' 4) Unload this form.
' theTextBox: The text box to be spelling-checked.
' Return: True if the custom spelling dialog should be displayed (by calling
' the Show method); False if checking is complete (the text contained no
' errors).
Public Function Start(theTextBox As TextBox) As Boolean
    Dim result As Integer
    Dim textLen As Long
    Dim textSz As Long
    Dim growth As Long

    Set checkTextBox = theTextBox

    ' Get the contents of the text box into a string.
    textBoxImage = checkTextBox.text

    ' textLen is the actual number of characters in the string.
    textLen = Len(textBoxImage)

    ' Add some extra space to allow room for growth.
    growth = textLen / 5
    If (growth < 100) Then
        growth = 100
    End If
    textBoxImage = textBoxImage + String$(growth, " ")

    ' textSz is the total capacity of the string.
    textSz = Len(textBoxImage)
    
    ' Start checking.
    cursor = 0
    Start = runChecker
End Function

' Fill the suggestions list with suggestions for the word in the
' problem field.
Private Sub fillSuggestionsList()
    Dim suggestions(16) As String
    Dim scores(16) As Integer
    Dim i As Integer

    Call SSCEVB_Suggest(SSCEVB_GetSid, problemText.text, suggestionDepth, _
      suggestions, scores, 16)
    Call suggestionsList.Clear
    For i = 0 To UBound(suggestions)
        If (suggestions(i) <> "") Then
            suggestionsList.AddItem (suggestions(i))
        End If
    Next

    ' Select the first suggestion and copy it to the Change To field.
    If (suggestionsList.ListCount > 0) Then
        suggestionsList.ListIndex = 0
        changeToText.text = suggestions(0)
    End If
End Sub
' Run the spelling checker and display the next misspelled word.
' Return: True if checking should continue; False if all text has been checked.
Private Function runChecker() As Boolean
    Dim word As String
    Dim otherWord As String
    Dim result As Integer

    runChecker = True
    
    ' Process auto-corrections
    Do
        result = SSCEVB_CheckString(SSCEVB_GetSid, textBoxImage, cursor, _
          word, otherWord)
        If (result = SSCE_AUTO_CHANGE_WORD_RSLT) Then
            ' Replace the word in the text block
            If (SSCEVB_ReplaceStringWord(SSCEVB_GetSid, textBoxImage, cursor, _
              otherWord) >= 0) Then
                ' Replace the word in the text box.
                checkTextBox.SelStart = cursor
                checkTextBox.SelLength = Len(word)
                checkTextBox.SelText = otherWord
            End If

            ' Skip over the replaced word to avoid problems caused by
            ' recursive replacements
            cursor = cursor + Len(otherWord)
        End If
    Loop While (result = SSCE_AUTO_CHANGE_WORD_RSLT)
    
    If (result = SSCE_END_OF_BLOCK_RSLT) Then
        ' End of text reached.
        Call cancelBtn_Click
        runChecker = False
    Else
        Dim problem As String

        ' A problem was detected.
        If (result = (SSCE_MISSPELLED_WORD_RSLT Or SSCE_UNCAPPED_WORD_RSLT)) Then
            problem = "Capitalization:"
        ElseIf ((result And SSCE_MISSPELLED_WORD_RSLT) <> 0) Then
            problem = "Not in dictionary:"
        ElseIf (result = SSCE_CONDITIONALLY_CHANGE_WORD_RSLT) Then
            problem = "Consider changing:"
        ElseIf (result = SSCE_DOUBLED_WORD_RSLT) Then
            problem = "Doubled word:"
        End If
        problemLbl.Caption = problem
        problemText.text = word

        If ((result And SSCE_MISSPELLED_WORD_RSLT) <> 0) Then
            ' Fill the suggestions list with suggestions.
            suggestionDepth = SSCEVB_GetMinSuggestDepth
            Call fillSuggestionsList
        ElseIf (result = SSCE_CONDITIONALLY_CHANGE_WORD_RSLT) Then
            ' Add the replacement word to the suggestions list.
            suggestionsList.Clear
            suggestionsList.AddItem (otherWord)
            suggestionsList.ListIndex = 0
        ElseIf (result = SSCE_DOUBLED_WORD_RSLT) Then
            ' Clear the suggestions list.
            suggestionsList.Clear
            changeToText.text = ""
        End If
        
        ' Highlight the problem word in the text box.
        checkTextBox.SelStart = cursor
        checkTextBox.SelLength = Len(word)
    End If
End Function

Private Sub addBtn_Click()
    Dim userDictFile As String

    ' Add the current word to the selected user dictionary.
    ' A different (slightly more complicated method) would involve
    ' displaying a dropdown-list of user dictionary files (call
    ' SSCEVB_GetUserLexFiles) and letting the user pick the user
    ' dictionary file to add the word to.
    Call SSCEVB_GetSelUserLexFile(userDictFile)
    If (userDictFile <> "") Then
        Dim lexId As Integer
        
        lexId = SSCEVB_GetLexId(userDictFile)
        If (lexId >= 0) Then
            Call SSCEVB_AddToLex(SSCEVB_GetSid, lexId, problemText.text, _
              SSCE_IGNORE_ACTION, "")
        End If
    End If
    
    ' Keep checking. The word will be automatically skipped.
    Call runChecker
End Sub

Private Sub cancelBtn_Click()
    If (Me.Visible) Then
        Me.Hide
    End If
End Sub

Private Sub changeAllBtn_Click()
    Dim lexId As Integer

    If (changeToText.text <> "") Then
        ' Add the word and replacement to the temporary dictionary
        lexId = SSCEVB_GetLexId("")
        If (lexId >= 0) Then
            Call SSCEVB_AddToLex(SSCEVB_GetSid, lexId, problemText.text, _
              SSCE_AUTO_CHANGE_PRESERVE_CASE_ACTION, changeToText.text)
        End If
    End If

    ' Keep checking. This and all further occurrences of the word will
    ' be automatically replaced.
    Call runChecker
End Sub

Private Sub changeBtn_Click()
    If (changeToText.text <> "") Then
        ' Replace the current word with the word in the Change To field.
        If (SSCEVB_ReplaceStringWord(SSCEVB_GetSid, textBoxImage, cursor, _
          changeToText.text) >= 0) Then
            ' Change the word in the text box.
            checkTextBox.SelStart = cursor
            checkTextBox.SelLength = Len(problemText.text)
            checkTextBox.SelText = changeToText.text
        End If
    Else
        Dim delText As String
        
        ' Delete the current word and any leading whitespace.
        cursor = SSCEVB_DelStringWord(SSCEVB_GetSid, textBoxImage, cursor, delText)
        If (cursor >= 0) Then
            ' Delete the word in the text box.
            checkTextBox.SelStart = cursor
            checkTextBox.SelLength = Len(delText)
            checkTextBox.SelText = ""
        End If
    End If
    
    ' Keep checking.
    Call runChecker
End Sub

Private Sub ignoreAllBtn_Click()
    Dim lexId As Integer
    
    ' Add the word to the temporary dictionary
    lexId = SSCEVB_GetLexId(0&)
    If (lexId >= 0) Then
        Call SSCEVB_AddToLex(SSCEVB_GetSid, lexId, problemText.text, _
          SSCE_IGNORE_ACTION, "")
    End If
    
    ' Keep checking. This and all further occurrences of the word will
    ' be skipped.
    Call runChecker
End Sub

Private Sub ignoreBtn_Click()
    Dim word As String
    
    ' Advance to the next word.
    cursor = SSCEVB_GetStringWord(SSCEVB_GetSid, textBoxImage, cursor, word)
    cursor = cursor + Len(word)
    Call runChecker
End Sub

Private Sub suggestBtn_Click()
    ' Locate better suggestions by increasing the suggestion depth.
    suggestionDepth = suggestionDepth + 10
    Call fillSuggestionsList
End Sub

Private Sub suggestionsList_Click()
    ' Copy the selected suggestion to the Change To field.
    changeToText.text = suggestionsList.List(suggestionsList.ListIndex)
End Sub
