/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// CellFormat.cpp: implementation of the CNumericFormat class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ugformat.h"
#include "NumericFormat.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNumericFormat::CNumericFormat()
{
}

CNumericFormat::~CNumericFormat()
{
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void CNumericFormat::ApplyDisplayFormat( CUGCell* cell )
{
	double dNum;
	CString sNumber;
	CString sFormat;

	dNum = cell->GetNumber();
		
	if( cell->IsPropertySet( UGCELL_NUMBERDEC_SET ) )
	{
		sFormat.Format( _T( "%%1.%dlf" ), cell->GetNumberDecimals() );
		sNumber.Format( sFormat, cell->GetNumber() );
	}
	else
	{
		sNumber.Format( _T( "%lf" ), cell->GetNumber() );
	}
	
	cell->SetText( sNumber );
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
int CNumericFormat::ValidateCellInfo( CUGCell* /* cell */ )
{
	
	//AfxMessageBox( cell->GetText() );
	return UG_SUCCESS;
}
