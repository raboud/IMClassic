/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// PropSheetReportIssueWizard.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "PropSheetReportIssueWizard.h"
#include "SetIssues.h"
#include "SetSettings.h"
#include "setemployees.h"

// CPropSheetReportIssueWizard

IMPLEMENT_DYNAMIC(CPropSheetReportIssueWizard, CPropertySheet)
CPropSheetReportIssueWizard::CPropSheetReportIssueWizard(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_propTypeOfIssue);
	AddPage(&m_propStorePONumber);
	AddPage(&m_propDescription);
	//AddPage(&m_propSummary);

	SetWizardMode();
}			  
			  
CPropSheetReportIssueWizard::CPropSheetReportIssueWizard(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_propTypeOfIssue);
	AddPage(&m_propStorePONumber);
	AddPage(&m_propDescription);
	//AddPage(&m_propSummary);

	SetWizardMode();
}

CPropSheetReportIssueWizard::~CPropSheetReportIssueWizard()
{
}


BEGIN_MESSAGE_MAP(CPropSheetReportIssueWizard, CPropertySheet)
END_MESSAGE_MAP()


// CPropSheetReportIssueWizard message handlers

CString CPropSheetReportIssueWizard::GetSubmitInfo()
{
	CString strInfo = "";
	strInfo.Format("Type: %s\r\n\r\nStore/PO: %s\r\n\r\nDescription:\r\n%s", m_propTypeOfIssue.GetInfo(), m_propStorePONumber.GetInfo(), m_propDescription.GetInfo());
	
	return strInfo;
}

int CPropSheetReportIssueWizard::SubmitIssue()
{
	int iSubmitID = -1;

	// get user ID
	int iUserID = CGlobals::GetEmployeeID();
	CString strUserName = CGlobals::GetUserFirstAndLastName();
	CString strInfo = GetSubmitInfo();
	CString strType = m_propTypeOfIssue.GetInfo();

	CSetIssues setIssues(&g_dbFlooring);
	// we are setting the filter so that after we added this issue, we
	// will have at least one row in our recordset.  This is so the
	// functionality for getting the IDENTITY column will work.
	setIssues.m_strFilter.Format("AddedByUser = %d", iUserID);
	setIssues.Open();

	setIssues.AddNew();

	setIssues.m_AddedByUser = iUserID;
	setIssues.m_DateAdded = COleDateTime(CGlobals::GetCurrentSystemTime());
	setIssues.m_Description = strInfo.Left(1024);
	setIssues.m_StatusID = 1;

	if (setIssues.Update())
	{
		setIssues.Requery();
		CString strIdentity = setIssues.m_Identity;
		if (strIdentity.GetLength() > 0)
		{
			iSubmitID = atol(strIdentity);
		}
	}

	if (iSubmitID != -1)
	{
		// email the info
		CString strSubject;
		strSubject.Format("Installation Manager Issue: %d - %s (Submitted By: %s)", iSubmitID, strType, strUserName);
		CSetSettings setSettings(&g_dbFlooring);
		if (setSettings.GetSetting("IssueNotificationEmailEnable") == "1")
		{
			SendIssueEmailSMTP(strSubject, strInfo, iUserID);
		}
	}

	return iSubmitID;
}

void CPropSheetReportIssueWizard::SendIssueEmailSMTP(CString strSubject, CString strBody, int /* iUserID */)
{
	CString EmailFrom = CGlobals::GetCurrentUserSMTPEmailAddress();
	CString EmailReplyTo = CGlobals::GetCurrentUserReplyToEmailAddress();
	CString EmailFromPassword = CGlobals::GetUserEmailPassword();
	
	CSetSettings setSettings(&g_dbFlooring);
	CString EmailTo = setSettings.GetSettings("IssueNotificationEmailTo");
	
	if (EmailFrom.GetLength() == 0)
	{
		EmailFrom = setSettings.GetSetting("EmailInternalFromDefault");
		EmailFromPassword = setSettings.GetSetting("EmailInternalFromPassword");
	}

	setSettings.Close();	

	CString strError = "";

	bool bOK = CGlobals::SendEmail(EmailTo, EmailFrom, EmailFromPassword, EmailFrom, EmailReplyTo, strSubject, strBody, strError);

	// DKB Commenting this out because we were having issues with ODBC and multiple threads
	/*SendEmailParams* pParams = new SendEmailParams();
	pParams->parentWindowHandle = AfxGetApp()->m_pMainWnd->m_hWnd;
	pParams->strTo = EmailTo;
	pParams->strFrom = EmailFrom;	
	pParams->strPassword = EmailFromPassword;
	pParams->strReplyToAddr = EmailReplyTo;
	pParams->strSubject = strSubject;
	pParams->strBody = strBody;

	AfxBeginThread(CGlobals::SendEmailWorkerThread, pParams);*/
	
	if (!bOK)
	{
		CString strMessage;
		if (strError.GetLength() > 0)
		{
			strMessage.Format("The issue could not be e-mailed! \r\nThe error was: %s", strError);
		}
		else
		{
			strMessage = "The issue could not be e-mailed! \r\nSee the email log file for details.";
		}
		MessageBox(strMessage, "Error!");
	}
}