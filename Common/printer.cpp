/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#include "stdafx.h"
#include "Printer.h"

CPrinter::CPrinter(CDC * usedc)
    {
     dc = usedc;
     pageVMargin = 0;
     pageHMargin = 0;
     pageHeight = 0;
     Y = 0;
     lineHeight = 0; 
     pageStarted = FALSE;
     docStarted = FALSE;
     pageNumber = 0;
    } // CPrinter::Printer

CPrinter::~CPrinter()
    {
     if(docStarted)
	EndPrinting();
    } // CPrinter::~Printer

BOOL CPrinter::StartPrinting()
    {
     DOCINFO info;
     ::ZeroMemory(&info, sizeof(info));
     info.lpszDocName = AfxGetAppName();

     SetPrinterFont();

     dc->StartDoc(&info);
     docStarted = TRUE;

     TEXTMETRIC tm;
     dc->GetTextMetrics(&tm);
     lineHeight  = tm.tmHeight + tm.tmInternalLeading;
     pageVMargin = dc->GetDeviceCaps(LOGPIXELSY) / 2;
     pageHMargin = dc->GetDeviceCaps(LOGPIXELSX) / 2;
     pageHeight  = dc->GetDeviceCaps(VERTRES);
     pageWidth   = dc->GetDeviceCaps(HORZRES);
     Y = pageVMargin;
     return TRUE;
    } // CPrinter::StartPrinting

void CPrinter::PrintLine(const CString & s)
    {
     if(!pageStarted || Y > pageHeight - pageVMargin)
	{ /* new page */
	 if(pageStarted)
	    dc->EndPage();
	 dc->StartPage();
	 pageNumber++;
	 Y = pageVMargin;
	 pageStarted = TRUE;
	 PageHeading();
	} /* new page */
     dc->TextOut(pageHMargin, Y, s);
     Y += lineHeight;
    } // CPrinter::PrintLine

void CPrinter::EndPrinting()
    {
     dc->EndPage();
     dc->EndDoc();
     docStarted = FALSE;
    } // CPrinter::EndPrinting

void CPrinter::SetPrinterFont()
    {
     CFont f;
     f.CreateStockObject(ANSI_FIXED_FONT);
     dc->SelectObject(f);
    } // CPrinter::SetPrinterFont

void CPrinter::PageHeading()
    {
     CString s(AfxGetAppName());
     int headingY = pageVMargin - (3 * lineHeight) / 2;
     int lineY = pageVMargin - lineHeight / 2;
     int saved = dc->SaveDC();
     dc->SetTextColor(RGB(0,0,0));
     CPen pen(PS_SOLID, dc->GetDeviceCaps(LOGPIXELSX) / 100, RGB(255, 0, 0));
     dc->SelectObject(pen);
     dc->TextOut(pageHMargin, headingY, s);
     s.Format(_T("%d"), pageNumber);
     int w = dc->GetTextExtent(s).cx;
     dc->TextOut(pageWidth - pageHMargin - w, headingY, s);
     dc->MoveTo(pageHMargin, lineY);
     dc->LineTo(pageWidth - pageHMargin, lineY);
     dc->RestoreDC(saved);
    } // CPrinter::PageHeading
