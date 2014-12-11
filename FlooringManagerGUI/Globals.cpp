/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#include "stdafx.h"
#include "Globals.h"
#include "SetOrders.h"
#include "SetStores.h"
#include "Flooring.h"
#include "SetMaterialType.h"
#include "SetSettings.h"
#include "SetStores.h"
#include "DlgStoreSelection.h"
#include "SetDiscrepancies.h"
#include "SetVwOrdersWithDiscrepancies.h"
#include "SetViewOrderSOMerchandiseDetails.h"
#include "SetViewOrderRegMerchandiseDetails.h"
#include "SetCustomer.h"
#include "SetContactTitles.h"
#include "SetEmployees.h"
#include "SetOrderSOMerchandiseDetails.h"
#include "SetVwMaterialsRequiringWoodWaiver.h"
#include "DlgPassword.h"
#include "Logger.h"

#import "mailbee.dll" no_namespace

extern CDatabase g_dbFlooring;

using namespace CFI::Utility::Mail;
using namespace CFI::InstallationManager::Business;

CGlobals::CGlobals(void)
{
}

CGlobals::~CGlobals(void)
{
}

CString CGlobals::POFromOrderID(int iOrderID)
{
	CString strPONumber = "";

	CSetOrders setOrders(&g_dbFlooring) ;
	setOrders.m_strFilter.Format("[OrderId] = '%d'", iOrderID) ;
	setOrders.Open();
	if (!setOrders.IsEOF())
	{
		strPONumber = setOrders.m_PurchaseOrderNumber;						
	}
	setOrders.Close();

	return strPONumber;
}

long CGlobals::POtoStoreId (CString strPO) 
{
	strPO.TrimRight() ;

	CSetStores setStores(&g_dbFlooring) ;
	CString strStoreNumber = CGlobals::POtoStoreNumber(strPO);
	if ( strStoreNumber.GetLength() > 0 )
	{
		setStores.m_strFilter = "[StoreNumber] = " + CGlobals::POtoStoreNumber(strPO) + "'" ;
		setStores.Open() ;
		long storeID = setStores.m_StoreID ;
		setStores.Close() ;
		return storeID ;
	}
	else
	{
		return -1;
	}
}

long CGlobals::OrderIDFromPOAndStoreID(CString strPO, long lStoreID)
{
	long lOrderID = -1;
	CSetOrders setOrders(&g_dbFlooring);
	setOrders.m_strFilter.Format("PurchaseOrderNumber = '%s' AND StoreID = %d", strPO, lStoreID);
	setOrders.Open();
	if (!setOrders.IsEOF())
	{
		lOrderID = setOrders.m_OrderID;
	}
	setOrders.Close();

	return lOrderID;
}

long CGlobals::OrderIDFromPOAndStoreNumber(CString strPO, CString strStoreNumber)
{
	long lStoreID = CGlobals::StoreIDFromStoreNumber(strStoreNumber);
	return CGlobals::OrderIDFromPOAndStoreID(strPO, lStoreID);	
}

long CGlobals::OrderIDFromSONumberAndStoreNumber(CString strSO, CString strStoreNumber)
{
	long lOrderID = -1;
	//int iStoreID = CGlobals::StoreIDFromStoreNumber(strStoreNumber);
	CSetOrderSOMerchandiseDetails setSO(&g_dbFlooring);
	setSO.m_strFilter.Format("SONumber = '%s'", strSO);
	setSO.m_strSort.Format("SONumber, OrderID");
	setSO.Open();
	while (!setSO.IsEOF())
	{
		if (strStoreNumber == CGlobals::StoreNumberFromOrderID(setSO.m_OrderID))
		{
			// only return orderid if it's not marked deleted
			if (!OrderIsDeleted(setSO.m_OrderID))
			{
				lOrderID = setSO.m_OrderID;
				break;
			}
		}
		setSO.MoveNext() ;
	}
	setSO.Close();
	return lOrderID;
}

long CGlobals::CustomerIDFromOrderID(int iOrderID)
{
	long lCustID = -1;
	CSetOrders setOrders(&g_dbFlooring);
	setOrders.m_strFilter.Format("OrderID = %d", iOrderID);
	setOrders.Open();
	if (!setOrders.IsEOF())
	{
		lCustID = setOrders.m_CustomerID;
	}
	setOrders.Close();

	return lCustID;
}


void CGlobals::GetUserSetting(const CString& strSetting, bool& bValue, bool bDefault)
{
	CFlooringApp* pApp = (CFlooringApp*) AfxGetApp() ;
	int iUserID = pApp->GetEmployeeID();

	CSetSettings setSettings(&g_dbFlooring);
	long lDefault = (bDefault) ? 1 : 0;
	long lValue = setSettings.GetValueLong(strSetting, iUserID, lDefault);

	bValue = (lValue != 0) ;
}

void CGlobals::GetUserSetting(const CString& strSetting, CString& strValue, const CString& strDefault)
{
	CFlooringApp* pApp = (CFlooringApp*) AfxGetApp() ;
	int iUserID = pApp->GetEmployeeID();

	CSetSettings setSettings(&g_dbFlooring);
	strValue = setSettings.GetValueString(strSetting, iUserID, strDefault);
}

void CGlobals::SetUserSetting(const CString& strSetting, bool bValue) 
{
	CFlooringApp* pApp = (CFlooringApp*) AfxGetApp() ;
	int iUserID = pApp->GetEmployeeID();

	CSetSettings setSettings(&g_dbFlooring);
		
	if (bValue)
	{
		setSettings.SetSetting(strSetting, 1, iUserID);
	}
	else
	{
		setSettings.SetSetting(strSetting, 0, iUserID);
	}
}

void CGlobals::SetUserSetting(const CString& strSetting, const CString& strValue) 
{
	CFlooringApp* pApp = (CFlooringApp*) AfxGetApp() ;
	int iUserID = pApp->GetEmployeeID();

	CSetSettings setSettings(&g_dbFlooring);
	
	if (strValue.GetLength() > 0)
	{
		setSettings.SetSetting(strSetting, strValue, iUserID);
	}
}


CString CGlobals::POtoStoreNumber(CString strPO, CString strCurrentStoreNumber) 
{
	strPO.TrimRight() ;
	CString strStore = "";
	if (strPO.GetLength() != 4)
	{
		CSetStores setStores(&g_dbFlooring) ;
		setStores.m_strFilter = "[StoreNumber] LIKE '__" + strPO.Left(2) + "'" ;
		setStores.Open() ;
		int iCount = 0 ;
		while (!setStores.IsEOF())
		{
			strStore += setStores.m_StoreNumber + "\n" ;
			iCount++ ;
			setStores.MoveNext() ;
		}
		setStores.Close() ;

		if (iCount == 1)
		{
			strStore.TrimRight() ;
		}
		else if (iCount == 0)
		{
			strStore = "" ;
		}
		else
		{
			CDlgStoreSelection dlgStore ;
			dlgStore.SetStoreList(strStore) ;
			dlgStore.SetCurrentStoreNumber(strCurrentStoreNumber);

			if (dlgStore.DoModal() == IDOK)
			{
				strStore = dlgStore.GetStoreNumber() ;
			}
		}
	}
	else // PO length is = 4, might be a store number
	{
		CSetStores setStores(&g_dbFlooring) ;
		setStores.m_strFilter.Format("[StoreNumber] = %s", strPO) ;
		setStores.Open() ;
		if (!setStores.IsEOF())
		{
			strStore = strPO ;
		}
		setStores.Close() ;
	}

	return strStore ;
}

CString CGlobals::StoreNumberFromOrderID(int iOrderID)
{
	CString strStoreNumber = "";

	CSetOrders setOrders(&g_dbFlooring);
	CSetStores setStores(&g_dbFlooring);

	setOrders.m_strFilter.Format("[OrderID] = %d", iOrderID);
	setOrders.Open();
	if (!setOrders.IsEOF())
	{
		setStores.m_strFilter.Format("[StoreID] = %d", setOrders.m_StoreID);
		setStores.Open();
		if (!setStores.IsEOF())
		{
			strStoreNumber = setStores.m_StoreNumber;
		}
		setStores.Close();
	}
	setStores.Close();

	return strStoreNumber;
}

CString CGlobals::StoreNumberFromStoreID(int iStoreID)
{
	CString strStoreNumber = "";

	CSetStores setStores(&g_dbFlooring);

	setStores.m_strFilter.Format("[StoreID] = %d", iStoreID);
	setStores.Open();
	if (!setStores.IsEOF())
	{
		strStoreNumber = setStores.m_StoreNumber;
	}
	setStores.Close();

	return strStoreNumber;
}

int CGlobals::MarketIDFromStoreNumber(CString strStoreNumber)
{
	int iMarketID = -1;

	CSetStores setStores(&g_dbFlooring);
	setStores.m_strFilter.Format("[StoreNumber] = '%s'", strStoreNumber);
	setStores.Open();

	if (!setStores.IsEOF())
	{
		iMarketID = setStores.m_MarketId;
	}

	setStores.Close();

	return iMarketID;
}

int CGlobals::StoreIDFromStoreNumber(CString strStoreNumber)
{
	int iStoreID = -1;

	CSetStores setStores(&g_dbFlooring);
	setStores.m_strFilter.Format("[StoreNumber] = '%s'", strStoreNumber);
	setStores.Open();

	if (!setStores.IsEOF())
	{
		iStoreID = setStores.m_StoreID;
	}

	setStores.Close();

	return iStoreID;
}

int CGlobals::StoreTypeIDFromStoreNumber(CString strStoreNumber)
{
	int iStoreTypeID = -1;

	CSetStores setStores(&g_dbFlooring);
	setStores.m_strFilter.Format("[StoreNumber] = '%s'", strStoreNumber);
	setStores.Open();

	if (!setStores.IsEOF())
	{
		iStoreTypeID = setStores.m_StoreTypeID;
	}

	setStores.Close();

	return iStoreTypeID;
}

bool CGlobals::POInUse(CString strPO, CString strStoreNumber)
{
	int iOrderID = -1;
	return CGlobals::POInUse(strPO, strStoreNumber, iOrderID);
}

bool CGlobals::POInUse(CString strPO, CString strStoreNumber, int& iOrderID)
{
	// we only want to check on real PO Numbers...
	ASSERT(strPO.GetLength() == 8);
	
	iOrderID = -1;
	bool bInUse = false;

	CSetOrders setOrders(&g_dbFlooring);
	if (strStoreNumber.GetLength() > 0)
	{
		int iStoreID = CGlobals::StoreIDFromStoreNumber(strStoreNumber);
		setOrders.m_strFilter.Format("[PurchaseOrderNumber] = '%s' AND [StoreID] = %i", strPO, iStoreID);
	}
	else
	{
		setOrders.m_strFilter.Format("[PurchaseOrderNumber] = '%s'", strPO);
	}

	setOrders.m_strFilter += " AND Deleted = 0";

	setOrders.Open();
	if (!setOrders.IsEOF())
	{
		iOrderID = setOrders.m_OrderID;
		bInUse = true;
	}
	setOrders.Close();

	return bInUse;
}

bool CGlobals::MarketAndDivisionFromOrderID(int iOrderID, int& iMarketID, int& iDivisionID)
{
	bool bOK = false;
	iMarketID = -1;
	iDivisionID = -1;
	CSetOrders setOrders(&g_dbFlooring);
	setOrders.m_strFilter.Format("OrderID = %d", iOrderID);
	setOrders.Open();
	if (!setOrders.IsEOF())
	{
		int iMaterialTypeID = setOrders.m_MaterialTypeID;
		int iStoreID = setOrders.m_StoreID;
		iMarketID = CGlobals::MarketIDFromStoreID(iStoreID);
		iDivisionID = CGlobals::DivisionIDFromMaterialTypeID(iMaterialTypeID);
		if ((iMarketID != -1) && (iDivisionID != -1))
		{
			bOK = true;
		}
	}
	setOrders.Close();

	return bOK;
}

int CGlobals::MarketIDFromStoreID(int iStoreID)
{
	int iMarketID = -1;

	CSetStores setStores(&g_dbFlooring);
	setStores.m_strFilter.Format("StoreID = %d", iStoreID);
	setStores.Open();
	if (!setStores.IsEOF())
	{
		iMarketID = setStores.m_MarketId;
	}
	setStores.Close();

	return iMarketID;
}

int CGlobals::DivisionIDFromMaterialTypeID(int iMaterialTypeID)
{
	int iDivisionID = -1;

	CSetMaterialType setMat(&g_dbFlooring);
	setMat.m_strFilter.Format("MaterialTypeID = %d", iMaterialTypeID);
	setMat.Open();
	if (!setMat.IsEOF())
	{
		iDivisionID = setMat.m_DivisionID;
	}

	return iDivisionID;
}

bool CGlobals::RefreshPrices( int /* iOrderID */)
{
	// this function calls a stored procedure up_RefreshPrices to retrieve the latest prices for all 
	// items associated with this order id
	bool bSuccess = true;

	//CCFIDatabase db;
	//db.OpenEx( _T( "DSN=Flooring"), CDatabase::noOdbcDialog);
	//db.PrepareStoreProcedure("up_RefreshPrices");
	//db.SetParam_Long(1, iOrderID);
	//db.ExecuteSQL("{?=call up_RefreshPrices(?)}");
	//long retcode = db.GetParam_Long(0);
	//bSuccess = (retcode == 0);
	//db.Close();

    return bSuccess;
}

bool CGlobals::CustomerHasAlerts(int iCustomerID)
{
	if (iCustomerID == -1) return false;

	bool bHasAlerts = false;

	CSetDiscrepancies setDisc(&g_dbFlooring);
	setDisc.m_strFilter.Format("DetailID = %d AND Reviewed = 0 AND DiscrepancyTypeID = %d", iCustomerID, CGlobals::DISC_CUSTOMER);
	setDisc.Open();
	bHasAlerts = !setDisc.IsEOF();
	setDisc.Close();

	return bHasAlerts;
}

bool CGlobals::OrderHasAlerts(int iOrderID, bool bIncludeAllCustomerAlerts /*= false*/)
{
	if (iOrderID == -1) return false;

	bool bHasAlerts = false;
	CSetVwOrdersWithDiscrepancies setDisc(&g_dbFlooring);
	setDisc.m_strFilter.Format("OrderID = %d", iOrderID);
	setDisc.Open();
	bHasAlerts = !setDisc.IsEOF();
	setDisc.Close();

	// if there are alerts for the same customer on a different PO, also return
	// true
	if (bIncludeAllCustomerAlerts)
	{
		bHasAlerts = bHasAlerts || CustomerHasAlerts(CustomerIDFromOrderID(iOrderID));
	}

	//// return true if order itself has not been reviewed
	//CSetOrders setOrders(&g_dbFlooring);
	//setOrders.m_strFilter.Format("OrderID = %d and Reviewed = 0", iOrderID);
	//setOrders.Open();
	//bHasAlerts = bHasAlerts || !setOrders.IsEOF();
	//setOrders.Close();

	return bHasAlerts;
}

bool CGlobals::OrderIsReviewed(int iOrderID)
{
	if (iOrderID == -1) return false;

	bool bOrderReviewed = false;

	CSetOrders setOrders(&g_dbFlooring);
	setOrders.m_strFilter.Format("OrderID = %d AND Reviewed = 1", iOrderID);
	setOrders.Open();
	bOrderReviewed = !setOrders.IsEOF();
	setOrders.Close();
	return bOrderReviewed;
}

bool CGlobals::OrderIsCancelled(int iOrderID)
{
	if (iOrderID == -1) return false;

	bool bOrderCancelled = false;

	CSetOrders setOrders(&g_dbFlooring);
	setOrders.m_strFilter.Format("OrderID = %d AND Cancelled = 1", iOrderID);
	setOrders.Open();
	bOrderCancelled = !setOrders.IsEOF();
	setOrders.Close();
	return bOrderCancelled;
}

bool CGlobals::OrderIsDeleted(int iOrderID)
{
	if (iOrderID == -1) return false;

	bool bOrderDeleted = false;

	CSetOrders setOrders(&g_dbFlooring);
	setOrders.m_strFilter.Format("OrderID = %d AND Deleted = 1", iOrderID);
	setOrders.Open();
	bOrderDeleted = !setOrders.IsEOF();
	setOrders.Close();
	return bOrderDeleted;
}

bool CGlobals::OrderHasCustomerAlerts(int iOrderID)
{
	if (iOrderID == -1) return false;

	bool bHasCustomerAlerts = false;
	CSetDiscrepancies setDisc(&g_dbFlooring);
	setDisc.m_strFilter.Format("OrderID = %d AND Reviewed = 0 AND DiscrepancyTypeID = %d", iOrderID, CGlobals::DISC_CUSTOMER);
	setDisc.Open();
	bHasCustomerAlerts = !setDisc.IsEOF();
	setDisc.Close();

	return bHasCustomerAlerts;
}

bool CGlobals::OrderHasSOMerchandiseAlerts(int iOrderID)
{
	if (iOrderID == -1) return false;
	bool bHasAlerts = false;
	CSetViewOrderSOMerchandiseDetails setDetails(&g_dbFlooring);
	setDetails.m_strFilter.Format("OrderID = %d AND Reviewed = 0", iOrderID);
	setDetails.Open();
	bHasAlerts = !setDetails.IsEOF();
	setDetails.Close();
	return bHasAlerts;
}

bool CGlobals::OrderHasRegMerchandiseAlerts(int iOrderID)
{
	if (iOrderID == -1) return false;
	bool bHasAlerts = false;
	CSetViewOrderRegMerchandiseDetails setDetails(&g_dbFlooring);
	setDetails.m_strFilter.Format("OrderID = %d AND Reviewed = 0", iOrderID);
	setDetails.Open();
	bHasAlerts = !setDetails.IsEOF();
	setDetails.Close();
    return bHasAlerts;
}

bool CGlobals::OrderHasNotesAlerts(int iOrderID)
{
	if (iOrderID == -1) return false;

	bool bHasNotesAlerts = false;

	CSetDiscrepancies setDisc(&g_dbFlooring);
	setDisc.m_strFilter.Format("OrderID = %d AND DiscrepancyTypeID = 7 AND DiscrepancySubTypeID = 27 AND Reviewed = 0", iOrderID);
	setDisc.Open();
	if (!setDisc.IsEOF())
	{
		bHasNotesAlerts = true;
	}
	setDisc.Close();

	return bHasNotesAlerts;
}

CString CGlobals::CustomerNameFromCustomerID(int CustomerID)
{
	CString strName = "";

	CSetCustomer setCust(&g_dbFlooring);
	setCust.m_strFilter.Format("CustomerID = %d", CustomerID);
	setCust.Open();
	if (!setCust.IsEOF())
	{
		strName = setCust.m_LastName + ", " + setCust.m_FirstName;
	}
	setCust.Close();

	return strName;
}

COleDateTime CGlobals::GetCurrentSystemTime()
{
	COleDateTime dt;
	return dt.GetCurrentTime();
}

bool CGlobals::IsInstall(int iOrderID, bool &bIsInstall)
{
	bool bOK = false;
	bIsInstall = false;

	CSetOrders setOrders(&g_dbFlooring) ;
	setOrders.m_strFilter.Format("[OrderId] = '%d'", iOrderID) ;
	setOrders.Open();
	if (!setOrders.IsEOF())
	{
		CSetMaterialType setMaterialType(&g_dbFlooring);
		setMaterialType.m_strFilter.Format("MaterialTypeID = '%d'", setOrders.m_MaterialTypeID);
		setMaterialType.Open();
		if (!setMaterialType.IsEOF())
		{
			if (setMaterialType.m_HDType == "I")
			{
				bIsInstall = true;
			}
			bOK = true;
		}
		setMaterialType.Close();
	}
	setOrders.Close();

	return bOK;
}

bool CGlobals::HasStorePickup(long lOrderID)
{
	CPoList listPOs;
	listPOs.AddHead(lOrderID);
	return HasStorePickup(&listPOs);
}

bool CGlobals::HasStorePickup(CPoList* plistPOs)
{
	bool bOk = true ;
	bool bOk2 = true ;

	CSetViewOrderRegMerchandiseDetails set(&g_dbFlooring) ;
	CSetViewOrderSOMerchandiseDetails set2(&g_dbFlooring) ;

	CString strTemp ;
	CString strFilter = "((" ;

	POSITION pos = plistPOs->GetHeadPosition() ;
	bool bFirst = true ;
	while (pos)
	{
		strTemp.Format("[OrderID] = '%d'", plistPOs->GetNext(pos) ) ;
		if (!bFirst)
		{
			strFilter += " OR " ;
		}
		bFirst = false ;
		strFilter += strTemp ;
	} 
	strFilter += ") AND ([Status] = 'Store Pickup') AND (Deleted = '0') and (Quantity > 0))" ;

	set.m_strFilter = strFilter;
	set.Open() ;
	bOk = !set.IsEOF() ;
	set.Close() ;

	set2.m_strFilter = strFilter;
	set2.Open() ;
	bOk2 = !set2.IsEOF() ;
	set2.Close() ;

	return bOk || bOk2 ;
}

CString CGlobals::GetTitleName(int iTitleID)
{
	CSetContactTitles setTitles(&g_dbFlooring);
	setTitles.m_strFilter.Format("ID = %d", iTitleID);
	setTitles.Open();
	if (!setTitles.IsEOF())
	{
		return setTitles.m_Title;
	}

	return "";
}

CString CGlobals::GetCurrentUserSMTPEmailAddress()
{
	CString strEmail = "";

	CFlooringApp* pApp = (CFlooringApp*) AfxGetApp() ;
	int iUserID = pApp->GetEmployeeID();

	CSetEmployees setEmployees(&g_dbFlooring);
	setEmployees.m_strFilter.Format("ID = %d", iUserID);
	setEmployees.Open();
	if (!setEmployees.IsEOF())
	{
		if (!setEmployees.IsFieldNull(&setEmployees.m_SMTPEmail))
		{
			strEmail = setEmployees.m_SMTPEmail;
		}
	}
	setEmployees.Close();

	return strEmail;
}

CString CGlobals::GetCurrentUserReplyToEmailAddress()
{
	CString strEmail = "";

	CFlooringApp* pApp = (CFlooringApp*) AfxGetApp() ;
	int iUserID = pApp->GetEmployeeID();

	CSetEmployees setEmployees(&g_dbFlooring);
	setEmployees.m_strFilter.Format("ID = %d", iUserID);
	setEmployees.Open();
	if (!setEmployees.IsEOF())
	{
		if (!setEmployees.IsFieldNull(&setEmployees.m_Email))
		{
			strEmail = setEmployees.m_Email;
		}
	}
	setEmployees.Close();

	return strEmail;
}

bool CGlobals::IsSOSI(int iOrderID)
{
	bool bIsSOSI = false;

	CSetOrders setOrders(&g_dbFlooring) ;
	setOrders.m_strFilter.Format("[OrderId] = '%d'", iOrderID) ;
	setOrders.Open();
	if (!setOrders.IsEOF())
	{
		if ((setOrders.m_EntryMethodID == CGlobals::ENTRY_SOSI_IMPORTED) || (setOrders.m_EntryMethodID == CGlobals::ENTRY_SOSI_IMPORTED_HANDMODIFIED))
		{
			bIsSOSI = true;
		}
	}

	return bIsSOSI;
}

CString CGlobals::GetEntryMethodText(int iOrderID)
{
	CString strText = "";

	CSetOrders setOrders(&g_dbFlooring) ;
	setOrders.m_strFilter.Format("[OrderId] = '%d'", iOrderID) ;
	setOrders.Open();
	if (!setOrders.IsEOF())
	{
		switch (setOrders.m_EntryMethodID)
		{
			case CGlobals::ENTRY_SOSI_IMPORTED:
			case CGlobals::ENTRY_SOSI_IMPORTED_HANDMODIFIED:
			case CGlobals::ENTRY_SOSI_IMPORTED_XMLDELETED:
				strText = "SOSI";
				break;
			case CGlobals::ENTRY_MANUAL:
				strText = "HAND ENTERED";
				break;
			case CGlobals::ENTRY_SPN_IMPORTED:
			case CGlobals::ENTRY_SPN_IMPORTED_HANDMODIFIED:
			case CGlobals::ENTRY_SPN_IMPORTED_XMLDELETED:
				strText = "SPN";
				break;
			default:
				strText = "";
				break;
		}
	}

	return strText;
}

CString CGlobals::GetUserEmailPassword()
{
	CString strEmailPassword = "";

	try
	{
		CFlooringApp* pApp = (CFlooringApp*) AfxGetApp() ;

		CSetSettings setSettings(&g_dbFlooring);

		strEmailPassword = setSettings.GetSetting("UserEmailPassword", "", pApp->GetEmployeeID());
		if (strEmailPassword.GetLength() == 0)
		{
			CDlgPassword dlgEmailPassword;
			dlgEmailPassword.SetTitle("Enter Email Password");
			if (dlgEmailPassword.DoModal() == IDOK)
			{
				strEmailPassword = dlgEmailPassword.GetPassword();
				setSettings.SetSetting("UserEmailPassword", strEmailPassword, pApp->GetEmployeeID());
			}			
		}
	}
	catch(CException* pe)
	{		
		strEmailPassword = "";
		pe->Delete();
	}	

	return strEmailPassword;
}

bool CGlobals::SendEmail( CString ToAddress, CString FromAddress, CString Password, CString CCAddress, CString ReplyToAddress, CString Subject, CString Body, CString &Error )
{
	CSetSettings setSettings(&g_dbFlooring);

	Error = "";

	CString Server = setSettings.GetSetting("SMTPServer");
	int PortNumber = atoi(setSettings.GetSetting("SMTPPortNumber", "25"));
	bool UseSSL = (setSettings.GetSetting("SMTPUseTLS", "0") == "1");

	Mailer^ mailer = gcnew Mailer(gcnew System::String(Server), PortNumber, UseSSL );

	bool sendSuccessful = mailer->SendMail(gcnew System::String(Subject), 
		gcnew System::String(Body), 
		false,
		gcnew System::String(""), 
		gcnew System::String(ToAddress), 
		gcnew System::String(CCAddress), 
		gcnew System::String(FromAddress),
		gcnew System::String(FromAddress), 
		gcnew System::String(FromAddress), 
		gcnew System::String(Password));
	
	return sendSuccessful;
}

//bool CGlobals::SendEmail( CString strTo, CString strFrom, CString strPassword, CString strCC, CString strReplyToAddr, CString strSubject, CString strBody, CString &strError )
//{
//	bool Success = false;
//
//	try
//	{
//		//CFlooringApp* pApp = (CFlooringApp*) AfxGetApp() ;
//		CSetSettings setSettings(&g_dbFlooring);		
//
//		CString strServer = setSettings.GetSetting("SMTPServer");
//		CString strPortNumber = setSettings.GetSetting("SMTPPortNumber", "25");
//		CString strUseTLS = setSettings.GetSetting("SMTPUseTLS", "0");
//		CString strSMTPAuthMethod = setSettings.GetSetting("SMTPAuthMethod", "0");		
//		
//		setSettings.Close();
//
//		ISMTPPtr pMailer("MailBee.SMTP");
//		ISSLPtr pSSL("MailBee.SSL");
//
//		// Logging is useful for troubleshooting
//		COleDateTime currentDate = CGlobals::GetCurrentSystemTime();
//		CString currentDateString = currentDate.Format("%m%d%Y");
//		CString emailLogFile = "";
//		emailLogFile.Format("C:\\Temp\\IMC-Email-%s.log", currentDateString);
//		pMailer->LogFilePath = emailLogFile.AllocSysString();
//		pMailer->EnableLogging = TRUE;
//		//pMailer->ClearLog();
//
//		pMailer->LicenseKey = "MBC600-8C8477E62A-3A51B6CED49D3706290496A96E4D900C";		
//	
//		if (strUseTLS == "1")
//		{		
//			pSSL->LicenseKey = "MBC600-8C8477E62A-3A51B6CED49D3706290496A96E4D900C";
//			pSSL->UseStartTLS = TRUE;
//			pMailer->SSL = pSSL;
//		}				
//	
//		pMailer->PortNumber = atoi(strPortNumber);
//
//		pMailer->ServerName = strServer.AllocSysString();
//							
//		// Using authentication is required by most SMTP servers
//		pMailer->AuthMethod = atoi(strSMTPAuthMethod);
//		pMailer->UserName = strFrom.AllocSysString();
//		pMailer->Password = strPassword.AllocSysString();
//
//		// Set e-mail values
//		pMailer->FromAddr = strFrom.AllocSysString();
//		pMailer->Message->ReplyToAddr = strReplyToAddr.AllocSysString();
//		pMailer->ToAddr = strTo.AllocSysString();
//		if (strCC.GetLength() > 0)
//		{
//			pMailer->CCAddr = strCC.AllocSysString();
//		}
//		pMailer->Subject = strSubject.AllocSysString();
//		pMailer->BodyFormat = 0;
//		pMailer->BodyText = strBody.AllocSysString();
//		pMailer->Charset = "UTF-8";
//
//		Success = (pMailer->Send() == VARIANT_TRUE);
//			
//		if (pMailer->IsError)
//		{
//			long ErrorCode = pMailer->ErrCode;
//			CString ErrorDesc = pMailer->ErrDesc.GetBSTR();
//			CString ServerResponse = pMailer->ServerResponse.GetBSTR();
//			strError.Format("Error Description: %s (Err. Code %lu).  Server Response: %s", ErrorDesc, ErrorCode, ServerResponse);
//						
//			if (strError.MakeUpper().Find("AUTHENTICATION FAILED") > 0)
//			{
//				strError = "Could not send the email.  Please verify that your password is correct.";
//			}
//		}
//				
//		pMailer->Disconnect();	
//
//	}
//	catch(CException* pe)
//	{
//		TCHAR szError[1024];
//		pe->GetErrorMessage(szError, sizeof(szError));
//		strError = _T("Exception Thrown: ");
//		strError += szError;
//		pe->Delete();
//	}
//
//	return Success;
//}

bool CGlobals::RequiresWoodWaiver(int OrderID)
{
	bool requiresWoodWaiver = false;

	CSetOrders setOrders(&g_dbFlooring) ;
	setOrders.m_strFilter.Format("[OrderId] = '%d'", OrderID) ;
	setOrders.Open();
	if (!setOrders.IsEOF())
	{
		CSetVwMaterialsRequiringWoodWaiver setVwMaterialsRequiringWoodWaiver(&g_dbFlooring);
		setVwMaterialsRequiringWoodWaiver.Open();
		while (!setVwMaterialsRequiringWoodWaiver.IsEOF())
		{
			if (setVwMaterialsRequiringWoodWaiver.m_MaterialTypeID == setOrders.m_MaterialTypeID)
			{
				requiresWoodWaiver = true;
				break;
			}
			setVwMaterialsRequiringWoodWaiver.MoveNext() ;
		}
		setVwMaterialsRequiringWoodWaiver.Close() ;
	}
	setOrders.Close();

	return requiresWoodWaiver;
}

CString CGlobals::GetBooleanString(bool BooleanValue)
{
	return (BooleanValue) ? "true" : "false";
}

bool CGlobals::QueueNoteForExpeditor(int NoteID, bool CopyToSASM, bool CopyToExpeditorEmail)
{
	bool Success = true;

	Logger::Instance().LogMessage("Entering CGlobals::QueueNoteForExpeditor()");

	CString strSQL = "";
	strSQL.Format("EXEC up_QueueSPNAction %d, '%d', '%s', '%s'", CGlobals::iSPN_ACTION_ADD_EXPEDITOR_NOTE, NoteID, CGlobals::GetBooleanString(CopyToSASM), CGlobals::GetBooleanString(CopyToExpeditorEmail));
	try
	{
		g_dbFlooring.ExecuteSQL(strSQL);
	}
	catch(CException* e)
	{
		TCHAR szError[255];
		e->GetErrorMessage(szError, 255);
		Logger::Instance().LogException(szError);
	}
	
	return Success;
}

UINT CGlobals::SendEmailWorkerThread( LPVOID pParam )
{
	SendEmailParams* pEmailParams = (SendEmailParams*)pParam;

	if (pEmailParams == NULL)
	{
		return 1;
	}

	CString strError = "";
	bool Success = CGlobals::SendEmail(pEmailParams->strTo, pEmailParams->strFrom, pEmailParams->strPassword, pEmailParams->strCC, pEmailParams->strReplyToAddr, pEmailParams->strSubject, pEmailParams->strBody, strError);

	if (!Success)
	{
		CString* s = new CString(strError);
		::PostMessage(pEmailParams->parentWindowHandle, wm_SendEmailError, 0, (LPARAM)s);
	}

	delete pEmailParams;

	return 0;
}