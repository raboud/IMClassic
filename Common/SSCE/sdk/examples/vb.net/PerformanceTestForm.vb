Public Class PerformanceTestForm
    ' Sentry Spelling Checker Engine
    ' VB.NET Example
    ' PerformanceTestForm: Measure the performance of the Sentry spelling engine.
    '
    ' Copyright (c) 2002 Wintertree Software Inc.
    ' www.wintertree-software.com
    '
    ' Use, duplication, and disclosure of this file is governed
    ' by a license agreement between Wintertree Software Inc. and
    ' the licensee.
    '
    ' $Id$

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
    Friend WithEvents ResultsLbl As System.Windows.Forms.Label
    Friend WithEvents Button3 As System.Windows.Forms.Button
    Friend WithEvents Button1 As System.Windows.Forms.Button
    Friend WithEvents Label4 As System.Windows.Forms.Label
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents RichTextBox1 As System.Windows.Forms.RichTextBox
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.ResultsLbl = New System.Windows.Forms.Label()
        Me.Button3 = New System.Windows.Forms.Button()
        Me.Button1 = New System.Windows.Forms.Button()
        Me.Label4 = New System.Windows.Forms.Label()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.RichTextBox1 = New System.Windows.Forms.RichTextBox()
        Me.SuspendLayout()
        '
        'ResultsLbl
        '
        Me.ResultsLbl.Location = New System.Drawing.Point(176, 263)
        Me.ResultsLbl.Name = "ResultsLbl"
        Me.ResultsLbl.Size = New System.Drawing.Size(480, 16)
        Me.ResultsLbl.TabIndex = 39
        '
        'Button3
        '
        Me.Button3.BackColor = System.Drawing.SystemColors.Control
        Me.Button3.Location = New System.Drawing.Point(40, 256)
        Me.Button3.Name = "Button3"
        Me.Button3.Size = New System.Drawing.Size(120, 23)
        Me.Button3.TabIndex = 37
        Me.Button3.Text = "Start"
        '
        'Button1
        '
        Me.Button1.BackColor = System.Drawing.SystemColors.Control
        Me.Button1.DialogResult = System.Windows.Forms.DialogResult.OK
        Me.Button1.Location = New System.Drawing.Point(295, 296)
        Me.Button1.Name = "Button1"
        Me.Button1.TabIndex = 35
        Me.Button1.Text = "Close"
        '
        'Label4
        '
        Me.Label4.Location = New System.Drawing.Point(12, 96)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(640, 56)
        Me.Label4.TabIndex = 34
        Me.Label4.Text = "Click the Start button to check the spelling of words in the rich-text box. You c" & _
        "an also edit the rich-text box to add your own text. Sentry will check the spell" & _
        "ing of each word and measure the time it takes. When all words have been checked" & _
        ", some performance measurements will be displayed."
        '
        'Label2
        '
        Me.Label2.BackColor = System.Drawing.Color.FromArgb(CType(255, Byte), CType(224, Byte), CType(192, Byte))
        Me.Label2.Location = New System.Drawing.Point(48, 40)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(568, 48)
        Me.Label2.TabIndex = 33
        Me.Label2.Text = "One feature you and your end-users will really appreciate is Sentry's amazing spe" & _
        "ed. Sentry can check over 10,000 words per second on modest systems. Try the per" & _
        "formance test presented here to see how well Sentry performs on your system!"
        '
        'Label1
        '
        Me.Label1.Font = New System.Drawing.Font("Arial", 12.0!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label1.Location = New System.Drawing.Point(8, 8)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(640, 32)
        Me.Label1.TabIndex = 32
        Me.Label1.Text = "How fast is Sentry?"
        '
        'RichTextBox1
        '
        Me.RichTextBox1.Location = New System.Drawing.Point(16, 152)
        Me.RichTextBox1.Name = "RichTextBox1"
        Me.RichTextBox1.Size = New System.Drawing.Size(632, 88)
        Me.RichTextBox1.TabIndex = 40
        Me.RichTextBox1.Text = ""
        '
        'PerformanceTestForm
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 15)
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.ClientSize = New System.Drawing.Size(664, 336)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.RichTextBox1, Me.ResultsLbl, Me.Button3, Me.Button1, Me.Label4, Me.Label2, Me.Label1})
        Me.Name = "PerformanceTestForm"
        Me.Text = "PerformanceTestForm"
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub PerformanceTestForm_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        Try
            RichTextBox1.LoadFile("..\..\alice.rtf")
        Catch iox As System.IO.IOException
            RichTextBox1.Text = ""
        Finally
            ' Do nothing
        End Try
    End Sub

    Private Sub Button3_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button3.Click
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

        ResultsLbl.Text = ""

        ' Get the text from RichTextBox1.
        text = RichTextBox1.Text

        ' textLen is the number of characters in the string.
        textLen = Len(text)

        ' Open a block to check the text. Checking text using CheckBlock
        ' is faster in VB than CheckString, probably because VB makes a
        ' new copy of the string on each call.
        blkId = SSCEVB_OpenBlock(SSCE_GetSid, text, textLen, textLen, True)
        If (blkId < 0) Then
            MsgBox("SSCEVB_OpenBlock returned " & Str(blkId))
            Exit Sub
        End If

        ' Keep checking until all the text has been checked.
        numMisspelledWords = 0
        totalTime = 0
        Do
            startTime = Microsoft.VisualBasic.Timer()
            result = SSCEVB_CheckBlock(SSCEVB_GetSid, blkId, word, otherWord)
            endTime = Microsoft.VisualBasic.Timer()
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
        ResultsLbl.Text = wordCount & " words. " & _
          numMisspelledWords & " misspelled words. " & _
          Math.Round(totalTime, 2) & " seconds. " & _
          Math.Round(wordCount / totalTime) & " words per second."

        Call SSCEVB_CloseBlock(SSCEVB_GetSid, blkId)

    End Sub
End Class
