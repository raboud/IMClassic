/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once

#include <afxtempl.h>

#import <msxml4.dll> raw_interfaces_only rename("DOMDocument", "TempDOMDocument")

using namespace MSXML2;

enum EnMCStatus
{
	EnMCStatus_SUCCESS = 0,
	EnMCStatus_LOGIN_ERROR = -1,
	EnMCStatus_INTERNAL_DB_ERROR = -2,
	EnMCStatus_INCOMPLETE_INPUTS = -3,
	EnMCStatus_DATA_NOT_FOUND = -4
} ;



//typedef CList <CLineItem*, CLineItem*> _LineItemList ;



class CInstallerJobData
{
public:
	CInstallerJobData(CString strStoreNumber, CString strInstallPO, CString strInstallOrderNumber, CString strMeasureNumber) ;
	~CInstallerJobData();

	int GetCalcList(CStringList& listCalcDates) ;
	int GetNumberLineItems(const CString& strCalcDate);
	//bool GetLineItem(const CString& strCalcDate, int LineItemNumber, CString& strMaterialType, CString& strMaterialDescription, CString& strMaterialWidth, CString& strPatternMatch, CString& strMaterialAmount);
	//_LineItemList GetLineItems(const CString& strCalcDate);

	static bool GetDrawing(CString strStoreNumber, CString strInstallPO, CString strInstallOrderNumber, CString strMeasureNumber, COleDateTime CalcDate, int iLineNumber = 0, int iStyle = 1) ;
	static bool GetDrawing(bool bPrint, CString strStoreNumber, CString strInstallPO, CString strInstallOrderNumber, CString strMeasureNumber, COleDateTime CalcDate, int iLineNumber = 0, int iStyle = 1) ;
	static CString FormatDrawingFilename(CString strStoreNumber, CString strInstallPO, CString strInstallOrderNumber, CString strMeasureNumber, COleDateTime CalcDate, int iLineNumber = 0, int iStyle = 1) ;

	CString m_strMeasureNumber ;
	CString m_strStoreNumber ;
	CString m_strMeasureOrderNumber ;
	CString m_strLastName ;
	CString m_strFirstName ;
	CString m_strAddress1 ;
	CString m_strAddress2 ;
	CString m_strCity ;
	CString m_strState ;
	CString m_strZip ;
	CString m_strHomePhone ;
	CString m_strBusinessPhone ;
	CString m_strCellPhone ;
	CString m_strPager ;
	CString m_strSalespersonName ;
	CString m_strCrossStreetDir1 ;
	CString m_strCrossStreet1 ;
	CString m_strCrossStreetDir2 ;
	CString m_strCrossStreet2 ;
	CString m_strMeasureOrderCreationDate ;
	CString m_strHeat ;
	CString m_strPets ;
	CString m_strElectricity ;
	CString m_strFurnitureMoving ;
	CString m_strNewPaint ;
	CString m_strRemoval ;
	CString m_strPavedDriveway ;
	CString m_strGarage ;
	CString m_strElevator ;
	CString m_strDisposal ;
	CString m_strAccess ;
	CString m_strSiteType ;
	CString m_strMetalColor ;
	CString m_strEmailAddress ;

	class CCalculation
	{
	public:
		CCalculation() ;
		~CCalculation() ;

		bool ParseCalculations(MSXML2::IXMLDOMNode *pCalcNode) ;

		CString m_strTimeStamp ;
		CString m_strAssigned ;

		class CLineItem
		{
		public:
			CLineItem() ;
			~CLineItem() ;

			bool ParseLineItems(MSXML2::IXMLDOMNode *pLintItem) ;

			CString m_strLineItemNumber ;
			CString m_strMaterialType ;
			CString m_strMaterialDescription ;
			CString m_strMaterialWidth ;
			CString m_strPatternMatch ;
			CString m_strMaterialAmount ;
		} ;

		CList <CLineItem*, CLineItem*> m_LineItemList;
	} ;

	CList <CCalculation*, CCalculation*> m_CalcList;

protected:
	// METHODS
	bool Open(CString strStoreNumber, CString strInstallPO, CString strInstallOrderNumber, CString strMeasureNumber);

	// Parses the XML returned from measure comp
	bool ParseXml(void);

	bool CreateDOM(MSXML2::IXMLDOMDocument **pXMLDom);

	bool ParseInstallerJobData(MSXML2::IXMLDOMDocument *pXMLDom) ;
	bool ParseInstallerJob(MSXML2::IXMLDOMNode *pJobNode) ;

	// PROPERTIES:
	// measure exists and has been parsed
	bool m_bOpened;
	// The raw XML
	CString m_strXML;
	// Result code for MeasureComp
	int m_iResultCode;
	CString m_strResultDescr ;

	
	CString m_strTimeStamp ;
	CString m_strAssigned ;

};


