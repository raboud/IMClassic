Using the Ultimate Grid with Codebase

The CodeBase datasource is not fully supported for Ultimate Grid,
in part because of the tremendous flexibility of the CodeBase
product.  What we provide here is a basic CUGDataSource derived 
class with some basic functionality that can be extended and further
customized by the knowledgeable codebase user.

Comments and suggestions welcome - email tech@dundas.com.

CBase1 Example:

	Before the example will compile, you may need to add a path
	(Tools | Options | Directories ) to the codebase source and lib 
	(e.g. Codebase\Cpp\Source, Codebase\Cpp\MSC50) directories 
    so that the required header and lib files can be found.

	The CBase1 example opens CUGCBDataSource objects as members 
	of the document class, and sets the ds as the default datasource
	for the grid in the views' OnInitialUpdate.

    Find fuctionality is demonstrated - Edit | Find in the view menu.

    Double clicking on the column heading will try to set the index 
    to that column if one exists.

    Scrolling will be slower in debug mode, due to the use of a 
    'debug' version of MyCug which TRACEs calls to almost all methods
    of the (MyCug) class.

General:

	For information on using custom datasources with Ultimate Grid,
	please refer to the on-line documentation and articles on the 
	developer's site.


Steps to hooking Codebase up to VC++ APP's:

	1) Develop an application in VC++. Run the application, just
	   to make sure everything compiles and you get a blank DLG, or
	   View.

	2) Make sure all settings under Build->Settings and Tools->Options 
	   are set properly for Codebase(see Codebase set up instructions
	   for your particular compiler).

	3) Link the .LIB files into your project for Codebase and remember
	   to #include your .H or .HPP files into you proper sections.

	4) I have found these settings to constantly work for VC++
	 	   
			Build - Settings - C/C++
			
			General->Preprocessor Definitions
			WIN32,_WINDOWS,_AFXDLL,_MBCS,S4DLL	
	
			Code Generation-Processor
			80486 (or your type of computer)

			Code Generation-Use Run-time library
			Multithreaded DLL

			Code Generation-Calling convention
			_stdcall

			Code Generation-Struct member alignment
			1 Byte  (depends on build of CodeBase DLL/LIBs)

			Preprocessor-Preprocessor definitions
			WIN32,_WINDOWS,_AFXDLL,_MBCS,S4DLL

			Resources-Preprocessor definitions
			_DEBUG,_AFXDLL,S4DLL

	   
	6) Compile the program and make sure everything links, compiles and
	   runs without any problem!



PREVIOUS REVISIONS (ug30)

The Ultimate Grid and Codebase 5.0+
(Updated as of November 15, 1996)


Create:
	
	Create(LPCSTR name,FIELD4INFO *m_fieldNames,TAG4INFO *option)

	This function now takes 3 parameters. The first parameter is 
	the database name; The second is a FIELD4INFO structure that you
	will define in your app's OnCreate or OnInitDialog and then pass
	in. The third parameter is a TAG4INFO structure that you would
	define in your OnCreate or OnInitDialog and pass in.
	
	

Open:

	Open(LPCSTR name, LPCSTR option);

	There is nothing new with this function externally. Internally however,
	has been completely rewritten. You can now
	open any DBF file or equivalent, just by calling the Open command
	with the path of the file; the function will take care of the rest.

Member Variable m_indexOnFlag:

	The Grid's Codebase Datasource can now create and use the indexes
	just by clicking on the top headers. Setting the member variable
	to TRUE, then clicking on a top heading will, if an index does not
	already exist, prompt the client to create one.  If set to FALSE,
	it will just use the indexes that have already been defined.
	
	Use the SetOption(1,BOOL state,NULL) function (where state is a
	boolean TRUE or FALSE statement) to set the member variable.

::AddIndex(LPCSTR indexName,LPCSTR sortOn)
::AddIndex(LPCSTR indexName,LPCSTR sortOn,LPCSTR filter,
		   int unique,int descendOrAscend,TAG4INFO *tag)

	There are two overloaded members that do indexing. The first
	function is a simple AddIndex(). All you need to provide is the 
	name of the tag and the field upon which the tag will be based.
	By default, this will set up a descending, non-unique index 
	structure (which is the most comonly used index).

	Its overloaded partner is used for the more advanced settings.
	It takes the name and the field, but also the filter, uniqueness,
	desending or ascending, and a TAG4INFO structure.
	(NOTE: You may set TAG4INFO to NULL, as it is not being used right
	now.  It will be used in the future, however)

	NOTE: As of this date, an index file must already be open in order
		  for the indexing to work. If no index exist, an error will
		  occur.							