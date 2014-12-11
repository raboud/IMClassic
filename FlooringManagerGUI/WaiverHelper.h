#pragma once

#include <afxtempl.h>

#include "SetOrders.h"	// Added by ClassView
#include "SetCustomer.h"	// Added by ClassView
#include "Flooring.h"

class CWaiverHelper
{
public:
	CWaiverHelper(void);
	~CWaiverHelper(void);

	bool SetPoList(CPoList* listPOs);
	CString GetScheduledAM();
	CString GetScheduledDate();
	CString GetShowAMPM();

	CString m_strErrorMessage;

protected:

	void InitializeFilters(void);
	//bool SetParameters(void);

	CPoList m_PoList;
	CSetCustomer m_setCustomer;
	CSetOrders m_setOrders;

	bool m_bAM;
	bool m_bScheduled;
	COleDateTime m_dateScheduled;

	CString m_strPOList;          // list of POs for CR.
};
