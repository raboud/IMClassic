#pragma once

#include <afxtempl.h>
#include "SetOrders.h"	// Added by ClassView
#include "SetCustomer.h"	// Added by ClassView
#include "Flooring.h"

class CWorkOrderHelper
{
public:
	CWorkOrderHelper(void);
	~CWorkOrderHelper(void);

	bool SetPoList(CPoList* listPOs);

	//bool ViewReport(void);      // show the report, user can print if desired
	//bool PrintReport(void);     // just print it

	CString m_strErrorMessage;

	CString GetPOList();          // gets string list of PO Numbers for the report.
	CString GetScheduledDate();   // gets formatted scheduled date
	CString GetCustomerID();      // gets Cust. ID in string format
	CString GetShowStorePickup(); 

protected:

	void InitializeFilters(void);

	bool SetParameters(void);

	CPoList m_PoList;
	CSetCustomer m_setCustomer;
	CSetOrders m_setOrders;

	bool m_bAM;
	bool m_bScheduled;
	COleDateTime m_dateScheduled;
	int m_iCustomerID;
	bool m_bHasStorePickup;

	CString m_strPOList;          // list of POs for CR.

	//CReportDialog m_ReportDlg;

	bool HasAlerts(int iOrderID);

};
