#pragma once

#include "CFRichEdit.h"

// CCustSatPropertyPage dialog

class CCustSatPropertyPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CCustSatPropertyPage)

public:
	//CCustSatPropertyPage(UINT dlgID, UINT editExistingID, UINT editAdditionalID);
	CCustSatPropertyPage();
	virtual ~CCustSatPropertyPage();

	CString GetExistingRTF();
	CString GetAdditionalRTF();
	int GetAdditionalParagraphContents(CStringArray& strParagraphs);
	
	CString GetCombinedRTF();

	void SetExistingWindowText(CString strText);
	void SetAdditionalWindowText(CString strText);

	void SetSelectionBold();
	void SetSelectionItalic();
	void SetSelectionUnderlined();

	void SetExistingReadOnly( bool bReadOnly );

	enum { IDD = IDD_ACTION_REPORT_CAUSE_PROPPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	UINT m_editExistingID;
	UINT m_editAdditionalID;

	CCFRichEdit m_editExisting;
	CCFRichEdit m_editAdditional;

	CString m_strExistingWindowText;
	CString m_strAdditionalWindowText;

	bool m_bExistingReadOnly;

	virtual LRESULT OnRichEditChange(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};

inline int CCustSatPropertyPage::GetAdditionalParagraphContents(CStringArray& strParagraphs)
{
	return m_editAdditional.GetParagraphContents(strParagraphs);
}

inline CString CCustSatPropertyPage::GetExistingRTF()
{
	return m_editExisting.GetRTF();
}

inline CString CCustSatPropertyPage::GetAdditionalRTF()
{
	return m_editAdditional.GetRTF();
}

inline void CCustSatPropertyPage::SetExistingWindowText(CString strText)
{
	m_strExistingWindowText = strText;
}

inline void CCustSatPropertyPage::SetAdditionalWindowText(CString strText)
{
	m_strAdditionalWindowText = strText;
}

inline void CCustSatPropertyPage::SetSelectionBold()
{
	m_editExisting.SetSelectionBold();
	m_editAdditional.SetSelectionBold();
}

inline void CCustSatPropertyPage::SetSelectionItalic()
{
	m_editExisting.SetSelectionItalic();
	m_editAdditional.SetSelectionItalic();
}

inline void CCustSatPropertyPage::SetSelectionUnderlined()
{
	m_editExisting.SetSelectionUnderlined();
	m_editAdditional.SetSelectionUnderlined();
}

inline void CCustSatPropertyPage::SetExistingReadOnly( bool bReadOnly )
{
	m_bExistingReadOnly = bReadOnly;
}