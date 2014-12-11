// CFIRecordset.cpp: implementation of the CCFIRecordset class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CFIRecordset.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCFIRecordset::CCFIRecordset(CDatabase* pDatabase):CRecordset(pDatabase)
{
	m_pDatabase = pDatabase;
	m_pFields = NULL;
	m_pParams = NULL;
	m_nParams = 0;
	m_nInputParams = 0;
	m_nOutputParams = 0;
	m_nInputOutputParams = 0;
	m_nReturnParam = 0;
}

CCFIRecordset::~CCFIRecordset()
{
	if( m_pFields != NULL )
		delete[]	m_pFields;
	m_pFields = NULL;

	if(m_pParams)
		delete[] m_pParams;
	m_pParams = NULL;
}

bool CCFIRecordset::SafeOpen(CString Sql)
{
	int length=Sql.GetLength();
	if(length==0)
	{
		AfxMessageBox("SQL String is 0 Length!");
		return false;
	}
	if(IsOpen())
		Close();
	try
	{
		Open(Sql,AFX_DB_USE_DEFAULT_TYPE,CRecordset::snapshot);
	}
	catch(CDBException *E)
	{
#ifdef _DEBUG
		AfxMessageBox(Sql);
#endif
		AfxMessageBox(E->m_strError);
		return false;
	}
	return true;
}

BOOL	CCFIRecordset::Open( CString strSQL,	UINT nOpenType,	DWORD dwOptions )
{
	m_nFields = 255;
	m_bNotLoadedFieldsMap = true;
	if(IsOpen())
		Close();
	return CRecordset::Open( nOpenType, (LPCTSTR)strSQL,dwOptions );
}

void	CCFIRecordset::MakeFieldMap()
{
	m_mapField.RemoveAll();
	int	nFields = m_nFields = GetODBCFieldCount();
	
	if(m_pFields)
		delete[] m_pFields;
	m_pFields = new CDBField[ m_nFields ];

	CODBCFieldInfo	fi;
	CString			strName;
	for( int i = 0; i < nFields; i++ ) 
	{
		GetODBCFieldInfo( i, fi );
		SetDBFieldType( m_pFields[i], fi );
		
		//	Set the field name
		fi.m_strName.MakeUpper();
		strName = fi.m_strName;

		//	Make different field names for the fields with
		//	equal names.
		int	fldCount = 1;
		while( GetFieldID( strName ) != -1 ) 
		{
			fldCount++;
			strName.Format( "%s%d", fi.m_strName, fldCount );
		}
		m_pFields[i].m_strFieldName = strName;
		m_mapField.SetAt(i,strName);
	}
}

short CCFIRecordset::SQLType2CType( short nSQLType )
{
	short nFieldType = 0;

	switch( nSQLType )
	{
	case SQL_BIT:
		nFieldType = SQL_C_BIT;
		break;

	case SQL_TINYINT:
		nFieldType = SQL_C_UTINYINT;
		break;

	case SQL_SMALLINT:
		nFieldType = SQL_C_SSHORT;
		break;

	case SQL_INTEGER:
		nFieldType = SQL_C_SLONG;
		break;

	case SQL_REAL:
		nFieldType = SQL_C_FLOAT;
		break;

	case SQL_FLOAT:
	case SQL_DOUBLE:
	case SQL_NUMERIC:
	case SQL_DECIMAL:
		nFieldType = SQL_C_DOUBLE;
		break;

	case SQL_DATE:
	case SQL_TIME:
	case SQL_TIMESTAMP:
		nFieldType = SQL_C_TIMESTAMP;
		break;

	case SQL_BIGINT:
	case SQL_CHAR:
	case SQL_VARCHAR:
	case SQL_WCHAR:
	case SQL_WVARCHAR:
		nFieldType = SQL_C_CHAR;
		break;
	case SQL_WLONGVARCHAR:
	case SQL_LONGVARCHAR:
	case SQL_BINARY:
	case SQL_VARBINARY:
	case SQL_LONGVARBINARY:
		nFieldType = SQL_C_BINARY;
		break;

	default:
		ASSERT( FALSE );
	}
	return	nFieldType;
}

void	CCFIRecordset::SetDBFieldType( CDBVariant& varValue, CODBCFieldInfo& fi )
{
	int	nFieldType = SQLType2CType( fi.m_nSQLType );
	switch( nFieldType )
	{
	case SQL_C_BIT:
		varValue.m_dwType = DBVT_BOOL;
		break;

	case SQL_C_UTINYINT:
		varValue.m_dwType = DBVT_UCHAR;
		break;

	case SQL_C_SSHORT:
	case SQL_C_SLONG:
		varValue.m_dwType = DBVT_LONG;
		break;

	case SQL_C_FLOAT:
		varValue.m_dwType = DBVT_SINGLE;
		break;

	case SQL_C_DOUBLE:
		varValue.m_dwType = DBVT_DOUBLE;
		break;

	case SQL_C_TIMESTAMP:
		varValue.m_pdate = new TIMESTAMP_STRUCT;
		varValue.m_dwType = DBVT_DATE;
		break;

	case SQL_C_CHAR:
		varValue.m_pstring = new CString;
		varValue.m_dwType = DBVT_STRING;
		break;

	case SQL_C_BINARY:
		varValue.m_pbinary = new CLongBinary;
		varValue.m_dwType = DBVT_BINARY;
		break;

	default:
		//	Unknown data type
		ASSERT( FALSE );
	}
}

void	CCFIRecordset::Move( long nRows, WORD wFetchType /*= SQL_FETCH_RELATIVE*/ )
{
	if( m_bNotLoadedFieldsMap )
	{
		MakeFieldMap();
		m_bNotLoadedFieldsMap = false;
	}
	CRecordset::Move( nRows, wFetchType );
}
////////////////////////////////////////////////////////////////

void	CCFIRecordset::Close()
{
	CRecordset::Close();
	m_nInputParams=0;
	m_nOutputParams=0;
	m_nInputOutputParams=0;
	m_nReturnParam=0;
	m_nParams = 0;
	m_mapParam.RemoveAll();
	m_mapField.RemoveAll();
	delete[] m_pParams;
	m_pParams = NULL;
	delete[] m_pFields;
	m_pFields = NULL;
}

int	CCFIRecordset::GetFieldID( CString strName )
{
	strName.MakeUpper();
	CString s1;
	for (int i=0;m_mapField.Lookup( i, s1 ) ;i++)
	{
		if(s1==strName)
			return i;
	}
	return -1;
}

CString	CCFIRecordset::GetFieldName( int nField )
{
	ASSERT( nField >= 0 );
	ASSERT( nField < GetODBCFieldCount() );
	CString strFieldName;
	if(m_mapField.Lookup(nField,strFieldName))
		return strFieldName;
	else
	{
		strFieldName.Empty();
		return strFieldName;
	}
}

CString	CCFIRecordset::GetParamName( int nParamId )
{
	ASSERT( nParamId >= 0 );

	CString		cName;
	CParamInfo paramInfo;
	if(m_mapParam.Lookup(nParamId,paramInfo))
		return paramInfo.m_strParamName;
	else
	{
		cName.Empty();
		return	cName;
	}
}

void CCFIRecordset::DoFieldExchange( CFieldExchange* pFX )
{

	pFX->SetFieldType( CFieldExchange::outputColumn );
	CString		strFieldName;
	for( UINT i = 0; i < m_nFields && pFX->m_nOperation!=CFieldExchange::BindParam && pFX->m_nOperation!=CFieldExchange::RebindParam; i++ )
	{
		strFieldName.Format( "[%s]", GetFieldName(i) );
		switch( m_pFields[i].m_dwType )
		{
		case	DBVT_NULL:
					break;
		case	DBVT_BOOL:
					RFX_Bool( pFX, strFieldName, m_pFields[i].m_boolVal );
					break;
		case	DBVT_UCHAR:
					RFX_Byte( pFX, strFieldName, m_pFields[i].m_chVal );
					break;
		case	DBVT_SHORT:
					m_pFields[i].m_dwType = DBVT_LONG;
					RFX_Long( pFX, strFieldName, m_pFields[i].m_lVal );
					break;
		case	DBVT_LONG:
					RFX_Long( pFX, strFieldName, m_pFields[i].m_lVal );
					break;
		case	DBVT_SINGLE:
					RFX_Single( pFX, strFieldName, m_pFields[i].m_fltVal );
					break;
		case	DBVT_DOUBLE:
					RFX_Double( pFX, strFieldName, m_pFields[i].m_dblVal );
					break;
		case	DBVT_DATE:
					RFX_Date( pFX, strFieldName, *m_pFields[i].m_pdate );
					break;
		case	DBVT_STRING:
				{
					CODBCFieldInfo	fi;
					GetODBCFieldInfo( i, fi );
					RFX_Text( pFX, strFieldName, *m_pFields[i].m_pstring, fi.m_nPrecision );
					break;
				}
		case	DBVT_BINARY:
					RFX_LongBinary( pFX, strFieldName, *(m_pFields[i].m_pbinary) );
					break;
		default:
			ASSERT( FALSE );
		}
		m_pFields[i].SetNull( FALSE != IsFieldStatusNull( i ) );
	}

	if(m_nReturnParam>0 )
	{
		pFX->SetFieldType( CFieldExchange::outputParam );
		RFX_Long( pFX, _T("[@RETURN_VALUE]"), m_pParams[0].m_lVal );
	}
	
	CString paramName;
	int nLength;
	if(m_nInputParams>0 )
	{
		pFX->SetFieldType( CFieldExchange::inputParam );
		for( i=0;i<m_nParams;i++)
		{
			if(m_mapParam[i].m_nColType != SQL_PARAM_INPUT)
				continue;
			paramName=m_mapParam[i].m_strParamName;
			nLength=m_mapParam[i].m_nLength;
			switch( m_pParams[i].m_dwType )
			{
				case	DBVT_NULL:
							break;
				case	DBVT_BOOL:
							RFX_Bool( pFX, paramName, m_pParams[i].m_boolVal );
							break;
				case	DBVT_UCHAR:
							RFX_Byte( pFX, paramName, m_pParams[i].m_chVal );
							break;
				case	DBVT_SHORT:
							m_pParams[i].m_dwType = DBVT_LONG;
							RFX_Long( pFX, paramName, m_pParams[i].m_lVal );
							break;
				case	DBVT_LONG:
							RFX_Long( pFX, paramName, m_pParams[i].m_lVal );
							break;
				case	DBVT_SINGLE:
							RFX_Single( pFX, paramName, m_pParams[i].m_fltVal );
							break;
				case	DBVT_DOUBLE:
							RFX_Double( pFX, paramName, m_pParams[i].m_dblVal );
							break;
				case	DBVT_DATE:
							RFX_Date( pFX, paramName, *m_pParams[i].m_pdate );
							break;
				case	DBVT_STRING:
						{
							RFX_Text( pFX, paramName, *m_pParams[i].m_pstring, nLength );
							break;
						}
				case	DBVT_BINARY:
							RFX_LongBinary( pFX, paramName, *(m_pParams[i].m_pbinary) );
							break;
				default:
					ASSERT( FALSE );
			}
		}
	}

	if(m_nOutputParams>0)
	{
		pFX->SetFieldType( CFieldExchange::outputParam );
		for(i=0;i<m_nParams;i++)
		{
			if(m_mapParam[i].m_nColType != SQL_PARAM_OUTPUT)
				continue;
			paramName=m_mapParam[i].m_strParamName;
			nLength=m_mapParam[i].m_nLength;
			switch( m_pParams[i].m_dwType )
			{
			case	DBVT_NULL:
						break;
			case	DBVT_BOOL:
						RFX_Bool( pFX, paramName, m_pParams[i].m_boolVal );
						break;
			case	DBVT_UCHAR:
						RFX_Byte( pFX, paramName, m_pParams[i].m_chVal );
						break;
			case	DBVT_SHORT:
						m_pParams[i].m_dwType = DBVT_LONG;
						RFX_Long( pFX, paramName, m_pParams[i].m_lVal );
						break;
			case	DBVT_LONG:
						RFX_Long( pFX, paramName, m_pParams[i].m_lVal );
						break;
			case	DBVT_SINGLE:
						RFX_Single( pFX, paramName, m_pParams[i].m_fltVal );
						break;
			case	DBVT_DOUBLE:
						RFX_Double( pFX, paramName, m_pParams[i].m_dblVal );
						break;
			case	DBVT_DATE:
						RFX_Date( pFX, paramName, *m_pParams[i].m_pdate );
						break;
			case	DBVT_STRING:
					{
						RFX_Text( pFX, paramName, *m_pParams[i].m_pstring,nLength );
						break;
					}
			case	DBVT_BINARY:
						RFX_LongBinary( pFX, paramName, *(m_pParams[i].m_pbinary) );
						break;
			default:
				ASSERT( FALSE );
			}
		}
	}
	
	if(m_nInputOutputParams>0)
	{
		pFX->SetFieldType( CFieldExchange::inoutParam );
		for(i=0;i<m_nParams;i++)
		{
			if(m_mapParam[i].m_nColType != SQL_PARAM_INPUT_OUTPUT)
				continue;
			paramName=m_mapParam[i].m_strParamName;
			nLength=m_mapParam[i].m_nLength;
			switch( m_pParams[i].m_dwType )
			{
			case	DBVT_NULL:
						break;
			case	DBVT_BOOL:
						RFX_Bool( pFX, paramName, m_pParams[i].m_boolVal );
						break;
			case	DBVT_UCHAR:
						RFX_Byte( pFX, paramName, m_pParams[i].m_chVal );
						break;
			case	DBVT_SHORT:
						m_pParams[i].m_dwType = DBVT_LONG;
						RFX_Long( pFX, paramName, m_pParams[i].m_lVal );
						break;
			case	DBVT_LONG:
						RFX_Long( pFX, paramName, m_pParams[i].m_lVal );
						break;
			case	DBVT_SINGLE:
						RFX_Single( pFX, paramName, m_pParams[i].m_fltVal );
						break;
			case	DBVT_DOUBLE:
						RFX_Double( pFX, paramName, m_pParams[i].m_dblVal );
						break;
			case	DBVT_DATE:
						RFX_Date( pFX, paramName, *m_pParams[i].m_pdate );
						break;
			case	DBVT_STRING:
					{
						RFX_Text( pFX, paramName, *m_pParams[i].m_pstring,nLength );
						break;
					}
			case	DBVT_BINARY:
						RFX_LongBinary( pFX, paramName, *(m_pParams[i].m_pbinary) );
						break;
			default:
				ASSERT( FALSE );
			}
		}
	}
}

CDBField&	CCFIRecordset::Field( int nField ) 
{
	ASSERT( m_pFields != NULL );
	ASSERT( nField >= 0 );
	ASSERT( nField < GetODBCFieldCount() );
	ASSERT( IsOpen() );

	return	m_pFields[ nField ];
}

bool	CCFIRecordset::GetBool( int nCol ) 
{
	return	Field( nCol ).AsBool();
}

unsigned char	CCFIRecordset::GetChar( int nCol ) 
{
	return	Field( nCol ).AsChar();
}

short	CCFIRecordset::GetShort( int nCol ) 
{
	return	Field( nCol ).AsShort();
}

int		CCFIRecordset::GetInt( int nCol ) 
{
	return	Field( nCol ).AsInt();
}

long	CCFIRecordset::GetLong( int nCol ) 
{
	return	Field( nCol ).AsLong();
}

float	CCFIRecordset::GetFloat( int nCol ) 
{
	return	Field( nCol ).AsFloat();
}

double	CCFIRecordset:: GetDouble( int nCol ) 
{
	return	Field( nCol ).AsDouble();
}

COleDateTime	CCFIRecordset::GetDate( int nCol ) 
{
	return	Field( nCol ).AsDate();
}

CString	CCFIRecordset::GetString( int nCol ) 
{
	return	Field( nCol ).AsString();
}

CLongBinary*	CCFIRecordset::GetBinary( int nCol ) 
{
	return	Field( nCol ).AsBinary();
}

bool	CCFIRecordset::PrepareStoreProcedure(CString strStoreProcedureName)
{
	CProcedureColumns splParamSet(m_pDatabase);
	BOOL bRet;
	bRet=splParamSet.Open(NULL,NULL,strStoreProcedureName,NULL);
	if(!bRet)
	{
		AfxMessageBox("Failed to open:CRecordset,PrepareStoreProcedure!");
		return false;
	}
	CString s1;
	int i=0;
	struct CParamInfo paramInfo;
	m_nInputParams=0;
	m_nOutputParams=0;
	m_nInputOutputParams=0;
	m_nReturnParam=0;
	m_mapParam.RemoveAll();
	while(!splParamSet.IsEOF())
	{
		paramInfo.m_strParamName = splParamSet.m_strColumnName;
		paramInfo.m_nColType = splParamSet.m_fColumnType;
		if(paramInfo.m_nColType == SQL_PARAM_INPUT)
			m_nInputParams++;
		if(paramInfo.m_nColType == SQL_PARAM_OUTPUT)
			m_nOutputParams++;
		if(paramInfo.m_nColType == SQL_PARAM_INPUT_OUTPUT)
			m_nInputOutputParams++;
		if(paramInfo.m_nColType == SQL_RETURN_VALUE)
			m_nReturnParam++;
		paramInfo.m_nDataType = splParamSet.m_nDataType ;
		paramInfo.m_nLength = splParamSet.m_nLength;
		m_mapParam.SetAt(i++,paramInfo);
		splParamSet.MoveNext();
	}
	splParamSet.Close();
	m_nParams =UINT( m_mapParam.GetCount());
	if(m_pParams != NULL)
	{
		delete[] m_pParams;
		m_pParams=NULL;
	}
	if(m_nParams == 0)
		return true;
	m_pParams = new CDBField[ m_nParams ];
	bRet=splParamSet.Open(NULL,NULL,strStoreProcedureName,NULL);
	if(!bRet)
	{
		AfxMessageBox("Failed to open!");
		return false;
	}
	i=0;
	CODBCFieldInfo fieldInfo;
	while(!splParamSet.IsEOF())
	{
		fieldInfo.m_nSQLType=splParamSet.m_nDataType;
		SetDBFieldType(m_pParams[i],fieldInfo);
		i++;
		splParamSet.MoveNext();
	}
	splParamSet.Close();
	return true;
}

bool	CCFIRecordset::PrepareSQL(CString strSQL)
{
	SQLRETURN retcode;
	SQLHSTMT hstmt;

	retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_pDatabase->m_hdbc, &hstmt);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
	{
		return false;
	}
	retcode = SQLPrepare(hstmt,(SQLCHAR *)strSQL.GetBuffer(strSQL.GetLength()),SQL_NTS);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
		return false;
	SQLSMALLINT nParams;
	retcode = SQLNumParams(hstmt, &nParams);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
		return false;
	struct CParamInfo paramInfo;
	m_nInputParams=0;
	m_nOutputParams=0;
	m_nInputOutputParams=0;
	m_nReturnParam=0;
	m_mapParam.RemoveAll();
	if(m_pParams != NULL)
	{
		delete[] m_pParams;
		m_pParams=NULL;
	}
	m_nParams=nParams;
	m_nInputParams=nParams;
	if(m_nParams==0)
		return true;
	m_pParams = new CDBField[ m_nParams ];
	SQLSMALLINT DataType, DecimalDigits, Nullable;
	SQLUINTEGER   ParamSize;
	CODBCFieldInfo fieldInfo;
	SQLCHAR	SqlState[6],Msg[SQL_MAX_MESSAGE_LENGTH];
	SQLINTEGER	NativeError;
	SQLSMALLINT	n,MsgLen;
	SQLRETURN retcode2;
	for(UINT i=0;i<m_nParams;i++)
	{
		retcode=SQLDescribeParam(hstmt, i+1, &DataType, &ParamSize, &DecimalDigits, &Nullable);
		if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
		{
			n = 1;
			CString strMsg;
			while ((retcode2 = SQLGetDiagRec(SQL_HANDLE_STMT, hstmt, n, SqlState, &NativeError,Msg, sizeof(Msg), &MsgLen)) != SQL_NO_DATA) 
			{
				strMsg=Msg;
				AfxMessageBox(strMsg);
				n++;
			}
			return false;
		}
		paramInfo.m_nColType = 	SQL_PARAM_INPUT;
		paramInfo.m_nDataType = DataType;
		paramInfo.m_nLength = ParamSize;
		(paramInfo.m_strParamName).Format("%d",i);
		paramInfo.m_nDecimalDigits = DecimalDigits;
		m_mapParam.SetAt(i,paramInfo);
		fieldInfo.m_nSQLType=DataType;
		SetDBFieldType(m_pParams[i],fieldInfo);
	}
	SQLFreeHandle(SQL_HANDLE_STMT,hstmt);

	return true;
}

void	CCFIRecordset::SetParam_Long(UINT nParamId,long nParamValue)
{
	ASSERT(nParamId>=0);
	ASSERT(nParamId<m_nParams);
	m_pParams[nParamId].m_lVal = nParamValue;
}

int	CCFIRecordset::GetParam_Long(UINT nParamId)
{
	ASSERT(nParamId>=0);
	if(m_mapParam[nParamId].m_nColType == SQL_PARAM_OUTPUT || m_mapParam[nParamId].m_nColType == SQL_PARAM_INPUT_OUTPUT ||m_mapParam[nParamId].m_nColType == SQL_RETURN_VALUE)
		return m_pParams[nParamId].m_lVal;
	else
	{
		ASSERT(FALSE);
		return -1;
	}
}

void	CCFIRecordset::SetParam_Float(UINT nParamId,float fltParamValue)
{
	ASSERT(nParamId>=0);
	ASSERT(nParamId<m_nParams);
	m_pParams[nParamId].m_fltVal = fltParamValue;
}

float	CCFIRecordset::GetParam_Float(UINT nParamId)
{
	ASSERT(nParamId>=0);
	if(m_mapParam[nParamId].m_nColType == SQL_PARAM_OUTPUT || m_mapParam[nParamId].m_nColType == SQL_PARAM_INPUT_OUTPUT)
		return m_pParams[nParamId].m_fltVal;
	else
	{
		ASSERT(FALSE);
		return 0.0;
	}
}

void	CCFIRecordset::SetParam_Double(UINT nParamId,double dblParamValue)
{
	ASSERT(nParamId>=0);
	ASSERT(nParamId<m_nParams);
	m_pParams[nParamId].m_dblVal = dblParamValue;
}

double	CCFIRecordset::GetParam_Double(UINT nParamId)
{
	ASSERT(nParamId>=0);
	if(m_mapParam[nParamId].m_nColType == SQL_PARAM_OUTPUT || m_mapParam[nParamId].m_nColType == SQL_PARAM_INPUT_OUTPUT)
		return m_pParams[nParamId].m_dblVal;
	else
	{
		ASSERT(FALSE);
		return 0.0;
	}
}

void	CCFIRecordset::SetParam_Bool(UINT nParamId,BOOL bParamValue)
{
	ASSERT(nParamId>=0);
	ASSERT(nParamId<m_nParams);
	m_pParams[nParamId].m_boolVal = bParamValue;
}

BOOL	CCFIRecordset::GetParam_Bool(UINT nParamId)
{
	ASSERT(nParamId>=0);
	if(m_mapParam[nParamId].m_nColType == SQL_PARAM_OUTPUT || m_mapParam[nParamId].m_nColType == SQL_PARAM_INPUT_OUTPUT)
		return m_pParams[nParamId].m_boolVal;
	else
	{
		ASSERT(FALSE);
		return FALSE;
	}
}

void	CCFIRecordset::SetParam_DateTime(UINT nParamId,TIMESTAMP_STRUCT dtParamValue)
{
	ASSERT(nParamId>=0);
	ASSERT(nParamId<m_nParams);
	m_pParams[nParamId].m_pdate->year = dtParamValue.year;
	m_pParams[nParamId].m_pdate->month = dtParamValue.month;
	m_pParams[nParamId].m_pdate->day = dtParamValue.day;
	m_pParams[nParamId].m_pdate->hour = dtParamValue.hour;
	m_pParams[nParamId].m_pdate->minute = dtParamValue.minute;
	m_pParams[nParamId].m_pdate->second = dtParamValue.second;
	m_pParams[nParamId].m_pdate->fraction = dtParamValue.fraction;
}

TIMESTAMP_STRUCT	CCFIRecordset::GetParam_DateTime(UINT nParamId)
{
	ASSERT(nParamId>=0);
	if(!(m_mapParam[nParamId].m_nColType == SQL_PARAM_OUTPUT || m_mapParam[nParamId].m_nColType == SQL_PARAM_INPUT_OUTPUT))
		ASSERT(FALSE);
	return *(m_pParams[nParamId].m_pdate);
}

void	CCFIRecordset::SetParam_String(UINT nParamId,CString strParamValue)
{
	ASSERT(nParamId>=0);
	ASSERT(nParamId<m_nParams);
	*(m_pParams[nParamId].m_pstring)=strParamValue;
}


////////////////////////////////////////////////////////////////
//	CDBField
///////////////////////////////////////////////////////////////

CDBField::CDBField() 
{
	m_bIsNull = true;
}

CDBField::~CDBField() 
{
}

bool	CDBField::AsBool()	const
{
	if( IsNull() )
		return	false;

	CString	cValue;
	switch( m_dwType ) {
	case	DBVT_NULL:
				return	false;

	case	DBVT_BOOL:
				return	(m_boolVal == TRUE);

	case	DBVT_UCHAR:
				return	(m_chVal == 'T' || m_chVal == '1');

	case	DBVT_SHORT:
				return	(m_iVal != 0);

	case	DBVT_LONG:
				return	(m_lVal != 0);

	case	DBVT_SINGLE:
				return	(m_fltVal != 0.0);

	case	DBVT_DOUBLE:
				return	(m_dblVal != 0.0);

	case	DBVT_DATE:
				//	Cannot convert date to bool
				ASSERT( FALSE );
				break;

	case	DBVT_STRING:
				ASSERT( m_pstring != NULL );
				if( m_pstring->GetLength() < 1 )
					return	false;
				return	((*m_pstring)[0] == 'T' || (*m_pstring)[0] == '1');

	case	DBVT_BINARY:
				//	Cannot convert long binary to bool
				ASSERT( FALSE );
				break;
	}
	//	Undefined data type
	ASSERT( FALSE );
	return	false;
}

unsigned char	CDBField::AsChar()	const
{
	if( IsNull() )
		return	' ';

	switch( m_dwType ) {
	case	DBVT_NULL:
				return	' ';

	case	DBVT_BOOL:
				return	(m_boolVal) ? 'T' : 'F';

	case	DBVT_UCHAR:
				return	m_chVal;

	case	DBVT_SHORT:
				return	(unsigned char)m_iVal;

	case	DBVT_LONG:
				return	(unsigned char)m_lVal;

	case	DBVT_SINGLE:
				return	(unsigned char)m_fltVal;

	case	DBVT_DOUBLE:
				return	(unsigned char)m_dblVal;

	case	DBVT_DATE:
				//	Cannot convert date to unsigned char
				ASSERT( FALSE );
				break;

	case	DBVT_STRING:
				ASSERT( m_pstring != NULL );
				if( m_pstring->GetLength() < 1 )
					return	' ';
				return	(unsigned char)((*m_pstring)[0]);

	case	DBVT_BINARY:
				//	Cannot convert long binary to unsigned char
				ASSERT( FALSE );
				break;
	}
	//	Undefined data type
	ASSERT( FALSE );
	return	' ';
}

short	CDBField::AsShort()	const
{
	if( IsNull() )
		return	0;

	switch( m_dwType ) {
	case	DBVT_NULL:
				return	0;

	case	DBVT_BOOL:
				return	m_boolVal ? 1 : 0;

	case	DBVT_UCHAR:
				return	(short)m_chVal;

	case	DBVT_SHORT:
				return	m_iVal;

	case	DBVT_LONG:
				return	(short)m_lVal;

	case	DBVT_SINGLE:
				return	(short)m_fltVal;

	case	DBVT_DOUBLE:
				return	(short)m_dblVal;

	case	DBVT_DATE:
				//	Cannot convert date to short
				ASSERT( FALSE );
				break;

	case	DBVT_STRING:
				ASSERT( m_pstring != NULL );
				return	(short)atoi( *m_pstring );

	case	DBVT_BINARY:
				//	Cannot conver long binary to short
				ASSERT( FALSE );
				break;
	}
	//	Undefined data type
	ASSERT( FALSE );
	return	0;
}

int		CDBField::AsInt()	const
{
	return	AsLong();
}

long	CDBField::AsLong()	const
{
	if( IsNull() )
		return	0;

	switch( m_dwType ) {
	case	DBVT_NULL:
				return	0;

	case	DBVT_BOOL:
				return	m_boolVal ? 1 : 0;

	case	DBVT_UCHAR:
				return	(long)m_chVal;

	case	DBVT_SHORT:
				return	(long)m_iVal;

	case	DBVT_LONG:
				return	m_lVal;

	case	DBVT_SINGLE:
				return	(long)m_fltVal;

	case	DBVT_DOUBLE:
				return	(long)m_dblVal;

	case	DBVT_DATE:
				//	Cannot convert date to long
				ASSERT( FALSE );
				break;

	case	DBVT_STRING:
				ASSERT( m_pstring != NULL );
				return	atol( *m_pstring );

	case	DBVT_BINARY:
				//	Cannot conver long binary to long
				ASSERT( FALSE );
				break;
	}
	//	Undefined data type
	ASSERT( FALSE );
	return	0;
}

float	CDBField::AsFloat()	const
{
	if( IsNull() )
		return	0.0;

	switch( m_dwType ) {
	case	DBVT_NULL:
				return	0.0;

	case	DBVT_BOOL:
				return	(float)(m_boolVal ? 1.0 : 0.0);

	case	DBVT_UCHAR:
				return	(float)m_chVal;

	case	DBVT_SHORT:
				return	(float)m_iVal;

	case	DBVT_LONG:
				return	(float)m_lVal;

	case	DBVT_SINGLE:
				return	m_fltVal;

	case	DBVT_DOUBLE:
				return	(float)m_dblVal;

	case	DBVT_DATE:
				//	Cannot convert date to float
				ASSERT( FALSE );
				break;

	case	DBVT_STRING:
				ASSERT( m_pstring != NULL );
				return	(float)atof( *m_pstring );

	case	DBVT_BINARY:
				//	Cannot conver long binary to float
				ASSERT( FALSE );
				break;
	}
	//	Undefined data type
	ASSERT( FALSE );
	return	0.0;
}

double	CDBField::AsDouble()	const
{
	if( IsNull() )
		return	0.0;

	switch( m_dwType ) {
	case	DBVT_NULL:
				return	0.0;

	case	DBVT_BOOL:
				return	m_boolVal ? 1.0 : 0.0;

	case	DBVT_UCHAR:
				return	(double)m_chVal;

	case	DBVT_SHORT:
				return	(double)m_iVal;

	case	DBVT_LONG:
				return	(double)m_lVal;

	case	DBVT_SINGLE:
				return	(double)m_fltVal;

	case	DBVT_DOUBLE:
				return	m_dblVal;

	case	DBVT_DATE:
				//	Cannot convert date to double
				ASSERT( FALSE );
				break;

	case	DBVT_STRING:
				ASSERT( m_pstring != NULL );
				return	atof( *m_pstring );

	case	DBVT_BINARY:
				//	Cannot conver long binary to double
				ASSERT( FALSE );
				break;
	}
	//	Undefined data type
	ASSERT( FALSE );
	return	0.0;
}

COleDateTime	CDBField::AsDate()	const
{
	COleDateTime	date;
	if( IsNull() ) {
		date.SetStatus( COleDateTime::null );
		return	date;
	}

	switch( m_dwType ) {
	case	DBVT_NULL:
			date.SetStatus( COleDateTime::null );
			return	date;

	case	DBVT_BOOL:
			date.SetStatus( COleDateTime::invalid );
			return	date;

	case	DBVT_UCHAR:
			date.SetStatus( COleDateTime::invalid );
			return	date;

	case	DBVT_SHORT:
			return	COleDateTime( (time_t)m_iVal );

	case	DBVT_LONG:
			return	COleDateTime( (time_t)m_lVal );

	case	DBVT_SINGLE:
			return	COleDateTime( (time_t)m_fltVal );

	case	DBVT_DOUBLE:
			return	COleDateTime( (time_t)m_dblVal );

	case	DBVT_DATE:
			ASSERT( m_pdate != NULL );
			return	COleDateTime(	m_pdate->year, m_pdate->month, m_pdate->day,
									m_pdate->hour, m_pdate->minute, m_pdate->second );

	case	DBVT_STRING:
			ASSERT( m_pstring != NULL );
			date.ParseDateTime( *m_pstring );
			return	date;

	case	DBVT_BINARY:
			//	Cannot conver long binary to date
			ASSERT( FALSE );
			break;
	}
	//	Undefined data type
	ASSERT( FALSE );
	date.SetStatus( COleDateTime::invalid );
	return	date;
}

CString		CDBField::AsString()
{
	CString	cValue;
	if( IsNull() ) 
		return cValue;

	switch( m_dwType ) {
	case	DBVT_NULL:
			return	cValue;

	case	DBVT_BOOL:
			return	CString( m_boolVal ? "T" : "F" );

	case	DBVT_UCHAR:
			unsigned char s1[2];
			s1[0]=m_chVal;
			s1[1]='\0';
			return	CString( s1 );

	case	DBVT_SHORT:
			cValue.Format( "%hd", m_iVal );
			return	cValue;

	case	DBVT_LONG:
			cValue.Format( "%ld", m_lVal );
			return	cValue;

	case	DBVT_SINGLE:
			cValue.Format( "%f", m_fltVal );
			return	cValue;

	case	DBVT_DOUBLE:
			cValue.Format( "%f", m_dblVal );
			return	cValue;

	case	DBVT_DATE:
		{
			ASSERT( m_pdate != NULL );
			COleDateTime	date( m_pdate->year, m_pdate->month, m_pdate->day,
								  m_pdate->hour, m_pdate->minute, m_pdate->second );
			return	date.Format();
		}
	case	DBVT_STRING:
			ASSERT( m_pstring != NULL );
			return	*m_pstring;

	case	DBVT_BINARY:
			ASSERT( m_pbinary != NULL );
			BinaryToString( cValue,true );
			return	cValue;
	}
	//	Undefined data type
	ASSERT( FALSE );
	return	cValue;
}

CLongBinary*	CDBField::AsBinary()	const
{
	if( IsNull() )
		return NULL;

	switch( m_dwType ) 
	{
	case	DBVT_NULL:
			return	NULL;

	case	DBVT_BOOL:
	case	DBVT_UCHAR:
	case	DBVT_SHORT:
	case	DBVT_LONG:
	case	DBVT_SINGLE:
	case	DBVT_DOUBLE:
	case	DBVT_DATE:
	case	DBVT_STRING:
			//	Cannot convert to long binary
			ASSERT( FALSE );
			break;

	case	DBVT_BINARY:
			return	m_pbinary;
	}
	//	Undefined data type
	ASSERT( FALSE );
	return	m_pbinary;
}

bool	CDBField::IsNull() const
{ 
	return m_bIsNull || m_dwType == DBVT_NULL; 
}

void	CDBField::SetNull( bool bIsNull )
{
	m_bIsNull = bIsNull; 
}

void	CDBField::BinaryToString( CString& cStr, bool bExpand )
{
	if(m_pbinary == NULL)
		return;

	int	nSize = min( (int)m_pbinary->m_dwDataLength, cStr.GetLength() );
	if( bExpand )
		nSize = m_pbinary->m_dwDataLength;

	if( nSize < 1 ) {
		cStr.Empty();
		return;
	}

	void*	p = ::GlobalLock( m_pbinary->m_hData );
	if( p == NULL )
		::AfxThrowMemoryException();
	
	char* pStr = cStr.GetBuffer( nSize );
	memcpy( pStr, p, nSize );
	cStr.ReleaseBuffer( nSize );
	::GlobalUnlock( m_pbinary->m_hData );
}
