' Sentry Spelling Checker Engine
' VB.NET Example
' MainForm: Present demos to the user.
'
' Copyright (c) 2002 Wintertree Software Inc.
' www.wintertree-software.com
'
' Use, duplication, and disclosure of this file is governed
' by a license agreement between Wintertree Software Inc. and
' the licensee.
'
' $Id$

Public Class MainForm
    Inherits System.Windows.Forms.Form

    ' Set this constant to your Sentry license key, provided by
    ' Wintertree Software. Alternatively, you can leave it set to
    ' 0 and enter your license key at run time. Note that your license
    ' key must be set as a hexadecimal constant like this: &H1234ABCD
    Private Const SENTRY_LICENSE_KEY = 0

    ' The actual license key
    Private LicenseKey As Integer = SENTRY_LICENSE_KEY


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
    Friend WithEvents CheckBackgroundBtn As System.Windows.Forms.Button
    Friend WithEvents CheckStringBtn As System.Windows.Forms.Button
    Friend WithEvents CheckTextBoxBtn As System.Windows.Forms.Button
    Friend WithEvents CheckTextInCodeBtn As System.Windows.Forms.Button
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents Label4 As System.Windows.Forms.Label
    Friend WithEvents PerformanceTestBtn As System.Windows.Forms.Button
    Friend WithEvents CustomDialogBtn As System.Windows.Forms.Button
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.CheckTextBoxBtn = New System.Windows.Forms.Button()
        Me.CheckBackgroundBtn = New System.Windows.Forms.Button()
        Me.CheckStringBtn = New System.Windows.Forms.Button()
        Me.CheckTextInCodeBtn = New System.Windows.Forms.Button()
        Me.CustomDialogBtn = New System.Windows.Forms.Button()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.Label4 = New System.Windows.Forms.Label()
        Me.PerformanceTestBtn = New System.Windows.Forms.Button()
        Me.SuspendLayout()
        '
        'Label1
        '
        Me.Label1.Font = New System.Drawing.Font("Arial", 18.0!, (System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Italic), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label1.Location = New System.Drawing.Point(4, 8)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(560, 40)
        Me.Label1.TabIndex = 0
        Me.Label1.Text = "Sentry Spelling Checker Engine"
        '
        'CheckTextBoxBtn
        '
        Me.CheckTextBoxBtn.BackColor = System.Drawing.SystemColors.Control
        Me.CheckTextBoxBtn.Location = New System.Drawing.Point(36, 192)
        Me.CheckTextBoxBtn.Name = "CheckTextBoxBtn"
        Me.CheckTextBoxBtn.Size = New System.Drawing.Size(160, 23)
        Me.CheckTextBoxBtn.TabIndex = 1
        Me.CheckTextBoxBtn.Text = "Check Text Box"
        '
        'CheckBackgroundBtn
        '
        Me.CheckBackgroundBtn.BackColor = System.Drawing.SystemColors.Control
        Me.CheckBackgroundBtn.Location = New System.Drawing.Point(204, 192)
        Me.CheckBackgroundBtn.Name = "CheckBackgroundBtn"
        Me.CheckBackgroundBtn.Size = New System.Drawing.Size(160, 23)
        Me.CheckBackgroundBtn.TabIndex = 2
        Me.CheckBackgroundBtn.Text = "Check Background"
        '
        'CheckStringBtn
        '
        Me.CheckStringBtn.BackColor = System.Drawing.SystemColors.Control
        Me.CheckStringBtn.Location = New System.Drawing.Point(372, 192)
        Me.CheckStringBtn.Name = "CheckStringBtn"
        Me.CheckStringBtn.Size = New System.Drawing.Size(160, 23)
        Me.CheckStringBtn.TabIndex = 3
        Me.CheckStringBtn.Text = "Check String"
        '
        'CheckTextInCodeBtn
        '
        Me.CheckTextInCodeBtn.BackColor = System.Drawing.SystemColors.Control
        Me.CheckTextInCodeBtn.Location = New System.Drawing.Point(36, 232)
        Me.CheckTextInCodeBtn.Name = "CheckTextInCodeBtn"
        Me.CheckTextInCodeBtn.Size = New System.Drawing.Size(160, 23)
        Me.CheckTextInCodeBtn.TabIndex = 4
        Me.CheckTextInCodeBtn.Text = "Check Text in Code"
        '
        'CustomDialogBtn
        '
        Me.CustomDialogBtn.BackColor = System.Drawing.SystemColors.Control
        Me.CustomDialogBtn.Location = New System.Drawing.Point(372, 232)
        Me.CustomDialogBtn.Name = "CustomDialogBtn"
        Me.CustomDialogBtn.Size = New System.Drawing.Size(160, 23)
        Me.CustomDialogBtn.TabIndex = 6
        Me.CustomDialogBtn.Text = "Custom Dialog Box"
        '
        'Label2
        '
        Me.Label2.Location = New System.Drawing.Point(8, 48)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(552, 23)
        Me.Label2.TabIndex = 7
        Me.Label2.Text = "VB.NET Example"
        '
        'Label3
        '
        Me.Label3.BackColor = System.Drawing.Color.Bisque
        Me.Label3.Location = New System.Drawing.Point(60, 72)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(448, 56)
        Me.Label3.TabIndex = 8
        Me.Label3.Text = "Welcome to the Sentry Spelling Checker Engine VB.NET Example! This example progra" & _
        "m demonstrates some of Sentry's most important features."
        Me.Label3.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'Label4
        '
        Me.Label4.Location = New System.Drawing.Point(8, 136)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(552, 40)
        Me.Label4.TabIndex = 9
        Me.Label4.Text = "To see a feature in action, click one of the buttons below. To see how the featur" & _
        "e works, examine the VB module which implements the feature."
        '
        'PerformanceTestBtn
        '
        Me.PerformanceTestBtn.BackColor = System.Drawing.SystemColors.Control
        Me.PerformanceTestBtn.Location = New System.Drawing.Point(204, 232)
        Me.PerformanceTestBtn.Name = "PerformanceTestBtn"
        Me.PerformanceTestBtn.Size = New System.Drawing.Size(160, 23)
        Me.PerformanceTestBtn.TabIndex = 10
        Me.PerformanceTestBtn.Text = "Performance Test"
        '
        'MainForm
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 15)
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.ClientSize = New System.Drawing.Size(568, 272)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.PerformanceTestBtn, Me.Label4, Me.Label3, Me.Label2, Me.CustomDialogBtn, Me.CheckTextInCodeBtn, Me.CheckStringBtn, Me.CheckBackgroundBtn, Me.CheckTextBoxBtn, Me.Label1})
        Me.Name = "MainForm"
        Me.Text = "Sentry Spelling Checker Engine VB.NET Example"
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub CheckTextBoxBtn_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles CheckTextBoxBtn.Click
        If (Not getLicenseKey()) Then
            Exit Sub
        End If
        Dim theForm = New CheckTextBoxForm()
        theForm.ShowDialog()
    End Sub

    ' Make sure a valid license key has been set.
    ' @return True if the user wants to continue; False if the user wants to cancel.
    Private Function getLicenseKey() As Boolean
        Dim licForm = New LicenseForm()

        getLicenseKey = True
        ' Make sure we have a valid license key or the examples won't work.
        If (LicenseKey = 0) Then
            If (licForm.ShowDialog() = System.Windows.Forms.DialogResult.OK) Then
                LicenseKey = licForm.GetLicenseKey
                licForm.Hide()
            Else
                getLicenseKey = False
            End If
        End If
        If (LicenseKey <> 0) Then
            SSCEVB_SetKey(LicenseKey)
        End If

    End Function

    Private Sub CheckBackgroundBtn_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles CheckBackgroundBtn.Click
        If (Not getLicenseKey()) Then
            Exit Sub
        End If
        Dim theForm = New CheckBackgroundForm()
        theForm.ShowDialog()
    End Sub

    Private Sub CheckStringBtn_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles CheckStringBtn.Click
        If (Not getLicenseKey()) Then
            Exit Sub
        End If
        Dim theForm = New CheckStringForm()
        theForm.ShowDialog()
    End Sub

    Private Sub CheckTextInCodeBtn_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles CheckTextInCodeBtn.Click
        If (Not getLicenseKey()) Then
            Exit Sub
        End If
        Dim theForm = New CheckTextInCodeForm()
        theForm.ShowDialog()
    End Sub

    Private Sub PerformanceTestBtn_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PerformanceTestBtn.Click
        If (Not getLicenseKey()) Then
            Exit Sub
        End If
        Dim theForm = New PerformanceTestForm()
        theForm.ShowDialog()
    End Sub

    Private Sub CustomDialogBtn_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles CustomDialogBtn.Click
        If (Not getLicenseKey()) Then
            Exit Sub
        End If
        Dim theForm = New CustomDialogBoxForm()
        theForm.ShowDialog()
    End Sub
End Class
