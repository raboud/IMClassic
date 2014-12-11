// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#ifndef __FRECORDVIEW_H__
#define __FRECORDVIEW_H__

#ifndef __AFXDB_H__
#include <AFXDB.h>
#endif

#include "cfres.h"
/////////////////////////////////////////////////////////////////////////////

#ifdef _AFX_PACKING
#pragma pack(push, _AFX_PACKING)
#endif


#ifdef _AFXDLL
class CFRecordView : public CRecordView
#else
class AFX_NOVTABLE CFRecordView : public CRecordView
#endif
{
	DECLARE_DYNAMIC(CFRecordView)

// Construction
protected:  // must derive your own class
	CFRecordView(LPCTSTR lpszTemplateName);
	CFRecordView(UINT nIDTemplate);

	virtual void OnInitialUpdate(); // called first time after construct

// Attributes
public:

// Operations
public:

// Implementation
public:
	virtual void CloseView();
	virtual ~CFRecordView();
	void EnableNavControls(CToolBarCtrl* pToolBar, bool bEnable);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	bool m_bInsertable;
	bool m_bInserting;
	bool m_bEditing;
	bool m_bAdding;
	bool m_bIsAdmin;
	void EnableControl (UINT uId, bool bState);
	void ShowControl(UINT uId, int nCmdShow);

	virtual void EnableControls( bool bEnable );

	//{{AFX_MSG(CFRecordView)
	afx_msg void OnUpdateRecordFirst(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRecordPrev(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRecordNext(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRecordLast(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRecordNew(CCmdUI* pCmdUI);
	afx_msg void OnRecordNew();
	afx_msg void OnOK();
	afx_msg void OnCancel();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

inline void CFRecordView::EnableControls( bool /* bEnable */)
{
}

/////////////////////////////////////////////////////////////////////////////
// Inline function declarations

#ifdef _AFX_PACKING
#pragma pack(pop)
#endif

#endif //__FRECORDVIEW_H__

/////////////////////////////////////////////////////////////////////////////
