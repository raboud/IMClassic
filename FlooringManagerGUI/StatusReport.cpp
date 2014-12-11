/*----------------------------------------------------------------------
	Copyright © 2001-2002 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// StatusReport.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "StatusReport.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "SetOrderAndCustomer.h"
#include "SetMaterialOrderDetailed.h"

const int iSEPARATOR = 10 ;

/////////////////////////////////////////////////////////////////////////////
// CStatusReport

IMPLEMENT_DYNCREATE(CStatusReport, CCFScrollView)

CStatusReport::CStatusReport()
{
	this->m_strStoreNumber = "" ;
	this->m_iDetailLevel = 1 ;
}

CStatusReport::~CStatusReport()
{
	m_listString.RemoveAll() ;
}


BEGIN_MESSAGE_MAP(CStatusReport, CCFScrollView)
	//{{AFX_MSG_MAP(CStatusReport)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatusReport drawing

void CStatusReport::OnInitialUpdate()
{
//	CFont* def_font = SelectFont(120, "Arial", pDC);
	CCFScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = 1000;
//	BuildReport() ;
	sizeTotal.cy = m_iLineHeight * m_iReport ;
//	SetScrollSizes(MM_TEXT, sizeTotal);
}

void CStatusReport::OnDraw(CDC* pDC)
{
	CFont* def_font = SelectFont(100, "Lucida Console", pDC);
	CRect rect ;
	
	this->GetClientRect(&rect) ;
	// TODO: calculate the total size of this view

	int iYPos = rect.top ;
	int iHeight ;
	m_Pos = m_listString.GetHeadPosition() ;
	while (m_Pos != NULL)
	{
		iHeight = PrintLine(pDC, 0, iYPos, rect.Width()) ; 
		iYPos += iHeight ;

		if (m_Pos != NULL)
		{
			pDC->MoveTo(0, iYPos + (iSEPARATOR/2)) ;
			pDC->LineTo(rect.Width(), iYPos + (iSEPARATOR/2)) ;
			iYPos += iSEPARATOR ;
		}
	}
	CSize sizeTotal;
	CSize sizePage ;
	CSize sizeLine ;

	sizePage.cx = rect.Width() - 40;
	sizePage.cy = rect.Height() ;
	sizeLine.cx = rect.Width() - 40;
	sizeLine.cy = m_iLineHeight ;

	sizeTotal.cy = iYPos ;
	sizeTotal.cx = rect.Width() - 40;
	SetScrollSizes(MM_TEXT, sizeTotal, sizePage, sizeLine);

	pDC->SelectObject(def_font);
}

/////////////////////////////////////////////////////////////////////////////
// CStatusReport diagnostics

#ifdef _DEBUG
void CStatusReport::AssertValid() const
{
	CCFScrollView::AssertValid();
}

void CStatusReport::Dump(CDumpContext& dc) const
{
	CCFScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStatusReport message handlers


BOOL CStatusReport::OnPreparePrinting(CPrintInfo* pInfo) 
{
	DeterminePageBreaks() ;
	pInfo->SetMaxPage(m_pageOffsets.GetSize() - 1) ;
	
	return CCFScrollView::OnPreparePrinting(pInfo);
}

void CStatusReport::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	GotoPage(pInfo->m_nCurPage) ;
	CCFScrollView::OnPrint(pDC, pInfo);
}

void CStatusReport::DeterminePageBreaks()
{
	CDC	dc ;

	CreateDefaultPrinterDC(&dc) ;
	// Do something with the font just created...
	CFont* def_font = SelectFont(100, "Lucida Console", &dc);
//	m_iLinesPerPage = 70 ;

	m_Pos = m_listString.GetHeadPosition() ;
	CString strStoreNumber = "" ;
	int iPages = 0 ;
	int iPixelsForStore = 0;
	int iIndex = 0 ;
	m_pageOffsets.SetSize(0, 1) ;

	if (m_iReport > 0)
	{
		while (m_Pos)
		{
			CString strLine = m_listString.GetNext(m_Pos) ;

			if (GetStoreNumber(strLine).Compare(strStoreNumber))
			{
				strStoreNumber = GetStoreNumber(strLine) ;
				m_pageOffsets.Add(iIndex) ;
				iPages++ ;
				iPixelsForStore = 0;
			}
			iPixelsForStore += Lines( strLine) * m_iLineHeight + iSEPARATOR ;

			if (iPixelsForStore > m_iPixelPageBodyY)
			{
				iPages++ ;
				m_pageOffsets.Add(iIndex) ;
				iPixelsForStore = (Lines( strLine) * m_iLineHeight) + iSEPARATOR;
			}
			iIndex++ ;
		}
	}
	m_pageOffsets.Add(iIndex) ;
	dc.SelectObject(def_font);

}

void CStatusReport::GotoPage(int iPageNumber)
{
	if (m_iReport > 0)
	{
		CTime timeDate ;
		timeDate = CTime::GetCurrentTime() ;

		m_Pos = m_listString.FindIndex(m_pageOffsets[(iPageNumber - 1)]) ;
		m_PosNextPage = m_listString.FindIndex(m_pageOffsets[(iPageNumber)]) ;

		CString strLine = m_listString.GetAt(m_Pos) ;

		m_strTitle.Format("STORE %s - STATUS REPORT - %s", GetStoreNumber(strLine), timeDate.Format("%Y/%m/%d")) ;
	}
}

void CStatusReport::PrintPageBody(CDC *pDC, CPrintInfo *pInfo)
{
	// Do something with the font just created...
	CFont* def_font = SelectFont(100, "Lucida Console", pDC);

	int iYPos = pInfo->m_rectDraw.top ;
	int iHeight = 0 ;

	if (m_iReport > 0)
	{
		CString strLine = m_listString.GetAt(m_Pos) ;
		CString strStore = GetStoreNumber(strLine) ;

	//	while (m_Pos && (!strStore.Compare(GetStoreNumber(strLine.Mid(1)))) && (iYPos < (pInfo->m_rectDraw.bottom - (m_iLineHeight * Lines(strLine)))))
		while (m_Pos != m_PosNextPage)
		{
	//		strStore = GetStoreNumber(strLine.Mid(1)) ;

			iHeight = PrintLine(pDC, pInfo->m_rectDraw.left, iYPos, pInfo->m_rectDraw.Width() + 10) ;
			iYPos += iHeight ;

			if (m_Pos != m_PosNextPage)
			{
				pDC->MoveTo(pInfo->m_rectDraw.left, iYPos + (iSEPARATOR/2)) ;
				pDC->LineTo(pInfo->m_rectDraw.right, iYPos + (iSEPARATOR/2)) ;
				iYPos += iSEPARATOR ;
	//			strLine = m_listString.GetAt(m_Pos) ;
			}
		} 
	}
	pDC->SelectObject(def_font);
}

int CStatusReport::PrintLine(CDC *pDC, int iX, int iY, int iW)
{
	CString strOut ;
	int iHeight = 0 ;

	iHeight = DrawAlignedText(pDC, &iX, &iY, int(iW), m_listString.GetNext(m_Pos).Mid(5), DT_LEFT) ;

	return iHeight ;

}

void CStatusReport::BuildReport()
{
	CWaitCursor curWait ;
	CSetOrderAndCustomer setOrders(&g_dbFlooring)  ;
	CSetMaterialOrderDetailed setDetails(&g_dbFlooring)  ;
	CSetCallDetails setCalls(&g_dbFlooring)  ;

	m_iReport = 0 ;
	m_listString.RemoveAll() ;

	if (m_strStoreNumber == "")
	{
		setOrders.m_strFilter = "(([Paid] = 0 AND [Billed] = 1 AND [Warrenty] = 0) or [Billed] = 0) and [Cancelled] = 0" ;
		setOrders.m_strSort = "[StoreNumber], [PurchaseOrderNumber]" ;
		setOrders.Open() ;

		setDetails.m_strFilter.Format("(([Paid] = 0 AND [Billed] = 0 AND [Warrenty] = 0 and [Cancelled] = 0 ) or ([MatStatusID] = 3)) AND IsPadding = 0") ;
		setDetails.m_strSort = "[StoreNumber], [PurchaseOrderNumber]" ;
		setDetails.Open() ;

		setCalls.m_strSort = "[StoreNumber], [PurchaseOrderNumber]" ;
		setCalls.Open() ;
	}
	else
	{
		setOrders.m_strFilter.Format("(([Paid] = 0 AND [Billed] = 1 AND [Warrenty] = 0) or [Billed] = 0) and [Cancelled] = 0 and [StoreNumber] = '%s'", m_strStoreNumber) ;
		setOrders.m_strSort = "[StoreNumber], [PurchaseOrderNumber]" ;
		setOrders.Open() ;

		setDetails.m_strFilter.Format("(([Paid] = 0 AND [Billed] = 0 AND [Warrenty] = 0 and [Cancelled] = 0 ) or ([MatStatusID] = 3)) AND IsPadding = 0 and [StoreNumber] = '%s'", m_strStoreNumber) ;
		setDetails.m_strSort = "[StoreNumber], [PurchaseOrderNumber]" ;
		setDetails.Open() ;

		setCalls.m_strFilter.Format("[StoreNumber] = '%s'", m_strStoreNumber) ;
		setCalls.m_strSort = "[StoreNumber], [PurchaseOrderNumber]" ;
		setCalls.Open() ;
	}
	CString strTemp ;
	CString strOld = "" ;

	CString strLastPO = "" ;

	while (!setDetails.IsEOF())
	{
		CString strName = setDetails.m_LastName + ", " + setDetails.m_FirstName ;
		CString strPO ;
		strPO.Format("0%-4s%-8s - %-40s - %-25s", setDetails.m_StoreNumber, setDetails.m_PurchaseOrderNumber, strName.Left(39), setDetails.m_MaterialTypeName.Left(24)) ;

		CString strStyleColor = setDetails.m_Style + " - " + setDetails.m_Color ;
		CString strQuanity ;

		if (strPO.CompareNoCase(strLastPO))
		{
			if (strLastPO.CompareNoCase(""))
			{
				m_listString.AddTail(strTemp) ;
			}
			strTemp = strPO ;
			m_iReport += 1 ;
		}

		CString strContinue ;
		strQuanity.Format ("%7.2f %2s", setDetails.m_Size, setDetails.m_Description) ;
//		if (setDetails.m_MatStatusID == 1)
		{
			strContinue.Format("\n  %-8s %s %-40s - %-20s", setDetails.m_SONumber, strQuanity, strStyleColor.Left(40), setDetails.m_Status.Left(20)) ;
		}
		strTemp += strContinue ;
		m_iReport += 1 ;
		strLastPO = strPO ;
		setDetails.MoveNext() ;
	}

	strLastPO = "" ;

	while (!setOrders.IsEOF())
	{
		CString strName = setOrders.m_LastName + ", " + setOrders.m_FirstName ;
		CString strPO ;
		strPO.Format("1%-4s%-8s - %-40s - %-25s", setOrders.m_StoreNumber, setOrders.m_PurchaseOrderNumber, strName.Left(39), setOrders.m_MaterialTypeName.Left(24)) ;

		if (strPO.CompareNoCase(strLastPO))
		{
			if (strLastPO.CompareNoCase(""))
			{
				m_listString.AddTail(strTemp) ;
			}
			strTemp = strPO ;
			m_iReport += 1 ;
		}

		CString strContinue ;
		
		if (setOrders.m_Billed && !setOrders.m_Paid)
		{
			strContinue.Format("\n  WAIVER SENT   - %s - JOB COMPLETE - NOT PAID YET", setOrders.m_BilledDate.Format("%m/%d/%Y")) ;
		}
		else if (setOrders.m_Scheduled)
		{
			strContinue.Format("\n  SCHEDULED FOR - %s", setOrders.m_ScheduleDate.Format("%m/%d/%Y")) ;
		}
		else
		{
			strContinue.Format("\n  NOT SCHEDULED") ;
		}
		strTemp += strContinue ;
		m_iReport += 1 ;
		strLastPO = strPO ;
		setOrders.MoveNext() ;
	}

	strLastPO = "" ;
	m_listString.AddTail(strTemp) ;

	while (!setCalls.IsEOF() && m_iDetailLevel > 0)
	{
		CString strName = setCalls.m_LastName + ", " + setCalls.m_FirstName ;
		CString strPO ;
		strPO.Format("2%-4s%-8s - %-40s - %-25s", setCalls.m_StoreNumber, setCalls.m_PurchaseOrderNumber, strName.Left(39), setCalls.m_MaterialTypeName.Left(24)) ;
		CString strTT = setCalls.m_SW_Text ;
		if (setCalls.m_SW_Text.CompareNoCase("Spoke with other") == 0)
		{
			if (!setCalls.IsFieldNull(&setCalls.m_Other))
			{
				strTT = "SPOKE WITH " + setCalls.m_Other ;
			}
		}
		if (setCalls.m_SW_Text != "")
		{
			strTT += "\n" ;
		}
		if (setCalls.m_NeedColor)
		{
			strTT += "NEED COLOR\n" ;
		}
		if (setCalls.m_NeedStyle)
		{
			strTT += "NEED STYLE\n" ;
		}
		if (setCalls.m_NeedDrawings)
		{
			strTT += "NEED DRAWINGS\n" ;
		}
		if (setCalls.m_NeedPadding)
		{
			strTT += "NEED PADDING PO\n" ;
		}
		if (setCalls.m_NeedLabor)
		{
			strTT += "NEED LABOR PO\n" ;
		}
		if (setCalls.m_Schedule)
		{
			strTT += "SCHEDULED\n" ;
		}
		if (setCalls.m_Unscheduled)
		{
			strTT += "UNSCHEDULED\n" ;
		}
		if (!setCalls.IsFieldNull(&setCalls.m_Comments))
		{
			strTT += setCalls.m_Comments ;
		}
		strTT.TrimRight() ;
		while (strTT.GetLength() > 0)
		{
			if (strTT.GetAt(strTT.GetLength() - 1) == '\n')
			{
				strTT = strTT.Left(strTT.GetLength() - 1) ;
			}
			else
			{
				break ;
			}
		}

		CString strT ;
		int iCR = 0 ;
		while (strTT.Replace(" \n", "\n")) ;
		while (strTT.Replace("\n\n", "\n")) ;
		while (strTT.Replace("\n ", "\n")) ;
		while (strTT.Replace("\r\n", "\n")) ;
		while (strTT.Replace("\n\r", "\n")) ;

		const int iCOMMENT_WIDTH = 36 ;
		while (strTT.Mid(iCR).GetLength() > iCOMMENT_WIDTH)
		{
			int iNextCR = (strTT.Mid(iCR)).Left(iCOMMENT_WIDTH).ReverseFind('\n') ;

			if ((iNextCR > iCOMMENT_WIDTH) || (iNextCR == -1))
			{
				int iSpace = (strTT.Mid(iCR)).Left(iCOMMENT_WIDTH).ReverseFind(' ') ;
				strTT.SetAt(iCR + iSpace, '\n') ;
				iCR += iSpace + 1 ;
			}
			else 
			{
				iCR += iNextCR + 1;
			}
		}

		strTT.Replace("\n", "\n                                               ") ;

		if (strPO.CompareNoCase(strLastPO))
		{
			if (strLastPO.CompareNoCase(""))
			{
				m_listString.AddTail(strTemp) ;
			}
			strTemp = strPO ;
			m_iReport += 1 ;
		}
//		else 
		{
			CString strContinue ;
			strContinue.Format("\n  %s - %-18s - %s", setCalls.m_Time.Format("%m/%d/%Y - %I:%M %p"), setCalls.m_Text, strTT) ;
			strTemp += strContinue ;
			m_iReport += 1 ;
		}
		strLastPO = strPO ;
		setCalls.MoveNext() ;
	}
	m_listString.AddTail(strTemp) ;
/*		else
		{
			CSetMaterialOrderDetailed setDetails ;
			setDetails.m_strFilter.Format("[MatStatusID] = 1 AND [OrderID] = '%d'", setOrders.m_OrderID);
			setDetails.Open() ;

			if (!setDetails.IsEOF())
			{
				strTemp.Format("%-50s", strName) ;
				m_iReport += 1 ;
				while (!setDetails.IsEOF())
				{
					CString str2 ;
					str2.Format("\n  WAITING ON MATERIAL - SO Number %s", setDetails.m_SONumber) ;
					strTemp += str2 ;
					m_iReport += 1 ;
					setDetails.MoveNext() ;
				} 
				m_listString.AddTail(strTemp) ;
			}
			else
			{
				CSetCalls setCalled(&g_dbFlooring) ;
				setCalled.m_strFilter.Format("[OrderID] = '%d'", setOrders.m_OrderID);
				setCalled.Open() ;
				if (!setCalled.IsEOF())
				{
					strTemp.Format("%-50s", strName) ;
					m_iReport += 1 ;
					while (!setCalled.IsEOF())
					{
						CString str2 ;
						str2.Format("\n  %s%s%s - %s", setCalled.m_Time.Format("%m/%d/%Y - %I:%M %p"), GetLocation(setCalled), GetSpokeWith(setCalled), setCalled.m_Comments) ;
						strTemp += str2 ;
						m_iReport += 1 ;
						setCalled.MoveNext() ;
					} 
					m_listString.AddTail(strTemp) ;
				}
				setCalled.Close() ;
			}
			setDetails.Close() ;
		}
		setOrders.MoveNext() ;
	}
*/
	if (m_iReport > 0)
	{
		SortReport() ;
	}

	CString strNum = "" ;

	setCalls.Close() ;
	setDetails.Close() ;
	setOrders.Close() ;
	curWait.Restore() ;
}

void CStatusReport::SortReport()
{
	CString str1 ;
	CString str2 ;
	CString str1Temp ;
	CString str2Temp ;

	POSITION pos ;
	POSITION pos1 ;
	POSITION pos2 ;

	bool bMovedOne ;

	do
	{
		bMovedOne = false ;
		pos = m_listString.GetHeadPosition() ;
		pos1 = pos ;
		str1 = m_listString.GetNext(pos) ;
		str1Temp = str1.Mid(1,83) ;
//		if ((str1.Mid(4,1).Compare(" ")))
//		{
//			str1Temp = "1" + str1.Mid(1, 79) ;
//		}

		while (pos != NULL)
		{
			pos2 = pos ;
			str2 = m_listString.GetNext(pos) ;
			str2Temp = str2.Mid(1, 83) ;
//			if ((str2.Mid(8,1).Compare(" ")))
//			{
//				str2Temp = "1" + str2.Mid(1,79) ;
//			}

			if (str2Temp.Compare(str1Temp) < 0)
			{
				bMovedOne = true ;
				m_listString.SetAt(pos1, str2) ;
				m_listString.SetAt(pos2, str1) ;
				pos1 = pos2 ;
			}
			else if (str2Temp.Compare(str1Temp) == 0)
			{
				str1 += "\n" + str2.Mid(83) ;
//				m_iReport -= 1 ;
				m_listString.SetAt(pos1, str1) ;
				m_listString.RemoveAt(pos2) ;
			}
			else
			{
				str1 = str2 ;
				str1Temp = str2Temp ;
				pos1 = pos2 ;
			}
		}
	} while (bMovedOne) ;

}
/*
CString CStatusReport::GetLocation(CSetCallDetails& set)
{
	CString str ;
	set.m
	switch (set.m_Location)
	{
		case CSetCalls::WORK :
			str = " - Called Work Number " ;
			break ;

		case CSetCalls::HOME:
			str = " - Called Home Number " ;
			break ;

		case CSetCalls::BOTH :
			str = " - Called Both Numbers" ;
			break ;

		case CSetCalls::CUSTOMER :
			str = " - Customer Called    " ;
			break ;

		case CSetCalls::CALLED_STORE :
			str = " - Called Store       " ;
			break ;

		case CSetCalls::STORE_CALLED :
			str = " - Store Called       " ;
			break ;

		case CSetCalls::FAXED_STORE :
			str = " - Faxed Store        " ;
			break ;

		case CSetCalls::STORE_FAXED :
			str = " - Store Faxed        " ;
			break ;

	}

	return str ;
}
*/
/*
CString CStatusReport::GetSpokeWith(CSetCallDetails& set)
{
	CString str ;
	switch(set.m_SpokeWith)
	{

		case CSetCalls::MR:
//			str = "Spoke with MR.     " ;
			break ;

		case CSetCalls::MS :
//			str = "Spoke with MS.     " ;
			break ;

		case CSetCalls::OTHER :
//			str.Format("%-19s", set.m_Other) ;
			break ;

		case CSetCalls::LEFT_MESSAGE:
			str = " - Left Message       " ;
			break ;

		case CSetCalls::NO_ANSWER:
			str = " - No Answer          " ;
			break ;
	}
	return str ;
}
*/
int CStatusReport::Lines(CString strLine)
{
	int iLines = 0 ;
	int iStart = 0 ;
	do 
	{
		iLines++ ;
		iStart = strLine.Find('\n', iStart + 1) ;
	} while (iStart > 0) ;
	return iLines ;
}

CString CStatusReport::GetStoreNumber(CString strLine)
{
	CString strStore = strLine ;
	strStore = strLine.Mid(1, 4) ;
//	if (strStore.GetAt(3) != ' ')
//	{
//		strStore = "1" + strLine.Left(2) ;
//	}
//	else
//	{
//		strStore = strLine.Left(3) ;
//	}
	return strStore ;

}

void CStatusReport::SetStoreNumber(CString strStoreNumber)
{
	m_strStoreNumber = strStoreNumber ;
/*	CSize sizeTotal;
	this->BuildReport() ;
	this->Invalidate() ;
*/}

void CStatusReport::SetDetailLevel(int iLevel)
{
	m_iDetailLevel = iLevel ;

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = 1000;
	BuildReport() ;
	sizeTotal.cy = m_iLineHeight * m_iReport ;
	this->Invalidate() ;
}
