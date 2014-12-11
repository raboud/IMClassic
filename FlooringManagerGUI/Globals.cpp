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
#include "DlgPassword.h"
#include "Logger.h"

#include "SetOrderDiagrams.h"
#include "InstallerJobData.h"

extern CDatabase g_dbFlooring;

extern CMultiDocTemplate* g_pTemplateInvoice ;

using namespace CFI::Utility::Mail;
using namespace CFI::InstallationManager::Business;
using namespace CFI::InstallationManager::Reports::UI;
using namespace CFI::InstallationManager::Shared::Forms;
using namespace CFI::InstallationManager::Controls;
using namespace CFI::InstallationManager;

CGlobals::CGlobals(void)
{
}

CGlobals::~CGlobals(void)
{
}

::System::Collections::Generic::List<int>^ GetPoList(CPoList* listPOs)
{
	::System::Collections::Generic::List<int>^ l = gcnew ::System::Collections::Generic::List<int>();
		POSITION pos = listPOs->GetHeadPosition() ;
		while (pos)
		{
			l->Add(listPOs->GetNext(pos));
		}
	return l;
}

::System::Collections::Generic::List<int>^ GetPoList(int po)
{
	::System::Collections::Generic::List<int>^ l = gcnew ::System::Collections::Generic::List<int>();
			l->Add(po);
	return l;
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
	int iUserID = CGlobals::GetEmployeeID();

	CSetSettings setSettings;
	long lDefault = (bDefault) ? 1 : 0;
	long lValue = setSettings.GetValueLong(strSetting, iUserID, lDefault);

	bValue = (lValue != 0) ;
}

void CGlobals::GetUserSetting(const CString& strSetting, CString& strValue, const CString& strDefault)
{
	int iUserID = CGlobals::GetEmployeeID();

	CSetSettings setSettings;
	strValue = setSettings.GetValueString(strSetting, iUserID, strDefault);
}

void CGlobals::SetUserSetting(const CString& strSetting, bool bValue) 
{
	int iUserID = CGlobals::GetEmployeeID();

	CSetSettings setSettings;
		
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
	int iUserID = CGlobals::GetEmployeeID();

	CSetSettings setSettings;
	
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
	return Singleton::Cache->CurrentUser->EmailAddress;	
}

CString CGlobals::GetCurrentUserReplyToEmailAddress()
{
	return Singleton::Cache->CurrentUser->ReplyToEmailAddress;	
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
		CSetSettings setSettings;

		strEmailPassword = setSettings.GetSetting("UserEmailPassword", "",CGlobals::GetEmployeeID());
		if (strEmailPassword.GetLength() == 0)
		{
			CDlgPassword dlgEmailPassword;
			dlgEmailPassword.SetTitle("Enter Email Password");
			if (dlgEmailPassword.DoModal() == IDOK)
			{
				strEmailPassword = dlgEmailPassword.GetPassword();
				setSettings.SetSetting("UserEmailPassword", strEmailPassword, CGlobals::GetEmployeeID());
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
	CSetSettings setSettings;

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

bool CGlobals::RequiresWoodWaiver(int OrderID)
{
	bool requiresWoodWaiver = false;

	CSetOrders setOrders(&g_dbFlooring) ;
	setOrders.m_strFilter.Format("[OrderId] = '%d'", OrderID) ;
	setOrders.Open();
	if (!setOrders.IsEOF())
	{
		CSetMaterialType mt(&g_dbFlooring);
		mt.m_strFilter.Format("[MaterialTypeID] = '%d' and [WoodWaiver] = '1'", setOrders.m_MaterialTypeID);
		mt.Open();
		if (!mt.IsEOF())
		{
			requiresWoodWaiver = true;
		}
		mt.Close() ;
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
	Logger::Instance().LogMessage("Entering CGlobals::QueueNoteForExpeditor()");
	return SPNActionQueueBLL::QueueNoteToExpeditor(Singleton::Connection->Clone(), NoteID, CopyToSASM, CopyToExpeditorEmail); 
}

bool CGlobals::QueueSchedulePO(int OrderID)
{
	return SPNActionQueueBLL::QueueSchedulePO(Singleton::Connection->Clone(), OrderID); 
}

bool CGlobals::QueueClosePO(int OrderID, COleDateTime date)
{
	return SPNActionQueueBLL::QueueClosePO(Singleton::Connection->Clone(), OrderID, System::DateTime::FromOADate(date)); 
}
bool CGlobals::QueueProductReceipt(int soID)
{
	return SPNActionQueueBLL::QueueProductReceipt(Singleton::Connection->Clone(), soID); 
}

bool CGlobals::SPNUpdatePO(CPoList* pListPOs)
{
	::System::Collections::Generic::List<int>^ l = gcnew ::System::Collections::Generic::List<int>();
		POSITION pos = pListPOs->GetHeadPosition() ;
		while (pos)
		{
			l->Add(pListPOs->GetNext(pos));
		}

		return FormSPN::SPNUpdatePO(Singleton::Connection->Clone(), l);
}

bool CGlobals::SPNUpdatePO(CString strStoreNumber, CString strPONumber)
{
	return FormSPN::SPNUpdatePO(Singleton::Connection->Clone(), gcnew System::String(strStoreNumber), gcnew System::String(strPONumber));
}
	
void CGlobals::PreparePaperWork(int id, PRINT_MODE enMode, bool printOnly)
{
	ReportHelper::PreparePaperWork(GetPoList(id), (CFI::InstallationManager::Reports::UI::POReport) enMode, printOnly ? Mode::Print : Mode::View);
}
	
void CGlobals::PreparePaperWork(CPoList* listPOs, PRINT_MODE enMode, bool printOnly)
{
	ReportHelper::PreparePaperWork(GetPoList(listPOs), (CFI::InstallationManager::Reports::UI::POReport) enMode, printOnly ? Mode::Print : Mode::View);
}

CString CGlobals::InitDefaultContext()
{
	Singleton::Connection = DataConnection::Create("InstallationManager");
	CString temp(Singleton::Connection->Context->ODBCConnestionString);
	ReportHelper::Connection = Singleton::Connection->Clone();
	return temp;
}

void CGlobals::OnStoreInfo() 
{
	ReportHelper::Stores(Mode::View);
}

void CGlobals::OnOverdueInvoices() 
{
	ReportHelper::OverdueInvoices(Mode::View);
}

void CGlobals::OnOpenInvoices() 
{
	ReportHelper::OpenInvoices(Mode::View);
}

void CGlobals::OnReportsPending() 
{
	ReportHelper::PendingInvoices(Mode::View);
}

void CGlobals::OnNotBilled() 
{
	ReportHelper::NotBilled(Mode::View);
}

void CGlobals::OnInventory() 
{
	ReportHelper::Inventory(Mode::View);
}

int CGlobals::GetEmployeeID()
{
	if (CGlobals::m_iUserID == -1)
	{
		CGlobals::SetEmployeeID();
	}
	
	return CGlobals::m_iUserID ;
}

void CGlobals::SetAdmin()
{
	m_bAdmin = Singleton::Cache->CurrentUser->IsAdmin;
}

void CGlobals::OnReportsBilling() 
{
	ReportHelper::Billing(Mode::View);
}

void CGlobals::OnWarrantySched() 
{
	ReportHelper::ScheduledWarranties(Mode::View);
}

void CGlobals::OnWarrantyOpen() 
{
	ReportHelper::OpenWarranties(Mode::View);
}

void CGlobals::OnMaterialRa() 
{
	ReportHelper::InventoryWaitingOnRA(Mode::View);
}

void CGlobals::OnMaterialsNotreceivedyet() 
{
	ReportHelper::InventoryNotPresent(Mode::View);
}

void CGlobals::OnReportsStatus() 
{

	// This function call will cause the stored procedure to generate data for all stores
	int iResponse = AfxMessageBox("This report takes more than 1 minute to generate.\n\nClick OK button to proceed, Cancel to quit.", MB_OKCANCEL | MB_ICONINFORMATION);

	if (iResponse == IDOK)
	{
		ReportHelper::DetailedStatus(Mode::View);
	}
}

void CGlobals::OnReportsStatusSingle() 
{
	CDlgStoreSelection dlgStore ;

	if (dlgStore.DoModal() == IDOK)
	{
		ReportHelper::DetailedStatusByStore(gcnew System::String(dlgStore.GetStoreNumber()), Mode::View);
	}
}

void CGlobals::OnReportsPulllist()
{
	ReportHelper::PullList(Mode::View);
}

void CGlobals::OnReportsWeeklyTotals() 
{
	ReportHelper::WeeklyTotals(Mode::View);
}

void CGlobals::OnReportsCompletedJobsNotPaid()
{
	ReportHelper::CompletedJobsNotPaid(Mode::View);
}

void CGlobals::OnReportsChargebacksByDate()
{
	ReportHelper::ChargebacksByDate(Mode::View);
}

void CGlobals::OnReportsWorkSummaryByWeek()
{
	ReportHelper::WeeklyUnitsTotals(Mode::View);
}

void CGlobals::OnReportsSubPhonelist()
{
	ReportHelper::SubContractorsPhoneList(Mode::View);
}

void CGlobals::OnBackgroundChecksAlphaByLastName()
{
	ReportHelper::SubContractorsBackgroundCheckStatus(Mode::View);
}

void CGlobals::OnJobsAssignments()
{
	ReportHelper::InstallerAssignments(Mode::View);
}

void CGlobals::OnSubHelpers()
{
	ReportHelper::HelperAssignments(Mode::View);
}

void CGlobals::OnWorkmansCompByDate()
{
	ReportHelper::WorkmansCompByDate(Mode::View);
}

void CGlobals::OnLiabilityByDate()
{
	ReportHelper::LiabilityByDate(Mode::View);
}

void CGlobals::OnMaterialsDamaged()
{
	ReportHelper::InventoryDamage(Mode::View);
}

void CGlobals::PrintPONote(int iNoteID)
{
	ReportHelper::PONote(iNoteID, Mode::Print);
}

void CGlobals::PrintCheck(int iCheckID)
{
	ReportHelper::Check(iCheckID, Mode::Print);
}

void CGlobals::ViewCheck(int iCheckID)
{
	ReportHelper::Check(iCheckID, Mode::View);
}

void CGlobals::PrintCustSatReport(int iReportID)
{
	ReportHelper::CustomerSatisfactionConcern(iReportID, Mode::Print);
}
void CGlobals::ViewCustSatReport(int iReportID)
{
	ReportHelper::CustomerSatisfactionConcern(iReportID, Mode::View);
}
//void CGlobals::PrintPO(int iOrderID)
//{
//	PreparePaperWork(iOrderID, (PO(iOrderID, Mode::Print);
//}

//void CGlobals::ViewPO(int iOrderID)
//{
//	ReportHelper::PO(iOrderID, Mode::View);
//}
//
//void CGlobals::PrintReviewChecklist(int OrderID)
//{
//	ReportHelper::ReviewChecklist(OrderID, Mode::Print);
//}
//
//void CGlobals::PrintSchedulingChecklist(int OrderID)
//{
//	ReportHelper::SchedulingChecklist(OrderID, Mode::Print);
//}
//
//void CGlobals::ViewWoodFlooringWaiver(int OrderID, bool PrintOnly)
//{
//	if (PrintOnly)
//	{
//		ReportHelper::WoodFlooringWaiver(OrderID, Mode::Print);
//	}
//	else
//	{
//		ReportHelper::WoodFlooringWaiver(OrderID, Mode::View);
//	}
//}
//
//void CGlobals::PrintWoodFlooringWaiver(int OrderID)
//{
//	ViewWoodFlooringWaiver(OrderID, true);
//
//}

void CGlobals::PayrollReport(CString strGrandTotal, COleDateTime timeWE)
{
	ReportHelper::PayrollReport(gcnew System::String(strGrandTotal), System::DateTime::FromOADate(timeWE), Mode::View);
}

bool CGlobals::CanViewJobAssign()
{
	return CFI::InstallationManager::Shared::Forms::FormWorkorders::CanView(Singleton::Cache->CurrentUser);
}

void CGlobals::ViewJobAssign()
{
	CFI::InstallationManager::Shared::Forms::FormWorkorders::Open(Singleton::Connection->Clone());
}

void CGlobals::SetEmployeeID(int ID)
{
	if (ID != -1)
	{
		Singleton::Cache->ImpersonateUser(ID);						
	}

	SetEmployeeID();
}

void CGlobals::SetEmployeeID()
{
	m_iUserID = Singleton::Cache->CurrentUser->UserID;
	m_strUserName = Singleton::Cache->CurrentUser->UserName;

	SetAdmin();
}

bool CGlobals::IsAdmin()
{
	return m_bAdmin;
}

CString CGlobals::GetUserFirstAndLastName()
{
	return Singleton::Cache->CurrentUser->FullName;	
}

CString CGlobals::GetComputerName()
{
	CString computerName = "";
	TCHAR buffer[256] = TEXT("");	
	DWORD dwSize = sizeof(buffer);

	if (GetComputerNameEx(ComputerNamePhysicalDnsHostname, buffer, &dwSize))
	{
		computerName = CString(buffer);
	}

	return computerName;
}

BOOL CGlobals::ValidateMinimumVersion( CString strVersion )
{
	BOOL bValid = FALSE;

	int iMinimumVersionMajorSW = atoi(strVersion.Left(strVersion.Find('.')));
	int iMinimumVersionMinorSW = atoi(strVersion.Right(strVersion.GetLength() - strVersion.Find('.') - 1));

	CString computerName = GetComputerName();
	if (computerName.GetLength() > 0)
	{
		CSetSettings setSettings;
		CString ComputerAndVersionValue = "";
		ComputerAndVersionValue.Format("%s - %s", computerName, strVersion);
		setSettings.SetSetting("IMClassicVersion", ComputerAndVersionValue, CGlobals::m_iUserID);
	}

	VersionBLL^ versionBll = gcnew VersionBLL(Singleton::Connection->Clone());

	if ( (iMinimumVersionMajorSW > versionBll->IMClassicMinimumVersionMajor) ||
		 ((iMinimumVersionMajorSW == versionBll->IMClassicMinimumVersionMajor) &&
		 (iMinimumVersionMinorSW >= versionBll->IMClassicMinimumVersionMinor))
	   )
	{
		bValid = TRUE;
	}
	else
	{
		CString strReqVersion;
		strReqVersion.Format("%d.%d", versionBll->IMClassicMinimumVersionMajor, versionBll->IMClassicMinimumVersionMinor);
		CString strMessage;
		strMessage.Format("This version of Installation Manager (%s) and is too old to run against the database.  You must run Flooring version %s or higher.",
			strVersion, strReqVersion);
		AfxMessageBox(strMessage, MB_OK);
	}

    return bValid;

}

bool CGlobals::HasPermission(const CString strPermission)
{
	bool bOK = Singleton::Cache->CurrentUser->HasPermission(gcnew System::String(strPermission));
	return bOK;
}

bool CGlobals::HasPermission(const CString strPermission, int iMarketID, int iDivisionID)
{
	bool bOK = Singleton::Cache->CurrentUser->HasPermission(iMarketID, iDivisionID, gcnew System::String(strPermission));
	return bOK;
}

bool CGlobals::HasNoteTypePermission(const CString strNoteType)
{
	bool bOK = Singleton::Cache->CurrentUser->HasNoteTypePermission(gcnew System::String(strNoteType));
	return bOK;
}

bool CGlobals::GetBasicPrices(int iBasicLaborID, COleDateTime OrderDate, COleDateTime ScheduleDate, int iStoreID, double& dCost, double& dPrice)
{
	double temp = -11.0;
	temp = (double) PricingBLL::GetBasicPrice(Singleton::Connection, iBasicLaborID, iStoreID, System::DateTime::FromOADate(OrderDate));
	dPrice = temp;
	temp = (double) PricingBLL::GetBasicCost(Singleton::Connection, iBasicLaborID, iStoreID, System::DateTime::FromOADate(ScheduleDate));
	dCost = temp;
	return true;
}

bool CGlobals::GetOptionPrices(int iOptionID, COleDateTime OrderDate, COleDateTime ScheduleDate, int iStoreID, double& dCost, double& dPrice)
{
	double temp = -11.0;
	temp = (double) PricingBLL::GetOptionPrice(Singleton::Connection, iOptionID, iStoreID, System::DateTime::FromOADate(OrderDate));
	dPrice = temp;
	temp = (double) PricingBLL::GetOptionCost(Singleton::Connection, iOptionID, iStoreID, System::DateTime::FromOADate(ScheduleDate));
	dCost = temp;
	return true;
}
