// SetPONotes.h : Implementation of the CSetPONotes class



// CSetPONotes implementation

// code generated on Wednesday, August 24, 2005, 9:08 AM

#include "stdafx.h"
#include "SetPONotes.h"
#include "flooring.h"
IMPLEMENT_DYNAMIC(CSetPONotes, CRecordset)

CSetPONotes::CSetPONotes(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_OrderID = 0;
	m_NoteTypeID = 0;
	m_SpokeWithID = 0;
	m_ContactName = L"";
	m_DateTimeEntered;
	m_NoteText = "";
	m_EnteredByUserID = 0;
	m_CustomerToCallBack = FALSE;
	m_Scheduled = FALSE;
	m_UnScheduled = FALSE;
	m_ScheduledAM = FALSE;
	m_ScheduledDate;
	m_Deleted = FALSE;
	m_SentViaXML = FALSE;
	m_DateTimeSent;
	m_nFields = 16;
	m_nDefaultType = dynaset;
}

CString CSetPONotes::GetDefaultSQL()
{
	return _T("[dbo].[PONotes]");
}

void CSetPONotes::DoFieldExchange(CFieldExchange* pFX)
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
	RFX_Long(pFX, _T("[NoteTypeID]"), m_NoteTypeID);
	RFX_Long(pFX, _T("[SpokeWithID]"), m_SpokeWithID);
	RFX_Text(pFX, _T("[ContactName]"), m_ContactName);
	RFX_Date(pFX, _T("[DateTimeEntered]"), m_DateTimeEntered);
	RFX_Text(pFX, _T("[NoteText]"), m_NoteText, CGlobals::iMAX_ORDER_NOTES);
	RFX_Long(pFX, _T("[EnteredByUserID]"), m_EnteredByUserID);
	RFX_Bool(pFX, _T("[CustomerToCallBack]"), m_CustomerToCallBack);
	RFX_Bool(pFX, _T("[Scheduled]"), m_Scheduled);
	RFX_Bool(pFX, _T("[UnScheduled]"), m_UnScheduled);
	RFX_Bool(pFX, _T("[ScheduledAM]"), m_ScheduledAM);
	RFX_Date(pFX, _T("[ScheduledDate]"), m_ScheduledDate);
	RFX_Bool(pFX, _T("[Deleted]"), m_Deleted);
	RFX_Bool(pFX, _T("[SentViaXML]"), m_SentViaXML);
	RFX_Date(pFX, _T("[DateTimeSent]"), m_DateTimeSent);

}
/////////////////////////////////////////////////////////////////////////////
// CSetPONotes diagnostics

#ifdef _DEBUG
void CSetPONotes::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetPONotes::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


