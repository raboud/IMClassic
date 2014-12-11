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

#include "DlgDeletePOConfirm.h"
#include "DlgTransferPO.h"
#include "DlgChangePONumber.h"
#include "SetCustomer.h"
#include "SetStores.h"
#include "SetActionReport.h"
#include "DlgFind.h"
#include "SetVwOrderBasicLaborDetails.h"
#include "SetViewOrderSOMerchandiseDetails.h"
#include "SetSettings.h"
#include "DlgPONotesList.h"

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

	long lRow = 0;
	SetNumberRows (0, false) ;

	//Add the Row Heading to the grid
	while (!m_setPickList.IsEOF())
	{
		AppendRow() ;
		lRow = GetNumberRows() - 1;

		CString strTemp ;

		strTemp.Format("%d", m_setPickList.m_OrderID);
		QuickSetText(ID, lRow, strTemp);
		QuickSetText(PO, lRow, m_setPickList.m_PurchaseOrderNumber) ;
		QuickSetText(ORDER_DATE, lRow, m_setPickList.m_OrderDate.Format( "%Y/%m/%d" ));

		if (m_setPickList.m_Scheduled)
		{
			strTemp.Format("%s %s", m_setPickList.m_ScheduleStartDate.Format( "%Y/%m/%d" ), (m_setPickList.m_ScheduledAM) ? "AM" : "PM");
			QuickSetText(SCHED_START_DATE, lRow, strTemp );
		}

		QuickSetText(MATERIAL_TYPE, lRow, m_setPickList.m_ShortName ) ;

		if (!m_setPickList.IsFieldNull(&m_setPickList.m_Total))
		{
			QuickSetNumber(MAT_SIZE, lRow, m_setPickList.m_Total);
		}

		QuickSetBool(REPORTS, lRow, m_setPickList.m_HasReports == 1);

		QuickSetBool(NOTES, lRow, m_setPickList.m_HasNotes == 1) ;

		UpdateRowColor(lRow);

		m_setPickList.MoveNext();

	}

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

		//** Add the Menu Items
		if (CGlobals::HasPermission("CanAddPO"))
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
			if (iNumSelected == 1)
			{
				m_pPrintMenu->AppendMenu(MF_STRING, 3001, "Invoices") ;
			}
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
				m_pViewMenu->AppendMenu(MF_STRING, 3105, "Invoice") ;
				m_pViewMenu->AppendMenu(MF_STRING, 3101, "Selected PO") ;
			}
			
			m_pViewMenu->AppendMenu(MF_STRING, 3102, "Work Order") ;
			m_pViewMenu->AppendMenu(MF_STRING, 3103, "Release") ;
			
			if (CGlobals::RequiresWoodWaiver((long)QuickGetNumber(ID, row)))
			{
				m_pViewMenu->AppendMenu(MF_STRING, 3104, "F&&I Wood Waiver") ;
			}						

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
				
				nGrayed = (CGlobals::HasPermission("CanEditPONumber")) ? 0 : MF_GRAYED;
				m_pModifyMenu->AppendMenu(MF_STRING | nGrayed, 3201, "Change PO Number") ;

				nGrayed = (CGlobals::HasPermission("CanDeletePO")) ? 0 : MF_GRAYED;
				m_pModifyMenu->AppendMenu(MF_STRING | nGrayed, 3200, "Delete PO") ;

				nGrayed = (CGlobals::HasPermission("CanTransferPO")) ? 0 : MF_GRAYED;
				m_pModifyMenu->AppendMenu(MF_STRING | nGrayed, 3202, "Transfer PO") ;

				nGrayed = (IsInvoicedNotPaid(row) && CGlobals::HasPermission("CanUnInvoicePO")) ? 0 : MF_GRAYED;
				m_pModifyMenu->AppendMenu(MF_STRING | nGrayed, 3204, "Un-Invoice PO") ;
			}

			if (iNumSelected > 1)
			{
				nGrayed = 0;
				
				nGrayed = (CGlobals::HasPermission("CanDeletePO")) ? 0 : MF_GRAYED;
				m_pModifyMenu->AppendMenu(MF_STRING | nGrayed, 3200, "Delete POs") ;

				nGrayed = (CGlobals::HasPermission("CanTransferPO")) ? 0 : MF_GRAYED;
				m_pModifyMenu->AppendMenu(MF_STRING | nGrayed, 3202, "Transfer POs") ;
			}

			if (iNumSelected == 2)
			{
				UINT nGrayed = 0;
				
				nGrayed = (CGlobals::HasPermission("CanSwapPONumbers")) ? 0 : MF_GRAYED;
				m_pModifyMenu->AppendMenu(MF_STRING | nGrayed, 3203, "Swap PO Numbers") ;
			}
			m_menu->AppendMenu(MF_POPUP, (UINT) m_pModifyMenu->m_hMenu, "Modify") ;
			m_menu->AppendMenu(MF_STRING, 3210, "Update PO from SPN") ;
			
			int iOrderID = atoi(QuickGetText(ID, row));
			if (CGlobals::OrderIsReviewed(iOrderID) == true)
			{
				if (CGlobals::HasPermission("CanMarkPOReviewed"))
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
				PrintPaperWork(CGlobals::PM_ALL) ;
				break ;
		
			case 3001:
				PrintPaperWork(CGlobals::PM_INVOICE) ;
				break ;

			case 3105:
				ViewPaperWork(CGlobals::PM_INVOICE) ;
				break ;

			case 3002 :
				PrintPaperWork(CGlobals::PM_WORKORDER) ;
				break ;

			case 3003:
				PrintPaperWork(CGlobals::PM_WAIVER) ;
				break ;

			case 3004:
				PrintPaperWork(CGlobals::PM_DIAGRAMS) ;
				break ;

			case 3005:
				PrintPaperWork(CGlobals::PM_STORE_PICKUP) ;
				break ;

			case 3006:
				PrintPaperWork(CGlobals::PM_PO) ;
				break ;

			case 3007:
				this->PrintReviewChecklist();
				break;

			case 3008:
				this->PrintSchedulingChecklist();
				break;

			case 3009:
				PrintPaperWork(CGlobals::PM_WOODWAIVER);
				break;

			case 3101:
				ViewPaperWork(CGlobals::PM_PO);
				break;

			case 3102:
				ViewPaperWork(CGlobals::PM_WORKORDER);
				break;

			case 3103:
				ViewPaperWork(CGlobals::PM_WAIVER);
				break;

			case 3104:
				ViewPaperWork(CGlobals::PM_WOODWAIVER);
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

void CPOPickList::ViewPaperWork(CGlobals::PRINT_MODE enMode)
{
	GetSelectedPOs();
	CGlobals::PreparePaperWork(&m_listPOs, enMode, false);
}

void CPOPickList::PrintReviewChecklist()
{
	GetSelectedPOs() ;
	POSITION pos = m_listPOs.GetHeadPosition() ;
	while (pos)
	{
		int iOrderID = m_listPOs.GetNext(pos);
		CGlobals::PreparePaperWork(iOrderID, CGlobals::PM_REVIEW_CHECKLIST, true);	
	}		
}

void CPOPickList::PrintSchedulingChecklist()
{
	GetSelectedPOs() ;
	POSITION pos = m_listPOs.GetHeadPosition() ;
	while (pos)
	{
		int iOrderID = m_listPOs.GetNext(pos);
		CGlobals::PreparePaperWork(iOrderID, CGlobals::PM_SCHEDULE_CHECKLIST, true);	
	}		
}

void CPOPickList::PrintWoodFlooringWaiver()
{
	GetSelectedPOs() ;
	CGlobals::PreparePaperWork(&m_listPOs, CGlobals::PM_WOODWAIVER, true);
}

void CPOPickList::UpdatePO()
{
	GetSelectedPOs() ;

	CGlobals::SPNUpdatePO(&m_listPOs);
	Update(m_lCustomerId) ;
}

void CPOPickList::PrintPaperWork(CGlobals::PRINT_MODE enMode)
{
	GetSelectedPOs();
	CGlobals::PreparePaperWork(&m_listPOs, enMode, true);
	Update(m_lCustomerId) ;
	RedrawAll() ;
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

	setSODetails.m_strFilter.Format("(([OrderID] = '%d') AND (Deleted = 0) and (Quantity > 0) and [NotNeeded] = 0)", iOrderID);
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
	int iUserID = CGlobals::GetEmployeeID();
	
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