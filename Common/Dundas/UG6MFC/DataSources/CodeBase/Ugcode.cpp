/***************************************************
Ultimate Grid 97 for MFC
Dundas Software Ltd. 1994-1999

  CodeBase DataSource


  Standard Return Values: UG_SUCCESS - success (0)
						  UG_NA		 - not available (-1)
						  1 and up   - error codes
****************************************************/
#include "stdafx.h"
#include "d4all.hpp"
#include "UGCtrl.h"
#include "UGcode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/***************************************************
Constructor
	Init all data here
****************************************************/
CUGCBDataSource::CUGCBDataSource(){
	m_CurrentRow	= 1;
	m_numOfIndexs	= -1;
	m_indexOnFlag   = TRUE;

    m_indexNames    = NULL;
	m_fieldsArray   = NULL;
	m_numOfTags     = NULL;

    m_recordCount   = -1;
}
/***************************************************
Destructor
	Perform clean up here
****************************************************/
CUGCBDataSource::~CUGCBDataSource(){
	Close();
}

/***************************************************
********** creating, opening and closing ***********
****************************************************/

/***************************************************
Create
	Override this function to create a database in a 
	a data source
return
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CUGCBDataSource::Create(LPCSTR name,FIELD4INFO *m_fieldNames,TAG4INFO *option)
{

	m_datafile.create(m_codebase,name,m_fieldNames,option);
	
	if(!m_datafile.isValid()){
		if(m_fieldsArray != NULL){
			delete m_fieldsArray;
			delete m_indexNames;
		}
		return 0;
	}

	m_numOfTags = new	Tag4info(m_datafile);

	m_fieldsArray = new Field4[m_datafile.numFields()];
	m_indexNames  = new CString[m_numOfTags->numTags()];
	
	CString names;

	for(int x=0;x<m_datafile.numFields();x++){
		GetColName(x,&names);
		m_fieldsArray[x].init(m_datafile,names);
	}

	int count = 0;
	m_index.initFirst(m_datafile);
	do{
		if(!m_index.isValid())
			break;
		
		m_indexNames[count] = m_index.alias();
		count++;
		m_index.initNext();
		m_numOfIndexs++;

	}while(m_index.isValid());


	m_datafile.select(m_indexNames[0]);
	
	return UG_SUCCESS;

}
/***************************************************
Open
	Override this function to provide file loading to
	a data source
return
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CUGCBDataSource::Open(LPCSTR name,LPCSTR option){
	m_codebase.errOpen = 0;

	m_dataexist = m_datafile.open(m_codebase,name);


	if(!m_datafile.isValid()){
        TRACE("ERROR %ld:  Failed to open %s\n", m_dataexist, name);
		return 1;
	}

	m_numOfTags = new	Tag4info(m_datafile);

	m_fieldsArray = new Field4[m_datafile.numFields()];
	int nt = m_numOfTags->numTags();
	m_indexNames  = new CString[m_numOfTags->numTags()];

	CString names;

	for(int x=0;x<m_datafile.numFields();x++){
		GetColName(x,&names);
		m_fieldsArray[x].init(m_datafile,names);
	}

	int count = 0;
	m_index.initFirst(m_datafile);
	do{
		if(!m_index.isValid())
			break;
		
		m_indexNames[count] = m_index.alias();
		count++;
		m_index.initNext();
		m_numOfIndexs++;

	}while(m_index.isValid());

    m_recordCount = m_datafile.recCount();

	return UG_SUCCESS;
 }
/***************************************************
SetPassword
	Override this function if a password is needed 
	for the data source
return
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CUGCBDataSource::SetPassword(LPCSTR user,LPCSTR pass){
	return UG_NA;
}
/***************************************************
Close
	Override this function if a close command is needed
	for the data source
return
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CUGCBDataSource::Close(){

	if(m_datafile.isValid()){
    	m_datafile.close();
	}

	m_codebase.closeAll();
	m_codebase.initUndo();
    
    if(m_indexNames != NULL)
	    delete[] m_indexNames;
    if(m_fieldsArray != NULL)
    	delete[] m_fieldsArray;
    if(m_numOfTags != NULL)
	    delete m_numOfTags;

	return UG_SUCCESS;
}
/***************************************************
************ row and col info **********************
****************************************************/

/***************************************************
GetNumRows
	Returns the number of rows of data available
return
	UG_NA		not available
	number of rows
****************************************************/
long CUGCBDataSource::GetNumRows(){

    m_recordCount = m_datafile.recCount();

    if(m_recordCount < 0)
        return UG_NA;

   	return m_recordCount;
}
/***************************************************
GetNumCols
	Returns the number of Columns of data avialable
return
	UG_NA		not available
	number of cols
****************************************************/
int CUGCBDataSource::GetNumCols(){

return m_datafile.numFields();
}
/***************************************************
GetColName
	Returns the name of a column
return
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CUGCBDataSource::GetColName(int col,CString * string){

	if(col <0 || col >=m_datafile.numFields())
		return 1;

	m_f4field = d4fieldJ(m_datafile,col+1);
	*string = m_f4field->name;

	return UG_SUCCESS;

}
/***************************************************
GetColType

	Returns the default data type of a column
	type =	0-string 1-bool 2-short 3-long 4-float 
			5-double 6-currency 7-data 8-time
			8-blob 9-graphic 10-ole

return
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CUGCBDataSource::GetColType(int col,int *type){
	return UG_NA;
}
	
/***************************************************
************* add-update-clear *********************
****************************************************/

/***************************************************
AppendRow
	Appends a new row at the end of the current data
	in the data source
return
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CUGCBDataSource::AppendRow(){

	m_datafile.append();

    GetNumRows();

	return UG_SUCCESS;
}
/***************************************************
InsertRow
	Inserts a row at the specified position in the
	current data
return
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CUGCBDataSource::InsertRow(long row){
	return UG_NA;
}
/***************************************************
AppendCol
	Appends a column to the end of the current data
	in the data source
return
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CUGCBDataSource::AppendCol(){
	return UG_NA;
}
/***************************************************
InsertCol
	Inserts a new column at the specified position 
	in the data
return
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CUGCBDataSource::InsertCol(int col){
	return UG_NA;
}
/***************************************************
DeleteRow
	Deletes the specified row from the data in the 
	data source
return
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CUGCBDataSource::DeleteRow(long row){

	if(row+1 > m_recordCount)
		return 1;
	
	if(row+1<=m_recordCount){

		GetRecord(0,row+1,NULL);
		m_datafile.deleteRec();
		m_datafile.pack();
		m_CurrentRow = 1;
		m_datafile.top();
        GetNumRows();
	}		
		
	else
		return UG_NA;


	return UG_SUCCESS;
}
/***************************************************
DeleteCol
	Deletes the specified column of data from the 
	data in the data source
return
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CUGCBDataSource::DeleteCol(long col){
	return UG_NA;
}
/***************************************************
Empty 
	Empties all the data in the data source
return
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CUGCBDataSource::Empty(){
	return UG_NA;
}
/***************************************************
Delete 
	Deletes the specified cell from the data in the
	data source
return
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CUGCBDataSource::DeleteCell(int col,long row){
 	return UG_NA;
}
/***************************************************
****************** cell info ***********************
****************************************************/

/***************************************************
GetRecord
	A private function that is used to keep track of
	data loading for the grid.
	  
	return
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CUGCBDataSource::GetRecord(int col,long row, CUGCell *cell){

	if(row > m_recordCount)
		return 1;

	if(row == 1){
		m_datafile.top();
		m_CurrentRow = 1;
	}
    else if ( row == m_recordCount )
    {
        m_datafile.bottom();
        m_CurrentRow = GetNumRows();
    }
    else if(m_CurrentRow != row){

        int nSkipRows = row - m_CurrentRow;

        m_datafile.skip( nSkipRows ); // negative values ok
        m_CurrentRow += nSkipRows;
	}
	return UG_SUCCESS;

}	
/***************************************************
GetCell
	Updates the given cell with 'set' information for
	the specified cell. (only information that is 'set'
	should be updated, since every data property has an
	'unset' state).
return
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CUGCBDataSource::GetCell(int col,long row,CUGCell *cell){

    static char buf2[100];

    if(row < 0){
        CString str;
        GetColName(col,&str);
        cell->SetText(str);
        return UG_SUCCESS;
    }

	if(col < 0){
		if(m_ctrl->GetCurrentRow() == row){
			cell->SetCellType(UGCT_ARROW);
			cell->SetCellTypeEx(UGCT_ARROWRIGHT);
		}
		return 1;
	}
    
    if(GetRecord(col,row+1,cell) == 1)
			return 1;

	else if(row+1<=m_recordCount){
	
		m_f4field = d4fieldJ(m_datafile,col+1);
		cell->SetText(f4str(m_f4field));
		
		return UG_SUCCESS;
	}

	return UG_NA;
}

/***************************************************
SetCell
	Sets the cell - including all 'unset' information

return
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CUGCBDataSource::SetCell(int col,long row,CUGCell *cell){

	if (m_dataexist < GL_SUCCESS)
		return UG_NA;

	if(col < 0 )
		return 1;
		
	if(row+1<=m_recordCount && m_recordCount != 0){

		GetRecord(col,row+1,cell);

		m_f4field = d4fieldJ(m_datafile,col+1);
		CString string;
		cell->GetText(&string);
		f4assign(m_f4field,string);

		return UG_SUCCESS;
	}		
	else
	{
		GetRecord(col,row+1,cell);

		m_datafile.lockAll();

		for(int x=1;x<=m_datafile.numFields();x++){
		m_f4field = d4fieldJ(m_datafile,x);
		f4assign(m_f4field," ");
		}
		
		m_f4field = d4fieldJ(m_datafile,col+1);
		CString string;
		cell->GetText(&string);
		f4assign(m_f4field,string);
	
		m_datafile.append();
		m_datafile.unlock();

		m_CurrentRow = 1;
		m_datafile.top();
	
		return UG_SUCCESS;
		
	}
	
	return UG_NA;
	
}

/***************************************************
****************  finding sorting ******************
****************************************************/

/***************************************************
FindFirst
	Returns the first row that contained the specified 
	string in the specified column
return
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CUGCBDataSource::FindFirst(CString *string,int *col,long *row,long flags){
	// TODO: position grid and record at first cell
	// or first cell in column if flags & UG_FIND_ALLCOLUMNS
	// User best to GotoRow(0) then make this call.
	return FindNext(string, col, row, flags);

}

/***************************************************
FindNext
	Returns the next row/col that contained the specified 
	string in the specified column.  Designed to work
    with the grid controls built in FindDialog.
return
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CUGCBDataSource::FindNext(CString *string, int *col, long *row, int flags){

	if ( 0 > m_recordCount)
        return UG_NA;

	int  retval = UG_SUCCESS;


	long nStartRow = m_ctrl->GetCurrentRow();
	long nSearchRow = nStartRow;

	int  nMaxCol = GetNumCols()-1;

	int  nStartColumn = *col;	
	int  nSearchColumn = *col;		
	CUGCell cell;
	CString strCell;

	BOOL bCheckForWrap = FALSE;		// as soon as we're past the raw start +2 we 
									// can start checking for wrap.  This would 
									// be easier with a counter (X recs processed)
									// checked against a record count.
	
	long nSearchCount = 0;			// Help! I've wrapped and I can't find the text!
									// Must be > 1 to enter wrap detection code

	long nRecs = m_recordCount;
	
	if(-1 == nRecs)		// error getting number of records
		return UG_NA;

	CWaitCursor	cw;					// a nice touch...


	while(1) {


		// positioning... a bit complex, but all in one place.
		if(UG_FIND_ALLCOLUMNS&flags) {
			if(UG_FIND_UP&flags) {
				nSearchColumn--;
				if(nSearchColumn < 0) {
					nSearchColumn = nMaxCol;
					nSearchRow--;
					if(nSearchRow < 0) {
						nSearchRow = nRecs-1;
					}
					// wrap code - have we looped longer than nRecs?
					if(nSearchCount > nRecs+1) {
						retval = UG_NA;
						break;
					}
					else {
						nSearchCount++;
					}
				}
			}
			else {  // finding downward...
				nSearchColumn++;
				if(nSearchColumn > nMaxCol) {
					nSearchColumn = 0;
					nSearchRow++;
					if(nSearchRow > nRecs-1) {
						nSearchRow = 0;
					}
					// wrap code - have we looped longer than nRecs?
					if(nSearchCount > nRecs+1) {
						retval = UG_NA;
						break;
					}
					else {
						nSearchCount++;
					}
				}
			}
		}
		else {
		
			if(UG_FIND_UP&flags) {
				nSearchRow--;
				if(nSearchRow < 0) {
					nSearchRow = nRecs-1;
				}

				// wrap code - have we looped longer than nRecs?
				if(nSearchCount > nRecs+1) {
					retval = UG_NA;
					break;
				}
				else {
					nSearchCount++;
				}
			}
			else {
				nSearchRow++;
				if(nSearchRow > nRecs-1) {
					nSearchRow = 0;
				}

				// wrap code - have we looped longer than nRecs?
				if(nSearchCount > nRecs+1) {
					retval = UG_NA;
					break;
				}
				else {
					nSearchCount++;
				}
			}

		}

		

		
		if(GetCell(nSearchColumn, nSearchRow, &cell) != UG_SUCCESS) { 
			TRACE(_T("Unexpected return code from GetCell in FindNext"));
			retval = UG_NA;			// no more data.
			break;
		}

		cell.GetText(&strCell);		// get the text.

		if(UG_FIND_CASEINSENSITIVE&flags) {
			// make both upper case
			string->MakeUpper();
			strCell.MakeUpper();
		}

		if(UG_FIND_PARTIAL&flags) {
			if(strCell.Find(*string) != -1) {		// compare partial
				*col = nSearchColumn;
				*row = nSearchRow;
				retval = UG_SUCCESS;
				break;
			}
		}
		else {
			if(strCell == *string) {					// match whole cell
				*col = nSearchColumn;
				*row = nSearchRow;
				retval = UG_SUCCESS;
				break;
			}
		}
	}		
	
	return retval;

}
/***************************************************
SortBy
	Sorts (or m_indexes) the data by the specified column

return
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CUGCBDataSource::SortBy(int col, int flags){
	int count = 0;
	CString field_on;

	CString field_name = m_fieldsArray[col].name();

	m_index.initFirst(m_datafile);

	try{
		field_on = m_index.expr();
	}
	catch(...){
		MessageBox(NULL,"This file does not have an\nindex associated with it.","ERROR:",MB_ICONEXCLAMATION|MB_OK);
		return 1;
	}
	
	int nt = m_numOfTags->numTags();
	
	while(field_on.CompareNoCase(field_name)){
		
		m_index.initNext();
		if(!m_index.isValid()){
			if(m_indexOnFlag == TRUE){
				if(MessageBox(NULL,"This Field does not have an Index\nDo you wish to create one?",					"NOTICE:",MB_ICONINFORMATION|MB_OKCANCEL) == IDOK){
					field_name.MakeUpper();
					AddIndex(field_name,field_name);
					m_datafile.select(m_indexNames[count+1]);
					return 1;
				}
				else
					return 1;
			}
			else
				return 1;
		}

		field_on = m_index.expr();
		count++;
	}
	m_datafile.select(m_indexNames[count]);
	return UG_SUCCESS;
}
/***************************************************
SortBy
	Sorts the data starting with the specified column
	then sub-sorts it up to 'num' cols
return
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CUGCBDataSource::SortBy(int *cols,int num, int flags){
	return SortBy(*cols, flags);
}

/***************************************************
********************* options **********************
****************************************************/

/***************************************************
SetOption
	Datasource dependant function. Used to set data source
	specific information and modes of operation
return
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CUGCBDataSource::SetOption(int option,long param1,long param2){

	if(option == CUG_CODE_INDEXON){
		m_indexOnFlag = param1;
		return UG_SUCCESS;
	}
	return UG_NA;
}
/***************************************************
GetOption
	Datasource dependant function. Used to get data source
	specific information and modes of operation
return
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CUGCBDataSource::GetOption(int option,long& param1,long& param2){
	return UG_NA;
}
/****************************************************/
/***************************************************
AddIndex
	AddIndex adds a new m_index to the current production m_index.
	The first overloaded function is a basic AddIndex function,
	taking only the name and which field to sort on. Its overloaded
	partner takes 5 parameters.
return
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CUGCBDataSource::AddIndex(LPCSTR m_indexName,LPCSTR sortOn){

	AddIndex(m_indexName,sortOn,NULL,0,0,NULL);

	return UG_SUCCESS;
}
int CUGCBDataSource::AddIndex(LPCSTR m_indexName,LPCSTR sortOn,LPCSTR filter,
			  int unique,int descendOrAscend,TAG4INFO *tag){

	m_indexOptions.init(m_datafile,NULL);

	for(int x=0;x<=m_numOfIndexs;x++){
		int check = x;
		int who = m_numOfIndexs;
		if(!m_indexNames[x].Compare(m_indexName))
			return 1;
	}


	m_numOfTags->free();
	m_numOfTags->add(m_indexName,sortOn,filter,unique,descendOrAscend);


	if(!m_indexOptions.isValid())
		return 1;
	
	m_wnd_Handle = m_numOfTags->tags();

	m_indexOptions.tagAdd(m_wnd_Handle);

	m_numOfTags->free();	
	
	delete		m_numOfTags;
	delete[]	m_indexNames;

	m_numOfTags	= new	Tag4info(m_datafile);
	m_indexNames  = new CString[m_numOfTags->numTags()];

	int count = 0;
	m_numOfIndexs =-1;

	m_index.initFirst(m_datafile);
	do{
		if(!m_index.isValid())
			break;
		
		m_indexNames[count] = m_index.alias();
		count++;
		m_index.initNext();
		m_numOfIndexs++;

	}while(m_index.isValid());

	int nt = m_numOfTags->numTags();

return UG_SUCCESS;
}

/***************************************************
****************************************************/
int CUGCBDataSource::OnHitBottom(long numrows,long rowspast,long *rowsfound){
	return UG_NA;
}
