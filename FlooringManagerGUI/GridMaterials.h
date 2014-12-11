/*----------------------------------------------------------------------
	Copyright © 2001-2002 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// GridMaterials.h: interface for the CGridMaterials class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDMATERIALS_H__FF7102CC_96EB_4060_BF06_4DFB31ECDC63__INCLUDED_)
#define AFX_GRIDMATERIALS_H__FF7102CC_96EB_4060_BF06_4DFB31ECDC63__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GridPOBase.h"

#include "CurrencyFormat.h"	// Added by ClassView
#include "NumericFormat.h"	// Added by ClassView
#include "NumericEdit.h"	// Added by ClassView
#include "SetBasicLabor.h"
#include "SetUintOfMeaser.h"	// Added by ClassView

const UINT    wm_MATERIAL_UPDATE = RegisterWindowMessage( "Material Update" ) ;

class CGridMaterials : public CGridPOBase  
{
public:
	virtual int AppendRow();
	void SetOrderID (long lOrderID);
	void UpdateRecordSet(long lOrderID);
	virtual int DeleteRow(long lRow);
	double CalculatePrice (void);
	virtual BOOL OnCanMove(int oldcol, long oldrow, int newcol, long newrow);
	virtual int OnEditStart(int col, long row,CWnd **edit);

	virtual int OnCellTypeNotify(long ID,int col,long row,long msg,long param);
	void SetMaterialType (long lMaterialType, bool bShowActiveOnly = false);
	virtual void OnSetup();
	CGridMaterials();
	virtual ~CGridMaterials();

protected:
	enum {ID = -1, TYPE, LEN_FEET, LEN_INCHES, WIDTH_FEET, WIDTH_INCHES, MAT_SIZE, STYLE, COLOR, SO, STATUS, RETAIL, EXTENTION, PRICE, COST, LAST} ;
	//{{AFX_MSG(CGridMaterials)
	afx_msg void OnKillFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void SelectMaterial (long lId);
	void UpdateGrid ();
	long m_lOrderID;
	long m_lMaterialType;
	CUGEdit m_editUpper;
	CNumericEdit m_editNumeric;
	bool m_bHas2Dim ;
	bool m_bHasSo ;
	bool m_bHasStyle ;
	bool m_bHasColor ;
	CNumericFormat m_formatNumeric;
	CCurrencyFormat m_formatCurrency;
	void GetMaterialType (CString strOption);
	void GetMaterialType (long lRow);
	CSetBasicLabor m_setBasicLabor;
	double CalculateRowRetail(long lRow);
	double CalculateRowPrice(long lRow);
};

#endif // !defined(AFX_GRIDMATERIALS_H__FF7102CC_96EB_4060_BF06_4DFB31ECDC63__INCLUDED_)
