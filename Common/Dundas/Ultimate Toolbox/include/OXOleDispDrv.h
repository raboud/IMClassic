// ==========================================================================
// 							Class Specification : COXOleDispatchDriver
// ==========================================================================

// Header file : OXOleDispDrv.h

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved
                         
// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	YES	Derived from COleDispatchDriver

//	NO	Is a Cwnd.                     
//	NO	Two stage creation (constructor & Create())
//	NO	Has a message map
//	NO	Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	YES Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Desciption :         
//		none

// Remark:
//		none

// Prerequisites (necessary conditions):
//		none

/////////////////////////////////////////////////////////////////////////////
#ifndef __OXOLEDISPDRV_H__
#define __OXOLEDISPDRV_H__


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"


class OX_CLASS_DECL COXOleDispatchDriver  : public COleDispatchDriver
{
// Data members -------------------------------------------------------------
public:             
	
protected:
	CMap<CString, LPCTSTR, DISPID, DISPID>
				m_mapNameToDISPID;
	
private:
	
// Member functions ---------------------------------------------------------
public:     
	// Construction
	
	COXOleDispatchDriver();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Default contructor (Before using this object,
	//				you should connect an IDispatch to it using either
	//				CreateDispatch or AttachDispatch.

	COXOleDispatchDriver(LPDISPATCH lpDispatch, BOOL bAutoRelease = TRUE);
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : contructs and connects the object with the IDispatch

	COXOleDispatchDriver(const COleDispatchDriver& dispatchSrc);
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Copy contructor

	
	virtual ~COXOleDispatchDriver();
	// --- In :	
	// --- Out : 
	// --- Returns :
	// --- Effect : Disconnects the IDispatch if necessary and destructs the object

	void AFX_CDECL InvokeMethod(LPCTSTR lpszName, VARTYPE vtRet, 
			void* pvRet, const BYTE* pbParamInfo, ...);
	// --- In :	
	// --- Out : 
	// --- Returns :
	// --- Effect : 

	void AFX_CDECL SetProperty(LPCTSTR lpszName, VARTYPE vtProp, ...);
	// --- In :	
	// --- Out : 
	// --- Returns :
	// --- Effect : 

	void GetProperty(LPCTSTR lpszName, VARTYPE vtProp, void* pvProp) const;
	// --- In :	
	// --- Out : 
	// --- Returns :
	// --- Effect : 


	// The redefinition of these existing functions makes them overloadable
	void AFX_CDECL SetProperty(DISPID dwDispID, VARTYPE vtProp, ...);
	void GetProperty(DISPID dwDispID, VARTYPE vtProp, void* pvProp) const;

		
protected:      
	void ConvertToDISPID(CString sDispName, DISPID& dwDispID);
	void SetPropertyHelper(DISPID dwDispID, VARTYPE vtProp, va_list argList);

private:
                   
};

#endif //__OXOLEDISPDRV_H__
