//
// sproxy.exe generated file
// do not modify this file
//
// Created: 03/01/2011@18:11:12
//

#pragma once


#if !defined(_WIN32_WINDOWS) && !defined(_WIN32_WINNT) && !defined(_WIN32_WCE)
#pragma message("warning: defining _WIN32_WINDOWS = 0x0410")
#define _WIN32_WINDOWS 0x0410
#endif

#include <atlsoap.h>
extern CString g_strSPNWebServiceURL;

namespace SPNService
{

template <typename TClient = CSoapSocketClientT<> >
class CSPNServiceT : 
	public TClient, 
	public CSoapRootHandler
{
protected:

	const _soapmap ** GetFunctionMap();
	const _soapmap ** GetHeaderMap();
	void * GetHeaderValue();
	const wchar_t * GetNamespaceUri();
	const char * GetServiceName();
	const char * GetNamespaceUriA();
	HRESULT CallFunction(
		void *pvParam, 
		const wchar_t *wszLocalName, int cchLocalName,
		size_t nItem);
	HRESULT GetClientReader(ISAXXMLReader **ppReader);

public:

	HRESULT __stdcall QueryInterface(REFIID riid, void **ppv)
	{
		if (ppv == NULL)
		{
			return E_POINTER;
		}

		*ppv = NULL;

		if (InlineIsEqualGUID(riid, IID_IUnknown) ||
			InlineIsEqualGUID(riid, IID_ISAXContentHandler))
		{
			*ppv = static_cast<ISAXContentHandler *>(this);
			return S_OK;
		}

		return E_NOINTERFACE;
	}

	ULONG __stdcall AddRef()
	{
		return 1;
	}

	ULONG __stdcall Release()
	{
		return 1;
	}

	CSPNServiceT(ISAXXMLReader *pReader = NULL)
		:TClient(_T(g_strSPNWebServiceURL))
	{
		SetClient(true);
		SetReader(pReader);
	}
	
	~CSPNServiceT()
	{
		Uninitialize();
	}
	
	void Uninitialize()
	{
		UninitializeSOAP();
	}	

	HRESULT ClosePO(
		BSTR ID, 
		BSTR StoreNumber, 
		BSTR PONumber, 
		bool* ClosePOResult
	);

	HRESULT SchedulePO(
		BSTR ID, 
		BSTR StoreNumber, 
		BSTR PONumber, 
		BSTR StartDate, 
		BSTR EndDate, 
		bool* SchedulePOResult
	);

	HRESULT SendNoteToStoreByNoteID(
		BSTR ID, 
		int NoteID, 
		bool CopyToSASM, 
		bool CopyToExpeditorEmail, 
		bool* SendNoteToStoreByNoteIDResult
	);

	HRESULT DownloadPO2(
		BSTR ID, 
		BSTR strStoreNumber, 
		BSTR strPoNumber, 
		bool* DownloadPO2Result
	);

	HRESULT GetPoPdf2(
		BSTR ID, 
		BSTR StoreNumber, 
		BSTR PONumber, 
		bool* GetPoPdf2Result, 
		BSTR* PDFFile
	);

	HRESULT SetSetting(
		BSTR ID, 
		BSTR Name, 
		BSTR Value, 
		bool* SetSettingResult
	);

	HRESULT GetPoPdf(
		BSTR strStoreNumber, 
		BSTR strPoNumber, 
		bool* GetPoPdfResult, 
		BSTR* strPdfFile
	);

	HRESULT DownloadPO(
		BSTR strStoreNumber, 
		BSTR strPoNumber, 
		bool* DownloadPOResult
	);

	HRESULT SendNoteToStoreByNoteID2(
		BSTR ID, 
		int NoteID, 
		bool CopyToSASM, 
		bool CopyToExpeditorEmail, 
		bool* SendNoteToStoreByNoteID2Result, 
		BSTR* Status
	);

	HRESULT GetSetting(
		BSTR ID, 
		BSTR Name, 
		BSTR DefaultValue, 
		BSTR* GetSettingResult
	);

	HRESULT SendNoteToStore(
		BSTR ID, 
		BSTR StoreNumber, 
		BSTR PONumber, 
		BSTR Note, 
		bool CopyToSASM, 
		bool CopyToExpeditorEmail, 
		bool* SendNoteToStoreResult
	);
};

typedef CSPNServiceT<> CSPNService;

struct __CSPNService_ClosePO_struct
{
	BSTR ID;
	BSTR StoreNumber;
	BSTR PONumber;
	bool ClosePOResult;
};

extern __declspec(selectany) const _soapmapentry __CSPNService_ClosePO_entries[] =
{

	{
		0x000009AD, 
		"ID", 
		L"ID", 
		sizeof("ID")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSPNService_ClosePO_struct, ID),
		NULL,
		NULL,
		-1,
	},
	{
		0xE64D5276, 
		"StoreNumber", 
		L"StoreNumber", 
		sizeof("StoreNumber")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSPNService_ClosePO_struct, StoreNumber),
		NULL,
		NULL,
		-1,
	},
	{
		0x54404D88, 
		"PONumber", 
		L"PONumber", 
		sizeof("PONumber")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSPNService_ClosePO_struct, PONumber),
		NULL,
		NULL,
		-1,
	},
	{
		0x620C4414, 
		"ClosePOResult", 
		L"ClosePOResult", 
		sizeof("ClosePOResult")-1, 
		SOAPTYPE_BOOLEAN, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSPNService_ClosePO_struct, ClosePOResult),
		NULL,
		NULL,
		-1,
	},
	{ 0x00000000 }
};

extern __declspec(selectany) const _soapmap __CSPNService_ClosePO_map =
{
	0x15D4B964,
	"ClosePO",
	L"ClosePOResponse",
	sizeof("ClosePO")-1,
	sizeof("ClosePOResponse")-1,
	SOAPMAP_FUNC,
	__CSPNService_ClosePO_entries,
	sizeof(__CSPNService_ClosePO_struct),
	1,
	-1,
	SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
	0xB6702561,
	"Jrs-Tech.net/SPNWebSerices",
	L"Jrs-Tech.net/SPNWebSerices",
	sizeof("Jrs-Tech.net/SPNWebSerices")-1
};


struct __CSPNService_SchedulePO_struct
{
	BSTR ID;
	BSTR StoreNumber;
	BSTR PONumber;
	BSTR StartDate;
	BSTR EndDate;
	bool SchedulePOResult;
};

extern __declspec(selectany) const _soapmapentry __CSPNService_SchedulePO_entries[] =
{

	{
		0x000009AD, 
		"ID", 
		L"ID", 
		sizeof("ID")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSPNService_SchedulePO_struct, ID),
		NULL,
		NULL,
		-1,
	},
	{
		0xE64D5276, 
		"StoreNumber", 
		L"StoreNumber", 
		sizeof("StoreNumber")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSPNService_SchedulePO_struct, StoreNumber),
		NULL,
		NULL,
		-1,
	},
	{
		0x54404D88, 
		"PONumber", 
		L"PONumber", 
		sizeof("PONumber")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSPNService_SchedulePO_struct, PONumber),
		NULL,
		NULL,
		-1,
	},
	{
		0x0F44464C, 
		"StartDate", 
		L"StartDate", 
		sizeof("StartDate")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSPNService_SchedulePO_struct, StartDate),
		NULL,
		NULL,
		-1,
	},
	{
		0xC7425D55, 
		"EndDate", 
		L"EndDate", 
		sizeof("EndDate")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSPNService_SchedulePO_struct, EndDate),
		NULL,
		NULL,
		-1,
	},
	{
		0x94E506CB, 
		"SchedulePOResult", 
		L"SchedulePOResult", 
		sizeof("SchedulePOResult")-1, 
		SOAPTYPE_BOOLEAN, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSPNService_SchedulePO_struct, SchedulePOResult),
		NULL,
		NULL,
		-1,
	},
	{ 0x00000000 }
};

extern __declspec(selectany) const _soapmap __CSPNService_SchedulePO_map =
{
	0x61E905DB,
	"SchedulePO",
	L"SchedulePOResponse",
	sizeof("SchedulePO")-1,
	sizeof("SchedulePOResponse")-1,
	SOAPMAP_FUNC,
	__CSPNService_SchedulePO_entries,
	sizeof(__CSPNService_SchedulePO_struct),
	1,
	-1,
	SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
	0xB6702561,
	"Jrs-Tech.net/SPNWebSerices",
	L"Jrs-Tech.net/SPNWebSerices",
	sizeof("Jrs-Tech.net/SPNWebSerices")-1
};


struct __CSPNService_SendNoteToStoreByNoteID_struct
{
	BSTR ID;
	int NoteID;
	bool CopyToSASM;
	bool CopyToExpeditorEmail;
	bool SendNoteToStoreByNoteIDResult;
};

extern __declspec(selectany) const _soapmapentry __CSPNService_SendNoteToStoreByNoteID_entries[] =
{

	{
		0x000009AD, 
		"ID", 
		L"ID", 
		sizeof("ID")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSPNService_SendNoteToStoreByNoteID_struct, ID),
		NULL,
		NULL,
		-1,
	},
	{
		0xBE0C5443, 
		"NoteID", 
		L"NoteID", 
		sizeof("NoteID")-1, 
		SOAPTYPE_INT, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSPNService_SendNoteToStoreByNoteID_struct, NoteID),
		NULL,
		NULL,
		-1,
	},
	{
		0x1BC56C72, 
		"CopyToSASM", 
		L"CopyToSASM", 
		sizeof("CopyToSASM")-1, 
		SOAPTYPE_BOOLEAN, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSPNService_SendNoteToStoreByNoteID_struct, CopyToSASM),
		NULL,
		NULL,
		-1,
	},
	{
		0x8A79933A, 
		"CopyToExpeditorEmail", 
		L"CopyToExpeditorEmail", 
		sizeof("CopyToExpeditorEmail")-1, 
		SOAPTYPE_BOOLEAN, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSPNService_SendNoteToStoreByNoteID_struct, CopyToExpeditorEmail),
		NULL,
		NULL,
		-1,
	},
	{
		0x9E1FB20D, 
		"SendNoteToStoreByNoteIDResult", 
		L"SendNoteToStoreByNoteIDResult", 
		sizeof("SendNoteToStoreByNoteIDResult")-1, 
		SOAPTYPE_BOOLEAN, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSPNService_SendNoteToStoreByNoteID_struct, SendNoteToStoreByNoteIDResult),
		NULL,
		NULL,
		-1,
	},
	{ 0x00000000 }
};

extern __declspec(selectany) const _soapmap __CSPNService_SendNoteToStoreByNoteID_map =
{
	0xA47B899D,
	"SendNoteToStoreByNoteID",
	L"SendNoteToStoreByNoteIDResponse",
	sizeof("SendNoteToStoreByNoteID")-1,
	sizeof("SendNoteToStoreByNoteIDResponse")-1,
	SOAPMAP_FUNC,
	__CSPNService_SendNoteToStoreByNoteID_entries,
	sizeof(__CSPNService_SendNoteToStoreByNoteID_struct),
	1,
	-1,
	SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
	0xB6702561,
	"Jrs-Tech.net/SPNWebSerices",
	L"Jrs-Tech.net/SPNWebSerices",
	sizeof("Jrs-Tech.net/SPNWebSerices")-1
};


struct __CSPNService_DownloadPO2_struct
{
	BSTR ID;
	BSTR strStoreNumber;
	BSTR strPoNumber;
	bool DownloadPO2Result;
};

extern __declspec(selectany) const _soapmapentry __CSPNService_DownloadPO2_entries[] =
{

	{
		0x000009AD, 
		"ID", 
		L"ID", 
		sizeof("ID")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSPNService_DownloadPO2_struct, ID),
		NULL,
		NULL,
		-1,
	},
	{
		0x4797196F, 
		"strStoreNumber", 
		L"strStoreNumber", 
		sizeof("strStoreNumber")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSPNService_DownloadPO2_struct, strStoreNumber),
		NULL,
		NULL,
		-1,
	},
	{
		0x90616741, 
		"strPoNumber", 
		L"strPoNumber", 
		sizeof("strPoNumber")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSPNService_DownloadPO2_struct, strPoNumber),
		NULL,
		NULL,
		-1,
	},
	{
		0x9956B848, 
		"DownloadPO2Result", 
		L"DownloadPO2Result", 
		sizeof("DownloadPO2Result")-1, 
		SOAPTYPE_BOOLEAN, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSPNService_DownloadPO2_struct, DownloadPO2Result),
		NULL,
		NULL,
		-1,
	},
	{ 0x00000000 }
};

extern __declspec(selectany) const _soapmap __CSPNService_DownloadPO2_map =
{
	0x498D0A98,
	"DownloadPO2",
	L"DownloadPO2Response",
	sizeof("DownloadPO2")-1,
	sizeof("DownloadPO2Response")-1,
	SOAPMAP_FUNC,
	__CSPNService_DownloadPO2_entries,
	sizeof(__CSPNService_DownloadPO2_struct),
	1,
	-1,
	SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
	0xB6702561,
	"Jrs-Tech.net/SPNWebSerices",
	L"Jrs-Tech.net/SPNWebSerices",
	sizeof("Jrs-Tech.net/SPNWebSerices")-1
};


struct __CSPNService_GetPoPdf2_struct
{
	BSTR ID;
	BSTR StoreNumber;
	BSTR PONumber;
	bool GetPoPdf2Result;
	BSTR PDFFile;
};

extern __declspec(selectany) const _soapmapentry __CSPNService_GetPoPdf2_entries[] =
{

	{
		0x000009AD, 
		"ID", 
		L"ID", 
		sizeof("ID")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSPNService_GetPoPdf2_struct, ID),
		NULL,
		NULL,
		-1,
	},
	{
		0xE64D5276, 
		"StoreNumber", 
		L"StoreNumber", 
		sizeof("StoreNumber")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSPNService_GetPoPdf2_struct, StoreNumber),
		NULL,
		NULL,
		-1,
	},
	{
		0x54404D88, 
		"PONumber", 
		L"PONumber", 
		sizeof("PONumber")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSPNService_GetPoPdf2_struct, PONumber),
		NULL,
		NULL,
		-1,
	},
	{
		0x75262D2A, 
		"GetPoPdf2Result", 
		L"GetPoPdf2Result", 
		sizeof("GetPoPdf2Result")-1, 
		SOAPTYPE_BOOLEAN, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSPNService_GetPoPdf2_struct, GetPoPdf2Result),
		NULL,
		NULL,
		-1,
	},
	{
		0xB1ECA9DA, 
		"PDFFile", 
		L"PDFFile", 
		sizeof("PDFFile")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSPNService_GetPoPdf2_struct, PDFFile),
		NULL,
		NULL,
		-1,
	},
	{ 0x00000000 }
};

extern __declspec(selectany) const _soapmap __CSPNService_GetPoPdf2_map =
{
	0x570D3FFA,
	"GetPoPdf2",
	L"GetPoPdf2Response",
	sizeof("GetPoPdf2")-1,
	sizeof("GetPoPdf2Response")-1,
	SOAPMAP_FUNC,
	__CSPNService_GetPoPdf2_entries,
	sizeof(__CSPNService_GetPoPdf2_struct),
	2,
	-1,
	SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
	0xB6702561,
	"Jrs-Tech.net/SPNWebSerices",
	L"Jrs-Tech.net/SPNWebSerices",
	sizeof("Jrs-Tech.net/SPNWebSerices")-1
};


struct __CSPNService_SetSetting_struct
{
	BSTR ID;
	BSTR Name;
	BSTR Value;
	bool SetSettingResult;
};

extern __declspec(selectany) const _soapmapentry __CSPNService_SetSetting_entries[] =
{

	{
		0x000009AD, 
		"ID", 
		L"ID", 
		sizeof("ID")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSPNService_SetSetting_struct, ID),
		NULL,
		NULL,
		-1,
	},
	{
		0x002C70A1, 
		"Name", 
		L"Name", 
		sizeof("Name")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSPNService_SetSetting_struct, Name),
		NULL,
		NULL,
		-1,
	},
	{
		0x064B46FD, 
		"Value", 
		L"Value", 
		sizeof("Value")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSPNService_SetSetting_struct, Value),
		NULL,
		NULL,
		-1,
	},
	{
		0x92D18469, 
		"SetSettingResult", 
		L"SetSettingResult", 
		sizeof("SetSettingResult")-1, 
		SOAPTYPE_BOOLEAN, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSPNService_SetSetting_struct, SetSettingResult),
		NULL,
		NULL,
		-1,
	},
	{ 0x00000000 }
};

extern __declspec(selectany) const _soapmap __CSPNService_SetSetting_map =
{
	0x8CEB62F9,
	"SetSetting",
	L"SetSettingResponse",
	sizeof("SetSetting")-1,
	sizeof("SetSettingResponse")-1,
	SOAPMAP_FUNC,
	__CSPNService_SetSetting_entries,
	sizeof(__CSPNService_SetSetting_struct),
	1,
	-1,
	SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
	0xB6702561,
	"Jrs-Tech.net/SPNWebSerices",
	L"Jrs-Tech.net/SPNWebSerices",
	sizeof("Jrs-Tech.net/SPNWebSerices")-1
};


struct __CSPNService_GetPoPdf_struct
{
	BSTR strStoreNumber;
	BSTR strPoNumber;
	bool GetPoPdfResult;
	BSTR strPdfFile;
};

extern __declspec(selectany) const _soapmapentry __CSPNService_GetPoPdf_entries[] =
{

	{
		0x4797196F, 
		"strStoreNumber", 
		L"strStoreNumber", 
		sizeof("strStoreNumber")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSPNService_GetPoPdf_struct, strStoreNumber),
		NULL,
		NULL,
		-1,
	},
	{
		0x90616741, 
		"strPoNumber", 
		L"strPoNumber", 
		sizeof("strPoNumber")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSPNService_GetPoPdf_struct, strPoNumber),
		NULL,
		NULL,
		-1,
	},
	{
		0x7E1D0858, 
		"GetPoPdfResult", 
		L"GetPoPdfResult", 
		sizeof("GetPoPdfResult")-1, 
		SOAPTYPE_BOOLEAN, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSPNService_GetPoPdf_struct, GetPoPdfResult),
		NULL,
		NULL,
		-1,
	},
	{
		0xCD480093, 
		"strPdfFile", 
		L"strPdfFile", 
		sizeof("strPdfFile")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSPNService_GetPoPdf_struct, strPdfFile),
		NULL,
		NULL,
		-1,
	},
	{ 0x00000000 }
};

extern __declspec(selectany) const _soapmap __CSPNService_GetPoPdf_map =
{
	0x79279EA8,
	"GetPoPdf",
	L"GetPoPdfResponse",
	sizeof("GetPoPdf")-1,
	sizeof("GetPoPdfResponse")-1,
	SOAPMAP_FUNC,
	__CSPNService_GetPoPdf_entries,
	sizeof(__CSPNService_GetPoPdf_struct),
	2,
	-1,
	SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
	0xB6702561,
	"Jrs-Tech.net/SPNWebSerices",
	L"Jrs-Tech.net/SPNWebSerices",
	sizeof("Jrs-Tech.net/SPNWebSerices")-1
};


struct __CSPNService_DownloadPO_struct
{
	BSTR strStoreNumber;
	BSTR strPoNumber;
	bool DownloadPOResult;
};

extern __declspec(selectany) const _soapmapentry __CSPNService_DownloadPO_entries[] =
{

	{
		0x4797196F, 
		"strStoreNumber", 
		L"strStoreNumber", 
		sizeof("strStoreNumber")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSPNService_DownloadPO_struct, strStoreNumber),
		NULL,
		NULL,
		-1,
	},
	{
		0x90616741, 
		"strPoNumber", 
		L"strPoNumber", 
		sizeof("strPoNumber")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSPNService_DownloadPO_struct, strPoNumber),
		NULL,
		NULL,
		-1,
	},
	{
		0x8EB9A7B6, 
		"DownloadPOResult", 
		L"DownloadPOResult", 
		sizeof("DownloadPOResult")-1, 
		SOAPTYPE_BOOLEAN, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSPNService_DownloadPO_struct, DownloadPOResult),
		NULL,
		NULL,
		-1,
	},
	{ 0x00000000 }
};

extern __declspec(selectany) const _soapmap __CSPNService_DownloadPO_map =
{
	0x23698D86,
	"DownloadPO",
	L"DownloadPOResponse",
	sizeof("DownloadPO")-1,
	sizeof("DownloadPOResponse")-1,
	SOAPMAP_FUNC,
	__CSPNService_DownloadPO_entries,
	sizeof(__CSPNService_DownloadPO_struct),
	1,
	-1,
	SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
	0xB6702561,
	"Jrs-Tech.net/SPNWebSerices",
	L"Jrs-Tech.net/SPNWebSerices",
	sizeof("Jrs-Tech.net/SPNWebSerices")-1
};


struct __CSPNService_SendNoteToStoreByNoteID2_struct
{
	BSTR ID;
	int NoteID;
	bool CopyToSASM;
	bool CopyToExpeditorEmail;
	bool SendNoteToStoreByNoteID2Result;
	BSTR Status;
};

extern __declspec(selectany) const _soapmapentry __CSPNService_SendNoteToStoreByNoteID2_entries[] =
{

	{
		0x000009AD, 
		"ID", 
		L"ID", 
		sizeof("ID")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSPNService_SendNoteToStoreByNoteID2_struct, ID),
		NULL,
		NULL,
		-1,
	},
	{
		0xBE0C5443, 
		"NoteID", 
		L"NoteID", 
		sizeof("NoteID")-1, 
		SOAPTYPE_INT, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSPNService_SendNoteToStoreByNoteID2_struct, NoteID),
		NULL,
		NULL,
		-1,
	},
	{
		0x1BC56C72, 
		"CopyToSASM", 
		L"CopyToSASM", 
		sizeof("CopyToSASM")-1, 
		SOAPTYPE_BOOLEAN, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSPNService_SendNoteToStoreByNoteID2_struct, CopyToSASM),
		NULL,
		NULL,
		-1,
	},
	{
		0x8A79933A, 
		"CopyToExpeditorEmail", 
		L"CopyToExpeditorEmail", 
		sizeof("CopyToExpeditorEmail")-1, 
		SOAPTYPE_BOOLEAN, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSPNService_SendNoteToStoreByNoteID2_struct, CopyToExpeditorEmail),
		NULL,
		NULL,
		-1,
	},
	{
		0x957E0D7F, 
		"SendNoteToStoreByNoteID2Result", 
		L"SendNoteToStoreByNoteID2Result", 
		sizeof("SendNoteToStoreByNoteID2Result")-1, 
		SOAPTYPE_BOOLEAN, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSPNService_SendNoteToStoreByNoteID2_struct, SendNoteToStoreByNoteID2Result),
		NULL,
		NULL,
		-1,
	},
	{
		0xCA067464, 
		"Status", 
		L"Status", 
		sizeof("Status")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSPNService_SendNoteToStoreByNoteID2_struct, Status),
		NULL,
		NULL,
		-1,
	},
	{ 0x00000000 }
};

extern __declspec(selectany) const _soapmap __CSPNService_SendNoteToStoreByNoteID2_map =
{
	0xECDE898F,
	"SendNoteToStoreByNoteID2",
	L"SendNoteToStoreByNoteID2Response",
	sizeof("SendNoteToStoreByNoteID2")-1,
	sizeof("SendNoteToStoreByNoteID2Response")-1,
	SOAPMAP_FUNC,
	__CSPNService_SendNoteToStoreByNoteID2_entries,
	sizeof(__CSPNService_SendNoteToStoreByNoteID2_struct),
	2,
	-1,
	SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
	0xB6702561,
	"Jrs-Tech.net/SPNWebSerices",
	L"Jrs-Tech.net/SPNWebSerices",
	sizeof("Jrs-Tech.net/SPNWebSerices")-1
};


struct __CSPNService_GetSetting_struct
{
	BSTR ID;
	BSTR Name;
	BSTR DefaultValue;
	BSTR GetSettingResult;
};

extern __declspec(selectany) const _soapmapentry __CSPNService_GetSetting_entries[] =
{

	{
		0x000009AD, 
		"ID", 
		L"ID", 
		sizeof("ID")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSPNService_GetSetting_struct, ID),
		NULL,
		NULL,
		-1,
	},
	{
		0x002C70A1, 
		"Name", 
		L"Name", 
		sizeof("Name")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSPNService_GetSetting_struct, Name),
		NULL,
		NULL,
		-1,
	},
	{
		0xE61E9122, 
		"DefaultValue", 
		L"DefaultValue", 
		sizeof("DefaultValue")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSPNService_GetSetting_struct, DefaultValue),
		NULL,
		NULL,
		-1,
	},
	{
		0x0053BDDD, 
		"GetSettingResult", 
		L"GetSettingResult", 
		sizeof("GetSettingResult")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSPNService_GetSetting_struct, GetSettingResult),
		NULL,
		NULL,
		-1,
	},
	{ 0x00000000 }
};

extern __declspec(selectany) const _soapmap __CSPNService_GetSetting_map =
{
	0x63E1C96D,
	"GetSetting",
	L"GetSettingResponse",
	sizeof("GetSetting")-1,
	sizeof("GetSettingResponse")-1,
	SOAPMAP_FUNC,
	__CSPNService_GetSetting_entries,
	sizeof(__CSPNService_GetSetting_struct),
	1,
	-1,
	SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
	0xB6702561,
	"Jrs-Tech.net/SPNWebSerices",
	L"Jrs-Tech.net/SPNWebSerices",
	sizeof("Jrs-Tech.net/SPNWebSerices")-1
};


struct __CSPNService_SendNoteToStore_struct
{
	BSTR ID;
	BSTR StoreNumber;
	BSTR PONumber;
	BSTR Note;
	bool CopyToSASM;
	bool CopyToExpeditorEmail;
	bool SendNoteToStoreResult;
};

extern __declspec(selectany) const _soapmapentry __CSPNService_SendNoteToStore_entries[] =
{

	{
		0x000009AD, 
		"ID", 
		L"ID", 
		sizeof("ID")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSPNService_SendNoteToStore_struct, ID),
		NULL,
		NULL,
		-1,
	},
	{
		0xE64D5276, 
		"StoreNumber", 
		L"StoreNumber", 
		sizeof("StoreNumber")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSPNService_SendNoteToStore_struct, StoreNumber),
		NULL,
		NULL,
		-1,
	},
	{
		0x54404D88, 
		"PONumber", 
		L"PONumber", 
		sizeof("PONumber")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSPNService_SendNoteToStore_struct, PONumber),
		NULL,
		NULL,
		-1,
	},
	{
		0x002CAD16, 
		"Note", 
		L"Note", 
		sizeof("Note")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSPNService_SendNoteToStore_struct, Note),
		NULL,
		NULL,
		-1,
	},
	{
		0x1BC56C72, 
		"CopyToSASM", 
		L"CopyToSASM", 
		sizeof("CopyToSASM")-1, 
		SOAPTYPE_BOOLEAN, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSPNService_SendNoteToStore_struct, CopyToSASM),
		NULL,
		NULL,
		-1,
	},
	{
		0x8A79933A, 
		"CopyToExpeditorEmail", 
		L"CopyToExpeditorEmail", 
		sizeof("CopyToExpeditorEmail")-1, 
		SOAPTYPE_BOOLEAN, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSPNService_SendNoteToStore_struct, CopyToExpeditorEmail),
		NULL,
		NULL,
		-1,
	},
	{
		0x6A832E0F, 
		"SendNoteToStoreResult", 
		L"SendNoteToStoreResult", 
		sizeof("SendNoteToStoreResult")-1, 
		SOAPTYPE_BOOLEAN, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSPNService_SendNoteToStore_struct, SendNoteToStoreResult),
		NULL,
		NULL,
		-1,
	},
	{ 0x00000000 }
};

extern __declspec(selectany) const _soapmap __CSPNService_SendNoteToStore_map =
{
	0x17AE0E1F,
	"SendNoteToStore",
	L"SendNoteToStoreResponse",
	sizeof("SendNoteToStore")-1,
	sizeof("SendNoteToStoreResponse")-1,
	SOAPMAP_FUNC,
	__CSPNService_SendNoteToStore_entries,
	sizeof(__CSPNService_SendNoteToStore_struct),
	1,
	-1,
	SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
	0xB6702561,
	"Jrs-Tech.net/SPNWebSerices",
	L"Jrs-Tech.net/SPNWebSerices",
	sizeof("Jrs-Tech.net/SPNWebSerices")-1
};

extern __declspec(selectany) const _soapmap * __CSPNService_funcs[] =
{
	&__CSPNService_ClosePO_map,
	&__CSPNService_SchedulePO_map,
	&__CSPNService_SendNoteToStoreByNoteID_map,
	&__CSPNService_DownloadPO2_map,
	&__CSPNService_GetPoPdf2_map,
	&__CSPNService_SetSetting_map,
	&__CSPNService_GetPoPdf_map,
	&__CSPNService_DownloadPO_map,
	&__CSPNService_SendNoteToStoreByNoteID2_map,
	&__CSPNService_GetSetting_map,
	&__CSPNService_SendNoteToStore_map,
	NULL
};

template <typename TClient>
inline HRESULT CSPNServiceT<TClient>::ClosePO(
		BSTR ID, 
		BSTR StoreNumber, 
		BSTR PONumber, 
		bool* ClosePOResult
	)
{
    if ( ClosePOResult == NULL )
		return E_POINTER;

	HRESULT __atlsoap_hr = InitializeSOAP(NULL);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_INITIALIZE_ERROR);
		return __atlsoap_hr;
	}
	
	CleanupClient();

	CComPtr<IStream> __atlsoap_spReadStream;
	__CSPNService_ClosePO_struct __params;
	memset(&__params, 0x00, sizeof(__params));
	__params.ID = ID;
	__params.StoreNumber = StoreNumber;
	__params.PONumber = PONumber;

	__atlsoap_hr = SetClientStruct(&__params, 0);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_OUTOFMEMORY);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = GenerateResponse(GetWriteStream());
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_GENERATE_ERROR);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = SendRequest(_T("SOAPAction: \"Jrs-Tech.net/SPNWebSerices/ClosePO\"\r\n"));
	if (FAILED(__atlsoap_hr))
	{
		goto __skip_cleanup;
	}
	__atlsoap_hr = GetReadStream(&__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_READ_ERROR);
		goto __skip_cleanup;
	}
	
	// cleanup any in/out-params and out-headers from previous calls
	Cleanup();
	__atlsoap_hr = BeginParse(__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_PARSE_ERROR);
		goto __cleanup;
	}

	*ClosePOResult = __params.ClosePOResult;
	goto __skip_cleanup;
	
__cleanup:
	Cleanup();
__skip_cleanup:
	ResetClientState(true);
	memset(&__params, 0x00, sizeof(__params));
	return __atlsoap_hr;
}

template <typename TClient>
inline HRESULT CSPNServiceT<TClient>::SchedulePO(
		BSTR ID, 
		BSTR StoreNumber, 
		BSTR PONumber, 
		BSTR StartDate, 
		BSTR EndDate, 
		bool* SchedulePOResult
	)
{
    if ( SchedulePOResult == NULL )
		return E_POINTER;

	HRESULT __atlsoap_hr = InitializeSOAP(NULL);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_INITIALIZE_ERROR);
		return __atlsoap_hr;
	}
	
	CleanupClient();

	CComPtr<IStream> __atlsoap_spReadStream;
	__CSPNService_SchedulePO_struct __params;
	memset(&__params, 0x00, sizeof(__params));
	__params.ID = ID;
	__params.StoreNumber = StoreNumber;
	__params.PONumber = PONumber;
	__params.StartDate = StartDate;
	__params.EndDate = EndDate;

	__atlsoap_hr = SetClientStruct(&__params, 1);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_OUTOFMEMORY);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = GenerateResponse(GetWriteStream());
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_GENERATE_ERROR);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = SendRequest(_T("SOAPAction: \"Jrs-Tech.net/SPNWebSerices/SchedulePO\"\r\n"));
	if (FAILED(__atlsoap_hr))
	{
		goto __skip_cleanup;
	}
	__atlsoap_hr = GetReadStream(&__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_READ_ERROR);
		goto __skip_cleanup;
	}
	
	// cleanup any in/out-params and out-headers from previous calls
	Cleanup();
	__atlsoap_hr = BeginParse(__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_PARSE_ERROR);
		goto __cleanup;
	}

	*SchedulePOResult = __params.SchedulePOResult;
	goto __skip_cleanup;
	
__cleanup:
	Cleanup();
__skip_cleanup:
	ResetClientState(true);
	memset(&__params, 0x00, sizeof(__params));
	return __atlsoap_hr;
}

template <typename TClient>
inline HRESULT CSPNServiceT<TClient>::SendNoteToStoreByNoteID(
		BSTR ID, 
		int NoteID, 
		bool CopyToSASM, 
		bool CopyToExpeditorEmail, 
		bool* SendNoteToStoreByNoteIDResult
	)
{
    if ( SendNoteToStoreByNoteIDResult == NULL )
		return E_POINTER;

	HRESULT __atlsoap_hr = InitializeSOAP(NULL);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_INITIALIZE_ERROR);
		return __atlsoap_hr;
	}
	
	CleanupClient();

	CComPtr<IStream> __atlsoap_spReadStream;
	__CSPNService_SendNoteToStoreByNoteID_struct __params;
	memset(&__params, 0x00, sizeof(__params));
	__params.ID = ID;
	__params.NoteID = NoteID;
	__params.CopyToSASM = CopyToSASM;
	__params.CopyToExpeditorEmail = CopyToExpeditorEmail;

	__atlsoap_hr = SetClientStruct(&__params, 2);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_OUTOFMEMORY);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = GenerateResponse(GetWriteStream());
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_GENERATE_ERROR);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = SendRequest(_T("SOAPAction: \"Jrs-Tech.net/SPNWebSerices/SendNoteToStoreByNoteID\"\r\n"));
	if (FAILED(__atlsoap_hr))
	{
		goto __skip_cleanup;
	}
	__atlsoap_hr = GetReadStream(&__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_READ_ERROR);
		goto __skip_cleanup;
	}
	
	// cleanup any in/out-params and out-headers from previous calls
	Cleanup();
	__atlsoap_hr = BeginParse(__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_PARSE_ERROR);
		goto __cleanup;
	}

	*SendNoteToStoreByNoteIDResult = __params.SendNoteToStoreByNoteIDResult;
	goto __skip_cleanup;
	
__cleanup:
	Cleanup();
__skip_cleanup:
	ResetClientState(true);
	memset(&__params, 0x00, sizeof(__params));
	return __atlsoap_hr;
}

template <typename TClient>
inline HRESULT CSPNServiceT<TClient>::DownloadPO2(
		BSTR ID, 
		BSTR strStoreNumber, 
		BSTR strPoNumber, 
		bool* DownloadPO2Result
	)
{
    if ( DownloadPO2Result == NULL )
		return E_POINTER;

	HRESULT __atlsoap_hr = InitializeSOAP(NULL);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_INITIALIZE_ERROR);
		return __atlsoap_hr;
	}
	
	CleanupClient();

	CComPtr<IStream> __atlsoap_spReadStream;
	__CSPNService_DownloadPO2_struct __params;
	memset(&__params, 0x00, sizeof(__params));
	__params.ID = ID;
	__params.strStoreNumber = strStoreNumber;
	__params.strPoNumber = strPoNumber;

	__atlsoap_hr = SetClientStruct(&__params, 3);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_OUTOFMEMORY);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = GenerateResponse(GetWriteStream());
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_GENERATE_ERROR);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = SendRequest(_T("SOAPAction: \"Jrs-Tech.net/SPNWebSerices/DownloadPO2\"\r\n"));
	if (FAILED(__atlsoap_hr))
	{
		goto __skip_cleanup;
	}
	__atlsoap_hr = GetReadStream(&__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_READ_ERROR);
		goto __skip_cleanup;
	}
	
	// cleanup any in/out-params and out-headers from previous calls
	Cleanup();
	__atlsoap_hr = BeginParse(__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_PARSE_ERROR);
		goto __cleanup;
	}

	*DownloadPO2Result = __params.DownloadPO2Result;
	goto __skip_cleanup;
	
__cleanup:
	Cleanup();
__skip_cleanup:
	ResetClientState(true);
	memset(&__params, 0x00, sizeof(__params));
	return __atlsoap_hr;
}

template <typename TClient>
inline HRESULT CSPNServiceT<TClient>::GetPoPdf2(
		BSTR ID, 
		BSTR StoreNumber, 
		BSTR PONumber, 
		bool* GetPoPdf2Result, 
		BSTR* PDFFile
	)
{
    if ( GetPoPdf2Result == NULL )
		return E_POINTER;
    if ( PDFFile == NULL )
		return E_POINTER;

	HRESULT __atlsoap_hr = InitializeSOAP(NULL);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_INITIALIZE_ERROR);
		return __atlsoap_hr;
	}
	
	CleanupClient();

	CComPtr<IStream> __atlsoap_spReadStream;
	__CSPNService_GetPoPdf2_struct __params;
	memset(&__params, 0x00, sizeof(__params));
	__params.ID = ID;
	__params.StoreNumber = StoreNumber;
	__params.PONumber = PONumber;

	__atlsoap_hr = SetClientStruct(&__params, 4);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_OUTOFMEMORY);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = GenerateResponse(GetWriteStream());
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_GENERATE_ERROR);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = SendRequest(_T("SOAPAction: \"Jrs-Tech.net/SPNWebSerices/GetPoPdf2\"\r\n"));
	if (FAILED(__atlsoap_hr))
	{
		goto __skip_cleanup;
	}
	__atlsoap_hr = GetReadStream(&__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_READ_ERROR);
		goto __skip_cleanup;
	}
	
	// cleanup any in/out-params and out-headers from previous calls
	Cleanup();
	__atlsoap_hr = BeginParse(__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_PARSE_ERROR);
		goto __cleanup;
	}

	*GetPoPdf2Result = __params.GetPoPdf2Result;
	*PDFFile = __params.PDFFile;
	goto __skip_cleanup;
	
__cleanup:
	Cleanup();
__skip_cleanup:
	ResetClientState(true);
	memset(&__params, 0x00, sizeof(__params));
	return __atlsoap_hr;
}

template <typename TClient>
inline HRESULT CSPNServiceT<TClient>::SetSetting(
		BSTR ID, 
		BSTR Name, 
		BSTR Value, 
		bool* SetSettingResult
	)
{
    if ( SetSettingResult == NULL )
		return E_POINTER;

	HRESULT __atlsoap_hr = InitializeSOAP(NULL);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_INITIALIZE_ERROR);
		return __atlsoap_hr;
	}
	
	CleanupClient();

	CComPtr<IStream> __atlsoap_spReadStream;
	__CSPNService_SetSetting_struct __params;
	memset(&__params, 0x00, sizeof(__params));
	__params.ID = ID;
	__params.Name = Name;
	__params.Value = Value;

	__atlsoap_hr = SetClientStruct(&__params, 5);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_OUTOFMEMORY);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = GenerateResponse(GetWriteStream());
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_GENERATE_ERROR);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = SendRequest(_T("SOAPAction: \"Jrs-Tech.net/SPNWebSerices/SetSetting\"\r\n"));
	if (FAILED(__atlsoap_hr))
	{
		goto __skip_cleanup;
	}
	__atlsoap_hr = GetReadStream(&__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_READ_ERROR);
		goto __skip_cleanup;
	}
	
	// cleanup any in/out-params and out-headers from previous calls
	Cleanup();
	__atlsoap_hr = BeginParse(__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_PARSE_ERROR);
		goto __cleanup;
	}

	*SetSettingResult = __params.SetSettingResult;
	goto __skip_cleanup;
	
__cleanup:
	Cleanup();
__skip_cleanup:
	ResetClientState(true);
	memset(&__params, 0x00, sizeof(__params));
	return __atlsoap_hr;
}

template <typename TClient>
inline HRESULT CSPNServiceT<TClient>::GetPoPdf(
		BSTR strStoreNumber, 
		BSTR strPoNumber, 
		bool* GetPoPdfResult, 
		BSTR* strPdfFile
	)
{
    if ( GetPoPdfResult == NULL )
		return E_POINTER;
    if ( strPdfFile == NULL )
		return E_POINTER;

	HRESULT __atlsoap_hr = InitializeSOAP(NULL);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_INITIALIZE_ERROR);
		return __atlsoap_hr;
	}
	
	CleanupClient();

	CComPtr<IStream> __atlsoap_spReadStream;
	__CSPNService_GetPoPdf_struct __params;
	memset(&__params, 0x00, sizeof(__params));
	__params.strStoreNumber = strStoreNumber;
	__params.strPoNumber = strPoNumber;

	__atlsoap_hr = SetClientStruct(&__params, 6);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_OUTOFMEMORY);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = GenerateResponse(GetWriteStream());
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_GENERATE_ERROR);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = SendRequest(_T("SOAPAction: \"Jrs-Tech.net/SPNWebSerices/GetPoPdf\"\r\n"));
	if (FAILED(__atlsoap_hr))
	{
		goto __skip_cleanup;
	}
	__atlsoap_hr = GetReadStream(&__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_READ_ERROR);
		goto __skip_cleanup;
	}
	
	// cleanup any in/out-params and out-headers from previous calls
	Cleanup();
	__atlsoap_hr = BeginParse(__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_PARSE_ERROR);
		goto __cleanup;
	}

	*GetPoPdfResult = __params.GetPoPdfResult;
	*strPdfFile = __params.strPdfFile;
	goto __skip_cleanup;
	
__cleanup:
	Cleanup();
__skip_cleanup:
	ResetClientState(true);
	memset(&__params, 0x00, sizeof(__params));
	return __atlsoap_hr;
}

template <typename TClient>
inline HRESULT CSPNServiceT<TClient>::DownloadPO(
		BSTR strStoreNumber, 
		BSTR strPoNumber, 
		bool* DownloadPOResult
	)
{
    if ( DownloadPOResult == NULL )
		return E_POINTER;

	HRESULT __atlsoap_hr = InitializeSOAP(NULL);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_INITIALIZE_ERROR);
		return __atlsoap_hr;
	}
	
	CleanupClient();

	CComPtr<IStream> __atlsoap_spReadStream;
	__CSPNService_DownloadPO_struct __params;
	memset(&__params, 0x00, sizeof(__params));
	__params.strStoreNumber = strStoreNumber;
	__params.strPoNumber = strPoNumber;

	__atlsoap_hr = SetClientStruct(&__params, 7);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_OUTOFMEMORY);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = GenerateResponse(GetWriteStream());
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_GENERATE_ERROR);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = SendRequest(_T("SOAPAction: \"Jrs-Tech.net/SPNWebSerices/DownloadPO\"\r\n"));
	if (FAILED(__atlsoap_hr))
	{
		goto __skip_cleanup;
	}
	__atlsoap_hr = GetReadStream(&__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_READ_ERROR);
		goto __skip_cleanup;
	}
	
	// cleanup any in/out-params and out-headers from previous calls
	Cleanup();
	__atlsoap_hr = BeginParse(__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_PARSE_ERROR);
		goto __cleanup;
	}

	*DownloadPOResult = __params.DownloadPOResult;
	goto __skip_cleanup;
	
__cleanup:
	Cleanup();
__skip_cleanup:
	ResetClientState(true);
	memset(&__params, 0x00, sizeof(__params));
	return __atlsoap_hr;
}

template <typename TClient>
inline HRESULT CSPNServiceT<TClient>::SendNoteToStoreByNoteID2(
		BSTR ID, 
		int NoteID, 
		bool CopyToSASM, 
		bool CopyToExpeditorEmail, 
		bool* SendNoteToStoreByNoteID2Result, 
		BSTR* Status
	)
{
    if ( SendNoteToStoreByNoteID2Result == NULL )
		return E_POINTER;
    if ( Status == NULL )
		return E_POINTER;

	HRESULT __atlsoap_hr = InitializeSOAP(NULL);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_INITIALIZE_ERROR);
		return __atlsoap_hr;
	}
	
	CleanupClient();

	CComPtr<IStream> __atlsoap_spReadStream;
	__CSPNService_SendNoteToStoreByNoteID2_struct __params;
	memset(&__params, 0x00, sizeof(__params));
	__params.ID = ID;
	__params.NoteID = NoteID;
	__params.CopyToSASM = CopyToSASM;
	__params.CopyToExpeditorEmail = CopyToExpeditorEmail;

	__atlsoap_hr = SetClientStruct(&__params, 8);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_OUTOFMEMORY);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = GenerateResponse(GetWriteStream());
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_GENERATE_ERROR);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = SendRequest(_T("SOAPAction: \"Jrs-Tech.net/SPNWebSerices/SendNoteToStoreByNoteID2\"\r\n"));
	if (FAILED(__atlsoap_hr))
	{
		goto __skip_cleanup;
	}
	__atlsoap_hr = GetReadStream(&__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_READ_ERROR);
		goto __skip_cleanup;
	}
	
	// cleanup any in/out-params and out-headers from previous calls
	Cleanup();
	__atlsoap_hr = BeginParse(__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_PARSE_ERROR);
		goto __cleanup;
	}

	*SendNoteToStoreByNoteID2Result = __params.SendNoteToStoreByNoteID2Result;
	*Status = __params.Status;
	goto __skip_cleanup;
	
__cleanup:
	Cleanup();
__skip_cleanup:
	ResetClientState(true);
	memset(&__params, 0x00, sizeof(__params));
	return __atlsoap_hr;
}

template <typename TClient>
inline HRESULT CSPNServiceT<TClient>::GetSetting(
		BSTR ID, 
		BSTR Name, 
		BSTR DefaultValue, 
		BSTR* GetSettingResult
	)
{
    if ( GetSettingResult == NULL )
		return E_POINTER;

	HRESULT __atlsoap_hr = InitializeSOAP(NULL);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_INITIALIZE_ERROR);
		return __atlsoap_hr;
	}
	
	CleanupClient();

	CComPtr<IStream> __atlsoap_spReadStream;
	__CSPNService_GetSetting_struct __params;
	memset(&__params, 0x00, sizeof(__params));
	__params.ID = ID;
	__params.Name = Name;
	__params.DefaultValue = DefaultValue;

	__atlsoap_hr = SetClientStruct(&__params, 9);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_OUTOFMEMORY);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = GenerateResponse(GetWriteStream());
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_GENERATE_ERROR);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = SendRequest(_T("SOAPAction: \"Jrs-Tech.net/SPNWebSerices/GetSetting\"\r\n"));
	if (FAILED(__atlsoap_hr))
	{
		goto __skip_cleanup;
	}
	__atlsoap_hr = GetReadStream(&__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_READ_ERROR);
		goto __skip_cleanup;
	}
	
	// cleanup any in/out-params and out-headers from previous calls
	Cleanup();
	__atlsoap_hr = BeginParse(__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_PARSE_ERROR);
		goto __cleanup;
	}

	*GetSettingResult = __params.GetSettingResult;
	goto __skip_cleanup;
	
__cleanup:
	Cleanup();
__skip_cleanup:
	ResetClientState(true);
	memset(&__params, 0x00, sizeof(__params));
	return __atlsoap_hr;
}

template <typename TClient>
inline HRESULT CSPNServiceT<TClient>::SendNoteToStore(
		BSTR ID, 
		BSTR StoreNumber, 
		BSTR PONumber, 
		BSTR Note, 
		bool CopyToSASM, 
		bool CopyToExpeditorEmail, 
		bool* SendNoteToStoreResult
	)
{
    if ( SendNoteToStoreResult == NULL )
		return E_POINTER;

	HRESULT __atlsoap_hr = InitializeSOAP(NULL);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_INITIALIZE_ERROR);
		return __atlsoap_hr;
	}
	
	CleanupClient();

	CComPtr<IStream> __atlsoap_spReadStream;
	__CSPNService_SendNoteToStore_struct __params;
	memset(&__params, 0x00, sizeof(__params));
	__params.ID = ID;
	__params.StoreNumber = StoreNumber;
	__params.PONumber = PONumber;
	__params.Note = Note;
	__params.CopyToSASM = CopyToSASM;
	__params.CopyToExpeditorEmail = CopyToExpeditorEmail;

	__atlsoap_hr = SetClientStruct(&__params, 10);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_OUTOFMEMORY);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = GenerateResponse(GetWriteStream());
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_GENERATE_ERROR);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = SendRequest(_T("SOAPAction: \"Jrs-Tech.net/SPNWebSerices/SendNoteToStore\"\r\n"));
	if (FAILED(__atlsoap_hr))
	{
		goto __skip_cleanup;
	}
	__atlsoap_hr = GetReadStream(&__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_READ_ERROR);
		goto __skip_cleanup;
	}
	
	// cleanup any in/out-params and out-headers from previous calls
	Cleanup();
	__atlsoap_hr = BeginParse(__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_PARSE_ERROR);
		goto __cleanup;
	}

	*SendNoteToStoreResult = __params.SendNoteToStoreResult;
	goto __skip_cleanup;
	
__cleanup:
	Cleanup();
__skip_cleanup:
	ResetClientState(true);
	memset(&__params, 0x00, sizeof(__params));
	return __atlsoap_hr;
}

template <typename TClient>
ATL_NOINLINE inline const _soapmap ** CSPNServiceT<TClient>::GetFunctionMap()
{
	return __CSPNService_funcs;
}

template <typename TClient>
ATL_NOINLINE inline const _soapmap ** CSPNServiceT<TClient>::GetHeaderMap()
{
	static const _soapmapentry __CSPNService_ClosePO_atlsoapheader_entries[] =
	{
		{ 0x00000000 }
	};

	static const _soapmap __CSPNService_ClosePO_atlsoapheader_map = 
	{
		0x15D4B964,
		"ClosePO",
		L"ClosePOResponse",
		sizeof("ClosePO")-1,
		sizeof("ClosePOResponse")-1,
		SOAPMAP_HEADER,
		__CSPNService_ClosePO_atlsoapheader_entries,
		0,
		0,
		-1,
		SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		0xB6702561,
		"Jrs-Tech.net/SPNWebSerices",
		L"Jrs-Tech.net/SPNWebSerices",
		sizeof("Jrs-Tech.net/SPNWebSerices")-1
	};

	static const _soapmapentry __CSPNService_SchedulePO_atlsoapheader_entries[] =
	{
		{ 0x00000000 }
	};

	static const _soapmap __CSPNService_SchedulePO_atlsoapheader_map = 
	{
		0x61E905DB,
		"SchedulePO",
		L"SchedulePOResponse",
		sizeof("SchedulePO")-1,
		sizeof("SchedulePOResponse")-1,
		SOAPMAP_HEADER,
		__CSPNService_SchedulePO_atlsoapheader_entries,
		0,
		0,
		-1,
		SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		0xB6702561,
		"Jrs-Tech.net/SPNWebSerices",
		L"Jrs-Tech.net/SPNWebSerices",
		sizeof("Jrs-Tech.net/SPNWebSerices")-1
	};

	static const _soapmapentry __CSPNService_SendNoteToStoreByNoteID_atlsoapheader_entries[] =
	{
		{ 0x00000000 }
	};

	static const _soapmap __CSPNService_SendNoteToStoreByNoteID_atlsoapheader_map = 
	{
		0xA47B899D,
		"SendNoteToStoreByNoteID",
		L"SendNoteToStoreByNoteIDResponse",
		sizeof("SendNoteToStoreByNoteID")-1,
		sizeof("SendNoteToStoreByNoteIDResponse")-1,
		SOAPMAP_HEADER,
		__CSPNService_SendNoteToStoreByNoteID_atlsoapheader_entries,
		0,
		0,
		-1,
		SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		0xB6702561,
		"Jrs-Tech.net/SPNWebSerices",
		L"Jrs-Tech.net/SPNWebSerices",
		sizeof("Jrs-Tech.net/SPNWebSerices")-1
	};

	static const _soapmapentry __CSPNService_DownloadPO2_atlsoapheader_entries[] =
	{
		{ 0x00000000 }
	};

	static const _soapmap __CSPNService_DownloadPO2_atlsoapheader_map = 
	{
		0x498D0A98,
		"DownloadPO2",
		L"DownloadPO2Response",
		sizeof("DownloadPO2")-1,
		sizeof("DownloadPO2Response")-1,
		SOAPMAP_HEADER,
		__CSPNService_DownloadPO2_atlsoapheader_entries,
		0,
		0,
		-1,
		SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		0xB6702561,
		"Jrs-Tech.net/SPNWebSerices",
		L"Jrs-Tech.net/SPNWebSerices",
		sizeof("Jrs-Tech.net/SPNWebSerices")-1
	};

	static const _soapmapentry __CSPNService_GetPoPdf2_atlsoapheader_entries[] =
	{
		{ 0x00000000 }
	};

	static const _soapmap __CSPNService_GetPoPdf2_atlsoapheader_map = 
	{
		0x570D3FFA,
		"GetPoPdf2",
		L"GetPoPdf2Response",
		sizeof("GetPoPdf2")-1,
		sizeof("GetPoPdf2Response")-1,
		SOAPMAP_HEADER,
		__CSPNService_GetPoPdf2_atlsoapheader_entries,
		0,
		0,
		-1,
		SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		0xB6702561,
		"Jrs-Tech.net/SPNWebSerices",
		L"Jrs-Tech.net/SPNWebSerices",
		sizeof("Jrs-Tech.net/SPNWebSerices")-1
	};

	static const _soapmapentry __CSPNService_SetSetting_atlsoapheader_entries[] =
	{
		{ 0x00000000 }
	};

	static const _soapmap __CSPNService_SetSetting_atlsoapheader_map = 
	{
		0x8CEB62F9,
		"SetSetting",
		L"SetSettingResponse",
		sizeof("SetSetting")-1,
		sizeof("SetSettingResponse")-1,
		SOAPMAP_HEADER,
		__CSPNService_SetSetting_atlsoapheader_entries,
		0,
		0,
		-1,
		SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		0xB6702561,
		"Jrs-Tech.net/SPNWebSerices",
		L"Jrs-Tech.net/SPNWebSerices",
		sizeof("Jrs-Tech.net/SPNWebSerices")-1
	};

	static const _soapmapentry __CSPNService_GetPoPdf_atlsoapheader_entries[] =
	{
		{ 0x00000000 }
	};

	static const _soapmap __CSPNService_GetPoPdf_atlsoapheader_map = 
	{
		0x79279EA8,
		"GetPoPdf",
		L"GetPoPdfResponse",
		sizeof("GetPoPdf")-1,
		sizeof("GetPoPdfResponse")-1,
		SOAPMAP_HEADER,
		__CSPNService_GetPoPdf_atlsoapheader_entries,
		0,
		0,
		-1,
		SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		0xB6702561,
		"Jrs-Tech.net/SPNWebSerices",
		L"Jrs-Tech.net/SPNWebSerices",
		sizeof("Jrs-Tech.net/SPNWebSerices")-1
	};

	static const _soapmapentry __CSPNService_DownloadPO_atlsoapheader_entries[] =
	{
		{ 0x00000000 }
	};

	static const _soapmap __CSPNService_DownloadPO_atlsoapheader_map = 
	{
		0x23698D86,
		"DownloadPO",
		L"DownloadPOResponse",
		sizeof("DownloadPO")-1,
		sizeof("DownloadPOResponse")-1,
		SOAPMAP_HEADER,
		__CSPNService_DownloadPO_atlsoapheader_entries,
		0,
		0,
		-1,
		SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		0xB6702561,
		"Jrs-Tech.net/SPNWebSerices",
		L"Jrs-Tech.net/SPNWebSerices",
		sizeof("Jrs-Tech.net/SPNWebSerices")-1
	};

	static const _soapmapentry __CSPNService_SendNoteToStoreByNoteID2_atlsoapheader_entries[] =
	{
		{ 0x00000000 }
	};

	static const _soapmap __CSPNService_SendNoteToStoreByNoteID2_atlsoapheader_map = 
	{
		0xECDE898F,
		"SendNoteToStoreByNoteID2",
		L"SendNoteToStoreByNoteID2Response",
		sizeof("SendNoteToStoreByNoteID2")-1,
		sizeof("SendNoteToStoreByNoteID2Response")-1,
		SOAPMAP_HEADER,
		__CSPNService_SendNoteToStoreByNoteID2_atlsoapheader_entries,
		0,
		0,
		-1,
		SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		0xB6702561,
		"Jrs-Tech.net/SPNWebSerices",
		L"Jrs-Tech.net/SPNWebSerices",
		sizeof("Jrs-Tech.net/SPNWebSerices")-1
	};

	static const _soapmapentry __CSPNService_GetSetting_atlsoapheader_entries[] =
	{
		{ 0x00000000 }
	};

	static const _soapmap __CSPNService_GetSetting_atlsoapheader_map = 
	{
		0x63E1C96D,
		"GetSetting",
		L"GetSettingResponse",
		sizeof("GetSetting")-1,
		sizeof("GetSettingResponse")-1,
		SOAPMAP_HEADER,
		__CSPNService_GetSetting_atlsoapheader_entries,
		0,
		0,
		-1,
		SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		0xB6702561,
		"Jrs-Tech.net/SPNWebSerices",
		L"Jrs-Tech.net/SPNWebSerices",
		sizeof("Jrs-Tech.net/SPNWebSerices")-1
	};

	static const _soapmapentry __CSPNService_SendNoteToStore_atlsoapheader_entries[] =
	{
		{ 0x00000000 }
	};

	static const _soapmap __CSPNService_SendNoteToStore_atlsoapheader_map = 
	{
		0x17AE0E1F,
		"SendNoteToStore",
		L"SendNoteToStoreResponse",
		sizeof("SendNoteToStore")-1,
		sizeof("SendNoteToStoreResponse")-1,
		SOAPMAP_HEADER,
		__CSPNService_SendNoteToStore_atlsoapheader_entries,
		0,
		0,
		-1,
		SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		0xB6702561,
		"Jrs-Tech.net/SPNWebSerices",
		L"Jrs-Tech.net/SPNWebSerices",
		sizeof("Jrs-Tech.net/SPNWebSerices")-1
	};


	static const _soapmap * __CSPNService_headers[] =
	{
		&__CSPNService_ClosePO_atlsoapheader_map,
		&__CSPNService_SchedulePO_atlsoapheader_map,
		&__CSPNService_SendNoteToStoreByNoteID_atlsoapheader_map,
		&__CSPNService_DownloadPO2_atlsoapheader_map,
		&__CSPNService_GetPoPdf2_atlsoapheader_map,
		&__CSPNService_SetSetting_atlsoapheader_map,
		&__CSPNService_GetPoPdf_atlsoapheader_map,
		&__CSPNService_DownloadPO_atlsoapheader_map,
		&__CSPNService_SendNoteToStoreByNoteID2_atlsoapheader_map,
		&__CSPNService_GetSetting_atlsoapheader_map,
		&__CSPNService_SendNoteToStore_atlsoapheader_map,
		NULL
	};
	
	return __CSPNService_headers;
}

template <typename TClient>
ATL_NOINLINE inline void * CSPNServiceT<TClient>::GetHeaderValue()
{
	return this;
}

template <typename TClient>
ATL_NOINLINE inline const wchar_t * CSPNServiceT<TClient>::GetNamespaceUri()
{
	return L"Jrs-Tech.net/SPNWebSerices";
}

template <typename TClient>
ATL_NOINLINE inline const char * CSPNServiceT<TClient>::GetServiceName()
{
	return NULL;
}

template <typename TClient>
ATL_NOINLINE inline const char * CSPNServiceT<TClient>::GetNamespaceUriA()
{
	return "Jrs-Tech.net/SPNWebSerices";
}

template <typename TClient>
ATL_NOINLINE inline HRESULT CSPNServiceT<TClient>::CallFunction(
	void *, 
	const wchar_t *, int,
	size_t)
{
	return E_NOTIMPL;
}

template <typename TClient>
ATL_NOINLINE inline HRESULT CSPNServiceT<TClient>::GetClientReader(ISAXXMLReader **ppReader)
{
	if (ppReader == NULL)
	{
		return E_INVALIDARG;
	}
	
	CComPtr<ISAXXMLReader> spReader = GetReader();
	if (spReader.p != NULL)
	{
		*ppReader = spReader.Detach();
		return S_OK;
	}
	return TClient::GetClientReader(ppReader);
}

} // namespace SPNService
