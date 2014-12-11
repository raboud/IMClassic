Public Class CustomDialogBoxForm
    ' Sentry Spelling Checker Engine
    ' VB.NET example
    ' CustomDialogBoxForm: Demonstrates custom spelling dialog box
    '
    ' Copyright (c) 2002 Wintertree Software Inc.
    ' www.wintertree-software.com
    '
    ' $Id: CustomDialogBoxForm.vb,v 5.14.12 2002/06/26 17:33:00 wsi Exp wsi $

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
    Friend WithEvents StartBtn As System.Windows.Forms.Button
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.StartBtn = New System.Windows.Forms.Button()
        Me.Button1 = New System.Windows.Forms.Button()
        Me.Label4 = New System.Windows.Forms.Label()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.TextBox1 = New System.Windows.Forms.TextBox()
        Me.SuspendLayout()
        '
        'StartBtn
        '
        Me.StartBtn.BackColor = System.Drawing.SystemColors.Control
        Me.StartBtn.Location = New System.Drawing.Point(171, 256)
        Me.StartBtn.Name = "StartBtn"
        Me.StartBtn.Size = New System.Drawing.Size(120, 23)
        Me.StartBtn.TabIndex = 45
        Me.StartBtn.Text = "Start"
        '
        'Button1
        '
        Me.Button1.BackColor = System.Drawing.SystemColors.Control
        Me.Button1.DialogResult = System.Windows.Forms.DialogResult.OK
        Me.Button1.Location = New System.Drawing.Point(426, 256)
        Me.Button1.Name = "Button1"
        Me.Button1.TabIndex = 44
        Me.Button1.Text = "Close"
        '
        'Label4
        '
        Me.Label4.Location = New System.Drawing.Point(16, 96)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(640, 56)
        Me.Label4.TabIndex = 43
        Me.Label4.Text = "To run the example, enter some text in the text area and click the Check Spelling" & _
        " button."
        '
        'Label2
        '
        Me.Label2.BackColor = System.Drawing.Color.FromArgb(CType(255, Byte), CType(224, Byte), CType(192, Byte))
        Me.Label2.Location = New System.Drawing.Point(52, 40)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(568, 48)
        Me.Label2.TabIndex = 42
        Me.Label2.Text = "Sentry includes built-in dialog boxes, but there are times when a custom look or " & _
        "special behavior is needed. This example shows how to interact with the user wit" & _
        "h a spelling dialog written in VB.NET."
        '
        'Label1
        '
        Me.Label1.Font = New System.Drawing.Font("Arial", 12.0!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label1.Location = New System.Drawing.Point(12, 8)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(640, 32)
        Me.Label1.TabIndex = 41
        Me.Label1.Text = "Check spelling using a custom dialog box"
        '
        'TextBox1
        '
        Me.TextBox1.HideSelection = False
        Me.TextBox1.Location = New System.Drawing.Point(12, 152)
        Me.TextBox1.Multiline = True
        Me.TextBox1.Name = "TextBox1"
        Me.TextBox1.ScrollBars = System.Windows.Forms.ScrollBars.Vertical
        Me.TextBox1.Size = New System.Drawing.Size(648, 88)
        Me.TextBox1.TabIndex = 46
        Me.TextBox1.Text = "Either the well was very deep, or she fell very slowly, for" & Microsoft.VisualBasic.ChrW(13) & Microsoft.VisualBasic.ChrW(10) & "she had plenty of ti" & _
        "me as she went down to look about her and to " & Microsoft.VisualBasic.ChrW(13) & Microsoft.VisualBasic.ChrW(10) & "wonnder what was going to happen " & _
        "next. First, she" & Microsoft.VisualBasic.ChrW(13) & Microsoft.VisualBasic.ChrW(10) & "tried to look down and make out what she was coming to, but it" & _
        " was " & Microsoft.VisualBasic.ChrW(13) & Microsoft.VisualBasic.ChrW(10) & "too dark to see anything; then she looked at the sides of" & Microsoft.VisualBasic.ChrW(13) & Microsoft.VisualBasic.ChrW(10) & "the well, and " & _
        "noticed that they were filled with cupboards and " & Microsoft.VisualBasic.ChrW(13) & Microsoft.VisualBasic.ChrW(10) & "book-shelfes; here and there " & _
        "she saw maps and pictures" & Microsoft.VisualBasic.ChrW(13) & Microsoft.VisualBasic.ChrW(10) & "hung upon pegs. She took down a jar from one of the s" & _
        "helves " & Microsoft.VisualBasic.ChrW(13) & Microsoft.VisualBasic.ChrW(10) & "as she passed; it was labelled ""ORANGE MARMALADE""," & Microsoft.VisualBasic.ChrW(13) & Microsoft.VisualBasic.ChrW(10) & "but to her great di" & _
        "sapointment it was empty: she did not like to " & Microsoft.VisualBasic.ChrW(13) & Microsoft.VisualBasic.ChrW(10) & "drop the jar for fear of killing" & _
        " somebody, so managed to put" & Microsoft.VisualBasic.ChrW(13) & Microsoft.VisualBasic.ChrW(10) & "it into one of the cupboards as she fell past it."
        '
        'CustomDialogBoxForm
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 15)
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.ClientSize = New System.Drawing.Size(672, 304)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.TextBox1, Me.StartBtn, Me.Button1, Me.Label4, Me.Label2, Me.Label1})
        Me.Name = "CustomDialogBoxForm"
        Me.Text = "CustomDialogBoxForm"
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub StartBtn_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles StartBtn.Click
        ' Use SpellingDialogForm to check the spelling of the text box.
        Dim spellingDialog = New SpellingDialogForm()
        If (spellingDialog.Start(TextBox1)) Then
            spellingDialog.ShowDialog()
        End If
    End Sub
End Class
