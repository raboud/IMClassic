Sentry VCL
==========

This directory contains the Delphi source code for a VCL. Delphi users
may prefer to access the Sentry API through a VCL rather than calling the
API directly. The VCL is provided as a starting point and for compatibility
with previous versions of the Sentry Windows SDK. The VCL is not supported.

Before you can use the Sentry VCL in a Delphi application, you must
install the VCL into Delphi. If you are using the Sentry Win16 SDK, you
must install the Sentry VCL using Delphi 1.0. If you are using the
Sentry Win32 SDK, you must install the Sentry VCL using Delphi 2.0 or
later. Before you install the Sentry VCL, make sure the Sentry DLL
(SSCE5316.DLL or SSCE5332.DLL) is in your Windows\System directory.
Delphi requires that the DLL be accessible while it is rebuilding the
component library.

If you are installing a new version of Sentry over a previous version,
remove the previous instance of SSCEVcl before installing the new
instance. Similarly, remove SSCEVCL.KWF from Delphi's HelpInst program
before installing the SSCEVcl help.

Source code for the Sentry VCL is located in sscevcl.pas. Consult the
Delphi user's guide for VCL installation instructions applicable to your
version of Delphi.

The file sscevcl.kwf contains help keywords for the Sentry VCL. To
install context-sensitive help for the Sentry VCL, consult the Delphi
user's guide for keyword-file installation instructions applicable to
your version of Delphi.

The Sentry VCL is a non-visual component (like the File Open Dialog
component, for example). You can place a copy of the component on any
form. The Sentry VCL icon is a document symbol with a red check mark.
Instructions for using the Sentry VCL are contained in the on-line help.
To access help for the Sentry VCL, select the Sentry VCL icon in the
Component Palette or on a form, then press F1.

To use the Sentry VCL in your Delphi application:

1. Add the Sentry spelling-checker dialog object (SsceSpellDlg) to one
of your project's forms by selecting the SsceSpellDlg icon in the
Dialogs palette.

2. To check the text in a TEdit, TRichEdit, or TMemo component, add
statements similar to the following to an event handler (e.g., in
response to a button press or menu selection):

	SsceSpellDlg1.ControlHandle := Memo1.Handle;
	SsceSpellDlg1.Execute;

The TEdit, TRichEdit, or TMemo component should have the Hide Selection
property set to False and the ScrollBars property set to ssVertical.

3. To check the text in a string, add statements similar to the following
to an event handler (e.g., in response to a button press or menu
selection):

	SsceSpellDlg1.TextStr := 'heloo worlld';
	SsceSpellDlg1.Execute;

