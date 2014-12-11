/*----------------------------------------------------------------------
	Copyright © 2001-2012 JRS Technology, Inc.
-----------------------------------------------------------------------*/
#ifndef _VERSIONNO_H
#define _VERSIONNO_H

#ifdef _DEBUG
	#ifdef _BETA
		#define VINFO_VERSIONFLAGS				VS_FF_DEBUG | VS_FF_PRERELEASE
	#else
		#define VINFO_VERSIONFLAGS				VS_FF_DEBUG
	#endif
#else
	#ifdef _BETA
		#define VINFO_VERSIONFLAGS				VS_FF_PRERELEASE
	#else
		#define VINFO_VERSIONFLAGS				0x0
	#endif
#endif

// set generic version info
#define VINFO_HI_FILEVERSION 			03
#define VINFO_LO_FILEVERSION 			20
#define VINFO_HI_FILEBUILD   			00
#define VINFO_LO_FILEBUILD   			300

#define VINFO_HI_PRODUCTVERSION 		03
#define VINFO_LO_PRODUCTVERSION 		20
#define VINFO_HI_PRODUCTBUILD   		00
#define VINFO_LO_PRODUCTBUILD   		300

#define VINFO_STRING_COMMENTS			"Installation Manager Classic\000"
#define VINFO_STRING_COMPANYNAME		"Custom Installations, Inc.\000"
#define VINFO_STRING_COPYRIGHT			"Copyright © 2001-2012, Custom Installations, Inc.\000"
#define VINFO_STRING_FILEDESCRIPTION	"Installation Manager Classic\000"
#define VINFO_STRING_PRODUCTNAME		"Installation Manager Classic\000"

// set to filename with no .exe
#define VINFO_STRING_INTERNALNAME		"Installation Manager Classic\000"
// set to filename with exe
#define VINFO_STRING_ORIGINALNAME		"flooring.exe\000"

// set version stuff according to debug
	#ifdef _DEBUG
		#ifdef _BETA
			#define VINFO_STRING_FILEVERSION		"3.20 (Debug Beta Build 300)\000"
			#define VINFO_STRING_PRODUCTVERSION		"3.20 (Debug Beta Build 300)\000"
		#else
			#define VINFO_STRING_FILEVERSION		"3.20 (Debug Build 300)\000"
			#define VINFO_STRING_PRODUCTVERSION		"3.20 (Debug Build 300)\000"
		#endif
	#else
		#ifdef _BETA
			#define VINFO_STRING_FILEVERSION		"3.20 (Release Beta Build 300)\000"
			#define VINFO_STRING_PRODUCTVERSION		"3.20 (Release Beta Build 300)\000"
		#else
			#define VINFO_STRING_FILEVERSION		"3.20 (Release Build 300)\000"
			#define VINFO_STRING_PRODUCTVERSION		"3.20 (Release Build 300)\000" 
		#endif
	#endif
#endif


