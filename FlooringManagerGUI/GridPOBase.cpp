// GridPOBase.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "GridPOBase.h"

// CGridPOBase


CGridPOBase::CGridPOBase()
{
	m_bConsolidatedView = false;
	m_bInvokedFromSPN = false;
	m_bCanMarkReviewed = true;

	if (CGlobals::HasPermission("CanModifyImportedItem"))
	{
		m_bCanModifyImported = true;
	}
	else
	{
		m_bCanModifyImported = false;
	}

	m_bIsAdmin = CGlobals::IsAdmin() ;
}

CGridPOBase::~CGridPOBase()
{
}


BEGIN_MESSAGE_MAP(CGridPOBase, CCFGrid)
END_MESSAGE_MAP()



// CGridPOBase message handlers

int CGridPOBase::AppendRow()
{
	return CCFGrid::AppendRow();
}
int CGridPOBase::DeleteRow(long /* lRow */)
{
	// any grid derived from this class needs to override this function since we never really delete a row, only
	// mark it as deleted and hide it.
	ASSERT(FALSE);
	//return CCFGrid::DeleteRow(lRow);
	return 0;
}
BOOL CGridPOBase::OnCanMove(int oldcol, long oldrow, int newcol, long newrow)
{
	return CCFGrid::OnCanMove(oldcol, oldrow, newcol, newrow);
}
BOOL CGridPOBase::OnCanSizeCol(int col)
{
	return CCFGrid::OnCanSizeCol(col);
}
int CGridPOBase::OnCellTypeNotify(long ControlID,int col,long row,long msg,long param)
{
	return CCFGrid::OnCellTypeNotify(ControlID, col, row, msg, param);
}
void CGridPOBase::OnCellChange(int oldcol, int newcol, long oldrow, long newrow)
{
	CCFGrid::OnCellChange(oldcol, newcol, oldrow, newrow);
}
void CGridPOBase::OnMenuCommand(int col,long row,int section,int item)
{
	CCFGrid::OnMenuCommand(col, row, section, item);
}
int CGridPOBase::OnMenuStart(int col,long row,int section)
{
	if (m_bConsolidatedView)
	{
		return FALSE;
	}

	return CCFGrid::OnMenuStart(col, row, section);
}
void CGridPOBase::OnCharDown(UINT *vcKey, BOOL processed)
{
	CCFGrid::OnCharDown(vcKey, processed);
}
void CGridPOBase::OnKeyDown(UINT *vcKey, BOOL processed)
{
	CCFGrid::OnKeyDown(vcKey, processed);
}
int CGridPOBase::OnEditStart(int col, long row, CWnd **edit)
{
	return CCFGrid::OnEditStart(col, row, edit);
}
int CGridPOBase::OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag)
{
	return CCFGrid::OnEditFinish(col, row, edit, string, cancelFlag);
}
int CGridPOBase::OnEditContinue(int oldcol, long oldrow, int *newcol, long *newrow)
{
	return CCFGrid::OnEditContinue(oldcol, oldrow, newcol, newrow);
}
int CGridPOBase::OnSortEvaluate(CUGCell* cell1, CUGCell* cell2, int flags)
{
	return CCFGrid::OnSortEvaluate(cell1, cell2, flags);
}
void CGridPOBase::Reset()
{
	CCFGrid::ClearAllDataRows();
}
void CGridPOBase::OnDClicked(int col,long row, RECT *rect, POINT *point, BOOL processed)
{
	CCFGrid::OnDClicked(col, row, rect, point, processed);
}

void CGridPOBase::OnSetup()
{
	CCFGrid::OnSetup();
	SetHighlightRow(FALSE);
}

void CGridPOBase::UpdateGrid()
{
}

void CGridPOBase::UpdateRecordSet()
{
}

void CGridPOBase::SetPODate(COleDateTime _date)
{
	m_datePO = _date;
}

void CGridPOBase::SetPOScheduleDate(COleDateTime _date)
{
	m_datePOScheduleDate = _date;
}

void CGridPOBase::SetStoreID(int iStoreID)
{
	m_iStoreID = iStoreID;
}

void CGridPOBase::SetPOList(CPoList* pListPOs, bool bUpdateGrid /*=true*/)
{
	m_listPOs.AddHead(pListPOs);
	if (m_listPOs.GetCount() > 1)
	{
		m_bConsolidatedView = true;
	}

	m_strRecordSetFilter = "";

	int iMarketID = -1;
	int iDivisionID = -1;
	POSITION pos = m_listPOs.GetHeadPosition();
	while(pos)
	{
		int iOrderID = m_listPOs.GetNext(pos);
		if (m_strRecordSetFilter.GetLength() > 0)
		{
			m_strRecordSetFilter += " OR ";
		}
		CString strTemp;
		strTemp.Format("([OrderID] = %d)", iOrderID);
		m_strRecordSetFilter += strTemp;
		CGlobals::MarketAndDivisionFromOrderID(iOrderID, iMarketID, iDivisionID);
		m_bCanMarkReviewed = m_bCanMarkReviewed && CGlobals::HasPermission("CanReviewAlert", iMarketID, iDivisionID);
	}

	if (bUpdateGrid)
	{
		UpdateGrid();
	}
}

void CGridPOBase::CommitChanges()
{

}

bool CGridPOBase::IsDirty() 
{
	bool bDirty = false;

	long lNumRows = GetNumberRows();
	for (long lRow = 0; lRow < lNumRows; lRow++)
	{
		bDirty =bDirty || IsRowDirty(lRow);
		if (bDirty)
		{
			// no need to keep going
			break;
		}
	}

    return bDirty;
}
void CGridPOBase::UpdateColors()
{
	long lNumRows = GetNumberRows();
	for (long lRow = 0; lRow < lNumRows; lRow++)
	{
		UpdateRowColor(lRow) ;
	}
}

int CGridPOBase::GetSelectedRows()
{
	m_listRows.RemoveAll();
	
	int iCol ;
	long lRow ;
	long lLastRow = -1 ;

	EnumFirstSelected(&iCol, &lRow) ;
	do
	{
		if (lRow != lLastRow)
		{
			m_listRows.AddTail(lRow);
		}
		lLastRow = lRow ;
	} while (this->EnumNextSelected(&iCol, &lRow) == UG_SUCCESS) ;

	return m_listRows.GetCount();
}
