// vwPONotesWithName.h : Implementation of the CvwPONotesWithName class



// CvwPONotesWithName implementation

// code generated on Tuesday, August 30, 2005, 2:02 PM

#include "stdafx.h"
#include "vwPONotesWithName.h"
IMPLEMENT_DYNAMIC(CvwPONotesWithName, CRecordset)

CvwPONotesWithName::CvwPONotesWithName(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_OrderID = 0;
	m_DateTimeEntered;
	m_NoteText = "";
	m_EnteredByName = L"";
	m_nFields = 5;
	m_nDefaultType = dynaset;
}
#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CvwPONotesWithName::GetDefaultConnect()
{
	return _T("DSN=Flooring;APP=Microsoft\x00ae Visual Studio .NET;WSID=DELL4550-01;DATABASE=Flooring;Trusted_Connection=Yes");
}

CString CvwPONotesWithName::GetDefaultSQL()
{
	return _T("[dbo].[vwPONotesWithName]");
}

void CvwPONotesWithName::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[OrderID]"), m_OrderID);
	RFX_Date(pFX, _T("[DateTimeEntered]"), m_DateTimeEntered);
	RFX_Text(pFX, _T("[NoteText]"), m_NoteText);
	RFX_Text(pFX, _T("[EnteredByName]"), m_EnteredByName);

}
/////////////////////////////////////////////////////////////////////////////
// CvwPONotesWithName diagnostics

#ifdef _DEBUG
void CvwPONotesWithName::AssertValid() const
{
	CRecordset::AssertValid();
}

void CvwPONotesWithName::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


