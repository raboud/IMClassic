/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// GridDiscrepancies.h: interface for the CGridDiscrepancies class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDDISCREPANCIES_H__D61C34FE_6981_45D3_AF81_A7880F6BB448__INCLUDED_)
#define AFX_GRIDDISCREPANCIES_H__D61C34FE_6981_45D3_AF81_A7880F6BB448__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CFGrid.h"

class CGridDiscrepancies : public CCFGrid  
{
public:
	CGridDiscrepancies();
	virtual ~CGridDiscrepancies();

	virtual void OnMenuCommand(int col,long row,int section,int item);
	virtual int OnMenuStart(int col,long row,int section);
	virtual void OnSetup();
	virtual void OnSH_DClicked(int col,long row, RECT *rect, POINT *point, BOOL processed) ;
	virtual void OnDClicked(int col,long row, RECT *rect, POINT *point, BOOL processed) ;
	virtual int OnCellTypeNotify(long ControlID, int col, long row, long msg, long param) ;
	virtual int OnHint(int col, long row, int section, CString *string, int *maxwidth);
	void Update() ;
	void SetPOList(CPoList* pListPOs, bool bShowReviewed = false, bool bUpdateGrid = true);
	void UpdateRecordSet();

protected:
	// menu items
	enum {CORRECT_DISCREPANCY = 2000, DELETE_DISCREPANCY} ;

	// columns
	enum {ID = -1, PO_NUMBER, STORE_NUMBER, CUSTOMER, DISC_TYPE, DISC_SUBTYPE, /*CUSTSTOREID, */CURRENT_DATA, NEW_DATA, REVIEWED, ORG_REVIEWED, CAN_REVIEW_ALERT,/*XML_FILE_PATH, DATE_FOUND,*/ LAST} ;

	void CorrectDiscrepancy(long row) ;
	bool HandleDiscrepancy(int DiscType, int DiscSubType, long DetailID, long OrderID, 
						   CString CurrentData, CString NewData, CString XMLFilePath, COleDateTime DTFound);

	bool CanReviewAlertForCustomer();

	virtual bool IsRowDirty(long lRow);
	virtual bool IsColumnDirty(int iCol, long lRow);

	int OnCanSizeTopHdg();
	BOOL OnCanSizeCol(int col);

	void UpdateRowHeights();
	int GetMaxRowHeight(int iColumnID1, int iColumnID2, long lRow);

	bool m_bConsolidatedView;
	CPoList m_listPOs;
	CString m_strRecordSetFilter;

	long m_lCustomerID;

	bool m_bShowReviewed;

};

#endif // !defined(AFX_GRIDSTORES_H__D61C34FE_6981_45D3_AF81_A7880F6BB448__INCLUDED_)
