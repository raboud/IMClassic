#pragma once

#include "cfgrid.h"

class CGridSubContractorsList : public CCFGrid
{
public:
	CGridSubContractorsList(void);
	~CGridSubContractorsList(void);

	virtual void OnMenuCommand(int col,long row,int section,int item);
	virtual int OnMenuStart(int col,long row,int section);
	virtual void OnSetup();
	virtual void OnSH_DClicked(int col,long row, RECT *rect, POINT *point, BOOL processed) ;
	virtual void OnDClicked(int col,long row, RECT *rect, POINT *point, BOOL processed) ;
	void Update() ;

	void ShowActiveOnly( bool bShowActiveOnly );
	void SetShowFilter( int iFilter );

protected:
	// menu items
	enum {EDIT_SUB = 2000, NEW_SUB, DELETE_SUB} ;

	// columns
	enum {ID = -1, LAST_NAME, FIRST_NAME, ADDRESS, CITY, STATE, ZIP, HOME_PHONE, CELL_PHONE, RETAINAGE_RATE, LAST} ;

	void EditSubContractor(long row) ;
	void NewSubContractor() ;
	void DeleteSubContractor(long row);
	CString GetRetainagePercent(CString strValue);

	virtual bool IsRowDirty(long lRow);
	virtual bool IsColumnDirty(int iCol, long lRow);

	bool m_bShowActiveOnly;

	int m_iInstallerStatusFilter;
};
