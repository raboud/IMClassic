#ifndef _DATA_EXCHANGE_H_
#define _DATA_EXCHANGE_H_

#include <afxdb.h>

void AFXAPI DDX_ComboBoxData(CDataExchange* pDX, int nIDC, long& lStore) ;
void AFXAPI DDX_ListBoxMultiSelect(CDataExchange* pDX, int nIDC, long& lValue);
void AFXAPI DDV_TELEPHONE(CDataExchange* pDX, CString& value, CRecordset* pSet, bool bMustBeFull = false) ;
void AFXAPI DDX_MultiListBoxData(CDataExchange* pDX, int nIDC, long& lStore) ;

#endif