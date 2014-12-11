// CFIDatabase.h: interface for the CFIRecordset class.
//
// Author:		lindapeng ( lindapeng@163.net )
//
// Description:	This class is especially for working with parameterized sql and store procedures
//				which return record sets.
//
// Using:		(1) Prepare the SQL statement or stored procedure,such as PrepareSQL("select * from table where no > ?")
//					or PrepareStoreProcedure ("procedure name").
//				(2) Set value for each input parameters, such as SetParam_Long(0,100),SetParam_Double(1,12.34).
//					Keep in mind the field number of stored procedure is starting from 1 not 0, because the 0 is 
//					for return value from store procedure.
//				(3) Open the statement, such as Open("select * from table where no > ?") or Open("{? = call procudure(?,?)}").
//				(4) Do a loop to fetch each row.
//
// Thanks:		Great thanks to Stefan Tchekanov  (stefant@iname.com) who has written CODBCRecordset and CDBField class for
//				fetching rows from non parameterized SQL statment.Some of my codes were taken from the two classes.
//
// Rights:		It can be used or distributed or modified freely for personal use. If you think it helps you with your
//				work, it will be nice to let me know with a mail.
////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYRECORDSET_H__3B9B8908_DCC0_43E7_B4FF_A0D0A873FDF8__INCLUDED_)
#define AFX_MYRECORDSET_H__3B9B8908_DCC0_43E7_B4FF_A0D0A873FDF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxdb.h>
#include <afxtempl.h>
#include "catsets.h"

struct CParamInfo
{
	CString			m_strParamName;
	int				m_nColType;
	int				m_nDataType;
	int				m_nLength;
	int				m_nDecimalDigits;
};

class	CDBField : public CDBVariant 
{
public:
	CDBField();
	virtual ~CDBField();

	bool			AsBool()	const;
	unsigned char	AsChar()	const;
	short			AsShort()	const;
	int				AsInt()		const;
	long			AsLong()	const;
	float			AsFloat()	const;
	double			AsDouble()	const;
	COleDateTime	AsDate()	const;
	CString			AsString();
	CLongBinary*	AsBinary()	const;
	
	bool			IsNull()	const;
	void			SetNull( bool bIsNull );
	void			BinaryToString( CString& cStr, bool bExpand );

	CString			m_strFieldName;
	bool			m_bIsNull;
};

class CCFIRecordset : public CRecordset  
{
public:
	CCFIRecordset(CDatabase* pDatabase);
	virtual ~CCFIRecordset();

	bool			SafeOpen(CString strSql);
	BOOL			Open( CString strSQL,UINT nOpenType = AFX_DB_USE_DEFAULT_TYPE, DWORD dwOptions = 0 );
	void			Move( long nRows, WORD wFetchType = SQL_FETCH_RELATIVE );
	void			Close();

	bool			GetBool( int nCol );
	unsigned char	GetChar( int nCol );
	short			GetShort( int nCol );
	int				GetInt( int nCol );
	long			GetLong( int nCol );
	float			GetFloat( int nCol );
	double			GetDouble( int nCol );
	COleDateTime	GetDate( int nCol );
	CString			GetString( int nCol );
	CLongBinary*	GetBinary( int nCol );

	bool			PrepareStoreProcedure(CString strStoreProcedureName);
	bool			PrepareSQL(CString strSQL);

	void			SetParam_Long(UINT nParamId,long nParamValue);
	void			SetParam_Float(UINT nParamId,float fltParamValue);
	void			SetParam_Double(UINT nParamId,double dblParamValue);
	void			SetParam_String(UINT nParamId,CString strParamValue);
	void			SetParam_DateTime(UINT nParamId,TIMESTAMP_STRUCT dtParamValue);
	void			SetParam_Bool(UINT nParamId,BOOL bParamValue);

	BOOL			GetParam_Bool(UINT nParamId);
	int				GetParam_Long(UINT nParamId);
	float			GetParam_Float(UINT nParamId);
	double			GetParam_Double(UINT nParamId);
	TIMESTAMP_STRUCT	GetParam_DateTime(UINT nParamId);

	int				GetFieldID( CString strName );
	CString			GetFieldName( int nID );
	CString			GetParamName( int nParamId);
	CDBField&		Field( int nField ); 

private:
	CDatabase*		m_pDatabase;
	CDBField*		m_pFields;			//	Storage for fields
	CDBField*		m_pParams;			//	storage for params
	bool			m_bNotLoadedFieldsMap;	//	Is field names map still not loaded
	void			LoadFieldNamesMap();
	int				m_nReturnParam;
	int				m_nInputParams;
	int				m_nOutputParams;
	int				m_nInputOutputParams;
	CMap<int,int,CString,CString> m_mapField;
	CMap<int,int,CParamInfo,CParamInfo> m_mapParam;
	
	void			MakeFieldMap();
	virtual	void	DoFieldExchange( CFieldExchange* pFX );
	void			SetDBFieldType( CDBVariant& varValue, CODBCFieldInfo& fi );
	short			SQLType2CType( short nSQLType );


};

#endif // !defined(AFX_MYRECORDSET_H__3B9B8908_DCC0_43E7_B4FF_A0D0A873FDF8__INCLUDED_)
