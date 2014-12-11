// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "FRecordView.h"

#ifdef AFX_DB_SEG
#pragma code_seg(AFX_DB_SEG)
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CFRecordView, CRecordView)
	//{{AFX_MSG_MAP(CFRecordView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_RECORD_NEW, OnRecordNew)
	ON_COMMAND(IDOK, OnOK)
	ON_COMMAND(IDCANCEL, OnCancel)
	ON_UPDATE_COMMAND_UI(ID_RECORD_FIRST, OnUpdateRecordFirst)
	ON_UPDATE_COMMAND_UI(ID_RECORD_PREV, OnUpdateRecordPrev)
	ON_UPDATE_COMMAND_UI(ID_RECORD_NEXT, OnUpdateRecordNext)
	ON_UPDATE_COMMAND_UI(ID_RECORD_LAST, OnUpdateRecordLast)
	ON_UPDATE_COMMAND_UI(ID_RECORD_NEW, OnUpdateRecordNew)
END_MESSAGE_MAP()


CFRecordView::CFRecordView(LPCTSTR lpszTemplateName)
	: CRecordView(lpszTemplateName)
{
	m_bInserting = false ;
	m_bInsertable = false ;
	m_bEditing = false;
	m_bAdding = false;
	m_bIsAdmin = false;

}

CFRecordView::CFRecordView(UINT nIDTemplate)
	: CRecordView(nIDTemplate)
{
	m_bInserting = false ;
	m_bInsertable = false ;
	m_bEditing = false;
	m_bAdding = false;
	m_bIsAdmin = false;
}

CFRecordView::~CFRecordView()
{
}

void CFRecordView::OnInitialUpdate()
{
	CRecordView::OnInitialUpdate();
	ResizeParentToFit(false);
	if (m_bInsertable)
	{
		CButton* pOk = (CButton*) GetDlgItem(IDOK) ;
		CButton* pCancel = (CButton*) GetDlgItem(IDCANCEL) ;

		if ((pOk != NULL) && (pCancel != NULL))
		{
			pOk->ShowWindow(false) ;
			pCancel->ShowWindow(false) ;

			CRecordset* prs = OnGetRecordset();
			if (!prs->CanAppend())
			{
				m_bInsertable = false ;
			}
		}
		else
		{
			m_bInsertable = false ;
		}
	}
}

void CFRecordView::OnRecordNew() 
{
	CRecordset* prs = OnGetRecordset();

	if (prs->CanUpdate() && !prs->IsDeleted())
	{
		if (!prs->IsEOF() && !prs->IsBOF())
		{
			prs->Edit();
			if (!UpdateData())
			{
				return ;
			}
			prs->Update();
		}
		if (prs->CanAppend())
		{
			prs->AddNew() ;
			UpdateData(false) ;
			GetDlgItem(IDOK)->ShowWindow(true) ;
			GetDlgItem(IDCANCEL)->ShowWindow(true) ;
			m_bInserting = true ;
		}
	}
}

void CFRecordView::OnOK() 
{
	CRecordset* prs = OnGetRecordset();

	try
	{
		UpdateData(true) ;
		prs->Update() ;
		prs->Requery() ;
		UpdateData(false) ;
		//GetDlgItem(IDOK)->ShowWindow(false) ;
		//GetDlgItem(IDCANCEL)->ShowWindow(false) ;
		m_bInserting = false ;
	}
	catch( CDBException *e )
	{
		e->Delete();
	}

}

void CFRecordView::OnCancel() 
{
	CRecordset* prs = OnGetRecordset();
	prs->CancelUpdate() ;
	UpdateData(false) ;
	//GetDlgItem(IDOK)->ShowWindow(false) ;
	//GetDlgItem(IDCANCEL)->ShowWindow(false) ;
	m_bInserting = false ;
}

void CFRecordView::OnUpdateRecordFirst(CCmdUI* pCmdUI)
{
	if (m_bEditing || m_bAdding)
	{
		pCmdUI->Enable(false) ;
	}
	else
	{
		CRecordView::OnUpdateRecordFirst(pCmdUI) ;
	}
}

void CFRecordView::OnUpdateRecordPrev(CCmdUI* pCmdUI)
{
	if (m_bEditing || m_bAdding)
	{
		pCmdUI->Enable(false) ;
	}
	else
	{
		CRecordView::OnUpdateRecordPrev(pCmdUI) ;
	}
}

void CFRecordView::OnUpdateRecordNext(CCmdUI* pCmdUI)
{
	if (m_bEditing || m_bAdding)
	{
		pCmdUI->Enable(false) ;
	}
	else
	{
		CRecordView::OnUpdateRecordNext(pCmdUI) ;
	}
}

void CFRecordView::OnUpdateRecordLast(CCmdUI* pCmdUI)
{
	if (m_bEditing || m_bAdding)
	{
		pCmdUI->Enable(false) ;
	}
	else
	{
		CRecordView::OnUpdateRecordLast(pCmdUI) ;
	}
}

void CFRecordView::OnUpdateRecordNew(CCmdUI* pCmdUI)
{
/*	if (m_bIsAdmin)
	{
		pCmdUI->Enable(m_bInsertable && !m_bEditing && !m_bAdding) ;
	}
	else
*/	{
		pCmdUI->Enable(FALSE);
	}
}



/////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
void CFRecordView::AssertValid() const
{
	CRecordView::AssertValid();
}

void CFRecordView::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);

	dc << "m_bOnFirstRecord = " << m_bOnFirstRecord;
	dc << "\nm_bOnLastRecord = " << m_bOnLastRecord;

	dc << "\n";
}
#endif

#ifdef AFX_INIT_SEG
#pragma code_seg(AFX_INIT_SEG)
#endif

IMPLEMENT_DYNAMIC(CFRecordView, CRecordView)

/////////////////////////////////////////////////////////////////////////////

void CFRecordView::CloseView()
{
	CRecordset* pSet = OnGetRecordset() ;
	if (pSet->CanUpdate() && !pSet->IsDeleted())
	{
		pSet->Edit();
		if (!UpdateData())
		{
			pSet->CancelUpdate();
			return ;
		}
		pSet->Update();
	}
}

void CFRecordView::ShowControl(UINT uId, int nCmdShow)
{
	this->GetDlgItem(uId)->ShowWindow(nCmdShow) ;
}

void CFRecordView::EnableControl(UINT uId, bool bState)
{
	this->GetDlgItem(uId)->EnableWindow(bState) ;
}



