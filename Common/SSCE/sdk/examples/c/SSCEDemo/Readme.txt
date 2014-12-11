SSCE Demo Readme File
=====================

SSCEDemo demonstrates calling the SSCE API from a C program. SSCEDemo
allows you to call any function in Sentry Core and Windows APIs.

Note that the first function you should call is SSCE_SetKey, passing in
the license key provided by Wintertree Software. If SSCE_SetKey is not
called with a valid key, the demo program will not work correctly.

To build Win16 SSCE Demo:
-------------------------

If you use MSVC, open project sscedemo.mak.

If you use other compilers, follow these steps to build SSCEDemo:

1. Define _WIN16 using your compiler's preprocessor-symbol feature.

2. Add ssce\sdk\include to your compiler's include path.

3. Compile sscedemo.c.

4. Compile sscedemo.rc using a resource compiler.

5. Link sscedemo.obj, sscedemo.def, sscedemo.res, and
   ssce\sdk\lib\ssce5316.lib to build sscedemo.exe.

To build Win32 SSCE Demo:
-------------------------

If you use VC++, open project sscedemo.vcp.

If you use other compilers, or an older version of VC++ which does not
accept the sscedemo.vcp project file, use these steps to build SSCEDemo:

1. Add ssce\sdk\include to your compiler's include path.

2. Compile sscedemo.c.

3. Compile sscedemo.rc using a resource compiler.

4. Link sscedemo.obj, sscedemo.def, sscedemo.res, and
   ssce\sdk\lib\ssce5332.lib to build sscedemo.exe.

