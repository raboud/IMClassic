/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_SETACTIONREPORT_H__801E6886_B26F_435A_B49E_3DC5056A90BD__INCLUDED_)
#define AFX_SETACTIONREPORT_H__801E6886_B26F_435A_B49E_3DC5056A90BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetActionReport.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetActionReport recordset
//const int iMAX_NOTES = 2000;
const int iMAX_ERROR_STRING = 100;

class CSetActionReport : public CRecordset
{
public:
	CSetActionReport(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetActionReport)

// Field/Param Data
	//{{AFX_FIELD(CSetActionReport, CRecordset)
	COleDateTime m_ReportDate;
	COleDateTime m_LastEditedDate;
	CString	m_Nature;
	CString	m_ActionRequired;
	CString	m_Cause;
	BOOL	m_Closed;
	long	m_ID;
	long	m_InstallerError;
	long	m_MeasureError;
	long	m_MillError;
	long	m_OrderID;
	long	m_StoreError;
	CString m_StoreErrorText;
	CString m_MillErrorText;
	CString m_MeasureErrorText;
	CString m_InstallerErrorText;
	long    m_EnteredBy;
	long	m_LastEditedBy;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetActionReport)
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

#endif // !defined(AFX_SETACTIONREPORT_H__801E6886_B26F_435A_B49E_3DC5056A90BD__INCLUDED_)
