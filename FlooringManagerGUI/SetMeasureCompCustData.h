// SetMeasureCompCustData.h : Declaration of the CSetMeasureCompCustData

#pragma once

// code generated on Friday, April 09, 2004, 1:17 AM

class CSetMeasureCompCustData : public CRecordset
{
public:
	CSetMeasureCompCustData(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetMeasureCompCustData)

// Field/Param Data

	long	m_ID;
	long	m_CustomerID;
	CString	m_LastName;
	CString	m_FirstName;
	CString	m_Address1;
	CString	m_Address2;
	CString	m_City;
	CString	m_State;
	CString	m_Zip;
	CString	m_HomePhone;
	CString	m_BusinessPhone;
	CString	m_CellPhone;
	CString	m_Pager;
	CString	m_CrossStreetDir1;
	CString	m_CrossStreet1;
	CString	m_CrossStreetDir2;
	CString	m_CrossStreet2;

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


