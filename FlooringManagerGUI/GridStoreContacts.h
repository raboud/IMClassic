#pragma once

#include "cfgrid.h"
#include "SetDepartments.h"
#include "SetContactTitles.h"
#include "OXMaskedEdit.h"

class CGridStoreContacts : public CCFGrid
{
public:
	CGridStoreContacts(void);
	~CGridStoreContacts(void);

	int AppendRow(int iDeptID = -1);
	virtual int DeleteRow(long lRow);
	virtual int OnEditStart(int col, long row,CWnd **edit);
	virtual int OnEditFinish(int col, long row, CWnd *edit, LPCTSTR string, BOOL cancelFlag) ;
	virtual void OnMenuCommand(int col,long row,int section,int item);
	virtual int OnMenuStart(int col,long row,int section);
	virtual int OnCellTypeNotify(long ID,int col,long row,long msg,long param);
	virtual void OnCellChange(int oldcol, int newcol, long oldrow, long newrow);
	virtual void OnDClicked(int col,long row, RECT *rect, POINT *point, BOOL processed);
	virtual void OnTH_LClicked(int col, long row, int updn,RECT * rect, POINT * point, BOOL processed);
	virtual void OnDrawFocusRect(CDC *dc,RECT *rect);
	
	virtual void OnSetup();
//	virtual void OnSH_DClicked(int col,long row, RECT *rect, POINT *point, BOOL processed) ;
	
	void Update() ;
	void UpdateRecordSet();
	void SetStoreID(int iStoreID, bool bUpdate = true);

protected:
	// menu items
	enum {DELETE_CONTACT = 2000, NEW_CONTACT} ;
	afx_msg void OnKillFocus(CWnd* pOldWnd);

	// columns
	enum {DEPARTMENTSSTORESASSIGNMENTID = -1, STORECONTACTID, DEPARTMENT, TITLE, FIRST_NAME, LAST_NAME, CONTACT_INFO, CONTACT_INFO_1, OPTIONS, OPTIONS_1, LAST} ;
	enum {NO_FAX = 0, FAX, ALT_FAX, TRY_BOTH, FAX_LAST};
	char* m_aszFAX_STRINGS[FAX_LAST];

	enum {contact_rowoffset_EMAIL = 0, contact_rowoffset_PHONE, contact_rowoffset_ALTPHONE, contact_rowoffset_FAX1, contact_rowoffset_FAX2, contact_rowoffset_LAST};
	enum {options_rowoffset_FAX_STATUS = 0, options_rowoffset_EMAIL_STATUS, options_rowoffset_LAST};

	void DeleteContact(long row);
	void AddNewContact();
	long InsertRow(int iDeptID);
	void InitRow(long row, int iDeptID);
	bool ValidateFaxNumber(int col, long row);
	bool ValidateFaxNumber(CString& strFaxNumber);
	bool ValidateEmailAddress(CString& strEmailAddress);
	int GetFaxToID(CString strFaxToID);
	CString GetFaxToString(long iID);
	void UpdateFaxToDropDown(bool bFaxValid, bool bAltFaxValid, long row);

	virtual bool IsRowDirty(long lRow);
	virtual bool IsColumnDirty(int iCol, long lRow);
	
	void UpdateGrid();

	int m_iStoreID;

	CSetDepartments m_setDepartments;
	CSetContactTitles m_setContactTitles;
	
	COXMaskedEdit m_editPhone;
	COXMaskedEdit m_editFax;

	int m_iNumRowsPerEntry;

};

inline void CGridStoreContacts::SetStoreID(int iStoreID, bool bUpdate /*= true*/)
{
	m_iStoreID = iStoreID;
	if (bUpdate)
	{
		UpdateGrid();
	}
}