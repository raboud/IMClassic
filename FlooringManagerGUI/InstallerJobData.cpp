/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#include "StdAfx.h"

#include <afxinet.h>
#include ".\installerjobdata.h"
#include "SetSettings.h"

extern CDatabase g_dbFlooring;

CInstallerJobData::CCalculation::CCalculation()
: m_strTimeStamp("")
,   m_strAssigned("")
{
}

CInstallerJobData::CCalculation::~CCalculation()
{
	while(m_LineItemList.GetCount())
	{
		CLineItem* pLine = m_LineItemList.GetTail() ;
		delete pLine ;
		m_LineItemList.RemoveTail() ;
	}
}

CInstallerJobData::CInstallerJobData(CString strStoreNumber, CString strInstallPO, CString strInstallOrderNumber, CString strMeasureNumber)
: m_bOpened(false)
, m_strXML(_T(""))
, m_iResultCode(0)
, m_strResultDescr(_T(""))
{
	if (Open(strStoreNumber, strInstallPO, strInstallOrderNumber.Trim(), strMeasureNumber))
	{
		m_bOpened = ParseXml() ;
	}
}

CInstallerJobData::~CInstallerJobData()
{
	while(m_CalcList.GetCount())
	{
		CCalculation* pCalc = m_CalcList.GetTail() ;
		delete pCalc ;
		m_CalcList.RemoveTail() ;
	}
}

bool CInstallerJobData::Open(CString strStoreNumber, CString strInstallPO, CString strInstallOrderNumber, CString strMeasureNumber)
{
	bool bStatus = false ;
	CString strParams ;
	CString strName ;
	CSetSettings setSettings;
	CString strDrawingsFolder = setSettings.GetSetting("DrawingsFolder");
	strName.Format(strDrawingsFolder + "%s-%s-%s-%s.xml", strStoreNumber, strInstallPO, strInstallOrderNumber, strMeasureNumber) ;

	strParams.Format("scripts/installercomm.exe/GetJobData?UserID=st50032587&Password=50032587&StoreNumber=%s&InstallPO=%s&InstallOrderNumber=%s&MeasureNumber=%s", strStoreNumber, strInstallPO, strInstallOrderNumber, strMeasureNumber) ;
	CInternetSession session("Get Data") ;
	CHttpConnection *pServer = NULL ;
	CHttpFile *pFile = NULL ;

	try
	{
		pServer = session.GetHttpConnection("www.measurecomp.com") ;
		pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_GET, strParams) ;
		pFile->SendRequest() ;
		DWORD dwRet ;
		pFile->QueryInfoStatusCode(dwRet) ;
		if (dwRet == HTTP_STATUS_OK)
		{
			CString strData ;
			while (pFile->ReadString(strData))
			{
				m_strXML += strData ;
			}
			CStdioFile fileXml ;
			CFileException fe;
			if (fileXml.Open(strName, CFile::modeCreate | CFile::modeWrite | CFile::typeText, &fe))
			{
				fileXml.WriteString(m_strXML) ;
				fileXml.Close() ;
				bStatus = true ;
			}
			else
			{
				MessageBox(NULL, "The downloaded data could not be saved.", "Error!", MB_OK);
			}
		}
	}
	catch (CInternetException *pEx)
	{
		char acError[1000] ;
		pEx->GetErrorMessage(acError, sizeof(acError)) ;
		pEx->Delete() ;
	}
	pFile->Close() ;
	delete pFile ;
	pServer->Close() ;
	delete pServer ;
	session.Close() ;

	return bStatus;
}

// Parses the XML returned from measure comp
bool CInstallerJobData::ParseXml(void)
{
	bool bStatus = false ;

	MSXML2::IXMLDOMDocument *pXMLDom=NULL;
	if (CreateDOM(&pXMLDom))
	{
		if (ParseInstallerJobData(pXMLDom))
		{
			bStatus = true ;
		}
	}

	return bStatus;
}

bool CInstallerJobData::CreateDOM(MSXML2::IXMLDOMDocument **pXMLDom)
{
	bool bStatus = false;
	HRESULT hr ;
	hr = CoCreateInstance(__uuidof(MSXML2::DOMDocument40),
                    NULL,
                    CLSCTX_INPROC_SERVER,
					__uuidof(MSXML2::IXMLDOMDocument),
                    (void**) pXMLDom);

	if (hr == S_OK)
	{
		VARIANT_BOOL        vtIsSuccessful = FALSE;
		if (hr == S_OK) hr = (*pXMLDom)->loadXML(T2BSTR(m_strXML), &vtIsSuccessful);
		if (hr == S_OK) bStatus = (vtIsSuccessful != FALSE) ;
	}
	return (bStatus) ;
}

bool CInstallerJobData::ParseInstallerJobData(MSXML2::IXMLDOMDocument *pXMLDom)
{
	bool bStatus = false ;
	HRESULT hr ;
	MSXML2::IXMLDOMNode *pNode = NULL ;
	MSXML2::IXMLDOMNamedNodeMap *pAttribs = NULL;

	hr = pXMLDom->selectSingleNode(CComBSTR("InstallerJobData"), &pNode) ;
	if ((hr == S_OK) && (pNode != NULL)) hr = pNode->get_attributes(&pAttribs) ;

	VARIANT vt ;
	MSXML2::IXMLDOMNode *pAttrib=NULL;

	// get ResultCode and convert to int
	if ((hr == S_OK) && (pAttribs != NULL)) hr = pAttribs->getNamedItem(CComBSTR("ResultCode"), &pAttrib) ;
	if ((hr == S_OK) && (pAttrib != NULL))
	{
		hr = pAttrib->get_nodeValue(&vt) ;
		if (hr == S_OK)
		{
			CComVariant vt2(vt) ;
			vt2.ChangeType(VT_INT) ; 
			m_iResultCode = vt2.iVal ;
		}
	}

	// get Restult description
	if ((hr == S_OK) && (pAttribs != NULL)) hr = pAttribs->getNamedItem(CComBSTR("ResultDescription"), &pAttrib) ;
	if ((hr == S_OK) && (pAttrib != NULL))
	{
		hr = pAttrib->get_nodeValue(&vt) ;
		if (hr == S_OK)
		{
			m_strResultDescr = vt.bstrVal ;
		}
	}

	if (hr == S_OK) 
	{
		if (m_iResultCode == EnMCStatus_SUCCESS)
		{
			// good news so far everything is okay
			MSXML2::IXMLDOMNode *pJobNode=NULL;
			hr = pNode->selectSingleNode(CComBSTR("InstallerJob"), &pJobNode) ;
			if (hr == S_OK)
			{
				if (ParseInstallerJob(pJobNode))
				{
					bStatus = true ;
				}
			}
		}
	}

	return bStatus ;
}


bool CInstallerJobData::ParseInstallerJob(MSXML2::IXMLDOMNode *pJobNode)
{
	bool bStatus = false ;
	VARIANT vt ;

	VariantInit(&vt);	
	
	MSXML2::IXMLDOMNodeList *pCalcNodes=NULL;
	MSXML2::IXMLDOMNode *pCalcNode=NULL;

	HRESULT hr = pJobNode->selectNodes(CComBSTR("Calculation"), &pCalcNodes) ;

	long iCount ;
	pCalcNodes->get_length(&iCount) ;

	MSXML2::IXMLDOMNamedNodeMap *pAttribs ;
	MSXML2::IXMLDOMNode *pAttrib=NULL;

	hr = pJobNode->get_attributes(&pAttribs) ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("MeasureNumber"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strMeasureNumber = vt.bstrVal ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("StoreNumber"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strStoreNumber = vt.bstrVal ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("MeasureOrderNumber"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strMeasureOrderNumber = vt.bstrVal ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("LastName"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strLastName = vt.bstrVal ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("FirstName"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strFirstName = vt.bstrVal ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("Address1"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strAddress1 = vt.bstrVal ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("Address2"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strAddress2 = vt.bstrVal ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("City"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strCity = vt.bstrVal ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("State"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strState = vt.bstrVal ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("Zip"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strZip = vt.bstrVal ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("HomePhone"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strHomePhone = vt.bstrVal ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("BusinessPhone"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strBusinessPhone = vt.bstrVal ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("CellPhone"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strCellPhone = vt.bstrVal ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("Pager"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strPager = vt.bstrVal ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("SalespersonName"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strSalespersonName = vt.bstrVal ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("CrossStreetDir1"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strCrossStreetDir1 = vt.bstrVal ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("CrossStreet1"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strCrossStreet1 = vt.bstrVal ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("CrossStreetDir2"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strCrossStreetDir2 = vt.bstrVal ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("CrossStreet2"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strCrossStreet2 = vt.bstrVal ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("MeasureOrderCreationDate"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strMeasureOrderCreationDate = vt.bstrVal ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("Heat"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strHeat = vt.bstrVal ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("Pets"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strPets = vt.bstrVal ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("Electricity"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strElectricity = vt.bstrVal ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("FurnitureMoving"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strFurnitureMoving = vt.bstrVal ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("NewPaint"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strNewPaint = vt.bstrVal ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("Removal"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strRemoval = vt.bstrVal ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("PavedDriveway"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strPavedDriveway = vt.bstrVal ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("Garage"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strGarage = vt.bstrVal ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("Elevator"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strElevator = vt.bstrVal ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("Disposal"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strDisposal = vt.bstrVal ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("Access"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strAccess = vt.bstrVal ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("SiteType"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strSiteType = vt.bstrVal ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("MetalColor"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strMetalColor = vt.bstrVal ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("Email"), &pAttrib) ;
	if (hr == S_OK && pAttrib != NULL) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK && pAttrib != NULL) this->m_strEmailAddress = vt.bstrVal ;

	if (hr == S_OK)
	{
		for (int i = 0; i < iCount; i++)
		{
			hr = pCalcNodes->nextNode(&pCalcNode) ;
			if (hr == S_OK) 
			{
				CCalculation* pCalcItem = new CCalculation() ;
				m_CalcList.AddTail(pCalcItem) ;

				if (pCalcItem->ParseCalculations(pCalcNode))
				{
					bStatus = true ;
				}
				else
				{
					bStatus = false ;
				}
			}
		}
	}

	return bStatus ;
}





bool CInstallerJobData::CCalculation::ParseCalculations(MSXML2::IXMLDOMNode *pCalcNode)
{
	bool bStatus = false ;
	HRESULT hr ;
	VARIANT vt ;

	VariantInit(&vt);

	vt.vt = VT_EMPTY ;

	MSXML2::IXMLDOMNamedNodeMap *pCalcAttribs ;
	MSXML2::IXMLDOMNode *pAttrib=NULL;

	hr = pCalcNode->get_attributes(&pCalcAttribs) ;

	if (hr == S_OK) hr = pCalcAttribs->getNamedItem(CComBSTR("CalcTimeStamp"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strTimeStamp = vt.bstrVal ;

	if (hr == S_OK) hr = pCalcAttribs->getNamedItem(CComBSTR("Assigned"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strAssigned = vt.bstrVal ;

	if (hr == S_OK) 
	{
		MSXML2::IXMLDOMNodeList *pLineItemNodes = NULL ;
		hr = pCalcNode->selectNodes(CComBSTR("LineItemListEntry"), &pLineItemNodes)  ;
		if (hr == S_OK)
		{
			long iCount ;
			pLineItemNodes->get_length(&iCount) ;
			for (int i = 0; i < iCount; i++)
			{
				MSXML2::IXMLDOMNode *pLineItemNode = NULL ;
				hr = pLineItemNodes->nextNode(&pLineItemNode) ;
				if (hr == S_OK) 
				{
					CLineItem* pLineItem = new CLineItem() ;
					m_LineItemList.AddTail(pLineItem) ;
					if (pLineItem->ParseLineItems(pLineItemNode))
					{
						bStatus = true ;
					}
					else
					{
						bStatus = false ;
						break ;
					}
				}
			}
		}

	}

	return bStatus ;
}
CInstallerJobData::CCalculation::CLineItem::CLineItem()
: m_strLineItemNumber("")
, m_strMaterialType("")
, m_strMaterialDescription("")
, m_strMaterialWidth("")
, m_strPatternMatch("")
, m_strMaterialAmount("")
{
}

CInstallerJobData::CCalculation::CLineItem::~CLineItem()
{
}

bool CInstallerJobData::CCalculation::CLineItem::ParseLineItems(MSXML2::IXMLDOMNode *pLintItem)
{
	bool bStatus = false ;
	HRESULT hr ;
	VARIANT vt ;

	VariantInit(&vt);

	vt.vt = VT_EMPTY ;

	MSXML2::IXMLDOMNamedNodeMap *pAttribs ;
	MSXML2::IXMLDOMNode *pAttrib=NULL;

	hr = pLintItem->get_attributes(&pAttribs) ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("LineItemNumber"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strLineItemNumber = vt.bstrVal ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("MaterialType"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strMaterialType = vt.bstrVal ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("MaterialDescription"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strMaterialDescription = vt.bstrVal ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("MaterialWidth"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strMaterialWidth = vt.bstrVal ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("PatternMatch"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strPatternMatch = vt.bstrVal ;

	if (hr == S_OK) hr = pAttribs->getNamedItem(CComBSTR("MaterialAmount"), &pAttrib) ;
	if (hr == S_OK) hr = pAttrib->get_nodeValue(&vt) ;
	if (hr == S_OK) m_strMaterialAmount = vt.bstrVal ;

	if (hr == S_OK) bStatus = true ;

	return bStatus ;
}

int CInstallerJobData::GetCalcList(CStringList& listCalcDates)
{
	int iNumCalcs = -1;
	if (m_bOpened)
	{
		iNumCalcs = 0;
		listCalcDates.RemoveAll() ;

		POSITION pos = m_CalcList.GetHeadPosition();
		while (pos != NULL) 
		{
            CCalculation* pCalc = m_CalcList.GetAt(pos) ;
			listCalcDates.AddTail(pCalc->m_strTimeStamp) ;
			iNumCalcs++;
			m_CalcList.GetNext(pos) ;
		}
	}
	return (iNumCalcs) ;
}

CString CInstallerJobData::FormatDrawingFilename(CString strStoreNumber, CString strInstallPO, CString strInstallOrderNumber, CString strMeasureNumber, COleDateTime CalcDate, int iLineNumber, int iStyle)
{
	CString strFileName;
	CString strCalcDate = CalcDate.Format("%m%d%Y%H%M");
	CSetSettings setSettings;
	CString strDrawingsFolder = setSettings.GetSetting("DrawingsFolder");
	strFileName.Format(strDrawingsFolder + "%s-%s-%s-%s-%s-%d-%d.pdf", strStoreNumber, strInstallPO, strInstallOrderNumber, strMeasureNumber, strCalcDate, iStyle, iLineNumber) ;

	return strFileName;
}

bool CInstallerJobData::GetDrawing(CString strStoreNumber, CString strInstallPO, CString strInstallOrderNumber, CString strMeasureNumber, COleDateTime CalcDate, int iLineNumber, int iStyle)
{
	return GetDrawing(false, strStoreNumber, strInstallPO, strInstallOrderNumber, strMeasureNumber, CalcDate, iLineNumber, iStyle);
}

bool CInstallerJobData::GetDrawing(bool bPrint, CString strStoreNumber, CString strInstallPO, CString strInstallOrderNumber, CString strMeasureNumber, COleDateTime CalcDate, int iLineNumber, int iStyle)
{
	bool bStatus = false ;
	CString strParams ;
	CString strPDF = "" ;

	CString strCalcDate = CalcDate.Format("%m%d%Y%H%M%S");
	//strCalcDate.Replace(":", "") ;
	//strCalcDate.Replace(" ", "") ;
	//strCalcDate.Replace("/", "") ;
	//strCalcDate = strCalcDate.Left(12) ;


	if (iLineNumber == 0)
	{
		strParams.Format("scripts/renderpdfsys.exe/InstallerGetPlan?UserID=st50032587&Password=50032587&StoreNumber=%s&InstallPO=%s&InstallOrderNumber=%s&MeasureNumber=%s&CalcDateTime=%s&Style=%d&ResetZero=0", strStoreNumber, strInstallPO, strInstallOrderNumber, strMeasureNumber, strCalcDate, iStyle) ;
	}
	else
	{
		strParams.Format("scripts/renderpdfsys.exe/InstallerGetPlan?UserID=st50032587&Password=50032587&StoreNumber=%s&InstallPO=%s&InstallOrderNumber=%s&MeasureNumber=%s&CalcDateTime=%s&Style=%d&Line=%d&ResetZero=0", strStoreNumber, strInstallPO, strInstallOrderNumber, strMeasureNumber, strCalcDate, iStyle, iLineNumber) ;
	}
	CInternetSession session("Get Data") ;
	CHttpConnection *pServer = NULL ;
	CHttpFile *pFile = NULL ;
	CString strFileName ;

	try
	{
		pServer = session.GetHttpConnection("www.measurecomp.com") ;
		pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_GET, strParams) ;
		pFile->SendRequest() ;
		DWORD dwRet ;
		pFile->QueryInfoStatusCode(dwRet) ;
		if (dwRet == HTTP_STATUS_OK)
		{
			CFile filePDF ;
			strFileName = FormatDrawingFilename(strStoreNumber, strInstallPO, strInstallOrderNumber, strMeasureNumber, CalcDate, iLineNumber, iStyle) ;
			filePDF.Open(strFileName, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary) ;

			unsigned char b[2000] ;
			UINT nCount = 0 ;
			while ((nCount = pFile->Read(&b, sizeof(b))) != 0)
			{
				filePDF.Write(&b, nCount) ;
			}
			filePDF.Close() ;
			bStatus = true ;
		}
	}
	catch (CInternetException *pEx)
	{
		char acError[1000] ;
		pEx->GetErrorMessage(acError, sizeof(acError)) ;
		pEx->Delete() ;
	}
	pFile->Close() ;
	delete pFile ;
	pServer->Close() ;
	delete pServer ;
	session.Close() ;

	if (bStatus && bPrint)
	{
		ShellExecute(NULL, "print", strFileName, NULL, NULL, SW_HIDE ) ;
	}

	return bStatus;
}

int CInstallerJobData::GetNumberLineItems(const CString& strCalcDate)
{
	int iNumLineItems = -1;
	POSITION pos = m_CalcList.GetHeadPosition();
	while (pos != NULL) 
	{
        CCalculation* pCalc = m_CalcList.GetAt(pos) ;
		if (pCalc->m_strTimeStamp == strCalcDate)
		{
			iNumLineItems = pCalc->m_LineItemList.GetCount();
			break;
		}
		m_CalcList.GetNext(pos) ;
	}

	return iNumLineItems;
}

//_LineItemList CInstallerJobData::GetLineItems(const CString& strCalcDate)
//{
//	_LineItemList lineItems;
//	
//
//	return lineItems;
//}
//bool CInstallerJobData::GetLineItem(const CString& strCalcDate, int LineItemIndex, int& LineItemNumber, CString& strMaterialType, CString& strMaterialDescription, CString& strMaterialWidth, CString& strPatternMatch, CString& strMaterialAmount)
//{
//	bool bOK = false;
//	int CurrentIndex = 0;
//
//	if (LineItemIndex < 0)
//	{
//		return false;
//	}
//
//	POSITION pos = m_CalcList.GetHeadPosition();
//	while (pos != NULL) 
//	{
//        CCalculation* pCalc = m_CalcList.GetAt(pos) ;
//		if (pCalc->m_strTimeStamp == strCalcDate)
//		{
//			POSITION pos2 = pCalc->m_LineItemList.GetHeadPosition();
//			if (LineItemIndex < pCalc->m_LineItemList.GetCount())
//			{
//				CCalculation::CLineItem* pLineItem = pCalc->m_LineItemList.GetAt(pos2);
//				for (int iIndex = 0; iIndex < LineItemIndex; iIndex++)
//				{
//					pCalc->m_LineItemList.GetNext(pos2);
//				}
//
//				int CurLineItem = atoi(pLineItem->m_strLineItemNumber);
//				if (CurLineItem == LineItemNumber)
//				{
//					strMaterialType = pLineItem->m_strMaterialType;
//					strMaterialDescription = pLineItem->m_strMaterialDescription;
//					strMaterialWidth = pLineItem->m_strMaterialWidth;
//					strPatternMatch = pLineItem->m_strPatternMatch;
//					strMaterialAmount = pLineItem->m_strMaterialAmount;
//					bOK = true;
//					break;
//				}
//			}
//			else
//			{
//				// line item index bigger than number of line items!
//				return false;
//			}
//			break;
//		}
//		m_CalcList.GetNext(pos) ;
//	}
//
//	return bOK;
//}
