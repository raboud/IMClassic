/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// Flooring.h : main header file for the FLOORING application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include <afxinet.h>
#include "resource.h"       // main symbols

#include "DlgUserAlerts.h"
#include "DlgActivePOs.h"
#include "DlgActivityList.h"

const UINT wm_UPDATE_USER_ALERTS = RegisterWindowMessage( "Update User Alerts" ) ;
const UINT wm_TAB_COLOR_UPDATE = RegisterWindowMessage( "Tab Color Update" ) ;
const UINT wm_SendEmailError = RegisterWindowMessage( "Error Sending Email" ) ;

const char szWO_NOTES[] = "WO Notes";
const char szSPN_NOTES[] = "HD Notes";
//const char szINTERNAL_NOTES[] = "Internal Notes";

//#include <afxtempl.h>
//typedef CList<int, int> CPoList;

extern CDatabase g_dbFlooring;

//enum EnLocation {EnLocation_REORDER, EnLocation_NOT_PRESENT = 0, EnLocation_PRESENT, EnLocation_AT_SITE, EnLocation_STORE_PICKUP} ;

inline double Currency (double fAmount, bool bRound = true)
{
	long lAmount = 0;

	
	if (bRound)
	{
		if (fAmount > 0)
		{
			lAmount = int((fAmount * 100.) + .5000000001) ;
		}
		else if (fAmount < 0)
		{
			lAmount = int((fAmount * 100.) - .5000000001) ;
		}

	}
	else
	{
		lAmount = int(fAmount * 100.) ;
	}
	return double(lAmount / 100.) ;
}

//CString POFromOrderID(int iOrderID);


/////////////////////////////////////////////////////////////////////////////
// CFlooringApp:
// See Flooring.cpp for the implementation of this class
//

class CFlooringApp : public CWinApp
{
public:
	CString GetCFUserName();
	CFlooringApp();
	~CFlooringApp();

//	CString GetEmailPassword();
//	void SetEmailPassword(CString strPassword);

	CDlgUserAlerts* m_pDlgUserAlerts;
	CDlgActivePOs* m_pDlgActivePOs;
	CDlgActivityList* m_pDlgActivityList;

	void ImpersonateUser();
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlooringApp)
	public:
	virtual int Run();
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CFlooringApp)
	afx_msg void OnAppAbout();
	afx_msg void OnViewStores();
	afx_msg void OnViewSubcontractors();
	afx_msg void OnViewCustomerPo();
	afx_msg void OnInvoicing();
	afx_msg void OnBillingReceivecheck();
	afx_msg void OnUpdateBillingReceivecheck(CCmdUI* pCmdUI);
	afx_msg void OnUpdateInvoicing(CCmdUI* pCmdUI);
	afx_msg void OnBillingChargebacks();
	afx_msg void OnPayroll();
	afx_msg void OnUpdatePayroll(CCmdUI* pCmdUI);
	afx_msg void OnUpdateReportsBilling(CCmdUI* pCmdUI);
	afx_msg void OnMaterialsChangestatus();
	afx_msg void OnUpdateReportsWorkSummaryByWeek(CCmdUI* pCmdUI);
	afx_msg LRESULT OnCustomerSelected (WPARAM, LPARAM);
	afx_msg void OnUpdateSubHelpers(CCmdUI *pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	

protected:
	int m_iDBVersion;

	CMultiDocTemplate* m_pTemplateCustomerPO;

	SQLHANDLE m_shSQLEnv ;
public:
	afx_msg void OnUpdateReportsPending(CCmdUI *pCmdUI);
	afx_msg void OnUpdateReportNotBilled(CCmdUI *pCmdUI);
	afx_msg void OnUpdateReportsWeeklytotals(CCmdUI *pCmdUI);
	afx_msg void OnUpdateReportOpenInvoice(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOverdueInvoices(CCmdUI *pCmdUI);
	afx_msg void OnUpdateReportsPulllist(CCmdUI *pCmdUI);
	afx_msg void OnUpdateReportsChargebacksbydate(CCmdUI *pCmdUI);
	afx_msg void OnUpdateReportsChargebacksIssued(CCmdUI *pCmdUI);
	afx_msg void OnUpdateReportsCompletedjobsnotpaid(CCmdUI *pCmdUI);
	afx_msg void OnUpdateReportsStatus(CCmdUI *pCmdUI);
	afx_msg void OnUpdateReportsStatusSingle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateReportsStatusSummary(CCmdUI *pCmdUI);
	afx_msg void OnUpdateReportsStatusSingleSummary(CCmdUI *pCmdUI);
	afx_msg void OnUpdateWarrantyOpen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateWarrantySched(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCriminalCheckDate(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCriminalCheckName(CCmdUI *pCmdUI);
	afx_msg void OnUpdateWorkmanscompBydate(CCmdUI *pCmdUI);
	afx_msg void OnUpdateWorkmanscompByname(CCmdUI *pCmdUI);
	afx_msg void OnUpdateInventory(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMaterialsNotreceivedyet(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMaterialRa(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBillingChargebacks(CCmdUI *pCmdUI);
	afx_msg void OnUpdateReportsSubPhonelist(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBackgroundChecksAlphaByLastName(CCmdUI *pCmdUI);
	afx_msg void OnUpdateJobsAssignments(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePayrollMessages(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMaintenanceUnitTests(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMaintenanceSpndiscrepancies(CCmdUI *pCmdUI);
	afx_msg void OnUpdateWorkmansCompByDate(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLiabilityByDate(CCmdUI *pCmdUI);
	afx_msg void OnUpdateViewJobAssign(CCmdUI *pCmdUI);

	afx_msg void OnMaintenanceSpndiscrepancies();
	afx_msg void OnMaintenanceUnitTests();
	afx_msg void OnFileSetEmailPassword();

	afx_msg void OnReportsPulllist();
	afx_msg void OnReportsCompletedJobsNotPaid();
	afx_msg void OnReportsChargebacksByDate();
	afx_msg void OnReportsChargebacksIssued();
	afx_msg void OnReportsFIConsuption();
	afx_msg void OnReportSchedule();
	afx_msg void OnReportBillingCover();
	afx_msg void OnSubHelpers();
	afx_msg void OnViewUseralerts();	
	afx_msg void OnWorkmansCompByDate();
	afx_msg void OnLiabilityByDate();
	afx_msg void OnHelpReportissue();
	afx_msg void OnViewActivePOs();
	afx_msg void OnViewJobAssign();
	afx_msg void OnViewActivitylist();
	afx_msg void OnMaterialsDamaged();
	afx_msg void OnReportsSubPhonelist();
	afx_msg void OnBackgroundChecksAlphaByLastName();
	afx_msg void OnJobsAssignments();
	afx_msg void OnPayrollMessages();

	afx_msg void OnStoreInfo();
	afx_msg void OnOverdueInvoices();
	afx_msg void OnOpenInvoices();
	afx_msg void OnReportsBilling();
	afx_msg void OnWarrantySched();
	afx_msg void OnWarrantyOpen();
	afx_msg void OnMaterialRa();
	afx_msg void OnMaterialsNotreceivedyet();
	afx_msg void OnReportsStatusSingle();
	afx_msg void OnReportsWorkSummaryByWeek();
	afx_msg void OnReportsPending();
	afx_msg void OnReportsWeeklyTotals();
	afx_msg void OnNotBilled();
	afx_msg void OnInventory();
	afx_msg void OnWorkmanscompBydate();
	afx_msg void OnWorkmanscompByname();
	afx_msg void OnCriminalCheckName();
	afx_msg void OnReportsStatus();
};

int DownloadDrawing(CString strNumber, CString strTimeStamp) ;
DWORD GetPage(CHttpConnection* pConnection, CString strUrl, CString strHeaders, CString strFormData, CString &buffer, HANDLE heMail = NULL) ;
DWORD GetPage(CHttpConnection* pConnection, CString strUrl, CString strHeaders, CString strFormData, CString &buffer, DWORD &dwTotalWritten, HANDLE heMail = NULL) ;
int DownloadDrawingList(CString strNumber, CString& strTimeStamp) ;
CString GetDrawingURL(CString strSubString);

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
