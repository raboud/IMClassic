/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// UGEdit.cpp : implementation file
//

#include "stdafx.h"
#include <ctype.h>

#include "UGCtrl.h"
#include "NumericEdit.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////
CNumericEdit::CNumericEdit()
{
}

///////////////////////////////////////////////////////////////////
CNumericEdit::~CNumericEdit()
{
}


///////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CNumericEdit, CUGEdit)
	//{{AFX_MSG_MAP(CNumericEdit)
	ON_WM_CHAR()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////
void CNumericEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	int iNumberOfDecimals = m_ctrl->m_editCell.GetNumberDecimals() ;
	
	if (((nChar >= '0') && (nChar <= '9')) ||
		(nChar == VK_BACK) ||
		(nChar == '-'))
	{
		CUGEdit::OnChar(nChar, nRepCnt, nFlags);
	}
	else if ((nChar == '.') && (iNumberOfDecimals))
	{
		CString strNumber ;
		this->GetWindowText(strNumber) ;
		if (strNumber.Find('.') == -1)
		{
			CUGEdit::OnChar(nChar, nRepCnt, nFlags);
		}
	}
	else if(nChar == VK_TAB || nChar == VK_RETURN || nChar == VK_ESCAPE)
	{
		return;
	}
}

void CNumericEdit::OnKillFocus(CWnd *pNewWnd)
{
	int iNumberOfDecimals = m_ctrl->m_editCell.GetNumberDecimals() ;
	
	CString strNumber ;
	this->GetWindowText(strNumber) ;
	strNumber.Replace("$", "") ;
	int iDecimalPos = strNumber.Find('.') ;
	int iStringLen = strNumber.GetLength() ;
	int iDecimalsInString = iStringLen - iDecimalPos - 1 ;
	int iZerosToAdd = 0 ;
	CString strPad = "";
	if (iDecimalPos != -1)
	{
		strNumber = strNumber.Left(iDecimalPos + iNumberOfDecimals + 1) ;
	}

	if ((iDecimalPos == -1) && (iNumberOfDecimals > 0))
	{
		strNumber += "." ;
		iZerosToAdd = iNumberOfDecimals ;
	}
	else if ((iDecimalPos != -1) && (iDecimalsInString < iNumberOfDecimals))
	{
		iZerosToAdd = iNumberOfDecimals - iDecimalsInString ;
	}
	while (iZerosToAdd)
	{
		strNumber += "0" ;
		iZerosToAdd-- ;
	}
	SetWindowText(strNumber) ;
	CUGEdit::OnKillFocus(pNewWnd) ;
}
