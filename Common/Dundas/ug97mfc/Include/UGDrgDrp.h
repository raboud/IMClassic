/***********************************************
	Ultimate Grid 97
	Copyright 1994 - 1997 Dundas Software Ltd.

	Class 
		CUGDropTarget
	Purpose
		This class handles the grid's drag and
		drop client operations.
	Details
		 An instance of this class is created 
		 inside of the main	grid class. This class 
		 then sends notifications to the main grid 
		 class then performs the appropriate actions 
		 based on the return value of the notification.
************************************************/
#if !defined(AFX_UGDRAGDROP_H__337078A6_C453_4F31_A84C_7CA629BADC18__INCLUDED_)
#define AFX_UGDRAGDROP_H__337078A6_C453_4F31_A84C_7CA629BADC18__INCLUDED_

#ifdef UG_ENABLE_DRAGDROP


class CUGDropTarget: public COleDropTarget{


public:

	CUGDropTarget();
	~CUGDropTarget();

	CUGCtrl		*	m_ctrl;			//pointer to the main class

	virtual DROPEFFECT OnDragEnter( CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point );
	virtual DROPEFFECT OnDragOver( CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point );
	virtual DROPEFFECT OnDropEx( CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropDefault, DROPEFFECT dropList, CPoint point );
};

#endif   


#endif // AFX_UGDRAGDROP_H__337078A6_C453_4F31_A84C_7CA629BADC18__INCLUDED_
// the next line must be put in so the MSVC++1.5x will not give an 
// unexpected end of file found error, MSVC++1.5x compiler does not
// compile properly if an #endif is the last line
#define UGDRGDRPH
