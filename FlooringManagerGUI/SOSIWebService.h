//
// sproxy.exe generated file
// do not modify this file
//
// Created: 05/30/2009@12:43:18
//

#pragma once


#if !defined(_WIN32_WINDOWS) && !defined(_WIN32_WINNT) && !defined(_WIN32_WCE)
#pragma message("warning: defining _WIN32_WINDOWS = 0x0410")
#define _WIN32_WINDOWS 0x0410
#endif

#include <atlsoap.h>

namespace SOSIService
{

template <typename TClient = CSoapSocketClientT<> >
class CSOSIServiceT : 
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

	CSOSIServiceT(ISAXXMLReader *pReader = NULL)
		:TClient(_T("http://localhost/SOSIWebService/SOSIWebService.asmx"))
	{
		SetClient(true);
		SetReader(pReader);
	}
	
	~CSOSIServiceT()
	{
		Uninitialize();
	}
	
	void Uninitialize()
	{
		UninitializeSOAP();
	}	

	HRESULT PrintPO(
		int OrderID, 
		bool* PrintPOResult, 
		BSTR* Message
	);

	HRESULT VerifyProductReceipt(
		int OrderSOMerchandiseID, 
		bool* VerifyProductReceiptResult, 
		BSTR* Message
	);

	HRESULT InstallScheduleUpdate(
		int OrderID, 
		BSTR ReasonCode, 
		bool* InstallScheduleUpdateResult, 
		BSTR* Message
	);

	HRESULT SendMeasureCapacity(
		bool* SendMeasureCapacityResult, 
		BSTR* Message
	);

	HRESULT ScheduleWillCall(
		int OrderID, 
		int WillCallLineNumber, 
		BSTR ScheduledPickUpDateTime, 
		BSTR ContactName, 
		bool* ScheduleWillCallResult, 
		BSTR* Message
	);

	HRESULT InstallNoteForExpeditor(
		int NoteID, 
		bool* InstallNoteForExpeditorResult, 
		BSTR* Message
	);

	HRESULT AssignReassignMeasureTechnician(
		int OrderID, 
		BSTR MeasureTechUserID, 
		bool* AssignReassignMeasureTechnicianResult, 
		BSTR* Message
	);

	HRESULT InstallServiceComplete(
		int OrderID, 
		bool* InstallServiceCompleteResult, 
		BSTR* Message
	);

	HRESULT ConfirmMeasurePOCancel(
		int OrderID, 
		bool* ConfirmMeasurePOCancelResult, 
		BSTR* Message
	);

	HRESULT MeasureApptCustomerCancellation(
		int OrderID, 
		BSTR ReasonCode, 
		bool* MeasureApptCustomerCancellationResult, 
		BSTR* Message
	);

	HRESULT ConfirmInstallPOCancel(
		int OrderID, 
		bool* ConfirmInstallPOCancelResult, 
		BSTR* Message
	);

	HRESULT MeasureApptRescheduleWithDate(
		int OrderID, 
		BSTR ReasonCode, 
		bool* MeasureApptRescheduleWithDateResult, 
		BSTR* Message
	);

	HRESULT ConfirmInstallPOChange(
		int OrderID, 
		bool* ConfirmInstallPOChangeResult, 
		BSTR* Message
	);

	HRESULT HelloWorld(
		BSTR* HelloWorldResult
	);

	HRESULT MeasureNoteForExpeditor(
		int NoteID, 
		bool* MeasureNoteForExpeditorResult, 
		BSTR* Message
	);
};

typedef CSOSIServiceT<> CSOSIService;

struct __CSOSIService_PrintPO_struct
{
	int OrderID;
	bool PrintPOResult;
	BSTR Message;
};

extern __declspec(selectany) const _soapmapentry __CSOSIService_PrintPO_entries[] =
{

	{
		0xD26FBA89, 
		"OrderID", 
		L"OrderID", 
		sizeof("OrderID")-1, 
		SOAPTYPE_INT, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSOSIService_PrintPO_struct, OrderID),
		NULL,
		NULL,
		-1,
	},
	{
		0x2E7D79CB, 
		"PrintPOResult", 
		L"PrintPOResult", 
		sizeof("PrintPOResult")-1, 
		SOAPTYPE_BOOLEAN, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSOSIService_PrintPO_struct, PrintPOResult),
		NULL,
		NULL,
		-1,
	},
	{
		0x1B3F0965, 
		"Message", 
		L"Message", 
		sizeof("Message")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSOSIService_PrintPO_struct, Message),
		NULL,
		NULL,
		-1,
	},
	{ 0x00000000 }
};

extern __declspec(selectany) const _soapmap __CSOSIService_PrintPO_map =
{
	0xC36A38DB,
	"PrintPO",
	L"PrintPOResponse",
	sizeof("PrintPO")-1,
	sizeof("PrintPOResponse")-1,
	SOAPMAP_FUNC,
	__CSOSIService_PrintPO_entries,
	sizeof(__CSOSIService_PrintPO_struct),
	2,
	-1,
	SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
	0x9177334C,
	"fusioncomp.com/SOSIWebService",
	L"fusioncomp.com/SOSIWebService",
	sizeof("fusioncomp.com/SOSIWebService")-1
};


struct __CSOSIService_VerifyProductReceipt_struct
{
	int OrderSOMerchandiseID;
	bool VerifyProductReceiptResult;
	BSTR Message;
};

extern __declspec(selectany) const _soapmapentry __CSOSIService_VerifyProductReceipt_entries[] =
{

	{
		0x59887DAE, 
		"OrderSOMerchandiseID", 
		L"OrderSOMerchandiseID", 
		sizeof("OrderSOMerchandiseID")-1, 
		SOAPTYPE_INT, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSOSIService_VerifyProductReceipt_struct, OrderSOMerchandiseID),
		NULL,
		NULL,
		-1,
	},
	{
		0x68981581, 
		"VerifyProductReceiptResult", 
		L"VerifyProductReceiptResult", 
		sizeof("VerifyProductReceiptResult")-1, 
		SOAPTYPE_BOOLEAN, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSOSIService_VerifyProductReceipt_struct, VerifyProductReceiptResult),
		NULL,
		NULL,
		-1,
	},
	{
		0x1B3F0965, 
		"Message", 
		L"Message", 
		sizeof("Message")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSOSIService_VerifyProductReceipt_struct, Message),
		NULL,
		NULL,
		-1,
	},
	{ 0x00000000 }
};

extern __declspec(selectany) const _soapmap __CSOSIService_VerifyProductReceipt_map =
{
	0xEE9A9A11,
	"VerifyProductReceipt",
	L"VerifyProductReceiptResponse",
	sizeof("VerifyProductReceipt")-1,
	sizeof("VerifyProductReceiptResponse")-1,
	SOAPMAP_FUNC,
	__CSOSIService_VerifyProductReceipt_entries,
	sizeof(__CSOSIService_VerifyProductReceipt_struct),
	2,
	-1,
	SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
	0x9177334C,
	"fusioncomp.com/SOSIWebService",
	L"fusioncomp.com/SOSIWebService",
	sizeof("fusioncomp.com/SOSIWebService")-1
};


struct __CSOSIService_InstallScheduleUpdate_struct
{
	int OrderID;
	BSTR ReasonCode;
	bool InstallScheduleUpdateResult;
	BSTR Message;
};

extern __declspec(selectany) const _soapmapentry __CSOSIService_InstallScheduleUpdate_entries[] =
{

	{
		0xD26FBA89, 
		"OrderID", 
		L"OrderID", 
		sizeof("OrderID")-1, 
		SOAPTYPE_INT, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSOSIService_InstallScheduleUpdate_struct, OrderID),
		NULL,
		NULL,
		-1,
	},
	{
		0x64AFCE03, 
		"ReasonCode", 
		L"ReasonCode", 
		sizeof("ReasonCode")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSOSIService_InstallScheduleUpdate_struct, ReasonCode),
		NULL,
		NULL,
		-1,
	},
	{
		0xC39DB006, 
		"InstallScheduleUpdateResult", 
		L"InstallScheduleUpdateResult", 
		sizeof("InstallScheduleUpdateResult")-1, 
		SOAPTYPE_BOOLEAN, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSOSIService_InstallScheduleUpdate_struct, InstallScheduleUpdateResult),
		NULL,
		NULL,
		-1,
	},
	{
		0x1B3F0965, 
		"Message", 
		L"Message", 
		sizeof("Message")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSOSIService_InstallScheduleUpdate_struct, Message),
		NULL,
		NULL,
		-1,
	},
	{ 0x00000000 }
};

extern __declspec(selectany) const _soapmap __CSOSIService_InstallScheduleUpdate_map =
{
	0x2170E9D6,
	"InstallScheduleUpdate",
	L"InstallScheduleUpdateResponse",
	sizeof("InstallScheduleUpdate")-1,
	sizeof("InstallScheduleUpdateResponse")-1,
	SOAPMAP_FUNC,
	__CSOSIService_InstallScheduleUpdate_entries,
	sizeof(__CSOSIService_InstallScheduleUpdate_struct),
	2,
	-1,
	SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
	0x9177334C,
	"fusioncomp.com/SOSIWebService",
	L"fusioncomp.com/SOSIWebService",
	sizeof("fusioncomp.com/SOSIWebService")-1
};


struct __CSOSIService_SendMeasureCapacity_struct
{
	bool SendMeasureCapacityResult;
	BSTR Message;
};

extern __declspec(selectany) const _soapmapentry __CSOSIService_SendMeasureCapacity_entries[] =
{

	{
		0x3124F7C9, 
		"SendMeasureCapacityResult", 
		L"SendMeasureCapacityResult", 
		sizeof("SendMeasureCapacityResult")-1, 
		SOAPTYPE_BOOLEAN, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSOSIService_SendMeasureCapacity_struct, SendMeasureCapacityResult),
		NULL,
		NULL,
		-1,
	},
	{
		0x1B3F0965, 
		"Message", 
		L"Message", 
		sizeof("Message")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSOSIService_SendMeasureCapacity_struct, Message),
		NULL,
		NULL,
		-1,
	},
	{ 0x00000000 }
};

extern __declspec(selectany) const _soapmap __CSOSIService_SendMeasureCapacity_map =
{
	0x0DE92E59,
	"SendMeasureCapacity",
	L"SendMeasureCapacityResponse",
	sizeof("SendMeasureCapacity")-1,
	sizeof("SendMeasureCapacityResponse")-1,
	SOAPMAP_FUNC,
	__CSOSIService_SendMeasureCapacity_entries,
	sizeof(__CSOSIService_SendMeasureCapacity_struct),
	2,
	-1,
	SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
	0x9177334C,
	"fusioncomp.com/SOSIWebService",
	L"fusioncomp.com/SOSIWebService",
	sizeof("fusioncomp.com/SOSIWebService")-1
};


struct __CSOSIService_ScheduleWillCall_struct
{
	int OrderID;
	int WillCallLineNumber;
	BSTR ScheduledPickUpDateTime;
	BSTR ContactName;
	bool ScheduleWillCallResult;
	BSTR Message;
};

extern __declspec(selectany) const _soapmapentry __CSOSIService_ScheduleWillCall_entries[] =
{

	{
		0xD26FBA89, 
		"OrderID", 
		L"OrderID", 
		sizeof("OrderID")-1, 
		SOAPTYPE_INT, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSOSIService_ScheduleWillCall_struct, OrderID),
		NULL,
		NULL,
		-1,
	},
	{
		0x47B10705, 
		"WillCallLineNumber", 
		L"WillCallLineNumber", 
		sizeof("WillCallLineNumber")-1, 
		SOAPTYPE_INT, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSOSIService_ScheduleWillCall_struct, WillCallLineNumber),
		NULL,
		NULL,
		-1,
	},
	{
		0x3B0B028A, 
		"ScheduledPickUpDateTime", 
		L"ScheduledPickUpDateTime", 
		sizeof("ScheduledPickUpDateTime")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSOSIService_ScheduleWillCall_struct, ScheduledPickUpDateTime),
		NULL,
		NULL,
		-1,
	},
	{
		0xDD44A82D, 
		"ContactName", 
		L"ContactName", 
		sizeof("ContactName")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSOSIService_ScheduleWillCall_struct, ContactName),
		NULL,
		NULL,
		-1,
	},
	{
		0xA44E7C00, 
		"ScheduleWillCallResult", 
		L"ScheduleWillCallResult", 
		sizeof("ScheduleWillCallResult")-1, 
		SOAPTYPE_BOOLEAN, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSOSIService_ScheduleWillCall_struct, ScheduleWillCallResult),
		NULL,
		NULL,
		-1,
	},
	{
		0x1B3F0965, 
		"Message", 
		L"Message", 
		sizeof("Message")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSOSIService_ScheduleWillCall_struct, Message),
		NULL,
		NULL,
		-1,
	},
	{ 0x00000000 }
};

extern __declspec(selectany) const _soapmap __CSOSIService_ScheduleWillCall_map =
{
	0xF1849C50,
	"ScheduleWillCall",
	L"ScheduleWillCallResponse",
	sizeof("ScheduleWillCall")-1,
	sizeof("ScheduleWillCallResponse")-1,
	SOAPMAP_FUNC,
	__CSOSIService_ScheduleWillCall_entries,
	sizeof(__CSOSIService_ScheduleWillCall_struct),
	2,
	-1,
	SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
	0x9177334C,
	"fusioncomp.com/SOSIWebService",
	L"fusioncomp.com/SOSIWebService",
	sizeof("fusioncomp.com/SOSIWebService")-1
};


struct __CSOSIService_InstallNoteForExpeditor_struct
{
	int NoteID;
	bool InstallNoteForExpeditorResult;
	BSTR Message;
};

extern __declspec(selectany) const _soapmapentry __CSOSIService_InstallNoteForExpeditor_entries[] =
{

	{
		0xBE0C5443, 
		"NoteID", 
		L"NoteID", 
		sizeof("NoteID")-1, 
		SOAPTYPE_INT, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSOSIService_InstallNoteForExpeditor_struct, NoteID),
		NULL,
		NULL,
		-1,
	},
	{
		0xAB3636C7, 
		"InstallNoteForExpeditorResult", 
		L"InstallNoteForExpeditorResult", 
		sizeof("InstallNoteForExpeditorResult")-1, 
		SOAPTYPE_BOOLEAN, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSOSIService_InstallNoteForExpeditor_struct, InstallNoteForExpeditorResult),
		NULL,
		NULL,
		-1,
	},
	{
		0x1B3F0965, 
		"Message", 
		L"Message", 
		sizeof("Message")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSOSIService_InstallNoteForExpeditor_struct, Message),
		NULL,
		NULL,
		-1,
	},
	{ 0x00000000 }
};

extern __declspec(selectany) const _soapmap __CSOSIService_InstallNoteForExpeditor_map =
{
	0x514624D7,
	"InstallNoteForExpeditor",
	L"InstallNoteForExpeditorResponse",
	sizeof("InstallNoteForExpeditor")-1,
	sizeof("InstallNoteForExpeditorResponse")-1,
	SOAPMAP_FUNC,
	__CSOSIService_InstallNoteForExpeditor_entries,
	sizeof(__CSOSIService_InstallNoteForExpeditor_struct),
	2,
	-1,
	SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
	0x9177334C,
	"fusioncomp.com/SOSIWebService",
	L"fusioncomp.com/SOSIWebService",
	sizeof("fusioncomp.com/SOSIWebService")-1
};


struct __CSOSIService_AssignReassignMeasureTechnician_struct
{
	int OrderID;
	BSTR MeasureTechUserID;
	bool AssignReassignMeasureTechnicianResult;
	BSTR Message;
};

extern __declspec(selectany) const _soapmapentry __CSOSIService_AssignReassignMeasureTechnician_entries[] =
{

	{
		0xD26FBA89, 
		"OrderID", 
		L"OrderID", 
		sizeof("OrderID")-1, 
		SOAPTYPE_INT, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSOSIService_AssignReassignMeasureTechnician_struct, OrderID),
		NULL,
		NULL,
		-1,
	},
	{
		0xE31CDB42, 
		"MeasureTechUserID", 
		L"MeasureTechUserID", 
		sizeof("MeasureTechUserID")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSOSIService_AssignReassignMeasureTechnician_struct, MeasureTechUserID),
		NULL,
		NULL,
		-1,
	},
	{
		0x5BD8A808, 
		"AssignReassignMeasureTechnicianResult", 
		L"AssignReassignMeasureTechnicianResult", 
		sizeof("AssignReassignMeasureTechnicianResult")-1, 
		SOAPTYPE_BOOLEAN, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSOSIService_AssignReassignMeasureTechnician_struct, AssignReassignMeasureTechnicianResult),
		NULL,
		NULL,
		-1,
	},
	{
		0x1B3F0965, 
		"Message", 
		L"Message", 
		sizeof("Message")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSOSIService_AssignReassignMeasureTechnician_struct, Message),
		NULL,
		NULL,
		-1,
	},
	{ 0x00000000 }
};

extern __declspec(selectany) const _soapmap __CSOSIService_AssignReassignMeasureTechnician_map =
{
	0xB449EA58,
	"AssignReassignMeasureTechnician",
	L"AssignReassignMeasureTechnicianResponse",
	sizeof("AssignReassignMeasureTechnician")-1,
	sizeof("AssignReassignMeasureTechnicianResponse")-1,
	SOAPMAP_FUNC,
	__CSOSIService_AssignReassignMeasureTechnician_entries,
	sizeof(__CSOSIService_AssignReassignMeasureTechnician_struct),
	2,
	-1,
	SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
	0x9177334C,
	"fusioncomp.com/SOSIWebService",
	L"fusioncomp.com/SOSIWebService",
	sizeof("fusioncomp.com/SOSIWebService")-1
};


struct __CSOSIService_InstallServiceComplete_struct
{
	int OrderID;
	bool InstallServiceCompleteResult;
	BSTR Message;
};

extern __declspec(selectany) const _soapmapentry __CSOSIService_InstallServiceComplete_entries[] =
{

	{
		0xD26FBA89, 
		"OrderID", 
		L"OrderID", 
		sizeof("OrderID")-1, 
		SOAPTYPE_INT, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSOSIService_InstallServiceComplete_struct, OrderID),
		NULL,
		NULL,
		-1,
	},
	{
		0xAC1811A0, 
		"InstallServiceCompleteResult", 
		L"InstallServiceCompleteResult", 
		sizeof("InstallServiceCompleteResult")-1, 
		SOAPTYPE_BOOLEAN, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSOSIService_InstallServiceComplete_struct, InstallServiceCompleteResult),
		NULL,
		NULL,
		-1,
	},
	{
		0x1B3F0965, 
		"Message", 
		L"Message", 
		sizeof("Message")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSOSIService_InstallServiceComplete_struct, Message),
		NULL,
		NULL,
		-1,
	},
	{ 0x00000000 }
};

extern __declspec(selectany) const _soapmap __CSOSIService_InstallServiceComplete_map =
{
	0x120A19F0,
	"InstallServiceComplete",
	L"InstallServiceCompleteResponse",
	sizeof("InstallServiceComplete")-1,
	sizeof("InstallServiceCompleteResponse")-1,
	SOAPMAP_FUNC,
	__CSOSIService_InstallServiceComplete_entries,
	sizeof(__CSOSIService_InstallServiceComplete_struct),
	2,
	-1,
	SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
	0x9177334C,
	"fusioncomp.com/SOSIWebService",
	L"fusioncomp.com/SOSIWebService",
	sizeof("fusioncomp.com/SOSIWebService")-1
};


struct __CSOSIService_ConfirmMeasurePOCancel_struct
{
	int OrderID;
	bool ConfirmMeasurePOCancelResult;
	BSTR Message;
};

extern __declspec(selectany) const _soapmapentry __CSOSIService_ConfirmMeasurePOCancel_entries[] =
{

	{
		0xD26FBA89, 
		"OrderID", 
		L"OrderID", 
		sizeof("OrderID")-1, 
		SOAPTYPE_INT, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSOSIService_ConfirmMeasurePOCancel_struct, OrderID),
		NULL,
		NULL,
		-1,
	},
	{
		0xC081DA44, 
		"ConfirmMeasurePOCancelResult", 
		L"ConfirmMeasurePOCancelResult", 
		sizeof("ConfirmMeasurePOCancelResult")-1, 
		SOAPTYPE_BOOLEAN, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSOSIService_ConfirmMeasurePOCancel_struct, ConfirmMeasurePOCancelResult),
		NULL,
		NULL,
		-1,
	},
	{
		0x1B3F0965, 
		"Message", 
		L"Message", 
		sizeof("Message")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSOSIService_ConfirmMeasurePOCancel_struct, Message),
		NULL,
		NULL,
		-1,
	},
	{ 0x00000000 }
};

extern __declspec(selectany) const _soapmap __CSOSIService_ConfirmMeasurePOCancel_map =
{
	0xE8089B94,
	"ConfirmMeasurePOCancel",
	L"ConfirmMeasurePOCancelResponse",
	sizeof("ConfirmMeasurePOCancel")-1,
	sizeof("ConfirmMeasurePOCancelResponse")-1,
	SOAPMAP_FUNC,
	__CSOSIService_ConfirmMeasurePOCancel_entries,
	sizeof(__CSOSIService_ConfirmMeasurePOCancel_struct),
	2,
	-1,
	SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
	0x9177334C,
	"fusioncomp.com/SOSIWebService",
	L"fusioncomp.com/SOSIWebService",
	sizeof("fusioncomp.com/SOSIWebService")-1
};


struct __CSOSIService_MeasureApptCustomerCancellation_struct
{
	int OrderID;
	BSTR ReasonCode;
	bool MeasureApptCustomerCancellationResult;
	BSTR Message;
};

extern __declspec(selectany) const _soapmapentry __CSOSIService_MeasureApptCustomerCancellation_entries[] =
{

	{
		0xD26FBA89, 
		"OrderID", 
		L"OrderID", 
		sizeof("OrderID")-1, 
		SOAPTYPE_INT, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSOSIService_MeasureApptCustomerCancellation_struct, OrderID),
		NULL,
		NULL,
		-1,
	},
	{
		0x64AFCE03, 
		"ReasonCode", 
		L"ReasonCode", 
		sizeof("ReasonCode")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSOSIService_MeasureApptCustomerCancellation_struct, ReasonCode),
		NULL,
		NULL,
		-1,
	},
	{
		0xA11481E5, 
		"MeasureApptCustomerCancellationResult", 
		L"MeasureApptCustomerCancellationResult", 
		sizeof("MeasureApptCustomerCancellationResult")-1, 
		SOAPTYPE_BOOLEAN, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSOSIService_MeasureApptCustomerCancellation_struct, MeasureApptCustomerCancellationResult),
		NULL,
		NULL,
		-1,
	},
	{
		0x1B3F0965, 
		"Message", 
		L"Message", 
		sizeof("Message")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSOSIService_MeasureApptCustomerCancellation_struct, Message),
		NULL,
		NULL,
		-1,
	},
	{ 0x00000000 }
};

extern __declspec(selectany) const _soapmap __CSOSIService_MeasureApptCustomerCancellation_map =
{
	0x37E3AF75,
	"MeasureApptCustomerCancellation",
	L"MeasureApptCustomerCancellationResponse",
	sizeof("MeasureApptCustomerCancellation")-1,
	sizeof("MeasureApptCustomerCancellationResponse")-1,
	SOAPMAP_FUNC,
	__CSOSIService_MeasureApptCustomerCancellation_entries,
	sizeof(__CSOSIService_MeasureApptCustomerCancellation_struct),
	2,
	-1,
	SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
	0x9177334C,
	"fusioncomp.com/SOSIWebService",
	L"fusioncomp.com/SOSIWebService",
	sizeof("fusioncomp.com/SOSIWebService")-1
};


struct __CSOSIService_ConfirmInstallPOCancel_struct
{
	int OrderID;
	bool ConfirmInstallPOCancelResult;
	BSTR Message;
};

extern __declspec(selectany) const _soapmapentry __CSOSIService_ConfirmInstallPOCancel_entries[] =
{

	{
		0xD26FBA89, 
		"OrderID", 
		L"OrderID", 
		sizeof("OrderID")-1, 
		SOAPTYPE_INT, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSOSIService_ConfirmInstallPOCancel_struct, OrderID),
		NULL,
		NULL,
		-1,
	},
	{
		0xBBCF5949, 
		"ConfirmInstallPOCancelResult", 
		L"ConfirmInstallPOCancelResult", 
		sizeof("ConfirmInstallPOCancelResult")-1, 
		SOAPTYPE_BOOLEAN, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSOSIService_ConfirmInstallPOCancel_struct, ConfirmInstallPOCancelResult),
		NULL,
		NULL,
		-1,
	},
	{
		0x1B3F0965, 
		"Message", 
		L"Message", 
		sizeof("Message")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSOSIService_ConfirmInstallPOCancel_struct, Message),
		NULL,
		NULL,
		-1,
	},
	{ 0x00000000 }
};

extern __declspec(selectany) const _soapmap __CSOSIService_ConfirmInstallPOCancel_map =
{
	0xECB1EFD9,
	"ConfirmInstallPOCancel",
	L"ConfirmInstallPOCancelResponse",
	sizeof("ConfirmInstallPOCancel")-1,
	sizeof("ConfirmInstallPOCancelResponse")-1,
	SOAPMAP_FUNC,
	__CSOSIService_ConfirmInstallPOCancel_entries,
	sizeof(__CSOSIService_ConfirmInstallPOCancel_struct),
	2,
	-1,
	SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
	0x9177334C,
	"fusioncomp.com/SOSIWebService",
	L"fusioncomp.com/SOSIWebService",
	sizeof("fusioncomp.com/SOSIWebService")-1
};


struct __CSOSIService_MeasureApptRescheduleWithDate_struct
{
	int OrderID;
	BSTR ReasonCode;
	bool MeasureApptRescheduleWithDateResult;
	BSTR Message;
};

extern __declspec(selectany) const _soapmapentry __CSOSIService_MeasureApptRescheduleWithDate_entries[] =
{

	{
		0xD26FBA89, 
		"OrderID", 
		L"OrderID", 
		sizeof("OrderID")-1, 
		SOAPTYPE_INT, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSOSIService_MeasureApptRescheduleWithDate_struct, OrderID),
		NULL,
		NULL,
		-1,
	},
	{
		0x64AFCE03, 
		"ReasonCode", 
		L"ReasonCode", 
		sizeof("ReasonCode")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSOSIService_MeasureApptRescheduleWithDate_struct, ReasonCode),
		NULL,
		NULL,
		-1,
	},
	{
		0xAB110004, 
		"MeasureApptRescheduleWithDateResult", 
		L"MeasureApptRescheduleWithDateResult", 
		sizeof("MeasureApptRescheduleWithDateResult")-1, 
		SOAPTYPE_BOOLEAN, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSOSIService_MeasureApptRescheduleWithDate_struct, MeasureApptRescheduleWithDateResult),
		NULL,
		NULL,
		-1,
	},
	{
		0x1B3F0965, 
		"Message", 
		L"Message", 
		sizeof("Message")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSOSIService_MeasureApptRescheduleWithDate_struct, Message),
		NULL,
		NULL,
		-1,
	},
	{ 0x00000000 }
};

extern __declspec(selectany) const _soapmap __CSOSIService_MeasureApptRescheduleWithDate_map =
{
	0xB2F83154,
	"MeasureApptRescheduleWithDate",
	L"MeasureApptRescheduleWithDateResponse",
	sizeof("MeasureApptRescheduleWithDate")-1,
	sizeof("MeasureApptRescheduleWithDateResponse")-1,
	SOAPMAP_FUNC,
	__CSOSIService_MeasureApptRescheduleWithDate_entries,
	sizeof(__CSOSIService_MeasureApptRescheduleWithDate_struct),
	2,
	-1,
	SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
	0x9177334C,
	"fusioncomp.com/SOSIWebService",
	L"fusioncomp.com/SOSIWebService",
	sizeof("fusioncomp.com/SOSIWebService")-1
};


struct __CSOSIService_ConfirmInstallPOChange_struct
{
	int OrderID;
	bool ConfirmInstallPOChangeResult;
	BSTR Message;
};

extern __declspec(selectany) const _soapmapentry __CSOSIService_ConfirmInstallPOChange_entries[] =
{

	{
		0xD26FBA89, 
		"OrderID", 
		L"OrderID", 
		sizeof("OrderID")-1, 
		SOAPTYPE_INT, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSOSIService_ConfirmInstallPOChange_struct, OrderID),
		NULL,
		NULL,
		-1,
	},
	{
		0xEBD3CAE9, 
		"ConfirmInstallPOChangeResult", 
		L"ConfirmInstallPOChangeResult", 
		sizeof("ConfirmInstallPOChangeResult")-1, 
		SOAPTYPE_BOOLEAN, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSOSIService_ConfirmInstallPOChange_struct, ConfirmInstallPOChangeResult),
		NULL,
		NULL,
		-1,
	},
	{
		0x1B3F0965, 
		"Message", 
		L"Message", 
		sizeof("Message")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSOSIService_ConfirmInstallPOChange_struct, Message),
		NULL,
		NULL,
		-1,
	},
	{ 0x00000000 }
};

extern __declspec(selectany) const _soapmap __CSOSIService_ConfirmInstallPOChange_map =
{
	0x2F994979,
	"ConfirmInstallPOChange",
	L"ConfirmInstallPOChangeResponse",
	sizeof("ConfirmInstallPOChange")-1,
	sizeof("ConfirmInstallPOChangeResponse")-1,
	SOAPMAP_FUNC,
	__CSOSIService_ConfirmInstallPOChange_entries,
	sizeof(__CSOSIService_ConfirmInstallPOChange_struct),
	2,
	-1,
	SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
	0x9177334C,
	"fusioncomp.com/SOSIWebService",
	L"fusioncomp.com/SOSIWebService",
	sizeof("fusioncomp.com/SOSIWebService")-1
};


struct __CSOSIService_HelloWorld_struct
{
	BSTR HelloWorldResult;
};

extern __declspec(selectany) const _soapmapentry __CSOSIService_HelloWorld_entries[] =
{

	{
		0x0588E51B, 
		"HelloWorldResult", 
		L"HelloWorldResult", 
		sizeof("HelloWorldResult")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSOSIService_HelloWorld_struct, HelloWorldResult),
		NULL,
		NULL,
		-1,
	},
	{ 0x00000000 }
};

extern __declspec(selectany) const _soapmap __CSOSIService_HelloWorld_map =
{
	0x8AFDB82B,
	"HelloWorld",
	L"HelloWorldResponse",
	sizeof("HelloWorld")-1,
	sizeof("HelloWorldResponse")-1,
	SOAPMAP_FUNC,
	__CSOSIService_HelloWorld_entries,
	sizeof(__CSOSIService_HelloWorld_struct),
	1,
	-1,
	SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
	0x9177334C,
	"fusioncomp.com/SOSIWebService",
	L"fusioncomp.com/SOSIWebService",
	sizeof("fusioncomp.com/SOSIWebService")-1
};


struct __CSOSIService_MeasureNoteForExpeditor_struct
{
	int NoteID;
	bool MeasureNoteForExpeditorResult;
	BSTR Message;
};

extern __declspec(selectany) const _soapmapentry __CSOSIService_MeasureNoteForExpeditor_entries[] =
{

	{
		0xBE0C5443, 
		"NoteID", 
		L"NoteID", 
		sizeof("NoteID")-1, 
		SOAPTYPE_INT, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSOSIService_MeasureNoteForExpeditor_struct, NoteID),
		NULL,
		NULL,
		-1,
	},
	{
		0xB06B82C2, 
		"MeasureNoteForExpeditorResult", 
		L"MeasureNoteForExpeditorResult", 
		sizeof("MeasureNoteForExpeditorResult")-1, 
		SOAPTYPE_BOOLEAN, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CSOSIService_MeasureNoteForExpeditor_struct, MeasureNoteForExpeditorResult),
		NULL,
		NULL,
		-1,
	},
	{
		0x1B3F0965, 
		"Message", 
		L"Message", 
		sizeof("Message")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CSOSIService_MeasureNoteForExpeditor_struct, Message),
		NULL,
		NULL,
		-1,
	},
	{ 0x00000000 }
};

extern __declspec(selectany) const _soapmap __CSOSIService_MeasureNoteForExpeditor_map =
{
	0x78FE5B92,
	"MeasureNoteForExpeditor",
	L"MeasureNoteForExpeditorResponse",
	sizeof("MeasureNoteForExpeditor")-1,
	sizeof("MeasureNoteForExpeditorResponse")-1,
	SOAPMAP_FUNC,
	__CSOSIService_MeasureNoteForExpeditor_entries,
	sizeof(__CSOSIService_MeasureNoteForExpeditor_struct),
	2,
	-1,
	SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
	0x9177334C,
	"fusioncomp.com/SOSIWebService",
	L"fusioncomp.com/SOSIWebService",
	sizeof("fusioncomp.com/SOSIWebService")-1
};

extern __declspec(selectany) const _soapmap * __CSOSIService_funcs[] =
{
	&__CSOSIService_PrintPO_map,
	&__CSOSIService_VerifyProductReceipt_map,
	&__CSOSIService_InstallScheduleUpdate_map,
	&__CSOSIService_SendMeasureCapacity_map,
	&__CSOSIService_ScheduleWillCall_map,
	&__CSOSIService_InstallNoteForExpeditor_map,
	&__CSOSIService_AssignReassignMeasureTechnician_map,
	&__CSOSIService_InstallServiceComplete_map,
	&__CSOSIService_ConfirmMeasurePOCancel_map,
	&__CSOSIService_MeasureApptCustomerCancellation_map,
	&__CSOSIService_ConfirmInstallPOCancel_map,
	&__CSOSIService_MeasureApptRescheduleWithDate_map,
	&__CSOSIService_ConfirmInstallPOChange_map,
	&__CSOSIService_HelloWorld_map,
	&__CSOSIService_MeasureNoteForExpeditor_map,
	NULL
};

template <typename TClient>
inline HRESULT CSOSIServiceT<TClient>::PrintPO(
		int OrderID, 
		bool* PrintPOResult, 
		BSTR* Message
	)
{
    if ( PrintPOResult == NULL )
		return E_POINTER;
    if ( Message == NULL )
		return E_POINTER;

	HRESULT __atlsoap_hr = InitializeSOAP(NULL);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_INITIALIZE_ERROR);
		return __atlsoap_hr;
	}
	
	CleanupClient();

	CComPtr<IStream> __atlsoap_spReadStream;
	__CSOSIService_PrintPO_struct __params;
	memset(&__params, 0x00, sizeof(__params));
	__params.OrderID = OrderID;

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
	
	__atlsoap_hr = SendRequest(_T("SOAPAction: \"fusioncomp.com/SOSIWebService/PrintPO\"\r\n"));
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

	*PrintPOResult = __params.PrintPOResult;
	*Message = __params.Message;
	goto __skip_cleanup;
	
__cleanup:
	Cleanup();
__skip_cleanup:
	ResetClientState(true);
	memset(&__params, 0x00, sizeof(__params));
	return __atlsoap_hr;
}

template <typename TClient>
inline HRESULT CSOSIServiceT<TClient>::VerifyProductReceipt(
		int OrderSOMerchandiseID, 
		bool* VerifyProductReceiptResult, 
		BSTR* Message
	)
{
    if ( VerifyProductReceiptResult == NULL )
		return E_POINTER;
    if ( Message == NULL )
		return E_POINTER;

	HRESULT __atlsoap_hr = InitializeSOAP(NULL);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_INITIALIZE_ERROR);
		return __atlsoap_hr;
	}
	
	CleanupClient();

	CComPtr<IStream> __atlsoap_spReadStream;
	__CSOSIService_VerifyProductReceipt_struct __params;
	memset(&__params, 0x00, sizeof(__params));
	__params.OrderSOMerchandiseID = OrderSOMerchandiseID;

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
	
	__atlsoap_hr = SendRequest(_T("SOAPAction: \"fusioncomp.com/SOSIWebService/VerifyProductReceipt\"\r\n"));
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

	*VerifyProductReceiptResult = __params.VerifyProductReceiptResult;
	*Message = __params.Message;
	goto __skip_cleanup;
	
__cleanup:
	Cleanup();
__skip_cleanup:
	ResetClientState(true);
	memset(&__params, 0x00, sizeof(__params));
	return __atlsoap_hr;
}

template <typename TClient>
inline HRESULT CSOSIServiceT<TClient>::InstallScheduleUpdate(
		int OrderID, 
		BSTR ReasonCode, 
		bool* InstallScheduleUpdateResult, 
		BSTR* Message
	)
{
    if ( InstallScheduleUpdateResult == NULL )
		return E_POINTER;
    if ( Message == NULL )
		return E_POINTER;

	HRESULT __atlsoap_hr = InitializeSOAP(NULL);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_INITIALIZE_ERROR);
		return __atlsoap_hr;
	}
	
	CleanupClient();

	CComPtr<IStream> __atlsoap_spReadStream;
	__CSOSIService_InstallScheduleUpdate_struct __params;
	memset(&__params, 0x00, sizeof(__params));
	__params.OrderID = OrderID;
	__params.ReasonCode = ReasonCode;

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
	
	__atlsoap_hr = SendRequest(_T("SOAPAction: \"fusioncomp.com/SOSIWebService/InstallScheduleUpdate\"\r\n"));
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

	*InstallScheduleUpdateResult = __params.InstallScheduleUpdateResult;
	*Message = __params.Message;
	goto __skip_cleanup;
	
__cleanup:
	Cleanup();
__skip_cleanup:
	ResetClientState(true);
	memset(&__params, 0x00, sizeof(__params));
	return __atlsoap_hr;
}

template <typename TClient>
inline HRESULT CSOSIServiceT<TClient>::SendMeasureCapacity(
		bool* SendMeasureCapacityResult, 
		BSTR* Message
	)
{
    if ( SendMeasureCapacityResult == NULL )
		return E_POINTER;
    if ( Message == NULL )
		return E_POINTER;

	HRESULT __atlsoap_hr = InitializeSOAP(NULL);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_INITIALIZE_ERROR);
		return __atlsoap_hr;
	}
	
	CleanupClient();

	CComPtr<IStream> __atlsoap_spReadStream;
	__CSOSIService_SendMeasureCapacity_struct __params;
	memset(&__params, 0x00, sizeof(__params));

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
	
	__atlsoap_hr = SendRequest(_T("SOAPAction: \"fusioncomp.com/SOSIWebService/SendMeasureCapacity\"\r\n"));
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

	*SendMeasureCapacityResult = __params.SendMeasureCapacityResult;
	*Message = __params.Message;
	goto __skip_cleanup;
	
__cleanup:
	Cleanup();
__skip_cleanup:
	ResetClientState(true);
	memset(&__params, 0x00, sizeof(__params));
	return __atlsoap_hr;
}

template <typename TClient>
inline HRESULT CSOSIServiceT<TClient>::ScheduleWillCall(
		int OrderID, 
		int WillCallLineNumber, 
		BSTR ScheduledPickUpDateTime, 
		BSTR ContactName, 
		bool* ScheduleWillCallResult, 
		BSTR* Message
	)
{
    if ( ScheduleWillCallResult == NULL )
		return E_POINTER;
    if ( Message == NULL )
		return E_POINTER;

	HRESULT __atlsoap_hr = InitializeSOAP(NULL);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_INITIALIZE_ERROR);
		return __atlsoap_hr;
	}
	
	CleanupClient();

	CComPtr<IStream> __atlsoap_spReadStream;
	__CSOSIService_ScheduleWillCall_struct __params;
	memset(&__params, 0x00, sizeof(__params));
	__params.OrderID = OrderID;
	__params.WillCallLineNumber = WillCallLineNumber;
	__params.ScheduledPickUpDateTime = ScheduledPickUpDateTime;
	__params.ContactName = ContactName;

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
	
	__atlsoap_hr = SendRequest(_T("SOAPAction: \"fusioncomp.com/SOSIWebService/ScheduleWillCall\"\r\n"));
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

	*ScheduleWillCallResult = __params.ScheduleWillCallResult;
	*Message = __params.Message;
	goto __skip_cleanup;
	
__cleanup:
	Cleanup();
__skip_cleanup:
	ResetClientState(true);
	memset(&__params, 0x00, sizeof(__params));
	return __atlsoap_hr;
}

template <typename TClient>
inline HRESULT CSOSIServiceT<TClient>::InstallNoteForExpeditor(
		int NoteID, 
		bool* InstallNoteForExpeditorResult, 
		BSTR* Message
	)
{
    if ( InstallNoteForExpeditorResult == NULL )
		return E_POINTER;
    if ( Message == NULL )
		return E_POINTER;

	HRESULT __atlsoap_hr = InitializeSOAP(NULL);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_INITIALIZE_ERROR);
		return __atlsoap_hr;
	}
	
	CleanupClient();

	CComPtr<IStream> __atlsoap_spReadStream;
	__CSOSIService_InstallNoteForExpeditor_struct __params;
	memset(&__params, 0x00, sizeof(__params));
	__params.NoteID = NoteID;

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
	
	__atlsoap_hr = SendRequest(_T("SOAPAction: \"fusioncomp.com/SOSIWebService/InstallNoteForExpeditor\"\r\n"));
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

	*InstallNoteForExpeditorResult = __params.InstallNoteForExpeditorResult;
	*Message = __params.Message;
	goto __skip_cleanup;
	
__cleanup:
	Cleanup();
__skip_cleanup:
	ResetClientState(true);
	memset(&__params, 0x00, sizeof(__params));
	return __atlsoap_hr;
}

template <typename TClient>
inline HRESULT CSOSIServiceT<TClient>::AssignReassignMeasureTechnician(
		int OrderID, 
		BSTR MeasureTechUserID, 
		bool* AssignReassignMeasureTechnicianResult, 
		BSTR* Message
	)
{
    if ( AssignReassignMeasureTechnicianResult == NULL )
		return E_POINTER;
    if ( Message == NULL )
		return E_POINTER;

	HRESULT __atlsoap_hr = InitializeSOAP(NULL);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_INITIALIZE_ERROR);
		return __atlsoap_hr;
	}
	
	CleanupClient();

	CComPtr<IStream> __atlsoap_spReadStream;
	__CSOSIService_AssignReassignMeasureTechnician_struct __params;
	memset(&__params, 0x00, sizeof(__params));
	__params.OrderID = OrderID;
	__params.MeasureTechUserID = MeasureTechUserID;

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
	
	__atlsoap_hr = SendRequest(_T("SOAPAction: \"fusioncomp.com/SOSIWebService/AssignReassignMeasureTechnician\"\r\n"));
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

	*AssignReassignMeasureTechnicianResult = __params.AssignReassignMeasureTechnicianResult;
	*Message = __params.Message;
	goto __skip_cleanup;
	
__cleanup:
	Cleanup();
__skip_cleanup:
	ResetClientState(true);
	memset(&__params, 0x00, sizeof(__params));
	return __atlsoap_hr;
}

template <typename TClient>
inline HRESULT CSOSIServiceT<TClient>::InstallServiceComplete(
		int OrderID, 
		bool* InstallServiceCompleteResult, 
		BSTR* Message
	)
{
    if ( InstallServiceCompleteResult == NULL )
		return E_POINTER;
    if ( Message == NULL )
		return E_POINTER;

	HRESULT __atlsoap_hr = InitializeSOAP(NULL);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_INITIALIZE_ERROR);
		return __atlsoap_hr;
	}
	
	CleanupClient();

	CComPtr<IStream> __atlsoap_spReadStream;
	__CSOSIService_InstallServiceComplete_struct __params;
	memset(&__params, 0x00, sizeof(__params));
	__params.OrderID = OrderID;

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
	
	__atlsoap_hr = SendRequest(_T("SOAPAction: \"fusioncomp.com/SOSIWebService/InstallServiceComplete\"\r\n"));
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

	*InstallServiceCompleteResult = __params.InstallServiceCompleteResult;
	*Message = __params.Message;
	goto __skip_cleanup;
	
__cleanup:
	Cleanup();
__skip_cleanup:
	ResetClientState(true);
	memset(&__params, 0x00, sizeof(__params));
	return __atlsoap_hr;
}

template <typename TClient>
inline HRESULT CSOSIServiceT<TClient>::ConfirmMeasurePOCancel(
		int OrderID, 
		bool* ConfirmMeasurePOCancelResult, 
		BSTR* Message
	)
{
    if ( ConfirmMeasurePOCancelResult == NULL )
		return E_POINTER;
    if ( Message == NULL )
		return E_POINTER;

	HRESULT __atlsoap_hr = InitializeSOAP(NULL);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_INITIALIZE_ERROR);
		return __atlsoap_hr;
	}
	
	CleanupClient();

	CComPtr<IStream> __atlsoap_spReadStream;
	__CSOSIService_ConfirmMeasurePOCancel_struct __params;
	memset(&__params, 0x00, sizeof(__params));
	__params.OrderID = OrderID;

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
	
	__atlsoap_hr = SendRequest(_T("SOAPAction: \"fusioncomp.com/SOSIWebService/ConfirmMeasurePOCancel\"\r\n"));
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

	*ConfirmMeasurePOCancelResult = __params.ConfirmMeasurePOCancelResult;
	*Message = __params.Message;
	goto __skip_cleanup;
	
__cleanup:
	Cleanup();
__skip_cleanup:
	ResetClientState(true);
	memset(&__params, 0x00, sizeof(__params));
	return __atlsoap_hr;
}

template <typename TClient>
inline HRESULT CSOSIServiceT<TClient>::MeasureApptCustomerCancellation(
		int OrderID, 
		BSTR ReasonCode, 
		bool* MeasureApptCustomerCancellationResult, 
		BSTR* Message
	)
{
    if ( MeasureApptCustomerCancellationResult == NULL )
		return E_POINTER;
    if ( Message == NULL )
		return E_POINTER;

	HRESULT __atlsoap_hr = InitializeSOAP(NULL);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_INITIALIZE_ERROR);
		return __atlsoap_hr;
	}
	
	CleanupClient();

	CComPtr<IStream> __atlsoap_spReadStream;
	__CSOSIService_MeasureApptCustomerCancellation_struct __params;
	memset(&__params, 0x00, sizeof(__params));
	__params.OrderID = OrderID;
	__params.ReasonCode = ReasonCode;

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
	
	__atlsoap_hr = SendRequest(_T("SOAPAction: \"fusioncomp.com/SOSIWebService/MeasureApptCustomerCancellation\"\r\n"));
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

	*MeasureApptCustomerCancellationResult = __params.MeasureApptCustomerCancellationResult;
	*Message = __params.Message;
	goto __skip_cleanup;
	
__cleanup:
	Cleanup();
__skip_cleanup:
	ResetClientState(true);
	memset(&__params, 0x00, sizeof(__params));
	return __atlsoap_hr;
}

template <typename TClient>
inline HRESULT CSOSIServiceT<TClient>::ConfirmInstallPOCancel(
		int OrderID, 
		bool* ConfirmInstallPOCancelResult, 
		BSTR* Message
	)
{
    if ( ConfirmInstallPOCancelResult == NULL )
		return E_POINTER;
    if ( Message == NULL )
		return E_POINTER;

	HRESULT __atlsoap_hr = InitializeSOAP(NULL);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_INITIALIZE_ERROR);
		return __atlsoap_hr;
	}
	
	CleanupClient();

	CComPtr<IStream> __atlsoap_spReadStream;
	__CSOSIService_ConfirmInstallPOCancel_struct __params;
	memset(&__params, 0x00, sizeof(__params));
	__params.OrderID = OrderID;

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
	
	__atlsoap_hr = SendRequest(_T("SOAPAction: \"fusioncomp.com/SOSIWebService/ConfirmInstallPOCancel\"\r\n"));
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

	*ConfirmInstallPOCancelResult = __params.ConfirmInstallPOCancelResult;
	*Message = __params.Message;
	goto __skip_cleanup;
	
__cleanup:
	Cleanup();
__skip_cleanup:
	ResetClientState(true);
	memset(&__params, 0x00, sizeof(__params));
	return __atlsoap_hr;
}

template <typename TClient>
inline HRESULT CSOSIServiceT<TClient>::MeasureApptRescheduleWithDate(
		int OrderID, 
		BSTR ReasonCode, 
		bool* MeasureApptRescheduleWithDateResult, 
		BSTR* Message
	)
{
    if ( MeasureApptRescheduleWithDateResult == NULL )
		return E_POINTER;
    if ( Message == NULL )
		return E_POINTER;

	HRESULT __atlsoap_hr = InitializeSOAP(NULL);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_INITIALIZE_ERROR);
		return __atlsoap_hr;
	}
	
	CleanupClient();

	CComPtr<IStream> __atlsoap_spReadStream;
	__CSOSIService_MeasureApptRescheduleWithDate_struct __params;
	memset(&__params, 0x00, sizeof(__params));
	__params.OrderID = OrderID;
	__params.ReasonCode = ReasonCode;

	__atlsoap_hr = SetClientStruct(&__params, 11);
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
	
	__atlsoap_hr = SendRequest(_T("SOAPAction: \"fusioncomp.com/SOSIWebService/MeasureApptRescheduleWithDate\"\r\n"));
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

	*MeasureApptRescheduleWithDateResult = __params.MeasureApptRescheduleWithDateResult;
	*Message = __params.Message;
	goto __skip_cleanup;
	
__cleanup:
	Cleanup();
__skip_cleanup:
	ResetClientState(true);
	memset(&__params, 0x00, sizeof(__params));
	return __atlsoap_hr;
}

template <typename TClient>
inline HRESULT CSOSIServiceT<TClient>::ConfirmInstallPOChange(
		int OrderID, 
		bool* ConfirmInstallPOChangeResult, 
		BSTR* Message
	)
{
    if ( ConfirmInstallPOChangeResult == NULL )
		return E_POINTER;
    if ( Message == NULL )
		return E_POINTER;

	HRESULT __atlsoap_hr = InitializeSOAP(NULL);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_INITIALIZE_ERROR);
		return __atlsoap_hr;
	}
	
	CleanupClient();

	CComPtr<IStream> __atlsoap_spReadStream;
	__CSOSIService_ConfirmInstallPOChange_struct __params;
	memset(&__params, 0x00, sizeof(__params));
	__params.OrderID = OrderID;

	__atlsoap_hr = SetClientStruct(&__params, 12);
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
	
	__atlsoap_hr = SendRequest(_T("SOAPAction: \"fusioncomp.com/SOSIWebService/ConfirmInstallPOChange\"\r\n"));
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

	*ConfirmInstallPOChangeResult = __params.ConfirmInstallPOChangeResult;
	*Message = __params.Message;
	goto __skip_cleanup;
	
__cleanup:
	Cleanup();
__skip_cleanup:
	ResetClientState(true);
	memset(&__params, 0x00, sizeof(__params));
	return __atlsoap_hr;
}

template <typename TClient>
inline HRESULT CSOSIServiceT<TClient>::HelloWorld(
		BSTR* HelloWorldResult
	)
{
    if ( HelloWorldResult == NULL )
		return E_POINTER;

	HRESULT __atlsoap_hr = InitializeSOAP(NULL);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_INITIALIZE_ERROR);
		return __atlsoap_hr;
	}
	
	CleanupClient();

	CComPtr<IStream> __atlsoap_spReadStream;
	__CSOSIService_HelloWorld_struct __params;
	memset(&__params, 0x00, sizeof(__params));

	__atlsoap_hr = SetClientStruct(&__params, 13);
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
	
	__atlsoap_hr = SendRequest(_T("SOAPAction: \"fusioncomp.com/SOSIWebService/HelloWorld\"\r\n"));
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

	*HelloWorldResult = __params.HelloWorldResult;
	goto __skip_cleanup;
	
__cleanup:
	Cleanup();
__skip_cleanup:
	ResetClientState(true);
	memset(&__params, 0x00, sizeof(__params));
	return __atlsoap_hr;
}

template <typename TClient>
inline HRESULT CSOSIServiceT<TClient>::MeasureNoteForExpeditor(
		int NoteID, 
		bool* MeasureNoteForExpeditorResult, 
		BSTR* Message
	)
{
    if ( MeasureNoteForExpeditorResult == NULL )
		return E_POINTER;
    if ( Message == NULL )
		return E_POINTER;

	HRESULT __atlsoap_hr = InitializeSOAP(NULL);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_INITIALIZE_ERROR);
		return __atlsoap_hr;
	}
	
	CleanupClient();

	CComPtr<IStream> __atlsoap_spReadStream;
	__CSOSIService_MeasureNoteForExpeditor_struct __params;
	memset(&__params, 0x00, sizeof(__params));
	__params.NoteID = NoteID;

	__atlsoap_hr = SetClientStruct(&__params, 14);
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
	
	__atlsoap_hr = SendRequest(_T("SOAPAction: \"fusioncomp.com/SOSIWebService/MeasureNoteForExpeditor\"\r\n"));
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

	*MeasureNoteForExpeditorResult = __params.MeasureNoteForExpeditorResult;
	*Message = __params.Message;
	goto __skip_cleanup;
	
__cleanup:
	Cleanup();
__skip_cleanup:
	ResetClientState(true);
	memset(&__params, 0x00, sizeof(__params));
	return __atlsoap_hr;
}

template <typename TClient>
ATL_NOINLINE inline const _soapmap ** CSOSIServiceT<TClient>::GetFunctionMap()
{
	return __CSOSIService_funcs;
}

template <typename TClient>
ATL_NOINLINE inline const _soapmap ** CSOSIServiceT<TClient>::GetHeaderMap()
{
	static const _soapmapentry __CSOSIService_PrintPO_atlsoapheader_entries[] =
	{
		{ 0x00000000 }
	};

	static const _soapmap __CSOSIService_PrintPO_atlsoapheader_map = 
	{
		0xC36A38DB,
		"PrintPO",
		L"PrintPOResponse",
		sizeof("PrintPO")-1,
		sizeof("PrintPOResponse")-1,
		SOAPMAP_HEADER,
		__CSOSIService_PrintPO_atlsoapheader_entries,
		0,
		0,
		-1,
		SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		0x9177334C,
		"fusioncomp.com/SOSIWebService",
		L"fusioncomp.com/SOSIWebService",
		sizeof("fusioncomp.com/SOSIWebService")-1
	};

	static const _soapmapentry __CSOSIService_VerifyProductReceipt_atlsoapheader_entries[] =
	{
		{ 0x00000000 }
	};

	static const _soapmap __CSOSIService_VerifyProductReceipt_atlsoapheader_map = 
	{
		0xEE9A9A11,
		"VerifyProductReceipt",
		L"VerifyProductReceiptResponse",
		sizeof("VerifyProductReceipt")-1,
		sizeof("VerifyProductReceiptResponse")-1,
		SOAPMAP_HEADER,
		__CSOSIService_VerifyProductReceipt_atlsoapheader_entries,
		0,
		0,
		-1,
		SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		0x9177334C,
		"fusioncomp.com/SOSIWebService",
		L"fusioncomp.com/SOSIWebService",
		sizeof("fusioncomp.com/SOSIWebService")-1
	};

	static const _soapmapentry __CSOSIService_InstallScheduleUpdate_atlsoapheader_entries[] =
	{
		{ 0x00000000 }
	};

	static const _soapmap __CSOSIService_InstallScheduleUpdate_atlsoapheader_map = 
	{
		0x2170E9D6,
		"InstallScheduleUpdate",
		L"InstallScheduleUpdateResponse",
		sizeof("InstallScheduleUpdate")-1,
		sizeof("InstallScheduleUpdateResponse")-1,
		SOAPMAP_HEADER,
		__CSOSIService_InstallScheduleUpdate_atlsoapheader_entries,
		0,
		0,
		-1,
		SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		0x9177334C,
		"fusioncomp.com/SOSIWebService",
		L"fusioncomp.com/SOSIWebService",
		sizeof("fusioncomp.com/SOSIWebService")-1
	};

	static const _soapmapentry __CSOSIService_SendMeasureCapacity_atlsoapheader_entries[] =
	{
		{ 0x00000000 }
	};

	static const _soapmap __CSOSIService_SendMeasureCapacity_atlsoapheader_map = 
	{
		0x0DE92E59,
		"SendMeasureCapacity",
		L"SendMeasureCapacityResponse",
		sizeof("SendMeasureCapacity")-1,
		sizeof("SendMeasureCapacityResponse")-1,
		SOAPMAP_HEADER,
		__CSOSIService_SendMeasureCapacity_atlsoapheader_entries,
		0,
		0,
		-1,
		SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		0x9177334C,
		"fusioncomp.com/SOSIWebService",
		L"fusioncomp.com/SOSIWebService",
		sizeof("fusioncomp.com/SOSIWebService")-1
	};

	static const _soapmapentry __CSOSIService_ScheduleWillCall_atlsoapheader_entries[] =
	{
		{ 0x00000000 }
	};

	static const _soapmap __CSOSIService_ScheduleWillCall_atlsoapheader_map = 
	{
		0xF1849C50,
		"ScheduleWillCall",
		L"ScheduleWillCallResponse",
		sizeof("ScheduleWillCall")-1,
		sizeof("ScheduleWillCallResponse")-1,
		SOAPMAP_HEADER,
		__CSOSIService_ScheduleWillCall_atlsoapheader_entries,
		0,
		0,
		-1,
		SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		0x9177334C,
		"fusioncomp.com/SOSIWebService",
		L"fusioncomp.com/SOSIWebService",
		sizeof("fusioncomp.com/SOSIWebService")-1
	};

	static const _soapmapentry __CSOSIService_InstallNoteForExpeditor_atlsoapheader_entries[] =
	{
		{ 0x00000000 }
	};

	static const _soapmap __CSOSIService_InstallNoteForExpeditor_atlsoapheader_map = 
	{
		0x514624D7,
		"InstallNoteForExpeditor",
		L"InstallNoteForExpeditorResponse",
		sizeof("InstallNoteForExpeditor")-1,
		sizeof("InstallNoteForExpeditorResponse")-1,
		SOAPMAP_HEADER,
		__CSOSIService_InstallNoteForExpeditor_atlsoapheader_entries,
		0,
		0,
		-1,
		SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		0x9177334C,
		"fusioncomp.com/SOSIWebService",
		L"fusioncomp.com/SOSIWebService",
		sizeof("fusioncomp.com/SOSIWebService")-1
	};

	static const _soapmapentry __CSOSIService_AssignReassignMeasureTechnician_atlsoapheader_entries[] =
	{
		{ 0x00000000 }
	};

	static const _soapmap __CSOSIService_AssignReassignMeasureTechnician_atlsoapheader_map = 
	{
		0xB449EA58,
		"AssignReassignMeasureTechnician",
		L"AssignReassignMeasureTechnicianResponse",
		sizeof("AssignReassignMeasureTechnician")-1,
		sizeof("AssignReassignMeasureTechnicianResponse")-1,
		SOAPMAP_HEADER,
		__CSOSIService_AssignReassignMeasureTechnician_atlsoapheader_entries,
		0,
		0,
		-1,
		SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		0x9177334C,
		"fusioncomp.com/SOSIWebService",
		L"fusioncomp.com/SOSIWebService",
		sizeof("fusioncomp.com/SOSIWebService")-1
	};

	static const _soapmapentry __CSOSIService_InstallServiceComplete_atlsoapheader_entries[] =
	{
		{ 0x00000000 }
	};

	static const _soapmap __CSOSIService_InstallServiceComplete_atlsoapheader_map = 
	{
		0x120A19F0,
		"InstallServiceComplete",
		L"InstallServiceCompleteResponse",
		sizeof("InstallServiceComplete")-1,
		sizeof("InstallServiceCompleteResponse")-1,
		SOAPMAP_HEADER,
		__CSOSIService_InstallServiceComplete_atlsoapheader_entries,
		0,
		0,
		-1,
		SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		0x9177334C,
		"fusioncomp.com/SOSIWebService",
		L"fusioncomp.com/SOSIWebService",
		sizeof("fusioncomp.com/SOSIWebService")-1
	};

	static const _soapmapentry __CSOSIService_ConfirmMeasurePOCancel_atlsoapheader_entries[] =
	{
		{ 0x00000000 }
	};

	static const _soapmap __CSOSIService_ConfirmMeasurePOCancel_atlsoapheader_map = 
	{
		0xE8089B94,
		"ConfirmMeasurePOCancel",
		L"ConfirmMeasurePOCancelResponse",
		sizeof("ConfirmMeasurePOCancel")-1,
		sizeof("ConfirmMeasurePOCancelResponse")-1,
		SOAPMAP_HEADER,
		__CSOSIService_ConfirmMeasurePOCancel_atlsoapheader_entries,
		0,
		0,
		-1,
		SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		0x9177334C,
		"fusioncomp.com/SOSIWebService",
		L"fusioncomp.com/SOSIWebService",
		sizeof("fusioncomp.com/SOSIWebService")-1
	};

	static const _soapmapentry __CSOSIService_MeasureApptCustomerCancellation_atlsoapheader_entries[] =
	{
		{ 0x00000000 }
	};

	static const _soapmap __CSOSIService_MeasureApptCustomerCancellation_atlsoapheader_map = 
	{
		0x37E3AF75,
		"MeasureApptCustomerCancellation",
		L"MeasureApptCustomerCancellationResponse",
		sizeof("MeasureApptCustomerCancellation")-1,
		sizeof("MeasureApptCustomerCancellationResponse")-1,
		SOAPMAP_HEADER,
		__CSOSIService_MeasureApptCustomerCancellation_atlsoapheader_entries,
		0,
		0,
		-1,
		SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		0x9177334C,
		"fusioncomp.com/SOSIWebService",
		L"fusioncomp.com/SOSIWebService",
		sizeof("fusioncomp.com/SOSIWebService")-1
	};

	static const _soapmapentry __CSOSIService_ConfirmInstallPOCancel_atlsoapheader_entries[] =
	{
		{ 0x00000000 }
	};

	static const _soapmap __CSOSIService_ConfirmInstallPOCancel_atlsoapheader_map = 
	{
		0xECB1EFD9,
		"ConfirmInstallPOCancel",
		L"ConfirmInstallPOCancelResponse",
		sizeof("ConfirmInstallPOCancel")-1,
		sizeof("ConfirmInstallPOCancelResponse")-1,
		SOAPMAP_HEADER,
		__CSOSIService_ConfirmInstallPOCancel_atlsoapheader_entries,
		0,
		0,
		-1,
		SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		0x9177334C,
		"fusioncomp.com/SOSIWebService",
		L"fusioncomp.com/SOSIWebService",
		sizeof("fusioncomp.com/SOSIWebService")-1
	};

	static const _soapmapentry __CSOSIService_MeasureApptRescheduleWithDate_atlsoapheader_entries[] =
	{
		{ 0x00000000 }
	};

	static const _soapmap __CSOSIService_MeasureApptRescheduleWithDate_atlsoapheader_map = 
	{
		0xB2F83154,
		"MeasureApptRescheduleWithDate",
		L"MeasureApptRescheduleWithDateResponse",
		sizeof("MeasureApptRescheduleWithDate")-1,
		sizeof("MeasureApptRescheduleWithDateResponse")-1,
		SOAPMAP_HEADER,
		__CSOSIService_MeasureApptRescheduleWithDate_atlsoapheader_entries,
		0,
		0,
		-1,
		SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		0x9177334C,
		"fusioncomp.com/SOSIWebService",
		L"fusioncomp.com/SOSIWebService",
		sizeof("fusioncomp.com/SOSIWebService")-1
	};

	static const _soapmapentry __CSOSIService_ConfirmInstallPOChange_atlsoapheader_entries[] =
	{
		{ 0x00000000 }
	};

	static const _soapmap __CSOSIService_ConfirmInstallPOChange_atlsoapheader_map = 
	{
		0x2F994979,
		"ConfirmInstallPOChange",
		L"ConfirmInstallPOChangeResponse",
		sizeof("ConfirmInstallPOChange")-1,
		sizeof("ConfirmInstallPOChangeResponse")-1,
		SOAPMAP_HEADER,
		__CSOSIService_ConfirmInstallPOChange_atlsoapheader_entries,
		0,
		0,
		-1,
		SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		0x9177334C,
		"fusioncomp.com/SOSIWebService",
		L"fusioncomp.com/SOSIWebService",
		sizeof("fusioncomp.com/SOSIWebService")-1
	};

	static const _soapmapentry __CSOSIService_HelloWorld_atlsoapheader_entries[] =
	{
		{ 0x00000000 }
	};

	static const _soapmap __CSOSIService_HelloWorld_atlsoapheader_map = 
	{
		0x8AFDB82B,
		"HelloWorld",
		L"HelloWorldResponse",
		sizeof("HelloWorld")-1,
		sizeof("HelloWorldResponse")-1,
		SOAPMAP_HEADER,
		__CSOSIService_HelloWorld_atlsoapheader_entries,
		0,
		0,
		-1,
		SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		0x9177334C,
		"fusioncomp.com/SOSIWebService",
		L"fusioncomp.com/SOSIWebService",
		sizeof("fusioncomp.com/SOSIWebService")-1
	};

	static const _soapmapentry __CSOSIService_MeasureNoteForExpeditor_atlsoapheader_entries[] =
	{
		{ 0x00000000 }
	};

	static const _soapmap __CSOSIService_MeasureNoteForExpeditor_atlsoapheader_map = 
	{
		0x78FE5B92,
		"MeasureNoteForExpeditor",
		L"MeasureNoteForExpeditorResponse",
		sizeof("MeasureNoteForExpeditor")-1,
		sizeof("MeasureNoteForExpeditorResponse")-1,
		SOAPMAP_HEADER,
		__CSOSIService_MeasureNoteForExpeditor_atlsoapheader_entries,
		0,
		0,
		-1,
		SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		0x9177334C,
		"fusioncomp.com/SOSIWebService",
		L"fusioncomp.com/SOSIWebService",
		sizeof("fusioncomp.com/SOSIWebService")-1
	};


	static const _soapmap * __CSOSIService_headers[] =
	{
		&__CSOSIService_PrintPO_atlsoapheader_map,
		&__CSOSIService_VerifyProductReceipt_atlsoapheader_map,
		&__CSOSIService_InstallScheduleUpdate_atlsoapheader_map,
		&__CSOSIService_SendMeasureCapacity_atlsoapheader_map,
		&__CSOSIService_ScheduleWillCall_atlsoapheader_map,
		&__CSOSIService_InstallNoteForExpeditor_atlsoapheader_map,
		&__CSOSIService_AssignReassignMeasureTechnician_atlsoapheader_map,
		&__CSOSIService_InstallServiceComplete_atlsoapheader_map,
		&__CSOSIService_ConfirmMeasurePOCancel_atlsoapheader_map,
		&__CSOSIService_MeasureApptCustomerCancellation_atlsoapheader_map,
		&__CSOSIService_ConfirmInstallPOCancel_atlsoapheader_map,
		&__CSOSIService_MeasureApptRescheduleWithDate_atlsoapheader_map,
		&__CSOSIService_ConfirmInstallPOChange_atlsoapheader_map,
		&__CSOSIService_HelloWorld_atlsoapheader_map,
		&__CSOSIService_MeasureNoteForExpeditor_atlsoapheader_map,
		NULL
	};
	
	return __CSOSIService_headers;
}

template <typename TClient>
ATL_NOINLINE inline void * CSOSIServiceT<TClient>::GetHeaderValue()
{
	return this;
}

template <typename TClient>
ATL_NOINLINE inline const wchar_t * CSOSIServiceT<TClient>::GetNamespaceUri()
{
	return L"fusioncomp.com/SOSIWebService";
}

template <typename TClient>
ATL_NOINLINE inline const char * CSOSIServiceT<TClient>::GetServiceName()
{
	return NULL;
}

template <typename TClient>
ATL_NOINLINE inline const char * CSOSIServiceT<TClient>::GetNamespaceUriA()
{
	return "fusioncomp.com/SOSIWebService";
}

template <typename TClient>
ATL_NOINLINE inline HRESULT CSOSIServiceT<TClient>::CallFunction(
	void *, 
	const wchar_t *, int,
	size_t)
{
	return E_NOTIMPL;
}

template <typename TClient>
ATL_NOINLINE inline HRESULT CSOSIServiceT<TClient>::GetClientReader(ISAXXMLReader **ppReader)
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

} // namespace SOSIService
