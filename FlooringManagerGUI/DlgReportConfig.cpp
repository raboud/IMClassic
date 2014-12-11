/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// DlgReportConfig.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgReportConfig.h"
#include "setmarket.h"
#include "setdivision.h"
#include "Permissions.h"

const int iMARKETID_BIT_SHIFT = 8;
// CDlgReportConfig dialog

IMPLEMENT_DYNAMIC(CDlgReportConfig, CDialog)
CDlgReportConfig::CDlgReportConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgReportConfig::IDD, pParent)
	, m_strFilter(_T(""))
//	, m_strMarkets(_T("All"))
//	, m_strDivisions(_T("All"))
	, m_bShowStartDate(false)
	, m_bShowEndDate(false)
	, m_strReportTitle(_T(""))
//	, m_strCRMarketsFilterString(_T(""))
//	, m_strCRDivisionsFilterString(_T(""))
	, m_strStartDateText(_T("Date:"))
	, m_strEndDateText(_T("Date:"))
	, m_strPermissionName(_T(""))
{
}

CDlgReportConfig::~CDlgReportConfig()
{
}

void CDlgReportConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORTCONFIG_DTP_START, m_dtpStartDate);
	DDX_Control(pDX, IDC_REPORTCONFIG_STARTDATE, m_stStartDate);
	DDX_Control(pDX, IDC_REPORTCONFIG_ENDDATE, m_stEndDate);
	DDX_Control(pDX, IDC_REPORTCONFIG_TITLE, m_stReportTitle);
	DDX_Text(pDX, IDC_REPORTCONFIG_STARTDATE, m_strStartDateText);
	DDX_Text(pDX, IDC_REPORTCONFIG_ENDDATE, m_strEndDateText);
	DDX_Control(pDX, IDC_REPORTCONFIG_DTP_END, m_dtpEndDate);
	DDX_Control(pDX, IDC_REPORTCONFIG_MARKETDIVISIONLISTBOX, m_listMarketDivision);
	DDX_Control(pDX, IDC_REPORTCONFIG_ALLMARKETSANDDIVISIONS, m_btnAllMarketsDivisions);
	DDX_Control(pDX, IDC_REPORTCONFIG_SELECTEDMARKETSANDDIVISIONS, m_btnSelectedMarketsDivisions);
}


BEGIN_MESSAGE_MAP(CDlgReportConfig, CDialog)
	ON_BN_CLICKED(IDC_REPORTCONFIG_ALLMARKETSANDDIVISIONS, OnBnClickedReportconfigAllmarketsanddivisions)
	ON_BN_CLICKED(IDC_REPORTCONFIG_SELECTEDMARKETSANDDIVISIONS, OnBnClickedReportconfigSelectedmarketsanddivisions)
END_MESSAGE_MAP()


// CDlgReportConfig message handlers

BOOL CDlgReportConfig::OnInitDialog()
{
	ASSERT(m_strReportTitle != _T(""));
	ASSERT(m_strPermissionName != _T(""));

	CDialog::OnInitDialog();
	if (!m_bShowStartDate)
	{
		m_dtpStartDate.ShowWindow(SW_HIDE);
		m_stStartDate.ShowWindow(SW_HIDE);
	}

	if (!m_bShowEndDate)
	{
		m_dtpEndDate.ShowWindow(SW_HIDE);
		m_stEndDate.ShowWindow(SW_HIDE);
	}

	PopulateMarketsAndDivisions();

	m_btnAllMarketsDivisions.SetCheck(1);
	m_listMarketDivision.EnableWindow(FALSE);

	m_stReportTitle.SetWindowText(m_strReportTitle);

	if ( m_listMarketDivision.GetCount() == 0 )
	{
		AfxMessageBox("You do not have permission to run reports for any Market / Division.  Please contact a system administrator.");
		WPARAM wparam;
		LPARAM lparam;
		wparam = (BN_CLICKED << 16) | IDCANCEL;
		CWnd* pwnd = GetDlgItem(IDCANCEL);
		lparam = (LPARAM) pwnd->m_hWnd;
		::PostMessage(m_hWnd, WM_COMMAND, wparam, lparam);
	}

	if ( (m_listMarketDivision.GetCount() == 1) && 
		 (m_bShowStartDate == false) &&
		 (m_bShowEndDate == false))
	{
		// in this case we wish to just close the dialog box,
		// as there is really nothing for the user to do but hit
		// OK, so we do it for them...
		WPARAM wparam;
		LPARAM lparam;
		wparam = (BN_CLICKED << 16) | IDOK;
		CWnd* pwnd = GetDlgItem(IDOK);
		lparam = (LPARAM) pwnd->m_hWnd;
		::PostMessage(m_hWnd, WM_COMMAND, wparam, lparam);
	}

	CPermissions perm;
	if (!perm.HasPermission("CanSelectAllMarketsDivisions"))
	{
		m_btnAllMarketsDivisions.EnableWindow(FALSE);
		m_btnAllMarketsDivisions.SetCheck(0);
		m_btnSelectedMarketsDivisions.SetCheck(1);
		m_listMarketDivision.EnableWindow();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

CString CDlgReportConfig::GetFilterString(void)
{
	return m_strFilter;
}

void CDlgReportConfig::PopulateMarketsAndDivisions()
{
	CSetDivision rsDivision(&g_dbFlooring);
	rsDivision.Open();

	CSetMarket rsMarket(&g_dbFlooring);
	rsMarket.Open();

	CSetViewUserPermissions setVwUserPermissions(&g_dbFlooring);
	CFlooringApp* pApp = (CFlooringApp*) AfxGetApp() ;
	setVwUserPermissions.m_strFilter.Format("ID = %d AND PermissionName = '%s'", pApp->GetEmployeeID(), m_strPermissionName);
	setVwUserPermissions.m_strSort = "MarketName, DivisionName";
	setVwUserPermissions.Open();

	if (setVwUserPermissions.IsEOF() && !pApp->IsAdmin())
	{
		// not an admin and no permissions that match!
		return;
	}

	CPermissions permissions;
	CString strListString = "";
	DWORD dwItemData = 0;

	if (pApp->IsAdmin())
	{
		while (!rsMarket.IsEOF())
		{
			while (!rsDivision.IsEOF())
			{
				if (rsMarket.m_MarketId == -1)
				{
					if (rsDivision.m_DivisionID == -1)
					{
						strListString = "All Markets - All Divisions";
						int iIndex = m_listMarketDivision.AddString(strListString);
						if (iIndex != LB_ERR)
						{
							dwItemData = (0xffffffff);
							m_listMarketDivision.SetItemData(iIndex, dwItemData);
						}
					}
					else
					{
						strListString = "All Markets - " + rsDivision.m_Division.Trim();
						int iIndex = m_listMarketDivision.AddString(strListString);
						if (iIndex != LB_ERR)
						{
							dwItemData = (0xffff << 16) | rsDivision.m_DivisionID;
							m_listMarketDivision.SetItemData(iIndex, dwItemData);
						}
					}
				}
				else
				{
					if (rsDivision.m_DivisionID == -1)
					{
						strListString = rsMarket.m_MarketName.Trim() + " - All Divisions";
						int iIndex = m_listMarketDivision.AddString(strListString);
						if (iIndex != LB_ERR)
						{
							dwItemData = (rsMarket.m_MarketId << 16) | 0xffff;
							m_listMarketDivision.SetItemData(iIndex, dwItemData);
						}
					}
					else
					{
						strListString = rsMarket.m_MarketName.Trim() + " - " + rsDivision.m_Division.Trim();
						int iIndex = m_listMarketDivision.AddString(strListString);
						if (iIndex != LB_ERR)
						{
							dwItemData = (rsMarket.m_MarketId << 16) | rsDivision.m_DivisionID;
							m_listMarketDivision.SetItemData(iIndex, dwItemData);
						}
					}
				}
				rsDivision.MoveNext();
			}
			rsMarket.MoveNext();
			rsDivision.MoveFirst();
		}
	}
	else
	{
		// iterate through the users permissions and create a list reflecting them
		while(!setVwUserPermissions.IsEOF())
		{
			long MarketID = setVwUserPermissions.m_Market;
			long DivisionID = setVwUserPermissions.m_Division;
			if (MarketID == -1)
			{
				rsMarket.MoveFirst();
				while(!rsMarket.IsEOF())
				{
					if (DivisionID == -1)
					{
						rsDivision.MoveFirst();
						while(!rsDivision.IsEOF())
						{
							if (rsMarket.m_MarketId == -1)
							{
								if (rsDivision.m_DivisionID == -1)
								{
									strListString = "All Markets - All Divisions";
									if (m_listMarketDivision.FindStringExact(0, strListString) == -1)
									{
										int iIndex = m_listMarketDivision.AddString(strListString);
										if (iIndex != LB_ERR)
										{
											dwItemData = (0xffffffff);
											m_listMarketDivision.SetItemData(iIndex, dwItemData);
										}
									}
								}
								else
								{
									strListString = "All Markets - " + rsDivision.m_Division.Trim();
									if (m_listMarketDivision.FindStringExact(0, strListString) == -1)
									{
										int iIndex = m_listMarketDivision.AddString(strListString);
										if (iIndex != LB_ERR)
										{
											dwItemData = (0xffff << 16) | rsDivision.m_DivisionID;
											m_listMarketDivision.SetItemData(iIndex, dwItemData);
										}
									}
								}
							}
							else
							{
								if (rsDivision.m_DivisionID == -1)
								{
									strListString = rsMarket.m_MarketName.Trim() + " - All Divisions";
									if (m_listMarketDivision.FindStringExact(0, strListString) == -1)
									{
										int iIndex = m_listMarketDivision.AddString(strListString);
										if (iIndex != LB_ERR)
										{
											dwItemData = (rsMarket.m_MarketId << 16) | 0xffff;
											m_listMarketDivision.SetItemData(iIndex, dwItemData);
										}
									}
								}
								else
								{
									strListString = rsMarket.m_MarketName.Trim() + " - " + rsDivision.m_Division.Trim();
									if (m_listMarketDivision.FindStringExact(0, strListString) == -1)
									{
										int iIndex = m_listMarketDivision.AddString(strListString);
										if (iIndex != LB_ERR)
										{
											dwItemData = (rsMarket.m_MarketId << 16) | rsDivision.m_DivisionID;
											m_listMarketDivision.SetItemData(iIndex, dwItemData);
										}
									}
								}
							}
							rsDivision.MoveNext();
						}
					}
					else
					{
						strListString = rsMarket.m_MarketName.Trim() + " - " + setVwUserPermissions.m_DivisionName.Trim();
						if (m_listMarketDivision.FindStringExact(0, strListString) == -1)
						{
							int iIndex = m_listMarketDivision.AddString(strListString);
							if (iIndex != LB_ERR)
							{
								dwItemData = (rsMarket.m_MarketId << 16) | DivisionID;
								m_listMarketDivision.SetItemData(iIndex, dwItemData);
							}
						}
					}
					rsMarket.MoveNext();
				}
			}
			else
			{
				if (DivisionID == -1)
				{
					rsDivision.MoveFirst();
					while(!rsDivision.IsEOF())
					{
						if (rsDivision.m_DivisionID == -1)
						{
							strListString = setVwUserPermissions.m_MarketName.Trim() + " - All Divisions";
							if (m_listMarketDivision.FindStringExact(0, strListString) == -1)
							{
								int iIndex = m_listMarketDivision.AddString(strListString);
								if (iIndex != LB_ERR)
								{
									dwItemData = (MarketID << 16) | 0xffff;
									m_listMarketDivision.SetItemData(iIndex, dwItemData);
								}
							}
						}
						else
						{
							strListString = setVwUserPermissions.m_MarketName.Trim() + " - " + rsDivision.m_Division.Trim();
							if (m_listMarketDivision.FindStringExact(0, strListString) == -1)
							{
								int iIndex = m_listMarketDivision.AddString(strListString);
								if (iIndex != LB_ERR)
								{
									dwItemData = (MarketID << 16) | rsDivision.m_DivisionID;
									m_listMarketDivision.SetItemData(iIndex, dwItemData);
								}
							}
						}
						rsDivision.MoveNext();
					}
				}
				else
				{
					strListString = setVwUserPermissions.m_MarketName.Trim() + " - " + setVwUserPermissions.m_DivisionName.Trim();
					if (m_listMarketDivision.FindStringExact(0, strListString) == -1)
					{
						int iIndex = m_listMarketDivision.AddString(strListString);
						if (iIndex != LB_ERR)
						{
							dwItemData = (MarketID << 16) | DivisionID;
							m_listMarketDivision.SetItemData(iIndex, dwItemData);
						}
					}
				}
			}
			setVwUserPermissions.MoveNext();
		}
	}

	/*while (!rsDivision.IsEOF())
	{
		if (rsDivision.m_DivisionID != -1)
		{
			if ( permissions.HasPermissionDivision("AccessReportDivisionAllMarkets", rsDivision.m_DivisionID ) )
			{
				strListString = rsDivision.m_Division.Trim() + " - All Markets";
				int iIndex = m_listMarketDivision.AddString(strListString);
				if (iIndex != LB_ERR)
				{
					dwItemData = (0xffff << 16) | rsDivision.m_DivisionID;
					m_listMarketDivision.SetItemData(iIndex, dwItemData);
				}
			}

			while (!rsMarket.IsEOF())
			{
				if (rsMarket.m_MarketId != -1)
				{
					if ( permissions.HasPermission("AccessReportMarketDivision", rsMarket.m_MarketId, rsDivision.m_DivisionID) )
					{
						strListString = rsMarket.m_MarketName.Trim() + " - " + rsDivision.m_Division.Trim();
						int iIndex = m_listMarketDivision.AddString(strListString);
						if (iIndex != LB_ERR)
						{
							dwItemData = (rsMarket.m_MarketId << 16) | rsDivision.m_DivisionID;
							m_listMarketDivision.SetItemData(iIndex, dwItemData);
						}
					}
				}
				rsMarket.MoveNext();
			}
		}
		rsMarket.MoveFirst();
		rsDivision.MoveNext();
	}

	rsMarket.MoveFirst();
	while (!rsMarket.IsEOF())
	{
		if (rsMarket.m_MarketId != -1)
		{
			if ( permissions.HasPermissionMarket("AccessReportMarketAllDivisions", rsMarket.m_MarketId ) )
			{
				strListString = rsMarket.m_MarketName.Trim() + " - All Divisions";
				int iIndex = m_listMarketDivision.AddString(strListString);
				if (iIndex != LB_ERR)
				{
					dwItemData = (rsMarket.m_MarketId << 16) | 0xffff;
					m_listMarketDivision.SetItemData(iIndex, dwItemData);
				}
			}
		}
		rsMarket.MoveNext();
	}*/


	if (m_listMarketDivision.GetCount() == 1)
	{
		m_listMarketDivision.SetCurSel(0);
	}

	rsDivision.Close();
	rsMarket.Close();
}

void CDlgReportConfig::OnBnClickedReportconfigAllmarketsanddivisions()
{
	m_listMarketDivision.EnableWindow(FALSE);
}

void CDlgReportConfig::OnBnClickedReportconfigSelectedmarketsanddivisions()
{
	m_listMarketDivision.EnableWindow(TRUE);
}



COleDateTime CDlgReportConfig::GetStartDate(void)
{
	return m_dateStart;
}

COleDateTime CDlgReportConfig::GetEndDate(void)
{
	return m_dateEnd;
}

void CDlgReportConfig::OnOK()
{
	if (ValidateSelections())
	{
		m_dtpStartDate.GetTime(m_dateStart);
		m_dtpEndDate.GetTime(m_dateEnd);
		FormatFilterString();	
		CDialog::OnOK();
	}
}

bool CDlgReportConfig::ValidateSelections()
{
	bool bValid = true;

	if (m_btnSelectedMarketsDivisions.GetCheck() > 0)
	{
		if (m_listMarketDivision.GetSelCount() == 0) 
		{
			bValid = false;
			MessageBox("A Market / Division entry must be selected.", "Error");
		}
	}

	return bValid;
}

void CDlgReportConfig::FormatFilterString()
{
	InitFilterArrays();
	
	CString strTemp = "";
	m_strFilter = "";
	
	CArray<int,int> aiListBoxSel;
	DWORD dwMarketID;
	DWORD dwDivisionID;

	int iNumSel = m_listMarketDivision.GetSelCount();

	bool bAllMarkets = false;
	bool bAllDivisions = false;

	if (iNumSel == 0)
	{
		// non are selected - add all indexes to the selection array
        int iCount = m_listMarketDivision.GetCount();
		for (int iIndex = 0; iIndex < iCount; iIndex++)
		{
			aiListBoxSel.Add(iIndex);
		}
	}
	else
	{
		// have some selected, get the list of selected items
		aiListBoxSel.SetSize(iNumSel);
		m_listMarketDivision.GetSelItems(iNumSel, aiListBoxSel.GetData());
	}

	// iterate through the selection array
	int iCount = aiListBoxSel.GetCount();
	for (int iIndex = 0; iIndex < iCount; iIndex++)
	{
		// the list control stores the markets/divisions for each entry as a DWORD value.
		// the market is in the upper word and the division is in the lower word
        dwMarketID = m_listMarketDivision.GetItemData(aiListBoxSel[iIndex]);
		dwDivisionID = dwMarketID & 0x0000ffff;
		dwMarketID = dwMarketID >> 16;
		if (dwMarketID == 0x0000ffff)
		{
			if (dwDivisionID == 0x0000ffff)
			{
				// empty the arrays
				InitFilterArrays();

				// add all markets and division pairs
				AddAllMarketsAllDivisions();

				bAllMarkets = true;
				bAllDivisions = true;

				break;
			}
			else
			{
				// add all markets and the current division id
				AddAllMarkets(dwDivisionID);
				bAllMarkets = true;
			}
		}
		else
		{
			if (dwDivisionID == 0x0000ffff)
			{
				// add all divisions for this current market
				AddAllDivisions(dwMarketID);
				bAllDivisions = true;
			}
			else
			{
				// add market division pair
				AddMarketDivision(dwMarketID, dwDivisionID);
			}
		}
	}

	// need to remove duplicates
	RemoveDuplicatesFromFilterArray();

	// we should now have our Market/DivisionIDs array of structures filled
	SuMarketDivisionPair suTemp;
	m_strMarketsDivisions = "";
	CString strMarketList;
	CString strDivisionList;
	
	for (int iIndex = 0; iIndex < m_asuMarketsDivisions.GetCount(); iIndex++)
	{
		suTemp = m_asuMarketsDivisions.GetAt(iIndex);
		m_aiMarketsDivisions.Add(suTemp.dwMarketDivision);
		if (bAllMarkets)
		{
			if (!bAllDivisions)
			{
				if (strDivisionList.Find(suTemp.strDivisionName) == -1)
				{
					if (strDivisionList.GetLength() > 0) strDivisionList += ", ";
					strDivisionList += suTemp.strDivisionName;
				}
			}
		}
		else
		{
			if (bAllDivisions)
			{
				if (strMarketList.Find(suTemp.strMarketName) == -1)
				{
					if (strMarketList.GetLength() > 0) strMarketList += ", ";
					strMarketList += suTemp.strMarketName;
				}
			}
			else
			{
				if (m_strMarketsDivisions.GetLength() > 0) m_strMarketsDivisions += ", ";
				m_strMarketsDivisions += suTemp.strMarketName + "/" + suTemp.strDivisionName;
			}
		}
	}

	if (bAllMarkets)
	{
		if (bAllDivisions)
		{
			m_strMarketsDivisions = "All Markets / All Divisions";
		}
		else
		{
			m_strMarketsDivisions = "All Markets / Divisions: " + strDivisionList;
		}
	}
	else
	{
		if (bAllDivisions)
		{
			m_strMarketsDivisions = "All Divisions / Markets: " + strMarketList;
		}
	}

	if (m_strMarketsDivisions.GetLength() > 255)
	{
		m_strMarketsDivisions = m_strMarketsDivisions.Left(252);
		int iComma = m_strMarketsDivisions.ReverseFind(',');
		m_strMarketsDivisions = m_strMarketsDivisions.Left(iComma) + "...";
	}
}

void CDlgReportConfig::InitFilterArrays(void)
{
	m_aiMarketsDivisions.RemoveAll();
	m_asuMarketsDivisions.RemoveAll();
}

//bool CDlgReportConfig::InMarketArray(int iMarketID)
//{
//	bool bFound = false;
//	for (int i = 0; i < m_aiMarkets.GetCount(); i++)
//	{
//		if (m_aiMarkets[i] == iMarketID)
//		{
//			bFound = true;
//			break;
//		}
//	}
//
//	return bFound;
//}

//bool CDlgReportConfig::InDivisionArray(int iDivisionID)
//{
//	bool bFound = false;
//	for (int i = 0; i < m_aiDivisions.GetCount(); i++)
//	{
//		if (m_aiDivisions[i] == iDivisionID)
//		{
//			bFound = true;
//			break;
//		}
//	}
//
//	return bFound;
//}

CString CDlgReportConfig::AddAllMarkets(int iDivisionID)
{
	CString strTemp = "";

	CSetDivision rsDivision(&g_dbFlooring);
	rsDivision.m_strFilter.Format("DivisionID = %d", iDivisionID);
	rsDivision.Open();

	CSetMarket rsMarket(&g_dbFlooring);
	rsMarket.m_strFilter = "MarketId <> -1";
	rsMarket.Open();

	SuMarketDivisionPair suTemp;
	
	while (!rsMarket.IsEOF())
	{
		suTemp.dwMarketDivision = (rsMarket.m_MarketId << iMARKETID_BIT_SHIFT) | rsDivision.m_DivisionID;
		suTemp.strMarketName = rsMarket.m_MarketName.Trim();
		suTemp.strDivisionName = rsDivision.m_Division.Trim();
		m_asuMarketsDivisions.Add(suTemp);					
		rsMarket.MoveNext();
	}

	rsMarket.Close();
	rsDivision.Close();

	return strTemp;
}

CString CDlgReportConfig::AddAllDivisions(int iMarketID)
{
	CString strTemp = "";

	CSetMarket rsMarket(&g_dbFlooring);
	rsMarket.m_strFilter.Format("MarketId = %d", iMarketID);
	rsMarket.Open();

	CSetDivision rsDivision(&g_dbFlooring);
	rsDivision.m_strFilter = "DivisionID <> -1";
	rsDivision.Open();

	SuMarketDivisionPair suTemp;
	
	while (!rsDivision.IsEOF())
	{
		suTemp.dwMarketDivision = (rsMarket.m_MarketId << iMARKETID_BIT_SHIFT) | rsDivision.m_DivisionID;
		suTemp.strMarketName = rsMarket.m_MarketName.Trim();
		suTemp.strDivisionName = rsDivision.m_Division.Trim();
		m_asuMarketsDivisions.Add(suTemp);					
		rsDivision.MoveNext();
	}

	rsMarket.Close();
	rsDivision.Close();


	return strTemp;
}

CString CDlgReportConfig::AddAllMarketsAllDivisions()
{
	CString strTemp = "";

	CSetDivision rsDivision(&g_dbFlooring);
	rsDivision.m_strFilter = "DivisionID <> -1";
	rsDivision.Open();

	CSetMarket rsMarket(&g_dbFlooring);
	rsMarket.m_strFilter = "MarketID <> -1";
	rsMarket.Open();

	SuMarketDivisionPair suTemp;
	
	while (!rsMarket.IsEOF())
	{
		rsDivision.MoveFirst();
		while (!rsDivision.IsEOF())
		{
			suTemp.dwMarketDivision = (rsMarket.m_MarketId << iMARKETID_BIT_SHIFT) | rsDivision.m_DivisionID;
			suTemp.strMarketName = rsMarket.m_MarketName.Trim();
			suTemp.strDivisionName = rsDivision.m_Division.Trim();
			m_asuMarketsDivisions.Add(suTemp);
			rsDivision.MoveNext();
		}
		rsMarket.MoveNext();
	}

	rsMarket.Close();
	rsDivision.Close();

	return strTemp;
}

CString CDlgReportConfig::AddMarketDivision(int iMarketID, int iDivisionID)
{
	CString strTemp = "";

	CSetMarket rsMarket(&g_dbFlooring);
	rsMarket.m_strFilter.Format("MarketId = %d", iMarketID);
	rsMarket.Open();

	CSetDivision rsDivision(&g_dbFlooring);
	rsDivision.m_strFilter.Format("DivisionID = %d", iDivisionID);
	rsDivision.Open();

	SuMarketDivisionPair suTemp;
	
	if (!rsDivision.IsEOF() && !rsMarket.IsEOF())
	{
		suTemp.dwMarketDivision = (rsMarket.m_MarketId << iMARKETID_BIT_SHIFT) | rsDivision.m_DivisionID;
		suTemp.strMarketName = rsMarket.m_MarketName.Trim();
		suTemp.strDivisionName = rsDivision.m_Division.Trim();
		m_asuMarketsDivisions.Add(suTemp);					
	}

	rsMarket.Close();
	rsDivision.Close();

	return strTemp;
}

int CDlgReportConfig::RemoveDuplicatesFromFilterArray()
{
	int NumRemoved = 0;

	CArray <SuMarketDivisionPair, SuMarketDivisionPair> asuTemp;

	SuMarketDivisionPair suTemp;

	int iNumEntries = m_asuMarketsDivisions.GetCount();
	for (int iIndex = 0; iIndex < iNumEntries; iIndex++)
	{
		suTemp = m_asuMarketsDivisions.GetAt(iIndex);
		bool bFound = false;
		for (int iNewIndex=0; iNewIndex < asuTemp.GetCount(); iNewIndex++)
		{
			if (suTemp.dwMarketDivision == asuTemp[iNewIndex].dwMarketDivision)
			{
				bFound = true;
				break;
			}
		}
		if (!bFound)
		{
			asuTemp.Add(suTemp);
		}
	}

	NumRemoved = m_asuMarketsDivisions.GetCount() - asuTemp.GetCount();

	m_asuMarketsDivisions.RemoveAll();
	for (int iIndex = 0; iIndex < asuTemp.GetCount(); iIndex++)
	{
		m_asuMarketsDivisions.Add(asuTemp.GetAt(iIndex));
	}

	return NumRemoved;
}