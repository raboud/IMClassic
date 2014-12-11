/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#include "stdafx.h"
#include "pricing.h"
#include "Flooring.h"

using namespace CFI::InstallationManager::Business;

CPricing::CPricing(void)
{
}

CPricing::~CPricing(void)
{
}

bool CPricing::GetBasicPrices(int iBasicLaborID, COleDateTime OrderDate, COleDateTime ScheduleDate, int iStoreID, double& dCost, double& dPrice)
{
	double temp = -11.0;
	temp = PricingBLL::GetBasicPrice(CachedData::Context, iBasicLaborID, iStoreID, System::DateTime::FromOADate(OrderDate));
	dPrice = temp;
	temp = PricingBLL::GetBasicCost(CachedData::Context, iBasicLaborID, iStoreID, System::DateTime::FromOADate(ScheduleDate));
	dCost = temp;
	return true;
}

bool CPricing::GetOptionPrices(int iOptionID, COleDateTime OrderDate, COleDateTime ScheduleDate, int iStoreID, double& dCost, double& dPrice)
{
	double temp = -11.0;
	temp = PricingBLL::GetOptionPrice(CachedData::Context, iOptionID, iStoreID, System::DateTime::FromOADate(OrderDate));
	dPrice = temp;
	temp = PricingBLL::GetOptionCost(CachedData::Context, iOptionID, iStoreID, System::DateTime::FromOADate(ScheduleDate));
	dCost = temp;
	return true;
}
