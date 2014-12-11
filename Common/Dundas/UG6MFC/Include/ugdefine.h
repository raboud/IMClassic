/*************************************************************************
	Header file : ugdefine.h
	Copyright © Dundas Software Ltd. 1994 - 2002, All Rights Reserved

    Purpose
		This class file contains all standard defines for the Ultimate Grid.
*************************************************************************/
#ifndef _ugdefine_H_
#define _ugdefine_H_

//bit defines
#define BIT0	1
#define BIT1	2
#define BIT2	4
#define BIT3	8
#define BIT4	16
#define BIT5	32
#define BIT6	64
#define BIT7	128
#define BIT8	256
#define BIT9	512
#define BIT10	1024
#define BIT11	2048
#define BIT12	4096
#define BIT13	8192
#define BIT14	16384
#define BIT15	32768
#define BIT16	65536l
#define BIT17	131072l
#define BIT18	262144l
#define BIT19	524288l
#define BIT20	1048576l
#define BIT21	2097152l
#define BIT22	4194304l
#define BIT23	8388608l
#define BIT24	16777216l
#define BIT25	33554432l
#define BIT26	67108864l
#define BIT27	134217728l
#define BIT28	268435456l
#define BIT29	536870912l
#define BIT30	1073741824l
#define BIT31	2147483648l

#ifdef _BUILD_UG_INTO_EXTDLL
	#define UG_CLASS_DECL AFX_CLASS_EXPORT
#elif defined _LINK_TO_UG_IN_EXTDLL
	#define UG_CLASS_DECL AFX_CLASS_IMPORT
#else
	#define UG_CLASS_DECL
#endif

//UGID structure defines
#define LPCUGID const UGID *

// up/down movement defines
#define UG_LINEUP	0
#define UG_LINEDOWN	1
#define UG_PAGEUP	2
#define UG_PAGEDOWN	3
#define UG_TOP		4
#define UG_BOTTOM	5

// left/right movement defines
#define UG_COLLEFT	0
#define UG_COLRIGHT	1
#define UG_PAGELEFT	2
#define UG_PAGERIGHT	3
#define UG_LEFT		4
#define UG_RIGHT	5

//common return codes  - error and warning codes are positive values
#define UG_SUCCESS		0
#define UG_ERROR		1
#define UG_NA			-1

#define UG_PROCESSED	1

//data source
#define	UG_MAXDATASOURCES 5

//scrolling
#define UG_SCROLLNORMAL		0
#define UG_SCROLLTRACKING	1
#define UG_SCROLLJOYSTICK	2

#define UG_DRAGDROP_SCROLL_BORDER	10

//ballistics
#define UG_BALLISTICS_OFF		0
#define UG_BALLISTICS_NORMAL	1
#define UG_BALLISTICS_SQAURED	2
#define UG_BALLISTICS_CUBED		3

//alignment defines
#define UG_ALIGNLEFT		BIT0
#define UG_ALIGNRIGHT		BIT1
#define UG_ALIGNCENTER		BIT2
#define UG_ALIGNTOP			BIT3
#define UG_ALIGNBOTTOM		BIT4
#define UG_ALIGNVCENTER		BIT5

//border style defines
#define UG_BDR_LTHIN		BIT0
#define UG_BDR_TTHIN		BIT1
#define UG_BDR_RTHIN		BIT2
#define UG_BDR_BTHIN		BIT3
#define UG_BDR_LMEDIUM		BIT4
#define UG_BDR_TMEDIUM		BIT5
#define UG_BDR_RMEDIUM		BIT6
#define UG_BDR_BMEDIUM		BIT7
#define UG_BDR_LTHICK		BIT8
#define UG_BDR_TTHICK		BIT9
#define UG_BDR_RTHICK		BIT10
#define UG_BDR_BTHICK		BIT11
#define UG_BDR_RECESSED		BIT12
#define UG_BDR_RAISED		BIT13

//sorting
#define UG_SORT_ASCENDING		1
#define UG_SORT_DESCENDING		2

//finding
#define UG_FIND_PARTIAL			1
#define UG_FIND_CASEINSENSITIVE	2
#define UG_FIND_UP				4
#define UG_FIND_ALLCOLUMNS		8

//printing defines
#define UG_PRINT_TOPHEADING		1
#define UG_PRINT_SIDEHEADING	2
#define UG_PRINT_LEFTMARGIN		3
#define UG_PRINT_TOPMARGIN		4
#define UG_PRINT_RIGHTMARGIN	5
#define UG_PRINT_BOTTOMMARGIN	6
#define UG_PRINT_LANDSCAPE		7
#define UG_PRINT_SMALL			8
#define UG_PRINT_LARGE			9
#define UG_PRINT_FRAME			10

//edit control define
#define UG_EDITID			123
#define UG_MEDITID			124

//CellType Custom Windows Message
#define UGCT_MESSAGE		WM_USER+100

//best fit defines
#define UG_BESTFIT_TOPHEADINGS	1
#define UG_BESTFIT_AVERAGE		2


//Normal CellType/CellType Ex Values - most other cell types 
//also use these values, so bits 1-8 are reserved generally reserved
#define UGCT_NORMAL				0
#define UGCT_NORMALSINGLELINE	BIT0 
#define UGCT_NORMALMULTILINE	BIT1
#define UGCT_NORMALELLIPSIS		BIT2
#define UGCT_NORMALLABELTEXT	BIT3

//Droplist CellType
#define UGCT_DROPLIST		1
//CheckBox CellType
#define UGCT_CHECKBOX		2
//Arrow CellType
#define UGCT_ARROW			3

//SpinButton CellType/CellTypeEx Values
//Spinbutton OnCellType notifications
#define UGCT_SPINBUTTONUP	16
#define UGCT_SPINBUTTONDOWN	17
#define UGCT_SPINBUTTONHIDEBUTTON	BIT9

//Grid Sections - used by menu commands, etc
#define UG_GRID				1
#define UG_TOPHEADING		2
#define UG_SIDEHEADING		3
#define UG_CORNERBUTTON		4
#define UG_HSCROLL  		5
#define UG_VSCROLL  		6
#define UG_TAB				7

#endif // _ugdefine_H_