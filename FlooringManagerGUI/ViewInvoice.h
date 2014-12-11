/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_VIEWINVOICE_H__285A6A39_F9BB_48C0_A1D7_2CCC23AAB72C__INCLUDED_)
#define AFX_VIEWINVOICE_H__285A6A39_F9BB_48C0_A1D7_2CCC23AAB72C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewInvoice.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewInvoice view
#include "CFViewReport.h"
//#include <afxtempl.h>

#include "SetVwOrderBasicLaborDetails.h"
#include "SetOrderOptionsDetails.h"
#include "SeOrderCustomDetails.h"
#include "SetUintOfMeaser.h"
#include "SetMaterial.h"
#include "SetOptions.h"
#include "SetOrderAndCustomer.h"
#include "SetCompanyInfo.h"

//#include "SetOrders.h"	// Added by ClassView

class CViewInvoice : public CCFViewReport
{
protected:
	CViewInvoice();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CViewInvoice)

// Attributes
public:

// Operations
public:
	void SetPo(long lPO);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewInvoice)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CViewInvoice();

	// Generated message map functions
protected:
	void DrawHeadings2(CDC *pDC, CRect &rect, CString strTitle);
	void DrawHeadings(CDC *pDC, CRect& rect, CString strTitle);
	void DrawLogo(CDC* pDC);
	void DrawTripCharge(CDC* pDC, CRect& rect);
	CSetOrderAndCustomer m_setOrders ;
//	CSetOrders m_setOrders;
	bool m_bNoMin;
	long m_lMaterialTypeID;
	long m_lPO;
	void DrawTotal(CDC *pDC, CRect& rect);
//	double m_fTotal;

	double m_fTripCharg[2] ;
	double m_fOptions[2] ;
	double m_fBasic[2] ;
	double m_fCustom[2] ;

	void InitializeFilters(void);
	void DrawComments(CDC *pDC, CRect& rect);
	void DrawCustom(CDC *pDC, CRect& rect);
	void DrawOptions(CDC *pDC, CRect& rect);
	void DrawBasic(CDC *pDC, CRect& rect);
	void DrawCustomerData(CDC *pDC, CRect rect, long lCustomerId);

	CSetVwOrderBasicLaborDetails m_setMaterialDetails ;
	CSetOrderOptionsDetails m_setOptionDetails ;
	CSetOrderCustomDetails m_setCustomDetails ;
	CSetCompanyInfo m_setCompanyInfo;

	CSetUnitOfMeasure m_setUOM ;

	CSetOptions m_setOptions ;

	//{{AFX_MSG(CViewInvoice)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWINVOICE_H__285A6A39_F9BB_48C0_A1D7_2CCC23AAB72C__INCLUDED_)
