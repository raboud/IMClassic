// SetMeasureCompOrderData.h : Implementation of the CSetMeasureCompOrderData class



// CSetMeasureCompOrderData implementation

// code generated on Friday, April 09, 2004, 1:19 AM

#include "stdafx.h"
#include "SetMeasureCompOrderData.h"
IMPLEMENT_DYNAMIC(CSetMeasureCompOrderData, CRecordset)

CSetMeasureCompOrderData::CSetMeasureCompOrderData(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_OrderID = 0;
	m_Heat = FALSE;
	m_Pets = FALSE;
	m_Electricity = FALSE;
	m_FurnitureMoving = FALSE;
	m_NewPaint = FALSE;
	m_Removal = FALSE;
	m_PavedDriveway = FALSE;
	m_Garage = FALSE;
	m_Elevator = FALSE;
	m_Disposal = "";
	m_Access = "";
	m_SiteType = "";
	m_MetalColor = "";
	m_nFields = 15;
	m_nDefaultType = dynaset;
}

CString CSetMeasureCompOrderData::GetDefaultSQL()
{
	return _T("[dbo].[MeasureCompOrderData]");
}

void CSetMeasureCompOrderData::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[OrderID]"), m_OrderID);
	RFX_Bool(pFX, _T("[Heat]"), m_Heat);
	RFX_Bool(pFX, _T("[Pets]"), m_Pets);
	RFX_Bool(pFX, _T("[Electricity]"), m_Electricity);
	RFX_Bool(pFX, _T("[FurnitureMoving]"), m_FurnitureMoving);
	RFX_Bool(pFX, _T("[NewPaint]"), m_NewPaint);
	RFX_Bool(pFX, _T("[Removal]"), m_Removal);
	RFX_Bool(pFX, _T("[PavedDriveway]"), m_PavedDriveway);
	RFX_Bool(pFX, _T("[Garage]"), m_Garage);
	RFX_Bool(pFX, _T("[Elevator]"), m_Elevator);
	RFX_Text(pFX, _T("[Disposal]"), m_Disposal);
	RFX_Text(pFX, _T("[Access]"), m_Access);
	RFX_Text(pFX, _T("[SiteType]"), m_SiteType);
	RFX_Text(pFX, _T("[MetalColor]"), m_MetalColor);

}
/////////////////////////////////////////////////////////////////////////////
// CSetMeasureCompOrderData diagnostics

#ifdef _DEBUG
void CSetMeasureCompOrderData::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetMeasureCompOrderData::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


