// DlgWebService.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgWebService.h"

#include "SetStores.h"
#include "SetOrders.h"
#include "Logger.h"

const UINT m_WmError = RegisterWindowMessage( "Web Service Error" ) ;
const UINT m_WmContinue = RegisterWindowMessage( "Web Service OK" ) ;

// CDlgWebService dialog

IMPLEMENT_DYNAMIC(CDlgWebService, CDialog)
CDlgWebService::CDlgWebService(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWebService::IDD, pParent)
	, m_strStoreNumber("")
	, m_strPONumber("")
	, m_bError(false)
{
	m_listPOs.RemoveAll() ;
	m_strReasonCode = "";
	m_strTitle = "Exchanging Data";
}

CDlgWebService::~CDlgWebService()
{
}

void CDlgWebService::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_butOk);
	DDX_Control(pDX, IDC_EDIT1, m_editStatus);
}


BEGIN_MESSAGE_MAP(CDlgWebService, CDialog)
	ON_REGISTERED_MESSAGE( m_WmError, OnError)
	ON_REGISTERED_MESSAGE( m_WmContinue, OnContinue)
END_MESSAGE_MAP()


// CDlgWebService message handlers

INT_PTR CDlgWebService::SPNUpdatePO(CPoList* pListPOs)
{
	m_listPOs.AddHead(pListPOs) ;
	m_enMode = CDlgWebService::EnCOMMAND_SPN_UPDATE_PO;	
	return DoModal();
}

INT_PTR CDlgWebService::SPNUpdatePO(CString strStoreNumber, CString strPONumber)
{
	m_strStoreNumber = strStoreNumber;
	m_strPONumber = strPONumber;
	m_enMode = CDlgWebService::EnCOMMAND_SPN_SINGLE_PO;	
	return DoModal();
}

BOOL CDlgWebService::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetWindowText(m_strTitle);

	CRect rectAnimateCtrl;
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | ACS_CENTER | ACS_TRANSPARENT | ACS_TIMER; // | ACS_AUTOPLAY ;   // control styles

	GetDlgItem(IDC_ANIMATION)->GetClientRect(&rectAnimateCtrl);
	m_AnimateCtrl.Create(dwStyle, rectAnimateCtrl, GetDlgItem(IDC_ANIMATION), IDC_ANIMATE);

	m_AnimateCtrl.Open(IDR_REPORT);
	m_AnimateCtrl.Play(0, (UINT) -1, (UINT) -1) ;

	AfxBeginThread(CDlgWebService::ExecuteThread, this);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

UINT CDlgWebService::ExecuteThread(LPVOID pParam)
{
    CDlgWebService* pWebServiceDialog = (CDlgWebService*)pParam;
	// Initialize OLE libraries

	AfxOleInit() ;
	AfxEnableControlContainer();

    if (pWebServiceDialog == NULL) 
	{
	    return 1;   // if pWebServiceDialog is not valid
	}

	bool bResult = false ;

	switch (pWebServiceDialog->m_enMode)
	{
		case EnCOMMAND_SPN_PRINT_PO:
			bResult = pWebServiceDialog->PrintPOs() ;
			break ;
			
		case EnCOMMAND_SPN_UPDATE_PO:
			bResult = pWebServiceDialog->DownloadPOs() ;
			break ;

		case EnCOMMAND_SPN_SINGLE_PO:
			bResult = pWebServiceDialog->DownloadPO() ;
			break ;		

		case EnCOMMAND_SPN_ADD_NOTE_FOR_EXPEDITOR:
			bResult = pWebServiceDialog->SPNNoteForExpeditor();
			break;

		default:
			break ;
	}

	if (bResult)
	{
		Logger::Instance().LogMessage("ExecuteThread() - bResult = true");
		pWebServiceDialog->m_AnimateCtrl.Stop() ;
		pWebServiceDialog->m_AnimateCtrl.Close() ;
		::PostMessage(pWebServiceDialog->GetSafeHwnd(), m_WmContinue, 0, 0) ;
	}
	else
	{
		Logger::Instance().LogMessage("ExecuteThread() - bResult = false");
		::PostMessage(pWebServiceDialog->GetSafeHwnd(), m_WmError, 0, 0) ;
	}

	return 0 ;
}

bool CDlgWebService::PrintPOs(void)
{
	CSetOrders setOrders(&g_dbFlooring) ;
	CSetStores setStores(&g_dbFlooring) ;

	setOrders.m_strFilter = "OrderID = -1";
	setOrders.Open() ;

	setStores.m_strFilter = "StoreID = -1";
	setStores.Open() ;
		
	SPNService::CSPNServiceT<CSoapWininetClient> spn ;

	bool bOK = false ;

	POSITION pos = m_listPOs.GetHeadPosition() ;
	while(pos)
	{
		int iOrderID = m_listPOs.GetNext(pos);
		setOrders.m_strFilter.Format("[OrderId] = '%d'", iOrderID) ;
		setOrders.Requery() ;

		setStores.m_strFilter.Format("[StoreID] = '%d'", setOrders.m_StoreID) ;
		setStores.Requery() ;
		
		bool bDownLoaded = false ;
		CComBSTR bstrPDF("")  ;

		CString strTemp ;
		strTemp.Format("Generating PDF for %s %s", setStores.m_StoreNumber, setOrders.m_PurchaseOrderNumber) ;
		AddString(strTemp) ;
		Sleep(0) ;

		CFlooringApp* pApp = (CFlooringApp*)AfxGetApp();
		CString strText = pApp->GetCFUserName();

		spn.GetPoPdf2(CComBSTR(strText), CComBSTR(setStores.m_StoreNumber), CComBSTR(setOrders.m_PurchaseOrderNumber), &bDownLoaded, &bstrPDF) ;

		if (bDownLoaded)
		{
			CString strPDF = bstrPDF ;
			HINSTANCE PrintOK = ShellExecute(NULL, "print", strPDF, NULL, NULL, SW_HIDE ) ;
			
			if ((int)PrintOK > 32)
			{
				strTemp = "Printing PO...";
			}
			else 
			{
				strTemp.Format("Print Error - ShellExecute() returned error code %d", (int)PrintOK);
			}
			
			AddString(strTemp);
		}
		else
		{
			strTemp.Format("ERROR generating PDF for %s %s", setStores.m_StoreNumber, setOrders.m_PurchaseOrderNumber) ;
			AddString(strTemp) ;
		}
	}

	setOrders.Close() ;
	setStores.Close() ;

	return bOK ;
}

bool CDlgWebService::DownloadPOs(void)
{
	CSetOrders setOrders(&g_dbFlooring) ;
	CSetStores setStores(&g_dbFlooring) ;

	setOrders.m_strFilter = "OrderID = -1";
	setOrders.Open() ;

	setStores.m_strFilter = "StoreID = -1";
	setStores.Open() ;
		
	SPNService::CSPNServiceT<CSoapWininetClient> spn ;

	bool bOK = false ;

	POSITION pos = m_listPOs.GetHeadPosition() ;
	while(pos)
	{
		int iOrderID = m_listPOs.GetNext(pos);
		setOrders.m_strFilter.Format("[OrderId] = '%d'", iOrderID) ;
		setOrders.Requery() ;

		setStores.m_strFilter.Format("[StoreID] = '%d'", setOrders.m_StoreID) ;
		setStores.Requery() ;
		
		bool ReturnValue = false ;

		CString strTemp ;
		strTemp.Format("Downloading %s %s", setStores.m_StoreNumber, setOrders.m_PurchaseOrderNumber) ;
		AddString(strTemp) ;
		Sleep(0) ;

		CFlooringApp* pApp = (CFlooringApp*)AfxGetApp();
		CString strText = pApp->GetCFUserName();
		
		spn.DownloadPO2(CComBSTR(strText), CComBSTR(setStores.m_StoreNumber), CComBSTR(setOrders.m_PurchaseOrderNumber), &ReturnValue) ;
		if (ReturnValue)
		{
			strTemp.Format("Downloading %s %s Complete", setStores.m_StoreNumber, setOrders.m_PurchaseOrderNumber) ;
			AddString(strTemp) ;
			bOK = true ;
		}
		else
		{
			strTemp.Format("ERROR Downloading %s %s", setStores.m_StoreNumber, setOrders.m_PurchaseOrderNumber) ;
			AddString(strTemp) ;
		}
	}
	setOrders.Close() ;
	setStores.Close() ;

	return bOK;
}

bool CDlgWebService::DownloadPO(void)
{
		
	SPNService::CSPNServiceT<CSoapWininetClient> spn ;

	bool bOK = false ;

	CString strTemp ;

	strTemp.Format("Downloading %s %s", m_strStoreNumber, m_strPONumber) ;
	AddString(strTemp) ;
	Sleep(0) ;

	CFlooringApp* pApp = (CFlooringApp*)AfxGetApp();
	CString strText = pApp->GetCFUserName();

	bool ReturnValue = false;

	spn.DownloadPO2(CComBSTR(strText), CComBSTR(m_strStoreNumber), CComBSTR(m_strPONumber), &ReturnValue) ;
	if (ReturnValue)
	{
		strTemp.Format("Downloading %s %s Complete", m_strStoreNumber, m_strPONumber) ;
		AddString(strTemp) ;
		bOK = true;
	}
	else
	{
		strTemp.Format("ERROR Downloading %s %s", m_strStoreNumber, m_strPONumber) ;
		AddString(strTemp) ;
	}

	return bOK;
}

bool CDlgWebService::SPNNoteForExpeditor(void)
{		
	bool bOK = false ;

	try
	{
		SPNService::CSPNServiceT<CSoapWininetClient> spn ;		

		AddString("Sending note to store...");

		Sleep(0) ;

		CFlooringApp* pApp = (CFlooringApp*)AfxGetApp();
		CString strText = pApp->GetCFUserName();
		CComBSTR bstrStatus = "";

		spn.SendNoteToStoreByNoteID2(CComBSTR(strText), m_iNoteID, m_bCopyToSASM, m_bCopyToExpeditorEmail, &bOK, &bstrStatus) ;
		//spn.SendNoteToStoreByNoteID(CComBSTR(strText), m_iNoteID, m_bCopyToSASM, m_bCopyToExpeditorEmail, &bOK) ;

		Logger::Instance().LogMessage("SPNNoteForExpeditor() - After call to SendNoteToStoreByNoteID2()");

		if (bOK)
		{   
			AddString("Note sent successfully!") ;
		}
		else
		{
			CString strStatus = bstrStatus;
			if (strStatus.GetLength() > 0)
			{
				AddString(strStatus);
			}
			else
			{
				AddString("ERROR: Could not send note.") ;
			}
		}		
	}
	catch (CMemoryException* e)
	{		
		Logger::Instance().LogMessage("SPNNoteForExpeditor() - Memory Exception Thrown!");
		TCHAR szError[255];
		e->GetErrorMessage(szError, 255);
		Logger::Instance().LogException(szError);
	}
	catch (CFileException* e)
	{
		Logger::Instance().LogMessage("SPNNoteForExpeditor() - File Exception Thrown!");
		TCHAR szError[255];
		e->GetErrorMessage(szError, 255);
		Logger::Instance().LogException(szError);
	}
	catch (CException* e)
	{
		Logger::Instance().LogMessage("SPNNoteForExpeditor() - Exception Thrown!");
		TCHAR szError[255];
		e->GetErrorMessage(szError, 255);
		Logger::Instance().LogException(szError);
	}

	return bOK;
	
}

LRESULT CDlgWebService::OnError (WPARAM, LPARAM)
{
	Logger::Instance().LogMessage("OnError() called.");
	m_AnimateCtrl.Stop() ;
	m_butOk.EnableWindow() ;
	m_bError = true;
	return TRUE ;
}

LRESULT CDlgWebService::OnContinue (WPARAM, LPARAM)
{
	Logger::Instance().LogMessage("OnContinue() called.");
	m_AnimateCtrl.Stop() ;	
	EndDialog(IDCONTINUE) ;
	Logger::Instance().LogMessage("Leaving OnContinue().");
	return TRUE ;
}

void CDlgWebService::AddString(CString strText)
{
	CString strTemp;
	m_editStatus.GetWindowText(strTemp);
	if (strTemp.GetLength() > 0) strTemp += "\r\n";
	strTemp += strText;
	m_editStatus.SetWindowText(strTemp);
}

