/*----------------------------------------------------------------------
	Copyright © 2001-2002 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// ReportTotals.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "ReportTotals.h"
#include "DialogDatePicker.h"
#include "DlgReportConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int iLINES_FOR_MARGIN = 2;
const int iEXTRA_SPACING = 10;

/////////////////////////////////////////////////////////////////////////////
// CReportTotals

IMPLEMENT_DYNCREATE(CReportTotals, CCFScrollView)

CReportTotals::CReportTotals()
: m_setTotalMaterial(&g_dbFlooring),
  m_setCats(&g_dbFlooring),  
  m_setSubCats(&g_dbFlooring) 
{
	m_setTotalMaterial.Open() ;
	m_setCats.Open() ;
	m_setSubCats.Open() ;
	m_iLastCatId = -1 ;
	m_iLastSubCatId = -1 ;
	m_DayIndex = 0;
}

CReportTotals::~CReportTotals()
{
	m_setTotalMaterial.Close() ;
	m_setCats.Close();
	m_setSubCats.Close();

	for (int iIndex =0; iIndex < 8; iIndex++)
	{
		delete [] m_adAmounts[iIndex] ;
		delete [] m_adSuperAmounts[iIndex] ;
	}
	delete [] m_adAmounts ;
	delete [] m_adSuperAmounts ;
}


BEGIN_MESSAGE_MAP(CReportTotals, CCFScrollView)
	//{{AFX_MSG_MAP(CReportTotals)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportTotals drawing

void CReportTotals::OnInitialUpdate()
{
	m_strTitle = "Weekly Totals Report";
	CCFScrollView::OnInitialUpdate();
	
	// the date cannot be uninitialized for this report
	ASSERT(m_timeFilterTime != 0);
	m_timeStart = CTime(m_timeFilterTime.GetYear(), m_timeFilterTime.GetMonth(), m_timeFilterTime.GetDay(), 0, 0, 0) ;
	m_timeStart -= CTimeSpan(m_timeStart.GetDayOfWeek() - 1, 0, 0, 0) ;
	CTime m_timeWE = m_timeStart + CTimeSpan(7, 0, 0, 0) ;
	
//		m_setTotalOptions.m_strFilter.Format("CONVERT(nvarchar, ScheduleDate, 101) >= '%s' AND CONVERT(nvarchar, ScheduleDate, 101) < '%s'", timeStart.Format("%m/%d/%Y"), timeWE.Format("%m/%d/%Y")) ;
	m_setTotalMaterial.m_strFilter.Format("ScheduleDate >= '%s' AND ScheduleDate < '%s'", m_timeStart.Format("%m/%d/%Y"), m_timeWE.Format("%m/%d/%Y")) ;

	if (m_strDivMarketFilter.GetLength() > 0)
	{
		m_setTotalMaterial.m_strFilter += _T(" AND ") + m_strDivMarketFilter;
	}

	m_setTotalMaterial.m_strSort = "ScheduleDate, MaterialCatagoryID" ;
	m_strTitle.Format("Weekly Totals for %s", m_timeStart.Format("%m/%d/%Y")) ;
	GetParentFrame()->SetTitle(m_strTitle);

	InitializeData();
}

void CReportTotals::OnDraw(CDC* pDC)
{

	m_DayIndex = 0;
	CRect rect ;
	this->GetClientRect(&rect) ;

	CSize size ;
	size.cx = long(rect.Width() * .95) ;
	size.cy = PrintPageBody(pDC, rect) ; ;

	SetScrollSizes(MM_TEXT, size);
}

/////////////////////////////////////////////////////////////////////////////
// CReportTotals diagnostics

#ifdef _DEBUG
void CReportTotals::AssertValid() const
{
	CCFScrollView::AssertValid();
}

void CReportTotals::Dump(CDumpContext& dc) const
{
	CCFScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CReportTotals message handlers

void CReportTotals::PrintPageBody(CDC *pDC, CPrintInfo *pInfo)
{
	TRACE("PrintPageBody with pInfo\n");
	if (pInfo->m_nCurPage == 1)
	{
		m_DayIndex = 0;
	}
	PrintPageBody(pDC, pInfo->m_rectDraw) ;
}

int CReportTotals::PrintPageBody(CDC *pDC, CRect rect)
{
	TRACE("PrintPageBody with rect\n");
	long lSOColumWidth = long(rect.Width() * .15);
	long lStyleColumWidth = long(rect.Width() * .6);
	long lSizeColumWidth = long(rect.Width() * .15);

	ULONG uLinesPrinted = 0;
	int iY = rect.top ;

	CTime time = m_timeStart;
	TRACE("%s\n", time.Format("%A - %m/%d/%Y"));

	while (m_DayIndex < 8)
	{
		ASSERT(m_DayIndex != 8);
		if (m_abWorkThisDay[m_DayIndex])
		{
			// see how many lines are available for printing on the page
			UINT uLinesAvailable = m_iLinesPerPage - uLinesPrinted;
			// if the lines for this next day exceed the lines available,
			// break out of the loop so we can print on the next page.
			if ( (m_aiLinesPerDay[m_DayIndex] > uLinesAvailable) && pDC->IsPrinting() )
			{
				TRACE("Jumping out of PrintPageBody while loop\n");
				break;
			}
			
			CString strTotal ;
			// if the day is not equal to the last (Weekly Totals)
			// print a string with Day and date.
			if (m_DayIndex != 7)
			{
				TRACE("%s\n", time.Format("%A - %m/%d/%Y"));
				time = m_timeStart + CTimeSpan(m_DayIndex, 0,0,0);
				TRACE("%s\n", time.Format("%A - %m/%d/%Y"));
				strTotal.Format("%s" , time.Format("%A - %m/%d/%Y")) ;
			}
			else
			{
				strTotal.Format("Weekly Totals") ;
			}

			// draw a line followed by the text formatted above
			pDC->MoveTo(rect.left, iY) ;
			pDC->LineTo(rect.right, iY) ;
			iY += iEXTRA_SPACING ;
			DrawAlignedText(pDC, rect.left, &iY, lStyleColumWidth, strTotal) ;
			uLinesPrinted++;

			int iX = rect.left + lSOColumWidth ;

			// iterate through the category totals for the current day
			// we know we can print all of these based on the calcs above
			for (int iIndex = 1; iIndex <= m_iLastCatId; iIndex++)
			{
				if (m_adAmounts[m_DayIndex][iIndex] > 0)
				{
					m_setCats.m_strFilter.Format("[CatId] = '%d'", iIndex) ;
					m_setCats.Requery() ;
					iX = rect.left + lSOColumWidth ;
					
					if (m_setCats.IsFieldNull(&m_setCats.m_SubCatId))
					{
						DrawAlignedText(pDC, &iX, iY, lSOColumWidth, m_setCats.m_Description) ;
						strTotal.Format("%7.2f", m_adAmounts[m_DayIndex][iIndex]) ;
						DrawAlignedText(pDC, &iX, &iY, lSizeColumWidth, strTotal, DT_RIGHT | DT_SINGLELINE) ;
						uLinesPrinted++;
					}
				}
			}

			iX = rect.left  + lSOColumWidth;

			m_setSubCats.m_strSort = "SubCatId" ;
			m_setSubCats.Requery() ;

			m_setCats.m_strFilter = "SubCatId IS NOT NULL" ;
			m_setCats.m_strSort = "SubCatId" ;
			m_setCats.Requery() ;

			int iLastSub = 99999;

			while (!m_setCats.IsEOF())
			{
				if (iLastSub != m_setCats.m_SubCatId)
				{
					iX = rect.left  + lSOColumWidth;
					iLastSub = m_setCats.m_SubCatId ;
					if (m_adSuperAmounts[m_DayIndex][m_setCats.m_SubCatId] > 0)
					{
						m_setSubCats.m_strFilter.Format("SubCatId = '%d'", m_setCats.m_SubCatId) ;
						m_setSubCats.Requery() ;
						DrawAlignedText(pDC, &iX, iY, lSOColumWidth, m_setSubCats.m_Description) ;
						strTotal.Format("%7.2f", m_adSuperAmounts[m_DayIndex][m_setCats.m_SubCatId]) ;
						DrawAlignedText(pDC, &iX, &iY, lSizeColumWidth, strTotal, DT_RIGHT | DT_SINGLELINE) ;
						uLinesPrinted++;
					}
				}
				// print item 
				int iX = rect.left + int(rect.Width() * .3);
					
				if (m_adAmounts[m_DayIndex][m_setCats.m_CatId] > 0)
				{
					if (m_setCats.m_IsPadding)
					{
						DrawAlignedText(pDC, &iX, iY, lSOColumWidth + lSizeColumWidth, m_setCats.m_Description) ;
						strTotal.Format("%7.2f", m_adAmounts[m_DayIndex][m_setCats.m_CatId]) ;
						DrawAlignedText(pDC, &iX, iY, lSizeColumWidth, strTotal, DT_RIGHT | DT_SINGLELINE ) ;
						int iRolls = int((m_adAmounts[m_DayIndex][m_setCats.m_CatId] + m_setCats.m_YardsPerRoll - .5) / m_setCats.m_YardsPerRoll) ;
						strTotal.Format("%d Rolls ", iRolls) ;
						DrawAlignedText(pDC, &iX, &iY, lSizeColumWidth, strTotal, DT_RIGHT | DT_SINGLELINE) ;
						uLinesPrinted++;
					}
					else
					{
						DrawAlignedText(pDC, &iX, iY, lSOColumWidth + lSizeColumWidth, m_setCats.m_Description) ;
						strTotal.Format("%7.2f", m_adAmounts[m_DayIndex][m_setCats.m_CatId]) ;
						DrawAlignedText(pDC, &iX, &iY, lSizeColumWidth, strTotal, DT_RIGHT | DT_SINGLELINE) ;
						uLinesPrinted++;
					}
				}

				m_setCats.MoveNext() ;
			}
		}
		m_DayIndex++;
		TRACE("m_DayIndex incremented. - %d\n", m_DayIndex);
	}

	return iY ;

}

void CReportTotals::OnBeginPrinting(CDC* /* pDC */, CPrintInfo* /* pInfo */)
{
	
}

void CReportTotals::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: Add your specialized code here and/or call the base class

	CCFScrollView::OnEndPrinting(pDC, pInfo);
}

void CReportTotals::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: Add your specialized code here and/or call the base class

	CCFScrollView::OnPrepareDC(pDC, pInfo);
}

BOOL CReportTotals::OnPreparePrinting(CPrintInfo* pInfo)
{
	CDC	dc ;
	CreateDefaultPrinterDC(&dc) ;
	SelectFont(100, "Arial", &dc, iEXTRA_SPACING);
	pInfo->SetMaxPage((m_nTotalLines + m_iLinesPerPage + 1) / m_iLinesPerPage) ;
	return CCFScrollView::OnPreparePrinting(pInfo);
}

void CReportTotals::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	CCFScrollView::OnPrint(pDC, pInfo);
}

// Initializes the data structures, totals the amounts
bool CReportTotals::InitializeData(void)
{
	bool bSuccess = true;

	while (!m_setCats.IsEOF())
	{
		if (m_setCats.m_CatId > m_iLastCatId)
		{
			m_iLastCatId = m_setCats.m_CatId ;
		}
		m_setCats.MoveNext() ;
	}

	while (!m_setSubCats.IsEOF())
	{
		if (m_setSubCats.m_SubCatId > m_iLastSubCatId)
		{
			m_iLastSubCatId = m_setSubCats.m_SubCatId ;
		}
		m_setSubCats.MoveNext() ;
	}

	m_setTotalMaterial.Requery() ;

	m_adAmounts = new double* [8] ;
	m_adSuperAmounts = new double* [8] ;

	for (int iIndex =0; iIndex < 8; iIndex++)
	{
		m_adAmounts[iIndex] = new double [m_iLastCatId + 1] ;
		ZeroMemory(m_adAmounts[iIndex], sizeof(double) * (m_iLastCatId + 1)) ;
		m_adSuperAmounts[iIndex] = new double [m_iLastSubCatId + 1] ;
		ZeroMemory(m_adSuperAmounts[iIndex], sizeof(double) * (m_iLastSubCatId + 1)) ;
		m_abWorkThisDay[iIndex] = false ;
		m_aiLinesPerDay[iIndex] = 0;
	}

	while (!m_setTotalMaterial.IsEOF() )
	{
		m_adAmounts[m_setTotalMaterial.m_ScheduleDate.GetDayOfWeek() -1][m_setTotalMaterial.m_MaterialCatagoryID] += m_setTotalMaterial.m_Quanity ;
		m_adAmounts[7][m_setTotalMaterial.m_MaterialCatagoryID] += m_setTotalMaterial.m_Quanity ;
		if (!m_setTotalMaterial.IsFieldNull(&m_setTotalMaterial.m_SubCatId))
		{
			m_adSuperAmounts[m_setTotalMaterial.m_ScheduleDate.GetDayOfWeek() -1][m_setTotalMaterial.m_SubCatId] += m_setTotalMaterial.m_Quanity ;
			m_adSuperAmounts[7][m_setTotalMaterial.m_SubCatId] += m_setTotalMaterial.m_Quanity ;
		}
		m_abWorkThisDay[m_setTotalMaterial.m_ScheduleDate.GetDayOfWeek() -1] = true ;
		m_abWorkThisDay[7] = true ;
		m_setTotalMaterial.MoveNext() ;
	}

	m_nTotalLines = 0;
	for (int iDayIndex = 0; iDayIndex < 8; iDayIndex++)
	{
		if (m_abWorkThisDay[iDayIndex])
		{
			m_nTotalLines++;
			m_aiLinesPerDay[iDayIndex]++;			
			for (int iCatsIndex = 0; iCatsIndex < m_iLastCatId+1; iCatsIndex++)
			{
				if (m_adAmounts[iDayIndex][iCatsIndex] > 0)
				{
					m_nTotalLines++;
					m_aiLinesPerDay[iDayIndex]++;
				}
			}

			for (int iCatsSubIndex = 0; iCatsSubIndex < m_iLastSubCatId+1; iCatsSubIndex++)
			{
				if (m_adSuperAmounts[iDayIndex][iCatsSubIndex] > 0)
				{
					m_nTotalLines++;
					m_aiLinesPerDay[iDayIndex]++;
				}
			}
		}
	}

	return bSuccess;
}

