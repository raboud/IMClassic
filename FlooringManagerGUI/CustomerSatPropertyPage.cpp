/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// CustomerSatPropertyPage.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "CustomerSatPropertyPage.h"


// CCustomerSatPropertyPage dialog

IMPLEMENT_DYNAMIC(CCustomerSatPropertyPage, CPropertyPage)
CCustomerSatPropertyPage::CCustomerSatPropertyPage(UINT nIDCaption)
	: CPropertyPage(CCustomerSatPropertyPage::IDD, nIDCaption)
{
	m_bExistingReadOnly = true;
	m_bFirstNote = true;
}

CCustomerSatPropertyPage::~CCustomerSatPropertyPage()
{
}

void CCustomerSatPropertyPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ACTION_EXISTING, m_editExisting);
	DDX_Control(pDX, IDC_ACTION_ADDITIONAL, m_editAdditional);
	DDX_Control(pDX, IDC_ACTION_REPORT_EXISTING_NOTES, m_stExistingNotes);
	DDX_Control(pDX, IDC_ACTION_REPORT_ADDITIONAL_NOTES, m_stAdditionalNotes);
}


BEGIN_MESSAGE_MAP(CCustomerSatPropertyPage, CPropertyPage)
END_MESSAGE_MAP()


// CCustomerSatPropertyPage message handlers

bool CCustomerSatPropertyPage::GetCombinedRTF(CString& strRTFText, CString& strEnteredBy)
{
	bool bOK = false;
	CStringArray strParagraphs;
	strRTFText = "";

	if ((::IsWindow(m_editExisting.m_hWnd)) && (::IsWindow(m_editAdditional.m_hWnd)))
	{
		if (m_editExisting.GetPlainText().GetLength() > 0)
		{
			strRTFText = m_editExisting.GetRTF();
			int iIndex = strRTFText.Find("\\par", 0);
			int iOffset = iIndex;
			while (iIndex != -1)
			{
				iIndex = strRTFText.Find("\\par", iIndex+3);
				if (iIndex != -1) iOffset = iIndex;
			}

			if (iOffset == -1) return false;
			
			strRTFText = strRTFText.Left(iOffset + 4);

			CString strTemp;
			strTemp.Format("\\par\\fs17\r\n%s\\par", strEnteredBy);
			
			int iNumParagraphs = m_editAdditional.GetParagraphContents(strParagraphs);

			// only add the 'entered by' text if there are additional paragraphs
			if (iNumParagraphs > 0)
			{
				strRTFText += strTemp;
			}

			for (int iCount = 0; iCount < iNumParagraphs; iCount++)
			{
				strTemp = CString(strParagraphs.GetAt(iCount));
				strRTFText = strRTFText + strTemp;
			}

			strRTFText += "}";
		}
		else
		{
			strRTFText = m_editAdditional.GetRTF();

			if (strEnteredBy.GetLength() > 0)
			{
				CString strTemp;
				strTemp.Format("\\par\\fs17\r\n%s\\par", strEnteredBy);
				int iIndex = strRTFText.Find("\\pard", 0);
				if (iIndex > -1)
				{
					strRTFText.Insert(iIndex, strTemp);
				}
			}
		}

		bOK = true;
	}

	return bOK;
}
BOOL CCustomerSatPropertyPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	int iLimit = int(CGlobals::iMAX_RICHEDIT_FIELD_LENGTH * 0.8);

	m_editExisting.LimitText(iLimit);
	m_editAdditional.LimitText(iLimit);

	m_editExisting.SetEventMask( m_editExisting.GetEventMask() | ENM_CHANGE );
	m_editExisting.SetEventMask( m_editExisting.GetEventMask() | ENM_MOUSEEVENTS );
	
	m_editAdditional.SetEventMask( m_editAdditional.GetEventMask() | ENM_CHANGE );
	m_editAdditional.SetEventMask( m_editAdditional.GetEventMask() | ENM_MOUSEEVENTS );

	m_editAdditional.SetFontName(_T("Arial"));
	m_editAdditional.SetFontSize(12);

	m_editExisting.SetReadOnly( m_bExistingReadOnly == true );

	if (m_bFirstNote)
	{
		CRect rectExisting;
		CRect rectAdditional;
		m_editExisting.GetWindowRect( &rectExisting );
		m_editAdditional.GetWindowRect( &rectAdditional );
		rectAdditional.top = rectExisting.top;
		ScreenToClient(&rectAdditional);
		m_editAdditional.MoveWindow(&rectAdditional);  
		m_stExistingNotes.SetWindowText("New Note");
		m_editExisting.ShowWindow(SW_HIDE);
		m_stAdditionalNotes.ShowWindow(SW_HIDE);
	}

	m_editExisting.SetRTF( m_strExistingWindowText );

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

