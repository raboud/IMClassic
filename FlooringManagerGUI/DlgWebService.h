/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once
#include "afxwin.h"


// CDlgWebService dialog

class CDlgWebService
{

public:
	CDlgWebService();   // standard constructor
	virtual ~CDlgWebService();

	bool SPNUpdatePO(CPoList* pListPOs);
	bool SPNUpdatePO(CString strStoreNumber, CString strPONumber);

};
