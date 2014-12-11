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

	bool HasPermission(const CString strPermission);
	bool HasPermission(const CString strPermission, int iMarketID, int iDivisionID);
	bool HasPermissionMarket(const CString strPermission, int iMarketID);
	bool HasPermissionDivision(const CString strPermission, int iDivisionID);
	bool HasNoteTypePermission(const CString strNoteType);
};

inline bool CPermissions::HasPermissionMarket(const CString strPermission, int iMarketID)
{
	return HasPermission(strPermission, iMarketID, -1);
}

inline bool CPermissions::HasPermissionDivision(const CString strPermission, int iDivisionID)
{
	return HasPermission(strPermission, -1, iDivisionID);
}
