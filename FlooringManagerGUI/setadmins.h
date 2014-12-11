/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_SETADMINS_H__92AD7D92_9D57_4544_8821_DB07EEAB00B3__INCLUDED_)
#define AFX_SETADMINS_H__92AD7D92_9D57_4544_8821_DB07EEAB00B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetAdmins.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetAdmins recordset

class CSetAdmins : public CRecordset
{
public:
	CSetAdmins(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetAdmins)

// Field/Param Data
	//{{AFX_FIELD(CSetAdmins, CRecordset)
	CString	m_name;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetAdmins)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
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

#endif // !defined(AFX_SETADMINS_H__92AD7D92_9D57_4544_8821_DB07EEAB00B3__INCLUDED_)
