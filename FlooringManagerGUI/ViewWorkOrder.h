/*----------------------------------------------------------------------
	Copyright © 2001-2002 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_VIEWWORKORDER_H__285A6A39_F9BB_48C0_A1D7_2CCC23AAB72C__INCLUDED_)
#define AFX_VIEWWORKORDER_H__285A6A39_F9BB_48C0_A1D7_2CCC23AAB72C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewWorkOrder.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewWorkOrder view
#include "CFViewReport.h"
#include <afxtempl.h>

#include "SetMaterialOrderDetailed.h"
#include "SetOrderOptionsDetails.h"
#include "SeOrderCustomDetails.h"
#include "SetUintOfMeaser.h"
#include "SetMaterial.h"
#include "SetOptions.h"
#include "SetOrders.h"	// Added by ClassView
#include "SetCustomer.h"	// Added by ClassView

class CViewWorkOrder : public CCFViewReport
{
protected:
	CViewWorkOrder();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CViewWorkOrder)

// Attributes
public:

// Operations
public:
	bool SetPoList(CPoList* listPOs);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewWorkOrder)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CViewWorkOrder();

	// Generated message map functions
protected:
	void DrawStorePickup(CDC *pDC, CRect& rect);
	bool m_bStorePickup;
	bool m_bAM;
	bool m_bScheduled;
	CTime m_dateScheduled;
	void DrawMinApplied (CDC* pDC, CRect& rect);
	double m_fMaterialCost;
	CSetCustomer m_setCustomer;
	CSetOrders m_setOrders;
	void CalculatePadding(int& iRolls, int& iFeet, double fYards, int iYardPerRoll);
	double m_fTotal;
	void InitializeFilters(void);
	void DrawComments(CDC *pDC, CRect& rect);
	void DrawCustom(CDC *pDC, CRect& rect);
	void DrawOptions(CDC *pDC, CRect& rect, bool bApplyToMinimumWOOnly);
	void DrawBasic(CDC *pDC, CRect& rect);
	void DrawCustomerData(CDC *pDC, CRect& rect, long lCustomerId);
	void DrawPadding(CDC* pDC, CRect& rect);
	void DrawTotal(CDC *pDC, CRect& rect);
	void DrawMaterials (CDC *pDC, CRect& rect);
	void DrawDirections(CDC *pDC, CRect& rect);
	void DrawExtras(CDC *pDC, CRect &rect);
	void DrawInstallerComments(CDC *pDC, CRect &rect);
	CPoList m_PoList;

	CSetMaterialOrderDetailed m_setMaterialDetails ;
	CSetOrderOptionsDetails m_setOptionDetails ;
	CSetOrderCustomDetails m_setCustomDetails ;

	CSetUnitOfMeasure m_setUOM ;

	CSetOptions m_setOptions ;

	//{{AFX_MSG(CViewWorkOrder)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWWORKORDER_H__285A6A39_F9BB_48C0_A1D7_2CCC23AAB72C__INCLUDED_)
