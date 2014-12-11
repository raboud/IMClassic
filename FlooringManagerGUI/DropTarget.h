
#pragma once
#include "afxcoll.h"

const UINT wm_FILES_DROPPED = RegisterWindowMessage("Files Dropped");

// DropTarget command target

class DropTarget : public COleDropTarget
{
	DECLARE_DYNAMIC(DropTarget)

public:
	DropTarget();
	virtual ~DropTarget();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual DROPEFFECT OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual void OnDragLeave(CWnd* pWnd);
	virtual DROPEFFECT OnDragOver(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual BOOL OnDrop(CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	virtual BOOL DoPasteDate(COleDataObject* pDataObject);
	virtual void UpdateControl();
	CStringArray m_fileNames;
	DROPEFFECT m_dropEffect;
	int m_nMaxCount;
	CString m_strFolder;
};


