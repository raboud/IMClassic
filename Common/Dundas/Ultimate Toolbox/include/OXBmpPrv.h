// ==========================================================================
// 							Class Specification : COXBmpFileDialog
// ==========================================================================

// Header file : oxbmpprv.h

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved
                          
// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	YES	Derived from COXPreviewDialog

//	YES	Is a Cwnd.                     
//	NO	Two stage creation (constructor & Create())
//	YES	Has a message map
//	YES  Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	YES	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Desciption :         
//	This class implements the two virtual function of COXPreviewDialog, to display
//  BMP/DIB format.

// Remark:
//	

// Prerequisites (necessary conditions):
//	

/////////////////////////////////////////////////////////////////////////////
#ifndef __BMP_PREVDLG_H__
#define __BMP_PREVDLG_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"

#include "OXPrvDlg.h"
#include "oxdib.h"


class OX_CLASS_DECL COXBmpFileDialog : public COXPreviewDialog
{
DECLARE_DYNAMIC(COXBmpFileDialog)

// Data members -------------------------------------------------------------
public:
	
protected:
	COXDIB	m_dib;

private:
	
// Member functions ---------------------------------------------------------
public:
	COXBmpFileDialog(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Contructor of object

	virtual ~COXBmpFileDialog();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of object
	
#ifndef WIN32
	int DoModal();
#endif


protected:      
 	virtual void OnNewFileSelect(const CString& sFilename);
	virtual void OnPaintPreview(CDC* pDC, const CRect& paintRect);
 	virtual void OnDoRealizePalette(CWnd* pFocusWnd);

private:

};

#endif

