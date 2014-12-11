// ==========================================================================
// 							Screen Characteristics specification
// ==========================================================================

// Header file : screen.h

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved                      
                          
// //////////////////////////////////////////////////////////////////////////
// Desciption :         
//		Contains some ENUMS used by the MDI CLIENT 

// Remark:
//		***

// Prerequisites (necessary conditions):
//		***

/////////////////////////////////////////////////////////////////////////////
#ifndef __SCREEN_H__
#define __SCREEN_H__

enum EWallOrg
	{ 
	WP_Undefined 	=   0,
	WP_Center		= 	1,
	WP_Tile			=	2,
	WP_Scale		=	3
	};
const EWallOrg WP_FIRST = WP_Center;	
const EWallOrg WP_LAST =  WP_Scale;

enum EPalUpdate
	{ 
	PU_Undefined 	=   0,
	PU_NoUpdate		= 	1,
	PU_IntelUpdate	=	2,
	PU_ForceUpdate	=	3
	};
const EPalUpdate PU_FIRST = PU_NoUpdate;	
const EPalUpdate PU_LAST =  PU_ForceUpdate;

#endif
// ==========================================================================
