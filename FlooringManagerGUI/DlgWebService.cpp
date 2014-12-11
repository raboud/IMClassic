// DlgWebService.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgWebService.h"

#include "SetStores.h"
#include "SetOrders.h"
#include "Logger.h"

using namespace CFI::InstallationManager::SharedForms;

CDlgWebService::CDlgWebService()
{
}

CDlgWebService::~CDlgWebService()
{
}

bool CDlgWebService::SPNUpdatePO(CPoList* pListPOs)
{
	::System::Collections::Generic::List<int>^ l = gcnew ::System::Collections::Generic::List<int>();
		POSITION pos = pListPOs->GetHeadPosition() ;
		while (pos)
		{
			l->Add(pListPOs->GetNext(pos));
		}

		return FormSPN::SPNUpdatePO(l);
}

bool CDlgWebService::SPNUpdatePO(CString strStoreNumber, CString strPONumber)
{
	return FormSPN::SPNUpdatePO(gcnew System::String(strStoreNumber), gcnew System::String(strPONumber));
}

