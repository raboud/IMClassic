/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// DialogPo.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DialogPo.h"
#include <math.h>

#include "SetStores.h"
#include "SetCustomer.h"
#include "SetOrders.h"
#include "SetMaterialType.h"
#include "SetPayments.h"
#include "DlgPOEntry.h"
#include "InstallerJobData.h"
#include "SetMeasureCompCustData.h"
#include "SetMeasureCompOrderData.h"
#include "SetMeasureCompCalcData.h"
#include "SetMeasureCompLineItemData.h"
#include "SetOrderDiagrams.h"
#include "SetSettings.h"

//#include "DlgCalledList.h"
#include "DlgPONotesList.h"
#include ".\dialogpo.h"

#include "DlgDiscrepancies.h"
#include "SetVwDiscrepancies.h"
#include "Globals.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogPo dialog

CDlgPo::CDlgPo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPo::IDD, pParent)
	, m_bAdding(true)
	, m_bReadOnly(true)
	, m_bConsolidatedView(false)
	, m_lMaterialType(-1)
	, m_lStoreTypeId(-1)
	, m_lMarketId(-1)
	, m_lStoreId(-1)
	, m_lCustomerId(-1)
	, m_strPONumber(_T(""))
	, m_strOrigPONumber(_T(""))
	, m_strPOType(_T(""))
	, m_strStoreNumber(_T(""))
	, m_strMaterialTypeShortName(_T(""))
	, m_bDirty(false)
	, m_bInvokedFromSPN(false)
	, m_bXmlBase(false)
	, m_bReviewed(false)
	, m_bCancelled(false)
	, m_bBilled(false)
	, m_bUseSOSIDiagram(false)
	, m_strEntryMethod(_T(""))
{
	CGlobals::GetUserSetting("ShowUnitCost", m_bShowUnitCost) ;
	CGlobals::GetUserSetting("ShowInactive", m_bShowInactive) ;
	CGlobals::GetUserSetting("ShowCFIPrice", m_bShowCFIPrice) ;
	CGlobals::GetUserSetting("ShowDeleted", m_bShowDelete) ;

	m_setDiscrepancies.m_strFilter = "ID = -1";
	m_setDiscrepancies.Open();
}

CDlgPo::~CDlgPo()
{
	m_setDiscrepancies.Close();
}


void CDlgPo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogPo)
	DDX_Control(pDX, IDC_BILL_AMOUNT, m_editBillAmount);
	DDX_Control(pDX, IDC_ORDER_NO, m_editOrderNo);
	DDX_Control(pDX, IDC_BILLED_TEXT, m_statBilled);
	DDX_Control(pDX, IDC_SCHEDULED_TEXT, m_statScheduled);
	DDX_Control(pDX, IDC_DRAWING_TIME, m_comboDrawingTime);
	DDX_Control(pDX, IDC_DRAWING_NUMBER, m_editDrawing);
	DDX_Control(pDX, IDC_SEVEN_DAY, m_butSevenDay);
	DDX_Control(pDX, IDC_CHECK_LIST, m_listCheck);
	DDX_Control(pDX, IDCANCEL, m_butCancel);
	DDX_Control(pDX, IDC_TRIP_CHARGE, m_editTripCharge);
	DDX_Control(pDX, IDC_NO_MIN, m_butNoMin);
	DDX_Control(pDX, IDC_PRICE, m_editPrice);
	DDX_Control(pDX, IDC_CUSTOMER_DATA, m_editCustomerData);
	DDX_Control(pDX, IDC_TYPE, m_comboType);
	DDX_Control(pDX, IDC_ORDER_DATE, m_dateOrder);
	//	DDX_Control(pDX, IDC_NOTES, m_editNotes);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_SUMMARY_EDIT, m_editSummary);
	DDX_Control(pDX, IDC_XMLPRICE, m_editXMLPrice);
	DDX_Control(pDX, IDC_XMLPOAMOUNT_STATIC, m_stXMLPOAmount);
	DDX_Control(pDX, IDC_DRAWING_VIEW, m_butDrawingView);
	DDX_Control(pDX, IDC_BTN_ALERTS, m_btnAlerts);
	DDX_Control(pDX, IDC_REVIEWED_STATUS, m_stReviewedStatus);
	DDX_Control(pDX, IDC_DIAGRAMNAME_STATIC, m_stDiagramName);
}


BEGIN_MESSAGE_MAP(CDlgPo, CDialog)
	//{{AFX_MSG_MAP(CDialogPo)
	ON_CBN_KILLFOCUS(IDC_TYPE, OnKillfocusType)
	ON_EN_KILLFOCUS(IDC_DRAWING_NUMBER, OnKillfocusDrawingNumber)
	ON_EN_CHANGE(IDC_TRIP_CHARGE, OnChangeTripCharge)
	ON_BN_CLICKED(IDC_NO_MIN, OnNoMin)
	ON_BN_CLICKED(IDC_DRAWING_UPDATE, OnDrawingUpdate)
	ON_MESSAGE(CGlobals::WM_LABOR_UPDATE, OnLineItemUpdate)
	ON_COMMAND(ID_EDIT_CLEARREADONLY, OnEditClearreadonly)
	ON_COMMAND(ID_EDIT_EDITPONUMBER, OnEditEditponumber)
	ON_COMMAND(ID_VIEW_SHOWINACTIVEMATERIALS, OnViewShowinactivematerials)
	ON_COMMAND(ID_VIEW_SHOWCFIPRICE, OnViewShowcfiprice)
	ON_COMMAND(ID_VIEW_SHOWUNITCOST, OnViewShowUnitCost)
	ON_COMMAND(ID_VIEW_SHOWDELETED, OnViewShowDeleted)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SHOWINACTIVEMATERIALS, OnUpdateViewShowInactiveMaterials)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SHOWCFIPRICE, OnUpdateViewShowcfiprice)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SHOWUNITCOST, OnUpdateViewShowUnitCost)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SHOWDELETED, OnUpdateViewShowDeleted)
	//}}AFX_MSG_MAP
	ON_NOTIFY(NM_KILLFOCUS, IDC_ORDER_DATE, OnNMKillfocusOrderDate)
	ON_CBN_SELCHANGE(IDC_TYPE, OnCbnSelchangeType)
	ON_WM_INITMENUPOPUP()
	ON_BN_CLICKED(IDC_VIEW_WORKORDER, OnBnClickedViewWorkorder)
	ON_BN_CLICKED(IDC_REFRESH_PRICES, OnBnClickedRefreshPrices)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_DRAWING_VIEW, OnDrawingView)
	ON_CBN_SELCHANGE(IDC_DRAWING_TIME, OnCbnSelchangeDrawingTime)
	ON_BN_CLICKED(IDC_BTN_ALERTS, OnBnClickedAlerts)
	ON_BN_CLICKED(IDC_NOTES, OnBnClickedNotes)
	ON_EN_CHANGE(IDC_DRAWING_NUMBER, OnEnChangeDrawingNumber)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogPo message handlers

BOOL CDlgPo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	ASSERT(((m_bAdding == false) && m_bConsolidatedView) || !m_bConsolidatedView);

	// hide the diagram name static window by default
	m_stDiagramName.ShowWindow(SW_HIDE);
	
	// if we are adding a PO, we are dirty from the start.
	if (m_bAdding)
	{
		// adding a new po, disable notes button
		(GetDlgItem(IDC_NOTES))->EnableWindow(FALSE) ;
		(GetDlgItem(IDC_DRAWING_UPDATE))->EnableWindow(FALSE) ;
		m_bDirty = true;
	}
	else
	{
		CString strDiagramName = GetDiagramName(false);
		if (strDiagramName.GetLength() > 0)
		{
			m_stDiagramName.SetWindowText("SOSI ATTACHED...");
			m_stDiagramName.ShowWindow(SW_SHOW);
			m_editDrawing.ShowWindow(SW_HIDE);
			m_comboDrawingTime.ShowWindow(SW_HIDE);
			m_bUseSOSIDiagram = true;
			m_butDrawingView.EnableWindow(TRUE);
		}
	}

	CreateEmbeddedPropertySheet( this, &m_POPropSheet );
	PositionEmbeddedPropertySheet( this, &m_POPropSheet, IDC_MERCH_PROPSHEET);

	CreateEmbeddedPropertySheet( this, &m_NotesPropSheet );
	PositionEmbeddedPropertySheet( this, &m_NotesPropSheet, IDC_NOTES_PROPSHEET);

	m_NotesPropSheet.AdjustControls();
	
	m_gridLabor.AttachGrid(this, IDC_LABOR_GRID);

	m_editXMLPrice.ShowWindow(SW_HIDE);
	m_stXMLPOAmount.ShowWindow(SW_HIDE);

	if (m_bConsolidatedView)
	{
		InitForConsolidatedView();
	}
	else
	{
		InitNormal();
	}

	m_gridLabor.ShowDeleted(m_bShowDelete);
	m_gridLabor.ShowCFIPrice(m_bShowCFIPrice) ;
	m_gridLabor.ShowUnitCost(m_bShowUnitCost) ;
	
	m_POPropSheet.ShowDeleted(m_bShowDelete) ;
	m_POPropSheet.SetInvokedFromSPN(m_bInvokedFromSPN);

	EnableAlertsButton();

	m_NotesPropSheet.UpdateTabColors();

	if (!m_bAdding)
	{
		m_bDirty = false;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

bool CDlgPo::SaveData()
{
	bool bSaveOK = true;

	if (!m_bConsolidatedView)
	{
		UpdateData();

		if (m_POPropSheet.HasUnknownStatus())
		{
			if (IDYES != MessageBox("At least one material has an UNKNOWN status.  Save anyway?", "Question", MB_ICONQUESTION | MB_YESNOCANCEL))
			{
				return false;
			}
		}

		if (!m_bReadOnly || (CGlobals::HasPermission("CanOverridePO") == true))
		{
			if ((m_strPOType != "Invoice"))
			{
				CString strTemp;
				m_editOrderNo.GetWindowText(strTemp);
				strTemp.Remove(' ');
				if (strTemp.GetLength() == 0)
				{
					MessageBox("An Order Number must be entered.", "Order Number Error") ;
					m_editOrderNo.SetFocus();
					bSaveOK = false;
					return false;
				}
			}

			if (m_comboType.GetCurSel() == CB_ERR)
			{
				MessageBox("A Material Type must be selected.", "No Material Type") ;
				bSaveOK = false;
				return false;
			}

			CSetOrders setOrders(&g_dbFlooring) ;
			setOrders.m_strFilter = "OrderID = -1";   // keep from opening all records

			COleDateTime current = CGlobals::GetCurrentSystemTime();
			if (m_listPOs.GetCount() == 0)
			{
				setOrders.Open() ;
				setOrders.AddNew() ;
				setOrders.m_CustomerID = m_lCustomerId ;
				setOrders.m_Scheduled = false ;
				setOrders.m_Billed = false ;
				setOrders.m_Paid = false ;
				setOrders.m_Called = false ;
//				setOrders.SetFieldNull(&setOrders.m_BilledAmount) ;
				setOrders.m_EnteredBy = CGlobals::GetEmployeeID() ;
				setOrders.m_DateEntered = current;
				m_bCancelled = false;
				m_bBilled = false;
			}
			else
			{
				POSITION pos = m_listPOs.GetHeadPosition();
				int iOrderID = m_listPOs.GetNext(pos);

				setOrders.m_strFilter.Format("[OrderID] = '%d'", iOrderID) ;
				setOrders.Open() ;
				m_bCancelled = (TRUE == setOrders.m_Cancelled);
				m_bBilled = (TRUE == setOrders.m_Billed);
				setOrders.Edit() ;
			}

			m_dateOrder.GetTime(setOrders.m_OrderDate) ;

			setOrders.m_PurchaseOrderNumber = m_strPONumber;

			m_editOrderNo.GetWindowText(setOrders.m_CustOrderNo) ;
			setOrders.m_OriginalPO = m_strOrigPONumber;

			setOrders.m_StoreID = m_lStoreId ;
//			m_editNotes.GetWindowText(setOrders.m_Notes) ;
			setOrders.m_MaterialTypeID = m_comboType.GetItemData(m_comboType.GetCurSel()) ;
			CString strOrderAmount ;
			m_editPrice.GetWindowText(strOrderAmount) ;
			strOrderAmount.Insert(6, ".") ;

			setOrders.m_Warrenty = (m_strPOType == "Warranty") ;
			if (setOrders.m_Warrenty)
			{
				setOrders.m_OrderAmount = "0.00" ;
			}
			else
			{
				setOrders.m_OrderAmount = strOrderAmount ;
			}

			setOrders.m_Invoice = (m_strPOType == "Invoice") ;
			setOrders.m_NoMinimum = ((m_butNoMin.GetCheck()) == BST_CHECKED) ;
			setOrders.m_SevenDay = ((m_butSevenDay.GetCheck()) == BST_CHECKED) ;

			CString strTrip ;
			m_editTripCharge.GetWindowText(strTrip) ;
			setOrders.m_TripCharge = strTrip ;

			setOrders.Update() ;
			
			// check to see if we are adding a new PO.  If we are, then handle updating the orderid
			// list...
			if (m_listPOs.GetCount() == 0)
			{
				setOrders.m_strFilter.Format("PurchaseOrderNumber = '%s' AND StoreID = %d AND EnteredByID = %d and DateEntered = '%s'", m_strPONumber, m_lStoreId, CGlobals::GetEmployeeID(), current.Format("%Y-%m-%d %H:%M:%S") );
				setOrders.Requery();
				while (!setOrders.IsEOF())
				{
					setOrders.MoveNext();
				}
				if (setOrders.GetRecordCount() == 1)
				{
					setOrders.MoveFirst();
					m_listPOs.AddTail(setOrders.m_OrderID);
					m_gridLabor.SetPOList(&m_listPOs, false);
					m_POPropSheet.SetPOList(&m_listPOs, false);
					m_NotesPropSheet.SetPOList(&m_listPOs, false);
				}
				else
				{
					bSaveOK = false;
				}
			}

			if (bSaveOK)
			{
				if ( CGlobals::HasPermission("CanUpdatePOBilledAmount") == true )
				{
					CString strAmount ;
					m_editBillAmount.GetWindowText(strAmount) ;
					strAmount.Remove('$') ;

					if (strAmount.IsEmpty())
					{
						setOrders.Edit() ;
						setOrders.m_BilledAmount = strAmount ;
						setOrders.Update() ;
					}
					else if (!strAmount.IsEmpty())
					{
						setOrders.Edit() ;
						setOrders.m_BilledAmount = strAmount ;
						setOrders.Update() ;
					}
					setOrders.MoveLast() ;
				}

				if ( CGlobals::HasPermission("CanUpdatePOPaid") == true )
				{
					CSetPayments setPayments(&g_dbFlooring) ;
					setPayments.m_strFilter.Format("[OrderID] = '%d'", setOrders.m_OrderID) ;

					setPayments.Open() ;

					if (!setPayments.IsEOF())
					{
						if ((fabs(atof(setPayments.m_Balance)) <= 5) && (!setPayments.m_Paid))
						{
							setOrders.Edit() ;
							setOrders.m_Paid = TRUE ;
							setOrders.Update() ;
						}
						if ((fabs(atof(setPayments.m_Balance)) > 5) && (setPayments.m_Paid))
						{
							setOrders.Edit() ;
							setOrders.m_Paid = FALSE ;
							setOrders.Update() ;
						}
					}
					else
					{
						setOrders.Edit() ;
						if ((setOrders.m_Billed == 1) && ((atof(setOrders.m_BilledAmount)) == 0.0))
						{
							setOrders.m_Paid = TRUE ;
						}
						else
						{
							setOrders.m_Paid = FALSE ;
						}
						setOrders.Update() ;
					}
				}

				// update drawing info
				CSetOrderDiagrams setOrderDiagrams(&g_dbFlooring);
				setOrderDiagrams.m_strFilter.Format("OrderID = %d", setOrders.m_OrderID);
				setOrderDiagrams.Open();
				if (!setOrderDiagrams.IsEOF())
				{
					setOrderDiagrams.Edit();
				}
				else
				{
					setOrderDiagrams.AddNew();
					setOrderDiagrams.m_OrderID = setOrders.m_OrderID;
				}

				if (m_bUseSOSIDiagram)
				{
					setOrderDiagrams.SetFieldNull(&setOrderDiagrams.m_DiagramNumber);
					setOrderDiagrams.SetFieldNull(&setOrderDiagrams.m_DiagramDateTime);
				}
				else
				{
					if (m_comboDrawingTime.GetCurSel() != CB_ERR)
					{
						CString str ;
						m_comboDrawingTime.GetWindowText(str) ;
						str.TrimLeft() ;
						str.TrimRight() ;
						setOrderDiagrams.m_DiagramDateTime.ParseDateTime(str);
					}
					else
					{
						setOrderDiagrams.SetFieldNull(&setOrderDiagrams.m_DiagramDateTime) ;
					}
				
					m_editDrawing.GetWindowText(setOrderDiagrams.m_DiagramNumber) ;
					setOrderDiagrams.SetFieldNull(&setOrderDiagrams.m_DiagramFileName);
				}

				if ( ((setOrderDiagrams.m_DiagramNumber.IsEmpty() == false ) && (setOrderDiagrams.m_DiagramDateTime != NULL)) ||
					  (setOrderDiagrams.m_DiagramFileName.IsEmpty() == false) )
				{
					setOrderDiagrams.Update();
				}				
			
				try
				{
					m_gridLabor.UpdateRecordSet(setOrders.m_OrderID);
					m_POPropSheet.UpdateRecordSet();
					m_NotesPropSheet.UpdateRecordSet();
				}
				catch (CException* pE)
				{
					pE->Delete() ;
					bSaveOK = false;
				}
			}
			setOrders.Close() ;
		}
	}

	if (bSaveOK)
	{
		m_bDirty = false;
	}
	return bSaveOK;
}

void CDlgPo::OnOK() 
{
	if (SaveData())
	{
		// add data to database
		CFlooringApp* pApp = (CFlooringApp*) AfxGetApp();
		::PostMessage(pApp->m_pMainWnd->m_hWnd, wm_UPDATE_USER_ALERTS, 0, 0);

		int iDivisionID = CGlobals::DivisionIDFromMaterialTypeID(m_lMaterialType);
		if (CGlobals::HasPermission("CanMarkPOReviewed", m_lMarketId, iDivisionID))
		{
			int iOrderID = GetFirstOrderID();
			if (CGlobals::OrderHasAlerts(iOrderID) == false)
			{
				if ( m_bReviewed == false )
				{
					if (m_bCancelled)
					{
						if (IDYES == MessageBox("This order has been cancelled.  Mark as reviewed?", "Question", MB_ICONQUESTION | MB_YESNO))
						{
							SetReviewed(iOrderID, true);
							CloseCancelActivities(iOrderID);
						}
					}
					else if (m_bBilled)
					{
						if (IDYES == MessageBox("This order has already been billed.  Mark as reviewed?", "Question", MB_ICONQUESTION | MB_YESNO))
						{
							SetReviewed(iOrderID, true);
						}
					}
					else if (IDYES == MessageBox("Is this P.O. complete and ready to schedule?", "Question", MB_ICONQUESTION | MB_YESNO))
					{
						SetReviewed(iOrderID, true);
					}
				}
			}
			else
			{
				// order has alerts
				if (CGlobals::OrderIsCancelled(iOrderID))
				{
					if (IDYES == MessageBox("This order has been cancelled.  Mark all alerts as reviewed?", "Question", MB_ICONQUESTION | MB_YESNO))
					{
						MarkAlertsReviewed(iOrderID);
						SetReviewed(iOrderID, true);
						CloseCancelActivities(iOrderID);
					}
				}
				else
				{
					if ( m_bReviewed == true )
					{
						SetReviewed(iOrderID, false);
					}
				}
			}
		}

		// close any change activities if there are no alerts left...
		int iOrderID = GetFirstOrderID();
		if (CGlobals::OrderHasAlerts(iOrderID) == false)
		{
			CloseChangeActivities(iOrderID);
		}

		CDialog::OnOK();
	}
}

void CDlgPo::SetReviewed(int iOrderID, bool bReviewed)
{
	CSetOrders setOrders(&g_dbFlooring) ;
	setOrders.m_strFilter.Format("OrderID = %d", iOrderID);   
	setOrders.Open();
	if (!setOrders.IsEOF())
	{
		setOrders.Edit();
		setOrders.m_Reviewed = bReviewed;
		int iUserID = CGlobals::GetEmployeeID();
		setOrders.m_ReviewedBy = iUserID;
		setOrders.m_ReviewedDate = CGlobals::GetCurrentSystemTime();
		setOrders.Update();
	}
	setOrders.Close();
}


void CDlgPo::OnKillfocusType() 
{
	// Set the Material Types for both grids
	if (m_comboType.GetCurSel() != CB_ERR)
	{
		SetMaterialType() ;
		EnableMaterialTypesCombo(FALSE) ;
		GetDlgItem(IDOK)->EnableWindow() ;

		if ( CGlobals::HasPermission("EditPOBillAmount") == true )
		{
			m_editBillAmount.EnableWindow(m_bReadOnly == false) ;
			m_editBillAmount.ShowWindow(SW_SHOW) ;
		}

		m_butNoMin.EnableWindow(m_bReadOnly == false) ;
		m_butSevenDay.EnableWindow(m_bReadOnly == false) ;

//		m_editNotes.EnableWindow(m_bReadOnly == false) ;
		m_editTripCharge.EnableWindow(m_bReadOnly == false) ;
		m_editBillAmount.EnableWindow(m_bReadOnly == false) ;
		m_editOrderNo.EnableWindow(m_bReadOnly == false) ;

		m_gridLabor.EnableWindow(m_bReadOnly == false) ;
		m_POPropSheet.EnableWindow(m_bReadOnly == false);
		m_NotesPropSheet.SetReadOnly(m_bReadOnly);

		if (!m_bAdding)
		{
			GetDlgItem(IDC_DRAWING_UPDATE)->EnableWindow(TRUE) ;
		}
	}
}

void CDlgPo::SetMaterialType()
{
	m_lMaterialType = m_comboType.GetItemData(m_comboType.GetCurSel()) ;
	m_gridLabor.SetMaterialType(m_lMaterialType, true);

	CSetMaterialType setMaterialType(&g_dbFlooring) ;
	setMaterialType.m_strFilter.Format("[MaterialTypeID] = '%d'", m_lMaterialType ) ;
	setMaterialType.Open() ;

	m_POPropSheet.SetAllowStatusUpdate(setMaterialType.m_AllowMaterialStatusUpdate == TRUE) ;
	setMaterialType.Close() ;
}

void CDlgPo::UpdateCustomerData()
{
	CSetCustomer setCustomer(&g_dbFlooring) ;
	setCustomer.m_strFilter.Format("[CustomerID] = '%d'", m_lCustomerId) ;
	setCustomer.Open() ;
	CString strCustomer = setCustomer.m_LastName ;
	strCustomer.Format("%s, %s\r\n%s\r\n%s, %s %s\r\nHOME: %s - WORK: %s",
		setCustomer.m_LastName,
		setCustomer.m_FirstName,
		setCustomer.m_Address,
		setCustomer.m_City,
		setCustomer.m_State,
		setCustomer.m_ZipCode,
		setCustomer.m_PhoneNumber,
		setCustomer.m_WorkNumber) ;
	m_editCustomerData.SetWindowText(strCustomer) ;
	setCustomer.Close() ;
}

LRESULT CDlgPo::OnLineItemUpdate (WPARAM, LPARAM)
{
	UpdatePrice() ;	
	return TRUE ;
}

void CDlgPo::UpdatePrice()
{
	CString strPrice = "00000000" ;
	if ( m_strPOType != "Warranty" )
	{
		m_gridLabor.RecalculateRows();
		CSetMaterialType setMaterialType(&g_dbFlooring) ;
		setMaterialType.m_strFilter.Format("[MaterialTypeID] = '%d'", m_lMaterialType ) ;
		setMaterialType.Open() ;
		double fTrip ;
		CString strTrip ;
		m_editTripCharge.GetWindowText(strTrip) ;
		fTrip = (atof(strTrip) * setMaterialType.m_TripChargeMultiplier) ;

		double dPrice = 0.0 ;

		// get the price of all materials on the PO - if this Material Type only counts the BasicLabor towards
		// the minimum, our price returned will only be for the Basic Labor.

		dPrice = m_gridLabor.CalculatePrice(setMaterialType.m_OnlyBasicToMinimum == TRUE);

		// add the trip charge in if MaterialType includes all costs towards the minimum.
		if (!setMaterialType.m_OnlyBasicToMinimum)
		{
			dPrice += fTrip;
		}

		// if "No Minimum" checkbox is clear, we need to check the minimum price for this Material Type
		CButton* pNoMin = (CButton*) GetDlgItem(IDC_NO_MIN) ;
		double fMinimumPrice = 0.0;
		if (pNoMin->GetCheck() != BST_CHECKED)
		{
			fMinimumPrice = atof(setMaterialType.m_MinimumPrice );
			if ((dPrice < fMinimumPrice))
			{
				dPrice = fMinimumPrice ;
			}
		}

		if (setMaterialType.m_OnlyBasicToMinimum)
		{
			// dPrice equals (Basic OR Minimum Labor)
			// adjust price to reflect the minimum calculation

			double dBasicLaborPrice = m_gridLabor.CalculatePrice(true);

			dPrice += m_gridLabor.CalculatePrice(false);  // (Basic OR Minimum) + Basic + Optional + Custom
			dPrice -= dBasicLaborPrice;  // (Basic OR Minimum) + Optional + Custom
			dPrice += fTrip ;  // now dPrice is (Basic OR Minimum) + Optional + Custom + Trip
		}

		//long lPrice = long((dPrice * 100) + .5001) ; 

		// note: HD seems to be TRUNCATING this not rounding up...noticed during SPN imports of data
		long lPrice = long((dPrice * 100)) ; 
		strPrice.Format("%08d", lPrice) ;
		setMaterialType.Close() ;
	}
	m_editPrice.SetWindowText(strPrice) ;
	m_editXMLPrice.RedrawWindow();
	this->m_stXMLPOAmount.RedrawWindow();
}

bool CDlgPo::SetCustomerId(long lCustomerId)
{
	bool bOK = false;
	CSetCustomer setCustomer(&g_dbFlooring);
	setCustomer.m_strFilter.Format("[CustomerID] = %d", lCustomerId);
	setCustomer.Open();
	if (!setCustomer.IsEOF())
	{
		m_lCustomerId = lCustomerId;
		bOK = true;
	}
	setCustomer.Close();

	return bOK;
}

void CDlgPo::OnChangeTripCharge() 
{
	UpdatePrice() ;
	m_bDirty = true;
}

void CDlgPo::OnNoMin() 
{
	UpdatePrice() ;
	m_bDirty = true;
}

void CDlgPo::OnKillfocusDrawingNumber() 
{
	if (m_listPOs.GetCount() == 0)
	{
		if (!SaveData())
		{
			return;
		}
	}

	POSITION pos = m_listPOs.GetHeadPosition();
	int iOrderID = m_listPOs.GetNext(pos);
	int CustomerID = -1;
	CString strStoreNumber = CGlobals::StoreNumberFromOrderID(iOrderID); ;

	CString strPONumber = m_strPONumber ;
	
	// get the Install Number (Customer Order Number) and trim off leading zeros
	CString strInstallNumber;
	m_editOrderNo.GetWindowText(strInstallNumber);
	strInstallNumber = strInstallNumber.Trim();
	int iInstallNumberLength = strInstallNumber.GetLength();
	if ( iInstallNumberLength > 0)
	{
		for (int i = 0; i < iInstallNumberLength; i++)
		{
			CString strTemp = strInstallNumber.GetAt(0);
			if (strTemp == "0")
			{
				strInstallNumber = strInstallNumber.Right(strInstallNumber.GetLength() - 1);
			}
			else
			{
				break;
			}
		}
	}

	CString strMeasureNumber;
	m_editDrawing.GetWindowText(strMeasureNumber) ;

	CInstallerJobData jobData(strStoreNumber, strPONumber, strInstallNumber, strMeasureNumber) ;
	CStringList calcList ;
	
	// add brackets so WaitCursor gets destroyed automatically
	{
		CWaitCursor curWait ;
		int iNumDrawings = jobData.GetCalcList(calcList);
		if ( iNumDrawings >= 1)
		{
			m_butDrawingView.EnableWindow(TRUE) ;
			m_comboDrawingTime.ResetContent() ;
			CString strList = "";
			POSITION pos = calcList.GetHeadPosition() ;
			while (pos != NULL)
			{
				m_comboDrawingTime.AddString(calcList.GetAt(pos)) ;
				calcList.GetNext(pos) ;
			}

			if ( iNumDrawings == 1)
			{
				m_comboDrawingTime.SetCurSel(0) ;
				m_comboDrawingTime.EnableWindow(false) ;
			}
			else
			{
				// see if we can auto select the drawing time for the current PO
				m_comboDrawingTime.EnableWindow(true) ;
				m_comboDrawingTime.SetFocus() ;
				if (m_listPOs.GetCount() == 1)
				{
					CSetOrderDiagrams setOrderDiagrams(&g_dbFlooring) ;
					setOrderDiagrams.m_strFilter.Format("[OrderID] = '%d'", iOrderID) ;
					setOrderDiagrams.Open() ;
					if (!setOrderDiagrams.IsEOF())
					{
						if (!setOrderDiagrams.IsFieldNull(&setOrderDiagrams.m_DiagramDateTime))
						{
							CString strDrawingDateString = setOrderDiagrams.m_DiagramDateTime.Format("%Y-%m-%d %H:%M:%S");
							CString strDrawingDateStringOld = setOrderDiagrams.m_DiagramDateTime.Format("%Y-%m-%d %H:%M");
							if (m_comboDrawingTime.GetCount() > 0)
							{
								if (m_comboDrawingTime.FindStringExact(-1, strDrawingDateString) != CB_ERR)
								{
									m_comboDrawingTime.SelectString(-1, strDrawingDateString) ;
								}
								else
								{
									int iIndex = m_comboDrawingTime.FindString(-1, strDrawingDateStringOld);
									if (iIndex != CB_ERR)
									{
										m_comboDrawingTime.SetCurSel(iIndex) ;
									}
								}
							}
						}
					}
					setOrderDiagrams.Close();
				}
			}

			try
			{
				if (CustomerID == -1)
				{
					CSetOrders setOrders(&g_dbFlooring) ;
					setOrders.m_strFilter.Format("[OrderID] = '%d'", iOrderID) ;
					setOrders.Open() ;
					CustomerID = setOrders.m_CustomerID;
					setOrders.Close();
				}

				// update MeasureCompTables
				CSetMeasureCompCustData setMCCust(&g_dbFlooring);
				CSetMeasureCompOrderData setMCOrder(&g_dbFlooring);
				CSetMeasureCompCalcData setMCCalc(&g_dbFlooring);
				CSetMeasureCompLineItemData setMCLineItems(&g_dbFlooring);

				// update customer data
				setMCCust.m_strFilter.Format("CustomerID = %d", CustomerID);
				setMCCust.Open();
				if (setMCCust.IsEOF())
				{
					setMCCust.AddNew();
				}
				else
				{
					setMCCust.Edit();
				}
				setMCCust.m_CustomerID = CustomerID;
				setMCCust.m_LastName = jobData.m_strLastName.MakeUpper();
				setMCCust.m_FirstName = jobData.m_strFirstName.MakeUpper();
				setMCCust.m_Address1 = jobData.m_strAddress1.MakeUpper();
				setMCCust.m_Address2 = jobData.m_strAddress2.MakeUpper();
				setMCCust.m_City = jobData.m_strCity.MakeUpper();
				setMCCust.m_State = jobData.m_strState.MakeUpper();
				setMCCust.m_Zip = jobData.m_strZip;
				setMCCust.m_HomePhone = jobData.m_strHomePhone;
				setMCCust.m_BusinessPhone = jobData.m_strBusinessPhone;
				setMCCust.m_Pager = jobData.m_strPager;
				setMCCust.m_CellPhone = jobData.m_strCellPhone;
				setMCCust.m_CrossStreet1 = jobData.m_strCrossStreet1.MakeUpper();
				setMCCust.m_CrossStreetDir1 = jobData.m_strCrossStreetDir1.MakeUpper();
				setMCCust.m_CrossStreet2 = jobData.m_strCrossStreet2.MakeUpper();
				setMCCust.m_CrossStreetDir2 = jobData.m_strCrossStreetDir2.MakeUpper();
				
				// handle email
				setMCCust.m_EmailAddress = jobData.m_strEmailAddress;

				CSetCustomer setCustomer(&g_dbFlooring) ;
				setCustomer.m_strFilter.Format("[CustomerID] = '%d'", m_lCustomerId) ;
				setCustomer.Open() ;
				if (setCustomer.m_EmailAddress == "")
				{
					setCustomer.Edit();
					setCustomer.m_EmailAddress = setMCCust.m_EmailAddress;
					setCustomer.Update();
				}
				setCustomer.Close();

				setMCCust.Update();
				setMCCust.Close();


				// update order info
				setMCOrder.m_strFilter.Format("OrderID = %d", iOrderID);
				setMCOrder.Open();
				if (setMCOrder.IsEOF())
				{
					setMCOrder.AddNew();
				}
				else
				{
					setMCOrder.Edit();
				}
				setMCOrder.m_OrderID = iOrderID;
				setMCOrder.m_Heat = (jobData.m_strHeat == "Yes");
				setMCOrder.m_Pets = (jobData.m_strPets == "Yes");
				setMCOrder.m_Electricity = (jobData.m_strElectricity == "Yes");
				setMCOrder.m_FurnitureMoving = (jobData.m_strFurnitureMoving == "Yes");
				setMCOrder.m_NewPaint = (jobData.m_strNewPaint == "Yes");
				setMCOrder.m_Removal = (jobData.m_strRemoval == "Yes");
				setMCOrder.m_PavedDriveway = (jobData.m_strPavedDriveway == "Yes");
				setMCOrder.m_Garage = (jobData.m_strGarage == "Yes");
				setMCOrder.m_Elevator = (jobData.m_strElevator == "Yes");
				setMCOrder.m_Disposal = jobData.m_strDisposal.MakeUpper();
				setMCOrder.m_Access = jobData.m_strAccess.MakeUpper();
				setMCOrder.m_SiteType = jobData.m_strSiteType.MakeUpper();
				setMCOrder.m_MetalColor = jobData.m_strMetalColor.MakeUpper();
				setMCOrder.Update();
				setMCOrder.Close();

				setMCCalc.m_strFilter = "ID = -1";
				setMCCalc.Open();

				setMCLineItems.m_strFilter = "ID = -1";
				setMCLineItems.Open();

				POSITION pos = jobData.m_CalcList.GetHeadPosition();
				for (int iIndex = 0; iIndex < jobData.m_CalcList.GetCount(); iIndex++)
				{
					CInstallerJobData::CCalculation* pCalc = jobData.m_CalcList.GetNext(pos);
					CString strCalcTimeStamp = pCalc->m_strTimeStamp;
					setMCCalc.m_strFilter.Format("OrderID = %d and CalcTimeStamp = '%s'", iOrderID, strCalcTimeStamp);
					setMCCalc.Requery();

					long lCalcID = -1;

					if (!setMCCalc.IsEOF())
					{
						setMCCalc.Edit();
						setMCCalc.m_Assigned = 0;
						lCalcID = setMCCalc.m_ID;
					}
					else
					{
						setMCCalc.AddNew();
						setMCCalc.m_OrderID = iOrderID;
						COleDateTime dt;
						dt.ParseDateTime(strCalcTimeStamp);
						setMCCalc.m_CalcTimeStamp = dt;
						setMCCalc.m_Assigned = 0;
					}

					if (setMCCalc.Update())
					{
						setMCCalc.Requery();
						CString strIdentity = setMCCalc.m_Identity;
						if (strIdentity.GetLength() > 0)
						{
							lCalcID = atol(strIdentity);
						}
					}

					POSITION pos2 = pCalc->m_LineItemList.GetHeadPosition();
					for (int iIndex2 = 0; iIndex2 < pCalc->m_LineItemList.GetCount(); iIndex2++)
					{
						CInstallerJobData::CCalculation::CLineItem* pLineItem = pCalc->m_LineItemList.GetNext(pos2);
						setMCLineItems.m_strFilter.Format("CalcID = %d AND LineItemNumber = %d", lCalcID, atoi(pLineItem->m_strLineItemNumber));
						setMCLineItems.Requery();
						if (!setMCLineItems.IsEOF())
						{
							setMCLineItems.Edit();
							setMCLineItems.m_MaterialType = pLineItem->m_strMaterialType;
							setMCLineItems.m_MaterialDescription = pLineItem->m_strMaterialDescription.MakeUpper();
							setMCLineItems.m_MaterialWidth = atoi(pLineItem->m_strMaterialWidth);
							setMCLineItems.m_PatternMatch = pLineItem->m_strPatternMatch;
							setMCLineItems.m_MaterialAmount = pLineItem->m_strMaterialAmount;
						}
						else
						{
							setMCLineItems.AddNew();
							setMCLineItems.m_CalcID = lCalcID;
							setMCLineItems.m_LineItemNumber = atoi(pLineItem->m_strLineItemNumber);
							setMCLineItems.m_MaterialType = pLineItem->m_strMaterialType;
							setMCLineItems.m_MaterialDescription = pLineItem->m_strMaterialDescription.MakeUpper();
							setMCLineItems.m_MaterialWidth = atoi(pLineItem->m_strMaterialWidth);
							setMCLineItems.m_PatternMatch = pLineItem->m_strPatternMatch;
							setMCLineItems.m_MaterialAmount = pLineItem->m_strMaterialAmount;
						}
						
						setMCLineItems.Update();
					}
				}
			}
			catch(CException* pe)
			{
				pe->Delete();
			}

		}
		else if (iNumDrawings == 0)
		{
			m_butDrawingView.EnableWindow(FALSE) ;
			MessageBox("No drawings found.", "Error") ;
		}
		else
		{
			// we got a neg. count for the number of drawings...must be MC error
			m_comboDrawingTime.EnableWindow(false) ;
			if (m_listPOs.GetCount() == 1)
			{
				CSetOrderDiagrams setOrderDiagrams(&g_dbFlooring) ;

				setOrderDiagrams.m_strFilter.Format("[OrderID] = '%d'", iOrderID) ;
				setOrderDiagrams.Open() ;
				if (!setOrderDiagrams.IsEOF())
				{
					if (!setOrderDiagrams.IsFieldNull(&setOrderDiagrams.m_DiagramDateTime))
					{
						m_comboDrawingTime.AddString(setOrderDiagrams.m_DiagramDateTime.Format("%Y-%m-%d %H:%M:%S")) ;
						m_comboDrawingTime.SetCurSel(0) ;
					}
				}
				
				MessageBox("A MeasureComp update is not available.", "MeasureComp Error") ;
			}
		}
	}
}

void CDlgPo::OnDrawingUpdate() 
{
	m_stDiagramName.ShowWindow(SW_HIDE);
	m_bUseSOSIDiagram = false;

	m_editDrawing.ShowWindow(SW_SHOW);
	m_comboDrawingTime.ShowWindow(SW_SHOW);
	m_editDrawing.EnableWindow(true) ;
	m_editDrawing.SetFocus() ;
}


void CDlgPo::OnEditClearreadonly() 
{
	if (m_bConsolidatedView)
	{
		return;
	}
	
	m_bReadOnly = false ;

	m_butNoMin.EnableWindow() ;
	m_butSevenDay.EnableWindow() ;

	m_editBillAmount.EnableWindow() ;
	m_editBillAmount.EnableWindow() ;
//	m_editNotes.EnableWindow() ;
	m_NotesPropSheet.SetReadOnly(false);

	m_gridLabor.EnableWindow() ;
	m_POPropSheet.EnableWindow();

	if (!m_bXmlBase)
	{
		m_editTripCharge.EnableWindow() ;
		m_dateOrder.EnableWindow() ;
		m_editOrderNo.EnableWindow() ;
	}
}

void CDlgPo::OnNMKillfocusOrderDate(NMHDR * /* pNMHDR */, LRESULT *pResult)
{
	COleDateTime dateOrder;
	m_dateOrder.GetTime( dateOrder );

	m_gridLabor.SetPODate( dateOrder );

	*pResult = 0;
}

void CDlgPo::OnCbnSelchangeType()
{
	m_gridLabor.ShowWindow(SW_SHOW) ;
	m_POPropSheet.ShowWindow(SW_SHOW) ;
	m_NotesPropSheet.ShowWindow(SW_SHOW);
}



void CDlgPo::SetStoreNumber(CString strStoreNumber)
{
	m_strStoreNumber = strStoreNumber;
	m_lStoreTypeId = CGlobals::StoreTypeIDFromStoreNumber(m_strStoreNumber);
	m_lMarketId = CGlobals::MarketIDFromStoreNumber(m_strStoreNumber);
	m_lStoreId = CGlobals::StoreIDFromStoreNumber(m_strStoreNumber);
}

void CDlgPo::OnEditEditponumber()
{
	if (m_bConsolidatedView)
	{
		return;
	}

	CDlgPOEntry dlgPOEntry;
	POSITION pos = m_listPOs.GetHeadPosition();
	int iOrderID = m_listPOs.GetNext(pos);
	dlgPOEntry.SetOrderID(iOrderID);
	dlgPOEntry.SetPONumber(m_strPONumber);
	dlgPOEntry.SetPOType(m_strPOType);
	dlgPOEntry.SetOrigPONumber(m_strOrigPONumber);
	dlgPOEntry.SetStoreNumber(m_strStoreNumber);

	if (dlgPOEntry.DoModal() == IDOK)
	{
		CString strStoreNumber = dlgPOEntry.GetStoreNumber();
		long lStoreTypeID = CGlobals::StoreTypeIDFromStoreNumber(strStoreNumber);
		if (m_lStoreTypeId != lStoreTypeID)
		{
			MessageBox("The Store type has changed from its initial value.  To change the Store type at this point, click Cancel on the main PO dialog and start over.", "PO Entry Error");
		}
		else
		{			
			m_strPONumber = dlgPOEntry.GetPONumber();
			m_strPOType = dlgPOEntry.GetPOType();
			m_strOrigPONumber = dlgPOEntry.GetOrigPONumber();
			m_strMaterialTypeShortName = dlgPOEntry.GetMaterialTypeShortName();
			m_strStoreNumber = strStoreNumber;
			UpdateData(FALSE);
			// update m_lStoreTypeID, m_lStoreID
			SetStoreNumber(m_strStoreNumber);
		}
		UpdateTitleBar();
	}
}

void CDlgPo::UpdateTitleBar(void)
{
	CString strTitle;
	if (!m_bConsolidatedView)
	{
		strTitle.Format("Store %s | PO %s | %s | %s", m_strStoreNumber, m_strPONumber, m_strPOType, m_strEntryMethod);
		if (m_strPOType == "Warranty")
		{
			strTitle.Format("Store %s | PO %s | WARRANTY (Orig. PO %s) | %s", m_strStoreNumber, m_strPONumber, m_strOrigPONumber, m_strEntryMethod);
		}

		if (m_bCancelled)
		{
			strTitle += "     * * * C A N C E L L E D * * *";
		}
	}
	else
	{
		strTitle.Format("Consolidated View for POs: %s", m_strPONumber);
	}
	SetWindowText(strTitle);
}

void CDlgPo::SetMaterialTypeShortName(CString strShortName)
{
	m_strMaterialTypeShortName = strShortName;
}

void CDlgPo::OnViewShowinactivematerials()
{
	m_bShowInactive = !m_bShowInactive;
	CGlobals::SetUserSetting("ShowInactive", m_bShowInactive) ;
	if (m_bShowInactive)
	{
		m_comboType.UpdateChoices(m_lStoreTypeId, m_lMarketId) ;
	}
	else
	{
		m_comboType.UpdateChoices(m_lStoreTypeId, m_lMarketId, "", true) ;
	}
}

void CDlgPo::EnableMaterialTypesCombo(bool bEnable)
{
	m_comboType.EnableWindow( bEnable ) ;
	CMenu* mmenu = GetMenu();
	if (bEnable)
	{
		mmenu->EnableMenuItem(ID_VIEW_SHOWINACTIVEMATERIALS, MF_BYCOMMAND | MF_ENABLED);
	}
	else
	{
		mmenu->EnableMenuItem(ID_VIEW_SHOWINACTIVEMATERIALS, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	}
}
void CDlgPo::OnUpdateViewShowInactiveMaterials(CCmdUI *pCmdUI)
{
	if (m_bShowInactive)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}

void CDlgPo::OnInitMenuPopup(CMenu* pPopupMenu, UINT /*nIndex*/, BOOL /*bSysMenu*/)
{
	ASSERT(pPopupMenu != NULL);
	// Check the enabled state of various menu items.

	CCmdUI state;
	state.m_pMenu = pPopupMenu;
	ASSERT(state.m_pOther == NULL);
	ASSERT(state.m_pParentMenu == NULL);

	// Determine if menu is popup in top-level menu and set m_pOther to
	// it if so (m_pParentMenu == NULL indicates that it is secondary popup).
	HMENU hParentMenu;
	if (AfxGetThreadState()->m_hTrackingMenu == pPopupMenu->m_hMenu)
		state.m_pParentMenu = pPopupMenu;    // Parent == child for tracking popup.
	else if ((hParentMenu = ::GetMenu(m_hWnd)) != NULL)
	{
		CWnd* pParent = this;
		   // Child windows don't have menus--need to go to the top!
		if (pParent != NULL &&
		   (hParentMenu = ::GetMenu(pParent->m_hWnd)) != NULL)
		{
		   int nIndexMax = ::GetMenuItemCount(hParentMenu);
		   for (int nIndex = 0; nIndex < nIndexMax; nIndex++)
		   {
			if (::GetSubMenu(hParentMenu, nIndex) == pPopupMenu->m_hMenu)
			{
				// When popup is found, m_pParentMenu is containing menu.
				state.m_pParentMenu = CMenu::FromHandle(hParentMenu);
				break;
			}
		   }
		}
	}

	state.m_nIndexMax = pPopupMenu->GetMenuItemCount();
	for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax;
	  state.m_nIndex++)
	{
		state.m_nID = pPopupMenu->GetMenuItemID(state.m_nIndex);
		if (state.m_nID == 0)
		   continue; // Menu separator or invalid cmd - ignore it.

		ASSERT(state.m_pOther == NULL);
		ASSERT(state.m_pMenu != NULL);
		if (state.m_nID == (UINT)-1)
		{
		   // Possibly a popup menu, route to first item of that popup.
		   state.m_pSubMenu = pPopupMenu->GetSubMenu(state.m_nIndex);
		   if (state.m_pSubMenu == NULL ||
			(state.m_nID = state.m_pSubMenu->GetMenuItemID(0)) == 0 ||
			state.m_nID == (UINT)-1)
		   {
			continue;       // First item of popup can't be routed to.
		   }
		   state.DoUpdate(this, TRUE);   // Popups are never auto disabled.
		}
		else
		{
		   // Normal menu item.
		   // Auto enable/disable if frame window has m_bAutoMenuEnable
		   // set and command is _not_ a system command.
		   state.m_pSubMenu = NULL;
		   state.DoUpdate(this, FALSE);
		}

		// Adjust for menu deletions and additions.
		UINT nCount = pPopupMenu->GetMenuItemCount();
		if (nCount < state.m_nIndexMax)
		{
		   state.m_nIndex -= (state.m_nIndexMax - nCount);
		   while (state.m_nIndex < nCount &&
			pPopupMenu->GetMenuItemID(state.m_nIndex) == state.m_nID)
		   {
			state.m_nIndex++;
		   }
		}
		state.m_nIndexMax = nCount;
	}
}

BOOL CDlgPo::CreateEmbeddedPropertySheet( CWnd* pParent, CPropertySheet* pPSheet, DWORD dwStyle, DWORD dwExStyle )
{
	ASSERT_VALID(pParent);
	ASSERT_VALID(pPSheet);

	if (!pPSheet->Create( pParent, dwStyle, dwExStyle ) )
	{
		return FALSE;
	}

	pPSheet->ModifyStyle( 0, WS_TABSTOP );
	pPSheet->ModifyStyleEx( 0, WS_EX_CONTROLPARENT );
	pParent->ModifyStyleEx( 0, WS_EX_CONTROLPARENT );

	return TRUE;
}

void CDlgPo::PositionEmbeddedPropertySheet( CWnd* pParent, CPropertySheet* pPSheet, CRect rcNewPosition )
{
	ASSERT_VALID(pParent);
	ASSERT_VALID(pPSheet);

	CTabCtrl* pTabCtrl = pPSheet->GetTabControl();
	ASSERT(pTabCtrl != NULL);

	CRect rcTabCtrl;
	pTabCtrl->GetWindowRect( &rcTabCtrl );
	pParent->ScreenToClient( &rcTabCtrl );

	CRect rcPSheet;
	pPSheet->GetWindowRect( &rcPSheet );
	pPSheet->ScreenToClient( &rcPSheet );

	int dcx = rcPSheet.Width() - rcTabCtrl.Width();
	int dcy = rcPSheet.Height() - rcTabCtrl.Height();

	pPSheet->MoveWindow( rcNewPosition.left, rcNewPosition.top, rcNewPosition.Width(), rcNewPosition.Height());

	pTabCtrl->SetWindowPos( NULL, 0, 0, rcNewPosition.Width() - dcx, rcNewPosition.Height() - dcy, SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE );

	int nCurrentPage = pPSheet->GetActiveIndex();
	for (int i = 0; i < pPSheet->GetPageCount(); ++i)
	{
		pPSheet->SetActivePage(i);
	}

	pPSheet->SetActivePage(nCurrentPage);
}

void CDlgPo::PositionEmbeddedPropertySheet( CWnd* pParent, CPropertySheet* pPSheet, UINT nIDPSheetArea )
{
	ASSERT_VALID(pParent);
	ASSERT_VALID(pPSheet);

	CRect rcNewPosition;
	CWnd* pWndNewArea = pParent->GetDlgItem(nIDPSheetArea);
	if (pWndNewArea == NULL)
	{
		ASSERT( FALSE );
		return;
	}

	pWndNewArea->GetWindowRect(&rcNewPosition);
	pParent->ScreenToClient(&rcNewPosition);
	PositionEmbeddedPropertySheet( pParent, pPSheet, rcNewPosition );
}


void CDlgPo::OnViewShowDeleted()
{
	m_bShowDelete = !m_bShowDelete;
	CGlobals::SetUserSetting("ShowDeleted", m_bShowDelete) ;
	m_gridLabor.ShowDeleted(m_bShowDelete);
	m_POPropSheet.ShowDeleted(m_bShowDelete) ;
}

void CDlgPo::OnUpdateViewShowDeleted(CCmdUI *pCmdUI)
{
	if (m_bShowDelete)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}	
}

void CDlgPo::OnViewShowcfiprice()
{
	m_bShowCFIPrice = !m_bShowCFIPrice;
	CGlobals::SetUserSetting("ShowCFIPrice", m_bShowCFIPrice) ;
	m_gridLabor.ShowCFIPrice(m_bShowCFIPrice);
}

void CDlgPo::OnUpdateViewShowcfiprice(CCmdUI *pCmdUI)
{
	if (m_bShowCFIPrice)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}	
}

void CDlgPo::OnViewShowUnitCost()
{
	m_bShowUnitCost = !m_bShowUnitCost;
	CGlobals::SetUserSetting("ShowUnitCost", m_bShowUnitCost) ;
	m_gridLabor.ShowUnitCost(m_bShowUnitCost);
}

void CDlgPo::OnUpdateViewShowUnitCost(CCmdUI *pCmdUI)
{
	if (m_bShowUnitCost)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}	
}

void CDlgPo::SetPOList(CPoList* pListPOs)
{
	m_listPOs.AddHead(pListPOs);

	// this removes all POs except the first one since we don't want consolidated view to be active right now.
	// this code will be removed once consolidated view is fixed and complete.
	if (m_listPOs.GetCount() > 1)
	{
		int Count = m_listPOs.GetCount();
		for (int i = 0; i < Count-1; i++)
		{
			m_listPOs.RemoveTail();
		}
	}

	//if (m_listPOs.GetCount() > 1)
	//{
	//	m_bConsolidatedView = true;
	//	m_bReadOnly = true;
	//}

	m_strOrderIDFilter = "";
	m_strPOList = "";

	POSITION pos = m_listPOs.GetHeadPosition();
	while(pos)
	{
		int iOrderID = m_listPOs.GetNext(pos);
		if (m_strPOList.GetLength() > 0)
		{
			m_strPOList += ", ";
		}
		if (m_strOrderIDFilter.GetLength() > 0)
		{
			m_strOrderIDFilter += " OR ";
		}
		m_strPOList += CGlobals::POFromOrderID(iOrderID);
		CString strTemp;
		strTemp.Format("([OrderID] = %d)", iOrderID);
		m_strOrderIDFilter += strTemp;
	}

	if (m_listPOs.GetCount() > 0)
	{
		CSetOrders setOrders(&g_dbFlooring) ;
		setOrders.m_strFilter = m_strOrderIDFilter ;
		setOrders.Open() ;
		if (!setOrders.IsEOF())
		{
			m_bAdding = false;
			if (!m_bConsolidatedView)
			{
				if ((!setOrders.m_Warrenty) && (!setOrders.m_Invoice))
				{
					m_strPOType = "Regular";
				}
				else if ((setOrders.m_Warrenty) && (!setOrders.m_Invoice))
				{
					m_strPOType = "Warranty";
				}
				else if ((setOrders.m_Invoice) && (!setOrders.m_Warrenty))
				{
					m_strPOType = "Invoice";
				}
				
				m_strOrigPONumber = setOrders.m_OriginalPO.Trim();
				m_strStoreNumber = CGlobals::StoreNumberFromOrderID(setOrders.m_OrderID);
			}
			else
			{
				m_strPOType = "Consolidated View";
			}
		}
		setOrders.Close();
	}

	if (m_strOrderIDFilter.GetLength() == 0)
	{
		m_setDiscrepancies.m_strFilter = "ID = -1";
	}
	else
	{
		m_setDiscrepancies.m_strFilter = "(" + m_strOrderIDFilter + ") AND Reviewed = 0";
	}

	m_setDiscrepancies.Requery();
}

void CDlgPo::SetOrderId(int iOrderID)
{
	CPoList list;
	list.AddTail(iOrderID);
	m_listPOs.RemoveAll();
	SetPOList(&list);
}

void CDlgPo::InitForConsolidatedView()
{
	ASSERT(m_bAdding == false);
	m_bReadOnly = true ;

	m_editBillAmount.AllowBlank(true) ;

	CSetOrders setOrders(&g_dbFlooring) ;

	setOrders.m_strFilter = m_strOrderIDFilter ;
	setOrders.Open() ;

	m_lCustomerId = setOrders.m_CustomerID ;
	UpdateCustomerData() ;	

	CString strScheduledInfo = "";
	CString strBillingInfo = "";
	CString strCheckInfo = "";
	CString strNotes = "";
	CString strTemp;
	m_strPONumber = "";

	//CRect rect;
	//((CWnd*)GetDlgItem(IDC_PH1_STATIC))->GetWindowRect(&rect);
	//this->ScreenToClient(&rect);
	//m_listCheck.MoveWindow(&rect);

	m_gridLabor.SetPOList(&m_listPOs);
	m_POPropSheet.SetPOList(&m_listPOs);
	m_NotesPropSheet.SetPOList(&m_listPOs);
	
	while(!setOrders.IsEOF())
	{
		if (m_strPONumber.GetLength() > 0)
		{
			m_strPONumber += ", ";
		}
		m_strPONumber += setOrders.m_PurchaseOrderNumber;

		// Set Scheduled Status
		if(setOrders.m_Scheduled)
		{
			strTemp.Format("PO %s scheduled %s - ", setOrders.m_PurchaseOrderNumber, setOrders.m_ScheduleStartDate) ;
			if (setOrders.m_ScheduledAM)
			{
				strTemp += "AM" ;
			}
			else
			{
				strTemp += "PM" ;
			}

			if (strScheduledInfo.GetLength() > 0)
			{
				strScheduledInfo += "\r\n";
			}
			strScheduledInfo += strTemp;
		}

		// Set Billing Info
		if (setOrders.m_Billed)
		{
			double fAmount = atof(setOrders.m_BilledAmount) ;
			if (this->m_bConsolidatedView)
			{
				strTemp.Format("PO %s Billed    %s - $%.2f", setOrders.m_PurchaseOrderNumber, setOrders.m_BilledDate.Format("%Y-%m-%d"), fAmount) ;
			}
			else
			{
				strTemp.Format("Billed    %s - $%.2f", setOrders.m_BilledDate.Format("%Y-%m-%d"), fAmount) ;
			}
		}
		else
		{
			if (m_bConsolidatedView)
			{
				strTemp.Format("PO %s Not Billed\r\n", setOrders.m_PurchaseOrderNumber) ;
			}
			else
			{
				strTemp.Format("Not Billed\r\n", setOrders.m_PurchaseOrderNumber) ;
			}
		}

		if (strBillingInfo.GetLength() > 0)
		{
			strBillingInfo += "\r\n";
		}
		strBillingInfo += strTemp;
		
		m_editDrawing.ShowWindow(SW_HIDE);

		CSetOrderDiagrams setOrderDiagrams(&g_dbFlooring) ;
		setOrderDiagrams.m_strFilter = m_strOrderIDFilter ;
		setOrderDiagrams.Open() ;
		if (!setOrderDiagrams.IsEOF())
		{
			if (!setOrderDiagrams.IsFieldNull(&setOrderDiagrams.m_DiagramDateTime))
			{
				m_comboDrawingTime.AddString(setOrderDiagrams.m_DiagramDateTime.Format("%Y-%m-%d %H:%M:%S")) ;
				m_comboDrawingTime.SetCurSel(0) ;
				m_comboDrawingTime.EnableWindow(FALSE) ;
				m_editDrawing.EnableWindow(FALSE) ;
				m_butDrawingView.EnableWindow(TRUE) ;
			}
			else
			{
				OnKillfocusDrawingNumber() ;
			}
		}

		m_editBillAmount.ShowWindow(SW_HIDE);
		m_butSevenDay.ShowWindow(SW_HIDE);
		m_editOrderNo.ShowWindow(SW_HIDE);
		
		strTemp.Format("Notes for PO: %s\r\n%s\r\n\r\n", setOrders.m_PurchaseOrderNumber, setOrders.m_Notes);
		strNotes += strTemp;
//		m_editNotes.SetWindowText(strNotes) ;
//		m_editNotes.EnableWindow(m_bReadOnly == false) ;

		// Set Payments Info
		CSetPayments setPayments(&g_dbFlooring) ;
		setPayments.m_strFilter = m_strOrderIDFilter ;
		setPayments.Open() ;
		CRect rect ;
		m_listCheck.GetClientRect(rect) ;
		m_listCheck.SetTabStops(194 / 3) ;

		if (setPayments.IsEOF())
		{
			strCheckInfo = "No Payments" ;
		}
		else
		{
			while (!setPayments.IsEOF())
			{
				CString strCheck ;
				strCheck.Format("P.O. %s %s - CK# %7s - %s\r\n", setOrders.m_PurchaseOrderNumber, setPayments.m_CheckDate.Format("%Y-%m-%d"), setPayments.m_CheckNumber, setPayments.m_Amount) ;
				strCheckInfo += strCheck;
				setPayments.MoveNext() ;
			}
		}
		setPayments.Close() ;

		m_comboType.ShowWindow(SW_HIDE);
		m_editTripCharge.ShowWindow(SW_HIDE);
		m_butNoMin.ShowWindow(SW_HIDE);
		m_butSevenDay.ShowWindow(SW_HIDE);
		m_editOrderNo.ShowWindow(SW_HIDE);
		m_editBillAmount.ShowWindow(SW_HIDE);
		m_dateOrder.ShowWindow(SW_HIDE);
		m_editPrice.ShowWindow(SW_HIDE);
		(CWnd*)(GetDlgItem(IDC_MATERIAL_STATIC))->ShowWindow(SW_HIDE);
		(CWnd*)(GetDlgItem(IDC_ORDERNUM_STATIC))->ShowWindow(SW_HIDE);
		(CWnd*)(GetDlgItem(IDC_TRIPCHARGE_STATIC))->ShowWindow(SW_HIDE);
		(CWnd*)(GetDlgItem(IDC_POAMOUNT_STATIC))->ShowWindow(SW_HIDE);
		(CWnd*)(GetDlgItem(IDC_AMOUNTTOBILL_STATIC))->ShowWindow(SW_HIDE);
		(CWnd*)(GetDlgItem(IDC_DRAWING_STATIC))->ShowWindow(SW_HIDE);
		(CWnd*)(GetDlgItem(IDC_DRAWING_UPDATE))->ShowWindow(SW_HIDE);
		m_editDrawing.ShowWindow(SW_HIDE);
		m_comboDrawingTime.ShowWindow(SW_HIDE);
		
		setOrders.MoveNext();
	}

	CString strSummary = "Schedule Info:\r\n" + strScheduledInfo;
	strSummary += "\r\nBilling Info:\r\n" + strBillingInfo;
	strSummary += "Check Info:\r\n" + strCheckInfo;

	m_editSummary.SetWindowText(strSummary);
	m_editSummary.ShowWindow(SW_NORMAL);
	

	setOrders.Close() ;

	
	UpdatePrice() ;
	InitMenu();
	UpdateData(FALSE);
	UpdateTitleBar();

	
}

void CDlgPo::InitNormal()
{
	m_bReadOnly = false ;

	COleDateTime time = CGlobals::GetCurrentSystemTime();
	m_dateOrder.SetTime(time);

	COleDateTime time2 = COleDateTime(time.GetYear(), time.GetMonth(), time.GetDay(), 0,0,0);

	m_gridLabor.SetPODate( time2 );

	m_editBillAmount.AllowBlank(true) ;
	
	if (m_bAdding == false)  // we are editing an existing PO
	{
		// init our Orders data set
		CSetOrders setOrders(&g_dbFlooring) ;
		setOrders.m_strFilter = m_strOrderIDFilter ;
		setOrders.Open() ;
		m_lCustomerId = setOrders.m_CustomerID ;
		m_bReviewed = (setOrders.m_Reviewed == 1);
		UpdateCustomerData() ;	

		CString strScheduledInfo = "";
		CString strBillingInfo = "";
		CString strNotes = "";
		CString strTemp;
		COleDateTime timeScheduled;
		timeScheduled.ParseDateTime(setOrders.m_ScheduleStartDate);

		// init the Order date 
		m_dateOrder.SetTime(setOrders.m_OrderDate) ;

		// tell the labor grid what the order date is
		m_gridLabor.SetPODate( setOrders.m_OrderDate );
			
		// Set Scheduled Status
		if(setOrders.m_Scheduled)
		{
			strScheduledInfo.Format("Scheduled %s - ", setOrders.m_ScheduleStartDate) ;
			if (setOrders.m_ScheduledAM)
			{
				strScheduledInfo += "AM" ;
			}
			else
			{
				strScheduledInfo += "PM" ;
			}

			// update schedule date for grid
			m_gridLabor.SetPOScheduleDate( timeScheduled );
		}
		else
		{
			strScheduledInfo = "Not Scheduled" ;
			m_gridLabor.SetPOScheduleDate( setOrders.m_OrderDate );
		}

		m_statScheduled.SetWindowText(strScheduledInfo) ;

		// Set Payments Info
		CSetPayments setPayments(&g_dbFlooring) ;
		setPayments.m_strFilter = m_strOrderIDFilter ;
		setPayments.Open() ;
		CRect rect ;
		m_listCheck.GetClientRect(rect) ;
		m_listCheck.SetTabStops(194 / 3) ;

		if (setPayments.IsEOF())
		{
			m_listCheck.AddString("No Payments") ;
		}
		else
		{
			while (!setPayments.IsEOF())
			{
				CString strCheck ;
				strCheck.Format("%s - CK# %7s - %s", setPayments.m_CheckDate.Format("%Y-%m-%d"), setPayments.m_CheckNumber, setPayments.m_Amount) ;
				m_listCheck.AddString(strCheck) ;
				setPayments.MoveNext() ;
			}
		}
		setPayments.Close() ;

		// Set Billing Info
		if (setOrders.m_Billed)
		{
			m_bBilled = true;
			double fAmount = atof(setOrders.m_BilledAmount) ;
			if (m_bConsolidatedView)
			{
				strTemp.Format("PO %s Billed    %s - $%.2f", setOrders.m_PurchaseOrderNumber, setOrders.m_BilledDate.Format("%Y-%m-%d"), fAmount) ;
				strBillingInfo += strTemp + "\n";
			}
			else
			{
				strBillingInfo.Format("Billed    %s - $%.2f", setOrders.m_BilledDate.Format("%Y-%m-%d"), fAmount) ;
			}
		}
		else
		{
			strBillingInfo += "Not Billed\n" ;
		}
		m_statBilled.SetWindowText(strBillingInfo) ;

		// should not allow editing if this PO has been billed
		if ( setOrders.m_Billed || setOrders.m_Cancelled)
		{
			m_bReadOnly = true ;
		}

		m_bCancelled = (setOrders.m_Cancelled == TRUE);

		// Init the drawing info
		CSetOrderDiagrams setOrderDiagrams(&g_dbFlooring);
		setOrderDiagrams.m_strFilter = m_strOrderIDFilter;
		setOrderDiagrams.Open();
		if (!setOrderDiagrams.IsEOF())
		{
			if (!setOrderDiagrams.IsFieldNull(&setOrderDiagrams.m_DiagramNumber))
			{
				m_editDrawing.SetWindowText(setOrderDiagrams.m_DiagramNumber) ;
			}

			if (!setOrderDiagrams.IsFieldNull(&setOrderDiagrams.m_DiagramDateTime))
			{
				m_comboDrawingTime.AddString(setOrderDiagrams.m_DiagramDateTime.Format("%Y-%m-%d %H:%M:%S")) ;
				m_comboDrawingTime.SetCurSel(0) ;
				m_comboDrawingTime.EnableWindow(FALSE) ;
				m_editDrawing.EnableWindow(FALSE) ;
				m_butDrawingView.EnableWindow(TRUE) ;
			}
			
			/*if (!setOrderDiagrams.IsFieldNull(&setOrderDiagrams.m_DiagramFileName))
			{
				#pragma message("WARNING: DKB add code here to show something on dialog")
			}*/
		}
		
		// Init the Bill Amount field
		if ( CGlobals::HasPermission("EditPOBillAmount") == true )
		{
			if (!setOrders.IsFieldNull(&setOrders.m_BilledAmount))
			{
				double fAmount = atof(setOrders.m_BilledAmount) ;
				CString strAmount ;
				strAmount.Format("$%.2f", fAmount) ;
				m_editBillAmount.SetWindowText(strAmount) ;
			}
			m_editBillAmount.EnableWindow(TRUE) ;
			m_editBillAmount.ShowWindow(SW_SHOW) ;
		}
		else
		{
			m_editBillAmount.EnableWindow(FALSE) ;
			m_editBillAmount.ShowWindow(SW_HIDE) ;
		}

		m_butSevenDay.SetCheck(setOrders.m_SevenDay) ;
		strTemp = setOrders.m_CustOrderNo;
		strTemp.Remove(' ');
		m_editOrderNo.SetWindowText(strTemp) ;
		m_strPONumber = setOrders.m_PurchaseOrderNumber.Trim() ;
		m_strPONumber.TrimRight() ;

		// fill in the Notes field
//		m_editNotes.SetLimitText(iMAX_ORDER_NOTES) ;
//		strNotes = setOrders.m_Notes;
//		m_editNotes.SetWindowText(strNotes) ;
//		m_editNotes.EnableWindow(m_bReadOnly == false) ;

		// Set Store Info
		CSetStores setStore(&g_dbFlooring) ;
		setStore.m_strFilter.Format("[StoreID] = '%d'", setOrders.m_StoreID) ;
		setStore.Open() ;
		m_lStoreTypeId = setStore.m_StoreTypeID ;
		m_lStoreId = setOrders.m_StoreID ;
		m_lMarketId = setStore.m_MarketId;
		setStore.Close() ;
		
		// tell the labor grid the current store id
		m_gridLabor.SetStoreID( m_lStoreId );

		// init Materials combo box and select the correct one
		ASSERT(m_lStoreTypeId != -1);
		ASSERT(m_lMarketId != -1);
		m_comboType.UpdateChoices(m_lStoreTypeId, m_lMarketId, m_strMaterialTypeShortName) ;
		for (int iIndex = 0; iIndex < m_comboType.GetCount() ; iIndex++)
		{
			if (m_comboType.GetItemData(iIndex) == (unsigned long) setOrders.m_MaterialTypeID)
			{
				m_comboType.SetCurSel(iIndex) ;
				break ;
			}
		}

		OnKillfocusType() ;
		
		m_dateOrder.SetFocus() ;

		m_gridLabor.SetPOList(&m_listPOs);
		m_POPropSheet.SetPOList(&m_listPOs);
		m_NotesPropSheet.SetPOList(&m_listPOs);

		m_editTripCharge.SetWindowText(setOrders.m_TripCharge.Left(setOrders.m_TripCharge.GetLength() - 2) );
		m_butNoMin.SetCheck(setOrders.m_NoMinimum) ;

		m_butNoMin.EnableWindow(m_bReadOnly == false) ;
		m_butSevenDay.EnableWindow(m_bReadOnly == false) ;
		m_editBillAmount.EnableWindow(m_bReadOnly == false) ;
		m_editBillAmount.EnableWindow(m_bReadOnly == false) ;
//		m_editNotes.EnableWindow(m_bReadOnly == false) ;
		m_NotesPropSheet.SetReadOnly(m_bReadOnly);
		
		if (!setOrders.IsFieldNull(&setOrders.m_XMLOrderCostAmount))
		{
			m_bXmlBase = true ;
			m_editXMLPrice.ShowWindow(SW_NORMAL);
			m_stXMLPOAmount.ShowWindow(SW_NORMAL);
			int iPrice = (atoi(setOrders.m_XMLOrderCostAmount) + 50 ) / 100 ;
			CString strPrice;
			strPrice.Format("%08d", iPrice) ;
			m_editXMLPrice.SetWindowText(strPrice);
			m_dateOrder.EnableWindow(false) ;
			m_editTripCharge.SetReadOnly(true) ;
			m_editOrderNo.SetReadOnly(true) ;
			m_editTripCharge.EnableWindow() ;
			m_editOrderNo.EnableWindow() ;
		}
		else
		{
			m_dateOrder.EnableWindow(m_bReadOnly == false) ;
			m_editTripCharge.EnableWindow(m_bReadOnly == false) ;
			m_editOrderNo.EnableWindow(m_bReadOnly == false) ;
		}
	}
	else
	{
		ASSERT(m_lCustomerId != -1);
		ASSERT(m_lStoreTypeId != -1);
		ASSERT(m_lMarketId != -1);

		UpdateCustomerData() ;	

		m_gridLabor.ShowWindow(SW_HIDE);
		m_POPropSheet.ShowWindow(SW_HIDE);
		m_NotesPropSheet.ShowWindow(SW_HIDE);

		m_editPrice.SetWindowText("00000000") ;
		
		// tell the labor grid the current store id
		m_gridLabor.SetStoreID( m_lStoreId );

		if (m_strPOType == "Warranty")
		{
			// show all materialtypes incl. inactive ones
			m_comboType.UpdateChoices(m_lStoreTypeId, m_lMarketId, m_strMaterialTypeShortName) ;
		}
		else
		{
			m_comboType.UpdateChoices(m_lStoreTypeId, m_lMarketId, m_strMaterialTypeShortName, true) ;
		}
		EnableMaterialTypesCombo(!m_bReadOnly) ;
	}

	m_strEntryMethod = CGlobals::GetEntryMethodText(GetFirstOrderID());

	UpdatePrice() ;
	InitMenu();
	UpdateData(FALSE);
	UpdateTitleBar();
}

void CDlgPo::InitMenu()
{
	CMenu* mmenu = GetMenu();
	if ( (CGlobals::HasPermission("CanClearReadOnlyPO") == true) && (!m_bConsolidatedView))
	{
		mmenu->EnableMenuItem(ID_EDIT_CLEARREADONLY, MF_BYCOMMAND | MF_ENABLED);
	}
	else
	{
		mmenu->EnableMenuItem(ID_EDIT_CLEARREADONLY, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	}

	if ( ((m_strPONumber.GetLength() == 4) || CGlobals::HasPermission("CanEditPONumber") == true) && !m_bConsolidatedView)
	{
		mmenu->EnableMenuItem(ID_EDIT_EDITPONUMBER, MF_BYCOMMAND | MF_ENABLED);
	}
	else
	{
		mmenu->EnableMenuItem(ID_EDIT_EDITPONUMBER, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	}

	if (CGlobals::HasPermission("CanViewCFIPrice") == true)
	{
		mmenu->EnableMenuItem(ID_VIEW_SHOWCFIPRICE, MF_BYCOMMAND | MF_ENABLED);
	}
	else
	{
		mmenu->EnableMenuItem(ID_VIEW_SHOWCFIPRICE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	}

	if (m_bConsolidatedView)
	{
		mmenu->EnableMenuItem(ID_VIEW_SHOWINACTIVEMATERIALS, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	}
}
void CDlgPo::OnBnClickedViewWorkorder()
{
	if (SaveData())
	{
		CGlobals::PreparePaperWork(&m_listPOs, CGlobals::PM_WORKORDER, false);
	}
}

void CDlgPo::OnBnClickedRefreshPrices()
{
	m_gridLabor.RefreshPrices();
	UpdatePrice();
}

HBRUSH CDlgPo::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	int iControlID = pWnd->GetDlgCtrlID();

	if ((iControlID == IDC_XMLPRICE) ||
		(iControlID == IDC_XMLPOAMOUNT_STATIC))
	{
		CString strCalcPrice;
		CString strXMLPrice;
		m_editPrice.GetWindowText(strCalcPrice);
		m_editXMLPrice.GetWindowText(strXMLPrice);
		int Price = atoi(strCalcPrice);
		int XMLPrice = atoi(strXMLPrice);
		if (abs(Price-XMLPrice) > 1)
		{
			pDC->SetTextColor( RGB(255, 0, 0) );
		}
		else
		{
			pDC->SetTextColor( RGB(0,0,0) );
		}
	}

	if ((iControlID == IDC_ORDER_NO) ||
		(iControlID == IDC_ORDER_DATE) ||
		(iControlID == IDC_TRIP_CHARGE))
	{
		if (m_bXmlBase)
		{
			pDC->SetTextColor( RGB(0, 0, 255) );
		}
		else
		{
			pDC->SetTextColor( RGB(0,0,0) );
		}
	}

	if (iControlID == IDC_CUSTOMER_DATA)
	{
		int iOrderID = GetFirstOrderID();
		int iCustomerID = CGlobals::CustomerIDFromOrderID(iOrderID);
		if ( CGlobals::CustomerHasAlerts(iCustomerID) || CGlobals::OrderHasCustomerAlerts(iOrderID) )
		{
			pDC->SetTextColor( RGB(0, 0, 255) );
			pDC->SetBkColor( CGlobals::COLOR_ALERT );
		}
	}

	if (iControlID == IDC_NOTES_PROPSHEET)
	{
		if (CGlobals::OrderHasCustomerAlerts(GetFirstOrderID()))
		{
			pDC->SetTextColor( RGB(0, 0, 255) );
			pDC->SetBkColor( CGlobals::COLOR_ALERT );
		}
	}

	if (iControlID == IDC_REVIEWED_STATUS)
	{
		if (CGlobals::OrderIsReviewed(GetFirstOrderID()))
		{
			pDC->SetTextColor(RGB(0,0,255));
			m_stReviewedStatus.SetWindowText("Reviewed");
		}
		else
		{
			pDC->SetTextColor(RGB(255, 0, 0));
			m_stReviewedStatus.SetWindowText("Not Reviewed");
		}
	}
	
	return hbr;
}

void CDlgPo::OnDrawingView()
{
	if (m_bUseSOSIDiagram)
	{
		CString strFileName = GetDiagramName(true);
		ShellExecute(NULL, "open", strFileName, NULL, NULL, 10 ) ;
	}
	else if (m_comboDrawingTime.GetCurSel() != CB_ERR)
	{
		CWaitCursor curWait ;

		CString strInstallNumber;
		m_editOrderNo.GetWindowText(strInstallNumber);
		strInstallNumber = strInstallNumber.Trim();


		CString strMeasureNumber;
		m_editDrawing.GetWindowText(strMeasureNumber) ;

		CString str ;
		m_comboDrawingTime.GetWindowText(str) ;
		str.TrimLeft() ;
		str.TrimRight() ;
		COleDateTime dt;
		dt.ParseDateTime(str);

		if ( !CInstallerJobData::GetDrawing(false, m_strStoreNumber, m_strPONumber, strInstallNumber, strMeasureNumber, dt) )
		{
			MessageBox("Drawing Number or Calculation date is invalid", "Seaming Diagram", MB_OK) ;
		}
		else
		{
			CString strFileName = CInstallerJobData::FormatDrawingFilename(m_strStoreNumber, m_strPONumber, strInstallNumber, strMeasureNumber, dt) ;
			ShellExecute(NULL, "open", strFileName, NULL, NULL, 10 ) ;
		}
	}
}

void CDlgPo::OnCbnSelchangeDrawingTime()
{
	m_butDrawingView.EnableWindow(m_comboDrawingTime.GetCurSel() != CB_ERR) ;
	m_bDirty = true;
}

void CDlgPo::OnBnClickedAlerts()
{
	CDlgDiscrepancies dlg;
	dlg.SetPOList(&m_listPOs);
	if (dlg.DoModal() == IDOK)
	{
		UpdateCustomerData();
		m_NotesPropSheet.UpdateTabColors();
		EnableAlertsButton();
		m_gridLabor.RedrawAll();
		Invalidate();
	}
}

void CDlgPo::EnableAlertsButton()
{
	if (m_bConsolidatedView || m_bAdding)
	{
		// for consolidated view we are just going to disable the button....maybe change later
		m_btnAlerts.EnableWindow(FALSE);
	}
	else
	{
		int iOrderID = GetFirstOrderID();
		CString strRecordSetFilter;
		strRecordSetFilter.Format("(OrderID = %d)", iOrderID);

		// we update the button in the call to HasCustomerDiscrepancies
		CSetVwDiscrepancies setDiscrepancies(&g_dbFlooring) ;
		
		if (m_lCustomerId != -1)
		{
			CString strExtraFilter;
			strExtraFilter.Format(" OR (Type = 'CUSTOMER' AND DetailID = %d)", m_lCustomerId);
			strRecordSetFilter += strExtraFilter;
		}

		strRecordSetFilter = "((" + strRecordSetFilter + ") AND (Reviewed = 0))";
		setDiscrepancies.m_strFilter = strRecordSetFilter;
		setDiscrepancies.Open() ;
		if (!setDiscrepancies.IsEOF())
		{
			m_btnAlerts.EnableWindow();
		}
		else
		{
			m_btnAlerts.EnableWindow(FALSE);
		}

		// enable the alerts button if there are any alerts for this PO, OR any alerts for this CUSTOMER (hence the true parameter)
		//if (CGlobals::OrderHasAlerts(GetFirstOrderID(), true))
		//{
		//	m_btnAlerts.EnableWindow();
		//}
		//else
		//{
		//	m_btnAlerts.EnableWindow(FALSE);
		//}
	}
}

void CDlgPo::MarkAlertsReviewed(int iOrderID)
{
	CString strSQL;
	strSQL.Format("UPDATE OrderBasicLaborDetails SET Reviewed = 1 WHERE OrderID = %d", iOrderID);
	g_dbFlooring.ExecuteSQL(strSQL);

	strSQL.Format("UPDATE [Order Options Details] SET Reviewed = 1 WHERE OrderID = %d", iOrderID);
	g_dbFlooring.ExecuteSQL(strSQL);

	strSQL.Format("UPDATE OrderCustomDetails SET Reviewed = 1 WHERE OrderID = %d", iOrderID);
	g_dbFlooring.ExecuteSQL(strSQL);

	strSQL.Format("UPDATE OrderSOMerchandiseDetails SET Reviewed = 1 WHERE OrderID = %d", iOrderID);
	g_dbFlooring.ExecuteSQL(strSQL);

	strSQL.Format("UPDATE OrderRegMerchandiseDetails SET Reviewed = 1 WHERE OrderID = %d", iOrderID);
	g_dbFlooring.ExecuteSQL(strSQL);

	strSQL.Format("DELETE FROM Discrepancies WHERE OrderID = %d", iOrderID);
	g_dbFlooring.ExecuteSQL(strSQL);
}
void CDlgPo::OnBnClickedNotes()
{
	CDlgPONotesList dlg ;
	dlg.SetOrderId(m_listPOs.GetHead()) ;
	dlg.DoModal() ;
}

CString CDlgPo::GetDiagramName(bool bFullPath)
{
	CString strDiagramName = "";
	
	POSITION pos = m_listPOs.GetHeadPosition();
	int iOrderID = m_listPOs.GetNext(pos);

	CSetOrderDiagrams setDiagrams(&g_dbFlooring);
	setDiagrams.m_strFilter.Format("OrderID = %d", iOrderID);
	setDiagrams.Open();

	if (!setDiagrams.IsEOF())
	{
		if (!setDiagrams.IsFieldNull(&setDiagrams.m_DiagramFileName))
		{
			strDiagramName = setDiagrams.m_DiagramFileName;
			if (bFullPath)
			{
				CSetSettings setSettings;
				CString strDrawingsFolder = setSettings.GetSetting("DrawingsFolder");
				if (strDrawingsFolder.GetLength() > 0)
				{
					strDiagramName = strDrawingsFolder + strDiagramName;
				}
			}
		}
	}
	setDiagrams.Close();

	return strDiagramName;
}

void CDlgPo::OnCancel()
{
	m_bDirty = m_bDirty || m_gridLabor.IsDirty();
	m_bDirty = m_bDirty || m_POPropSheet.IsDirty();
	m_bDirty = m_bDirty || m_NotesPropSheet.IsDirty();
	
	if (m_bDirty)
	{
		if (IDYES == MessageBox("Discard Changes?", "Question", MB_ICONQUESTION | MB_YESNO))
		{
			CDialog::OnCancel();
		}
	}
	else
	{
		CDialog::OnCancel();
	}
}

void CDlgPo::OnEnChangeDrawingNumber()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	m_bDirty = true;
}

void CDlgPo::CloseCancelActivities( int iOrderID)
{
	try
	{
		CString strDateTime = CGlobals::GetCurrentSystemTime().Format("%Y-%m-%d %H:%M:%S");
		CString strSQL;
		strSQL.Format("UPDATE ActivityList SET ClosedByID = %d, ClosedDate = '%s' WHERE OrderID = %d AND ActivityTypeID = %d AND ClosedByID IS NULL", CGlobals::GetEmployeeID(), strDateTime, iOrderID, CGlobals::ACTIVITY_CANCELLED_PO_RECEIVED);
		g_dbFlooring.ExecuteSQL(strSQL);
	}
	catch (CDBException* e)
	{
		CString strMsg = e->m_strError;
		::MessageBox(NULL, strMsg, "Could not close CANCEL PO RECEIVED activity!", MB_OK);
		e->Delete();
	}
}

void CDlgPo::CloseChangeActivities( int iOrderID)
{
	try
	{
		CString strDateTime = CGlobals::GetCurrentSystemTime().Format("%Y-%m-%d %H:%M:%S");
		CString strSQL;
		strSQL.Format("UPDATE ActivityList SET ClosedByID = %d, ClosedDate = '%s' WHERE OrderID = %d AND ActivityTypeID = %d AND ClosedByID IS NULL", CGlobals::GetEmployeeID(), strDateTime, iOrderID, CGlobals::ACTIVITY_CHANGED_PO_RECEIVED);
		g_dbFlooring.ExecuteSQL(strSQL);
	}
	catch (CDBException* e)
	{
		CString strMsg = e->m_strError;
		::MessageBox(NULL, strMsg, "Could not close CHANGE PO RECEIVED activity!", MB_OK);
		e->Delete();
	}
}