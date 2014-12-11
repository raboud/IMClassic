// ==========================================================================
// 							Class Specification : COXDate
// ==========================================================================

// Header file : date.h

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved
                          
// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	YES	Derived from CObject

//	NO	Is a Cwnd.                     
//	NO	Two stage creation (constructor & Create())
//	NO	Has a message map
//	NO	Needs a resource (template)

//	YES	Persistent objects (saveable on disk)      
//	NO	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Desciption :         
//		This class encapsulates a date.                                              
//		Every input date must be valid, otherwise an assertion will occur.
//		Valid ranges for dates are:
//			Year :	1583 - ...			(see constant nEarliestYear)
//			Month :	1 - 12
//			Day :	1 - 31    
//		Input dates must not really exist.  E.g. 31st February 1990 is a valid date,
//		although it does not really exist.
//		Output dates are always valid and do always exist.
//		Special (non member) functions are provided to test Validity and Existance
//		of dates.
//
// Remark:
//		none

// Prerequisites (necessary conditions):
//		none

/////////////////////////////////////////////////////////////////////////////
#ifndef __DATE_H__
#define __DATE_H__


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"



class COXDate  : public CObject
{
// Data members -------------------------------------------------------------
public:             
	static const int nEarliestYear;
	// --- This is the earliest valid year of a COXDate object

	enum EDayOfWeek 
		{ 
		DOWSunday = 1, 
		DOWMonday, 
		DOWTuesday, 
		DOWWednesday,
		DOWThursday, 
		DOWFriday, 
		DOWSaturday 
		};
	// --- This enumerated type is used for the days of the week
					  
	
protected:
	DWORD m_nJulianDate;
	static const DWORD nEarliestJulianDate;

private:
	
// Member functions ---------------------------------------------------------
public:     
	// Construction
	
	COXDate();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Default contructor of an (unitialized) date
	//				This date must be initialized before any further
	//				computations can occur.
	
	COXDate(int nYear, int nMonth, int nDay);
	// --- In :	nYear :	full year (e.g. 1990 and not 90)
	//			nMonth: 
	//			nDay :
	// --- Out : 
	// --- Returns :
	// --- Effect : Contruction and initialisation of a date
	
    COXDate(const CTime& timeSrc);
	// --- In :	timeSrc
	// --- Out : 
	// --- Returns :
	// --- Effect : Contruction and initialisation of a date via a CTime object.
	//				Only the date information from timeSrc is used and the time
	//				information is discarded.
                
    COXDate(const COXDate& dateSrc);
	// copy operator
	// --- In :	dateSrc : Date object which will be copied
	// --- Out : 
	// --- Returns :
	// --- Effect : Copy contruction.

    // Access functions
    
	void SetDate(int nYear, int nMonth, int nDay);
	// --- In :	nYear :	full year (e.g. 1990 and not 90)
	//			nMonth: 
	//			nDay :
	// --- Out : 
	// --- Returns :
	// --- Effect : Reinitialisation of the date with new values
	
	int GetYear() const;
	// --- In :
	// --- Out : 
	// --- Returns : The year of that date
	
	int GetMonth() const;
	// --- In :
	// --- Out : 
	// --- Returns : The mont of that date
	
	int GetDay() const;
	// --- In :
	// --- Out : 
	// --- Returns : The day of that date
	
	void GetDate(int& nYear, int& nMonth, int& nDay) const;
	// --- In :
	// --- Out:	nYear :	full year (e.g. 1990 and not 90)
	//			nMonth: 
	//			nDay :
	// --- Returns : 
	// --- Effect : With this function you can get the entire date in one call
	
	EDayOfWeek GetDayOfWeek();
	// --- In :
	// --- Out:
	// --- Returns: The day of the week (Sunday, Monday, ...)
	// --- Effect : 
	
	// Operators
	
	COXDate& operator=(const COXDate& dateSrc);
	// --- In :	dataSrc : Date object which will be assign to 'this' date object
	// --- Out:
	// --- Returns: 
	// --- Effect : Assignment operator
	
	BOOL operator==(COXDate date) const;
	BOOL operator!=(COXDate date) const;
	BOOL operator<(COXDate date) const;
	BOOL operator>(COXDate date) const;
	BOOL operator<=(COXDate date) const;
	BOOL operator>=(COXDate date) const;
	// --- In :	data : Second date object to which the object will be compared
	// --- Out:
	// --- Returns: FALSE or TRUE
	// --- Effect : Comparison operator
	                                    
	COXDate operator+(int deltaDate) const;
	// --- In :	deltaDate : The number of days which must be added to the date
	// --- Out:
	// --- Returns: The new date (after addistion)
	// --- Effect : Addition operator
	
	const COXDate& operator+=(int deltaDate);
	// --- In :	deltaDate : The number of days which must be added to the date
	// --- Out:
	// --- Returns: The date (after addistion)
	// --- Effect : Addition assignment operator
	
	COXDate operator-(int deltaDate) const;
	// --- In :	deltaDate : The number of days which must be substracted from the date
	// --- Out:
	// --- Returns: The new date (after substraction)
	// --- Effect : Substraction operator
	
	const COXDate& operator-=(int deltaDate);
	// --- In :	deltaDate : The number of days which must be substracted from the date
	// --- Out:
	// --- Returns: The date (after substraction)
	// --- Effect : Substraction assignment operator
	
	int operator-(COXDate date) const;
	// --- In :	date : The second date
	// --- Out:
	// --- Returns: The number of days between the object and the second date.
	//				This can be negative.
	// --- Effect : Substraction operator

#ifdef _DEBUG
	virtual void Dump(CDumpContext&) const;
	virtual void AssertValid() const;
#endif //_DEBUG

	virtual ~COXDate();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of object

	// Friend functions
	friend CArchive& AFXAPI operator<<(CArchive& ar, COXDate date);
	friend CArchive& AFXAPI operator>>(CArchive& ar, COXDate& rdate);
		
protected:      

private:
                   
};

// ==========================================================================

// Non-member functions

BOOL ValidDate(int nYear, int nMonth, int nDay);
	// --- In :	nYear :	full year (e.g. 1990 and not 90)
	//			nMonth: 
	//			nDay :
	// --- Out : 
	// --- Returns : Whether the parameters fall in their valid range
	//				 nYear :    1583 - ...
	//				 nMonth : 	1 - 12
	//				 nDay : 	1 - 31
	//				 Whether the date really exists is not checked
	// --- Effect :
	
BOOL ExistingDate(int nYear, int nMonth, int nDay);
	// --- In :	nYear :	full year (e.g. 1990 and not 90)
	//			nMonth: 
	//			nDay :
	// --- Out : 
	// --- Returns : Whether the date really exists.
	//				 e.g. 1st January 1990 		exists
	//					  31st February 1990 	does NOT exist
	//					  55th March 1990 		does NOT exist
	// --- Effect :

#endif
// ==========================================================================
