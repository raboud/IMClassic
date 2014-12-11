/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once

class CPermissions
{
public:
	CPermissions(void);
	~CPermissions(void);

	bool IsAdmin();

	bool HasPermission(CString strPermission);
	bool HasPermission(CString strPermission, int iMarketID, int iDivisionID);
	bool HasPermissionMarket(CString strPermission, int iMarketID);
	bool HasPermissionDivision(CString strPermission, int iDivisionID);
	bool HasNoteTypePermission(CString strNoteType);

protected:
	int m_iUserID;
	bool m_bIsAdmin;
};

inline bool CPermissions::IsAdmin()
{
	return m_bIsAdmin;
}

inline bool CPermissions::HasPermissionMarket(CString strPermission, int iMarketID)
{
	return HasPermission(strPermission, iMarketID, -1);
}

inline bool CPermissions::HasPermissionDivision(CString strPermission, int iDivisionID)
{
	return HasPermission(strPermission, -1, iDivisionID);
}
