/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once

#include "setbasiclabor.h"
#include "setoptions.h"
#include "basicpricing.h"
#include "optionpricing.h"
#include "setstores.h"

class CPricing
{
public:
	CPricing(void);
	~CPricing(void);

	bool GetBasicPrices(int iBasicLaborID, COleDateTime OrderDate, COleDateTime ScheduleDate, int iStoreID, double& dCost, double& dPrice);
	bool GetOptionPrices(int iOptionID, COleDateTime OrderDate, COleDateTime ScheduleDate, int iStoreID, double& dCost, double& dPrice);

protected:

	CSetBasicLabor m_setBasicLabor;
	CSetOptions m_setOptions;

	CBasicPricing m_setBasicPricing;
	COptionPricing m_setOptionPricing;

	CSetStores m_setStores;

};
