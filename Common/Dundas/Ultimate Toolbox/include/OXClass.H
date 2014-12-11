// ==========================================================================
// 							Ultimate Toolbox include & library specification
// ==========================================================================

// Header file : OXClass.h

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved                      
                          
// //////////////////////////////////////////////////////////////////////////
// Desciption :         
//		Contains all includes for Ultimate Toolbox classes
//		When Ultimate Toolbox used in static library, includes necessary library automatically

// Remark:
//		***

// Prerequisites (necessary conditions):
//		***

/////////////////////////////////////////////////////////////////////////////
#ifndef __OXCLASS_H__
#define __OXCLASS_H__

#ifndef NOAUTOLIB
	#ifndef _AFXDLL
		#ifdef _DEBUG
			#pragma comment(lib, "oxlibd.lib")
		#else
			#pragma comment(lib, "oxlibr.lib")
		#endif // _DEBUG
	#else // _AFXDLL
		#ifdef _DEBUG
			#pragma comment(lib, "oxlibad.lib")
		#else
			#pragma comment(lib, "oxlibar.lib")
		#endif // _DEBUG
	#endif // _AFXDLL
#endif // NOAUTOLIB

#ifdef FILEMGMT
	#include "path.h" 
	#include "cpystdlg.h" 
	#include "dirlist.h" 
	#include "filelist.h" 
	#include "oxdirdlg.h"
	#include "oxuudec.h"
	#include "oxuudret.h"
	#include "oxdflhdr.h"
	#include "progress.h"
	#include "bdifcalc.h"
	#include "crypfile.h"
	#include "oxcmpfl.h"
	#include "oxbitbuf.h"

	#ifdef WIN32
		#include "oxurl.h"
		#include "oxiteratorunc.h"
		#include "oxfilewatcher.h"
	#endif

#endif // FILEMGMT

#ifdef UTILITY
	#include "xstring.h" 
	#include "date.h" 
	#include "verinfo.h" 
	#include "oxseh.h" 
	#include "oxcmdopt.h" 
	#include "oxcmdlex.h" 
	#include "oxsrlzr.h"
	#include "oxcrcchk.h"

	#ifdef WIN32
		#include "oxsgrp.h" 
		#include "oxbgrp.h" 
		#include "evntlog.h" 
		#include "registry.h" 
		#include "oxclipboard.h" 
		#include "oxscreengrab.h" 
		#include "oxresultobj.h" 
		#include "oxresultpart.h" 
		#include "oxworkspacestate.h" 
		#include "oxinstancemanager.h" 
		#include "oxtimer.h" 
		#include "oxshortcut.h" 
		#include "oxregistryitem.h" 
		#include "oxiteratorregistryitem.h" 
		#include "oxinteger.h" 
		#include "oxresourcefile.h" 
		#include "oxresourcelibrary.h" 
		#include "oxundo.h" 
		#include "oxsound.h" 
		#include "oxfilechanger.h" 
		#include "oxregistrywatcher.h" 
		#include "OXIteratorService.h"
		#include "OXSysInfo.h"
		#include "OXRegistryValFile.h"
	#endif

#endif // UTILITY

#ifdef WINCTRL
	#include "oxcllgrd.h" 
	#include "oxtxtcll.h" 
	#include "oxcllarr.h" 
	#include "oxrollup.h" 
	#include "oxusertl.h" 
	#include "xstatus.h" 
	#include "oxzoomvw.h" 

	#ifdef WIN32
		#include "oxshape.h" 
		#include "oxeditlist.h" 
		#include "oxdckpsh.h" 
		#include "oxdckppg.h" 
		#include "oxnetbrowsetree.h"
		#include "oxbitmapbutton.h"
		#include "xstatus4.h" 
		#include "oxframewnddock.h" 
		#include "oxsizedockbar.h" 
		#include "oxsizectrlbar.h" 
		#include "oxsizetoolbar.h" 
		#include "oxsizedlgbar.h" 
		#include "oxhistorycombo.h" 
		#include "oxphysicaledit.h" 
		#include "oxscrolltip.h"
		#include "oxscrolltipowner.h"
		#include "oxcontexthelpdialog.h"
		#include "oxcontexthelppropertysheet.h"
		#include "oxcontexthelppropertypage.h"
		#include "oxmulticombobox.h"
		#include "oxbitmapmenuorganizer.h"
		#include "oxlayoutmanager.h"
		#include "oxlayoutmanager.h"
		#include "oxwebview.h"
		#include "oxspinctrl.h"
		#include "oxcalendar.h"
		#include "oxstatictext.h"
	#endif

#endif // WINCTRL

#ifdef GRAPHICS
	#include "oxdib.h" 
	#include "oxbmpprv.h" 
	#include "xmdiclt.h" 
	#include "xmainfrm.h" 

	#ifdef WIN32
		#include "oxsplashwnd.h" 
		#include "oxcolorspace.h" 
	#endif

#endif // GRAPHICS

#ifdef JPEG
	#include "oxjpgfle.h" 
	#include "oxbmpfle.h" 
	#include "oxgiffle.h" 
	#include "oxjpgcom.h" 
	#include "oxjpgdom.h" 
	#include "oxjpgexp.h" 
#endif // JPEG

#ifdef COMMUNIC
	#include "oxmapi.h" 
	#include "oxscript.h" 

	#ifdef WIN32
		#include "oxcommunicator.h" 
		#include "oxblob.h" 
		#include "oxthreadengine.h" 
		#include "oxsercom.h" 
		#include "oxmdisp.h"
		#include "oxsendmail.h"
	#endif

#endif // COMMUNIC

#ifdef OLE

	#ifdef WIN32
		#include "oxownthreadcmdtarget.h" 
		#include "oxownthreaddocument.h" 
		#include "oxoledispdrv.h" 
	#endif

#endif // OLE

#endif //__OXCLASS_H__
// ==========================================================================
