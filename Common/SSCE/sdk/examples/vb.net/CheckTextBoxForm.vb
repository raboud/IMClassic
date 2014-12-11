Public Class CheckTextBoxForm
    ' Sentry Spelling Checker Engine
    ' VB.NET Example
    ' CheckTextBoxForm: Demonstrates checking text and rich-text boxes interactively
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
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents Label4 As System.Windows.Forms.Label
    Friend WithEvents TextBox1 As System.Windows.Forms.TextBox
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents Label5 As System.Windows.Forms.Label
    Friend WithEvents RichTextBox1 As System.Windows.Forms.RichTextBox
    Friend WithEvents Button1 As System.Windows.Forms.Button
    Friend WithEvents Button2 As System.Windows.Forms.Button
    Friend WithEvents Button3 As System.Windows.Forms.Button
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Label4 = New System.Windows.Forms.Label()
        Me.TextBox1 = New System.Windows.Forms.TextBox()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.Label5 = New System.Windows.Forms.Label()
        Me.RichTextBox1 = New System.Windows.Forms.RichTextBox()
        Me.Button1 = New System.Windows.Forms.Button()
        Me.Button2 = New System.Windows.Forms.Button()
        Me.Button3 = New System.Windows.Forms.Button()
        Me.SuspendLayout()
        '
        'Label1
        '
        Me.Label1.Font = New System.Drawing.Font("Arial", 12.0!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label1.Location = New System.Drawing.Point(8, 0)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(640, 32)
        Me.Label1.TabIndex = 0
        Me.Label1.Text = "Check spelling of text boxes and rich-text boxes interactively"
        '
        'Label2
        '
        Me.Label2.BackColor = System.Drawing.Color.FromArgb(CType(255, Byte), CType(224, Byte), CType(192, Byte))
        Me.Label2.Location = New System.Drawing.Point(44, 40)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(568, 48)
        Me.Label2.TabIndex = 1
        Me.Label2.Text = "You won't believe how easy it is to use Sentry to check the spelling of text ente" & _
        "red in text boxes on a form! One statement is all it takes. Make sure to set the" & _
        " text box's HideSelection property to False."
        '
        'Label4
        '
        Me.Label4.Location = New System.Drawing.Point(8, 96)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(640, 40)
        Me.Label4.TabIndex = 10
        Me.Label4.Text = "Click the Check Spelling button next to each text box to check its spelling. You " & _
        "can check the provided text or enter your own text."
        '
        'TextBox1
        '
        Me.TextBox1.HideSelection = False
        Me.TextBox1.Location = New System.Drawing.Point(8, 160)
        Me.TextBox1.Multiline = True
        Me.TextBox1.Name = "TextBox1"
        Me.TextBox1.ScrollBars = System.Windows.Forms.ScrollBars.Vertical
        Me.TextBox1.Size = New System.Drawing.Size(520, 80)
        Me.TextBox1.TabIndex = 11
        Me.TextBox1.Text = "Alice was begining to get very tired of siting by her sister on the" & Microsoft.VisualBasic.ChrW(13) & Microsoft.VisualBasic.ChrW(10) & "bank, and of" & _
        " having nothing to do: once or twice she had peeped into the" & Microsoft.VisualBasic.ChrW(13) & Microsoft.VisualBasic.ChrW(10) & "book her sister wa" & _
        "s reading, but it had no pictures or conversatoins in" & Microsoft.VisualBasic.ChrW(13) & Microsoft.VisualBasic.ChrW(10) & "it, ""and what is the use " & _
        "of a book,"" thought Alice ""without pictures or" & Microsoft.VisualBasic.ChrW(13) & Microsoft.VisualBasic.ChrW(10) & "conversation?"" " & Microsoft.VisualBasic.ChrW(13) & Microsoft.VisualBasic.ChrW(10) & Microsoft.VisualBasic.ChrW(13) & Microsoft.VisualBasic.ChrW(10) & "So she was co" & _
        "nsidering in her own mind (as well as she could, for the" & Microsoft.VisualBasic.ChrW(13) & Microsoft.VisualBasic.ChrW(10) & "hot day made her feel " & _
        "very sleepy and stupid), whether the pleasure of" & Microsoft.VisualBasic.ChrW(13) & Microsoft.VisualBasic.ChrW(10) & "making a daisy-chain would be " & _
        "worth the trouble of getting up and" & Microsoft.VisualBasic.ChrW(13) & Microsoft.VisualBasic.ChrW(10) & "picking the daisies, when suddenly a White " & _
        "Rabbit with pink eyes ran" & Microsoft.VisualBasic.ChrW(13) & Microsoft.VisualBasic.ChrW(10) & "close by her."
        '
        'Label3
        '
        Me.Label3.Location = New System.Drawing.Point(8, 144)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(592, 16)
        Me.Label3.TabIndex = 12
        Me.Label3.Text = "Text box:"
        '
        'Label5
        '
        Me.Label5.Location = New System.Drawing.Point(8, 256)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(592, 16)
        Me.Label5.TabIndex = 13
        Me.Label5.Text = "Rich Text box:"
        '
        'RichTextBox1
        '
        Me.RichTextBox1.HideSelection = False
        Me.RichTextBox1.Location = New System.Drawing.Point(8, 272)
        Me.RichTextBox1.Name = "RichTextBox1"
        Me.RichTextBox1.Size = New System.Drawing.Size(520, 72)
        Me.RichTextBox1.TabIndex = 14
        Me.RichTextBox1.Text = ""
        '
        'Button1
        '
        Me.Button1.BackColor = System.Drawing.SystemColors.Control
        Me.Button1.Location = New System.Drawing.Point(536, 216)
        Me.Button1.Name = "Button1"
        Me.Button1.Size = New System.Drawing.Size(112, 23)
        Me.Button1.TabIndex = 15
        Me.Button1.Text = "Check Spelling"
        '
        'Button2
        '
        Me.Button2.BackColor = System.Drawing.SystemColors.Control
        Me.Button2.Location = New System.Drawing.Point(536, 320)
        Me.Button2.Name = "Button2"
        Me.Button2.Size = New System.Drawing.Size(112, 23)
        Me.Button2.TabIndex = 16
        Me.Button2.Text = "Check Spelling"
        '
        'Button3
        '
        Me.Button3.BackColor = System.Drawing.SystemColors.Control
        Me.Button3.DialogResult = System.Windows.Forms.DialogResult.OK
        Me.Button3.Location = New System.Drawing.Point(272, 360)
        Me.Button3.Name = "Button3"
        Me.Button3.Size = New System.Drawing.Size(112, 23)
        Me.Button3.TabIndex = 17
        Me.Button3.Text = "Close"
        '
        'CheckTextBoxForm
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 15)
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.ClientSize = New System.Drawing.Size(656, 400)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.Button3, Me.Button2, Me.Button1, Me.RichTextBox1, Me.Label5, Me.Label3, Me.TextBox1, Me.Label4, Me.Label2, Me.Label1})
        Me.Name = "CheckTextBoxForm"
        Me.Text = "CheckTextBoxForm"
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        Call SSCEVB_CheckCtrlDlg(Me.Handle, TextBox1.Handle, False)
    End Sub

    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button2.Click
        Call SSCEVB_CheckCtrlDlg(Me.Handle, RichTextBox1.Handle, False)
    End Sub

    Private Sub CheckTextBoxForm_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        Try
            RichTextBox1.LoadFile("..\..\alice.rtf")
        Catch iox As System.IO.IOException
            RichTextBox1.Text = ""
        Finally
            ' Do nothing
        End Try
    End Sub
End Class
