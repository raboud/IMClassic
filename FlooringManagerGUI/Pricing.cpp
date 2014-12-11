/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#include "stdafx.h"
#include "pricing.h"
#include "Flooring.h"

CPricing::CPricing(void)
:   m_setBasicLabor(&g_dbFlooring)
  , m_setOptions(&g_dbFlooring)
  , m_setBasicPricing(&g_dbFlooring)
  , m_setOptionPricing(&g_dbFlooring)
  , m_setStores(&g_dbFlooring)
{
	m_setBasicLabor.m_strFilter = "BasicLaborID = -1";
	m_setBasicLabor.Open();

	m_setOptions.m_strFilter = "OptionID = -1";
	m_setOptions.Open();

	m_setBasicPricing.m_strFilter = "BasicPricingID = -1";
	m_setBasicPricing.Open();

	m_setOptionPricing.m_strFilter = "ID = -1";
	m_setOptionPricing.Open();

	m_setStores.m_strFilter = "StoreID = -1";
	m_setStores.Open();
}

CPricing::~CPricing(void)
{
	m_setBasicLabor.Close();
	m_setOptions.Close();
	m_setBasicPricing.Close();
	m_setOptionPricing.Close();
	m_setStores.Close();
}

bool CPricing::GetBasicPrices(int iBasicLaborID, COleDateTime OrderDate, COleDateTime ScheduleDate, int iStoreID, double& dCost, double& dPrice)
{
	bool bPriceAndRetailOK = false;
	bool bCostOK = false;

	// make sure the passed in basic labor id exists...
	m_setBasicLabor.m_strFilter.Format("[BasicLaborID] = '%d'", iBasicLaborID);
	m_setBasicLabor.Requery();
	ASSERT(!m_setBasicLabor.IsEOF());

	// make sure passed in store number exists...
	m_setStores.m_strFilter.Format("[StoreID] = %d", iStoreID);
	m_setStores.Requery();
	ASSERT(!m_setStores.IsEOF());

	// get the marketid for this store
	int iMarketID = m_setStores.m_MarketId;

	// see if we have entry in the BasicPricing table...if not, we'll use default
	// prices from BasicLabor table

	// Get Price and Retail -- Get Cost down below
	COleDateTime timePO(OrderDate.GetYear(), OrderDate.GetMonth(), OrderDate.GetDay(), 0, 0, 0) ;
	CString strDateFilter;
	strDateFilter.Format("('%s' >= StartDate) AND ('%s' <= EndDate)", timePO.Format("%m/%d/%Y"), timePO.Format("%m/%d/%Y") );
	m_setBasicPricing.m_strFilter.Format("[BasicLaborID] = '%d' AND [StoreID] = '%d' AND %s", iBasicLaborID, iStoreID, strDateFilter);
	m_setBasicPricing.Requery();

	// if no records found, try filtering on marketid and storeid = -1
	if (m_setBasicPricing.IsEOF())
	{
		m_setBasicPricing.m_strFilter.Format("[BasicLaborID] = '%d' AND [MarketID] = '%d' AND [StoreID] = -1 AND %s", iBasicLaborID, iMarketID, strDateFilter);
		m_setBasicPricing.Requery();
	}

	// if record found, use price from BasicPricing table, else use default
	if (!m_setBasicPricing.IsEOF())
	{
		// there should only be 1 that matches
		while (!m_setBasicPricing.IsEOF())
		{
			// have to do this for the GetRecordCount() to work right
			m_setBasicPricing.MoveNext();
		}
		if (m_setBasicPricing.GetRecordCount() == 1)
		{
			dPrice = m_setBasicPricing.m_Price;
			dCost = m_setBasicPricing.m_Cost;
			bPriceAndRetailOK = true;
		}
		else
		{
			// use default prices from basic labor table
			dPrice = atof(m_setBasicLabor.m_UnitPrice.GetBuffer());
			dCost = atof(m_setBasicLabor.m_UnitCost.GetBuffer());
			bPriceAndRetailOK = true;
		}
	}
	else
	{
		// use default prices from basic labor table
		dPrice = atof(m_setBasicLabor.m_UnitPrice.GetBuffer());
		dCost = atof(m_setBasicLabor.m_UnitCost.GetBuffer());
		bPriceAndRetailOK = true;
	}

	// if OrderDate is not equal to ScheduleDate, then we need to ensure we get the Cost value associated with the
	// ScheduleDate
	if (OrderDate != ScheduleDate)
	{
		timePO = COleDateTime(ScheduleDate.GetYear(), ScheduleDate.GetMonth(), ScheduleDate.GetDay(), 0, 0, 0) ;
		strDateFilter.Format("('%s' >= StartDate) AND ('%s' <= EndDate)", timePO.Format("%m/%d/%Y"), timePO.Format("%m/%d/%Y") );
		m_setBasicPricing.m_strFilter.Format("[BasicLaborID] = '%d' AND [StoreID] = '%d' AND %s", iBasicLaborID, iStoreID, strDateFilter);
		m_setBasicPricing.Requery();

		// if no records found, try filtering on marketid and storeid = -1
		if (m_setBasicPricing.IsEOF())
		{
			m_setBasicPricing.m_strFilter.Format("[BasicLaborID] = '%d' AND [MarketID] = '%d' AND [StoreID] = -1 AND %s", iBasicLaborID, iMarketID, strDateFilter);
			m_setBasicPricing.Requery();
		}

		// if record found, use price from BasicPricing table, else use default
		if (!m_setBasicPricing.IsEOF())
		{
			// there should only be 1 that matches
			while (!m_setBasicPricing.IsEOF())
			{
				// have to do this for the GetRecordCount() to work right
				m_setBasicPricing.MoveNext();
			}
			if (m_setBasicPricing.GetRecordCount() == 1)
			{
				dCost = m_setBasicPricing.m_Cost;
				bCostOK = true;
			}
			else
			{
				// use default prices from basic labor table
				dCost = atof(m_setBasicLabor.m_UnitCost.GetBuffer());
				bCostOK = true;
			}
		}
		else
		{
			// use default value from basic labor table
			dCost = atof(m_setBasicLabor.m_UnitCost.GetBuffer());
			bCostOK = true;
		}
	}
	else
	{
		bCostOK = true;
	}
    	
	return bPriceAndRetailOK && bCostOK;
}

bool CPricing::GetOptionPrices(int iOptionID, COleDateTime OrderDate, COleDateTime ScheduleDate, int iStoreID, double& dCost, double& dPrice)
{
	bool bPriceAndRetailOK = false;
	bool bCostOK = false;

	// make sure the passed in option id exists...
	m_setOptions.m_strFilter.Format("[OptionID] = '%d'", iOptionID);
	m_setOptions.Requery();
	ASSERT(!m_setOptions.IsEOF());

	// make sure passed in store number exists...
	m_setStores.m_strFilter.Format("[StoreID] = %d", iStoreID);
	m_setStores.Requery();
	ASSERT(!m_setStores.IsEOF());

	// get the marketid for this store
	int iMarketID = m_setStores.m_MarketId;

	// see if we have entry in the OptionPricing table...if not, we'll use default
	// prices from Options table

	COleDateTime timePO(OrderDate.GetYear() , OrderDate.GetMonth(), OrderDate.GetDay(), 0, 0, 0) ;
	CString strDateFilter;
	strDateFilter.Format("('%s' >= StartDate) AND ('%s' <= EndDate)", timePO.Format("%m/%d/%Y"), timePO.Format("%m/%d/%Y") );
	m_setOptionPricing.m_strFilter.Format("[OptionID] = '%d' AND [StoreID] = '%d' AND %s", iOptionID, iStoreID, strDateFilter);
	m_setOptionPricing.Requery();

	// if no records found, try just filtering on marketid
	if (m_setOptionPricing.IsEOF())
	{
		m_setOptionPricing.m_strFilter.Format("[OptionID] = '%d' AND [MarketID] = '%d' AND [StoreID] = -1 AND %s", iOptionID, iMarketID, strDateFilter);
		m_setOptionPricing.Requery();
	}

	// if record found, use price from BasicPricing table, else use default
	if (!m_setOptionPricing.IsEOF())
	{
		// there should only be 1 that matches
		while (!m_setOptionPricing.IsEOF())
		{
			m_setOptionPricing.MoveNext();
		}
		if (m_setOptionPricing.GetRecordCount() == 1)
		{
			dPrice = m_setOptionPricing.m_Price;
			dCost = m_setOptionPricing.m_Cost;
			bPriceAndRetailOK = true;
		}
		else
		{
			// use default prices from basic labor table
			dPrice = atof(m_setOptions.m_UnitPrice.GetBuffer());
			dCost = atof(m_setOptions.m_UnitCost.GetBuffer());
			bPriceAndRetailOK = true;
		}
	}
	else
	{
		// use default prices from basic labor table
		dPrice = atof(m_setOptions.m_UnitPrice.GetBuffer());
		dCost = atof(m_setOptions.m_UnitCost.GetBuffer());
		bPriceAndRetailOK = true;
	}

	// if OrderDate is not equal to ScheduleDate, then we want to pull the cost value using the ScheduleDate
	if (OrderDate != ScheduleDate)
	{
		timePO = COleDateTime(ScheduleDate.GetYear() , ScheduleDate.GetMonth(), ScheduleDate.GetDay(), 0, 0, 0) ;
		strDateFilter.Format("('%s' >= StartDate) AND ('%s' <= EndDate)", timePO.Format("%m/%d/%Y"), timePO.Format("%m/%d/%Y") );
		m_setOptionPricing.m_strFilter.Format("[OptionID] = '%d' AND [StoreID] = '%d' AND %s", iOptionID, iStoreID, strDateFilter);
		m_setOptionPricing.Requery();

		// if no records found, try just filtering on marketid
		if (m_setOptionPricing.IsEOF())
		{
			m_setOptionPricing.m_strFilter.Format("[OptionID] = '%d' AND [MarketID] = '%d' AND [StoreID] = -1 AND %s", iOptionID, iMarketID, strDateFilter);
			m_setOptionPricing.Requery();
		}

		// if record found, use price from BasicPricing table, else use default
		if (!m_setOptionPricing.IsEOF())
		{
			// there should only be 1 that matches
			while (!m_setOptionPricing.IsEOF())
			{
				m_setOptionPricing.MoveNext();
			}
			if (m_setOptionPricing.GetRecordCount() == 1)
			{
				dCost = m_setOptionPricing.m_Cost;
				bCostOK = true;
			}
			else
			{
				// use default prices from basic labor table
				dCost = atof(m_setOptions.m_UnitCost.GetBuffer());
				bCostOK = true;
			}
		}
		else
		{
			// use default prices from basic labor table
			dCost = atof(m_setOptions.m_UnitCost.GetBuffer());
			bCostOK = true;
		}
	}
	else
	{
		bCostOK = true;
	}

	return bPriceAndRetailOK && bCostOK;
}
