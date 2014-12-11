// SetOrderOptionsDetailsDeleted.h : Declaration of the CSetOrderOptionsDetailsDeleted

#pragma once

// code generated on Wednesday, April 09, 2003, 4:35 PM

class CSetOrderOptionsDetailsDeleted : public CRecordset
{
public:
	CSetOrderOptionsDetailsDeleted(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetOrderOptionsDetailsDeleted)

// Field/Param Data

	long	m_ID;
	long    m_OriginalID;
	long	m_OrderID;
	long	m_OptionID;
	double	m_Quantity;
	CString	m_UnitPrice;
	long	m_SubContractorID;
	CString	m_UnitCost;
	CString	m_UnitRetail;
	BOOL	m_SubContractorPaid;
	double	m_SubContractorPay;
	long    m_EntryMethodID;
	BOOL    m_Deleted;

// Overrides
	// Wizard generated virtual function overrides
	public:
	virtual CString GetDefaultConnect();	// Default connection string

	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


