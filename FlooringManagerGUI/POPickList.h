/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// POPickList.h: interface for the CPOPickList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POPICKLIST_H__4CB866DE_0C32_4BC6_BDF4_1790EE5CB261__INCLUDED_)
#define AFX_POPICKLIST_H__4CB866DE_0C32_4BC6_BDF4_1790EE5CB261__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Flooring.h"
#include "stdafx.h"
#include "CFGrid.h"
#include "SetOrders.h"
#include "DialogPo.h"
#include "SetMaterialType.h"
#include "SetVwOrderBasicLaborDetails.h"
#include "DlgReportList.h"
#include "DlgPONoteEntry.h"
#include "DlgActionReport.h"
#include "SetActionReport.h"
#include "SetVwPOPickList.h"

const UINT    wm_PO_SELECT = RegisterWindowMessage( "Purchase Order Select" ) ;

class CPOPickList : public CCFGrid  
{
public:
	virtual int OnEditStart(int col, long row, CWnd **edit);
	virtual void OnKeyDown(UINT *vcKey, BOOL processed);
	virtual void OnMenuCommand(int col,long row,int section,int item);
	virtual int OnMenuStart(int col,long row,int section);
	void Update (long lCustomerID);
	virtual void OnSetup();
	CPOPickList();
	virtual ~CPOPickList();
	virtual void OnSH_DClicked(int col,long row, RECT *rect, POINT *point, BOOL processed) ;
	virtual void OnDClicked(int col,long row, RECT *rect, POINT *point, BOOL processed) ;

protected:
	enum {ID = -1, PO, MATERIAL_TYPE, ORDER_DATE, SCHED_START_DATE, MAT_SIZE, NOTES, REPORTS, LAST} ;
	void ReportList(void);
	void NewReport(void);
	void CalledList(void);
	void NewCall(void);

	void InitSelectedPOs();

	CMenu *m_pPrintMenu;
	CMenu *m_pViewMenu;
	CMenu *m_pModifyMenu;
	void PrintPaperWork(CGlobals::PRINT_MODE enMode);
	void ViewPaperWork(CGlobals::PRINT_MODE enMode);
	void InitPOList();
	int GetSelectedPOs();
	bool SwapPONumbers(int iOrderID1, int iOrderID2);
	void NewPo();

	bool HasNotes();
	bool TransferCallNotes(int iOrderID);
	
	bool HasActionReports();
	bool TransferActionReports(int iOrderID);

	virtual int GetFirstColumnIndex();
	virtual int GetLastColumnIndex();

	bool GetOrderIDForTransfer(int& iNewOrderID);
	bool IsInvoicedNotPaid(long row);
	void UnInvoice(long row);
	bool IsMaterialPresent(int iOrderID);
	virtual void UpdateRowColor(long lRow);
	CString GetOrderIDFilter();
	void ViewConsolidatedPOs();

	long m_lCustomerId;
	CSetOrders m_setOrders;
	CPoList m_listPOs;

	CSetVwPOPickList m_setPickList;

	void PrintReviewChecklist() ;
	void PrintSchedulingChecklist() ;
	void PrintInstallerChecklist();
	void PrintWoodFlooringWaiver() ;

	void ViewReviewChecklist() ;
	void ViewSchedulingChecklist() ;
	void ViewInstallerChecklist();
	void ViewWoodFlooringWaiver() ;

	void UpdatePO() ;
	void SetPOReviewed(int iOrderID, bool bReviewed);

	virtual bool IsRowDirty(long lRow);
	virtual bool IsColumnDirty(int iCol, long lRow);
};

const CPOPickList::EnColorMode enMODE_SCHEDULED	= CCFGrid::EnColorMode_TEXT;
const CPOPickList::EnColorMode enMODE_INV_PAID	= CCFGrid::EnColorMode_BACK;
const CPOPickList::EnColorMode enMODE_INVOICED	= CCFGrid::EnColorMode_BACK;
const CPOPickList::EnColorMode enMODE_PAID		= CCFGrid::EnColorMode_TEXT;
const CPOPickList::EnColorMode enMODE_CANCELED	= CCFGrid::EnColorMode_BACK;
const CPOPickList::EnColorMode enMODE_WARRENTY	= CCFGrid::EnColorMode_TEXT;
const CPOPickList::EnColorMode enMODE_WAR_COMP	= CCFGrid::EnColorMode_BACK;
const CPOPickList::EnColorMode enMODE_NO_MATER	= CCFGrid::EnColorMode_TEXT;

#endif // !defined(AFX_POPICKLIST_H__4CB866DE_0C32_4BC6_BDF4_1790EE5CB261__INCLUDED_)
