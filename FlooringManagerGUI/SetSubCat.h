/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_SETSUBCAT_H__D61FD493_56FC_4904_BB76_4548D2A410DC__INCLUDED_)
#define AFX_SETSUBCAT_H__D61FD493_56FC_4904_BB76_4548D2A410DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetSubCat.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetSubCat recordset

class CSetSubCat : public CRecordset
{
public:
	CSetSubCat(CDatabase* pDatabase);
	DECLARE_DYNAMIC(CSetSubCat)

// Field/Param Data
	//{{AFX_FIELD(CSetSubCat, CRecordset)
	long	m_SubCatId;
	CString	m_Description;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetSubCat)
	public:
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETSUBCAT_H__D61FD493_56FC_4904_BB76_4548D2A410DC__INCLUDED_)
