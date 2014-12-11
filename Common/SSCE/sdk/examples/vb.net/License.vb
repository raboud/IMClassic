Public Class LicenseForm
    ' Sentry Spelling Checker Engine
    ' VB.NET Example
    ' License: Prompt the user for the Sentry license key
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
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents LicenseKeyText As System.Windows.Forms.TextBox
    Friend WithEvents OkBtn As System.Windows.Forms.Button
    Friend WithEvents CancelBtn As System.Windows.Forms.Button
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.LicenseKeyText = New System.Windows.Forms.TextBox()
        Me.OkBtn = New System.Windows.Forms.Button()
        Me.CancelBtn = New System.Windows.Forms.Button()
        Me.SuspendLayout()
        '
        'Label1
        '
        Me.Label1.Location = New System.Drawing.Point(8, 8)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(272, 48)
        Me.Label1.TabIndex = 0
        Me.Label1.Text = "Please enter your Sentry license key, provided by Wintertree Software. The exampl" & _
        "es will not run without the key."
        '
        'Label2
        '
        Me.Label2.Location = New System.Drawing.Point(8, 64)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(272, 48)
        Me.Label2.TabIndex = 1
        Me.Label2.Text = "To avoid seeing this message in future, set SENTRY_LICENSE_KEY in MainForm.vb to " & _
        "your license key."
        '
        'Label3
        '
        Me.Label3.Location = New System.Drawing.Point(10, 136)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(102, 16)
        Me.Label3.TabIndex = 2
        Me.Label3.Text = "License key:"
        '
        'LicenseKeyText
        '
        Me.LicenseKeyText.Location = New System.Drawing.Point(128, 128)
        Me.LicenseKeyText.Name = "LicenseKeyText"
        Me.LicenseKeyText.Size = New System.Drawing.Size(152, 22)
        Me.LicenseKeyText.TabIndex = 3
        Me.LicenseKeyText.Text = ""
        '
        'OkBtn
        '
        Me.OkBtn.BackColor = System.Drawing.SystemColors.Control
        Me.OkBtn.DialogResult = System.Windows.Forms.DialogResult.OK
        Me.OkBtn.Location = New System.Drawing.Point(57, 168)
        Me.OkBtn.Name = "OkBtn"
        Me.OkBtn.TabIndex = 4
        Me.OkBtn.Text = "OK"
        '
        'CancelBtn
        '
        Me.CancelBtn.BackColor = System.Drawing.SystemColors.Control
        Me.CancelBtn.DialogResult = System.Windows.Forms.DialogResult.Cancel
        Me.CancelBtn.Location = New System.Drawing.Point(161, 168)
        Me.CancelBtn.Name = "CancelBtn"
        Me.CancelBtn.TabIndex = 5
        Me.CancelBtn.Text = "OK"
        '
        'LicenseForm
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 15)
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.ClientSize = New System.Drawing.Size(292, 208)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.CancelBtn, Me.OkBtn, Me.LicenseKeyText, Me.Label3, Me.Label2, Me.Label1})
        Me.Name = "LicenseForm"
        Me.Text = "License Key"
        Me.ResumeLayout(False)

    End Sub

#End Region

    Public Function GetLicenseKey() As String
        GetLicenseKey = Val("&H" & LicenseKeyText.Text)
    End Function

End Class
