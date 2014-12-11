#define GL_SUCCESS 0
#define CUG_CODE_INDEXON 1 //used for extra indexing options
#include "ugctrl.h"
#include "d4all.hpp"

/***********************************************
************************************************/
class CUGCBDataSource: public CUGDataSource{

private:
	// defines

	// variables
	long			m_CurrentRec;	//current record
    long			m_CurrentRow;	//current row
    long            m_recordCount;  //count of records
	long			m_dataexist;    //does the datafile exist
	int				m_numOfIndexs;
	BOOL			m_indexOnFlag;
/****************************************
*****************************************/
	// Code base C++ classes
	Code4			m_codebase;
	Data4			m_datafile;
    FIELD4			*m_f4field;
	Field4  		*m_fieldsArray;
	Tag4	    	m_index;
	Tag4info    	*m_numOfTags,*m_tempNumOfTags;
	Index4		    m_indexOptions;
	TAG4INFO	    *m_wnd_Handle;

	char            *m_oldbuf;
	CString		    *m_indexNames;


/*****************************************
****************************************/

	// Functions

public:

	CUGCBDataSource();
	~CUGCBDataSource();

	//opening and closing
	virtual int Open(LPCSTR name, LPCSTR option);
	virtual int Create(LPCSTR name,FIELD4INFO *m_fieldNames,TAG4INFO *option);
	virtual int SetPassword(LPCSTR user,LPCSTR pass);
	virtual int Close();

	virtual int OnHitBottom(long numrows,long rowspast,long *rowsfound);

	//cell info
	virtual int GetRecord(int col,long row, CUGCell *cell);
	virtual int	GetCell(int col,long row,CUGCell *cell);
	virtual int	SetCell(int col,long row,CUGCell *cell);

	//add-update-clear
	virtual int AppendRow();
	virtual int InsertRow(long row);
	virtual int AppendCol();
	virtual int InsertCol(int col);
	virtual int DeleteRow(long row);
	virtual int DeleteCol(long col);
	virtual int DeleteCell(int col,long row);
	virtual int Empty();


	//finding sorting
	virtual int FindFirst(CString *string,int *col,long *row,long flags);
	virtual int FindNext(CString *string,int *col,long *row,int flags);
	virtual int SortBy(int col,int flags);
	virtual int SortBy(int *cols,int num,int flags);

	//options
	virtual int SetOption(int option,long param1,long param2);
	virtual int GetOption(int option,long& param1,long& param2);

	virtual long GetNumRows();
	virtual int GetNumCols();
	virtual int GetColName(int col,CString * string);
	virtual int GetColType(int col,int *type);//0-string 1-bool 2-short 3-long 4-float 
											//5-double 6-currency 7-data 8-time
										  //8-blob 9-graphic 10-ole
	virtual int AddIndex(LPCSTR indexName,LPCSTR sortOn);
	virtual int AddIndex(LPCSTR indexName,LPCSTR sortOn,LPCSTR filter,
				int unique,int descendOrAscend,TAG4INFO *tag);

};