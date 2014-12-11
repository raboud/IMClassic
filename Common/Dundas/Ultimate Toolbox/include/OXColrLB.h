// =============================================================================
// 							Class Specification : COXColorsListBox
// =============================================================================
//
// Header file : 		OXColrLB.h

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved

// /////////////////////////////////////////////////////////////////////////////
//
// Properties:
//
//	NO	Abstract class (does not have any objects)
//	YES	Derived from CListBox
//	YES	Is a Cwnd.
//	YES	Two stage creation (constructor & Create())
//	YES	Has a message map
//	NO  Needs a resource (template)
//	NO	Persistent objects (saveable on disk)
//	NO	Uses exceptions
//
////////////////////////////////////////////////////////////////////////////////
//
// Desciption :
//		This class provides a simple to use listbox of colors that the
//		user may edit via the color editing common dialog box. Also it 
//		allows to edit text descriptions in Windows Explorer manner.
//
// Remark:
//		This listbox class uses the item data to maintain the color
//		information for each item in the list at present.  Do *not*
//		take advantage of this; use the supplied member functions to
//		set and get the color information.  Future versions of the class
//		may maintain it separately to allow item data usage
//
//		messages number WM_OX_SETLISTBOXITEM_COLOR (WM_OX_APP + 140) and
//		WM_OX_SETLISTBOXITEM_TEXT (WM_OX_APP + 141) are in use.

//
// Prerequisites (necessary conditions):
//		The implementation relies upon the HID_BASE_RESOURCE id in the
//		AFXPRIV.H file to work around a problem with the MFC context
//		sensitive help system.  Make sure this file is included in the
//		pre-compiled header.
//
// Limited edition:
//
/////////////////////////////////////////////////////////////////////////////

#if !defined( _COLORSLISTBOX_H_ )
#define _COLORSLISTBOX_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"

// You can redefine WM_OX_APP by defining it before including this file
#ifndef WM_OX_APP            

	#ifndef WM_APP
		#define WM_APP                          0x8000
	#endif

	#define WM_OX_APP WM_APP + 100
#endif

// Send those notification messages to parent.
// If return value is -1 then discard changes.
#define WM_OX_SETLISTBOXITEM_COLOR (WM_OX_APP + 140) //WPARAM : int index, LPARAM : COLRREF new_color
#define WM_OX_SETLISTBOXITEM_TEXT (WM_OX_APP + 141) //WPARAM : int index, LPARAM : CString* new_text

// How far user can move mouse with left button down
// while it be considered as click but not drag.
#define OX_CLB_EDIT_RADIUS 1.5


class OX_CLASS_DECL COXColorsListBox : public CListBox
{
// Data members -------------------------------------------------------------
public:

protected:
	CEdit * m_pCurEditBox ;
	CPoint m_ptClicked ;
	int m_iEditedItem ;
	BOOL	m_bEditable;
	BOOL	m_bAutoEdit;
	
private:

// Member functions ---------------------------------------------------------
public:
	COXColorsListBox();
	// --- In  : 
	// --- Out : 
	// --- Returns :
	// --- Effect : Contructor of object
	//				It will initialize the internal state

	BOOL ReplaceListbox(CListBox* pWnd);
	// --- In  : the listbox to be replaced by this colorlistbox
	// --- Out : 
	// --- Returns : succeeded or not
	// --- Effect : Use this method to replace an existing dialog box listbox,
	//				fixing up the tab order and such as needed.

	int AddItemColor(LPCTSTR pcszName, COLORREF crColor);
	// --- In  : pcszName : the name of the item to be added
	//			 crColor : the color to be added
	// --- Out : 
	// --- Returns : the index of the added item otherwise LB_ERR if error occurs
	// --- Effect : Adds a color to the list.

	BOOL GetItemColor(int iIndex, COLORREF& cr);
	// --- In  : iIndex : the index of the item what properties are to be retrieved
	// --- Out : str : name of the item with index iIdex
	//			 cr : color of the item with index iIdex
	// --- Returns : succeeded or not
	// --- Effect : Gets the color information for a given item.

	BOOL SetItemColor(int iIndex, COLORREF cr, BOOL bUpdate = TRUE);
	// --- In  : iIndex : the index of the item what properties are to be set
	//			 cr : the color to be set
	//			 bUpdate : redraw or not
	// --- Out : 
	// --- Returns : succeeded or not
	// --- Effect : Sets the color information for a given item.

	virtual COLORREF EditSelectedColor(BOOL bSetColor = TRUE);
	// --- In  : bSetColor : whether the new selected color, must be assigned
	//						 immediately to the currently selected item.
	// --- Out : 
	// --- Returns : the newly selected color, 0x01000000 if error occurred(this is
	//				 an illegal COLORREF value : high order byte must be zero)
	// --- Effect : Forces display of the color editing common dialog box
	//				to allow the user to change the currently selected color.

	virtual void SetEditable(BOOL bEdit = TRUE);
	// --- In  : bEdit : Allow edit or not
	// --- Out : 
	// --- Returns : 
	// --- Effect : Whether to allow a item text to be edited or not
	//				By default editing is not allowed

	BOOL GetEditable() const;
	// --- In  : 
	// --- Out : 
	// --- Returns : Whether a item text is allowed to be edited or not
	// --- Effect : 

	virtual void SetAutoEdit(BOOL bAutoEdit = TRUE);
	// --- In  : bAutoEdit : Whether the item will be edited 
	//                       when a valid character is typed
	// --- Out : 
	// --- Returns : Whether it succeeded or not
	// --- Effect : Sets this control in auto edit mode.  
	//				Normally valid characters (e.g. A, B, 1, etc) are used to
	//				jump to the item that starts with that character.
	//				This setting can change that behaviouir into editing the item
	//				By default editing is not allowed

	BOOL GetAutoEdit() const;
	// --- In  : 
	// --- Out : 
	// --- Returns : Whether the control is in auto edit mode
	//               (whether focussed item will be edited when a valid character is typed)
	// --- Effect : 

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COXColorsListBox)
	public:
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

	virtual LRESULT OnSettingItemColor(int iIndex, COLORREF cr);
	virtual void EditSelectedText();
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : Create edit box in size and place of m_iEditedItem.
	//				If user approves changes by "Enter" sends WM_OX_SETLISTBOXITEM_TEXT
	//				to parent and replace the text.
	virtual void CalcItemRectangles( CDC * pDC, const CRect& rcItemFull, CRect& rcColor, CRect& rcText );
	// --- In  : pDC : Control DC to use current selected device context properties.
	//		     rcItemFull : what rectangle to devide into color and text part. 
	// --- Out : rcColor : color part
	//			 rcText : text part
	// --- Returns : 
	// --- Effect : Devide item rectangle int color and text parts.
	virtual void ResetEditing();
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : Clean up after editing.
	virtual BOOL IsMoveToFar( UINT nFlags, const CPoint& point ) const ;
	// --- In  : nFlags: See OnMouseMove
	//			 point : current mouse position
	// --- Out : 
	// --- Returns : if this point is to far away from m_ptClicked
	// --- Effect : Check distance between m_ptClicked and point more then OX_CL_EDIT_RADIUS
#ifdef _DEBUG
	virtual void Dump(CDumpContext&) const;
	virtual void AssertValid() const;
#endif //_DEBUG

	virtual ~COXColorsListBox();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of object

protected:
	void FastRect(CDC* pDC, CRect* pRect, COLORREF cr);
	
	// Generated message map functions
	//{{AFX_MSG(COXColorsListBox)
		afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
		afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
		afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
		afx_msg void OnMouseMove( UINT nFlags, CPoint point );
		afx_msg LRESULT OnEditCancel( WPARAM wp=0, LPARAM lp=0);
		afx_msg LRESULT OnEditOk( WPARAM, LPARAM );
		afx_msg void OnTimer( UINT nIDEvent );
		afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif	// _COLORSLISTBOX_H_
// ==========================================================================
