Public Class CheckStringForm
    ' Sentry Spelling Checker Engine
    ' VB.NET Example
    ' CheckStringForm: Demonstrates interactively checking the spelling of text in a string.
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
    Friend WithEvents Button1 As System.Windows.Forms.Button
    Friend WithEvents Label4 As System.Windows.Forms.Label
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents TextBox1 As System.Windows.Forms.TextBox
    Friend WithEvents Button3 As System.Windows.Forms.Button
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.Button1 = New System.Windows.Forms.Button()
        Me.Label4 = New System.Windows.Forms.Label()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.TextBox1 = New System.Windows.Forms.TextBox()
        Me.Button3 = New System.Windows.Forms.Button()
        Me.SuspendLayout()
        '
        'Button1
        '
        Me.Button1.BackColor = System.Drawing.SystemColors.Control
        Me.Button1.DialogResult = System.Windows.Forms.DialogResult.OK
        Me.Button1.Location = New System.Drawing.Point(376, 320)
        Me.Button1.Name = "Button1"
        Me.Button1.TabIndex = 20
        Me.Button1.Text = "Close"
        '
        'Label4
        '
        Me.Label4.Location = New System.Drawing.Point(16, 96)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(640, 40)
        Me.Label4.TabIndex = 17
        Me.Label4.Text = "Click the Check Spelling button to check the text entered below. You can also edi" & _
        "t the text box to add your own text."
        '
        'Label2
        '
        Me.Label2.BackColor = System.Drawing.Color.FromArgb(CType(255, Byte), CType(224, Byte), CType(192, Byte))
        Me.Label2.Location = New System.Drawing.Point(56, 40)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(568, 48)
        Me.Label2.TabIndex = 16
        Me.Label2.Text = "Sentry can interactively check the spelling of words in a String. The contents of" & _
        " the string can be displayed in a context area in the spelling dialog box."
        '
        'Label1
        '
        Me.Label1.Font = New System.Drawing.Font("Arial", 12.0!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label1.Location = New System.Drawing.Point(8, 8)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(640, 32)
        Me.Label1.TabIndex = 15
        Me.Label1.Text = "Interactively check spelling of strings"
        '
        'TextBox1
        '
        Me.TextBox1.Location = New System.Drawing.Point(24, 144)
        Me.TextBox1.Multiline = True
        Me.TextBox1.Name = "TextBox1"
        Me.TextBox1.ScrollBars = System.Windows.Forms.ScrollBars.Vertical
        Me.TextBox1.Size = New System.Drawing.Size(632, 160)
        Me.TextBox1.TabIndex = 21
        Me.TextBox1.Text = "So she was considerirng in her own mind (as well as she could, for the" & Microsoft.VisualBasic.ChrW(13) & Microsoft.VisualBasic.ChrW(10) & "hot day m" & _
        "ade her feel very sleeepy and stupid), whether the pleasue" & Microsoft.VisualBasic.ChrW(13) & Microsoft.VisualBasic.ChrW(10) & "of making a daisy-ch" & _
        "ain would be worth the trolble of getting up and" & Microsoft.VisualBasic.ChrW(13) & Microsoft.VisualBasic.ChrW(10) & "picking the daysies, when sudd" & _
        "enly a White Rabbit with pink eyes ran" & Microsoft.VisualBasic.ChrW(13) & Microsoft.VisualBasic.ChrW(10) & "close by her."
        '
        'Button3
        '
        Me.Button3.BackColor = System.Drawing.SystemColors.Control
        Me.Button3.Location = New System.Drawing.Point(176, 320)
        Me.Button3.Name = "Button3"
        Me.Button3.Size = New System.Drawing.Size(120, 23)
        Me.Button3.TabIndex = 23
        Me.Button3.Text = "Check Spelling"
        '
        'CheckStringForm
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 15)
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.ClientSize = New System.Drawing.Size(688, 360)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.Button3, Me.TextBox1, Me.Button1, Me.Label4, Me.Label2, Me.Label1})
        Me.Name = "CheckStringForm"
        Me.Text = "CheckStringForm"
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub Button3_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button3.Click
        Dim result As Integer
        Dim text As String
        Dim textLen As Long
        Dim textSz As Long
        Dim growth As Long

        ' Get the contents of the text box into a string.
        text = TextBox1.Text

        ' textLen is the actual number of characters in the string.
        textLen = Len(text)

        ' Add some extra space to allow room for growth.
        growth = textLen / 5
        If (growth < 100) Then
            growth = 100
        End If
        text = text + New String(CChar(" "), growth)

        ' textSz is the total capacity of the string.
        textSz = Len(text)

        ' Check the spelling.
        result = SSCEVB_CheckBlockDlg(Me.Handle, text, textLen, textSz, True)

        If (result >= 0) Then
            ' The return value from SSCEVB_CheckBlockDlg is the number of
            ' characters now in the string (following corrections made by
            ' the user).
            text = text.Substring(0, result)

            ' Put the corrected string back into the text box.
            TextBox1.Text = text
        End If

    End Sub
End Class
