/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once

#include "CFRichEdit.h"
#include "afxwin.h"

// CCustomerSatPropertyPage dialog

class CCustomerSatPropertyPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CCustomerSatPropertyPage)

public:
	CCustomerSatPropertyPage(UINT nIDCaption = 0);
	virtual ~CCustomerSatPropertyPage();

// Dialog Data
	enum { IDD = IDD_ACTION_REPORT_PROPPAGE };

	void SetExistingWindowText(CString strText);
	void SetExistingReadOnly( bool bReadOnly );

	void SetSelectionBold();
	void SetSelectionItalic();
	void SetSelectionUnderlined();
	void SetSelectionFontName(CString strFontName);
	void SetSelectionFontSize(int iFontSize);

	bool GetExistingRTF(CString& strRTFText);
	bool GetCombinedRTF(CString& strRTFText, CString& strEnteredBy);

	bool ExistingHasText();
	bool AdditionalHasText();

	CAutoRichEditCtrl* GetExistingRichEdit();
	CAutoRichEditCtrl* GetAdditionalRichEdit();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	CString m_strExistingWindowText;
	CString m_strAdditionalWindowText;
	bool m_bExistingReadOnly;

	CCFRichEdit m_editExisting;
	CCFRichEdit m_editAdditional;

	bool m_bFirstNote;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	CStatic m_stExistingNotes;
	CStatic m_stAdditionalNotes;
};

inline void CCustomerSatPropertyPage::SetExistingWindowText(CString strText)
{
	m_strExistingWindowText = strText;
	if (strText.GetLength() > 0)
	{
		m_bFirstNote = false;
	}
}

inline void CCustomerSatPropertyPage::SetExistingReadOnly( bool bReadOnly )
{
	m_bExistingReadOnly = bReadOnly;
}

inline void CCustomerSatPropertyPage::SetSelectionBold()
{
	if (!m_editExisting.IsReadOnly()) m_editExisting.SetSelectionBold();
	m_editAdditional.SetSelectionBold();
}

inline void CCustomerSatPropertyPage::SetSelectionItalic()
{
	if (!m_editExisting.IsReadOnly()) m_editExisting.SetSelectionItalic();
	m_editAdditional.SetSelectionItalic();
}

inline void CCustomerSatPropertyPage::SetSelectionUnderlined()
{
	if (!m_editExisting.IsReadOnly()) m_editExisting.SetSelectionUnderlined();
	m_editAdditional.SetSelectionUnderlined();
}

inline void CCustomerSatPropertyPage::SetSelectionFontName(CString strFontName)
{
	if (!m_editExisting.IsReadOnly()) m_editExisting.SetFontName(strFontName);
	m_editAdditional.SetFontName(strFontName);
}

inline void CCustomerSatPropertyPage::SetSelectionFontSize(int iFontSize)
{
	if (!m_editExisting.IsReadOnly()) m_editExisting.SetFontSize(iFontSize);
	m_editAdditional.SetFontSize(iFontSize);
}

inline bool CCustomerSatPropertyPage::GetExistingRTF(CString& strRTFText)
{
	bool bOK = false;
	strRTFText = "";

	if (::IsWindow(m_editExisting.m_hWnd))
	{
		strRTFText = m_editExisting.GetRTF();
		bOK = true;
	}

	return bOK;

}

inline bool CCustomerSatPropertyPage::ExistingHasText()
{
	return ( m_editExisting.GetPlainText().GetLength() > 0 );
}

inline bool CCustomerSatPropertyPage::AdditionalHasText()
{
	return ( m_editAdditional.GetPlainText().GetLength() > 0 );
}

inline CAutoRichEditCtrl* CCustomerSatPropertyPage::GetExistingRichEdit()
{
	return &m_editExisting;
}

inline CAutoRichEditCtrl* CCustomerSatPropertyPage::GetAdditionalRichEdit()
{
	return &m_editAdditional;
}