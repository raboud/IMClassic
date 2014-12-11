/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// POPickList.cpp: implementation of the CPOPickList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "POPickList.h"
#include "DlgPOEntry.h"
#include "SetPayments.h"
#include "SetDiscrepancies.h"
#include "Globals.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//extern CMultiDocTemplate* g_pTemplateWorkOrder ;
extern CMultiDocTemplate* g_pTemplateInvoice ;
//extern CMultiDocTemplate* g_pTemplateReportRelease ;
//extern CMultiDocTemplate* g_pTemplateViewStorePickup ;

#include "DlgDeletePOConfirm.h"
#include "DlgTransferPO.h"
#include "DlgChangePONumber.h"
#include "SetCustomer.h"
#include "SetStores.h"
#include "SetActionReport.h"
#include "DlgFind.h"
#include "SetVwOrderBasicLaborDetails.h"
#include "SetViewOrderSOMerchandiseDetails.h"
#include "InstallerJobData.h"
//#include "DlgSpnDownload.h"
#include "DlgWebService.h"
#include "SetOrderDiagrams.h"
#include "SetSettings.h"
#include "DlgPONotesList.h"
#include "DlgWebService.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPOPickList::CPOPickList()
: m_setOrders(&g_dbFlooring),
  m_setPickList(&g_dbFlooring)
{
	m_pPrintMenu = NULL ;
	m_pViewMenu = NULL;
	m_pModifyMenu = NULL;
	
	m_setOrders.m_strFilter = "OrderID = -1";
	m_setOrders.Open() ;

	m_setPickList.m_strFilter = "OrderID = -1";
	m_setPickList.Open();
}

CPOPickList::~CPOPickList()
{
	delete m_pPrintMenu ;
	delete m_pViewMenu;
	delete m_pModifyMenu;
	m_setOrders.Close() ;
	m_setPickList.Close();
}

void CPOPickList::OnSetup()
{
	CCFGrid::OnSetup() ;

	AddColumn("  ID  ", ID);
	AddColumn("PO Number  ", PO);
	AddColumn("Material Type", MATERIAL_TYPE);
	AddColumn("Order Date", ORDER_DATE);
	AddColumn("Sched Start Date   ", SCHED_START_DATE);
	//AddColumn("Sched End Date   ", SCHED_END_DATE);
	AddColumn("Size   ", MAT_SIZE);
	AddColumn("Notes", NOTES);
	AddColumn("Reports", REPORTS);

	InitColumnHeadings();

	CUGCell cell;

	GetColDefault(NOTES, &cell) ;
	cell.SetCellType( UGCT_CHECKBOX );
	cell.SetCellTypeEx( UGCT_CHECKBOXCHECKMARK|UGCT_CHECKBOXUSEALIGN );
	cell.SetAlignment( UG_ALIGNCENTER|UG_ALIGNVCENTER );
	cell.SetReadOnly(TRUE) ;
	SetColDefault(NOTES, &cell) ;
	SetColDefault(REPORTS, &cell) ;

	GetColDefault(MAT_SIZE, &cell);
	cell.SetNumberDecimals(2) ;
	SetColDefault(MAT_SIZE, &cell);

	EnableMenu(TRUE) ;
	SetMultiSelectMode(TRUE);
}

void CPOPickList::Update(long lCustomerID)
{
	m_lCustomerId = lCustomerID ;

	CWaitCursor cWait ;
	EnableUpdate(0);

	while(GetNumberRows())
	{
		DeleteRow(0) ;
	}

	m_setPickList.m_strFilter.Format("[CustomerID] = '%d'", m_lCustomerId) ;
	m_setPickList.m_strSort = "[OrderDate] DESC,[PurchaseOrderNumber]" ;
	m_setPickList.Requery() ;
//	m_setOrders.m_strFilter.Format("[CustomerID] = '%d' AND Deleted = 0", m_lCustomerId) ;
//	m_setOrders.m_strSort = "[OrderDate] DESC,[PurchaseOrderNumber]" ;
//	m_setOrders.Requery() ;

	long lRow = 0;
	SetNumberRows (0, false) ;

//	CSetMaterialType setMT(&g_dbFlooring) ;
//	setMT.Open() ;
	
	//Add the Row Heading to the grid
	//while (!m_setOrders.IsEOF())
	while (!m_setPickList.IsEOF())
	{
		AppendRow() ;
		lRow = GetNumberRows() - 1;

		CString strTemp ;

		strTemp.Format("%d", m_setPickList.m_OrderID);
		/*setMT.m_strFilter.Format("[MaterialTypeID] = '%d'", m_setOrders.m_MaterialTypeID) ;
		setMT.Requery() ;*/
		QuickSetText(ID, lRow, strTemp);
		QuickSetText(PO, lRow, m_setPickList.m_PurchaseOrderNumber) ;
		QuickSetText(ORDER_DATE, lRow, m_setPickList.m_OrderDate.Format( "%Y/%m/%d" ));

		//CSetVwOrderBasicLaborDetails setDetails(&g_dbFlooring) ;
		//setDetails.m_strFilter.Format("([OrderID] = '%d' and [Deleted] = 0 and [PrintOnWO] = 1)", m_setOrders.m_OrderID) ;
		//setDetails.Open() ;
		//double fSize = 0 ;
		//while (!setDetails.IsEOF())
		//{
		//	fSize += setDetails.m_InstallQuantity ;
		//	setDetails.MoveNext() ;
		//}
		//setDetails.Close() ;

		if (m_setPickList.m_Scheduled)
		//if (!m_setPickList.IsFieldNull(&m_setPickList.m_ScheduleStartDate))
		{
			strTemp.Format("%s %s", m_setPickList.m_ScheduleStartDate.Format( "%Y/%m/%d" ), (m_setPickList.m_ScheduledAM) ? "AM" : "PM");
			QuickSetText(SCHED_START_DATE, lRow, strTemp );
			
			//strTemp.Format("%s", m_setPickList.m_ScheduleEndDate.Format( "%Y/%m/%d" ));
			//QuickSetText(SCHED_END_DATE, lRow, strTemp );
		}

		//QuickSetText(MATERIAL_TYPE, lRow, setMT.m_ShortName ) ;
		QuickSetText(MATERIAL_TYPE, lRow, m_setPickList.m_ShortName ) ;

		//CUGCell cell ;
		//GetCell(MAT_SIZE, lRow, &cell) ;
		//cell.SetNumberDecimals(2) ;
		//cell.SetNumber(fSize) ;
		//SetCell(MAT_SIZE, lRow, &cell) ;
		if (!m_setPickList.IsFieldNull(&m_setPickList.m_Total))
		{
			QuickSetNumber(MAT_SIZE, lRow, m_setPickList.m_Total);
		}

		QuickSetBool(REPORTS, lRow, m_setPickList.m_HasReports == 1);

		QuickSetBool(NOTES, lRow, m_setPickList.m_HasNotes == 1) ;

		UpdateRowColor(lRow);

		//m_setOrders.MoveNext() ;
		m_setPickList.MoveNext();

		//lRow++ ;
	}
	//setMT.Close() ;

	EnableUpdate(TRUE);
	RedrawAll();
}

void CPOPickList::OnSH_DClicked(int col,long row, RECT * /* rect */, POINT * /* point */, BOOL /* processed */)
{
	UNREFERENCED_PARAMETER(col);

	if ((row < GetNumberRows()) && (row >= 0))
	{
		m_listPOs.RemoveAll();
		m_listPOs.AddTail(int(QuickGetNumber(-1, row)));
		
		CDlgPo dlgPo ;
		dlgPo.SetPOList(&m_listPOs);

		if (dlgPo.DoModal() != IDCANCEL)
		{        
			Update(m_lCustomerId) ;
		}
	}
}

void CPOPickList::OnDClicked(int col,long row, RECT *rect, POINT *point, BOOL processed)
{
	OnSH_DClicked(col, row, rect, point, processed) ;
}

int CPOPickList::OnMenuStart(int col, long row, int section)
{
	BOOL bShowMenu = FALSE;

	UINT nGrayed = 0;

	if (section == UG_GRID)
	{
		//* Empty the Menu!!
		EmptyMenu();

		CPermissions perm;

		//** Add the Menu Items
		if (perm.HasPermission("CanAddPO"))
		{
            AddMenuItem(1000,"New PO");
		}

		if ((row >= 0) && (row < this->GetNumberRows()))
		{
			int iNumSelected = 0;
			if (col < 0)
			{
				iNumSelected = 1;
				m_listPOs.RemoveAll();
				m_listPOs.AddTail(int(QuickGetNumber(-1, row)));

			}
			else if (col > -1)
			{
				iNumSelected = GetSelectedPOs();
			}

			CString strOrderId = QuickGetText(-1, row) ;

			m_setPickList.m_strFilter.Format("[OrderID] = %d", atoi(strOrderId)) ;
			m_setPickList.Requery() ;

			if (QuickGetBool(NOTES, row))
			{
				AddMenuItem(4002, "Notes List") ;
			}
			else
			{
				AddMenuItem(4003, "New Note") ;
			}
			
			if (!m_setPickList.m_Cancelled)
			{
				AddMenuItem(4001, "Cancel PO") ;
			}
			else
			{
				AddMenuItem(4000, "Un-Cancel PO") ;
			}

			if (QuickGetBool(REPORTS, row))
			{
				AddMenuItem(4004, "Customer Sat. Report List") ;
			}
			else
			{
				AddMenuItem(4005, "New Customer Sat. Report") ;
			}

			if (m_pPrintMenu != NULL)
			{
				delete m_pPrintMenu ;
			}
			m_pPrintMenu = new CMenu ;

			m_pPrintMenu->CreateMenu() ;
			
			m_pPrintMenu->AppendMenu(MF_STRING, 3000, "All Paperwork") ;
			m_pPrintMenu->AppendMenu(MF_STRING, 3001, "Invoices") ;
			m_pPrintMenu->AppendMenu(MF_STRING, 3002, "Work Order") ;
			m_pPrintMenu->AppendMenu(MF_STRING, 3003, "Release") ;
			if (CGlobals::RequiresWoodWaiver((long)QuickGetNumber(ID, row)))
			{
				m_pPrintMenu->AppendMenu(MF_STRING, 3009, "F&&I Wood Waiver");
			}			
			m_pPrintMenu->AppendMenu(MF_STRING, 3004, "Diagram") ;
			if (!CGlobals::HasStorePickup((long)QuickGetNumber(ID, row)))
			{
				nGrayed = 1;
			}
			m_pPrintMenu->AppendMenu(MF_STRING | nGrayed, 3005, "Store Pickup") ;
			m_pPrintMenu->AppendMenu(MF_STRING, 3006, "Selected POs") ;

			if (iNumSelected == 1)
			{
				m_pPrintMenu->AppendMenu(MF_STRING, 3007, "Review Checklist") ;
				m_pPrintMenu->AppendMenu(MF_STRING, 3008, "Scheduling Checklist") ;
			}
			
			this->m_menu->AppendMenu(MF_POPUP, (UINT) m_pPrintMenu->m_hMenu, "Print") ;

			if (m_pViewMenu != NULL)
			{
				delete m_pViewMenu ;
			}
			m_pViewMenu = new CMenu ;

			m_pViewMenu->CreateMenu() ;			
			
			if (iNumSelected == 1)
			{
				m_pViewMenu->AppendMenu(MF_STRING, 3101, "Selected PO") ;
			}
			
			m_pViewMenu->AppendMenu(MF_STRING, 3102, "Work Order") ;
			m_pViewMenu->AppendMenu(MF_STRING, 3103, "Release") ;
			
			if (CGlobals::RequiresWoodWaiver((long)QuickGetNumber(ID, row)))
			{
				m_pViewMenu->AppendMenu(MF_STRING, 3104, "F&&I Wood Waiver") ;
			}						
			
			//if (iNumSelected > 1)
			//{
				//m_pViewMenu->AppendMenu(MF_STRING /*| nGrayed*/, 3205, "View Selected POs") ;
			//}

			this->m_menu->AppendMenu(MF_POPUP, (UINT) m_pViewMenu->m_hMenu, "View") ;

			if (m_pModifyMenu != NULL)
			{
				delete m_pModifyMenu ;
			}
			m_pModifyMenu = new CMenu;
			m_pModifyMenu->CreateMenu();

			if (iNumSelected == 1)
			{
				nGrayed = 0;
				
				nGrayed = (perm.HasPermission("CanEditPONumber")) ? 0 : MF_GRAYED;
				m_pModifyMenu->AppendMenu(MF_STRING | nGrayed, 3201, "Change PO Number") ;

				nGrayed = (perm.HasPermission("CanDeletePO")) ? 0 : MF_GRAYED;
				m_pModifyMenu->AppendMenu(MF_STRING | nGrayed, 3200, "Delete PO") ;

				nGrayed = (perm.HasPermission("CanTransferPO")) ? 0 : MF_GRAYED;
				m_pModifyMenu->AppendMenu(MF_STRING | nGrayed, 3202, "Transfer PO") ;

				nGrayed = (IsInvoicedNotPaid(row) && perm.HasPermission("CanUnInvoicePO")) ? 0 : MF_GRAYED;
				m_pModifyMenu->AppendMenu(MF_STRING | nGrayed, 3204, "Un-Invoice PO") ;
			}

			if (iNumSelected > 1)
			{
				nGrayed = 0;
				
				nGrayed = (perm.HasPermission("CanDeletePO")) ? 0 : MF_GRAYED;
				m_pModifyMenu->AppendMenu(MF_STRING | nGrayed, 3200, "Delete POs") ;

				nGrayed = (perm.HasPermission("CanTransferPO")) ? 0 : MF_GRAYED;
				m_pModifyMenu->AppendMenu(MF_STRING | nGrayed, 3202, "Transfer POs") ;
			}

			if (iNumSelected == 2)
			{
				UINT nGrayed = 0;
				
				nGrayed = (perm.HasPermission("CanSwapPONumbers")) ? 0 : MF_GRAYED;
				m_pModifyMenu->AppendMenu(MF_STRING | nGrayed, 3203, "Swap PO Numbers") ;
			}
			m_menu->AppendMenu(MF_POPUP, (UINT) m_pModifyMenu->m_hMenu, "Modify") ;
			m_menu->AppendMenu(MF_STRING, 3210, "Update PO from SPN") ;
			
			int iOrderID = atoi(QuickGetText(ID, row));
			if (CGlobals::OrderIsReviewed(iOrderID) == true)
			{
				if (perm.HasPermission("CanMarkPOReviewed"))
				{
					AddMenuItem(4006, "Mark Order Un-Reviewed") ;
				}
			}

		}
		bShowMenu = TRUE;
	}
	
	return bShowMenu ;
}

void CPOPickList::OnMenuCommand(int /* col */, long row, int section, int item)
{
	if (section == UG_GRID)
	{
		switch (item)
		{
			case 1000 :
				NewPo() ;
				break ;
		
			case 3000:
				PrintPaperWork(PM_ALL) ;
				break ;
		
			case 3001:
				PrintPaperWork(PM_INVOICE) ;
				break ;

			case 3002 :
				PrintPaperWork(PM_WORKORDER) ;
				break ;

			case 3003:
				PrintPaperWork(PM_WAIVER) ;
				break ;

			case 3004:
				PrintPaperWork(PM_DIAGRAMS) ;
				break ;

			case 3005:
				PrintPaperWork(PM_STORE_PICKUP) ;
				break ;

			case 3006:
				this->PrintPO() ;
				break ;

			case 3007:
				this->PrintReviewChecklist();
				break;

			case 3008:
				this->PrintSchedulingChecklist();
				break;

			case 3009:
				PrintPaperWork(PM_WOODWAIVER);
				break;

			case 3101:
				ViewPaperWork(PM_PO);
				break;
			case 3102:
				ViewPaperWork(PM_WORKORDER);
				break;

			case 3103:
				ViewPaperWork(PM_WAIVER);
				break;

			case 3104:
				ViewPaperWork(PM_WOODWAIVER);
				break;

			case 3200:
				{
					// delete PO
					bool bContinue = false;
					int iNewCallNotesOrderID = -1;
					int iNewActionReportsOrderID = -1;
					CDlgDeletePOConfirm dlgDeletePO;
					dlgDeletePO.SetPOList(&m_listPOs);
					if (dlgDeletePO.CanDeletePO())
					{
						if (HasNotes())
						{
							int iResponse = MessageBox("There are call notes associated with the order(s) you wish to delete.\nDo you want to transfer these call notes to another order for the same customer?\n\nChoose 'Yes' to transfer the call notes, 'No' to delete the call notes, 'Cancel' to quit without any changes", "Info", MB_YESNOCANCEL);
							if (iResponse == IDYES)
							{
								// try to get a valid order id to transfer to
								if (GetOrderIDForTransfer(iNewCallNotesOrderID))
								{
									// got a valid order id, so we should continue
									bContinue = true;
								}
								else
								{
									MessageBox("Delete cancelled.  No records were changed.", "Info", MB_OK);
								}
							}
							else if (iResponse == IDNO)
							{
								// set flag so we can go ahead and delete
								bContinue = true;
							}
						}
						else
						{
							bContinue = true;
						}

						if (bContinue)
						{
							bContinue = false;
							if (HasActionReports())
							{
								int iResponse = MessageBox("There are action reports associated with the order(s) you wish to delete.\nDo you want to transfer these action reports to another order for the same customer?\n\nChoose 'Yes' to transfer the action reports, 'No' to delete the action reports, 'Cancel' to quit without any changes", "Info", MB_YESNOCANCEL);
								if (iResponse == IDYES)
								{
									// try to get a valid order id to transfer to
									if (GetOrderIDForTransfer(iNewActionReportsOrderID))
									{
										// got a valid order id, so we should continue
										bContinue = true;
									}
									else
									{
										MessageBox("Delete cancelled.  No records were changed.", "Info", MB_OK);
									}
								}
								else if (iResponse == IDNO)
								{
									// set flag so we can go ahead and delete
									bContinue = true;
								}
							}
							else
							{
								bContinue = true;
							}

							if (bContinue)
							{
								bool bTransactionCommitted = false;
								if (g_dbFlooring.BeginTrans())
								{
									if ( TransferCallNotes(iNewCallNotesOrderID) )
									{
										if ( TransferActionReports(iNewActionReportsOrderID) )
										{
											// ok, any call notes / action reports were transferred
											// successfully, so go ahead and try deleting the PO.
											if ( dlgDeletePO.DoModal() == IDOK)
											{
												// the PO was marked for deletion (i.e. we are in a transaction)

												// commit the transaction we started above so the call
												// notes and action reports get transferred properly
												if ( g_dbFlooring.CommitTrans() )
												{
													bTransactionCommitted = true;
												}
												else
												{
													// at this point, all we know is the commit failed,
													// below we will rollback the transaction 
													MessageBox("There was an error committing the transaction for deleting these P.O.s.", "Notice");
												}

												// update the grid
												Update(m_lCustomerId) ;
											}
										}
										else
										{
											MessageBox("There was an error transferring the action reports.  No records were changed.");
										}
									}
									else
									{
										MessageBox("There was an error transferring the call notes.  No records were changed.");
									}
								}
								else
								{
									MessageBox("There was a transaction error while trying to delete the records.  No records were deleted.");
								}
								
								if (!bTransactionCommitted)
								{
									g_dbFlooring.Rollback();
								}
							}
						}
					}
					else
					{
						MessageBox("This PO cannot be deleted since it is either referenced by a check or a job.", "Notice");
					}
				}
				break;
			case 3201:
				{
					// Change PO Number
					POSITION pos = m_listPOs.GetHeadPosition();
					int iOrderID = m_listPOs.GetNext(pos);

					CString strPONumber = CGlobals::POFromOrderID(iOrderID) ;
					if (strPONumber.GetLength() == 0)
					{
						MessageBox("There was an error finding the selected PO in the database.", "Error!");
						break;
					}

					CDlgChangePONumber dlgChangePO;
					dlgChangePO.SetOrderID(iOrderID);
					dlgChangePO.SetCurrentPONumber(strPONumber);

					if (dlgChangePO.DoModal() == IDOK)
					{
						Update(m_lCustomerId) ;
					}
				}
				break;
			case 3202:
				{
					// transfer PO
					CDlgTransferPO dlg;
					CString strCustName = "";
					CString strPONumber = "";

					CSetCustomer setCustomer(&g_dbFlooring);
					setCustomer.m_strFilter.Format("[CustomerID] = %d", m_lCustomerId);
					setCustomer.Open();
					if (!setCustomer.IsEOF())
					{
						strCustName = setCustomer.m_FirstName.MakeUpper() + " " + setCustomer.m_LastName.MakeUpper();
					}
					else
					{
						MessageBox("There was an error finding the current customer in the database.", "Error!");
						break;
					}

					POSITION pos = m_listPOs.GetHeadPosition();
					int iOrderID = m_listPOs.GetNext(pos);

					strPONumber = CGlobals::POFromOrderID(iOrderID) ;
					if (strPONumber.GetLength() == 0)
					{
						MessageBox("There was an error finding the selected PO in the database.", "Error!");
						break;
					}

					dlg.SetInfo(strCustName, m_lCustomerId, &m_listPOs);
					
					if (dlg.DoModal() == IDOK)
					{
						Update(m_lCustomerId) ;
					}
				}
				break;
			case 3203:
				{
					// swap PO Numbers
					POSITION pos = m_listPOs.GetHeadPosition();
					int iOrderID1 = m_listPOs.GetNext(pos);
					int iOrderID2 = m_listPOs.GetNext(pos);
					if (SwapPONumbers(iOrderID1, iOrderID2))
					{
						Update(m_lCustomerId) ;
					}
				}
				break;
			case 3204:
				{
					UnInvoice(row);
				}
				break;
			case 3205:
				{
					ViewConsolidatedPOs();
				}
				break;

			case 3210:
				UpdatePO() ;
				break ;

			case 4000: // uncancel PO
			case 4001:
				{
					// Cancel PO
					long lRow ;
					int iCol ;
					long lLastRow = -1 ;

					EnumFirstSelected(&iCol, &lRow) ;
					do
					{
						if (lRow != lLastRow)
						{
							CString strOrderId = QuickGetText(-1, lRow) ;

							m_setOrders.m_strFilter.Format("[OrderID] = '%s'", strOrderId) ;
							m_setOrders.Requery() ;

							m_setOrders.Edit() ;
							m_setOrders.m_Cancelled = (item == 4001) ;
							m_setOrders.Update() ;
						}
						lLastRow = lRow ;
					} while (this->EnumNextSelected(&iCol, &lRow) == UG_SUCCESS) ;
					Update(m_lCustomerId) ;
				}
				break ;

			case 4002 :
				CalledList() ;
				break ;

			case 4003:
				NewCall() ;
				break ;

			case 4004 :
				ReportList() ;
				break ;

			case 4005:
				NewReport() ;
				break ;

			case 4006:
				{
					int iCol;
					long lRow;
					EnumFirstSelected(&iCol, &lRow) ;
					int iOrderID = atoi(QuickGetText(ID, lRow));
					SetPOReviewed(iOrderID, false);
					UpdateRowColor(lRow);
					RedrawRow(lRow);
				}

				break ;

			default :
				break ;
		}

	}
}

void CPOPickList::OnKeyDown(UINT *vcKey, BOOL /* processed */)
{	
	if (*vcKey == VK_INSERT)
	{
		NewPo() ;
	}
}

void CPOPickList::NewPo()
{
	CDlgPOEntry dlgPOEntry;
	dlgPOEntry.SetCustomerID(m_lCustomerId);
	if (dlgPOEntry.DoModal() == IDOK)
	{
		CDlgPo dlgPo ;
		dlgPo.SetCustomerId(m_lCustomerId) ;
		dlgPo.SetPONumber(dlgPOEntry.GetPONumber(), dlgPOEntry.GetStoreNumber());
		dlgPo.SetPOType(dlgPOEntry.GetPOType());
		dlgPo.SetOrigPONumber(dlgPOEntry.GetOrigPONumber());
		dlgPo.SetMaterialTypeShortName(dlgPOEntry.GetMaterialTypeShortName());
		if (dlgPo.DoModal() == IDOK)
		{
			Update(m_lCustomerId) ;
		}
	}
}

int CPOPickList::OnEditStart(int /* col */, long /* row */, CWnd ** /* edit */)
{
	return FALSE ;
}

bool CPOPickList::InitPOList(PRINT_MODE enMode)
{
	bool bOK = true;

	m_listPOs.RemoveAll();

	//Add the Column Heading to the grid
	int iCol ;
	long lRow ;
	long lLastRow = -1 ;

	CWaitCursor curWait ;

	if (enMode != PM_DIAGRAMS)
	{
		if (IsNotPresent())
		{
			if (MessageBox("Not all material is present. Continue printing paperwork?", "Materials", MB_YESNO) == IDNO )
			{
				return false;
			}
		}
	}

	EnumFirstSelected(&iCol, &lRow) ;
	do
	{
		if (lRow != lLastRow)
		{
			if ((enMode == PM_INVOICE) || (enMode == PM_ALL))
			{
				CSetOrders setOrders(&g_dbFlooring) ;
				setOrders.m_strFilter.Format("[OrderId] = '%d'", int(QuickGetNumber(-1, lRow))) ;
				setOrders.m_strSort = "[PurchaseOrderNumber]" ;
				setOrders.Open() ;
				if (!setOrders.IsEOF())
				{
					if (!setOrders.m_Warrenty && (enMode == PM_INVOICE))
					{
						CFrameWnd* pFrame = g_pTemplateInvoice->CreateNewFrame(NULL,NULL) ;
						if (pFrame != NULL)
						{
							pFrame->InitialUpdateFrame(NULL, false) ;
							CViewInvoice* pView = (CViewInvoice*) pFrame->GetActiveView() ;
							pView->SetPo(int(QuickGetNumber(-1, lRow))) ;
							pView->SendMessage(WM_COMMAND, ID_FILE_PRINT, 0l) ;
						}
						else
						{
							MessageBox("Error trying to print Invoice...Please try to reprint.", "Error", MB_OK);
						}
					}
				}
				setOrders.Close() ;
			}
			m_listPOs.AddTail(int(QuickGetNumber(-1, lRow)));
		}
		lLastRow = lRow ;
	} while (this->EnumNextSelected(&iCol, &lRow) == UG_SUCCESS) ;

	return bOK;
}

void CPOPickList::ViewPaperWork(PRINT_MODE enMode)
{
	if ( !InitPOList(enMode) )
	{
		return;
	}

	if ( (enMode == PM_PO))
	{
		CFlooringApp* pApp = (CFlooringApp*) AfxGetApp();
		POSITION pos = m_listPOs.GetHeadPosition() ;
		if (pos)
		{
			pApp->ViewPO(m_listPOs.GetNext(pos));
		}
	}

	if ( (enMode == PM_WORKORDER) )
	{
		CFlooringApp* pApp = (CFlooringApp*) AfxGetApp();
		pApp->ViewWorkOrder(&m_listPOs);		
	}

	if ( (enMode == PM_WAIVER) )
	{
		CFlooringApp* pApp = (CFlooringApp*) AfxGetApp();
		pApp->ViewWaiver(&m_listPOs);		
	}

	if ( (enMode == PM_WOODWAIVER))
	{
		CFlooringApp* pApp = (CFlooringApp*) AfxGetApp();
		POSITION pos = m_listPOs.GetHeadPosition() ;
		if (pos)
		{
			pApp->ViewWoodFlooringWaiver(m_listPOs.GetNext(pos));
		}
	}
}

void CPOPickList::PrintPO()
{
	GetSelectedPOs() ;

	CFlooringApp* pApp = (CFlooringApp*) AfxGetApp();
	POSITION pos = m_listPOs.GetHeadPosition() ;
	while (pos)
	{
		pApp->PrintPO(m_listPOs.GetNext(pos));
	}

	Update(m_lCustomerId) ;
}

void CPOPickList::PrintReviewChecklist()
{
	CFlooringApp* pApp = (CFlooringApp*) AfxGetApp();
	POSITION pos = m_listPOs.GetHeadPosition() ;
	while (pos)
	{
		int iOrderID = m_listPOs.GetNext(pos);
		pApp->PrintReviewChecklist(iOrderID);	
	}		
}

void CPOPickList::PrintSchedulingChecklist()
{
	CFlooringApp* pApp = (CFlooringApp*) AfxGetApp();
	POSITION pos = m_listPOs.GetHeadPosition() ;
	while (pos)
	{
		int iOrderID = m_listPOs.GetNext(pos);
		pApp->PrintSchedulingChecklist(iOrderID);	
	}		
}

void CPOPickList::PrintWoodFlooringWaiver()
{
	CFlooringApp* pApp = (CFlooringApp*) AfxGetApp();
	POSITION pos = m_listPOs.GetHeadPosition() ;
	while (pos)
	{
		int iOrderID = m_listPOs.GetNext(pos);
		pApp->PrintWoodFlooringWaiver(iOrderID);
	}		
}

void CPOPickList::UpdatePO()
{
	GetSelectedPOs() ;

	CDlgWebService dlg;
	dlg.SPNUpdatePO(&m_listPOs);
	Update(m_lCustomerId) ;
}

void CPOPickList::PrintPaperWork(PRINT_MODE enMode)
{
	if ( !InitPOList(enMode) )
	{
		return;
	}

	if ((enMode == PM_WORKORDER) || (enMode == PM_ALL))
	{
		CFlooringApp* pApp = (CFlooringApp*) AfxGetApp();
		pApp->PrintWorkOrder(&m_listPOs);		
	}

	if ((enMode == PM_DIAGRAMS) || (enMode == PM_ALL))
	{
		CSetOrderDiagrams setOrderDiagrams(&g_dbFlooring) ;
		setOrderDiagrams.m_strFilter = "OrderID = -1";
		setOrderDiagrams.Open() ;

		CSetOrders setOrders(&g_dbFlooring) ;
		setOrders.m_strFilter = "OrderID = -1";
		setOrders.Open() ;

		POSITION pos = m_listPOs.GetHeadPosition() ;
		while(pos)
		{
			int iOrderID = m_listPOs.GetNext(pos);
			setOrderDiagrams.m_strFilter.Format("[OrderID] = '%d'", iOrderID) ;
			setOrderDiagrams.Requery() ;
			if (!setOrderDiagrams.IsEOF())
			{
				if (!setOrderDiagrams.IsFieldNull(&setOrderDiagrams.m_DiagramNumber) && !setOrderDiagrams.IsFieldNull(&setOrderDiagrams.m_DiagramDateTime))
				{
					CString strTimeStamp = setOrderDiagrams.m_DiagramDateTime.Format("%m/%d/%y %H:%M") ;
					setOrders.m_strFilter.Format("[OrderId] = '%d'", iOrderID) ;
					setOrders.Requery() ;
					if (!setOrders.IsEOF())
					{
						CWaitCursor curWait ;
						CString strStoreNumber = CGlobals::StoreNumberFromOrderID(iOrderID);
						CString strPONumber = setOrders.m_PurchaseOrderNumber;
						CString strInstallNumber = setOrders.m_CustOrderNo.Trim();
						CString strMeasureNumber = setOrderDiagrams.m_DiagramNumber;
						CString strCalc = setOrderDiagrams.m_DiagramDateTime.Format("%m/%d/%y %H:%M");
						if ( !CInstallerJobData::GetDrawing(true, strStoreNumber, strPONumber, strInstallNumber, strMeasureNumber, setOrderDiagrams.m_DiagramDateTime) )
						{
							MessageBox("Drawing Number or Calculation date is invalid", "Diagram", MB_OK) ;
						}
					}
					else
					{
						MessageBox("Order Number could not be found.", "Diagram", MB_OK) ;
					}
				}
				else if (!setOrderDiagrams.IsFieldNull(&setOrderDiagrams.m_DiagramFileName))
				{
					// if there is no measure number / measure date/time, it was probably a drawing sent via SOSI
					// and is therefore only accessible via the name
					if (setOrderDiagrams.m_DiagramFileName.GetLength() > 0)
					{
						CSetSettings setSettings(&g_dbFlooring);
						CString strDiagramFolder = setSettings.GetSetting("DrawingsFolder");
						CString strFileName = strDiagramFolder + setOrderDiagrams.m_DiagramFileName;
						if (PathFileExists(strFileName))
						{
							ShellExecute(NULL, "print", strFileName, NULL, NULL, SW_HIDE ) ;
						}
						else
						{
							MessageBox("Could not find file: " + strFileName, "Diagram", MB_OK) ;
						}
					}
				}
			}
		}
	}
	if ((enMode == PM_WAIVER) || (enMode == PM_ALL))
	{
		CFlooringApp* pApp = (CFlooringApp*) AfxGetApp();
		pApp->PrintWaiver(&m_listPOs);	
	}
	if ((enMode == PM_WOODWAIVER) || (enMode == PM_ALL))
	{
		CFlooringApp* pApp = (CFlooringApp*) AfxGetApp();
		POSITION pos = m_listPOs.GetHeadPosition() ;
		while (pos)
		{
			int iOrderID = m_listPOs.GetNext(pos);
			if (CGlobals::RequiresWoodWaiver(iOrderID))
			{
				pApp->PrintWoodFlooringWaiver(iOrderID);
			}
		}	
	}
	if ((enMode == PM_STORE_PICKUP) || (enMode == PM_ALL))
	{
		/*if (!CGlobals::HasStorePickup(&m_listPOs))
		{
			return;
		}*/

		CFlooringApp* pApp = (CFlooringApp*) AfxGetApp();
		POSITION pos = m_listPOs.GetHeadPosition() ;
		while (pos)
		{
			int iOrderID = m_listPOs.GetNext(pos);
			if (CGlobals::HasStorePickup(iOrderID))
			{
				pApp->PrintStorePickup(iOrderID);
			}
		}	
	}
	
	Update(m_lCustomerId) ;
	RedrawAll() ;
}

bool CPOPickList::IsNotPresent()
{
	int iCol ;
	long lRow ;
	long lLastRow = -1 ;
	CString strFilter = "" ;
	CSetViewOrderSOMerchandiseDetails set(&g_dbFlooring);
	set.m_strFilter = "((" ;
	bool bFirst = true ;
	bool bAllPresent = true ;

	EnumFirstSelected(&iCol, &lRow) ;
	do
	{
		if (lRow != lLastRow)
		{
			if (!bFirst)
			{
				set.m_strFilter += " OR " ;
			}
			strFilter.Format("[OrderId] = '%d'", int(QuickGetNumber(-1, lRow))) ;
			set.m_strFilter += strFilter ;
			bFirst = false ;
		}
		lLastRow = lRow ;
	} while (this->EnumNextSelected(&iCol, &lRow) == UG_SUCCESS) ;
	set.m_strFilter += ") and (Deleted = 0) and (Quantity > 0))" ;
	set.Open() ;

	while (!set.IsEOF())
	{
		if (set.m_MaterialStatusID == 1)
		{
			bAllPresent = false ;
		}
		set.MoveNext() ;
	}
	set.Close() ;

	return !bAllPresent ;
}

void CPOPickList::CalledList()
{
	if (GetSelectedPOs() == 1)
	{
		CDlgPONotesList dlg ;
		dlg.SetOrderId(m_listPOs.GetHead()) ;
		if (dlg.DoModal() == IDOK)
		{
			Update(m_lCustomerId) ;
		}
	}
	else
	{
		MessageBox("You must select one and only one PO.", "Notes List", MB_OK) ;
	}
}

void CPOPickList::NewCall()
{
	if (GetSelectedPOs() == 1)
	{
		CDlgPONoteEntry dlg;
		int iOrderID = m_listPOs.GetHead();
		dlg.SetOrderID(iOrderID) ;
		if (dlg.DoModal() == IDOK)
		{
			if (dlg.m_bSendToExpeditor)
			{
				//SendToExpeditor(dlg.GetNoteID(), dlg.m_bCopyToSASM, dlg.m_bCopyToExpeditorEmail);
				CGlobals::QueueNoteForExpeditor(dlg.GetNoteID(), dlg.m_bCopyToSASM, dlg.m_bCopyToExpeditorEmail);
			}
			Update(m_lCustomerId) ;
		}
	}
	else
	{
		MessageBox("You must select one and only one PO.", "Notes List", MB_OK) ;
	}
}

//void CPOPickList::SendToExpeditor(int iNoteID, bool CopyToSASM, bool CopyToExpeditorEmail)
//{
//	CDlgWebService dlg;
//	dlg.SPNAddExpeditorNote(iNoteID, CopyToSASM, CopyToExpeditorEmail);
//}

void CPOPickList::ReportList()
{
	if (GetSelectedPOs() == 1)
	{
		CDlgReportList dlg ;
		dlg.SetOrderId(m_listPOs.GetHead()) ;
		if (dlg.DoModal() == IDOK)
		{
			Update(m_lCustomerId) ;
		}
	}
	else
	{
		MessageBox("You must select one and only one PO.", "Report List", MB_OK) ;
	}
}

void CPOPickList::NewReport()
{
	if ( GetSelectedPOs() == 1)
	{
		CDlgActionReport dlg ;
		dlg.SetOrderId(m_listPOs.GetHead()) ;
		if (dlg.DoModal() == IDOK)
		{
			Update(m_lCustomerId) ;
		}
	}
	else
	{
		MessageBox("You must select one and only one PO.", "Notes List", MB_OK) ;
	}
}

int CPOPickList::GetSelectedPOs()
{
	m_listPOs.RemoveAll();
	
	int iCol ;
	long lRow ;
	long lLastRow = -1 ;
	
	EnumFirstSelected(&iCol, &lRow) ;
	do
	{
		if (lRow != lLastRow)
		{
			m_listPOs.AddTail(int(QuickGetNumber(-1, lRow)));
		}
		lLastRow = lRow ;
	} while (this->EnumNextSelected(&iCol, &lRow) == UG_SUCCESS) ;

	return m_listPOs.GetCount();
}

bool CPOPickList::SwapPONumbers(int iOrderID1, int iOrderID2)
{
	bool bSwapOK = false;
	bool bRefreshPrices = false;
	
	int iStoreID1 = -1;
	int iStoreID2 = -1;

	try
	{
		CSetOrders setOrders(&g_dbFlooring) ;
		setOrders.m_strFilter.Format("[OrderID] = %d OR [OrderID] = %d", iOrderID1, iOrderID2);
		setOrders.Open() ;

		while (!setOrders.IsEOF())
		{
			setOrders.MoveNext();
		}

		setOrders.MoveFirst();

		if (setOrders.GetRecordCount() == 2)
		{
			// init values from first record
			iStoreID1 = setOrders.m_StoreID;
			CString strPO1 = setOrders.m_PurchaseOrderNumber;

			setOrders.MoveNext();

			// init values from second record
			iStoreID2 = setOrders.m_StoreID;
			CString strPO2 = setOrders.m_PurchaseOrderNumber;

			if (iStoreID1 != iStoreID2)
			{
				CSetStores setStores(&g_dbFlooring);
				setStores.m_strFilter.Format("[StoreID] = %d OR [StoreID] = %d", iStoreID1, iStoreID2);
				setStores.Open();
				
				int iStoreTypeID1 = setStores.m_StoreTypeID;
				int iMarketID1 = setStores.m_MarketId;
				setStores.MoveNext();
				int iStoreTypeID2 = setStores.m_StoreTypeID;
				int iMarketID2 = setStores.m_MarketId;
				setStores.Close();

                if ( iStoreTypeID1 == iStoreTypeID2 )
				{
					if (iMarketID1 != iMarketID2)
					{
						bRefreshPrices = true;
					}
				}
				else
				{
					// we have a store type Id mismatch
					setOrders.Close();
					MessageBox("The store types do not match, therefore \nthese two P.O. numbers cannot be swapped.", "Notice");
					return false;
				}
			}
			
			setOrders.Edit();
			setOrders.m_PurchaseOrderNumber = strPO1;
			setOrders.Update();
			setOrders.MovePrev();
			setOrders.Edit();
			setOrders.m_PurchaseOrderNumber = strPO2;
			setOrders.Update();
			setOrders.Close();
			if (bRefreshPrices)
			{
				CGlobals::RefreshPrices(iOrderID1);
				CGlobals::RefreshPrices(iOrderID2);
			}
			bSwapOK = true;
		}
	}
	catch (CDBException* e)
	{
		MessageBox(e->m_strError, "Error!");
		e->Delete();
	}

	return bSwapOK;
}

bool CPOPickList::HasNotes()
{
	// returns true if there are call notes associated with any of the selected orders
	bool bHasNotes = false;

	CString strOrderIDFilter = GetOrderIDFilter();

	CSetPONotes setNotes(&g_dbFlooring);
	setNotes.m_strFilter = strOrderIDFilter;
	setNotes.Open();

	if (!setNotes.IsEOF())
	{
		bHasNotes = true;
	}
	setNotes.Close();

	return bHasNotes;
}

bool CPOPickList::TransferCallNotes(int iOrderID)
{
	bool bSuccess = false;

	if (iOrderID == -1)
	{
		return true;
	}

	CSetPONotes setPONotes(&g_dbFlooring);
	setPONotes.m_strFilter = GetOrderIDFilter();
	setPONotes.Open();
	if (!setPONotes.IsEOF())
	{
		// update the order Id fields of all the calls matching the set of selected orders
		while (!setPONotes.IsEOF())
		{
			setPONotes.Edit();
			setPONotes.m_OrderID = iOrderID;
			setPONotes.Update();
			setPONotes.MoveNext();
		}
		bSuccess = true;
	}
	else
	{
		MessageBox("No matching records found!", "Record Not Found") ;
	}
	setPONotes.Close();

	return bSuccess;
}

bool CPOPickList::GetOrderIDForTransfer(int& iNewOrderID)
{
	// this just gets and validates the orderid for where the call notes should be transferred to
	bool bSuccess = false;

	CDlgFind dlg(CDlgFind::EnFIND_TYPE_ORDERID, this) ;
	dlg.SetCaption("Enter Order Number") ;
	dlg.SetMaxChars(6);
	
	bool bContinue = true;
	do
	{
		int iReturnValue = dlg.DoModal();
		if (iReturnValue == IDCANCEL)
		{
			bContinue = false;
		}
		else
		{
			// convert the orderid to an int
			iNewOrderID = atoi(dlg.m_strNumber);

			// verify this is a valid order id
			CSetOrders setOrders(&g_dbFlooring);
			setOrders.m_strFilter.Format("[OrderId] = %d", iNewOrderID);
			setOrders.Open();
			if (setOrders.IsEOF())
			{
				//not a valid order id
				MessageBox("The Order Number you entered does not appear to be a valid Order Number.", "Error");
				iNewOrderID = -1;
			}
			else
			{
                // verify the order id entered isn't in the list to be deleted
				POSITION pos = m_listPOs.GetHeadPosition();
				bool bFoundDup = false;
				while(pos)
				{
					int iOrderID = m_listPOs.GetNext(pos);
					if (iNewOrderID == iOrderID)
					{
						MessageBox("You entered an Order Number that matches one of the Order Numbers to be deleted.", "Error");
						iNewOrderID = -1;
						bFoundDup = true;
						break;
					}
				}
				if (!bFoundDup)
				{
					bContinue = false;
					bSuccess = true;
				}
			}
			setOrders.Close();
		}
	}
	while (bContinue);

	return bSuccess;
}

CString CPOPickList::GetOrderIDFilter()
{
	CString strOrderIDFilter = "";

	POSITION pos = m_listPOs.GetHeadPosition();
	while(pos)
	{
		int iOrderID = m_listPOs.GetNext(pos);
		if (strOrderIDFilter.GetLength() > 0)
		{
			strOrderIDFilter += " OR ";
		}
		CString strTemp;
		strTemp.Format("([OrderId] = %d)", iOrderID);
		strOrderIDFilter += strTemp;
	}

	return strOrderIDFilter;
}

bool CPOPickList::HasActionReports()
{
	// returns true if there are call notes associated with any of the selected orders
	bool bHasActionReports = false;

	CString strOrderIDFilter = GetOrderIDFilter();

	CSetActionReport setActionReports(&g_dbFlooring);
	setActionReports.m_strFilter = strOrderIDFilter;
	setActionReports.Open();

	if (!setActionReports.IsEOF())
	{
		bHasActionReports = true;
	}
	setActionReports.Close();

	return bHasActionReports;
}

bool CPOPickList::TransferActionReports(int iOrderID)
{
	bool bSuccess = false;

	if (iOrderID == -1)
	{
		return true;
	}

	CSetActionReport setReports(&g_dbFlooring);
	setReports.m_strFilter = GetOrderIDFilter();
	setReports.Open();
	if (!setReports.IsEOF())
	{
		// update the order Id fields of all the calls matching the set of selected orders
		while (!setReports.IsEOF())
		{
			setReports.Edit();
			setReports.m_OrderID = iOrderID;
			setReports.Update();
			setReports.MoveNext();
		}
		bSuccess = true;
	}
	else
	{
		MessageBox("No matching records found!", "Record Not Found") ;
	}

	return bSuccess;
}

int CPOPickList::GetFirstColumnIndex()
{
	return ID+1;
}

int CPOPickList::GetLastColumnIndex()
{
	return LAST;
}

bool CPOPickList::IsInvoicedNotPaid(long row)
{
	int OrderID = atoi(QuickGetText(ID, row));
    m_setOrders.m_strFilter.Format("[OrderID] = '%d'", OrderID) ;
	m_setOrders.Requery() ;

	CSetPayments setPayments(&g_dbFlooring);
	setPayments.m_strFilter.Format("[OrderID] = '%d'", OrderID) ;
	setPayments.Open();

	bool bHasPayments = !setPayments.IsEOF();          // if EOF, then we have no payments for this orderid

	return ((m_setOrders.m_Billed) && (!m_setOrders.m_Paid) && !bHasPayments);
}

void CPOPickList::UnInvoice(long lRow)
{
	int iOrderID = atoi(QuickGetText(ID, lRow));
	m_setOrders.m_strFilter.Format("[OrderID] = '%d'", iOrderID) ;
	m_setOrders.Requery();

	m_setOrders.Edit();
	m_setOrders.m_Billed = FALSE;
	m_setOrders.SetFieldNull(&m_setOrders.m_BilledAmount);
	m_setOrders.SetFieldNull(&m_setOrders.m_BilledDate);
	m_setOrders.Update();
	m_setOrders.Requery();
	
	m_setPickList.m_strFilter.Format("[OrderID] = '%d'", iOrderID) ;
	m_setPickList.Requery();

	UpdateRowColor(lRow);
	RedrawRow(lRow);
}

void CPOPickList::UpdateRowColor(long lRow)
{
	if (lRow >= 0)
	{
		int iOrderID = atoi(QuickGetText(ID, lRow));

		// reset colors
		SetRowColor(lRow, CGlobals::COLOR_BLACK, CCFGrid::EnColorMode_TEXT);
		SetRowColor(lRow, CGlobals::COLOR_WHITE, CCFGrid::EnColorMode_BACK);

		if (CGlobals::OrderHasAlerts(iOrderID, true) || (CGlobals::OrderIsReviewed(iOrderID) == false))
		{
			if (m_setPickList.m_Cancelled)
			{
				SetRowColor(lRow, CGlobals::COLOR_RED, CCFGrid::EnColorMode_TEXT);
				SetRowColor(lRow, CGlobals::COLOR_ALERT, CCFGrid::EnColorMode_BACK);
			}
			else
			{
				SetRowColor(lRow, CGlobals::COLOR_BLUE, CCFGrid::EnColorMode_TEXT);
				SetRowColor(lRow, CGlobals::COLOR_ALERT, CCFGrid::EnColorMode_BACK);
			}
		}
		else if (m_setPickList.m_Cancelled)
		{
			SetRowColor (lRow, CGlobals::COLOR_CANCELED,	enMODE_CANCELED) ;
		}
		else if (m_setPickList.m_Warranty & m_setPickList.m_Billed)
		{
			SetRowColor (lRow, CGlobals::COLOR_WAR_COMP,	enMODE_WAR_COMP) ;
		}
		else if (m_setPickList.m_Billed && m_setPickList.m_Paid)
		{
			SetRowColor (lRow, CGlobals::COLOR_INV_PAID,	enMODE_INV_PAID) ;
		}
		else if (m_setPickList.m_Scheduled & !m_setPickList.m_Billed)
		{
			SetRowColor (lRow, CGlobals::COLOR_SCHEDULED,	enMODE_SCHEDULED) ;
		}
		else if (m_setPickList.m_Warranty & !m_setPickList.m_Billed)
		{
			SetRowColor (lRow, CGlobals::COLOR_WARRENTY,	enMODE_WARRENTY) ;
		}
		else if (m_setPickList.m_Paid)
		{
			SetRowColor (lRow, CGlobals::COLOR_PAID,		enMODE_PAID) ;
		}
		else if (m_setPickList.m_Billed)
		{
			SetRowColor (lRow, CGlobals::COLOR_INVOICED,	enMODE_INVOICED) ;
		}
		else if (!IsMaterialPresent(iOrderID))
		{
			SetRowColor (lRow, CGlobals::COLOR_NO_MATER,	enMODE_NO_MATER) ;
		}
	}
}

bool CPOPickList::IsMaterialPresent(int iOrderID)
{
	bool bPresent = true ;
	CSetViewOrderSOMerchandiseDetails setSODetails(&g_dbFlooring);

	setSODetails.m_strFilter.Format("(([OrderID] = '%d') AND (Deleted = 0) and (Quantity > 0))", iOrderID);
	setSODetails.Open();
	while (!setSODetails.IsEOF())
	{
		bPresent = bPresent && ((setSODetails.m_MaterialStatusID == 2) ||(setSODetails.m_MaterialStatusID == 4) || (setSODetails.m_MaterialStatusID == 11)) ;
		setSODetails.MoveNext() ;
	}
	setSODetails.Close() ;

	return bPresent;
}

void CPOPickList::InitSelectedPOs()
{
	m_listPOs.RemoveAll();

	int iCol;
	long lRow;
	long lLastRow = -1 ;

	EnumFirstSelected(&iCol, &lRow) ;
	do
	{
		if (lRow != lLastRow)
		{
			m_listPOs.AddTail(int(QuickGetNumber(-1, lRow)));
		}
		lLastRow = lRow ;
	} while (EnumNextSelected(&iCol, &lRow) == UG_SUCCESS) ;
}

void CPOPickList::ViewConsolidatedPOs()
{
	InitSelectedPOs();
	CDlgPo dlgPo ;
	dlgPo.SetPOList(&m_listPOs);
    
	dlgPo.DoModal();
}

void CPOPickList::SetPOReviewed(int iOrderID, bool bReviewed)
{
	int iReviewed = bReviewed ? 1 : 0;

	CFlooringApp* pApp = (CFlooringApp*) AfxGetApp() ;
	int iUserID = pApp->GetEmployeeID();
	
	CString strSQL;
	strSQL.Format("UPDATE Orders SET Reviewed = %d, ReviewedDate = '%s', ReviewedByID = %d WHERE OrderID = %d", iReviewed, CGlobals::GetCurrentSystemTime().Format(), iUserID, iOrderID);
	g_dbFlooring.ExecuteSQL(strSQL);
    
}

bool CPOPickList::IsRowDirty(long lRow)
{
	UNREFERENCED_PARAMETER(lRow);
	return false;
}

bool CPOPickList::IsColumnDirty(int iCol, long lRow)
{
	UNREFERENCED_PARAMETER(lRow);
	UNREFERENCED_PARAMETER(iCol);
	return false;
}