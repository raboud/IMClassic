/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetInstallerError.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "SetInstallerError.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetInstallerError

IMPLEMENT_DYNAMIC(CSetInstallerError, CRecordset)

CSetInstallerError::CSetInstallerError(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetInstallerError)
	m_Id = 0;
	m_Description = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CSetInstallerError::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetInstallerError::GetDefaultSQL()
{
	return _T("[dbo].[Installer Error]");
}

void CSetInstallerError::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetInstallerError)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Long(pFX, _T("[Id]"), m_Id);
	RFX_Text(pFX, _T("[Description]"), m_Description);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetInstallerError diagnostics

#ifdef _DEBUG
void CSetInstallerError::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetInstallerError::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
