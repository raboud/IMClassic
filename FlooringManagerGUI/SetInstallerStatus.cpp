// SetInstallerStatus.h : Implementation of the CSetInstallerStatus class

// CSetInstallerStatus implementation

// code generated on Tuesday, August 12, 2003, 10:59 AM

#include "stdafx.h"
#include "SetInstallerStatus.h"
IMPLEMENT_DYNAMIC(CSetInstallerStatus, CRecordset)

CSetInstallerStatus::CSetInstallerStatus(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_Status = _T("");
	m_nFields = 2;
	m_nDefaultType = dynaset;
}

CString CSetInstallerStatus::GetDefaultConnect()
{
	return _T("ODBC; DSN=Flooring;");
}

CString CSetInstallerStatus::GetDefaultSQL()
{
	return _T("[dbo].[InstallerStatus]");
}

void CSetInstallerStatus::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Status]"), m_Status);

}
/////////////////////////////////////////////////////////////////////////////
// CSetInstallerStatus diagnostics

#ifdef _DEBUG
void CSetInstallerStatus::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetInstallerStatus::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


