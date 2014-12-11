// SetSubContractorsDivisionAssignments.h : Implementation of the CSetSubContractorsDivisionAssignments class



// CSetSubContractorsDivisionAssignments implementation

// code generated on Tuesday, June 17, 2003, 3:22 PM

#include "stdafx.h"
#include "SetSubContractorsDivisionAssignments.h"
IMPLEMENT_DYNAMIC(CSetSubContractorsDivisionAssignments, CRecordset)

CSetSubContractorsDivisionAssignments::CSetSubContractorsDivisionAssignments(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_SubContractorID = 0;
	m_DivisionID = 0;
	m_SubDivisionID = 0;
	m_nFields = 4;
	m_nDefaultType = dynaset;
}

CString CSetSubContractorsDivisionAssignments::GetDefaultSQL()
{
	return _T("[dbo].[SubContractorsDivisionAssignments]");
}

void CSetSubContractorsDivisionAssignments::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[SubContractorID]"), m_SubContractorID);
	RFX_Long(pFX, _T("[DivisionID]"), m_DivisionID);
	RFX_Long(pFX, _T("[SubDivisionID]"), m_SubDivisionID);

}
/////////////////////////////////////////////////////////////////////////////
// CSetSubContractorsDivisionAssignments diagnostics

#ifdef _DEBUG
void CSetSubContractorsDivisionAssignments::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetSubContractorsDivisionAssignments::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


