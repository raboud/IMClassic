// ==========================================================================
// 					Class Specification : COXColor
// ==========================================================================

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved
                        
// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	NO	Derived from 

//	NO	Is a Cwnd.                     
//	NO	Two stage creation (constructor & Create())
//	NO	Has a message map
//	NO	Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	NO	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Desciption :         

// Remark:

// Prerequisites (necessary conditions):

/////////////////////////////////////////////////////////////////////////////

#ifndef __OXCOLOR_H__
#define __OXCOLOR_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"

// ... Number of colors in collection
#define OX_NUM_COLORS 558

#define  HLSMAX   240	/* H,L, and S vary over 0-HLSMAX */
#define  RGBMAX   255   /* R,G, and B vary over 0-RGBMAX */
                        /* HLSMAX BEST IF DIVISIBLE BY 6 */
                        /* RGBMAX, HLSMAX must each fit in a byte. */

/* Hue is undefined if Saturation is 0 (grey-scale) */
/* This value determines where the Hue scrollbar is */
/* initially set for achromatic colors */
#define UNDEFINED (HLSMAX*2/3) 


// define OX_COLORS_NO_NAMES to exclude the color names and the collection

class OX_CLASS_DECL COXColor
{
// Data members -------------------------------------------------------------
public:
#ifndef OX_COLORS_NO_NAMES 
	struct COXColorCouple
		{
		LPCTSTR m_pszName;
		COLORREF m_value;
		};
	static COXColorCouple m_colors[OX_NUM_COLORS + 1];
	// --- Collection of items with two values: color name and color value.
	//     It ends in {NULL, 0}

	static const int m_nNumberOfColors;
	// --- Number of items in collection (excluding terminating zero item)

#endif // OX_COLORS_NO_NAMES 

	static const COLORREF m_AliceBlue;
	static const COLORREF m_AntiqueWhite;
	static const COLORREF m_AntiqueWhite1;
	static const COLORREF m_AntiqueWhite2;
	static const COLORREF m_AntiqueWhite3;
	static const COLORREF m_AntiqueWhite4;
	static const COLORREF m_Aquamarine;
	static const COLORREF m_Aquamarine1;
	static const COLORREF m_Aquamarine2;
	static const COLORREF m_Aquamarine3;
	static const COLORREF m_Aquamarine4;
	static const COLORREF m_Azure;
	static const COLORREF m_Azure1;
	static const COLORREF m_Azure2;
	static const COLORREF m_Azure3;
	static const COLORREF m_Azure4;
	static const COLORREF m_Beet;
	static const COLORREF m_Beige;
	static const COLORREF m_Bisque;
	static const COLORREF m_Bisque1;
	static const COLORREF m_Bisque2;
	static const COLORREF m_Bisque3;
	static const COLORREF m_Bisque4;
	static const COLORREF m_Black;
	static const COLORREF m_BlanchedAlmond;
	static const COLORREF m_Blue;
	static const COLORREF m_Blue1;
	static const COLORREF m_Blue2;
	static const COLORREF m_Blue3;
	static const COLORREF m_Blue4;
	static const COLORREF m_BlueViolet;
	static const COLORREF m_BrightGray;
	static const COLORREF m_Brown;
	static const COLORREF m_Brown1;
	static const COLORREF m_Brown2;
	static const COLORREF m_Brown3;
	static const COLORREF m_Brown4;
	static const COLORREF m_Burlywood;
	static const COLORREF m_Burlywood1;
	static const COLORREF m_Burlywood2;
	static const COLORREF m_Burlywood3;
	static const COLORREF m_Burlywood4;
	static const COLORREF m_CadetBlue;
	static const COLORREF m_CadetBlue1;
	static const COLORREF m_CadetBlue2;
	static const COLORREF m_CadetBlue3;
	static const COLORREF m_CadetBlue4;
	static const COLORREF m_Chartreuse;
	static const COLORREF m_Chartreuse1;
	static const COLORREF m_Chartreuse2;
	static const COLORREF m_Chartreuse3;
	static const COLORREF m_Chartreuse4;
	static const COLORREF m_Chocolate;
	static const COLORREF m_Chocolate1;
	static const COLORREF m_Chocolate2;
	static const COLORREF m_Chocolate3;
	static const COLORREF m_Chocolate4;
	static const COLORREF m_Coral;
	static const COLORREF m_Coral1;
	static const COLORREF m_Coral2;
	static const COLORREF m_Coral3;
	static const COLORREF m_Coral4;
	static const COLORREF m_CornflowerBlue;
	static const COLORREF m_Cornsilk;
	static const COLORREF m_Cornsilk1;
	static const COLORREF m_Cornsilk2;
	static const COLORREF m_Cornsilk3;
	static const COLORREF m_Cornsilk4;
	static const COLORREF m_Crimson;
	static const COLORREF m_Cyan;
	static const COLORREF m_Cyan1;
	static const COLORREF m_Cyan2;
	static const COLORREF m_Cyan3;
	static const COLORREF m_Cyan4;
	static const COLORREF m_DarkBlue;
	static const COLORREF m_DarkCyan;
	static const COLORREF m_DarkGoldenrod;
	static const COLORREF m_DarkGoldenrod1;
	static const COLORREF m_DarkGoldenrod2;
	static const COLORREF m_DarkGoldenrod3;
	static const COLORREF m_DarkGoldenrod4;
	static const COLORREF m_DarkGray;
	static const COLORREF m_DarkGreen;
	static const COLORREF m_DarkKhaki;
	static const COLORREF m_DarkMagenta;
	static const COLORREF m_DarkOliveGreen;
	static const COLORREF m_DarkOliveGreen1;
	static const COLORREF m_DarkOliveGreen2;
	static const COLORREF m_DarkOliveGreen3;
	static const COLORREF m_DarkOliveGreen4;
	static const COLORREF m_DarkOrange;
	static const COLORREF m_DarkOrange1;
	static const COLORREF m_DarkOrange2;
	static const COLORREF m_DarkOrange3;
	static const COLORREF m_DarkOrange4;
	static const COLORREF m_DarkOrchid;
	static const COLORREF m_DarkOrchid1;
	static const COLORREF m_DarkOrchid2;
	static const COLORREF m_DarkOrchid3;
	static const COLORREF m_DarkOrchid4;
	static const COLORREF m_DarkRed;
	static const COLORREF m_DarkSalmon;
	static const COLORREF m_DarkSeaGreen;
	static const COLORREF m_DarkSeaGreen1;
	static const COLORREF m_DarkSeaGreen2;
	static const COLORREF m_DarkSeaGreen3;
	static const COLORREF m_DarkSeaGreen4;
	static const COLORREF m_DarkSlateBlue;
	static const COLORREF m_DarkSlateGray;
	static const COLORREF m_DarkSlateGray1;
	static const COLORREF m_DarkSlateGray2;
	static const COLORREF m_DarkSlateGray3;
	static const COLORREF m_DarkSlateGray4;
	static const COLORREF m_DarkTurquoise;
	static const COLORREF m_DarkViolet;
	static const COLORREF m_DeepPink;
	static const COLORREF m_DeepPink1;
	static const COLORREF m_DeepPink2;
	static const COLORREF m_DeepPink3;
	static const COLORREF m_DeepPink4;
	static const COLORREF m_DeepSkyBlue;
	static const COLORREF m_DeepSkyBlue1;
	static const COLORREF m_DeepSkyBlue2;
	static const COLORREF m_DeepSkyBlue3;
	static const COLORREF m_DeepSkyBlue4;
	static const COLORREF m_DimGray;
	static const COLORREF m_DodgerBlue;
	static const COLORREF m_DodgerBlue1;
	static const COLORREF m_DodgerBlue2;
	static const COLORREF m_DodgerBlue3;
	static const COLORREF m_DodgerBlue4;
	static const COLORREF m_Firebrick;
	static const COLORREF m_Firebrick1;
	static const COLORREF m_Firebrick2;
	static const COLORREF m_Firebrick3;
	static const COLORREF m_Firebrick4;
	static const COLORREF m_FloralWhite;
	static const COLORREF m_ForestGreen;
	static const COLORREF m_Gainsboro;
	static const COLORREF m_GhostWhite;
	static const COLORREF m_Gold;
	static const COLORREF m_Gold1;
	static const COLORREF m_Gold2;
	static const COLORREF m_Gold3;
	static const COLORREF m_Gold4;
	static const COLORREF m_Goldenrod;
	static const COLORREF m_Goldenrod1;
	static const COLORREF m_Goldenrod2;
	static const COLORREF m_Goldenrod3;
	static const COLORREF m_Goldenrod4;
	static const COLORREF m_Gray;
	static const COLORREF m_Gray0;
	static const COLORREF m_Gray2;
	static const COLORREF m_Gray3;
	static const COLORREF m_Gray4;
	static const COLORREF m_Gray5;
	static const COLORREF m_Gray6;
	static const COLORREF m_Gray7;
	static const COLORREF m_Gray8;
	static const COLORREF m_Gray9;
	static const COLORREF m_Gray1;
	static const COLORREF m_Gray10;
	static const COLORREF m_Gray11;
	static const COLORREF m_Gray12;
	static const COLORREF m_Gray13;
	static const COLORREF m_Gray14;
	static const COLORREF m_Gray15;
	static const COLORREF m_Gray16;
	static const COLORREF m_Gray17;
	static const COLORREF m_Gray18;
	static const COLORREF m_Gray19;
	static const COLORREF m_Gray20;
	static const COLORREF m_Gray21;
	static const COLORREF m_Gray22;
	static const COLORREF m_Gray23;
	static const COLORREF m_Gray24;
	static const COLORREF m_Gray25;
	static const COLORREF m_Gray26;
	static const COLORREF m_Gray27;
	static const COLORREF m_Gray28;
	static const COLORREF m_Gray29;
	static const COLORREF m_Gray30;
	static const COLORREF m_Gray31;
	static const COLORREF m_Gray32;
	static const COLORREF m_Gray33;
	static const COLORREF m_Gray34;
	static const COLORREF m_Gray35;
	static const COLORREF m_Gray36;
	static const COLORREF m_Gray37;
	static const COLORREF m_Gray38;
	static const COLORREF m_Gray39;
	static const COLORREF m_Gray40;
	static const COLORREF m_Gray41;
	static const COLORREF m_Gray42;
	static const COLORREF m_Gray43;
	static const COLORREF m_Gray44;
	static const COLORREF m_Gray45;
	static const COLORREF m_Gray46;
	static const COLORREF m_Gray47;
	static const COLORREF m_Gray48;
	static const COLORREF m_Gray49;
	static const COLORREF m_Gray50;
	static const COLORREF m_Gray51;
	static const COLORREF m_Gray52;
	static const COLORREF m_Gray53;
	static const COLORREF m_Gray54;
	static const COLORREF m_Gray55;
	static const COLORREF m_Gray56;
	static const COLORREF m_Gray57;
	static const COLORREF m_Gray58;
	static const COLORREF m_Gray59;
	static const COLORREF m_Gray60;
	static const COLORREF m_Gray61;
	static const COLORREF m_Gray62;
	static const COLORREF m_Gray63;
	static const COLORREF m_Gray64;
	static const COLORREF m_Gray65;
	static const COLORREF m_Gray66;
	static const COLORREF m_Gray67;
	static const COLORREF m_Gray68;
	static const COLORREF m_Gray69;
	static const COLORREF m_Gray70;
	static const COLORREF m_Gray71;
	static const COLORREF m_Gray72;
	static const COLORREF m_Gray73;
	static const COLORREF m_Gray74;
	static const COLORREF m_Gray75;
	static const COLORREF m_Gray76;
	static const COLORREF m_Gray77;
	static const COLORREF m_Gray78;
	static const COLORREF m_Gray79;
	static const COLORREF m_Gray80;
	static const COLORREF m_Gray81;
	static const COLORREF m_Gray82;
	static const COLORREF m_Gray83;
	static const COLORREF m_Gray84;
	static const COLORREF m_Gray85;
	static const COLORREF m_Gray86;
	static const COLORREF m_Gray87;
	static const COLORREF m_Gray88;
	static const COLORREF m_Gray89;
	static const COLORREF m_Gray90;
	static const COLORREF m_Gray91;
	static const COLORREF m_Gray92;
	static const COLORREF m_Gray93;
	static const COLORREF m_Gray94;
	static const COLORREF m_Gray95;
	static const COLORREF m_Gray96;
	static const COLORREF m_Gray97;
	static const COLORREF m_Gray98;
	static const COLORREF m_Gray99;
	static const COLORREF m_Gray100;
	static const COLORREF m_Green;
	static const COLORREF m_Green1;
	static const COLORREF m_Green2;
	static const COLORREF m_Green3;
	static const COLORREF m_Green4;
	static const COLORREF m_GreenYellow;
	static const COLORREF m_Honeydew;
	static const COLORREF m_Honeydew1;
	static const COLORREF m_Honeydew2;
	static const COLORREF m_Honeydew3;
	static const COLORREF m_Honeydew4;
	static const COLORREF m_HotPink;
	static const COLORREF m_HotPink1;
	static const COLORREF m_HotPink2;
	static const COLORREF m_HotPink3;
	static const COLORREF m_HotPink4;
	static const COLORREF m_IndianRed;
	static const COLORREF m_IndianRed1;
	static const COLORREF m_IndianRed2;
	static const COLORREF m_IndianRed3;
	static const COLORREF m_IndianRed4;
	static const COLORREF m_Indigo;
	static const COLORREF m_Indigo2;
	static const COLORREF m_Ivory;
	static const COLORREF m_Ivory1;
	static const COLORREF m_Ivory2;
	static const COLORREF m_Ivory3;
	static const COLORREF m_Ivory4;
	static const COLORREF m_Khaki;
	static const COLORREF m_Khaki1;
	static const COLORREF m_Khaki2;
	static const COLORREF m_Khaki3;
	static const COLORREF m_Khaki4;
	static const COLORREF m_Lavender;
	static const COLORREF m_LavenderBlush;
	static const COLORREF m_LavenderBlush1;
	static const COLORREF m_LavenderBlush2;
	static const COLORREF m_LavenderBlush3;
	static const COLORREF m_LavenderBlush4;
	static const COLORREF m_LawnGreen;
	static const COLORREF m_LemonChiffon;
	static const COLORREF m_LemonChiffon1;
	static const COLORREF m_LemonChiffon2;
	static const COLORREF m_LemonChiffon3;
	static const COLORREF m_LemonChiffon4;
	static const COLORREF m_LightBlue;
	static const COLORREF m_LightBlue1;
	static const COLORREF m_LightBlue2;
	static const COLORREF m_LightBlue3;
	static const COLORREF m_LightBlue4;
	static const COLORREF m_LightCoral;
	static const COLORREF m_LightCyan;
	static const COLORREF m_LightCyan1;
	static const COLORREF m_LightCyan2;
	static const COLORREF m_LightCyan3;
	static const COLORREF m_LightCyan4;
	static const COLORREF m_LightGoldenrod;
	static const COLORREF m_LightGoldenrod1;
	static const COLORREF m_LightGoldenrod2;
	static const COLORREF m_LightGoldenrod3;
	static const COLORREF m_LightGoldenrod4;
	static const COLORREF m_LightGoldenrodYellow;
	static const COLORREF m_LightGray;
	static const COLORREF m_LightGreen;
	static const COLORREF m_LightPink;
	static const COLORREF m_LightPink1;
	static const COLORREF m_LightPink2;
	static const COLORREF m_LightPink3;
	static const COLORREF m_LightPink4;
	static const COLORREF m_LightSalmon;
	static const COLORREF m_LightSalmon1;
	static const COLORREF m_LightSalmon2;
	static const COLORREF m_LightSalmon3;
	static const COLORREF m_LightSalmon4;
	static const COLORREF m_LightSeaGreen;
	static const COLORREF m_LightSkyBlue;
	static const COLORREF m_LightSkyBlue1;
	static const COLORREF m_LightSkyBlue2;
	static const COLORREF m_LightSkyBlue3;
	static const COLORREF m_LightSkyBlue4;
	static const COLORREF m_LightSlateBlue;
	static const COLORREF m_LightSlateGray;
	static const COLORREF m_LightSteelBlue;
	static const COLORREF m_LightSteelBlue1;
	static const COLORREF m_LightSteelBlue2;
	static const COLORREF m_LightSteelBlue3;
	static const COLORREF m_LightSteelBlue4;
	static const COLORREF m_LightYellow;
	static const COLORREF m_LightYellow1;
	static const COLORREF m_LightYellow2;
	static const COLORREF m_LightYellow3;
	static const COLORREF m_LightYellow4;
	static const COLORREF m_LimeGreen;
	static const COLORREF m_Linen;
	static const COLORREF m_Magenta;
	static const COLORREF m_Magenta1;
	static const COLORREF m_Magenta2;
	static const COLORREF m_Magenta3;
	static const COLORREF m_Magenta4;
	static const COLORREF m_Maroon;
	static const COLORREF m_Maroon1;
	static const COLORREF m_Maroon2;
	static const COLORREF m_Maroon3;
	static const COLORREF m_Maroon4;
	static const COLORREF m_MediumAquamarine;
	static const COLORREF m_MediumBlue;
	static const COLORREF m_MediumGray;
	static const COLORREF m_MediumOrchid;
	static const COLORREF m_MediumOrchid1;
	static const COLORREF m_MediumOrchid2;
	static const COLORREF m_MediumOrchid3;
	static const COLORREF m_MediumOrchid4;
	static const COLORREF m_MediumPurple;
	static const COLORREF m_MediumPurple1;
	static const COLORREF m_MediumPurple2;
	static const COLORREF m_MediumPurple3;
	static const COLORREF m_MediumPurple4;
	static const COLORREF m_MediumSeaGreen;
	static const COLORREF m_MediumSlateBlue;
	static const COLORREF m_MediumSpringGreen;
	static const COLORREF m_MediumTurquoise;
	static const COLORREF m_MediumVioletRed;
	static const COLORREF m_MidnightBlue;
	static const COLORREF m_MintCream;
	static const COLORREF m_MistyRose;
	static const COLORREF m_MistyRose1;
	static const COLORREF m_MistyRose2;
	static const COLORREF m_MistyRose3;
	static const COLORREF m_MistyRose4;
	static const COLORREF m_Moccasin;
	static const COLORREF m_NavajoWhite;
	static const COLORREF m_NavajoWhite1;
	static const COLORREF m_NavajoWhite2;
	static const COLORREF m_NavajoWhite3;
	static const COLORREF m_NavajoWhite4;
	static const COLORREF m_Navy;
	static const COLORREF m_NavyBlue;
	static const COLORREF m_OldLace;
	static const COLORREF m_OliveDrab;
	static const COLORREF m_OliveDrab1;
	static const COLORREF m_OliveDrab2;
	static const COLORREF m_OliveDrab3;
	static const COLORREF m_OliveDrab4;
	static const COLORREF m_Orange;
	static const COLORREF m_Orange1;
	static const COLORREF m_Orange2;
	static const COLORREF m_Orange3;
	static const COLORREF m_Orange4;
	static const COLORREF m_OrangeRed;
	static const COLORREF m_OrangeRed1;
	static const COLORREF m_OrangeRed2;
	static const COLORREF m_OrangeRed3;
	static const COLORREF m_OrangeRed4;
	static const COLORREF m_Orchid;
	static const COLORREF m_Orchid1;
	static const COLORREF m_Orchid2;
	static const COLORREF m_Orchid3;
	static const COLORREF m_Orchid4;
	static const COLORREF m_PaleGoldenrod;
	static const COLORREF m_PaleGreen;
	static const COLORREF m_PaleGreen1;
	static const COLORREF m_PaleGreen2;
	static const COLORREF m_PaleGreen3;
	static const COLORREF m_PaleGreen4;
	static const COLORREF m_PaleTurquoise;
	static const COLORREF m_PaleTurquoise1;
	static const COLORREF m_PaleTurquoise2;
	static const COLORREF m_PaleTurquoise3;
	static const COLORREF m_PaleTurquoise4;
	static const COLORREF m_PaleVioletRed;
	static const COLORREF m_PaleVioletRed1;
	static const COLORREF m_PaleVioletRed2;
	static const COLORREF m_PaleVioletRed3;
	static const COLORREF m_PaleVioletRed4;
	static const COLORREF m_PapayaWhip;
	static const COLORREF m_PeachPuff;
	static const COLORREF m_PeachPuff1;
	static const COLORREF m_PeachPuff2;
	static const COLORREF m_PeachPuff3;
	static const COLORREF m_PeachPuff4;
	static const COLORREF m_Peru;
	static const COLORREF m_Pink;
	static const COLORREF m_Pink1;
	static const COLORREF m_Pink2;
	static const COLORREF m_Pink3;
	static const COLORREF m_Pink4;
	static const COLORREF m_Plum;
	static const COLORREF m_Plum1;
	static const COLORREF m_Plum2;
	static const COLORREF m_Plum3;
	static const COLORREF m_Plum4;
	static const COLORREF m_PowderBlue;
	static const COLORREF m_Purple;
	static const COLORREF m_Purple1;
	static const COLORREF m_Purple2;
	static const COLORREF m_Purple3;
	static const COLORREF m_Purple4;
	static const COLORREF m_Red;
	static const COLORREF m_Red1;
	static const COLORREF m_Red2;
	static const COLORREF m_Red3;
	static const COLORREF m_Red4;
	static const COLORREF m_RosyBrown;
	static const COLORREF m_RosyBrown1;
	static const COLORREF m_RosyBrown2;
	static const COLORREF m_RosyBrown3;
	static const COLORREF m_RosyBrown4;
	static const COLORREF m_RoyalBlue;
	static const COLORREF m_RoyalBlue1;
	static const COLORREF m_RoyalBlue2;
	static const COLORREF m_RoyalBlue3;
	static const COLORREF m_RoyalBlue4;
	static const COLORREF m_SaddleBrown;
	static const COLORREF m_Salmon;
	static const COLORREF m_Salmon1;
	static const COLORREF m_Salmon2;
	static const COLORREF m_Salmon3;
	static const COLORREF m_Salmon4;
	static const COLORREF m_SandyBrown;
	static const COLORREF m_SeaGreen;
	static const COLORREF m_SeaGreen1;
	static const COLORREF m_SeaGreen2;
	static const COLORREF m_SeaGreen3;
	static const COLORREF m_SeaGreen4;
	static const COLORREF m_Seashell;
	static const COLORREF m_Seashell1;
	static const COLORREF m_Seashell2;
	static const COLORREF m_Seashell3;
	static const COLORREF m_Seashell4;
	static const COLORREF m_Sienna;
	static const COLORREF m_Sienna1;
	static const COLORREF m_Sienna2;
	static const COLORREF m_Sienna3;
	static const COLORREF m_Sienna4;
	static const COLORREF m_SkyBlue;
	static const COLORREF m_SkyBlue1;
	static const COLORREF m_SkyBlue2;
	static const COLORREF m_SkyBlue3;
	static const COLORREF m_SkyBlue4;
	static const COLORREF m_SlateBlue;
	static const COLORREF m_SlateBlue1;
	static const COLORREF m_SlateBlue2;
	static const COLORREF m_SlateBlue3;
	static const COLORREF m_SlateBlue4;
	static const COLORREF m_SlateGray;
	static const COLORREF m_SlateGray1;
	static const COLORREF m_SlateGray2;
	static const COLORREF m_SlateGray3;
	static const COLORREF m_SlateGray4;
	static const COLORREF m_Snow;
	static const COLORREF m_Snow1;
	static const COLORREF m_Snow2;
	static const COLORREF m_Snow3;
	static const COLORREF m_Snow4;
	static const COLORREF m_SpringGreen;
	static const COLORREF m_SpringGreen1;
	static const COLORREF m_SpringGreen2;
	static const COLORREF m_SpringGreen3;
	static const COLORREF m_SpringGreen4;
	static const COLORREF m_SteelBlue;
	static const COLORREF m_SteelBlue1;
	static const COLORREF m_SteelBlue2;
	static const COLORREF m_SteelBlue3;
	static const COLORREF m_SteelBlue4;
	static const COLORREF m_Tan;
	static const COLORREF m_Tan1;
	static const COLORREF m_Tan2;
	static const COLORREF m_Tan3;
	static const COLORREF m_Tan4;
	static const COLORREF m_Teal;
	static const COLORREF m_Thistle;
	static const COLORREF m_Thistle1;
	static const COLORREF m_Thistle2;
	static const COLORREF m_Thistle3;
	static const COLORREF m_Thistle4;
	static const COLORREF m_Tomato;
	static const COLORREF m_Tomato1;
	static const COLORREF m_Tomato2;
	static const COLORREF m_Tomato3;
	static const COLORREF m_Tomato4;
	static const COLORREF m_Turquoise;
	static const COLORREF m_Turquoise1;
	static const COLORREF m_Turquoise2;
	static const COLORREF m_Turquoise3;
	static const COLORREF m_Turquoise4;
	static const COLORREF m_VeryDarkGray;
	static const COLORREF m_VeryLightGray;
	static const COLORREF m_Violet;
	static const COLORREF m_VioletRed;
	static const COLORREF m_VioletRed1;
	static const COLORREF m_VioletRed2;
	static const COLORREF m_VioletRed3;
	static const COLORREF m_VioletRed4;
	static const COLORREF m_Wheat;
	static const COLORREF m_Wheat1;
	static const COLORREF m_Wheat2;
	static const COLORREF m_Wheat3;
	static const COLORREF m_Wheat4;
	static const COLORREF m_White;
	static const COLORREF m_WhiteSmoke;
	static const COLORREF m_Yellow;
	static const COLORREF m_Yellow1;
	static const COLORREF m_Yellow2;
	static const COLORREF m_Yellow3;
	static const COLORREF m_Yellow4;
	static const COLORREF m_YellowGreen;

protected:
private:
	
// Member functions ---------------------------------------------------------
public:
    static COLORREF HSBtoRGB(float hue, float saturation, float brightness);
    static COLORREF HSBtoRGB(BYTE hue, BYTE saturation, BYTE brightness);
	// --- In  : hue : the hue component of the color
	//			 saturation : the saturation component of the color
	//			 brightness : the brightness component of the color
	// --- Out : 
	// --- Returns : the RGB value of the color
	// --- Effect : Returns the RGB value corresponding to the color defined by the
    //				hue, saturation, and brightness components.

	static void RGBtoHSBFloat(int r, int g, int b, float* pHSBVals);
	static void RGBtoHSBInt(BYTE r, BYTE g, BYTE b, BYTE* pHSBVals);
	// --- In  : r : the red component of the color
	//			 g : the green component of the color
	//			 b : the blue component of the color
	// --- Out : pHSBVals : the array used to store the results [hue, saturation, brightness]
	// --- Returns :
	// --- Effect : Returns the HSB values corresponding to the color defined by the
    //				red, green, and blue components.

	static void ColorrefToHSB(COLORREF clrRGB, float* pHSBVals);
	static void ColorrefToHSB(COLORREF clrRGB, BYTE* pHSBVals);
	// --- In  : clrRGB : the RGB value of the color
	// --- Out : pHSBVals : the array used to store the results [hue, saturation, brightness]
	// --- Returns :
	// --- Effect : Returns the HSB values corresponding to the color defined by the
    //				RGB value of the color.

	static COLORREF RGBtoGrayscale(COLORREF clr);
	// --- In  : clr : the RGB value of the color
	// --- Out : 
	// --- Returns: returns corresponding grayscale approximation of clr color
	// --- Effect : convert RGB color to corresponding grayscale color

    static COLORREF CMYKtoRGB(WORD cyan, WORD magenta, WORD yellow, WORD black);
	// --- In  :	cyan : the cyan component of the CMYK color
	//				magenta : the magenta component of the CMYK color
	//				yellow : the yellow component of the CMYK color
	//				black : the black component of the CMYK color
	// --- Out : 
	// --- Returns: the RGB value of the CMYK color
	// --- Effect : Returns the RGB value corresponding to the color defined in 
	//				CMYK color space.
    static COLORREF CMYKtoRGB(COLORREF clrCMYK);
	// --- In  :	clrCMYK	: color in CMYK color space
	// --- Out : 
	// --- Returns: the RGB value of the CMYK color
	// --- Effect : Returns the RGB value corresponding to the color defined in 
	//				CMYK color space.

protected:
	// No object of this class should be constructed
	COXColor();
	virtual ~COXColor();

	static BYTE HueToRGB(WORD n1, WORD n2, BYTE hue);

private:
                   
};

#endif // __OXCOLOR_H__
// ==========================================================================
