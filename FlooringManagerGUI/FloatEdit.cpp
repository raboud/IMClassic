/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// FloatEdit.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "FloatEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFloatEdit

CFloatEdit::CFloatEdit()
{
	m_iNumOfDecimals = 2 ;
	m_bBlank = false ;
	m_bAllowNegative = true;
}

CFloatEdit::~CFloatEdit()
{
}


BEGIN_MESSAGE_MAP(CFloatEdit, CEdit)
	//{{AFX_MSG_MAP(CFloatEdit)
	ON_WM_CHAR()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFloatEdit message handlers

void CFloatEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	if (((nChar >= '0') && (nChar <= '9')) ||
		(nChar == VK_BACK) ||
		((nChar == '-') && (m_bAllowNegative)))
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
	else if ((nChar == '.') && (m_iNumOfDecimals))
	{
		CString strNumber ;
		this->GetWindowText(strNumber) ;
		if (strNumber.Find('.') == -1)
		{
			CEdit::OnChar(nChar, nRepCnt, nFlags);
		}
	}
	else if(nChar == VK_TAB || nChar == VK_RETURN || nChar == VK_ESCAPE)
	{
		return;
	}
}

void CFloatEdit::OnKillFocus(CWnd* pNewWnd) 
{
	UpdateField();
	CEdit::OnKillFocus(pNewWnd);
}

void CFloatEdit::AllowBlank(bool bBlank)
{
	m_bBlank = bBlank ;
}

void CFloatEdit::AllowNegative(bool bNegative)
{
	m_bAllowNegative = bNegative;
}

void CFloatEdit::UpdateField()
{
	if (!m_bBlank || (this->GetWindowTextLength() != 0))
	{
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
			strNumber = strNumber.Left(iDecimalPos + m_iNumOfDecimals + 1) ;
		}

		if ((iDecimalPos == -1) && (m_iNumOfDecimals > 0))
		{
			strNumber += "." ;
			iZerosToAdd = m_iNumOfDecimals ;
		}
		else if ((iDecimalPos != -1) && (iDecimalsInString < m_iNumOfDecimals))
		{
			iZerosToAdd = m_iNumOfDecimals - iDecimalsInString ;
		}
		while (iZerosToAdd)
		{
			strNumber += "0" ;
			iZerosToAdd-- ;
		}
		SetWindowText(strNumber) ;
	}
}
