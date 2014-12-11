/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#ifndef _CGlobals_h
#define _CGlobals_h

#include <afxtempl.h>
typedef CList<int, int> CPoList;

class CGlobals
{
public:
	CGlobals(void);
	~CGlobals(void);

	static const int iSOSI_INSTALL_SCHEDULE_UPDATE_DOC_ID = 20;
	static const int iSOSI_COMMUNICATE_INSTALL_SERVICE_COMPLETE_DOC_ID = 13;
	static const int iSOSI_VERIFY_PRODUCT_RECEIPT_DOC_ID = 22;
	static const int iSOSI_MEASURE_RESCHEDULE_WITH_DATE_DOC_ID = 8;

	static const COLORREF COLOR_BLUE					= RGB(  0,   0, 255) ;  // blue
	static const COLORREF COLOR_BLACK					= RGB(0,     0,   0) ;  // black
	static const COLORREF COLOR_WHITE					= RGB(255, 255, 255) ;  // white
	static const COLORREF COLOR_RED						= RGB(255,   0,   0) ;  // red

	static const COLORREF COLOR_ALERT					= RGB(255, 255,   0) ;  // yellow
	static const COLORREF COLOR_MANUAL					= RGB(0,     0,	  0) ;		// black
	static const COLORREF COLOR_IMPORTED				= RGB(0,     0, 255) ;		// blue
	static const COLORREF COLOR_IMPORTED_HAND_MODIFIED	= RGB(175, 160,  12) ;		// green
	static const COLORREF COLOR_XML_DELETED_TEXT		= RGB(255,   0,   0) ;		// red
	static const COLORREF COLOR_XML_DELETED_BACK		= RGB(255, 255, 255) ;		// white
	static const COLORREF COLOR_MANUAL_DELETED_TEXT		= RGB(0,     0,   0) ;		// black
	static const COLORREF COLOR_MANUAL_DELETED_BACK		= RGB(255,   0,   0) ;		// red
	static const COLORREF COLOR_NORMAL_BACK				= RGB(255, 255, 255) ;		// white

	static const COLORREF COLOR_SCHEDULED				= RGB(255,   0, 255) ;
	static const COLORREF COLOR_INV_PAID				= RGB(  0, 255,   0) ;
	static const COLORREF COLOR_INVOICED				= RGB(255,   0, 255) ;
	static const COLORREF COLOR_PAID					= RGB(  0, 255,   0) ;
	static const COLORREF COLOR_CANCELED				= RGB(255,   0,   0) ;
	static const COLORREF COLOR_WARRENTY				= RGB(  0,   0, 255) ;
	static const COLORREF COLOR_WAR_COMP				= RGB(  0,   0, 255) ;
	static const COLORREF COLOR_NO_MATER				= RGB(128, 128, 128) ;

	static const int ACTIVITY_CHANGED_PO_RECEIVED			= 1;
	static const int ACTIVITY_CANCELLED_PO_RECEIVED			= 2;
	static const int ACTIVITY_SPACTION_RECEIVED				= 3;
	static const int ACTIVITY_MEASURE_APPT_RESCHEDULED		= 4;
	static const int ACTIVITY_SCHEDULE_WILL_CALL_RECEIVED	= 5;
	static const int ACTIVITY_UPDATE_MEASURE_CAPACITY		= 6;
	static const int ACTIVITY_XML_ERROR_RECEIVED			= 7;
	static const int ACTIVITY_CALL_CUSTOMER					= 8;
	static const int ACTIVITY_INSTALL_SCHEDULE_UPDATE		= 9;
	static const int ACTIVITY_COMPLETE_SERVICE				= 10;
	static const int ACTIVITY_PRODUCT_PICKED_UP				= 11;
	static const int ACTIVITY_COMPLETE_SERVICE_FAILED		= 12;
	static const int ACTIVITY_BADGE_EXPIRATION				= 13;
	static const int ACTIVITY_PRODUCT_CHANGED_PO_RECEIVED	= 14;
	static const int ACTIVITY_SCHEDULE_UPDATE_FAILED		= 15;
	static const int ACTIVITY_CSFOLLOWUPDATED_FAILED		= 16;

	static const int ENTRY_MANUAL							= 1;
	static const int ENTRY_SPN_IMPORTED						= 2;
	static const int ENTRY_SPN_IMPORTED_HANDMODIFIED		= 3;
	static const int ENTRY_SPN_IMPORTED_XMLDELETED			= 4;
	static const int ENTRY_SOSI_IMPORTED					= 5;
	static const int ENTRY_SOSI_IMPORTED_HANDMODIFIED		= 6;
	static const int ENTRY_SOSI_IMPORTED_XMLDELETED			= 7;

	static const int NOTETYPE_NOTETOEXPEDITOR				= 2;

	static const int iMAX_ACTIVITY_DATA = 1024;
	static const int iMAX_ORDER_NOTES = 2500 ;
	static const int iMAX_PO_NUMBER = 8 ;
	static const int iMAX_SO_NUMBER = 8 ;
	static const int iMAX_ORDERID_DIGITS = 9;  // orderid is a long, which the max number has 10 digits
	static const int iMAX_CUSTID_DIGITS = 9;  // customerid is a long
	static const int iMAX_CUSTOMER_DIRECTIONS = 2000 ;

	static const int iMAX_RICHEDIT_FIELD_LENGTH = 20000;

	static const UINT WM_USER_RICHEDITCHANGE			 = WM_USER + 0x100 ;
	static const UINT WM_USER_RICHEDITLOSEFOCUS			 = WM_USER + 0x101 ;
	//static const UINT WM_USER_USER_ALERTS_VIEW_DESTROYED = WM_USER + 0x102 ;
	static const UINT WM_USER_USER_ALERTS_DLG_DESTROYED = WM_USER + 0x102 ;
	//static const UINT WM_USER_ACTIVE_POS_VIEW_DESTROYED	 = WM_USER + 0x103 ;
	static const UINT WM_USER_ACTIVE_POS_DLG_DESTROYED   = WM_USER + 0x103 ;
	//static const UINT wm_ACTIVITY_LIST_VIEW_DESTROYED	 = WM_USER + 0x104 ;
	static const UINT WM_ACTIVITY_LIST_DLG_DESTROYED	 = WM_USER + 0x104 ;
	static const UINT WM_ACTIVITY_DATA_UPDATE			 = WM_USER + 0x105 ;
	static const UINT WM_LABOR_UPDATE					 = WM_USER + 0x106 ;
	static const UINT WM_CHECK_FOR_IM_UPDATES			 = WM_USER + 0x107 ;	

	static const int DISC_CUSTOMER = 2;    // customer type discrepancy

	static CString POFromOrderID(int iOrderID);
	static long POtoStoreId (CString strPO) ;
	static CString POtoStoreNumber (CString strPO, CString strCurrentStoreNumber = "") ;
	static CString StoreNumberFromOrderID(int iOrderID);
	static long OrderIDFromPOAndStoreNumber(CString strPO, CString strStoreNumber);
	static long OrderIDFromSONumberAndStoreNumber(CString strSO, CString strStoreNumber);
	static long OrderIDFromPOAndStoreID(CString strPO, long iStoreNumber);
	static int StoreIDFromStoreNumber(CString strStoreNumber);
	static CString StoreNumberFromStoreID(int iStoreID);
	static int StoreTypeIDFromStoreNumber(CString strStoreNumber);
	static int MarketIDFromStoreNumber(CString strStoreNumber);
	static long CustomerIDFromOrderID(int iOrderID);
	static bool POInUse(CString strPO, CString strStoreNumber);
	static bool POInUse(CString strPO, CString strStoreNumber, int& iOrderID);
	static bool MarketAndDivisionFromOrderID(int iOrderID, int& iMarketID, int& iDivisionID);
	static int DivisionIDFromMaterialTypeID(int iMaterialTypeID);
	static int MarketIDFromStoreID(int iStoreID);
	static bool IsSOSI(int iOrderID);
	static CString GetEntryMethodText(int iOrderID);
	static CString GetBooleanString(bool BooleanValue);

	static void GetUserSetting(const CString& strSetting, bool& bValue, bool bDefault = false) ;
	static void GetUserSetting(const CString& strSetting, CString& strValue, const CString& strDefault = "") ;
	static void SetUserSetting(const CString& strSetting, bool bValue) ;
	static void SetUserSetting(const CString& strSetting, const CString& strValue) ;

	static COleDateTime GetCurrentSystemTime();

	static bool CustomerHasAlerts(int iCustomerID);
	static bool OrderHasAlerts(int iOrderID, bool bIncludeAllCustomerAlerts = false);
	static bool OrderHasCustomerAlerts(int iOrderID);
	static bool OrderHasSOMerchandiseAlerts(int iOrderID);
	static bool OrderHasRegMerchandiseAlerts(int iOrderID);
	static bool OrderHasNotesAlerts(int iOrderID);
	static bool OrderIsReviewed(int iOrderID);
	static bool OrderIsCancelled(int iOrderID);
	static bool OrderIsDeleted(int iOrderID);
	static CString CustomerNameFromCustomerID(int CustomerID);
	static bool IsInstall(int iOrderID, bool &bIsInstall);
	static bool HasStorePickup(CPoList* plistPOs);
	static bool HasStorePickup(long lOrderID);

	static CString GetTitleName(int iTitleID);

	static CString GetCurrentUserSMTPEmailAddress();
	static CString GetCurrentUserReplyToEmailAddress();

	static bool SendEmail(CString strTo, CString strFrom, CString strPassword, CString strCC, CString strReplyToAddr, CString strSubject, CString strBody, CString &strError);
	static CString GetUserEmailPassword();

	static bool RequiresWoodWaiver(int OrderID);

	static bool QueueNoteForExpeditor(int NoteID, bool CopyToSASM, bool CopyToExpeditorEmail);
	static bool QueueSchedulePO(int OrderID) ;
    static bool QueueClosePO(int OrderID, COleDateTime date);
    static bool QueueProductReceipt(int soID);

// .Net Wrappers
	static bool SPNUpdatePO(CPoList* pListPOs);
	static bool SPNUpdatePO(CString strStoreNumber, CString strPONumber);
	static CString InitDefaultContext();

	
	static void PrintPONote(int iNoteID);
	static void PrintCustSatReport(int iReportID);
	static void ViewCustSatReport(int iReportID);

//	static void PrintPO(int iOrderID);
//	static void ViewPO(int iOrderID);
//	static void PrintReviewChecklist(int OrderID);	
//	static void PrintSchedulingChecklist(int OrderID);	
//	static void PrintWoodFlooringWaiver(int OrderID);
	static void PrintCheck(int iCheckID);
	static void ViewCheck(int iCheckID);

//	static void ViewWoodFlooringWaiver(int OrderID, bool PrintOnly = false);

	static void PayrollReport(CString strGrandTotal, COleDateTime timeWE);
	static void SetEmployeeID();
	static void SetEmployeeID(int ID);
	static void ViewJobAssign();
	static bool CanViewJobAssign();
	static bool IsAdmin() ;
	static CString GetUserFirstAndLastName();

	static int m_iUserID;
	static CString m_strUserName;
	static bool m_bAdmin;		
	static int GetEmployeeID();

	static void OnReportsPulllist();
	static void OnReportsCompletedJobsNotPaid();
	static void OnReportsChargebacksByDate();
	static void OnReportsFIConsumption();
	static void OnReportsBillingCover();
	static void OnReportSchedule();
	static void OnSubHelpers();
	static void OnViewUseralerts();	
	static void OnWorkmansCompByDate();
	static void OnLiabilityByDate();
	static void OnHelpReportissue();
	static void OnViewActivePOs();
	static void OnViewActivitylist();
	static void OnMaterialsDamaged();
	static void OnReportsSubPhonelist();
	static void OnBackgroundChecksAlphaByLastName();
	static void OnJobsAssignments();
	static void OnPayrollMessages();
	static void OnStoreInfo();
	static void OnOverdueInvoices();
	static void OnOpenInvoices();
	static void OnReportsBilling();
	static void OnWarrantySched();
	static void OnWarrantyOpen();
	static void OnMaterialRa();
	static void OnMaterialsNotreceivedyet();
	static void OnReportsStatusSingle();
	static void OnReportsWorkSummaryByWeek();
	static void OnReportsPending();
	static void OnReportsWeeklyTotals();
	static void OnNotBilled();
	static void OnInventory();
	static void OnWorkmanscompBydate();
	static void OnWorkmanscompByname();
	static void OnCriminalCheckName();
	static void OnReportsStatus();
	static void SetAdmin();

	static BOOL ValidateMinimumVersion( CString strVersion );
	static CString GetComputerName();

	static bool HasPermission(const CString strPermission);
	static bool HasPermission(const CString strPermission, int iMarketID, int iDivisionID);
	static bool HasPermissionMarket(const CString strPermission, int iMarketID);
	static bool HasPermissionDivision(const CString strPermission, int iDivisionID);
	static bool HasNoteTypePermission(const CString strNoteType);

	static bool GetBasicPrices(int iBasicLaborID, COleDateTime OrderDate, COleDateTime ScheduleDate, int iStoreID, double& dCost, double& dPrice);
	static bool GetOptionPrices(int iOptionID, COleDateTime OrderDate, COleDateTime ScheduleDate, int iStoreID, double& dCost, double& dPrice);

	enum PRINT_MODE {PM_INVOICE = 0, PM_WORKORDER, PM_WAIVER, PM_DIAGRAMS, PM_STORE_PICKUP, PM_INSPECTION, PM_PO, PM_WOODWAIVER, PM_INSTALLER_CHECKLIST, PM_REVIEW_CHECKLIST, PM_SCHEDULE_CHECKLIST, PM_MEASURE, PM_ALL} ;
	static void PreparePaperWork(int po, PRINT_MODE enMode, bool PrintOnly = false);
	static void PreparePaperWork(CPoList* listPOs, PRINT_MODE enMode, bool PrintOnly = false);
};

inline bool CGlobals::HasPermissionMarket(const CString strPermission, int iMarketID)
{
	return HasPermission(strPermission, iMarketID, -1);
}

inline bool CGlobals::HasPermissionDivision(const CString strPermission, int iDivisionID)
{
	return HasPermission(strPermission, -1, iDivisionID);
}

#endif