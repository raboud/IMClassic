// CustSatPropertyPage.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "CustSatPropertyPage.h"


// CCustSatPropertyPage dialog

//const int iMAX_NOTES  = 2000;

IMPLEMENT_DYNAMIC(CCustSatPropertyPage, CPropertyPage)
//CCustSatPropertyPage::CCustSatPropertyPage(UINT dlgID, UINT editExistingID, UINT editAdditionalID)
//	: CPropertyPage(dlgID), m_editExistingID(editExistingID), m_editAdditionalID(editAdditionalID)
CCustSatPropertyPage::CCustSatPropertyPage()
	: CPropertyPage(CCustSatPropertyPage::IDD)
//	, m_editExistingID(editExistingID), m_editAdditionalID(editAdditionalID)

{
	m_strExistingWindowText = _T("");
	m_strAdditionalWindowText = _T("");
}

CCustSatPropertyPage::~CCustSatPropertyPage()
{
}

void CCustSatPropertyPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
//	DDX_Control(pDX, m_editExistingID, m_editExisting);
//	DDX_Control(pDX, m_editAdditionalID, m_editAdditional);
//	DDX_Text(pDX, m_editExistingID, m_strExistingWindowText);
//	DDX_Text(pDX, m_editAdditionalID, m_strAdditionalWindowText);
}


BEGIN_MESSAGE_MAP(CCustSatPropertyPage, CPropertyPage)
	ON_MESSAGE(WM_USER_RICHEDITCHANGE, OnRichEditChange)
END_MESSAGE_MAP()


// CCustSatPropertyPage message handlers

LRESULT CCustSatPropertyPage::OnRichEditChange(WPARAM wParam, LPARAM lParam)
{
	return 0;
}


BOOL CCustSatPropertyPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	int iLimit = (iMAX_RICHEDIT_FIELD_LENGTH * 0.8);

	m_editExisting.LimitText(iLimit);
	m_editAdditional.LimitText(iLimit);

	m_editExisting.SetEventMask( m_editExisting.GetEventMask() | ENM_CHANGE );
	m_editAdditional.SetEventMask( m_editAdditional.GetEventMask() | ENM_CHANGE );

	m_editExisting.SetFontName(_T("Arial"));
	m_editExisting.SetFontSize(12);

	m_editAdditional.SetFontName(_T("Arial"));
	m_editAdditional.SetFontSize(12);

	m_editExisting.EnableWindow( m_bExistingReadOnly == false ); 

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


CString CCustSatPropertyPage::GetCombinedRTF()
{
	CStringArray strParagraphs;
	
	CString strRTFText = m_editExisting.GetRTF();
	strRTFText = strRTFText.Left(strRTFText.GetLength() - 1);
	
	int iNumParagraphs = m_editAdditional.GetParagraphContents(strParagraphs);
	for (int iCount = 0; iCount < iNumParagraphs; iCount++)
	{
		CString strTemp = CString(strParagraphs.GetAt(iCount));
		strRTFText = strRTFText + strTemp;
	}
	strRTFText += "}";

	return strRTFText;
}
