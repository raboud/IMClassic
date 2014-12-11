// ==========================================================================
// 							Class Implementation : COXDate
// ==========================================================================

// Source file : date.cpp

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved                      
                          
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "date.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif                                                                

#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////
// Definition of static members
const int COXDate::nEarliestYear = 1583;
const DWORD COXDate::nEarliestJulianDate = 2299239; 	// == 1st January 1583


// Data members -------------------------------------------------------------
// protected:
	// DWORD m_nJulianDate;
	// --- 	This is the Julian Date.
	//		This number is an astronomical convention that allows dates to be
	//		cataloged by a single, long integer
	//		It is a continuous number which takes care of leap years etc.
	//		The number of days between to date becomes thus a simple subtraction
	
	// const DWORD nEarliestJulianDate = 2299239 	// == 1st January 1583
	// --- This is the smallest possible valid Julian date

// private:
	
// Member functions ---------------------------------------------------------
// public:

COXDate::COXDate()
	:
	m_nJulianDate(0)
	{                  
	}  
	
COXDate::COXDate(int nYear, int nMonth, int nDay)
	{
	SetDate(nYear, nMonth, nDay);
	}

COXDate::COXDate(const CTime& timeSrc)
	{
	SetDate(timeSrc.GetYear(), timeSrc.GetMonth(),timeSrc.GetDay());
	}                                                               

COXDate::COXDate(const COXDate& dateSrc)
	{
	m_nJulianDate = dateSrc.m_nJulianDate;
	}
	
void COXDate::SetDate(int nYear, int nMonth, int nDay)
	{
	ASSERT(1583 <= nYear);
	ASSERT((1 <= nMonth) && (nMonth <= 12));
	ASSERT((1 <= nDay) && (nDay <= 31));
	if (nMonth > 2)
		nMonth -= 3;
	else           
		{
		nMonth += 9;
		nYear--;	
		}
	m_nJulianDate = 146097L * (nYear / 100) / 4 + 1461L * (nYear % 100) / 4 +
		(153 * nMonth + 2) / 5 + nDay + 1721119;
	}
	
void COXDate::GetDate(int& nYear, int &nMonth, int& nDay) const
	{
	ASSERT(m_nJulianDate != 0);			// date object must be initialized
	DWORD x, y, m, d;
	
	x = 4 * m_nJulianDate - 6884477L;	
	y = (x / 146097L) * 100;
	d = (x % 146097) / 4;
	
	x = 4 * d + 3;
	y = (x / 1461) + y;
	d = (x % 1461) / 4 + 1;
	
	x = 5 * d - 3;
	m = x / 153 + 1;
	d = (x % 153) / 5 + 1;
	
	nYear = int(y + m / 11);		
	if (m < 11)
		nMonth = int(m + 2);
	else
		nMonth = int(m - 10);
	nDay = int(d);
	}	
	
COXDate::GetYear() const
	{
	ASSERT(m_nJulianDate != 0);			// date object must be initialized
	int nYear, nMonth, nDay;
	GetDate(nYear, nMonth, nDay);
	return(nYear);
	}
	
COXDate::GetMonth() const
	{
	ASSERT(m_nJulianDate != 0);			// date object must be initialized
	int nYear, nMonth, nDay;
	GetDate(nYear, nMonth, nDay);
	return(nMonth);
	}
COXDate::GetDay() const
	{
	ASSERT(m_nJulianDate != 0);			// date object must be initialized
	int nYear, nMonth, nDay;
	GetDate(nYear, nMonth, nDay);
	return(nDay);
	}
	
COXDate::EDayOfWeek COXDate::GetDayOfWeek()
	{
	ASSERT(m_nJulianDate != 0);			// date object must be initialized
	switch (m_nJulianDate % 7)
		{
		case 0:
			return(DOWMonday);
		case 1:
			return(DOWTuesday);
		case 2:
			return(DOWWednesday);
		case 3:
			return(DOWThursday);
		case 4:
			return(DOWFriday);
		case 5:
			return(DOWSaturday);
		case 6:
			return(DOWSunday);
		// ... default will never be reached, but must exist otherwise the compiler
		//	   will complain that not all control paths return a value.
		default:           
			return(DOWSunday);
		}
	}								


COXDate& COXDate::operator=(const COXDate& dateSrc)
{
	if(this==&dateSrc)
		return *this;
		
	ASSERT(dateSrc.m_nJulianDate != 0);			// date object must be initialized
	m_nJulianDate = dateSrc.m_nJulianDate; 
	return (*this); 
}


BOOL COXDate::operator==(COXDate date) const
	{ 
	ASSERT(m_nJulianDate != 0);			// date object must be initialized
	ASSERT(date.m_nJulianDate != 0);	// date object must be initialized
	return (m_nJulianDate == date.m_nJulianDate); 
	}
	
BOOL COXDate::operator!=(COXDate date) const
	{ 
	ASSERT(m_nJulianDate != 0);			// date object must be initialized
	ASSERT(date.m_nJulianDate != 0);	// date object must be initialized
	return (m_nJulianDate != date.m_nJulianDate); 
	}
	
BOOL COXDate::operator<(COXDate date) const
	{ 
	ASSERT(m_nJulianDate != 0);			// date object must be initialized
	ASSERT(date.m_nJulianDate != 0);	// date object must be initialized
	return (m_nJulianDate < date.m_nJulianDate); 
	}
	
BOOL COXDate::operator>(COXDate date) const
	{ 
	ASSERT(m_nJulianDate != 0);			// date object must be initialized
	ASSERT(date.m_nJulianDate != 0);	// date object must be initialized
	return (m_nJulianDate > date.m_nJulianDate); 
	}
	
BOOL COXDate::operator<=(COXDate date) const
	{ 
	ASSERT(m_nJulianDate != 0);			// date object must be initialized
	ASSERT(date.m_nJulianDate != 0);	// date object must be initialized
	return (m_nJulianDate <= date.m_nJulianDate); 
	}
	
BOOL COXDate::operator>=(COXDate date) const
	{ 
	ASSERT(m_nJulianDate != 0);			// date object must be initialized
	ASSERT(date.m_nJulianDate != 0);	// date object must be initialized
	return (m_nJulianDate >= date.m_nJulianDate); 
	}

COXDate COXDate::operator+(int deltaDate) const
	{                                      
	ASSERT(m_nJulianDate != 0);			// date object must be initialized
	ASSERT(nEarliestJulianDate	<= (m_nJulianDate + deltaDate));// Dates before 1583 are invalid
	COXDate returnDate(*this);
	returnDate.m_nJulianDate += deltaDate;
	return (returnDate);
	}
	
const COXDate& COXDate::operator+=(int deltaDate)
	{ 
	ASSERT(m_nJulianDate != 0);			// date object must be initialized
	ASSERT(nEarliestJulianDate	<= (m_nJulianDate + deltaDate));// Dates before 1583 are invalid
	m_nJulianDate += deltaDate; 
	return (*this); 
	}
	
COXDate COXDate::operator-(int deltaDate) const
	{                                      
	ASSERT(m_nJulianDate != 0);			// date object must be initialized
	ASSERT(nEarliestJulianDate	<= (m_nJulianDate - deltaDate));// Dates before 1583 are invalid
	COXDate returnDate(*this);
	returnDate.m_nJulianDate -= deltaDate;
	return (returnDate);
	}
	
const COXDate& COXDate::operator-=(int deltaDate)
	{ 
	ASSERT(m_nJulianDate != 0);			// date object must be initialized
	ASSERT(nEarliestJulianDate	<= (m_nJulianDate - deltaDate));// Dates before 1583 are invalid
	m_nJulianDate -= deltaDate; 
	return (*this); 
	}

int COXDate::operator-(COXDate date) const
	{
	ASSERT(m_nJulianDate != 0);			// date object must be initialized
	ASSERT(date.m_nJulianDate != 0);	// date object must be initialized
	return int(m_nJulianDate - date.m_nJulianDate);
	}

	
#ifdef _DEBUG
void COXDate::Dump(CDumpContext& dc) const
	{
	CObject::Dump(dc);
	dc << TEXT("\nm_nJulianDate : ") << m_nJulianDate;
	}

void COXDate::AssertValid() const
	{
	CObject::AssertValid();
	}
#endif

COXDate::~COXDate()
	{
	}

// protected:
	

// private:

// ==========================================================================

// Friend functions

CArchive& AFXAPI operator <<(CArchive& ar, COXDate date)
	{
	return ar << date.m_nJulianDate;
	}

CArchive& AFXAPI operator >>(CArchive& ar, COXDate& rDate)
	{
	return ar >>  rDate.m_nJulianDate;
	}

// ==========================================================================

// Non-member functions


BOOL ValidDate(int nYear, int nMonth, int nDay)
	{
	return( (COXDate::nEarliestYear <= nYear) && (1 <= nMonth) && (nMonth <= 12) && 
			(1 <= nDay) && (nDay <= 31));
	}
	
BOOL ExistingDate(int nYear, int nMonth, int nDay)
	{
	if (ValidDate(nYear, nMonth, nDay))
		{
		int nCheckYear, nCheckMonth, nCheckDay;
		COXDate testDate(nYear, nMonth, nDay);   
		testDate.GetDate(nCheckYear, nCheckMonth, nCheckDay);
		return ((nYear == nCheckYear) && (nMonth == nCheckMonth) && (nDay == nCheckDay));
		}
	else
		return(FALSE);
	}		
	
// ==========================================================================
