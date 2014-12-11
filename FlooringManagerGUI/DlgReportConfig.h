#pragma once
#include "afxwin.h"
#include "afxdtctl.h"


struct SuMarketDivisionPair
{
	// we don't need a DWORD here, but we
	// are using one since that is what we 
	// use everywhere else
	DWORD dwMarketDivision;
	CString strMarketName;
	CString strDivisionName;

};

// CDlgReportConfig dialog

class CDlgReportConfig : public CDialog
{
	DECLARE_DYNAMIC(CDlgReportConfig)

public:

	CString m_strReportTitle;
	CString m_strPermissionName;

	bool m_bShowStartDate;
	bool m_bShowEndDate;

	CDlgReportConfig(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgReportConfig();
	CString GetFilterString(void);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedReportconfigSelectedmarkets();
	COleDateTime GetStartDate(void);
	COleDateTime GetEndDate(void);

//	CString GetDivisionsString();
//	CString GetMarketsString();
	CString GetMarketsDivisionsString();
	CString GetCRMarketsFilterString();
//	CString GetCRDivisionsFilterString();

	//CArray <int, int> m_aiMarkets;
	//CArray <int, int> m_aiDivisions;
	CArray <int, int> m_aiMarketsDivisions;
	CArray <SuMarketDivisionPair, SuMarketDivisionPair> m_asuMarketsDivisions;
	
	void InitFilterArrays(void);

	void ShowStartDate( bool bShow );
	void ShowEndDate( bool bShow );
	void ShowStartAndEndDate(bool bShow);

	void SetStartDateText( CString strText ) ;
	void SetEndDateText( CString strText ) ;
	
	CString m_strStartDateText;
	CString m_strEndDateText;
	
	CListBox m_listMarketDivision;

	afx_msg void OnBnClickedReportconfigAllmarketsanddivisions();
	afx_msg void OnBnClickedReportconfigSelectedmarketsanddivisions();

// Dialog Data
	enum { IDD = IDD_REPORT_CONFIG };

protected:
//	CString m_strDivisions;     // contains string of Divisions selected by user
//	CString m_strMarkets;		// contains string of Markets selected by user
	CString m_strMarketsDivisions; // contains string of Markets/Divisions selected by user
	CString m_strFilter;
	COleDateTime m_dateStart;
	COleDateTime m_dateEnd;

	CButton m_btnAllMarketsDivisions;
	CButton m_btnSelectedMarketsDivisions;
	
	CDateTimeCtrl m_dtpStartDate;
	CDateTimeCtrl m_dtpEndDate;

	CStatic m_stStartDate;
	CStatic m_stEndDate;

	CStatic m_stReportTitle;

	CString m_strCRDivisionsFilterString;
	CString m_strCRMarketsFilterString;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
	void PopulateMarketsAndDivisions();
	virtual void OnOK();
	void FormatFilterString();
	bool ValidateSelections();

//	bool InMarketArray(int iMarketID);
//	bool InDivisionArray(int iDivisionID);

	CString AddAllDivisions(int iMarketID);
	CString AddAllMarkets(int iDivisionID);
	CString AddAllMarketsAllDivisions();
	CString AddMarketDivision(int MarketID, int DivisionID);

	int RemoveDuplicatesFromFilterArray();

	

};

//inline CString CDlgReportConfig::GetDivisionsString()
//{
//	return m_strDivisions;
//}

//inline CString CDlgReportConfig::GetMarketsString()
//{
//	return m_strMarkets;
//}

inline CString CDlgReportConfig::GetMarketsDivisionsString()
{
	return m_strMarketsDivisions;
}

//inline CString CDlgReportConfig::GetCRDivisionsFilterString()
//{
//	return m_strCRDivisionsFilterString;
//}

inline CString CDlgReportConfig::GetCRMarketsFilterString()
{
	return m_strCRMarketsFilterString;
}

inline void CDlgReportConfig::ShowStartDate( bool bShow )
{
	m_bShowStartDate = bShow;
}

inline void CDlgReportConfig::ShowEndDate( bool bShow )
{
	m_bShowEndDate = bShow;
}

inline void CDlgReportConfig::ShowStartAndEndDate( bool bShow )
{
	ShowStartDate( bShow );
	ShowEndDate( bShow );
}

inline void CDlgReportConfig::SetStartDateText( CString strText )
{
	m_strStartDateText = strText;
}

inline void CDlgReportConfig::SetEndDateText( CString strText )
{
	m_strEndDateText = strText;
}
