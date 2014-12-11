
#include "stdafx.h"

#include "DataExchange.h"

void AFXAPI DDX_ListBoxMultiSelect(CDataExchange* pDX, int nIDC, long& lValue)
{
	HWND hWndCtrl = pDX->PrepareCtrl(nIDC);
	if (pDX->m_bSaveAndValidate)
	{
		lValue = 0;
		int iNumSelItems = (int)::SendMessage(hWndCtrl, LB_GETSELCOUNT, 0, 0L);
		if (iNumSelItems > 0)
		{
			
			int* aiSelIndexes = new int[iNumSelItems];
            long lResult = ::SendMessage(hWndCtrl, LB_GETSELITEMS, (WPARAM)iNumSelItems, (LPARAM)aiSelIndexes) ;
			if (lResult > 0)
			{
				long lData = 0;
				for (int iIndex = 0; iIndex < iNumSelItems; iIndex++)
				{
					lData = ::SendMessage(hWndCtrl, LB_GETITEMDATA, aiSelIndexes[iIndex], 0) ;
					lValue = lValue | lData ;
				}
			}
			delete [] aiSelIndexes;
		}
	}
	else
	{
		int iCount = ::SendMessage(hWndCtrl, LB_GETCOUNT, 0, 0) ;
		for (int iIndex = 0; iIndex < iCount; iIndex++)
		{
			long lData = ::SendMessage(hWndCtrl, LB_GETITEMDATA, iIndex,0);
			if ((lValue & lData) == lData)
			{
				::SendMessage(hWndCtrl, LB_SETSEL, (WPARAM)TRUE, (LPARAM)iIndex);
			}
		}
	}
}

void AFXAPI DDX_ComboBoxData(CDataExchange* pDX, int nIDC, long& lStore)
{
	int iIndex ;
	HWND hWndCtrl = pDX->PrepareCtrl(nIDC);
	if (pDX->m_bSaveAndValidate)
	{
		iIndex = (int)::SendMessage(hWndCtrl, CB_GETCURSEL, 0, 0L);
		if (iIndex != -1)
		{
			lStore = ::SendMessage(hWndCtrl, CB_GETITEMDATA, iIndex,0) ;
		}
	}
	else
	{
		int iCount = ::SendMessage(hWndCtrl, CB_GETCOUNT, 0, 0) ;
		bool bNotFound = true ;
		for (iIndex =0; iIndex < iCount; iIndex++)
		{
			if (lStore == ::SendMessage(hWndCtrl, CB_GETITEMDATA, iIndex,0))
			{
				::SendMessage(hWndCtrl, CB_SETCURSEL, (WPARAM)iIndex, 0L);
				bNotFound = false ;
				break ;
			}
		}
		if (bNotFound)
		{
			::SendMessage(hWndCtrl, CB_SETCURSEL, (WPARAM) -1, 0L);
		}
	}
}

/*
/////////////////////////////////////////////////////////////////////////////
// Validation procs

AFX_STATIC void AFXAPI _AfxFailMinMaxReal(CDataExchange* pDX,
	 double minVal, double maxVal, int precision, UINT nIDPrompt)
	// error string must have '%1' and '%2' in it
{
	if (!pDX->m_bSaveAndValidate)
	{
		TRACE0("Warning: initial dialog data is out of range.\n");
		return;         // don't stop now
	}
	TCHAR szMin[32], szMax[32];
	CString prompt;

	_stprintf(szMin, _T("%.*g"), precision, minVal);
	_stprintf(szMax, _T("%.*g"), precision, maxVal);
	AfxFormatString2(prompt, nIDPrompt, szMin, szMax);

	AfxMessageBox(prompt, MB_ICONEXCLAMATION, nIDPrompt);
	prompt.Empty(); // exception prep
	pDX->Fail();
}
*/
void AFXAPI DDV_TELEPHONE(CDataExchange* pDX, CString& value, CRecordset* pSet, bool /* bMustBeFull */)
{
	if (!pDX->m_bSaveAndValidate)
	{
		int iLength = value.GetLength() ;
		if ((iLength >0) && (iLength < 10))
		{
			TRACE0("Warning: Phone number to short.\n");
		}
		else if ((iLength >0) && (iLength > 9))
		{
			if (value.Left(1).Compare("("))
			{
				value.Insert(0, "(") ;
				pSet->SetFieldDirty(&value, true) ;
			}
			if (value.Mid(4,2).Compare(") "))
			{
				value.Insert(4, ") ") ;
				pSet->SetFieldDirty(&value, true) ;
			}
			if (value.Mid(9,1).Compare("-"))
			{
				value.Insert(9, "-") ;
				pSet->SetFieldDirty(&value, true) ;
			}
		}
		return;         // don't stop now
	}
}


void AFXAPI DDX_MultiListBoxData(CDataExchange* pDX, int nIDC, long& lStore)
{
	int iIndex ;
	HWND hWndCtrl = pDX->PrepareCtrl(nIDC);
	if (pDX->m_bSaveAndValidate)
	{
		lStore = 0 ;
		int iCount = (int)::SendMessage(hWndCtrl, LB_GETSELCOUNT , 0, 0L);
		int *aiSelected = new int[iCount] ;
		SendMessage(hWndCtrl, LB_GETSELITEMS, iCount, (LPARAM) aiSelected) ;

		for (iIndex = 0; iIndex < iCount; iIndex++)
		{
			lStore |= ::SendMessage(hWndCtrl, LB_GETITEMDATA, aiSelected[iIndex],0) ;
		}
		delete [] aiSelected ;
	}
	else
	{
		int iCount = ::SendMessage(hWndCtrl, LB_GETCOUNT, 0, 0) ;
		for (iIndex =0; iIndex < iCount; iIndex++)
		{
			bool bSelected = (lStore & ::SendMessage(hWndCtrl, LB_GETITEMDATA, iIndex,0)) != 0 ;
			::SendMessage(hWndCtrl, LB_SETSEL, bSelected, (LPARAM)iIndex);
		}
	}

}
