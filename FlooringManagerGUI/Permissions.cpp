/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#include "stdafx.h"
#include "flooring.h"
#include "permissions.h"
#include "SetNoteTypes.h"

const int iEXPLICIT_PERMISSIONTYPE = 5;

CPermissions::CPermissions(void)
: m_setVwUserPermissions(&g_dbFlooring),
  m_setPermissions(&g_dbFlooring)
{
	m_setVwUserPermissions.m_strFilter = "ID = -1";
	m_setVwUserPermissions.Open();

	m_setPermissions.m_strFilter = "ID = -1";
	m_setPermissions.Open();

	CFlooringApp* pApp = (CFlooringApp*) AfxGetApp() ;
	m_iUserID = pApp->GetEmployeeID();
	m_bIsAdmin = pApp->IsAdmin();
}

CPermissions::~CPermissions(void)
{
	if (m_setVwUserPermissions.IsOpen()) m_setVwUserPermissions.Close();
}

bool CPermissions::HasPermission(CString strPermission)
{
	bool bOK = false;

	// make sure the permission even exists
	m_setPermissions.m_strFilter.Format("PermissionName = '%s'", strPermission);
    m_setPermissions.Requery();
	if (!m_setPermissions.IsEOF())
	{
		// if looking for a explicit permission, check for it, don't look at whether or not we are admin
		if (m_setPermissions.m_PermissionType == iEXPLICIT_PERMISSIONTYPE)
		{
			bOK = HasExplicitPermission(strPermission);
		}
		else
		{
			// if we are admin and not looking at a specific permission type, then return true else check for the
			// permission
			if (m_bIsAdmin)
			{
				bOK = true;
			}
			else
			{
				bOK = HasExplicitPermission(strPermission);
			}
		}
	}
	else
	{
		// permission doesn't exist - show assertion screen
#ifdef _DEBUG
		MessageBox(NULL, "Permission Does Not Exist!", "Error!", MB_OK);
#endif
	}

	return bOK;
}

bool CPermissions::HasExplicitPermission(CString strPermission)
{

	// doesn't care if you have admin privs or not - you must have this permission set to return true
	bool bOK = false;

	m_setVwUserPermissions.m_strFilter.Format("ID = %d AND PermissionName = '%s'", m_iUserID, strPermission);
	m_setVwUserPermissions.Requery();

	if ( !m_setVwUserPermissions.IsEOF() )
	{
		bOK = true;
	}

	return bOK;
}

bool CPermissions::HasPermission(CString strPermission, int iMarketID, int iDivisionID)
{
	bool bOK = false;

	// make sure the permission even exists
	m_setPermissions.m_strFilter.Format("PermissionName = '%s'", strPermission);
    m_setPermissions.Requery();
	if (!m_setPermissions.IsEOF())
	{
		CString strFilter;
		CString strTemp = "";
		strFilter.Format("ID = %d AND PermissionName = '%s'", m_iUserID, strPermission);

		if (iMarketID != -1)
		{
			strTemp.Format(" AND (Market = '%d' or Market = '-1')", iMarketID);
			strFilter += strTemp;
		}

		if (iDivisionID != -1)
		{
			strTemp.Format(" AND (Division = '%d' OR Division = '-1')", iDivisionID);
			strFilter += strTemp;
		}

		m_setVwUserPermissions.m_strFilter = strFilter;
		m_setVwUserPermissions.Requery();

		if (m_setPermissions.m_PermissionType == iEXPLICIT_PERMISSIONTYPE)
		{
			if ( !m_setVwUserPermissions.IsEOF() )
			{
				bOK = true;
			}
		}
		else
		{
			if (m_bIsAdmin) return true;

			if ( !m_setVwUserPermissions.IsEOF() )
			{
				bOK = true;
			}
		}
	}
	else
	{
		// permission not found
#ifdef _DEBUG
		MessageBox(NULL, "Permission Does Not Exist!", "Error!", MB_OK);
#endif
	}

	return bOK;
}

void CPermissions::Refresh()
{
	m_setVwUserPermissions.m_strFilter = "ID = -1";
	if (m_setVwUserPermissions.IsOpen())
	{
		m_setVwUserPermissions.Close();
	}
	m_setVwUserPermissions.Open();

	m_setPermissions.m_strFilter = "ID = -1";
	if (m_setPermissions.IsOpen())
	{
		m_setPermissions.Close();
	}
	m_setPermissions.Open();

	CFlooringApp* pApp = (CFlooringApp*) AfxGetApp() ;
	m_iUserID = pApp->GetEmployeeID();
	pApp->SetAdmin();
	m_bIsAdmin = pApp->IsAdmin();
}

bool CPermissions::HasNoteTypePermission(CString strNoteType)
{
	CSetNoteTypes setNoteType(&g_dbFlooring);
	setNoteType.m_strFilter.Format("NoteTypeDescription = '%s'", strNoteType);
	setNoteType.Open();
	if (!setNoteType.IsEOF())
	{
		if (setNoteType.m_PermissionRequiredToSelect)
		{
			strNoteType.Remove(' ');
			CString strPermissionName;
			strPermissionName.Format("CanSelectNoteType_%s", strNoteType);
			return HasPermission(strPermissionName);
		}
	}

	return true;
}