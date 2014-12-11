// ==========================================================================
// 							Class Implementation : COXOleDispatchDriver
// ==========================================================================

// Source file : OXOleDispDriver.cpp

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved
                          
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OXOleDispDrv.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif                                                                

#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////
// Definition of static members


// Data members -------------------------------------------------------------
// protected:
//	CTypedPtrMap<CMapStringToPtr, CString, DISPID>
//				m_mapNameToDISPID;

// private:
	
// Member functions ---------------------------------------------------------
// public:

COXOleDispatchDriver::COXOleDispatchDriver()
{                  
}  

COXOleDispatchDriver::COXOleDispatchDriver(LPDISPATCH lpDispatch, BOOL bAutoRelease) :
	COleDispatchDriver(lpDispatch, bAutoRelease)
{
}

COXOleDispatchDriver::COXOleDispatchDriver(const COleDispatchDriver& dispatchSrc) :
	COleDispatchDriver(dispatchSrc)
{
}
	
COXOleDispatchDriver::~COXOleDispatchDriver()
{
}

void AFX_CDECL COXOleDispatchDriver::InvokeMethod(LPCTSTR lpszName,
	VARTYPE vtRet, void* pvRet, const BYTE* pbParamInfo, ...)
{
	va_list argList;
	DISPID dwDispID;

	ConvertToDISPID(lpszName, dwDispID);
	va_start(argList, pbParamInfo);
	InvokeHelperV(dwDispID, DISPATCH_METHOD, vtRet, pvRet, pbParamInfo, argList);
	va_end(argList);

}

void AFX_CDECL COXOleDispatchDriver::SetProperty(LPCTSTR lpszName, VARTYPE vtProp, ...)
{
	va_list argList;    // really only one arg, but...
	DISPID dwDispID;

	ConvertToDISPID(lpszName, dwDispID);
	va_start(argList, vtProp);
	SetPropertyHelper(dwDispID, vtProp, argList);
	va_end(argList);
}

void COXOleDispatchDriver::GetProperty(LPCTSTR lpszName, VARTYPE vtProp, void* pvProp) const
{
	DISPID dwDispID;
	((COXOleDispatchDriver*)this)->ConvertToDISPID(lpszName, dwDispID);
	((COXOleDispatchDriver*)this)->InvokeHelper(dwDispID,
		DISPATCH_PROPERTYGET, vtProp, pvProp, NULL);
}

void AFX_CDECL COXOleDispatchDriver::SetProperty(DISPID dwDispID, VARTYPE vtProp, ...)
{
	va_list argList;
	va_start(argList, vtProp);
	SetPropertyHelper(dwDispID, vtProp, argList);
	va_end(argList);
}

void COXOleDispatchDriver::GetProperty(DISPID dwDispID, VARTYPE vtProp, void* pvProp) const
{
	((COleDispatchDriver*) this)->GetProperty(dwDispID, vtProp, pvProp);
}


// protected:

void COXOleDispatchDriver::ConvertToDISPID(CString sDispName, DISPID& dwDispID)
// --- In :	sDispName: the name of a method or property of the OLE object
// --- Out : dwDispID: the DISPID of the method or property
// --- Returns :
// --- Effect : converts the name of a method or property to a DISPID
{
	HRESULT	hr;
	BSTR	bstrDispName;

	if (m_mapNameToDISPID.Lookup(sDispName, dwDispID) == FALSE)
	{
		bstrDispName = sDispName.AllocSysString();
		hr = m_lpDispatch->GetIDsOfNames(IID_NULL, &bstrDispName, 1, LOCALE_SYSTEM_DEFAULT, &dwDispID);
		::SysFreeString(bstrDispName);
		if (hr!=S_OK)
		{
			TRACE1("The method or property '%s' is not supported by the OLE object !\n", sDispName);
			AfxThrowOleException(hr);
		}
		m_mapNameToDISPID.SetAt(sDispName, dwDispID);
	}
}

void COXOleDispatchDriver::SetPropertyHelper(DISPID dwDispID, VARTYPE vtProp, va_list argList)
// --- In :	dwDispID: the DISPID of the property
//			vtProp: the type of the property
//			argList: the new value for the property as a va_list with only one member
// --- Out : 
// --- Returns :
// --- Effect : Sets the new value for the property 
{
#ifdef _MAC
	argList -= 2;
#endif

	BYTE rgbParams[2];
	if (vtProp & VT_BYREF)
	{
		vtProp &= ~VT_BYREF;
		vtProp |= VT_MFCBYREF;
	}

#if !defined(_UNICODE) && !defined(OLE2ANSI)
		if (vtProp == VT_BSTR)
			vtProp = VT_BSTRA;
#endif

	rgbParams[0] = (BYTE)vtProp;
	rgbParams[1] = 0;
	WORD wFlags = (WORD)(vtProp == VT_DISPATCH ?
		DISPATCH_PROPERTYPUTREF : DISPATCH_PROPERTYPUT);
	InvokeHelperV(dwDispID, wFlags, VT_EMPTY, NULL, rgbParams, argList);
}
	

// private:

	
// ==========================================================================
