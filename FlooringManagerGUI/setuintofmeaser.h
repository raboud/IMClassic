/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_SETUINTOFMEASER_H__71BB2C17_6D2C_4999_9DFF_FA5D381A4357__INCLUDED_)
#define AFX_SETUINTOFMEASER_H__71BB2C17_6D2C_4999_9DFF_FA5D381A4357__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetUintOfMeaser.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetUnitOfMeasure recordset

class CSetUnitOfMeasure : public CRecordset
{
public:
	CSetUnitOfMeasure(CDatabase* pDatabase);
	DECLARE_DYNAMIC(CSetUnitOfMeasure)

// Field/Param Data
	//{{AFX_FIELD(CSetUnitOfMeasure, CRecordset)
	long	m_UnitOfMeasureID;
	CString	m_Description;
	double	m_Divisor ;
	long	m_NumberOfDecimals;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetUnitOfMeasure)
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

#endif // !defined(AFX_SETUINTOFMEASER_H__71BB2C17_6D2C_4999_9DFF_FA5D381A4357__INCLUDED_)
