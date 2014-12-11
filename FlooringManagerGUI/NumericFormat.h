/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// CellFormat.h: interface for the CNumericFormat class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CELLFORMAT_H__649F71C2_A48A_11D1_8F66_0020359646CF__INCLUDED_)
#define AFX_CELLFORMAT_H__649F71C2_A48A_11D1_8F66_0020359646CF__INCLUDED_

#include "ugctrl.h"
#include "ugformat.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CNumericFormat : public CUGCellFormat
{
public:
	CNumericFormat();
	virtual ~CNumericFormat();

	void ApplyDisplayFormat( CUGCell* cell );
	int ValidateCellInfo( CUGCell* cell );
};



#endif // !defined(AFX_CELLFORMAT_H__649F71C2_A48A_11D1_8F66_0020359646CF__INCLUDED_)
