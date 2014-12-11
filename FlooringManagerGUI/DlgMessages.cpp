// DlgMessages.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgMessages.h"
#include ".\dlgmessages.h"
#include "printer.h"


// CDlgMessages dialog

IMPLEMENT_DYNAMIC(CDlgMessages, CDialog)
CDlgMessages::CDlgMessages(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMessages::IDD, pParent)
	, m_strDialogTitle(_T(""))
	, m_strOKButtonText(_T("OK"))
	, m_strCancelButtonText(_T("Cancel"))
{
}

CDlgMessages::~CDlgMessages()
{
}

void CDlgMessages::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MESSAGES_LISTTITLE, m_stListTitle);
	DDX_Control(pDX, IDC_MESSAGES_LIST, m_lbMessages);
	DDX_Control(pDX, IDC_MESSAGES_PRINT, m_btnPrint);
}


BEGIN_MESSAGE_MAP(CDlgMessages, CDialog)
	ON_BN_CLICKED(IDC_MESSAGES_PRINT, OnBnClickedMessagesPrint)
END_MESSAGE_MAP()


// CDlgMessages message handlers

BOOL CDlgMessages::OnInitDialog()
{
	CDialog::OnInitDialog();

	int iCount = m_astrMessages.GetCount();
	for (int i = 0; i < iCount; i++)
	{
		COLORREF color = RGB(255, 255, 0);
		if (m_astrMessages[i].Find("ERROR:") != -1)
		{
			color = RGB(255, 0, 0);
		}
		m_lbMessages.AddEntry(m_astrMessages[i], color);
	}

	SetWindowText(m_strDialogTitle);
	m_stListTitle.SetWindowText(m_strListTitle);

	UpdateButtonText(IDOK, m_strOKButtonText);
	UpdateButtonText(IDCANCEL, m_strCancelButtonText);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMessages::OnBnClickedMessagesPrint()
{
	CPrinter* pPrinter = NULL;

	CPrintDialog dlg(FALSE, PD_ALLPAGES | PD_HIDEPRINTTOFILE | PD_NOPAGENUMS | PD_RETURNDC | PD_USEDEVMODECOPIES);
	m_btnPrint.EnableWindow(FALSE);
	if (dlg.DoModal() == IDOK)
	{
		CDC dc;
		dc.Attach(dlg.m_pd.hDC);
		pPrinter = new CPrinter(&dc);
		pPrinter->SetPrinterFont();
		if(pPrinter->StartPrinting())
		{
			int iCount = m_lbMessages.GetCount();
			for (int i = 0; i < iCount; i++)
			{
				pPrinter->PrintLine(m_astrMessages[i]);
			}

			pPrinter->EndPrinting();
		}

		delete pPrinter;
		::DeleteDC(dc.Detach());
	}
	m_btnPrint.EnableWindow();

}

void CDlgMessages::SetMessages(CStringArray* pstrMessages)
{
	m_astrMessages.Append(*pstrMessages);
}

void CDlgMessages::SetDialogTitle(CString strTitle)
{
	m_strDialogTitle = strTitle;
}

void CDlgMessages::SetListTitle(CString strTitle)
{
	m_strListTitle = strTitle;
}

void CDlgMessages::SetButtonText(int iButtonID, CString strText)
{
	if (iButtonID == IDOK)
	{
		m_strOKButtonText = strText;
	}
	else if (iButtonID == IDCANCEL)
	{
		m_strCancelButtonText = strText;
	}
}

void CDlgMessages::UpdateButtonText(int iButtonID, CString strText)
{
	CWnd* pWnd = (CWnd*) GetDlgItem(iButtonID);
	if (pWnd != NULL)
	{
		pWnd->SetWindowText(strText);
	}
}