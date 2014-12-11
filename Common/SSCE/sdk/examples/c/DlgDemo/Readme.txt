DlgDemo Readme File
===================

DlgDemo demonstrates use of the built-in Sentry dialogs and client-
supplied dialog templates from a C program. DlgDemo uses
SSCE_CheckCtrlDlg, SSCE_CheckCtrlDlgTmplt, SSCE_EditLexDlg, and
SSCE_OptionsDlg.

When built as a 32-bit program, DlgDemo also demonstrates how to check
spelling "as you type".

Before you can build DlgDemo, you must set the licenseKey variable
in dlgdemo.c to your license key, provided by Wintertree Software. Your
license key is provided as a hexadecimal number, so enter the key as a
hexadecimal constant like this:

	static const SSCE_U32 licenseKey = 0x1234ABCD;


To build Win16 DlgDemo:
-----------------------

If you use MSVC, open project DlgDemo.mak.

If you use other compilers, follow these steps to build DlgDemo:

1. Define _WIN16 using your compiler's preprocessor-symbol feature.

2. Add ssce\sdk\include to your compiler's include path.

3. Compile dlgdemo.c.

4. Compile dlgdemo.rc using a resource compiler.

5. Link dlgdemo.obj, dlgdmo16.def, dlgdemo.res, ssce\sdk\lib\ssce5316.lib
   to build dlgdemo.exe.

To build Win32 DlgDemo:
-----------------------

If you use VC++, open project DlgDemo32.vcp.

If you use other compilers, or an older version of VC++ which does not accept
the DlgDemo32.vcp project file, follow these steps to build DlgDemo:

1. Add ssce\sdk\include to your compiler's include path.

2. Compile dlgdemo.c.

3. Compile dlgdemo.rc using a resource compiler.

5. Link dlgdemo.obj, dlgdmo32.def, dlgdemo.res, ssce\sdk\lib\ssce5332.lib
   to build dlgdemo.exe.

The 32-bit version of DlgDemo uses the standard RichEdit control for
text entry. As you type, any misspelled words are shown in red. Right-
click the mouse on a misspelled word to see a pop-up menu containing
suggestions and common spelling-checker actions.

