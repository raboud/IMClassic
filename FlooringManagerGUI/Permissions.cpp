/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#include "stdafx.h"
#include "flooring.h"
#include "permissions.h"
#include "SetNoteTypes.h"

const int iEXPLICIT_PERMISSIONTYPE = 5;

using namespace CFI::InstallationManager::Business;

CPermissions::CPermissions(void)
{
	CFlooringApp* pApp = (CFlooringApp*) AfxGetApp() ;
	m_iUserID = pApp->GetEmployeeID();
	m_bIsAdmin = pApp->IsAdmin();
}

CPermissions::~CPermissions(void)
{
}

bool CPermissions::HasPermission(const CString strPermission)
{
	UserBLL^ userBll = gcnew UserBLL(m_iUserID, CachedData::Context);
	bool bOK = userBll->HasPermission(gcnew System::String(strPermission));
	return bOK;
}

bool CPermissions::HasPermission(const CString strPermission, int iMarketID, int iDivisionID)
{
	UserBLL^ userBll = gcnew UserBLL(m_iUserID, CachedData::Context);
	bool bOK = userBll->HasPermission(iMarketID, iDivisionID, gcnew System::String(strPermission));
	return bOK;
}

bool CPermissions::HasNoteTypePermission(const CString strNoteType)
{
	UserBLL^ userBll = gcnew UserBLL(m_iUserID, CachedData::Context);
	bool bOK = userBll->HasNoteTypePermission(gcnew System::String(strNoteType));
	return bOK;
}