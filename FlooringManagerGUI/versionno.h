/*----------------------------------------------------------------------
	Copyright © 2001-2012 R & R Engineering Technology, Inc.
-----------------------------------------------------------------------*/
#ifndef _VERSIONNO_H
#define _VERSIONNO_H

// set generic version info
#define VINFO_HI_FILEVERSION 			03
#define VINFO_LO_FILEVERSION 			31
#define VINFO_HI_FILEBUILD   			00
#define VINFO_LO_FILEBUILD   			00

#define VINFO_HI_PRODUCTVERSION 		03
#define VINFO_LO_PRODUCTVERSION 		31
#define VINFO_HI_PRODUCTBUILD   		00
#define VINFO_LO_PRODUCTBUILD   		00

#define VINFO_STRING_COMMENTS			"Installation Manager Classic\000"
#define VINFO_STRING_COMPANYNAME		"R & R Engineering, LLC\000"
#define VINFO_STRING_COPYRIGHT			"Copyright © 2001-2013, R & R Engineering, LLC\000"
#define VINFO_STRING_FILEDESCRIPTION	"Installation Manager Classic\000"
#define VINFO_STRING_PRODUCTNAME		"Installation Manager Classic\000"

// set to filename with no .exe
#define VINFO_STRING_INTERNALNAME		"Installation Manager Classic\000"
// set to filename with exe
#define VINFO_STRING_ORIGINALNAME		"flooring.exe\000"

// Create strings to be used in the version strings
#define FILEVERSION_STRING			MAKE_STRING(VINFO_HI_FILEVERSION) "." MAKE_STRING(VINFO_LO_FILEVERSION) "." MAKE_STRING( VINFO_HI_FILEBUILD ) "." MAKE_STRING( VINFO_LO_FILEBUILD )
#define PRODUCTVERSION_STRING		MAKE_STRING(VINFO_HI_PRODUCTVERSION) "." MAKE_STRING(VINFO_LO_PRODUCTVERSION) "." MAKE_STRING( VINFO_HI_PRODUCTBUILD ) "." MAKE_STRING( VINFO_LO_PRODUCTBUILD )

// Macro to create strings from non string 
// Note we need the two levels here so it works when passed a macro value 
#define INT_MAKE_STRING(in) #in
#define MAKE_STRING(in) INT_MAKE_STRING( in )

// set version stuff according to debug
	#ifdef _DEBUG
		#ifdef _BETA
			#define VINFO_VERSIONFLAGS				VS_FF_DEBUG | VS_FF_PRERELEASE
			#define VINFO_STRING_FILEVERSION		FILEVERSION_STRING "  Debug Beta\000"
			#define VINFO_STRING_PRODUCTVERSION		PRODUCTVERSION_STRING "  Debug Beta\000"
		#else
			#define VINFO_VERSIONFLAGS				VS_FF_DEBUG
			#define VINFO_STRING_FILEVERSION		FILEVERSION_STRING "  Debug\000"
			#define VINFO_STRING_PRODUCTVERSION		PRODUCTVERSION_STRING "  Debug\000"
		#endif
	#else
		#ifdef _BETA
			#define VINFO_VERSIONFLAGS				VS_FF_PRERELEASE
			#define VINFO_STRING_FILEVERSION		FILEVERSION_STRING "  Release Beta\000"
			#define VINFO_STRING_PRODUCTVERSION		PRODUCTVERSION_STRING "  Release Beta\000"
		#else
			#define VINFO_VERSIONFLAGS				0x0
			#define VINFO_STRING_FILEVERSION		FILEVERSION_STRING "  Release\000"
			#define VINFO_STRING_PRODUCTVERSION		PRODUCTVERSION_STRING "  Release\000"
		#endif
	#endif
#endif


