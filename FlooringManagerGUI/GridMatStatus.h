/*----------------------------------------------------------------------
	Copyright © 2001-2002 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_GRIDMATSTATUS_H__CAA56FF9_E97B_4275_B043_6497F9A4E6BD__INCLUDED_)
#define AFX_GRIDMATSTATUS_H__CAA56FF9_E97B_4275_B043_6497F9A4E6BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GridMatStatus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGridMatStatus window

#include "CFGrid.h"
#include "SetMaterial.h"

class CGridMatStatus : public CCFGrid
{
// Construction
public:
	virtual int AppendRow();
	void SetPoId (long lPoId);
	void UpdateRecordSet(long lPoID);
	virtual int DeleteRow(long lRow);
	double CalculatePrice (void);
	virtual BOOL OnCanMove(int oldcol, long oldrow, int newcol, long newrow);
	virtual int OnEditStart(int col, long row,CWnd **edit);

	virtual int OnCellTypeNotify(long ID,int col,long row,long msg,long param);
	void SetMaterialType (long lMaterialType);
	virtual void OnSetup();
	virtual ~CGridMatStatus();
	CGridMatStatus();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGridMatStatus)
	//}}AFX_VIRTUAL

// Implementation
public:

	// Generated message map functions
protected:
	enum {ID = -1, LEN_FEET, LEN_INCHES, WIDTH_FEET, WIDTH_INCHES, MAT_SIZE, STYLE, COLOR, SO, STATUS, LAST} ;
	//{{AFX_MSG(CGridMatStatus)
		// NOTE - the ClassWizard will add and remove member functions here.
	afx_msg void OnKillFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void SelectMaterial (long lId);
	void UpdateGrid ();
	CString m_strSoNumber;
	long m_lMaterialType;
	bool m_bHas2Dim ;
	bool m_bHasSo ;
	bool m_bHasStyle ;
	bool m_bHasColor ;
	CSetMaterial m_setMaterial;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDMATSTATUS_H__CAA56FF9_E97B_4275_B043_6497F9A4E6BD__INCLUDED_)
