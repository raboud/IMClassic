/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// CellFormat.cpp: implementation of the CCurrencyFormat class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CurrencyFormat.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCurrencyFormat::CCurrencyFormat()
{
}

CCurrencyFormat::~CCurrencyFormat()
{
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void CCurrencyFormat::ApplyDisplayFormat( CUGCell* cell )
{
	double dNum;
	CString sNumber;
	CString sFormat;

	dNum = cell->GetNumber();
		
	sNumber.Format( _T( "$%.2lf" ), cell->GetNumber() );
		
	cell->SetText( sNumber );
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
int CCurrencyFormat::ValidateCellInfo( CUGCell* /* cell */ )
{
	return UG_SUCCESS;
}
