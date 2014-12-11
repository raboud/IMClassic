Public Class SpellingDialogForm
    ' Sentry Spelling Checker Engine
    ' SpellingDialogForm: Demonstrates custom spelling dialog box
    '
    ' Copyright (c) 2002 Wintertree Software Inc.
    ' www.wintertree-software.com
    '
    ' $Id: SpellingDialogForm.vb,v 5.14.12 2002/06/26 17:33:00 wsi Exp wsi $

    Inherits System.Windows.Forms.Form

#Region " Windows Form Designer generated code "

    Public Sub New()
        MyBase.New()

        'This call is required by the Windows Form Designer.
        InitializeComponent()

        'Add any initialization after the InitializeComponent() call

    End Sub

    'Form overrides dispose to clean up the component list.
    Protected Overloads Overrides Sub Dispose(ByVal disposing As Boolean)
        If disposing Then
            If Not (components Is Nothing) Then
                components.Dispose()
            End If
        End If
        MyBase.Dispose(disposing)
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    Friend WithEvents ProblemLbl As System.Windows.Forms.Label
    Friend WithEvents ProblemText As System.Windows.Forms.TextBox
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents ChangeToText As System.Windows.Forms.TextBox
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents IgnoreBtn As System.Windows.Forms.Button
    Friend WithEvents IgnoreAllBtn As System.Windows.Forms.Button
    Friend WithEvents ChangeBtn As System.Windows.Forms.Button
    Friend WithEvents ChangeAllBtn As System.Windows.Forms.Button
    Friend WithEvents SuggestBtn As System.Windows.Forms.Button
    Friend WithEvents AddBtn As System.Windows.Forms.Button
    Friend WithEvents CloseBtn As System.Windows.Forms.Button
    Friend WithEvents SuggestionsList As System.Windows.Forms.ListBox
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.ProblemLbl = New System.Windows.Forms.Label()
        Me.ProblemText = New System.Windows.Forms.TextBox()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.ChangeToText = New System.Windows.Forms.TextBox()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.SuggestionsList = New System.Windows.Forms.ListBox()
        Me.IgnoreBtn = New System.Windows.Forms.Button()
        Me.IgnoreAllBtn = New System.Windows.Forms.Button()
        Me.ChangeBtn = New System.Windows.Forms.Button()
        Me.ChangeAllBtn = New System.Windows.Forms.Button()
        Me.SuggestBtn = New System.Windows.Forms.Button()
        Me.AddBtn = New System.Windows.Forms.Button()
        Me.CloseBtn = New System.Windows.Forms.Button()
        Me.SuspendLayout()
        '
        'ProblemLbl
        '
        Me.ProblemLbl.Location = New System.Drawing.Point(8, 8)
        Me.ProblemLbl.Name = "ProblemLbl"
        Me.ProblemLbl.Size = New System.Drawing.Size(144, 16)
        Me.ProblemLbl.TabIndex = 0
        Me.ProblemLbl.Text = "Not in dictionary:"
        Me.ProblemLbl.TextAlign = System.Drawing.ContentAlignment.MiddleRight
        '
        'ProblemText
        '
        Me.ProblemText.Location = New System.Drawing.Point(160, 8)
        Me.ProblemText.Name = "ProblemText"
        Me.ProblemText.Size = New System.Drawing.Size(192, 22)
        Me.ProblemText.TabIndex = 1
        Me.ProblemText.Text = ""
        '
        'Label1
        '
        Me.Label1.Location = New System.Drawing.Point(8, 32)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(144, 16)
        Me.Label1.TabIndex = 2
        Me.Label1.Text = "Change &to:"
        Me.Label1.TextAlign = System.Drawing.ContentAlignment.MiddleRight
        '
        'ChangeToText
        '
        Me.ChangeToText.Location = New System.Drawing.Point(160, 32)
        Me.ChangeToText.Name = "ChangeToText"
        Me.ChangeToText.Size = New System.Drawing.Size(192, 22)
        Me.ChangeToText.TabIndex = 3
        Me.ChangeToText.Text = ""
        '
        'Label2
        '
        Me.Label2.Location = New System.Drawing.Point(8, 56)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(144, 16)
        Me.Label2.TabIndex = 4
        Me.Label2.Text = "&Suggestions:"
        Me.Label2.TextAlign = System.Drawing.ContentAlignment.MiddleRight
        '
        'SuggestionsList
        '
        Me.SuggestionsList.ItemHeight = 16
        Me.SuggestionsList.Location = New System.Drawing.Point(160, 56)
        Me.SuggestionsList.Name = "SuggestionsList"
        Me.SuggestionsList.Size = New System.Drawing.Size(192, 132)
        Me.SuggestionsList.TabIndex = 5
        '
        'IgnoreBtn
        '
        Me.IgnoreBtn.Location = New System.Drawing.Point(360, 8)
        Me.IgnoreBtn.Name = "IgnoreBtn"
        Me.IgnoreBtn.Size = New System.Drawing.Size(88, 23)
        Me.IgnoreBtn.TabIndex = 6
        Me.IgnoreBtn.Text = "&Ignore"
        '
        'IgnoreAllBtn
        '
        Me.IgnoreAllBtn.Location = New System.Drawing.Point(360, 40)
        Me.IgnoreAllBtn.Name = "IgnoreAllBtn"
        Me.IgnoreAllBtn.Size = New System.Drawing.Size(88, 23)
        Me.IgnoreAllBtn.TabIndex = 7
        Me.IgnoreAllBtn.Text = "I&gnore All"
        '
        'ChangeBtn
        '
        Me.ChangeBtn.Location = New System.Drawing.Point(360, 72)
        Me.ChangeBtn.Name = "ChangeBtn"
        Me.ChangeBtn.Size = New System.Drawing.Size(88, 23)
        Me.ChangeBtn.TabIndex = 8
        Me.ChangeBtn.Text = "&Change"
        '
        'ChangeAllBtn
        '
        Me.ChangeAllBtn.Location = New System.Drawing.Point(360, 104)
        Me.ChangeAllBtn.Name = "ChangeAllBtn"
        Me.ChangeAllBtn.Size = New System.Drawing.Size(88, 23)
        Me.ChangeAllBtn.TabIndex = 9
        Me.ChangeAllBtn.Text = "C&hange All"
        '
        'SuggestBtn
        '
        Me.SuggestBtn.Location = New System.Drawing.Point(360, 136)
        Me.SuggestBtn.Name = "SuggestBtn"
        Me.SuggestBtn.Size = New System.Drawing.Size(88, 23)
        Me.SuggestBtn.TabIndex = 10
        Me.SuggestBtn.Text = "S&uggest"
        '
        'AddBtn
        '
        Me.AddBtn.Location = New System.Drawing.Point(360, 168)
        Me.AddBtn.Name = "AddBtn"
        Me.AddBtn.Size = New System.Drawing.Size(88, 23)
        Me.AddBtn.TabIndex = 11
        Me.AddBtn.Text = "&Add"
        '
        'CloseBtn
        '
        Me.CloseBtn.DialogResult = System.Windows.Forms.DialogResult.Cancel
        Me.CloseBtn.Location = New System.Drawing.Point(8, 168)
        Me.CloseBtn.Name = "CloseBtn"
        Me.CloseBtn.Size = New System.Drawing.Size(88, 23)
        Me.CloseBtn.TabIndex = 12
        Me.CloseBtn.Text = "C&lose"
        '
        'SpellingDialogForm
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 15)
        Me.CancelButton = Me.CloseBtn
        Me.ClientSize = New System.Drawing.Size(456, 200)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.CloseBtn, Me.AddBtn, Me.SuggestBtn, Me.ChangeAllBtn, Me.ChangeBtn, Me.IgnoreAllBtn, Me.IgnoreBtn, Me.SuggestionsList, Me.Label2, Me.ChangeToText, Me.Label1, Me.ProblemText, Me.ProblemLbl})
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.Name = "SpellingDialogForm"
        Me.Text = "SpellingDialogForm"
        Me.ResumeLayout(False)

    End Sub

#End Region

    ' Text box to check
    Private checkTextBox As TextBox

    ' Contents of the text box
    Private textBoxImage As String

    ' Cursor used to step through words in the text
    Private theCursor As Integer

    ' Suggestion depth -- increased each time Suggest button is pressed.
    Private suggestionDepth As Integer

    ' Start checking the contents of a text box using the custom dialog box.
    ' The following protocol should be used to check spelling:
    ' 1) Construct an instance this form
    ' 2) Call the Start function.
    ' 3) If the Start function returns True, Show this form modally (ShowDialog)
    ' theTextBox: The text box to be spelling-checked.
    ' Return: True if the custom spelling dialog should be displayed (by calling
    ' the ShowDialog method); False if checking is complete (the text contained no
    ' errors).
    Public Function Start(ByVal theTextBox As TextBox) As Boolean
        Dim result As Integer
        Dim textLen As Long
        Dim textSz As Long
        Dim growth As Long

        checkTextBox = theTextBox

        ' Get the contents of the text box into a string.
        textBoxImage = checkTextBox.text

        ' textLen is the actual number of characters in the string.
        textLen = Len(textBoxImage)

        ' Add some extra space to allow room for growth.
        growth = textLen / 5
        If (growth < 100) Then
            growth = 100
        End If
        textBoxImage = textBoxImage + New String(CChar(" "), growth)

        ' textSz is the total capacity of the string.
        textSz = Len(textBoxImage)

        ' Start checking.
        theCursor = 0
        Start = runChecker
    End Function

    ' Fill the suggestions list with suggestions for the word in the
    ' problem field.
    Private Sub fillSuggestionsList()
        Dim suggestions(16) As String
        Dim scores(16) As Short
        Dim i As Integer

        Call SSCEVB_Suggest(SSCEVB_GetSid, problemText.text, suggestionDepth, _
          suggestions, scores, 16)
        Call SuggestionsList.Items.Clear()
        For i = 0 To UBound(suggestions)
            If (suggestions(i) <> "") Then
                SuggestionsList.Items.Add(suggestions(i))
            End If
        Next

        ' Select the first suggestion and copy it to the Change To field.
        If (SuggestionsList.Items.Count > 0) Then
            SuggestionsList.SelectedIndex = 0
            ChangeToText.Text = suggestions(0)
        End If
    End Sub

    Private Sub onClose()
        If (Me.Visible) Then
            Me.Hide()
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
            result = SSCEVB_CheckString(SSCEVB_GetSid, textBoxImage, theCursor, _
              word, otherWord)
            If (result = SSCE_AUTO_CHANGE_WORD_RSLT) Then
                ' Replace the word in the text block
                If (SSCEVB_ReplaceStringWord(SSCEVB_GetSid, textBoxImage, theCursor, _
                  otherWord) >= 0) Then
                    ' Replace the word in the text box.
                    checkTextBox.SelectionStart = theCursor
                    checkTextBox.SelectionLength = Len(word)
                    checkTextBox.SelectedText = otherWord
                End If

                ' Skip over the replaced word to avoid problems caused by
                ' recursive replacements
                theCursor = theCursor + Len(otherWord)
            End If
        Loop While (result = SSCE_AUTO_CHANGE_WORD_RSLT)

        If (result = SSCE_END_OF_BLOCK_RSLT) Then
            ' End of text reached.
            Call onClose()
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
            ProblemLbl.Text = problem
            ProblemText.Text = word

            If ((result And SSCE_MISSPELLED_WORD_RSLT) <> 0) Then
                ' Fill the suggestions list with suggestions.
                suggestionDepth = SSCEVB_GetMinSuggestDepth()
                Call fillSuggestionsList()
            ElseIf (result = SSCE_CONDITIONALLY_CHANGE_WORD_RSLT) Then
                ' Add the replacement word to the suggestions list.
                SuggestionsList.Items.Clear()
                SuggestionsList.Items.Add(otherWord)
                SuggestionsList.SelectedIndex = 0
            ElseIf (result = SSCE_DOUBLED_WORD_RSLT) Then
                ' Clear the suggestions list.
                SuggestionsList.Items.Clear()
                ChangeToText.Text = ""
            End If

            ' Highlight the problem word in the text box.
            checkTextBox.SelectionStart = theCursor
            checkTextBox.SelectionLength = Len(word)
            checkTextBox.ScrollToCaret()
        End If
    End Function

    Private Sub AddBtn_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles AddBtn.Click
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
                Call SSCEVB_AddToLex(SSCEVB_GetSid, lexId, ProblemText.Text, _
                  SSCE_IGNORE_ACTION, "")
            End If
        End If

        ' Keep checking. The word will be automatically skipped.
        Call runChecker()
    End Sub

    Private Sub CloseBtn_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles CloseBtn.Click
        Call onClose()
    End Sub

    Private Sub ChangeAllBtn_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ChangeAllBtn.Click
        Dim lexId As Integer

        If (ChangeToText.Text <> "") Then
            ' Add the word and replacement to the temporary dictionary
            lexId = SSCEVB_GetLexId("")
            If (lexId >= 0) Then
                Call SSCEVB_AddToLex(SSCEVB_GetSid, lexId, ProblemText.Text, _
                  SSCE_AUTO_CHANGE_PRESERVE_CASE_ACTION, ChangeToText.Text)
            End If
        End If

        ' Keep checking. This and all further occurrences of the word will
        ' be automatically replaced.
        Call runChecker()
    End Sub

    Private Sub ChangeBtn_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ChangeBtn.Click
        If (ChangeToText.Text <> "") Then
            ' Replace the current word with the word in the Change To field.
            If (SSCEVB_ReplaceStringWord(SSCEVB_GetSid, textBoxImage, theCursor, _
              ChangeToText.Text) >= 0) Then
                ' Change the word in the text box.
                checkTextBox.SelectionStart = theCursor
                checkTextBox.SelectionLength = Len(ProblemText.Text)
                checkTextBox.SelectedText = ChangeToText.Text
            End If
        Else
            Dim delText As String

            ' Delete the current word and any leading whitespace.
            theCursor = SSCEVB_DelStringWord(SSCEVB_GetSid, textBoxImage, theCursor, delText)
            If (theCursor >= 0) Then
                ' Delete the word in the text box.
                checkTextBox.SelectionStart = theCursor
                checkTextBox.SelectionLength = Len(delText)
                checkTextBox.SelectedText = ""
            End If
        End If

        ' Keep checking.
        Call runChecker()
    End Sub

    Private Sub IgnoreAllBtn_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles IgnoreAllBtn.Click
        Dim lexId As Integer

        ' Add the word to the temporary dictionary
        lexId = SSCEVB_GetLexId(0&)
        If (lexId >= 0) Then
            Call SSCEVB_AddToLex(SSCEVB_GetSid, lexId, ProblemText.Text, _
              SSCE_IGNORE_ACTION, "")
        End If

        ' Keep checking. This and all further occurrences of the word will
        ' be skipped.
        Call runChecker()
    End Sub

    Private Sub IgnoreBtn_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles IgnoreBtn.Click
        Dim word As String

        ' Advance to the next word.
        theCursor = SSCEVB_GetStringWord(SSCEVB_GetSid, textBoxImage, theCursor, word)
        theCursor = theCursor + Len(word)
        Call runChecker()
    End Sub

    Private Sub SuggestBtn_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles SuggestBtn.Click
        ' Locate better suggestions by increasing the suggestion depth.
        suggestionDepth = suggestionDepth + 10
        Call fillSuggestionsList()
    End Sub

    Private Sub SuggestionsList_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles SuggestionsList.SelectedIndexChanged
        ' Copy the selected suggestion to the Change To field.
        ChangeToText.Text = SuggestionsList.Items(SuggestionsList.SelectedIndex)
    End Sub
End Class
