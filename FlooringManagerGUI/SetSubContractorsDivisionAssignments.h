// SetSubContractorsDivisionAssignments.h : Declaration of the CSetSubContractorsDivisionAssignments

#pragma once

// code generated on Tuesday, June 17, 2003, 3:22 PM

class CSetSubContractorsDivisionAssignments : public CRecordset
{
public:
	CSetSubContractorsDivisionAssignments(CDatabase* pDatabase);
	DECLARE_DYNAMIC(CSetSubContractorsDivisionAssignments)

// Field/Param Data

	long	m_ID;
	long	m_SubContractorID;
	long	m_DivisionID;
	long	m_SubDivisionID;

// Overrides
	// Wizard generated virtual function overrides
	public:

	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


