Public Class CheckBackgroundForm
    ' Sentry Spelling Checker Engine
    ' VB.NET Example
    ' CheckBackgroundForm: Demonstrates checking rich-text boxes in the background
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
    Friend WithEvents RichTextBox1 As System.Windows.Forms.RichTextBox
    Friend WithEvents RichTextBox2 As System.Windows.Forms.RichTextBox
    Friend WithEvents Button1 As System.Windows.Forms.Button
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Label4 = New System.Windows.Forms.Label()
        Me.RichTextBox1 = New System.Windows.Forms.RichTextBox()
        Me.RichTextBox2 = New System.Windows.Forms.RichTextBox()
        Me.Button1 = New System.Windows.Forms.Button()
        Me.SuspendLayout()
        '
        'Label1
        '
        Me.Label1.Font = New System.Drawing.Font("Arial", 12.0!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label1.Location = New System.Drawing.Point(8, 8)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(640, 32)
        Me.Label1.TabIndex = 1
        Me.Label1.Text = "Check spelling of rich-text boxes in the background"
        '
        'Label2
        '
        Me.Label2.BackColor = System.Drawing.Color.FromArgb(CType(255, Byte), CType(224, Byte), CType(192, Byte))
        Me.Label2.Location = New System.Drawing.Point(52, 40)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(568, 48)
        Me.Label2.TabIndex = 2
        Me.Label2.Text = "Sentry can check for misspelled words in a rich-text box as the user types. Missp" & _
        "elled words are shown in red, and the user can right-click over a misspelled wor" & _
        "d to see a pop-up menu of suggestions. Corrected words change back to black."
        '
        'Label4
        '
        Me.Label4.Location = New System.Drawing.Point(16, 96)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(640, 40)
        Me.Label4.TabIndex = 11
        Me.Label4.Text = "Enter some text, including misspelled words, in either of the rich-text boxes bel" & _
        "ow. Sentry watches in the background for misspelled words typed in the rich-text" & _
        " box that has the focus."
        '
        'RichTextBox1
        '
        Me.RichTextBox1.Location = New System.Drawing.Point(20, 136)
        Me.RichTextBox1.Name = "RichTextBox1"
        Me.RichTextBox1.Size = New System.Drawing.Size(632, 88)
        Me.RichTextBox1.TabIndex = 12
        Me.RichTextBox1.Text = ""
        '
        'RichTextBox2
        '
        Me.RichTextBox2.Location = New System.Drawing.Point(20, 232)
        Me.RichTextBox2.Name = "RichTextBox2"
        Me.RichTextBox2.Size = New System.Drawing.Size(632, 88)
        Me.RichTextBox2.TabIndex = 13
        Me.RichTextBox2.Text = ""
        '
        'Button1
        '
        Me.Button1.BackColor = System.Drawing.SystemColors.Control
        Me.Button1.DialogResult = System.Windows.Forms.DialogResult.OK
        Me.Button1.Location = New System.Drawing.Point(299, 328)
        Me.Button1.Name = "Button1"
        Me.Button1.TabIndex = 14
        Me.Button1.Text = "Close"
        '
        'CheckBackgroundForm
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 15)
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.ClientSize = New System.Drawing.Size(672, 368)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.Button1, Me.RichTextBox2, Me.RichTextBox1, Me.Label4, Me.Label2, Me.Label1})
        Me.Name = "CheckBackgroundForm"
        Me.Text = "CheckBackgroundForm"
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub RichTextBox1_Enter(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles RichTextBox1.Enter
        SSCEVB_CheckCtrlBackground(RichTextBox1.Handle)
    End Sub

    Private Sub RichTextBox2_Enter(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles RichTextBox2.Enter
        SSCEVB_CheckCtrlBackground(RichTextBox2.Handle)
    End Sub
End Class
