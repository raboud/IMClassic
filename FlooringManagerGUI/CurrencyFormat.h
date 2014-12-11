/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// CellFormat.h: interface for the CCurrencyFormat class.
//
//////////////////////////////////////////////////////////////////////
#include "ugctrl.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CCurrencyFormat : public CUGCellFormat
{
public:
	CCurrencyFormat();
	virtual ~CCurrencyFormat();

	void ApplyDisplayFormat( CUGCell* cell );
	int ValidateCellInfo( CUGCell* cell );
};

								
