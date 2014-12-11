Public Class CheckTextInCodeForm
    ' Sentry Spelling Checker Engine
    ' VB.NET Example
    ' CheckTextInCodeForm: Demonstrates checking text with no user interaction
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
    Friend WithEvents Button3 As System.Windows.Forms.Button
    Friend WithEvents TextBox1 As System.Windows.Forms.TextBox
    Friend WithEvents Button1 As System.Windows.Forms.Button
    Friend WithEvents Label4 As System.Windows.Forms.Label
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents TextBox2 As System.Windows.Forms.TextBox
    Friend WithEvents Label3 As System.Windows.Forms.Label
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.Button3 = New System.Windows.Forms.Button()
        Me.TextBox1 = New System.Windows.Forms.TextBox()
        Me.Button1 = New System.Windows.Forms.Button()
        Me.Label4 = New System.Windows.Forms.Label()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.TextBox2 = New System.Windows.Forms.TextBox()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.SuspendLayout()
        '
        'Button3
        '
        Me.Button3.BackColor = System.Drawing.SystemColors.Control
        Me.Button3.Location = New System.Drawing.Point(195, 352)
        Me.Button3.Name = "Button3"
        Me.Button3.Size = New System.Drawing.Size(120, 23)
        Me.Button3.TabIndex = 29
        Me.Button3.Text = "Check Spelling"
        '
        'TextBox1
        '
        Me.TextBox1.Location = New System.Drawing.Point(16, 152)
        Me.TextBox1.Multiline = True
        Me.TextBox1.Name = "TextBox1"
        Me.TextBox1.ScrollBars = System.Windows.Forms.ScrollBars.Vertical
        Me.TextBox1.Size = New System.Drawing.Size(632, 96)
        Me.TextBox1.TabIndex = 28
        Me.TextBox1.Text = "So she was considerirng in her own mind (as well as she could, for the" & Microsoft.VisualBasic.ChrW(13) & Microsoft.VisualBasic.ChrW(10) & "hot day m" & _
        "ade her feel very sleeepy and stupid), whether the pleasue" & Microsoft.VisualBasic.ChrW(13) & Microsoft.VisualBasic.ChrW(10) & "of making a daisy-ch" & _
        "ain would be worth the trolble of getting up and" & Microsoft.VisualBasic.ChrW(13) & Microsoft.VisualBasic.ChrW(10) & "picking the daysies, when sudd" & _
        "enly a White Rabbit with pink eyes ran" & Microsoft.VisualBasic.ChrW(13) & Microsoft.VisualBasic.ChrW(10) & "close by her."
        '
        'Button1
        '
        Me.Button1.BackColor = System.Drawing.SystemColors.Control
        Me.Button1.DialogResult = System.Windows.Forms.DialogResult.OK
        Me.Button1.Location = New System.Drawing.Point(395, 352)
        Me.Button1.Name = "Button1"
        Me.Button1.TabIndex = 27
        Me.Button1.Text = "Close"
        '
        'Label4
        '
        Me.Label4.Location = New System.Drawing.Point(12, 96)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(640, 56)
        Me.Label4.TabIndex = 26
        Me.Label4.Text = "Click the Check Spelling button to check the spelling of the text entered in the " & _
        "text box. You can also edit the text box to add your own text. Misspelled words " & _
        "and suggested replacements will be listed in the ""Misspelled words"" area."
        '
        'Label2
        '
        Me.Label2.BackColor = System.Drawing.Color.FromArgb(CType(255, Byte), CType(224, Byte), CType(192, Byte))
        Me.Label2.Location = New System.Drawing.Point(48, 40)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(568, 48)
        Me.Label2.TabIndex = 25
        Me.Label2.Text = "In some applications it's necessary to check spelling and look up suggestions wit" & _
        "hout interacting with the user. Sentry's Basic spell-checking API makes this eas" & _
        "y."
        '
        'Label1
        '
        Me.Label1.Font = New System.Drawing.Font("Arial", 12.0!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label1.Location = New System.Drawing.Point(8, 8)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(640, 32)
        Me.Label1.TabIndex = 24
        Me.Label1.Text = "Check spelling of strings in code without user interaction"
        '
        'TextBox2
        '
        Me.TextBox2.Location = New System.Drawing.Point(16, 272)
        Me.TextBox2.Multiline = True
        Me.TextBox2.Name = "TextBox2"
        Me.TextBox2.ScrollBars = System.Windows.Forms.ScrollBars.Vertical
        Me.TextBox2.Size = New System.Drawing.Size(632, 72)
        Me.TextBox2.TabIndex = 30
        Me.TextBox2.Text = ""
        '
        'Label3
        '
        Me.Label3.Location = New System.Drawing.Point(16, 256)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(616, 16)
        Me.Label3.TabIndex = 31
        Me.Label3.Text = "Misspelled words:"
        '
        'CheckTextInCodeForm
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 15)
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.ClientSize = New System.Drawing.Size(664, 392)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.Label3, Me.TextBox2, Me.Button3, Me.TextBox1, Me.Button1, Me.Label4, Me.Label2, Me.Label1})
        Me.Name = "CheckTextInCodeForm"
        Me.Text = "CheckTextInCodeForm"
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub Button3_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button3.Click
        Dim text As String
        Dim textLen As Integer
        Dim word As String
        Dim otherWord As String
        Dim suggestions(16) As String
        Dim scores(16) As Short
        Dim s As String
        Dim i As Integer
        Dim result As Integer
        Dim cursor As Integer = 0

        ' Get the text from Text1.
        text = TextBox1.Text

        ' textLen is the number of characters in the string.
        textLen = Len(text)

        ' Keep checking until all the text has been checked.
        Do
            result = SSCEVB_CheckString(SSCEVB_GetSid, text, cursor, word, otherWord)
            If (result < 0) Then
                MsgBox("SSCEVB_CheckString returned " & result)
                Exit Sub
            End If

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
                TextBox2.SelectedText = s & vbCrLf & vbCrLf
            End If

            ' Advance to the next word. This is necessary or SSCEVB_CheckString
            ' will keep reporting the same word.
            cursor = cursor + Len(word)
        Loop Until (result = SSCE_END_OF_BLOCK_RSLT)

    End Sub
End Class
