// ==========================================================================
//				Class Implementation : COXColor
// ==========================================================================

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved                      
			  
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OXColorSpace.h"

#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////
// Definition of static members
const COLORREF COXColor::m_AliceBlue	 = RGB(0xF0, 0xF8, 0xFF);
const COLORREF COXColor::m_AntiqueWhite	 = RGB(0xFA, 0xEB, 0xD7);
const COLORREF COXColor::m_AntiqueWhite1	 = RGB(0xFF, 0xEF, 0xDB);
const COLORREF COXColor::m_AntiqueWhite2	 = RGB(0xEE, 0xDF, 0xCC);
const COLORREF COXColor::m_AntiqueWhite3	 = RGB(0xCD, 0xC0, 0xB0);
const COLORREF COXColor::m_AntiqueWhite4	 = RGB(0x8B, 0x83, 0x78);
const COLORREF COXColor::m_Aquamarine	 = RGB(0x7F, 0xFF, 0xD4);
const COLORREF COXColor::m_Aquamarine1	 = RGB(0x7F, 0xFF, 0xD4);
const COLORREF COXColor::m_Aquamarine2	 = RGB(0x76, 0xEE, 0xC6);
const COLORREF COXColor::m_Aquamarine3	 = RGB(0x66, 0xCD, 0xAA);
const COLORREF COXColor::m_Aquamarine4	 = RGB(0x45, 0x8B, 0x74);
const COLORREF COXColor::m_Azure	 = RGB(0xF0, 0xFF, 0xFF);
const COLORREF COXColor::m_Azure1	 = RGB(0xF0, 0xFF, 0xFF);
const COLORREF COXColor::m_Azure2	 = RGB(0xE0, 0xEE, 0xEE);
const COLORREF COXColor::m_Azure3	 = RGB(0xC1, 0xCD, 0xCD);
const COLORREF COXColor::m_Azure4	 = RGB(0x83, 0x8B, 0x8B);
const COLORREF COXColor::m_Beet	 = RGB(0x8E, 0x38, 0x8E);
const COLORREF COXColor::m_Beige	 = RGB(0xF5, 0xF5, 0xDC);
const COLORREF COXColor::m_Bisque	 = RGB(0xFF, 0xE4, 0xC4);
const COLORREF COXColor::m_Bisque1	 = RGB(0xFF, 0xE4, 0xC4);
const COLORREF COXColor::m_Bisque2	 = RGB(0xEE, 0xD5, 0xB7);
const COLORREF COXColor::m_Bisque3	 = RGB(0xCD, 0xB7, 0x9E);
const COLORREF COXColor::m_Bisque4	 = RGB(0x8B, 0x7D, 0x6B);
const COLORREF COXColor::m_Black	 = RGB(0x00, 0x00, 0x00);
const COLORREF COXColor::m_BlanchedAlmond	 = RGB(0xFF, 0xEB, 0xCD);
const COLORREF COXColor::m_Blue	 = RGB(0x00, 0x00, 0xFF);
const COLORREF COXColor::m_Blue1	 = RGB(0x00, 0x00, 0xFF);
const COLORREF COXColor::m_Blue2	 = RGB(0x00, 0x00, 0xEE);
const COLORREF COXColor::m_Blue3	 = RGB(0x00, 0x00, 0xCD);
const COLORREF COXColor::m_Blue4	 = RGB(0x00, 0x00, 0x8B);
const COLORREF COXColor::m_BlueViolet	 = RGB(0x8A, 0x2B, 0xE2);
const COLORREF COXColor::m_BrightGray	 = RGB(0xC5, 0xC1, 0xAA);
const COLORREF COXColor::m_Brown	 = RGB(0xA5, 0x2A, 0x2A);
const COLORREF COXColor::m_Brown1	 = RGB(0xFF, 0x40, 0x40);
const COLORREF COXColor::m_Brown2	 = RGB(0xEE, 0x3B, 0x3B);
const COLORREF COXColor::m_Brown3	 = RGB(0xCD, 0x33, 0x33);
const COLORREF COXColor::m_Brown4	 = RGB(0x8B, 0x23, 0x23);
const COLORREF COXColor::m_Burlywood	 = RGB(0xDE, 0xB8, 0x87);
const COLORREF COXColor::m_Burlywood1	 = RGB(0xFF, 0xD3, 0x9B);
const COLORREF COXColor::m_Burlywood2	 = RGB(0xEE, 0xC5, 0x91);
const COLORREF COXColor::m_Burlywood3	 = RGB(0xCD, 0xAA, 0x7D);
const COLORREF COXColor::m_Burlywood4	 = RGB(0x8B, 0x73, 0x55);
const COLORREF COXColor::m_CadetBlue	 = RGB(0x5F, 0x9E, 0xA0);
const COLORREF COXColor::m_CadetBlue1	 = RGB(0x98, 0xF5, 0xFF);
const COLORREF COXColor::m_CadetBlue2	 = RGB(0x8E, 0xE5, 0xEE);
const COLORREF COXColor::m_CadetBlue3	 = RGB(0x7A, 0xC5, 0xCD);
const COLORREF COXColor::m_CadetBlue4	 = RGB(0x53, 0x86, 0x8B);
const COLORREF COXColor::m_Chartreuse	 = RGB(0x71, 0xC6, 0x71);
const COLORREF COXColor::m_Chartreuse1	 = RGB(0x7F, 0xFF, 0x00);
const COLORREF COXColor::m_Chartreuse2	 = RGB(0x76, 0xEE, 0x00);
const COLORREF COXColor::m_Chartreuse3	 = RGB(0x66, 0xCD, 0x00);
const COLORREF COXColor::m_Chartreuse4	 = RGB(0x45, 0x8B, 0x00);
const COLORREF COXColor::m_Chocolate	 = RGB(0xD2, 0x69, 0x1E);
const COLORREF COXColor::m_Chocolate1	 = RGB(0xFF, 0x7F, 0x24);
const COLORREF COXColor::m_Chocolate2	 = RGB(0xEE, 0x76, 0x21);
const COLORREF COXColor::m_Chocolate3	 = RGB(0xCD, 0x66, 0x1D);
const COLORREF COXColor::m_Chocolate4	 = RGB(0x8B, 0x45, 0x13);
const COLORREF COXColor::m_Coral	 = RGB(0xFF, 0x7F, 0x50);
const COLORREF COXColor::m_Coral1	 = RGB(0xFF, 0x72, 0x56);
const COLORREF COXColor::m_Coral2	 = RGB(0xEE, 0x6A, 0x50);
const COLORREF COXColor::m_Coral3	 = RGB(0xCD, 0x5B, 0x45);
const COLORREF COXColor::m_Coral4	 = RGB(0x8B, 0x3E, 0x2F);
const COLORREF COXColor::m_CornflowerBlue	 = RGB(0x64, 0x95, 0xED);
const COLORREF COXColor::m_Cornsilk	 = RGB(0xFF, 0xF8, 0xDC);
const COLORREF COXColor::m_Cornsilk1	 = RGB(0xFF, 0xF8, 0xDC);
const COLORREF COXColor::m_Cornsilk2	 = RGB(0xEE, 0xE8, 0xCD);
const COLORREF COXColor::m_Cornsilk3	 = RGB(0xCD, 0xC8, 0xB1);
const COLORREF COXColor::m_Cornsilk4	 = RGB(0x8B, 0x88, 0x78);
const COLORREF COXColor::m_Crimson	 = RGB(0xDC, 0x14, 0x3C);
const COLORREF COXColor::m_Cyan	 = RGB(0x00, 0xFF, 0xFF);
const COLORREF COXColor::m_Cyan1	 = RGB(0x00, 0xFF, 0xFF);
const COLORREF COXColor::m_Cyan2	 = RGB(0x00, 0xEE, 0xEE);
const COLORREF COXColor::m_Cyan3	 = RGB(0x00, 0xCD, 0xCD);
const COLORREF COXColor::m_Cyan4	 = RGB(0x00, 0x8B, 0x8B);
const COLORREF COXColor::m_DarkBlue	 = RGB(0x00, 0x00, 0x8B);
const COLORREF COXColor::m_DarkCyan	 = RGB(0x00, 0x8B, 0x8B);
const COLORREF COXColor::m_DarkGoldenrod	 = RGB(0xB8, 0x86, 0x0B);
const COLORREF COXColor::m_DarkGoldenrod1	 = RGB(0xFF, 0xB9, 0x0F);
const COLORREF COXColor::m_DarkGoldenrod2	 = RGB(0xEE, 0xAD, 0x0E);
const COLORREF COXColor::m_DarkGoldenrod3	 = RGB(0xCD, 0x95, 0x0C);
const COLORREF COXColor::m_DarkGoldenrod4	 = RGB(0x8B, 0x65, 0x08);
const COLORREF COXColor::m_DarkGray	 = RGB(0x55, 0x55, 0x55);
const COLORREF COXColor::m_DarkGreen	 = RGB(0x00, 0x64, 0x00);
const COLORREF COXColor::m_DarkKhaki	 = RGB(0xBD, 0xB7, 0x6B);
const COLORREF COXColor::m_DarkMagenta	 = RGB(0x8B, 0x00, 0x8B);
const COLORREF COXColor::m_DarkOliveGreen	 = RGB(0x55, 0x6B, 0x2F);
const COLORREF COXColor::m_DarkOliveGreen1	 = RGB(0xCA, 0xFF, 0x70);
const COLORREF COXColor::m_DarkOliveGreen2	 = RGB(0xBC, 0xEE, 0x68);
const COLORREF COXColor::m_DarkOliveGreen3	 = RGB(0xA2, 0xCD, 0x5A);
const COLORREF COXColor::m_DarkOliveGreen4	 = RGB(0x6E, 0x8B, 0x3D);
const COLORREF COXColor::m_DarkOrange	 = RGB(0xFF, 0x8C, 0x00);
const COLORREF COXColor::m_DarkOrange1	 = RGB(0xFF, 0x7F, 0x00);
const COLORREF COXColor::m_DarkOrange2	 = RGB(0xEE, 0x76, 0x00);
const COLORREF COXColor::m_DarkOrange3	 = RGB(0xCD, 0x66, 0x00);
const COLORREF COXColor::m_DarkOrange4	 = RGB(0x8B, 0x45, 0x00);
const COLORREF COXColor::m_DarkOrchid	 = RGB(0x99, 0x32, 0xCC);
const COLORREF COXColor::m_DarkOrchid1	 = RGB(0xBF, 0x3E, 0xFF);
const COLORREF COXColor::m_DarkOrchid2	 = RGB(0xB2, 0x3A, 0xEE);
const COLORREF COXColor::m_DarkOrchid3	 = RGB(0x9A, 0x32, 0xCD);
const COLORREF COXColor::m_DarkOrchid4	 = RGB(0x68, 0x22, 0x8B);
const COLORREF COXColor::m_DarkRed	 = RGB(0x8B, 0x00, 0x00);
const COLORREF COXColor::m_DarkSalmon	 = RGB(0xE9, 0x96, 0x7A);
const COLORREF COXColor::m_DarkSeaGreen	 = RGB(0x8F, 0xBC, 0x8F);
const COLORREF COXColor::m_DarkSeaGreen1	 = RGB(0xC1, 0xFF, 0xC1);
const COLORREF COXColor::m_DarkSeaGreen2	 = RGB(0xB4, 0xEE, 0xB4);
const COLORREF COXColor::m_DarkSeaGreen3	 = RGB(0x9B, 0xCD, 0x9B);
const COLORREF COXColor::m_DarkSeaGreen4	 = RGB(0x69, 0x8B, 0x69);
const COLORREF COXColor::m_DarkSlateBlue	 = RGB(0x48, 0x3D, 0x8B);
const COLORREF COXColor::m_DarkSlateGray	 = RGB(0x2F, 0x4F, 0x4F);
const COLORREF COXColor::m_DarkSlateGray1	 = RGB(0x97, 0xFF, 0xFF);
const COLORREF COXColor::m_DarkSlateGray2	 = RGB(0x8D, 0xEE, 0xEE);
const COLORREF COXColor::m_DarkSlateGray3	 = RGB(0x79, 0xCD, 0xCD);
const COLORREF COXColor::m_DarkSlateGray4	 = RGB(0x52, 0x8B, 0x8B);
const COLORREF COXColor::m_DarkTurquoise	 = RGB(0x00, 0xCE, 0xD1);
const COLORREF COXColor::m_DarkViolet	 = RGB(0x94, 0x00, 0xD3);
const COLORREF COXColor::m_DeepPink	 = RGB(0xFF, 0x14, 0x93);
const COLORREF COXColor::m_DeepPink1	 = RGB(0xFF, 0x14, 0x93);
const COLORREF COXColor::m_DeepPink2	 = RGB(0xEE, 0x12, 0x89);
const COLORREF COXColor::m_DeepPink3	 = RGB(0xCD, 0x10, 0x76);
const COLORREF COXColor::m_DeepPink4	 = RGB(0x8B, 0x0A, 0x50);
const COLORREF COXColor::m_DeepSkyBlue	 = RGB(0x00, 0xBF, 0xFF);
const COLORREF COXColor::m_DeepSkyBlue1	 = RGB(0x00, 0xBF, 0xFF);
const COLORREF COXColor::m_DeepSkyBlue2	 = RGB(0x00, 0xB2, 0xEE);
const COLORREF COXColor::m_DeepSkyBlue3	 = RGB(0x00, 0x9A, 0xCD);
const COLORREF COXColor::m_DeepSkyBlue4	 = RGB(0x00, 0x68, 0x8B);
const COLORREF COXColor::m_DimGray	 = RGB(0x69, 0x69, 0x69);
const COLORREF COXColor::m_DodgerBlue	 = RGB(0x1E, 0x90, 0xFF);
const COLORREF COXColor::m_DodgerBlue1	 = RGB(0x1E, 0x90, 0xFF);
const COLORREF COXColor::m_DodgerBlue2	 = RGB(0x1C, 0x86, 0xEE);
const COLORREF COXColor::m_DodgerBlue3	 = RGB(0x18, 0x74, 0xCD);
const COLORREF COXColor::m_DodgerBlue4	 = RGB(0x10, 0x4E, 0x8B);
const COLORREF COXColor::m_Firebrick	 = RGB(0xB2, 0x22, 0x22);
const COLORREF COXColor::m_Firebrick1	 = RGB(0xFF, 0x30, 0x30);
const COLORREF COXColor::m_Firebrick2	 = RGB(0xEE, 0x2C, 0x2C);
const COLORREF COXColor::m_Firebrick3	 = RGB(0xCD, 0x26, 0x26);
const COLORREF COXColor::m_Firebrick4	 = RGB(0x8B, 0x1A, 0x1A);
const COLORREF COXColor::m_FloralWhite	 = RGB(0xFF, 0xFA, 0xF0);
const COLORREF COXColor::m_ForestGreen	 = RGB(0x22, 0x8B, 0x22);
const COLORREF COXColor::m_Gainsboro	 = RGB(0xDC, 0xDC, 0xDC);
const COLORREF COXColor::m_GhostWhite	 = RGB(0xF8, 0xF8, 0xFF);
const COLORREF COXColor::m_Gold	 = RGB(0xFF, 0xD7, 0x00);
const COLORREF COXColor::m_Gold1	 = RGB(0xFF, 0xD7, 0x00);
const COLORREF COXColor::m_Gold2	 = RGB(0xEE, 0xC9, 0x00);
const COLORREF COXColor::m_Gold3	 = RGB(0xCD, 0xAD, 0x00);
const COLORREF COXColor::m_Gold4	 = RGB(0x8B, 0x75, 0x00);
const COLORREF COXColor::m_Goldenrod	 = RGB(0xDA, 0xA5, 0x20);
const COLORREF COXColor::m_Goldenrod1	 = RGB(0xFF, 0xC1, 0x25);
const COLORREF COXColor::m_Goldenrod2	 = RGB(0xEE, 0xB4, 0x22);
const COLORREF COXColor::m_Goldenrod3	 = RGB(0xCD, 0x9B, 0x1D);
const COLORREF COXColor::m_Goldenrod4	 = RGB(0x8B, 0x69, 0x14);
const COLORREF COXColor::m_Gray	 = RGB(0xBE, 0xBE, 0xBE);
const COLORREF COXColor::m_Gray0	 = RGB(0x00, 0x00, 0x00);
const COLORREF COXColor::m_Gray2	 = RGB(0x05, 0x05, 0x05);
const COLORREF COXColor::m_Gray3	 = RGB(0x08, 0x08, 0x08);
const COLORREF COXColor::m_Gray4	 = RGB(0x0A, 0x0A, 0x0A);
const COLORREF COXColor::m_Gray5	 = RGB(0x0D, 0x0D, 0x0D);
const COLORREF COXColor::m_Gray6	 = RGB(0x0F, 0x0F, 0x0F);
const COLORREF COXColor::m_Gray7	 = RGB(0x12, 0x12, 0x12);
const COLORREF COXColor::m_Gray8	 = RGB(0x14, 0x14, 0x14);
const COLORREF COXColor::m_Gray9	 = RGB(0x17, 0x17, 0x17);
const COLORREF COXColor::m_Gray1	 = RGB(0x03, 0x03, 0x03);
const COLORREF COXColor::m_Gray10	 = RGB(0x1A, 0x1A, 0x1A);
const COLORREF COXColor::m_Gray11	 = RGB(0x1C, 0x1C, 0x1C);
const COLORREF COXColor::m_Gray12	 = RGB(0x1E, 0x1E, 0x1E);
const COLORREF COXColor::m_Gray13	 = RGB(0x21, 0x21, 0x21);
const COLORREF COXColor::m_Gray14	 = RGB(0x24, 0x24, 0x24);
const COLORREF COXColor::m_Gray15	 = RGB(0x26, 0x26, 0x26);
const COLORREF COXColor::m_Gray16	 = RGB(0x29, 0x29, 0x29);
const COLORREF COXColor::m_Gray17	 = RGB(0x2B, 0x2B, 0x2B);
const COLORREF COXColor::m_Gray18	 = RGB(0x2E, 0x2E, 0x2E);
const COLORREF COXColor::m_Gray19	 = RGB(0x30, 0x30, 0x30);
const COLORREF COXColor::m_Gray20	 = RGB(0x33, 0x33, 0x33);
const COLORREF COXColor::m_Gray21	 = RGB(0x36, 0x36, 0x36);
const COLORREF COXColor::m_Gray22	 = RGB(0x38, 0x38, 0x38);
const COLORREF COXColor::m_Gray23	 = RGB(0x3B, 0x3B, 0x3B);
const COLORREF COXColor::m_Gray24	 = RGB(0x3D, 0x3D, 0x3D);
const COLORREF COXColor::m_Gray25	 = RGB(0x40, 0x40, 0x40);
const COLORREF COXColor::m_Gray26	 = RGB(0x42, 0x42, 0x42);
const COLORREF COXColor::m_Gray27	 = RGB(0x45, 0x45, 0x45);
const COLORREF COXColor::m_Gray28	 = RGB(0x47, 0x47, 0x47);
const COLORREF COXColor::m_Gray29	 = RGB(0x4A, 0x4A, 0x4A);
const COLORREF COXColor::m_Gray30	 = RGB(0x4D, 0x4D, 0x4D);
const COLORREF COXColor::m_Gray31	 = RGB(0x4F, 0x4F, 0x4F);
const COLORREF COXColor::m_Gray32	 = RGB(0x51, 0x51, 0x51);
const COLORREF COXColor::m_Gray33	 = RGB(0x54, 0x54, 0x54);
const COLORREF COXColor::m_Gray34	 = RGB(0x57, 0x57, 0x57);
const COLORREF COXColor::m_Gray35	 = RGB(0x59, 0x59, 0x59);
const COLORREF COXColor::m_Gray36	 = RGB(0x5B, 0x5B, 0x5B);
const COLORREF COXColor::m_Gray37	 = RGB(0x5E, 0x5E, 0x5E);
const COLORREF COXColor::m_Gray38	 = RGB(0x61, 0x61, 0x61);
const COLORREF COXColor::m_Gray39	 = RGB(0x63, 0x63, 0x63);
const COLORREF COXColor::m_Gray40	 = RGB(0x66, 0x66, 0x66);
const COLORREF COXColor::m_Gray41	 = RGB(0x69, 0x69, 0x69);
const COLORREF COXColor::m_Gray42	 = RGB(0x6B, 0x6B, 0x6B);
const COLORREF COXColor::m_Gray43	 = RGB(0x6E, 0x6E, 0x6E);
const COLORREF COXColor::m_Gray44	 = RGB(0x70, 0x70, 0x70);
const COLORREF COXColor::m_Gray45	 = RGB(0x73, 0x73, 0x73);
const COLORREF COXColor::m_Gray46	 = RGB(0x75, 0x75, 0x75);
const COLORREF COXColor::m_Gray47	 = RGB(0x78, 0x78, 0x78);
const COLORREF COXColor::m_Gray48	 = RGB(0x7A, 0x7A, 0x7A);
const COLORREF COXColor::m_Gray49	 = RGB(0x7D, 0x7D, 0x7D);
const COLORREF COXColor::m_Gray50	 = RGB(0x7F, 0x7F, 0x7F);
const COLORREF COXColor::m_Gray51	 = RGB(0x82, 0x82, 0x82);
const COLORREF COXColor::m_Gray52	 = RGB(0x84, 0x84, 0x84);
const COLORREF COXColor::m_Gray53	 = RGB(0x87, 0x87, 0x87);
const COLORREF COXColor::m_Gray54	 = RGB(0x8A, 0x8A, 0x8A);
const COLORREF COXColor::m_Gray55	 = RGB(0x8C, 0x8C, 0x8C);
const COLORREF COXColor::m_Gray56	 = RGB(0x8E, 0x8E, 0x8E);
const COLORREF COXColor::m_Gray57	 = RGB(0x91, 0x91, 0x91);
const COLORREF COXColor::m_Gray58	 = RGB(0x94, 0x94, 0x94);
const COLORREF COXColor::m_Gray59	 = RGB(0x96, 0x96, 0x96);
const COLORREF COXColor::m_Gray60	 = RGB(0x99, 0x99, 0x99);
const COLORREF COXColor::m_Gray61	 = RGB(0x9C, 0x9C, 0x9C);
const COLORREF COXColor::m_Gray62	 = RGB(0x9E, 0x9E, 0x9E);
const COLORREF COXColor::m_Gray63	 = RGB(0xA1, 0xA1, 0xA1);
const COLORREF COXColor::m_Gray64	 = RGB(0xA3, 0xA3, 0xA3);
const COLORREF COXColor::m_Gray65	 = RGB(0xA6, 0xA6, 0xA6);
const COLORREF COXColor::m_Gray66	 = RGB(0xA8, 0xA8, 0xA8);
const COLORREF COXColor::m_Gray67	 = RGB(0xAB, 0xAB, 0xAB);
const COLORREF COXColor::m_Gray68	 = RGB(0xAD, 0xAD, 0xAD);
const COLORREF COXColor::m_Gray69	 = RGB(0xB0, 0xB0, 0xB0);
const COLORREF COXColor::m_Gray70	 = RGB(0xB3, 0xB3, 0xB3);
const COLORREF COXColor::m_Gray71	 = RGB(0xB5, 0xB5, 0xB5);
const COLORREF COXColor::m_Gray72	 = RGB(0xB7, 0xB7, 0xB7);
const COLORREF COXColor::m_Gray73	 = RGB(0xBA, 0xBA, 0xBA);
const COLORREF COXColor::m_Gray74	 = RGB(0xBD, 0xBD, 0xBD);
const COLORREF COXColor::m_Gray75	 = RGB(0xBF, 0xBF, 0xBF);
const COLORREF COXColor::m_Gray76	 = RGB(0xC1, 0xC1, 0xC1);
const COLORREF COXColor::m_Gray77	 = RGB(0xC4, 0xC4, 0xC4);
const COLORREF COXColor::m_Gray78	 = RGB(0xC7, 0xC7, 0xC7);
const COLORREF COXColor::m_Gray79	 = RGB(0xC9, 0xC9, 0xC9);
const COLORREF COXColor::m_Gray80	 = RGB(0xCC, 0xCC, 0xCC);
const COLORREF COXColor::m_Gray81	 = RGB(0xCF, 0xCF, 0xCF);
const COLORREF COXColor::m_Gray82	 = RGB(0xD1, 0xD1, 0xD1);
const COLORREF COXColor::m_Gray83	 = RGB(0xD4, 0xD4, 0xD4);
const COLORREF COXColor::m_Gray84	 = RGB(0xD6, 0xD6, 0xD6);
const COLORREF COXColor::m_Gray85	 = RGB(0xD9, 0xD9, 0xD9);
const COLORREF COXColor::m_Gray86	 = RGB(0xDB, 0xDB, 0xDB);
const COLORREF COXColor::m_Gray87	 = RGB(0xDE, 0xDE, 0xDE);
const COLORREF COXColor::m_Gray88	 = RGB(0xE0, 0xE0, 0xE0);
const COLORREF COXColor::m_Gray89	 = RGB(0xE3, 0xE3, 0xE3);
const COLORREF COXColor::m_Gray90	 = RGB(0xE5, 0xE5, 0xE5);
const COLORREF COXColor::m_Gray91	 = RGB(0xE8, 0xE8, 0xE8);
const COLORREF COXColor::m_Gray92	 = RGB(0xEA, 0xEA, 0xEA);
const COLORREF COXColor::m_Gray93	 = RGB(0xED, 0xED, 0xED);
const COLORREF COXColor::m_Gray94	 = RGB(0xF0, 0xF0, 0xF0);
const COLORREF COXColor::m_Gray95	 = RGB(0xF2, 0xF2, 0xF2);
const COLORREF COXColor::m_Gray96	 = RGB(0xF4, 0xF4, 0xF4);
const COLORREF COXColor::m_Gray97	 = RGB(0xF7, 0xF7, 0xF7);
const COLORREF COXColor::m_Gray98	 = RGB(0xFA, 0xFA, 0xFA);
const COLORREF COXColor::m_Gray99	 = RGB(0xFC, 0xFC, 0xFC);
const COLORREF COXColor::m_Gray100	 = RGB(0xFF, 0xFF, 0xFF);
const COLORREF COXColor::m_Green	 = RGB(0x00, 0xFF, 0x00);
const COLORREF COXColor::m_Green1	 = RGB(0x00, 0xFF, 0x00);
const COLORREF COXColor::m_Green2	 = RGB(0x00, 0xEE, 0x00);
const COLORREF COXColor::m_Green3	 = RGB(0x00, 0xCD, 0x00);
const COLORREF COXColor::m_Green4	 = RGB(0x00, 0x8B, 0x00);
const COLORREF COXColor::m_GreenYellow	 = RGB(0xAD, 0xFF, 0x2F);
const COLORREF COXColor::m_Honeydew	 = RGB(0xF0, 0xFF, 0xF0);
const COLORREF COXColor::m_Honeydew1	 = RGB(0xF0, 0xFF, 0xF0);
const COLORREF COXColor::m_Honeydew2	 = RGB(0xE0, 0xEE, 0xE0);
const COLORREF COXColor::m_Honeydew3	 = RGB(0xC1, 0xCD, 0xC1);
const COLORREF COXColor::m_Honeydew4	 = RGB(0x83, 0x8B, 0x83);
const COLORREF COXColor::m_HotPink	 = RGB(0xFF, 0x69, 0xB4);
const COLORREF COXColor::m_HotPink1	 = RGB(0xFF, 0x6E, 0xB4);
const COLORREF COXColor::m_HotPink2	 = RGB(0xEE, 0x6A, 0xA7);
const COLORREF COXColor::m_HotPink3	 = RGB(0xCD, 0x60, 0x90);
const COLORREF COXColor::m_HotPink4	 = RGB(0x8B, 0x3A, 0x62);
const COLORREF COXColor::m_IndianRed	 = RGB(0xCD, 0x5C, 0x5C);
const COLORREF COXColor::m_IndianRed1	 = RGB(0xFF, 0x6A, 0x6A);
const COLORREF COXColor::m_IndianRed2	 = RGB(0xEE, 0x63, 0x63);
const COLORREF COXColor::m_IndianRed3	 = RGB(0xCD, 0x55, 0x55);
const COLORREF COXColor::m_IndianRed4	 = RGB(0x8B, 0x3A, 0x3A);
const COLORREF COXColor::m_Indigo	 = RGB(0x4B, 0x00, 0x82);
const COLORREF COXColor::m_Indigo2	 = RGB(0x21, 0x88, 0x68);
const COLORREF COXColor::m_Ivory	 = RGB(0xFF, 0xFF, 0xF0);
const COLORREF COXColor::m_Ivory1	 = RGB(0xFF, 0xFF, 0xF0);
const COLORREF COXColor::m_Ivory2	 = RGB(0xEE, 0xEE, 0xE0);
const COLORREF COXColor::m_Ivory3	 = RGB(0xCD, 0xCD, 0xC1);
const COLORREF COXColor::m_Ivory4	 = RGB(0x8B, 0x8B, 0x83);
const COLORREF COXColor::m_Khaki	 = RGB(0xF0, 0xE6, 0x8C);
const COLORREF COXColor::m_Khaki1	 = RGB(0xFF, 0xF6, 0x8F);
const COLORREF COXColor::m_Khaki2	 = RGB(0xEE, 0xE6, 0x85);
const COLORREF COXColor::m_Khaki3	 = RGB(0xCD, 0xC6, 0x73);
const COLORREF COXColor::m_Khaki4	 = RGB(0x8B, 0x86, 0x4E);
const COLORREF COXColor::m_Lavender	 = RGB(0xE6, 0xE6, 0xFA);
const COLORREF COXColor::m_LavenderBlush	 = RGB(0xFF, 0xF0, 0xF5);
const COLORREF COXColor::m_LavenderBlush1	 = RGB(0xFF, 0xF0, 0xF5);
const COLORREF COXColor::m_LavenderBlush2	 = RGB(0xEE, 0xE0, 0xE5);
const COLORREF COXColor::m_LavenderBlush3	 = RGB(0xCD, 0xC1, 0xC5);
const COLORREF COXColor::m_LavenderBlush4	 = RGB(0x8B, 0x83, 0x86);
const COLORREF COXColor::m_LawnGreen	 = RGB(0x7C, 0xFC, 0x00);
const COLORREF COXColor::m_LemonChiffon	 = RGB(0xFF, 0xFA, 0xCD);
const COLORREF COXColor::m_LemonChiffon1	 = RGB(0xFF, 0xFA, 0xCD);
const COLORREF COXColor::m_LemonChiffon2	 = RGB(0xEE, 0xE9, 0xBF);
const COLORREF COXColor::m_LemonChiffon3	 = RGB(0xCD, 0xC9, 0xA5);
const COLORREF COXColor::m_LemonChiffon4	 = RGB(0x8B, 0x89, 0x70);
const COLORREF COXColor::m_LightBlue	 = RGB(0x7D, 0x9E, 0xC0);
const COLORREF COXColor::m_LightBlue1	 = RGB(0xBF, 0xEF, 0xFF);
const COLORREF COXColor::m_LightBlue2	 = RGB(0xB2, 0xDF, 0xEE);
const COLORREF COXColor::m_LightBlue3	 = RGB(0x9A, 0xC0, 0xCD);
const COLORREF COXColor::m_LightBlue4	 = RGB(0x68, 0x83, 0x8B);
const COLORREF COXColor::m_LightCoral	 = RGB(0xF0, 0x80, 0x80);
const COLORREF COXColor::m_LightCyan	 = RGB(0xE0, 0xFF, 0xFF);
const COLORREF COXColor::m_LightCyan1	 = RGB(0xE0, 0xFF, 0xFF);
const COLORREF COXColor::m_LightCyan2	 = RGB(0xD1, 0xEE, 0xEE);
const COLORREF COXColor::m_LightCyan3	 = RGB(0xB4, 0xCD, 0xCD);
const COLORREF COXColor::m_LightCyan4	 = RGB(0x7A, 0x8B, 0x8B);
const COLORREF COXColor::m_LightGoldenrod	 = RGB(0xEE, 0xDD, 0x82);
const COLORREF COXColor::m_LightGoldenrod1	 = RGB(0xFF, 0xEC, 0x8B);
const COLORREF COXColor::m_LightGoldenrod2	 = RGB(0xEE, 0xDC, 0x82);
const COLORREF COXColor::m_LightGoldenrod3	 = RGB(0xCD, 0xBE, 0x70);
const COLORREF COXColor::m_LightGoldenrod4	 = RGB(0x8B, 0x81, 0x4C);
const COLORREF COXColor::m_LightGoldenrodYellow	 = RGB(0xFA, 0xFA, 0xD2);
const COLORREF COXColor::m_LightGray	 = RGB(0xAA, 0xAA, 0xAA);
const COLORREF COXColor::m_LightGreen	 = RGB(0x90, 0xEE, 0x90);
const COLORREF COXColor::m_LightPink	 = RGB(0xFF, 0xB6, 0xC1);
const COLORREF COXColor::m_LightPink1	 = RGB(0xFF, 0xAE, 0xB9);
const COLORREF COXColor::m_LightPink2	 = RGB(0xEE, 0xA2, 0xAD);
const COLORREF COXColor::m_LightPink3	 = RGB(0xCD, 0x8C, 0x95);
const COLORREF COXColor::m_LightPink4	 = RGB(0x8B, 0x5F, 0x65);
const COLORREF COXColor::m_LightSalmon	 = RGB(0xFF, 0xA0, 0x7A);
const COLORREF COXColor::m_LightSalmon1	 = RGB(0xFF, 0xA0, 0x7A);
const COLORREF COXColor::m_LightSalmon2	 = RGB(0xEE, 0x95, 0x72);
const COLORREF COXColor::m_LightSalmon3	 = RGB(0xCD, 0x81, 0x62);
const COLORREF COXColor::m_LightSalmon4	 = RGB(0x8B, 0x57, 0x42);
const COLORREF COXColor::m_LightSeaGreen	 = RGB(0x20, 0xB2, 0xAA);
const COLORREF COXColor::m_LightSkyBlue	 = RGB(0x87, 0xCE, 0xFA);
const COLORREF COXColor::m_LightSkyBlue1	 = RGB(0xB0, 0xE2, 0xFF);
const COLORREF COXColor::m_LightSkyBlue2	 = RGB(0xA4, 0xD3, 0xEE);
const COLORREF COXColor::m_LightSkyBlue3	 = RGB(0x8D, 0xB6, 0xCD);
const COLORREF COXColor::m_LightSkyBlue4	 = RGB(0x60, 0x7B, 0x8B);
const COLORREF COXColor::m_LightSlateBlue	 = RGB(0x84, 0x70, 0xFF);
const COLORREF COXColor::m_LightSlateGray	 = RGB(0x77, 0x88, 0x99);
const COLORREF COXColor::m_LightSteelBlue	 = RGB(0xB0, 0xC4, 0xDE);
const COLORREF COXColor::m_LightSteelBlue1	 = RGB(0xCA, 0xE1, 0xFF);
const COLORREF COXColor::m_LightSteelBlue2	 = RGB(0xBC, 0xD2, 0xEE);
const COLORREF COXColor::m_LightSteelBlue3	 = RGB(0xA2, 0xB5, 0xCD);
const COLORREF COXColor::m_LightSteelBlue4	 = RGB(0x6E, 0x7B, 0x8B);
const COLORREF COXColor::m_LightYellow	 = RGB(0xFF, 0xFF, 0xE0);
const COLORREF COXColor::m_LightYellow1	 = RGB(0xFF, 0xFF, 0xE0);
const COLORREF COXColor::m_LightYellow2	 = RGB(0xEE, 0xEE, 0xD1);
const COLORREF COXColor::m_LightYellow3	 = RGB(0xCD, 0xCD, 0xB4);
const COLORREF COXColor::m_LightYellow4	 = RGB(0x8B, 0x8B, 0x7A);
const COLORREF COXColor::m_LimeGreen	 = RGB(0x32, 0xCD, 0x32);
const COLORREF COXColor::m_Linen	 = RGB(0xFA, 0xF0, 0xE6);
const COLORREF COXColor::m_Magenta	 = RGB(0xFF, 0x00, 0xFF);
const COLORREF COXColor::m_Magenta1	 = RGB(0xFF, 0x00, 0xFF);
const COLORREF COXColor::m_Magenta2	 = RGB(0xEE, 0x00, 0xEE);
const COLORREF COXColor::m_Magenta3	 = RGB(0xCD, 0x00, 0xCD);
const COLORREF COXColor::m_Magenta4	 = RGB(0x8B, 0x00, 0x8B);
const COLORREF COXColor::m_Maroon	 = RGB(0xB0, 0x30, 0x60);
const COLORREF COXColor::m_Maroon1	 = RGB(0xFF, 0x34, 0xB3);
const COLORREF COXColor::m_Maroon2	 = RGB(0xEE, 0x30, 0xA7);
const COLORREF COXColor::m_Maroon3	 = RGB(0xCD, 0x29, 0x90);
const COLORREF COXColor::m_Maroon4	 = RGB(0x8B, 0x1C, 0x62);
const COLORREF COXColor::m_MediumAquamarine	 = RGB(0x66, 0xCD, 0xAA);
const COLORREF COXColor::m_MediumBlue	 = RGB(0x00, 0x00, 0xCD);
const COLORREF COXColor::m_MediumGray	 = RGB(0x84, 0x84, 0x84);
const COLORREF COXColor::m_MediumOrchid	 = RGB(0xBA, 0x55, 0xD3);
const COLORREF COXColor::m_MediumOrchid1	 = RGB(0xE0, 0x66, 0xFF);
const COLORREF COXColor::m_MediumOrchid2	 = RGB(0xD1, 0x5F, 0xEE);
const COLORREF COXColor::m_MediumOrchid3	 = RGB(0xB4, 0x52, 0xCD);
const COLORREF COXColor::m_MediumOrchid4	 = RGB(0x7A, 0x37, 0x8B);
const COLORREF COXColor::m_MediumPurple	 = RGB(0x93, 0x70, 0xDB);
const COLORREF COXColor::m_MediumPurple1	 = RGB(0xAB, 0x82, 0xFF);
const COLORREF COXColor::m_MediumPurple2	 = RGB(0x9F, 0x79, 0xEE);
const COLORREF COXColor::m_MediumPurple3	 = RGB(0x89, 0x68, 0xCD);
const COLORREF COXColor::m_MediumPurple4	 = RGB(0x5D, 0x47, 0x8B);
const COLORREF COXColor::m_MediumSeaGreen	 = RGB(0x3C, 0xB3, 0x71);
const COLORREF COXColor::m_MediumSlateBlue	 = RGB(0x7B, 0x68, 0xEE);
const COLORREF COXColor::m_MediumSpringGreen	 = RGB(0x00, 0xFA, 0x9A);
const COLORREF COXColor::m_MediumTurquoise	 = RGB(0x48, 0xD1, 0xCC);
const COLORREF COXColor::m_MediumVioletRed	 = RGB(0xC7, 0x15, 0x85);
const COLORREF COXColor::m_MidnightBlue	 = RGB(0x19, 0x19, 0x70);
const COLORREF COXColor::m_MintCream	 = RGB(0xF5, 0xFF, 0xFA);
const COLORREF COXColor::m_MistyRose	 = RGB(0xFF, 0xE4, 0xE1);
const COLORREF COXColor::m_MistyRose1	 = RGB(0xFF, 0xE4, 0xE1);
const COLORREF COXColor::m_MistyRose2	 = RGB(0xEE, 0xD5, 0xD2);
const COLORREF COXColor::m_MistyRose3	 = RGB(0xCD, 0xB7, 0xB5);
const COLORREF COXColor::m_MistyRose4	 = RGB(0x8B, 0x7D, 0x7B);
const COLORREF COXColor::m_Moccasin	 = RGB(0xFF, 0xE4, 0xB5);
const COLORREF COXColor::m_NavajoWhite	 = RGB(0xFF, 0xDE, 0xAD);
const COLORREF COXColor::m_NavajoWhite1	 = RGB(0xFF, 0xDE, 0xAD);
const COLORREF COXColor::m_NavajoWhite2	 = RGB(0xEE, 0xCF, 0xA1);
const COLORREF COXColor::m_NavajoWhite3	 = RGB(0xCD, 0xB3, 0x8B);
const COLORREF COXColor::m_NavajoWhite4	 = RGB(0x8B, 0x79, 0x5E);
const COLORREF COXColor::m_Navy	 = RGB(0x00, 0x00, 0x80);
const COLORREF COXColor::m_NavyBlue	 = RGB(0x00, 0x00, 0x80);
const COLORREF COXColor::m_OldLace	 = RGB(0xFD, 0xF5, 0xE6);
const COLORREF COXColor::m_OliveDrab	 = RGB(0x6B, 0x8E, 0x23);
const COLORREF COXColor::m_OliveDrab1	 = RGB(0xC0, 0xFF, 0x3E);
const COLORREF COXColor::m_OliveDrab2	 = RGB(0xB3, 0xEE, 0x3A);
const COLORREF COXColor::m_OliveDrab3	 = RGB(0x9A, 0xCD, 0x32);
const COLORREF COXColor::m_OliveDrab4	 = RGB(0x69, 0x8B, 0x22);
const COLORREF COXColor::m_Orange	 = RGB(0xFF, 0xA5, 0x00);
const COLORREF COXColor::m_Orange1	 = RGB(0xFF, 0xA5, 0x00);
const COLORREF COXColor::m_Orange2	 = RGB(0xEE, 0x9A, 0x00);
const COLORREF COXColor::m_Orange3	 = RGB(0xCD, 0x85, 0x00);
const COLORREF COXColor::m_Orange4	 = RGB(0x8B, 0x5A, 0x00);
const COLORREF COXColor::m_OrangeRed	 = RGB(0xFF, 0x45, 0x00);
const COLORREF COXColor::m_OrangeRed1	 = RGB(0xFF, 0x45, 0x00);
const COLORREF COXColor::m_OrangeRed2	 = RGB(0xEE, 0x40, 0x00);
const COLORREF COXColor::m_OrangeRed3	 = RGB(0xCD, 0x37, 0x00);
const COLORREF COXColor::m_OrangeRed4	 = RGB(0x8B, 0x25, 0x00);
const COLORREF COXColor::m_Orchid	 = RGB(0xDA, 0x70, 0xD6);
const COLORREF COXColor::m_Orchid1	 = RGB(0xFF, 0x83, 0xFA);
const COLORREF COXColor::m_Orchid2	 = RGB(0xEE, 0x7A, 0xE9);
const COLORREF COXColor::m_Orchid3	 = RGB(0xCD, 0x69, 0xC9);
const COLORREF COXColor::m_Orchid4	 = RGB(0x8B, 0x47, 0x89);
const COLORREF COXColor::m_PaleGoldenrod	 = RGB(0xEE, 0xE8, 0xAA);
const COLORREF COXColor::m_PaleGreen	 = RGB(0x98, 0xFB, 0x98);
const COLORREF COXColor::m_PaleGreen1	 = RGB(0x9A, 0xFF, 0x9A);
const COLORREF COXColor::m_PaleGreen2	 = RGB(0x90, 0xEE, 0x90);
const COLORREF COXColor::m_PaleGreen3	 = RGB(0x7C, 0xCD, 0x7C);
const COLORREF COXColor::m_PaleGreen4	 = RGB(0x54, 0x8B, 0x54);
const COLORREF COXColor::m_PaleTurquoise	 = RGB(0xAF, 0xEE, 0xEE);
const COLORREF COXColor::m_PaleTurquoise1	 = RGB(0xBB, 0xFF, 0xFF);
const COLORREF COXColor::m_PaleTurquoise2	 = RGB(0xAE, 0xEE, 0xEE);
const COLORREF COXColor::m_PaleTurquoise3	 = RGB(0x96, 0xCD, 0xCD);
const COLORREF COXColor::m_PaleTurquoise4	 = RGB(0x66, 0x8B, 0x8B);
const COLORREF COXColor::m_PaleVioletRed	 = RGB(0xDB, 0x70, 0x93);
const COLORREF COXColor::m_PaleVioletRed1	 = RGB(0xFF, 0x82, 0xAB);
const COLORREF COXColor::m_PaleVioletRed2	 = RGB(0xEE, 0x79, 0x9F);
const COLORREF COXColor::m_PaleVioletRed3	 = RGB(0xCD, 0x68, 0x89);
const COLORREF COXColor::m_PaleVioletRed4	 = RGB(0x8B, 0x47, 0x5D);
const COLORREF COXColor::m_PapayaWhip	 = RGB(0xFF, 0xEF, 0xD5);
const COLORREF COXColor::m_PeachPuff	 = RGB(0xFF, 0xDA, 0xB9);
const COLORREF COXColor::m_PeachPuff1	 = RGB(0xFF, 0xDA, 0xB9);
const COLORREF COXColor::m_PeachPuff2	 = RGB(0xEE, 0xCB, 0xAD);
const COLORREF COXColor::m_PeachPuff3	 = RGB(0xCD, 0xAF, 0x95);
const COLORREF COXColor::m_PeachPuff4	 = RGB(0x8B, 0x77, 0x65);
const COLORREF COXColor::m_Peru	 = RGB(0xCD, 0x85, 0x3F);
const COLORREF COXColor::m_Pink	 = RGB(0xFF, 0xC0, 0xCB);
const COLORREF COXColor::m_Pink1	 = RGB(0xFF, 0xB5, 0xC5);
const COLORREF COXColor::m_Pink2	 = RGB(0xEE, 0xA9, 0xB8);
const COLORREF COXColor::m_Pink3	 = RGB(0xCD, 0x91, 0x9E);
const COLORREF COXColor::m_Pink4	 = RGB(0x8B, 0x63, 0x6C);
const COLORREF COXColor::m_Plum	 = RGB(0xDD, 0xA0, 0xDD);
const COLORREF COXColor::m_Plum1	 = RGB(0xFF, 0xBB, 0xFF);
const COLORREF COXColor::m_Plum2	 = RGB(0xEE, 0xAE, 0xEE);
const COLORREF COXColor::m_Plum3	 = RGB(0xCD, 0x96, 0xCD);
const COLORREF COXColor::m_Plum4	 = RGB(0x8B, 0x66, 0x8B);
const COLORREF COXColor::m_PowderBlue	 = RGB(0xB0, 0xE0, 0xE6);
const COLORREF COXColor::m_Purple	 = RGB(0xA0, 0x20, 0xF0);
const COLORREF COXColor::m_Purple1	 = RGB(0x9B, 0x30, 0xFF);
const COLORREF COXColor::m_Purple2	 = RGB(0x91, 0x2C, 0xEE);
const COLORREF COXColor::m_Purple3	 = RGB(0x7D, 0x26, 0xCD);
const COLORREF COXColor::m_Purple4	 = RGB(0x55, 0x1A, 0x8B);
const COLORREF COXColor::m_Red	 = RGB(0xFF, 0x00, 0x00);
const COLORREF COXColor::m_Red1	 = RGB(0xFF, 0x00, 0x00);
const COLORREF COXColor::m_Red2	 = RGB(0xEE, 0x00, 0x00);
const COLORREF COXColor::m_Red3	 = RGB(0xCD, 0x00, 0x00);
const COLORREF COXColor::m_Red4	 = RGB(0x8B, 0x00, 0x00);
const COLORREF COXColor::m_RosyBrown	 = RGB(0xBC, 0x8F, 0x8F);
const COLORREF COXColor::m_RosyBrown1	 = RGB(0xFF, 0xC1, 0xC1);
const COLORREF COXColor::m_RosyBrown2	 = RGB(0xEE, 0xB4, 0xB4);
const COLORREF COXColor::m_RosyBrown3	 = RGB(0xCD, 0x9B, 0x9B);
const COLORREF COXColor::m_RosyBrown4	 = RGB(0x8B, 0x69, 0x69);
const COLORREF COXColor::m_RoyalBlue	 = RGB(0x41, 0x69, 0xE1);
const COLORREF COXColor::m_RoyalBlue1	 = RGB(0x48, 0x76, 0xFF);
const COLORREF COXColor::m_RoyalBlue2	 = RGB(0x43, 0x6E, 0xEE);
const COLORREF COXColor::m_RoyalBlue3	 = RGB(0x3A, 0x5F, 0xCD);
const COLORREF COXColor::m_RoyalBlue4	 = RGB(0x27, 0x40, 0x8B);
const COLORREF COXColor::m_SaddleBrown	 = RGB(0x8B, 0x45, 0x13);
const COLORREF COXColor::m_Salmon	 = RGB(0xC6, 0x71, 0x71);
const COLORREF COXColor::m_Salmon1	 = RGB(0xFF, 0x8C, 0x69);
const COLORREF COXColor::m_Salmon2	 = RGB(0xEE, 0x82, 0x62);
const COLORREF COXColor::m_Salmon3	 = RGB(0xCD, 0x70, 0x54);
const COLORREF COXColor::m_Salmon4	 = RGB(0x8B, 0x4C, 0x39);
const COLORREF COXColor::m_SandyBrown	 = RGB(0xF4, 0xA4, 0x60);
const COLORREF COXColor::m_SeaGreen	 = RGB(0x2E, 0x8B, 0x57);
const COLORREF COXColor::m_SeaGreen1	 = RGB(0x54, 0xFF, 0x9F);
const COLORREF COXColor::m_SeaGreen2	 = RGB(0x4E, 0xEE, 0x94);
const COLORREF COXColor::m_SeaGreen3	 = RGB(0x43, 0xCD, 0x80);
const COLORREF COXColor::m_SeaGreen4	 = RGB(0x2E, 0x8B, 0x57);
const COLORREF COXColor::m_Seashell	 = RGB(0xFF, 0xF5, 0xEE);
const COLORREF COXColor::m_Seashell1	 = RGB(0xFF, 0xF5, 0xEE);
const COLORREF COXColor::m_Seashell2	 = RGB(0xEE, 0xE5, 0xDE);
const COLORREF COXColor::m_Seashell3	 = RGB(0xCD, 0xC5, 0xBF);
const COLORREF COXColor::m_Seashell4	 = RGB(0x8B, 0x86, 0x82);
const COLORREF COXColor::m_Sienna	 = RGB(0xA0, 0x52, 0x2D);
const COLORREF COXColor::m_Sienna1	 = RGB(0xFF, 0x82, 0x47);
const COLORREF COXColor::m_Sienna2	 = RGB(0xEE, 0x79, 0x42);
const COLORREF COXColor::m_Sienna3	 = RGB(0xCD, 0x68, 0x39);
const COLORREF COXColor::m_Sienna4	 = RGB(0x8B, 0x47, 0x26);
const COLORREF COXColor::m_SkyBlue	 = RGB(0x87, 0xCE, 0xEB);
const COLORREF COXColor::m_SkyBlue1	 = RGB(0x87, 0xCE, 0xFF);
const COLORREF COXColor::m_SkyBlue2	 = RGB(0x7E, 0xC0, 0xEE);
const COLORREF COXColor::m_SkyBlue3	 = RGB(0x6C, 0xA6, 0xCD);
const COLORREF COXColor::m_SkyBlue4	 = RGB(0x4A, 0x70, 0x8B);
const COLORREF COXColor::m_SlateBlue	 = RGB(0x6A, 0x5A, 0xCD);
const COLORREF COXColor::m_SlateBlue1	 = RGB(0x83, 0x6F, 0xFF);
const COLORREF COXColor::m_SlateBlue2	 = RGB(0x7A, 0x67, 0xEE);
const COLORREF COXColor::m_SlateBlue3	 = RGB(0x69, 0x59, 0xCD);
const COLORREF COXColor::m_SlateBlue4	 = RGB(0x47, 0x3C, 0x8B);
const COLORREF COXColor::m_SlateGray	 = RGB(0x70, 0x80, 0x90);
const COLORREF COXColor::m_SlateGray1	 = RGB(0xC6, 0xE2, 0xFF);
const COLORREF COXColor::m_SlateGray2	 = RGB(0xB9, 0xD3, 0xEE);
const COLORREF COXColor::m_SlateGray3	 = RGB(0x9F, 0xB6, 0xCD);
const COLORREF COXColor::m_SlateGray4	 = RGB(0x6C, 0x7B, 0x8B);
const COLORREF COXColor::m_Snow	 = RGB(0xFF, 0xFA, 0xFA);
const COLORREF COXColor::m_Snow1	 = RGB(0xFF, 0xFA, 0xFA);
const COLORREF COXColor::m_Snow2	 = RGB(0xEE, 0xE9, 0xE9);
const COLORREF COXColor::m_Snow3	 = RGB(0xCD, 0xC9, 0xC9);
const COLORREF COXColor::m_Snow4	 = RGB(0x8B, 0x89, 0x89);
const COLORREF COXColor::m_SpringGreen	 = RGB(0x00, 0xFF, 0x7F);
const COLORREF COXColor::m_SpringGreen1	 = RGB(0x00, 0xFF, 0x7F);
const COLORREF COXColor::m_SpringGreen2	 = RGB(0x00, 0xEE, 0x76);
const COLORREF COXColor::m_SpringGreen3	 = RGB(0x00, 0xCD, 0x66);
const COLORREF COXColor::m_SpringGreen4	 = RGB(0x00, 0x8B, 0x45);
const COLORREF COXColor::m_SteelBlue	 = RGB(0x46, 0x82, 0xB4);
const COLORREF COXColor::m_SteelBlue1	 = RGB(0x63, 0xB8, 0xFF);
const COLORREF COXColor::m_SteelBlue2	 = RGB(0x5C, 0xAC, 0xEE);
const COLORREF COXColor::m_SteelBlue3	 = RGB(0x4F, 0x94, 0xCD);
const COLORREF COXColor::m_SteelBlue4	 = RGB(0x36, 0x64, 0x8B);
const COLORREF COXColor::m_Tan	 = RGB(0xD2, 0xB4, 0x8C);
const COLORREF COXColor::m_Tan1	 = RGB(0xFF, 0xA5, 0x4F);
const COLORREF COXColor::m_Tan2	 = RGB(0xEE, 0x9A, 0x49);
const COLORREF COXColor::m_Tan3	 = RGB(0xCD, 0x85, 0x3F);
const COLORREF COXColor::m_Tan4	 = RGB(0x8B, 0x5A, 0x2B);
const COLORREF COXColor::m_Teal	 = RGB(0x38, 0x8E, 0x8E);
const COLORREF COXColor::m_Thistle	 = RGB(0xD8, 0xBF, 0xD8);
const COLORREF COXColor::m_Thistle1	 = RGB(0xFF, 0xE1, 0xFF);
const COLORREF COXColor::m_Thistle2	 = RGB(0xEE, 0xD2, 0xEE);
const COLORREF COXColor::m_Thistle3	 = RGB(0xCD, 0xB5, 0xCD);
const COLORREF COXColor::m_Thistle4	 = RGB(0x8B, 0x7B, 0x8B);
const COLORREF COXColor::m_Tomato	 = RGB(0xFF, 0x63, 0x47);
const COLORREF COXColor::m_Tomato1	 = RGB(0xFF, 0x63, 0x47);
const COLORREF COXColor::m_Tomato2	 = RGB(0xEE, 0x5C, 0x42);
const COLORREF COXColor::m_Tomato3	 = RGB(0xCD, 0x4F, 0x39);
const COLORREF COXColor::m_Tomato4	 = RGB(0x8B, 0x36, 0x26);
const COLORREF COXColor::m_Turquoise	 = RGB(0x40, 0xE0, 0xD0);
const COLORREF COXColor::m_Turquoise1	 = RGB(0x00, 0xF5, 0xFF);
const COLORREF COXColor::m_Turquoise2	 = RGB(0x00, 0xE5, 0xEE);
const COLORREF COXColor::m_Turquoise3	 = RGB(0x00, 0xC5, 0xCD);
const COLORREF COXColor::m_Turquoise4	 = RGB(0x00, 0x86, 0x8B);
const COLORREF COXColor::m_VeryDarkGray	 = RGB(0x28, 0x28, 0x28);
const COLORREF COXColor::m_VeryLightGray	 = RGB(0xD6, 0xD6, 0xD6);
const COLORREF COXColor::m_Violet	 = RGB(0xEE, 0x82, 0xEE);
const COLORREF COXColor::m_VioletRed	 = RGB(0xD0, 0x20, 0x90);
const COLORREF COXColor::m_VioletRed1	 = RGB(0xFF, 0x3E, 0x96);
const COLORREF COXColor::m_VioletRed2	 = RGB(0xEE, 0x3A, 0x8C);
const COLORREF COXColor::m_VioletRed3	 = RGB(0xCD, 0x32, 0x78);
const COLORREF COXColor::m_VioletRed4	 = RGB(0x8B, 0x22, 0x52);
const COLORREF COXColor::m_Wheat	 = RGB(0xF5, 0xDE, 0xB3);
const COLORREF COXColor::m_Wheat1	 = RGB(0xFF, 0xE7, 0xBA);
const COLORREF COXColor::m_Wheat2	 = RGB(0xEE, 0xD8, 0xAE);
const COLORREF COXColor::m_Wheat3	 = RGB(0xCD, 0xBA, 0x96);
const COLORREF COXColor::m_Wheat4	 = RGB(0x8B, 0x7E, 0x66);
const COLORREF COXColor::m_White	 = RGB(0xFF, 0xFF, 0xFF);
const COLORREF COXColor::m_WhiteSmoke	 = RGB(0xF5, 0xF5, 0xF5);
const COLORREF COXColor::m_Yellow	 = RGB(0xFF, 0xFF, 0x00);
const COLORREF COXColor::m_Yellow1	 = RGB(0xFF, 0xFF, 0x00);
const COLORREF COXColor::m_Yellow2	 = RGB(0xEE, 0xEE, 0x00);
const COLORREF COXColor::m_Yellow3	 = RGB(0xCD, 0xCD, 0x00);
const COLORREF COXColor::m_Yellow4	 = RGB(0x8B, 0x8B, 0x00);
const COLORREF COXColor::m_YellowGreen	 = RGB(0x9A, 0xCD, 0x32);

#ifndef OX_COLORS_NO_NAMES 

const TCHAR szAliceBlue[] = _T("AliceBlue");
const TCHAR szAntiqueWhite[] = _T("AntiqueWhite");
const TCHAR szAntiqueWhite1[] = _T("AntiqueWhite1");
const TCHAR szAntiqueWhite2[] = _T("AntiqueWhite2");
const TCHAR szAntiqueWhite3[] = _T("AntiqueWhite3");
const TCHAR szAntiqueWhite4[] = _T("AntiqueWhite4");
const TCHAR szAquamarine[] = _T("Aquamarine");
const TCHAR szAquamarine1[] = _T("Aquamarine1");
const TCHAR szAquamarine2[] = _T("Aquamarine2");
const TCHAR szAquamarine3[] = _T("Aquamarine3");
const TCHAR szAquamarine4[] = _T("Aquamarine4");
const TCHAR szAzure[] = _T("Azure");
const TCHAR szAzure1[] = _T("Azure1");
const TCHAR szAzure2[] = _T("Azure2");
const TCHAR szAzure3[] = _T("Azure3");
const TCHAR szAzure4[] = _T("Azure4");
const TCHAR szBeet[] = _T("Beet");
const TCHAR szBeige[] = _T("Beige");
const TCHAR szBisque[] = _T("Bisque");
const TCHAR szBisque1[] = _T("Bisque1");
const TCHAR szBisque2[] = _T("Bisque2");
const TCHAR szBisque3[] = _T("Bisque3");
const TCHAR szBisque4[] = _T("Bisque4");
const TCHAR szBlack[] = _T("Black");
const TCHAR szBlanchedAlmond[] = _T("BlanchedAlmond");
const TCHAR szBlue[] = _T("Blue");
const TCHAR szBlue1[] = _T("Blue1");
const TCHAR szBlue2[] = _T("Blue2");
const TCHAR szBlue3[] = _T("Blue3");
const TCHAR szBlue4[] = _T("Blue4");
const TCHAR szBlueViolet[] = _T("BlueViolet");
const TCHAR szBrightGray[] = _T("BrightGray");
const TCHAR szBrown[] = _T("Brown");
const TCHAR szBrown1[] = _T("Brown1");
const TCHAR szBrown2[] = _T("Brown2");
const TCHAR szBrown3[] = _T("Brown3");
const TCHAR szBrown4[] = _T("Brown4");
const TCHAR szBurlywood[] = _T("Burlywood");
const TCHAR szBurlywood1[] = _T("Burlywood1");
const TCHAR szBurlywood2[] = _T("Burlywood2");
const TCHAR szBurlywood3[] = _T("Burlywood3");
const TCHAR szBurlywood4[] = _T("Burlywood4");
const TCHAR szCadetBlue[] = _T("CadetBlue");
const TCHAR szCadetBlue1[] = _T("CadetBlue1");
const TCHAR szCadetBlue2[] = _T("CadetBlue2");
const TCHAR szCadetBlue3[] = _T("CadetBlue3");
const TCHAR szCadetBlue4[] = _T("CadetBlue4");
const TCHAR szChartreuse[] = _T("Chartreuse");
const TCHAR szChartreuse1[] = _T("Chartreuse1");
const TCHAR szChartreuse2[] = _T("Chartreuse2");
const TCHAR szChartreuse3[] = _T("Chartreuse3");
const TCHAR szChartreuse4[] = _T("Chartreuse4");
const TCHAR szChocolate[] = _T("Chocolate");
const TCHAR szChocolate1[] = _T("Chocolate1");
const TCHAR szChocolate2[] = _T("Chocolate2");
const TCHAR szChocolate3[] = _T("Chocolate3");
const TCHAR szChocolate4[] = _T("Chocolate4");
const TCHAR szCoral[] = _T("Coral");
const TCHAR szCoral1[] = _T("Coral1");
const TCHAR szCoral2[] = _T("Coral2");
const TCHAR szCoral3[] = _T("Coral3");
const TCHAR szCoral4[] = _T("Coral4");
const TCHAR szCornflowerBlue[] = _T("CornflowerBlue");
const TCHAR szCornsilk[] = _T("Cornsilk");
const TCHAR szCornsilk1[] = _T("Cornsilk1");
const TCHAR szCornsilk2[] = _T("Cornsilk2");
const TCHAR szCornsilk3[] = _T("Cornsilk3");
const TCHAR szCornsilk4[] = _T("Cornsilk4");
const TCHAR szCrimson[] = _T("Crimson");
const TCHAR szCyan[] = _T("Cyan");
const TCHAR szCyan1[] = _T("Cyan1");
const TCHAR szCyan2[] = _T("Cyan2");
const TCHAR szCyan3[] = _T("Cyan3");
const TCHAR szCyan4[] = _T("Cyan4");
const TCHAR szDarkBlue[] = _T("DarkBlue");
const TCHAR szDarkCyan[] = _T("DarkCyan");
const TCHAR szDarkGoldenrod[] = _T("DarkGoldenrod");
const TCHAR szDarkGoldenrod1[] = _T("DarkGoldenrod1");
const TCHAR szDarkGoldenrod2[] = _T("DarkGoldenrod2");
const TCHAR szDarkGoldenrod3[] = _T("DarkGoldenrod3");
const TCHAR szDarkGoldenrod4[] = _T("DarkGoldenrod4");
const TCHAR szDarkGray[] = _T("DarkGray");
const TCHAR szDarkGreen[] = _T("DarkGreen");
const TCHAR szDarkKhaki[] = _T("DarkKhaki");
const TCHAR szDarkMagenta[] = _T("DarkMagenta");
const TCHAR szDarkOliveGreen[] = _T("DarkOliveGreen");
const TCHAR szDarkOliveGreen1[] = _T("DarkOliveGreen1");
const TCHAR szDarkOliveGreen2[] = _T("DarkOliveGreen2");
const TCHAR szDarkOliveGreen3[] = _T("DarkOliveGreen3");
const TCHAR szDarkOliveGreen4[] = _T("DarkOliveGreen4");
const TCHAR szDarkOrange[] = _T("DarkOrange");
const TCHAR szDarkOrange1[] = _T("DarkOrange1");
const TCHAR szDarkOrange2[] = _T("DarkOrange2");
const TCHAR szDarkOrange3[] = _T("DarkOrange3");
const TCHAR szDarkOrange4[] = _T("DarkOrange4");
const TCHAR szDarkOrchid[] = _T("DarkOrchid");
const TCHAR szDarkOrchid1[] = _T("DarkOrchid1");
const TCHAR szDarkOrchid2[] = _T("DarkOrchid2");
const TCHAR szDarkOrchid3[] = _T("DarkOrchid3");
const TCHAR szDarkOrchid4[] = _T("DarkOrchid4");
const TCHAR szDarkRed[] = _T("DarkRed");
const TCHAR szDarkSalmon[] = _T("DarkSalmon");
const TCHAR szDarkSeaGreen[] = _T("DarkSeaGreen");
const TCHAR szDarkSeaGreen1[] = _T("DarkSeaGreen1");
const TCHAR szDarkSeaGreen2[] = _T("DarkSeaGreen2");
const TCHAR szDarkSeaGreen3[] = _T("DarkSeaGreen3");
const TCHAR szDarkSeaGreen4[] = _T("DarkSeaGreen4");
const TCHAR szDarkSlateBlue[] = _T("DarkSlateBlue");
const TCHAR szDarkSlateGray[] = _T("DarkSlateGray");
const TCHAR szDarkSlateGray1[] = _T("DarkSlateGray1");
const TCHAR szDarkSlateGray2[] = _T("DarkSlateGray2");
const TCHAR szDarkSlateGray3[] = _T("DarkSlateGray3");
const TCHAR szDarkSlateGray4[] = _T("DarkSlateGray4");
const TCHAR szDarkTurquoise[] = _T("DarkTurquoise");
const TCHAR szDarkViolet[] = _T("DarkViolet");
const TCHAR szDeepPink[] = _T("DeepPink");
const TCHAR szDeepPink1[] = _T("DeepPink1");
const TCHAR szDeepPink2[] = _T("DeepPink2");
const TCHAR szDeepPink3[] = _T("DeepPink3");
const TCHAR szDeepPink4[] = _T("DeepPink4");
const TCHAR szDeepSkyBlue[] = _T("DeepSkyBlue");
const TCHAR szDeepSkyBlue1[] = _T("DeepSkyBlue1");
const TCHAR szDeepSkyBlue2[] = _T("DeepSkyBlue2");
const TCHAR szDeepSkyBlue3[] = _T("DeepSkyBlue3");
const TCHAR szDeepSkyBlue4[] = _T("DeepSkyBlue4");
const TCHAR szDimGray[] = _T("DimGray");
const TCHAR szDodgerBlue[] = _T("DodgerBlue");
const TCHAR szDodgerBlue1[] = _T("DodgerBlue1");
const TCHAR szDodgerBlue2[] = _T("DodgerBlue2");
const TCHAR szDodgerBlue3[] = _T("DodgerBlue3");
const TCHAR szDodgerBlue4[] = _T("DodgerBlue4");
const TCHAR szFirebrick[] = _T("Firebrick");
const TCHAR szFirebrick1[] = _T("Firebrick1");
const TCHAR szFirebrick2[] = _T("Firebrick2");
const TCHAR szFirebrick3[] = _T("Firebrick3");
const TCHAR szFirebrick4[] = _T("Firebrick4");
const TCHAR szFloralWhite[] = _T("FloralWhite");
const TCHAR szForestGreen[] = _T("ForestGreen");
const TCHAR szGainsboro[] = _T("Gainsboro");
const TCHAR szGhostWhite[] = _T("GhostWhite");
const TCHAR szGold[] = _T("Gold");
const TCHAR szGold1[] = _T("Gold1");
const TCHAR szGold2[] = _T("Gold2");
const TCHAR szGold3[] = _T("Gold3");
const TCHAR szGold4[] = _T("Gold4");
const TCHAR szGoldenrod[] = _T("Goldenrod");
const TCHAR szGoldenrod1[] = _T("Goldenrod1");
const TCHAR szGoldenrod2[] = _T("Goldenrod2");
const TCHAR szGoldenrod3[] = _T("Goldenrod3");
const TCHAR szGoldenrod4[] = _T("Goldenrod4");
const TCHAR szGray[] = _T("Gray");
const TCHAR szGray0[] = _T("Gray0");
const TCHAR szGray2[] = _T("Gray2");
const TCHAR szGray3[] = _T("Gray3");
const TCHAR szGray4[] = _T("Gray4");
const TCHAR szGray5[] = _T("Gray5");
const TCHAR szGray6[] = _T("Gray6");
const TCHAR szGray7[] = _T("Gray7");
const TCHAR szGray8[] = _T("Gray8");
const TCHAR szGray9[] = _T("Gray9");
const TCHAR szGray1[] = _T("Gray1");
const TCHAR szGray10[] = _T("Gray10");
const TCHAR szGray11[] = _T("Gray11");
const TCHAR szGray12[] = _T("Gray12");
const TCHAR szGray13[] = _T("Gray13");
const TCHAR szGray14[] = _T("Gray14");
const TCHAR szGray15[] = _T("Gray15");
const TCHAR szGray16[] = _T("Gray16");
const TCHAR szGray17[] = _T("Gray17");
const TCHAR szGray18[] = _T("Gray18");
const TCHAR szGray19[] = _T("Gray19");
const TCHAR szGray20[] = _T("Gray20");
const TCHAR szGray21[] = _T("Gray21");
const TCHAR szGray22[] = _T("Gray22");
const TCHAR szGray23[] = _T("Gray23");
const TCHAR szGray24[] = _T("Gray24");
const TCHAR szGray25[] = _T("Gray25");
const TCHAR szGray26[] = _T("Gray26");
const TCHAR szGray27[] = _T("Gray27");
const TCHAR szGray28[] = _T("Gray28");
const TCHAR szGray29[] = _T("Gray29");
const TCHAR szGray30[] = _T("Gray30");
const TCHAR szGray31[] = _T("Gray31");
const TCHAR szGray32[] = _T("Gray32");
const TCHAR szGray33[] = _T("Gray33");
const TCHAR szGray34[] = _T("Gray34");
const TCHAR szGray35[] = _T("Gray35");
const TCHAR szGray36[] = _T("Gray36");
const TCHAR szGray37[] = _T("Gray37");
const TCHAR szGray38[] = _T("Gray38");
const TCHAR szGray39[] = _T("Gray39");
const TCHAR szGray40[] = _T("Gray40");
const TCHAR szGray41[] = _T("Gray41");
const TCHAR szGray42[] = _T("Gray42");
const TCHAR szGray43[] = _T("Gray43");
const TCHAR szGray44[] = _T("Gray44");
const TCHAR szGray45[] = _T("Gray45");
const TCHAR szGray46[] = _T("Gray46");
const TCHAR szGray47[] = _T("Gray47");
const TCHAR szGray48[] = _T("Gray48");
const TCHAR szGray49[] = _T("Gray49");
const TCHAR szGray50[] = _T("Gray50");
const TCHAR szGray51[] = _T("Gray51");
const TCHAR szGray52[] = _T("Gray52");
const TCHAR szGray53[] = _T("Gray53");
const TCHAR szGray54[] = _T("Gray54");
const TCHAR szGray55[] = _T("Gray55");
const TCHAR szGray56[] = _T("Gray56");
const TCHAR szGray57[] = _T("Gray57");
const TCHAR szGray58[] = _T("Gray58");
const TCHAR szGray59[] = _T("Gray59");
const TCHAR szGray60[] = _T("Gray60");
const TCHAR szGray61[] = _T("Gray61");
const TCHAR szGray62[] = _T("Gray62");
const TCHAR szGray63[] = _T("Gray63");
const TCHAR szGray64[] = _T("Gray64");
const TCHAR szGray65[] = _T("Gray65");
const TCHAR szGray66[] = _T("Gray66");
const TCHAR szGray67[] = _T("Gray67");
const TCHAR szGray68[] = _T("Gray68");
const TCHAR szGray69[] = _T("Gray69");
const TCHAR szGray70[] = _T("Gray70");
const TCHAR szGray71[] = _T("Gray71");
const TCHAR szGray72[] = _T("Gray72");
const TCHAR szGray73[] = _T("Gray73");
const TCHAR szGray74[] = _T("Gray74");
const TCHAR szGray75[] = _T("Gray75");
const TCHAR szGray76[] = _T("Gray76");
const TCHAR szGray77[] = _T("Gray77");
const TCHAR szGray78[] = _T("Gray78");
const TCHAR szGray79[] = _T("Gray79");
const TCHAR szGray80[] = _T("Gray80");
const TCHAR szGray81[] = _T("Gray81");
const TCHAR szGray82[] = _T("Gray82");
const TCHAR szGray83[] = _T("Gray83");
const TCHAR szGray84[] = _T("Gray84");
const TCHAR szGray85[] = _T("Gray85");
const TCHAR szGray86[] = _T("Gray86");
const TCHAR szGray87[] = _T("Gray87");
const TCHAR szGray88[] = _T("Gray88");
const TCHAR szGray89[] = _T("Gray89");
const TCHAR szGray90[] = _T("Gray90");
const TCHAR szGray91[] = _T("Gray91");
const TCHAR szGray92[] = _T("Gray92");
const TCHAR szGray93[] = _T("Gray93");
const TCHAR szGray94[] = _T("Gray94");
const TCHAR szGray95[] = _T("Gray95");
const TCHAR szGray96[] = _T("Gray96");
const TCHAR szGray97[] = _T("Gray97");
const TCHAR szGray98[] = _T("Gray98");
const TCHAR szGray99[] = _T("Gray99");
const TCHAR szGray100[] = _T("Gray100");
const TCHAR szGreen[] = _T("Green");
const TCHAR szGreen1[] = _T("Green1");
const TCHAR szGreen2[] = _T("Green2");
const TCHAR szGreen3[] = _T("Green3");
const TCHAR szGreen4[] = _T("Green4");
const TCHAR szGreenYellow[] = _T("GreenYellow");
const TCHAR szHoneydew[] = _T("Honeydew");
const TCHAR szHoneydew1[] = _T("Honeydew1");
const TCHAR szHoneydew2[] = _T("Honeydew2");
const TCHAR szHoneydew3[] = _T("Honeydew3");
const TCHAR szHoneydew4[] = _T("Honeydew4");
const TCHAR szHotPink[] = _T("HotPink");
const TCHAR szHotPink1[] = _T("HotPink1");
const TCHAR szHotPink2[] = _T("HotPink2");
const TCHAR szHotPink3[] = _T("HotPink3");
const TCHAR szHotPink4[] = _T("HotPink4");
const TCHAR szIndianRed[] = _T("IndianRed");
const TCHAR szIndianRed1[] = _T("IndianRed1");
const TCHAR szIndianRed2[] = _T("IndianRed2");
const TCHAR szIndianRed3[] = _T("IndianRed3");
const TCHAR szIndianRed4[] = _T("IndianRed4");
const TCHAR szIndigo[] = _T("Indigo");
const TCHAR szIndigo2[] = _T("Indigo2");
const TCHAR szIvory[] = _T("Ivory");
const TCHAR szIvory1[] = _T("Ivory1");
const TCHAR szIvory2[] = _T("Ivory2");
const TCHAR szIvory3[] = _T("Ivory3");
const TCHAR szIvory4[] = _T("Ivory4");
const TCHAR szKhaki[] = _T("Khaki");
const TCHAR szKhaki1[] = _T("Khaki1");
const TCHAR szKhaki2[] = _T("Khaki2");
const TCHAR szKhaki3[] = _T("Khaki3");
const TCHAR szKhaki4[] = _T("Khaki4");
const TCHAR szLavender[] = _T("Lavender");
const TCHAR szLavenderBlush[] = _T("LavenderBlush");
const TCHAR szLavenderBlush1[] = _T("LavenderBlush1");
const TCHAR szLavenderBlush2[] = _T("LavenderBlush2");
const TCHAR szLavenderBlush3[] = _T("LavenderBlush3");
const TCHAR szLavenderBlush4[] = _T("LavenderBlush4");
const TCHAR szLawnGreen[] = _T("LawnGreen");
const TCHAR szLemonChiffon[] = _T("LemonChiffon");
const TCHAR szLemonChiffon1[] = _T("LemonChiffon1");
const TCHAR szLemonChiffon2[] = _T("LemonChiffon2");
const TCHAR szLemonChiffon3[] = _T("LemonChiffon3");
const TCHAR szLemonChiffon4[] = _T("LemonChiffon4");
const TCHAR szLightBlue[] = _T("LightBlue");
const TCHAR szLightBlue1[] = _T("LightBlue1");
const TCHAR szLightBlue2[] = _T("LightBlue2");
const TCHAR szLightBlue3[] = _T("LightBlue3");
const TCHAR szLightBlue4[] = _T("LightBlue4");
const TCHAR szLightCoral[] = _T("LightCoral");
const TCHAR szLightCyan[] = _T("LightCyan");
const TCHAR szLightCyan1[] = _T("LightCyan1");
const TCHAR szLightCyan2[] = _T("LightCyan2");
const TCHAR szLightCyan3[] = _T("LightCyan3");
const TCHAR szLightCyan4[] = _T("LightCyan4");
const TCHAR szLightGoldenrod[] = _T("LightGoldenrod");
const TCHAR szLightGoldenrod1[] = _T("LightGoldenrod1");
const TCHAR szLightGoldenrod2[] = _T("LightGoldenrod2");
const TCHAR szLightGoldenrod3[] = _T("LightGoldenrod3");
const TCHAR szLightGoldenrod4[] = _T("LightGoldenrod4");
const TCHAR szLightGoldenrodYellow[] = _T("LightGoldenrodYellow");
const TCHAR szLightGray[] = _T("LightGray");
const TCHAR szLightGreen[] = _T("LightGreen");
const TCHAR szLightPink[] = _T("LightPink");
const TCHAR szLightPink1[] = _T("LightPink1");
const TCHAR szLightPink2[] = _T("LightPink2");
const TCHAR szLightPink3[] = _T("LightPink3");
const TCHAR szLightPink4[] = _T("LightPink4");
const TCHAR szLightSalmon[] = _T("LightSalmon");
const TCHAR szLightSalmon1[] = _T("LightSalmon1");
const TCHAR szLightSalmon2[] = _T("LightSalmon2");
const TCHAR szLightSalmon3[] = _T("LightSalmon3");
const TCHAR szLightSalmon4[] = _T("LightSalmon4");
const TCHAR szLightSeaGreen[] = _T("LightSeaGreen");
const TCHAR szLightSkyBlue[] = _T("LightSkyBlue");
const TCHAR szLightSkyBlue1[] = _T("LightSkyBlue1");
const TCHAR szLightSkyBlue2[] = _T("LightSkyBlue2");
const TCHAR szLightSkyBlue3[] = _T("LightSkyBlue3");
const TCHAR szLightSkyBlue4[] = _T("LightSkyBlue4");
const TCHAR szLightSlateBlue[] = _T("LightSlateBlue");
const TCHAR szLightSlateGray[] = _T("LightSlateGray");
const TCHAR szLightSteelBlue[] = _T("LightSteelBlue");
const TCHAR szLightSteelBlue1[] = _T("LightSteelBlue1");
const TCHAR szLightSteelBlue2[] = _T("LightSteelBlue2");
const TCHAR szLightSteelBlue3[] = _T("LightSteelBlue3");
const TCHAR szLightSteelBlue4[] = _T("LightSteelBlue4");
const TCHAR szLightYellow[] = _T("LightYellow");
const TCHAR szLightYellow1[] = _T("LightYellow1");
const TCHAR szLightYellow2[] = _T("LightYellow2");
const TCHAR szLightYellow3[] = _T("LightYellow3");
const TCHAR szLightYellow4[] = _T("LightYellow4");
const TCHAR szLimeGreen[] = _T("LimeGreen");
const TCHAR szLinen[] = _T("Linen");
const TCHAR szMagenta[] = _T("Magenta");
const TCHAR szMagenta1[] = _T("Magenta1");
const TCHAR szMagenta2[] = _T("Magenta2");
const TCHAR szMagenta3[] = _T("Magenta3");
const TCHAR szMagenta4[] = _T("Magenta4");
const TCHAR szMaroon[] = _T("Maroon");
const TCHAR szMaroon1[] = _T("Maroon1");
const TCHAR szMaroon2[] = _T("Maroon2");
const TCHAR szMaroon3[] = _T("Maroon3");
const TCHAR szMaroon4[] = _T("Maroon4");
const TCHAR szMediumAquamarine[] = _T("MediumAquamarine");
const TCHAR szMediumBlue[] = _T("MediumBlue");
const TCHAR szMediumGray[] = _T("MediumGray");
const TCHAR szMediumOrchid[] = _T("MediumOrchid");
const TCHAR szMediumOrchid1[] = _T("MediumOrchid1");
const TCHAR szMediumOrchid2[] = _T("MediumOrchid2");
const TCHAR szMediumOrchid3[] = _T("MediumOrchid3");
const TCHAR szMediumOrchid4[] = _T("MediumOrchid4");
const TCHAR szMediumPurple[] = _T("MediumPurple");
const TCHAR szMediumPurple1[] = _T("MediumPurple1");
const TCHAR szMediumPurple2[] = _T("MediumPurple2");
const TCHAR szMediumPurple3[] = _T("MediumPurple3");
const TCHAR szMediumPurple4[] = _T("MediumPurple4");
const TCHAR szMediumSeaGreen[] = _T("MediumSeaGreen");
const TCHAR szMediumSlateBlue[] = _T("MediumSlateBlue");
const TCHAR szMediumSpringGreen[] = _T("MediumSpringGreen");
const TCHAR szMediumTurquoise[] = _T("MediumTurquoise");
const TCHAR szMediumVioletRed[] = _T("MediumVioletRed");
const TCHAR szMidnightBlue[] = _T("MidnightBlue");
const TCHAR szMintCream[] = _T("MintCream");
const TCHAR szMistyRose[] = _T("MistyRose");
const TCHAR szMistyRose1[] = _T("MistyRose1");
const TCHAR szMistyRose2[] = _T("MistyRose2");
const TCHAR szMistyRose3[] = _T("MistyRose3");
const TCHAR szMistyRose4[] = _T("MistyRose4");
const TCHAR szMoccasin[] = _T("Moccasin");
const TCHAR szNavajoWhite[] = _T("NavajoWhite");
const TCHAR szNavajoWhite1[] = _T("NavajoWhite1");
const TCHAR szNavajoWhite2[] = _T("NavajoWhite2");
const TCHAR szNavajoWhite3[] = _T("NavajoWhite3");
const TCHAR szNavajoWhite4[] = _T("NavajoWhite4");
const TCHAR szNavy[] = _T("Navy");
const TCHAR szNavyBlue[] = _T("NavyBlue");
const TCHAR szOldLace[] = _T("OldLace");
const TCHAR szOliveDrab[] = _T("OliveDrab");
const TCHAR szOliveDrab1[] = _T("OliveDrab1");
const TCHAR szOliveDrab2[] = _T("OliveDrab2");
const TCHAR szOliveDrab3[] = _T("OliveDrab3");
const TCHAR szOliveDrab4[] = _T("OliveDrab4");
const TCHAR szOrange[] = _T("Orange");
const TCHAR szOrange1[] = _T("Orange1");
const TCHAR szOrange2[] = _T("Orange2");
const TCHAR szOrange3[] = _T("Orange3");
const TCHAR szOrange4[] = _T("Orange4");
const TCHAR szOrangeRed[] = _T("OrangeRed");
const TCHAR szOrangeRed1[] = _T("OrangeRed1");
const TCHAR szOrangeRed2[] = _T("OrangeRed2");
const TCHAR szOrangeRed3[] = _T("OrangeRed3");
const TCHAR szOrangeRed4[] = _T("OrangeRed4");
const TCHAR szOrchid[] = _T("Orchid");
const TCHAR szOrchid1[] = _T("Orchid1");
const TCHAR szOrchid2[] = _T("Orchid2");
const TCHAR szOrchid3[] = _T("Orchid3");
const TCHAR szOrchid4[] = _T("Orchid4");
const TCHAR szPaleGoldenrod[] = _T("PaleGoldenrod");
const TCHAR szPaleGreen[] = _T("PaleGreen");
const TCHAR szPaleGreen1[] = _T("PaleGreen1");
const TCHAR szPaleGreen2[] = _T("PaleGreen2");
const TCHAR szPaleGreen3[] = _T("PaleGreen3");
const TCHAR szPaleGreen4[] = _T("PaleGreen4");
const TCHAR szPaleTurquoise[] = _T("PaleTurquoise");
const TCHAR szPaleTurquoise1[] = _T("PaleTurquoise1");
const TCHAR szPaleTurquoise2[] = _T("PaleTurquoise2");
const TCHAR szPaleTurquoise3[] = _T("PaleTurquoise3");
const TCHAR szPaleTurquoise4[] = _T("PaleTurquoise4");
const TCHAR szPaleVioletRed[] = _T("PaleVioletRed");
const TCHAR szPaleVioletRed1[] = _T("PaleVioletRed1");
const TCHAR szPaleVioletRed2[] = _T("PaleVioletRed2");
const TCHAR szPaleVioletRed3[] = _T("PaleVioletRed3");
const TCHAR szPaleVioletRed4[] = _T("PaleVioletRed4");
const TCHAR szPapayaWhip[] = _T("PapayaWhip");
const TCHAR szPeachPuff[] = _T("PeachPuff");
const TCHAR szPeachPuff1[] = _T("PeachPuff1");
const TCHAR szPeachPuff2[] = _T("PeachPuff2");
const TCHAR szPeachPuff3[] = _T("PeachPuff3");
const TCHAR szPeachPuff4[] = _T("PeachPuff4");
const TCHAR szPeru[] = _T("Peru");
const TCHAR szPink[] = _T("Pink");
const TCHAR szPink1[] = _T("Pink1");
const TCHAR szPink2[] = _T("Pink2");
const TCHAR szPink3[] = _T("Pink3");
const TCHAR szPink4[] = _T("Pink4");
const TCHAR szPlum[] = _T("Plum");
const TCHAR szPlum1[] = _T("Plum1");
const TCHAR szPlum2[] = _T("Plum2");
const TCHAR szPlum3[] = _T("Plum3");
const TCHAR szPlum4[] = _T("Plum4");
const TCHAR szPowderBlue[] = _T("PowderBlue");
const TCHAR szPurple[] = _T("Purple");
const TCHAR szPurple1[] = _T("Purple1");
const TCHAR szPurple2[] = _T("Purple2");
const TCHAR szPurple3[] = _T("Purple3");
const TCHAR szPurple4[] = _T("Purple4");
const TCHAR szRed[] = _T("Red");
const TCHAR szRed1[] = _T("Red1");
const TCHAR szRed2[] = _T("Red2");
const TCHAR szRed3[] = _T("Red3");
const TCHAR szRed4[] = _T("Red4");
const TCHAR szRosyBrown[] = _T("RosyBrown");
const TCHAR szRosyBrown1[] = _T("RosyBrown1");
const TCHAR szRosyBrown2[] = _T("RosyBrown2");
const TCHAR szRosyBrown3[] = _T("RosyBrown3");
const TCHAR szRosyBrown4[] = _T("RosyBrown4");
const TCHAR szRoyalBlue[] = _T("RoyalBlue");
const TCHAR szRoyalBlue1[] = _T("RoyalBlue1");
const TCHAR szRoyalBlue2[] = _T("RoyalBlue2");
const TCHAR szRoyalBlue3[] = _T("RoyalBlue3");
const TCHAR szRoyalBlue4[] = _T("RoyalBlue4");
const TCHAR szSaddleBrown[] = _T("SaddleBrown");
const TCHAR szSalmon[] = _T("Salmon");
const TCHAR szSalmon1[] = _T("Salmon1");
const TCHAR szSalmon2[] = _T("Salmon2");
const TCHAR szSalmon3[] = _T("Salmon3");
const TCHAR szSalmon4[] = _T("Salmon4");
const TCHAR szSandyBrown[] = _T("SandyBrown");
const TCHAR szSeaGreen[] = _T("SeaGreen");
const TCHAR szSeaGreen1[] = _T("SeaGreen1");
const TCHAR szSeaGreen2[] = _T("SeaGreen2");
const TCHAR szSeaGreen3[] = _T("SeaGreen3");
const TCHAR szSeaGreen4[] = _T("SeaGreen4");
const TCHAR szSeashell[] = _T("Seashell");
const TCHAR szSeashell1[] = _T("Seashell1");
const TCHAR szSeashell2[] = _T("Seashell2");
const TCHAR szSeashell3[] = _T("Seashell3");
const TCHAR szSeashell4[] = _T("Seashell4");
const TCHAR szSienna[] = _T("Sienna");
const TCHAR szSienna1[] = _T("Sienna1");
const TCHAR szSienna2[] = _T("Sienna2");
const TCHAR szSienna3[] = _T("Sienna3");
const TCHAR szSienna4[] = _T("Sienna4");
const TCHAR szSkyBlue[] = _T("SkyBlue");
const TCHAR szSkyBlue1[] = _T("SkyBlue1");
const TCHAR szSkyBlue2[] = _T("SkyBlue2");
const TCHAR szSkyBlue3[] = _T("SkyBlue3");
const TCHAR szSkyBlue4[] = _T("SkyBlue4");
const TCHAR szSlateBlue[] = _T("SlateBlue");
const TCHAR szSlateBlue1[] = _T("SlateBlue1");
const TCHAR szSlateBlue2[] = _T("SlateBlue2");
const TCHAR szSlateBlue3[] = _T("SlateBlue3");
const TCHAR szSlateBlue4[] = _T("SlateBlue4");
const TCHAR szSlateGray[] = _T("SlateGray");
const TCHAR szSlateGray1[] = _T("SlateGray1");
const TCHAR szSlateGray2[] = _T("SlateGray2");
const TCHAR szSlateGray3[] = _T("SlateGray3");
const TCHAR szSlateGray4[] = _T("SlateGray4");
const TCHAR szSnow[] = _T("Snow");
const TCHAR szSnow1[] = _T("Snow1");
const TCHAR szSnow2[] = _T("Snow2");
const TCHAR szSnow3[] = _T("Snow3");
const TCHAR szSnow4[] = _T("Snow4");
const TCHAR szSpringGreen[] = _T("SpringGreen");
const TCHAR szSpringGreen1[] = _T("SpringGreen1");
const TCHAR szSpringGreen2[] = _T("SpringGreen2");
const TCHAR szSpringGreen3[] = _T("SpringGreen3");
const TCHAR szSpringGreen4[] = _T("SpringGreen4");
const TCHAR szSteelBlue[] = _T("SteelBlue");
const TCHAR szSteelBlue1[] = _T("SteelBlue1");
const TCHAR szSteelBlue2[] = _T("SteelBlue2");
const TCHAR szSteelBlue3[] = _T("SteelBlue3");
const TCHAR szSteelBlue4[] = _T("SteelBlue4");
const TCHAR szTan[] = _T("Tan");
const TCHAR szTan1[] = _T("Tan1");
const TCHAR szTan2[] = _T("Tan2");
const TCHAR szTan3[] = _T("Tan3");
const TCHAR szTan4[] = _T("Tan4");
const TCHAR szTeal[] = _T("Teal");
const TCHAR szThistle[] = _T("Thistle");
const TCHAR szThistle1[] = _T("Thistle1");
const TCHAR szThistle2[] = _T("Thistle2");
const TCHAR szThistle3[] = _T("Thistle3");
const TCHAR szThistle4[] = _T("Thistle4");
const TCHAR szTomato[] = _T("Tomato");
const TCHAR szTomato1[] = _T("Tomato1");
const TCHAR szTomato2[] = _T("Tomato2");
const TCHAR szTomato3[] = _T("Tomato3");
const TCHAR szTomato4[] = _T("Tomato4");
const TCHAR szTurquoise[] = _T("Turquoise");
const TCHAR szTurquoise1[] = _T("Turquoise1");
const TCHAR szTurquoise2[] = _T("Turquoise2");
const TCHAR szTurquoise3[] = _T("Turquoise3");
const TCHAR szTurquoise4[] = _T("Turquoise4");
const TCHAR szVeryDarkGray[] = _T("VeryDarkGray");
const TCHAR szVeryLightGray[] = _T("VeryLightGray");
const TCHAR szViolet[] = _T("Violet");
const TCHAR szVioletRed[] = _T("VioletRed");
const TCHAR szVioletRed1[] = _T("VioletRed1");
const TCHAR szVioletRed2[] = _T("VioletRed2");
const TCHAR szVioletRed3[] = _T("VioletRed3");
const TCHAR szVioletRed4[] = _T("VioletRed4");
const TCHAR szWheat[] = _T("Wheat");
const TCHAR szWheat1[] = _T("Wheat1");
const TCHAR szWheat2[] = _T("Wheat2");
const TCHAR szWheat3[] = _T("Wheat3");
const TCHAR szWheat4[] = _T("Wheat4");
const TCHAR szWhite[] = _T("White");
const TCHAR szWhiteSmoke[] = _T("WhiteSmoke");
const TCHAR szYellow[] = _T("Yellow");
const TCHAR szYellow1[] = _T("Yellow1");
const TCHAR szYellow2[] = _T("Yellow2");
const TCHAR szYellow3[] = _T("Yellow3");
const TCHAR szYellow4[] = _T("Yellow4");
const TCHAR szYellowGreen[] = _T("YellowGreen");

COXColor::COXColorCouple COXColor::m_colors[] = 
{
	{ szAliceBlue, COXColor::m_AliceBlue },
	{ szAntiqueWhite, COXColor::m_AntiqueWhite },
	{ szAntiqueWhite1, COXColor::m_AntiqueWhite1 },
	{ szAntiqueWhite2, COXColor::m_AntiqueWhite2 },
	{ szAntiqueWhite3, COXColor::m_AntiqueWhite3 },
	{ szAntiqueWhite4, COXColor::m_AntiqueWhite4 },
	{ szAquamarine, COXColor::m_Aquamarine },
	{ szAquamarine1, COXColor::m_Aquamarine1 },
	{ szAquamarine2, COXColor::m_Aquamarine2 },
	{ szAquamarine3, COXColor::m_Aquamarine3 },
	{ szAquamarine4, COXColor::m_Aquamarine4 },
	{ szAzure, COXColor::m_Azure },
	{ szAzure1, COXColor::m_Azure1 },
	{ szAzure2, COXColor::m_Azure2 },
	{ szAzure3, COXColor::m_Azure3 },
	{ szAzure4, COXColor::m_Azure4 },
	{ szBeet, COXColor::m_Beet },
	{ szBeige, COXColor::m_Beige },
	{ szBisque, COXColor::m_Bisque },
	{ szBisque1, COXColor::m_Bisque1 },
	{ szBisque2, COXColor::m_Bisque2 },
	{ szBisque3, COXColor::m_Bisque3 },
	{ szBisque4, COXColor::m_Bisque4 },
	{ szBlack, COXColor::m_Black },
	{ szBlanchedAlmond, COXColor::m_BlanchedAlmond },
	{ szBlue, COXColor::m_Blue },
	{ szBlue1, COXColor::m_Blue1 },
	{ szBlue2, COXColor::m_Blue2 },
	{ szBlue3, COXColor::m_Blue3 },
	{ szBlue4, COXColor::m_Blue4 },
	{ szBlueViolet, COXColor::m_BlueViolet },
	{ szBrightGray, COXColor::m_BrightGray },
	{ szBrown, COXColor::m_Brown },
	{ szBrown1, COXColor::m_Brown1 },
	{ szBrown2, COXColor::m_Brown2 },
	{ szBrown3, COXColor::m_Brown3 },
	{ szBrown4, COXColor::m_Brown4 },
	{ szBurlywood, COXColor::m_Burlywood },
	{ szBurlywood1, COXColor::m_Burlywood1 },
	{ szBurlywood2, COXColor::m_Burlywood2 },
	{ szBurlywood3, COXColor::m_Burlywood3 },
	{ szBurlywood4, COXColor::m_Burlywood4 },
	{ szCadetBlue, COXColor::m_CadetBlue },
	{ szCadetBlue1, COXColor::m_CadetBlue1 },
	{ szCadetBlue2, COXColor::m_CadetBlue2 },
	{ szCadetBlue3, COXColor::m_CadetBlue3 },
	{ szCadetBlue4, COXColor::m_CadetBlue4 },
	{ szChartreuse, COXColor::m_Chartreuse },
	{ szChartreuse1, COXColor::m_Chartreuse1 },
	{ szChartreuse2, COXColor::m_Chartreuse2 },
	{ szChartreuse3, COXColor::m_Chartreuse3 },
	{ szChartreuse4, COXColor::m_Chartreuse4 },
	{ szChocolate, COXColor::m_Chocolate },
	{ szChocolate1, COXColor::m_Chocolate1 },
	{ szChocolate2, COXColor::m_Chocolate2 },
	{ szChocolate3, COXColor::m_Chocolate3 },
	{ szChocolate4, COXColor::m_Chocolate4 },
	{ szCoral, COXColor::m_Coral },
	{ szCoral1, COXColor::m_Coral1 },
	{ szCoral2, COXColor::m_Coral2 },
	{ szCoral3, COXColor::m_Coral3 },
	{ szCoral4, COXColor::m_Coral4 },
	{ szCornflowerBlue, COXColor::m_CornflowerBlue },
	{ szCornsilk, COXColor::m_Cornsilk },
	{ szCornsilk1, COXColor::m_Cornsilk1 },
	{ szCornsilk2, COXColor::m_Cornsilk2 },
	{ szCornsilk3, COXColor::m_Cornsilk3 },
	{ szCornsilk4, COXColor::m_Cornsilk4 },
	{ szCrimson, COXColor::m_Crimson },
	{ szCyan, COXColor::m_Cyan },
	{ szCyan1, COXColor::m_Cyan1 },
	{ szCyan2, COXColor::m_Cyan2 },
	{ szCyan3, COXColor::m_Cyan3 },
	{ szCyan4, COXColor::m_Cyan4 },
	{ szDarkBlue, COXColor::m_DarkBlue },
	{ szDarkCyan, COXColor::m_DarkCyan },
	{ szDarkGoldenrod, COXColor::m_DarkGoldenrod },
	{ szDarkGoldenrod1, COXColor::m_DarkGoldenrod1 },
	{ szDarkGoldenrod2, COXColor::m_DarkGoldenrod2 },
	{ szDarkGoldenrod3, COXColor::m_DarkGoldenrod3 },
	{ szDarkGoldenrod4, COXColor::m_DarkGoldenrod4 },
	{ szDarkGray, COXColor::m_DarkGray },
	{ szDarkGreen, COXColor::m_DarkGreen },
	{ szDarkKhaki, COXColor::m_DarkKhaki },
	{ szDarkMagenta, COXColor::m_DarkMagenta },
	{ szDarkOliveGreen, COXColor::m_DarkOliveGreen },
	{ szDarkOliveGreen1, COXColor::m_DarkOliveGreen1 },
	{ szDarkOliveGreen2, COXColor::m_DarkOliveGreen2 },
	{ szDarkOliveGreen3, COXColor::m_DarkOliveGreen3 },
	{ szDarkOliveGreen4, COXColor::m_DarkOliveGreen4 },
	{ szDarkOrange, COXColor::m_DarkOrange },
	{ szDarkOrange1, COXColor::m_DarkOrange1 },
	{ szDarkOrange2, COXColor::m_DarkOrange2 },
	{ szDarkOrange3, COXColor::m_DarkOrange3 },
	{ szDarkOrange4, COXColor::m_DarkOrange4 },
	{ szDarkOrchid, COXColor::m_DarkOrchid },
	{ szDarkOrchid1, COXColor::m_DarkOrchid1 },
	{ szDarkOrchid2, COXColor::m_DarkOrchid2 },
	{ szDarkOrchid3, COXColor::m_DarkOrchid3 },
	{ szDarkOrchid4, COXColor::m_DarkOrchid4 },
	{ szDarkRed, COXColor::m_DarkRed },
	{ szDarkSalmon, COXColor::m_DarkSalmon },
	{ szDarkSeaGreen, COXColor::m_DarkSeaGreen },
	{ szDarkSeaGreen1, COXColor::m_DarkSeaGreen1 },
	{ szDarkSeaGreen2, COXColor::m_DarkSeaGreen2 },
	{ szDarkSeaGreen3, COXColor::m_DarkSeaGreen3 },
	{ szDarkSeaGreen4, COXColor::m_DarkSeaGreen4 },
	{ szDarkSlateBlue, COXColor::m_DarkSlateBlue },
	{ szDarkSlateGray, COXColor::m_DarkSlateGray },
	{ szDarkSlateGray1, COXColor::m_DarkSlateGray1 },
	{ szDarkSlateGray2, COXColor::m_DarkSlateGray2 },
	{ szDarkSlateGray3, COXColor::m_DarkSlateGray3 },
	{ szDarkSlateGray4, COXColor::m_DarkSlateGray4 },
	{ szDarkTurquoise, COXColor::m_DarkTurquoise },
	{ szDarkViolet, COXColor::m_DarkViolet },
	{ szDeepPink, COXColor::m_DeepPink },
	{ szDeepPink1, COXColor::m_DeepPink1 },
	{ szDeepPink2, COXColor::m_DeepPink2 },
	{ szDeepPink3, COXColor::m_DeepPink3 },
	{ szDeepPink4, COXColor::m_DeepPink4 },
	{ szDeepSkyBlue, COXColor::m_DeepSkyBlue },
	{ szDeepSkyBlue1, COXColor::m_DeepSkyBlue1 },
	{ szDeepSkyBlue2, COXColor::m_DeepSkyBlue2 },
	{ szDeepSkyBlue3, COXColor::m_DeepSkyBlue3 },
	{ szDeepSkyBlue4, COXColor::m_DeepSkyBlue4 },
	{ szDimGray, COXColor::m_DimGray },
	{ szDodgerBlue, COXColor::m_DodgerBlue },
	{ szDodgerBlue1, COXColor::m_DodgerBlue1 },
	{ szDodgerBlue2, COXColor::m_DodgerBlue2 },
	{ szDodgerBlue3, COXColor::m_DodgerBlue3 },
	{ szDodgerBlue4, COXColor::m_DodgerBlue4 },
	{ szFirebrick, COXColor::m_Firebrick },
	{ szFirebrick1, COXColor::m_Firebrick1 },
	{ szFirebrick2, COXColor::m_Firebrick2 },
	{ szFirebrick3, COXColor::m_Firebrick3 },
	{ szFirebrick4, COXColor::m_Firebrick4 },
	{ szFloralWhite, COXColor::m_FloralWhite },
	{ szForestGreen, COXColor::m_ForestGreen },
	{ szGainsboro, COXColor::m_Gainsboro },
	{ szGhostWhite, COXColor::m_GhostWhite },
	{ szGold, COXColor::m_Gold },
	{ szGold1, COXColor::m_Gold1 },
	{ szGold2, COXColor::m_Gold2 },
	{ szGold3, COXColor::m_Gold3 },
	{ szGold4, COXColor::m_Gold4 },
	{ szGoldenrod, COXColor::m_Goldenrod },
	{ szGoldenrod1, COXColor::m_Goldenrod1 },
	{ szGoldenrod2, COXColor::m_Goldenrod2 },
	{ szGoldenrod3, COXColor::m_Goldenrod3 },
	{ szGoldenrod4, COXColor::m_Goldenrod4 },
	{ szGray, COXColor::m_Gray },
	{ szGray0, COXColor::m_Gray0 },
	{ szGray2, COXColor::m_Gray2 },
	{ szGray3, COXColor::m_Gray3 },
	{ szGray4, COXColor::m_Gray4 },
	{ szGray5, COXColor::m_Gray5 },
	{ szGray6, COXColor::m_Gray6 },
	{ szGray7, COXColor::m_Gray7 },
	{ szGray8, COXColor::m_Gray8 },
	{ szGray9, COXColor::m_Gray9 },
	{ szGray1, COXColor::m_Gray1 },
	{ szGray10, COXColor::m_Gray10 },
	{ szGray11, COXColor::m_Gray11 },
	{ szGray12, COXColor::m_Gray12 },
	{ szGray13, COXColor::m_Gray13 },
	{ szGray14, COXColor::m_Gray14 },
	{ szGray15, COXColor::m_Gray15 },
	{ szGray16, COXColor::m_Gray16 },
	{ szGray17, COXColor::m_Gray17 },
	{ szGray18, COXColor::m_Gray18 },
	{ szGray19, COXColor::m_Gray19 },
	{ szGray20, COXColor::m_Gray20 },
	{ szGray21, COXColor::m_Gray21 },
	{ szGray22, COXColor::m_Gray22 },
	{ szGray23, COXColor::m_Gray23 },
	{ szGray24, COXColor::m_Gray24 },
	{ szGray25, COXColor::m_Gray25 },
	{ szGray26, COXColor::m_Gray26 },
	{ szGray27, COXColor::m_Gray27 },
	{ szGray28, COXColor::m_Gray28 },
	{ szGray29, COXColor::m_Gray29 },
	{ szGray30, COXColor::m_Gray30 },
	{ szGray31, COXColor::m_Gray31 },
	{ szGray32, COXColor::m_Gray32 },
	{ szGray33, COXColor::m_Gray33 },
	{ szGray34, COXColor::m_Gray34 },
	{ szGray35, COXColor::m_Gray35 },
	{ szGray36, COXColor::m_Gray36 },
	{ szGray37, COXColor::m_Gray37 },
	{ szGray38, COXColor::m_Gray38 },
	{ szGray39, COXColor::m_Gray39 },
	{ szGray40, COXColor::m_Gray40 },
	{ szGray41, COXColor::m_Gray41 },
	{ szGray42, COXColor::m_Gray42 },
	{ szGray43, COXColor::m_Gray43 },
	{ szGray44, COXColor::m_Gray44 },
	{ szGray45, COXColor::m_Gray45 },
	{ szGray46, COXColor::m_Gray46 },
	{ szGray47, COXColor::m_Gray47 },
	{ szGray48, COXColor::m_Gray48 },
	{ szGray49, COXColor::m_Gray49 },
	{ szGray50, COXColor::m_Gray50 },
	{ szGray51, COXColor::m_Gray51 },
	{ szGray52, COXColor::m_Gray52 },
	{ szGray53, COXColor::m_Gray53 },
	{ szGray54, COXColor::m_Gray54 },
	{ szGray55, COXColor::m_Gray55 },
	{ szGray56, COXColor::m_Gray56 },
	{ szGray57, COXColor::m_Gray57 },
	{ szGray58, COXColor::m_Gray58 },
	{ szGray59, COXColor::m_Gray59 },
	{ szGray60, COXColor::m_Gray60 },
	{ szGray61, COXColor::m_Gray61 },
	{ szGray62, COXColor::m_Gray62 },
	{ szGray63, COXColor::m_Gray63 },
	{ szGray64, COXColor::m_Gray64 },
	{ szGray65, COXColor::m_Gray65 },
	{ szGray66, COXColor::m_Gray66 },
	{ szGray67, COXColor::m_Gray67 },
	{ szGray68, COXColor::m_Gray68 },
	{ szGray69, COXColor::m_Gray69 },
	{ szGray70, COXColor::m_Gray70 },
	{ szGray71, COXColor::m_Gray71 },
	{ szGray72, COXColor::m_Gray72 },
	{ szGray73, COXColor::m_Gray73 },
	{ szGray74, COXColor::m_Gray74 },
	{ szGray75, COXColor::m_Gray75 },
	{ szGray76, COXColor::m_Gray76 },
	{ szGray77, COXColor::m_Gray77 },
	{ szGray78, COXColor::m_Gray78 },
	{ szGray79, COXColor::m_Gray79 },
	{ szGray80, COXColor::m_Gray80 },
	{ szGray81, COXColor::m_Gray81 },
	{ szGray82, COXColor::m_Gray82 },
	{ szGray83, COXColor::m_Gray83 },
	{ szGray84, COXColor::m_Gray84 },
	{ szGray85, COXColor::m_Gray85 },
	{ szGray86, COXColor::m_Gray86 },
	{ szGray87, COXColor::m_Gray87 },
	{ szGray88, COXColor::m_Gray88 },
	{ szGray89, COXColor::m_Gray89 },
	{ szGray90, COXColor::m_Gray90 },
	{ szGray91, COXColor::m_Gray91 },
	{ szGray92, COXColor::m_Gray92 },
	{ szGray93, COXColor::m_Gray93 },
	{ szGray94, COXColor::m_Gray94 },
	{ szGray95, COXColor::m_Gray95 },
	{ szGray96, COXColor::m_Gray96 },
	{ szGray97, COXColor::m_Gray97 },
	{ szGray98, COXColor::m_Gray98 },
	{ szGray99, COXColor::m_Gray99 },
	{ szGray100, COXColor::m_Gray100 },
	{ szGreen, COXColor::m_Green },
	{ szGreen1, COXColor::m_Green1 },
	{ szGreen2, COXColor::m_Green2 },
	{ szGreen3, COXColor::m_Green3 },
	{ szGreen4, COXColor::m_Green4 },
	{ szGreenYellow, COXColor::m_GreenYellow },
	{ szHoneydew, COXColor::m_Honeydew },
	{ szHoneydew1, COXColor::m_Honeydew1 },
	{ szHoneydew2, COXColor::m_Honeydew2 },
	{ szHoneydew3, COXColor::m_Honeydew3 },
	{ szHoneydew4, COXColor::m_Honeydew4 },
	{ szHotPink, COXColor::m_HotPink },
	{ szHotPink1, COXColor::m_HotPink1 },
	{ szHotPink2, COXColor::m_HotPink2 },
	{ szHotPink3, COXColor::m_HotPink3 },
	{ szHotPink4, COXColor::m_HotPink4 },
	{ szIndianRed, COXColor::m_IndianRed },
	{ szIndianRed1, COXColor::m_IndianRed1 },
	{ szIndianRed2, COXColor::m_IndianRed2 },
	{ szIndianRed3, COXColor::m_IndianRed3 },
	{ szIndianRed4, COXColor::m_IndianRed4 },
	{ szIndigo, COXColor::m_Indigo },
	{ szIndigo2, COXColor::m_Indigo2 },
	{ szIvory, COXColor::m_Ivory },
	{ szIvory1, COXColor::m_Ivory1 },
	{ szIvory2, COXColor::m_Ivory2 },
	{ szIvory3, COXColor::m_Ivory3 },
	{ szIvory4, COXColor::m_Ivory4 },
	{ szKhaki, COXColor::m_Khaki },
	{ szKhaki1, COXColor::m_Khaki1 },
	{ szKhaki2, COXColor::m_Khaki2 },
	{ szKhaki3, COXColor::m_Khaki3 },
	{ szKhaki4, COXColor::m_Khaki4 },
	{ szLavender, COXColor::m_Lavender },
	{ szLavenderBlush, COXColor::m_LavenderBlush },
	{ szLavenderBlush1, COXColor::m_LavenderBlush1 },
	{ szLavenderBlush2, COXColor::m_LavenderBlush2 },
	{ szLavenderBlush3, COXColor::m_LavenderBlush3 },
	{ szLavenderBlush4, COXColor::m_LavenderBlush4 },
	{ szLawnGreen, COXColor::m_LawnGreen },
	{ szLemonChiffon, COXColor::m_LemonChiffon },
	{ szLemonChiffon1, COXColor::m_LemonChiffon1 },
	{ szLemonChiffon2, COXColor::m_LemonChiffon2 },
	{ szLemonChiffon3, COXColor::m_LemonChiffon3 },
	{ szLemonChiffon4, COXColor::m_LemonChiffon4 },
	{ szLightBlue, COXColor::m_LightBlue },
	{ szLightBlue1, COXColor::m_LightBlue1 },
	{ szLightBlue2, COXColor::m_LightBlue2 },
	{ szLightBlue3, COXColor::m_LightBlue3 },
	{ szLightBlue4, COXColor::m_LightBlue4 },
	{ szLightCoral, COXColor::m_LightCoral },
	{ szLightCyan, COXColor::m_LightCyan },
	{ szLightCyan1, COXColor::m_LightCyan1 },
	{ szLightCyan2, COXColor::m_LightCyan2 },
	{ szLightCyan3, COXColor::m_LightCyan3 },
	{ szLightCyan4, COXColor::m_LightCyan4 },
	{ szLightGoldenrod, COXColor::m_LightGoldenrod },
	{ szLightGoldenrod1, COXColor::m_LightGoldenrod1 },
	{ szLightGoldenrod2, COXColor::m_LightGoldenrod2 },
	{ szLightGoldenrod3, COXColor::m_LightGoldenrod3 },
	{ szLightGoldenrod4, COXColor::m_LightGoldenrod4 },
	{ szLightGoldenrodYellow, COXColor::m_LightGoldenrodYellow },
	{ szLightGray, COXColor::m_LightGray },
	{ szLightGreen, COXColor::m_LightGreen },
	{ szLightPink, COXColor::m_LightPink },
	{ szLightPink1, COXColor::m_LightPink1 },
	{ szLightPink2, COXColor::m_LightPink2 },
	{ szLightPink3, COXColor::m_LightPink3 },
	{ szLightPink4, COXColor::m_LightPink4 },
	{ szLightSalmon, COXColor::m_LightSalmon },
	{ szLightSalmon1, COXColor::m_LightSalmon1 },
	{ szLightSalmon2, COXColor::m_LightSalmon2 },
	{ szLightSalmon3, COXColor::m_LightSalmon3 },
	{ szLightSalmon4, COXColor::m_LightSalmon4 },
	{ szLightSeaGreen, COXColor::m_LightSeaGreen },
	{ szLightSkyBlue, COXColor::m_LightSkyBlue },
	{ szLightSkyBlue1, COXColor::m_LightSkyBlue1 },
	{ szLightSkyBlue2, COXColor::m_LightSkyBlue2 },
	{ szLightSkyBlue3, COXColor::m_LightSkyBlue3 },
	{ szLightSkyBlue4, COXColor::m_LightSkyBlue4 },
	{ szLightSlateBlue, COXColor::m_LightSlateBlue },
	{ szLightSlateGray, COXColor::m_LightSlateGray },
	{ szLightSteelBlue, COXColor::m_LightSteelBlue },
	{ szLightSteelBlue1, COXColor::m_LightSteelBlue1 },
	{ szLightSteelBlue2, COXColor::m_LightSteelBlue2 },
	{ szLightSteelBlue3, COXColor::m_LightSteelBlue3 },
	{ szLightSteelBlue4, COXColor::m_LightSteelBlue4 },
	{ szLightYellow, COXColor::m_LightYellow },
	{ szLightYellow1, COXColor::m_LightYellow1 },
	{ szLightYellow2, COXColor::m_LightYellow2 },
	{ szLightYellow3, COXColor::m_LightYellow3 },
	{ szLightYellow4, COXColor::m_LightYellow4 },
	{ szLimeGreen, COXColor::m_LimeGreen },
	{ szLinen, COXColor::m_Linen },
	{ szMagenta, COXColor::m_Magenta },
	{ szMagenta1, COXColor::m_Magenta1 },
	{ szMagenta2, COXColor::m_Magenta2 },
	{ szMagenta3, COXColor::m_Magenta3 },
	{ szMagenta4, COXColor::m_Magenta4 },
	{ szMaroon, COXColor::m_Maroon },
	{ szMaroon1, COXColor::m_Maroon1 },
	{ szMaroon2, COXColor::m_Maroon2 },
	{ szMaroon3, COXColor::m_Maroon3 },
	{ szMaroon4, COXColor::m_Maroon4 },
	{ szMediumAquamarine, COXColor::m_MediumAquamarine },
	{ szMediumBlue, COXColor::m_MediumBlue },
	{ szMediumGray, COXColor::m_MediumGray },
	{ szMediumOrchid, COXColor::m_MediumOrchid },
	{ szMediumOrchid1, COXColor::m_MediumOrchid1 },
	{ szMediumOrchid2, COXColor::m_MediumOrchid2 },
	{ szMediumOrchid3, COXColor::m_MediumOrchid3 },
	{ szMediumOrchid4, COXColor::m_MediumOrchid4 },
	{ szMediumPurple, COXColor::m_MediumPurple },
	{ szMediumPurple1, COXColor::m_MediumPurple1 },
	{ szMediumPurple2, COXColor::m_MediumPurple2 },
	{ szMediumPurple3, COXColor::m_MediumPurple3 },
	{ szMediumPurple4, COXColor::m_MediumPurple4 },
	{ szMediumSeaGreen, COXColor::m_MediumSeaGreen },
	{ szMediumSlateBlue, COXColor::m_MediumSlateBlue },
	{ szMediumSpringGreen, COXColor::m_MediumSpringGreen },
	{ szMediumTurquoise, COXColor::m_MediumTurquoise },
	{ szMediumVioletRed, COXColor::m_MediumVioletRed },
	{ szMidnightBlue, COXColor::m_MidnightBlue },
	{ szMintCream, COXColor::m_MintCream },
	{ szMistyRose, COXColor::m_MistyRose },
	{ szMistyRose1, COXColor::m_MistyRose1 },
	{ szMistyRose2, COXColor::m_MistyRose2 },
	{ szMistyRose3, COXColor::m_MistyRose3 },
	{ szMistyRose4, COXColor::m_MistyRose4 },
	{ szMoccasin, COXColor::m_Moccasin },
	{ szNavajoWhite, COXColor::m_NavajoWhite },
	{ szNavajoWhite1, COXColor::m_NavajoWhite1 },
	{ szNavajoWhite2, COXColor::m_NavajoWhite2 },
	{ szNavajoWhite3, COXColor::m_NavajoWhite3 },
	{ szNavajoWhite4, COXColor::m_NavajoWhite4 },
	{ szNavy, COXColor::m_Navy },
	{ szNavyBlue, COXColor::m_NavyBlue },
	{ szOldLace, COXColor::m_OldLace },
	{ szOliveDrab, COXColor::m_OliveDrab },
	{ szOliveDrab1, COXColor::m_OliveDrab1 },
	{ szOliveDrab2, COXColor::m_OliveDrab2 },
	{ szOliveDrab3, COXColor::m_OliveDrab3 },
	{ szOliveDrab4, COXColor::m_OliveDrab4 },
	{ szOrange, COXColor::m_Orange },
	{ szOrange1, COXColor::m_Orange1 },
	{ szOrange2, COXColor::m_Orange2 },
	{ szOrange3, COXColor::m_Orange3 },
	{ szOrange4, COXColor::m_Orange4 },
	{ szOrangeRed, COXColor::m_OrangeRed },
	{ szOrangeRed1, COXColor::m_OrangeRed1 },
	{ szOrangeRed2, COXColor::m_OrangeRed2 },
	{ szOrangeRed3, COXColor::m_OrangeRed3 },
	{ szOrangeRed4, COXColor::m_OrangeRed4 },
	{ szOrchid, COXColor::m_Orchid },
	{ szOrchid1, COXColor::m_Orchid1 },
	{ szOrchid2, COXColor::m_Orchid2 },
	{ szOrchid3, COXColor::m_Orchid3 },
	{ szOrchid4, COXColor::m_Orchid4 },
	{ szPaleGoldenrod, COXColor::m_PaleGoldenrod },
	{ szPaleGreen, COXColor::m_PaleGreen },
	{ szPaleGreen1, COXColor::m_PaleGreen1 },
	{ szPaleGreen2, COXColor::m_PaleGreen2 },
	{ szPaleGreen3, COXColor::m_PaleGreen3 },
	{ szPaleGreen4, COXColor::m_PaleGreen4 },
	{ szPaleTurquoise, COXColor::m_PaleTurquoise },
	{ szPaleTurquoise1, COXColor::m_PaleTurquoise1 },
	{ szPaleTurquoise2, COXColor::m_PaleTurquoise2 },
	{ szPaleTurquoise3, COXColor::m_PaleTurquoise3 },
	{ szPaleTurquoise4, COXColor::m_PaleTurquoise4 },
	{ szPaleVioletRed, COXColor::m_PaleVioletRed },
	{ szPaleVioletRed1, COXColor::m_PaleVioletRed1 },
	{ szPaleVioletRed2, COXColor::m_PaleVioletRed2 },
	{ szPaleVioletRed3, COXColor::m_PaleVioletRed3 },
	{ szPaleVioletRed4, COXColor::m_PaleVioletRed4 },
	{ szPapayaWhip, COXColor::m_PapayaWhip },
	{ szPeachPuff, COXColor::m_PeachPuff },
	{ szPeachPuff1, COXColor::m_PeachPuff1 },
	{ szPeachPuff2, COXColor::m_PeachPuff2 },
	{ szPeachPuff3, COXColor::m_PeachPuff3 },
	{ szPeachPuff4, COXColor::m_PeachPuff4 },
	{ szPeru, COXColor::m_Peru },
	{ szPink, COXColor::m_Pink },
	{ szPink1, COXColor::m_Pink1 },
	{ szPink2, COXColor::m_Pink2 },
	{ szPink3, COXColor::m_Pink3 },
	{ szPink4, COXColor::m_Pink4 },
	{ szPlum, COXColor::m_Plum },
	{ szPlum1, COXColor::m_Plum1 },
	{ szPlum2, COXColor::m_Plum2 },
	{ szPlum3, COXColor::m_Plum3 },
	{ szPlum4, COXColor::m_Plum4 },
	{ szPowderBlue, COXColor::m_PowderBlue },
	{ szPurple, COXColor::m_Purple },
	{ szPurple1, COXColor::m_Purple1 },
	{ szPurple2, COXColor::m_Purple2 },
	{ szPurple3, COXColor::m_Purple3 },
	{ szPurple4, COXColor::m_Purple4 },
	{ szRed, COXColor::m_Red },
	{ szRed1, COXColor::m_Red1 },
	{ szRed2, COXColor::m_Red2 },
	{ szRed3, COXColor::m_Red3 },
	{ szRed4, COXColor::m_Red4 },
	{ szRosyBrown, COXColor::m_RosyBrown },
	{ szRosyBrown1, COXColor::m_RosyBrown1 },
	{ szRosyBrown2, COXColor::m_RosyBrown2 },
	{ szRosyBrown3, COXColor::m_RosyBrown3 },
	{ szRosyBrown4, COXColor::m_RosyBrown4 },
	{ szRoyalBlue, COXColor::m_RoyalBlue },
	{ szRoyalBlue1, COXColor::m_RoyalBlue1 },
	{ szRoyalBlue2, COXColor::m_RoyalBlue2 },
	{ szRoyalBlue3, COXColor::m_RoyalBlue3 },
	{ szRoyalBlue4, COXColor::m_RoyalBlue4 },
	{ szSaddleBrown, COXColor::m_SaddleBrown },
	{ szSalmon, COXColor::m_Salmon },
	{ szSalmon1, COXColor::m_Salmon1 },
	{ szSalmon2, COXColor::m_Salmon2 },
	{ szSalmon3, COXColor::m_Salmon3 },
	{ szSalmon4, COXColor::m_Salmon4 },
	{ szSandyBrown, COXColor::m_SandyBrown },
	{ szSeaGreen, COXColor::m_SeaGreen },
	{ szSeaGreen1, COXColor::m_SeaGreen1 },
	{ szSeaGreen2, COXColor::m_SeaGreen2 },
	{ szSeaGreen3, COXColor::m_SeaGreen3 },
	{ szSeaGreen4, COXColor::m_SeaGreen4 },
	{ szSeashell, COXColor::m_Seashell },
	{ szSeashell1, COXColor::m_Seashell1 },
	{ szSeashell2, COXColor::m_Seashell2 },
	{ szSeashell3, COXColor::m_Seashell3 },
	{ szSeashell4, COXColor::m_Seashell4 },
	{ szSienna, COXColor::m_Sienna },
	{ szSienna1, COXColor::m_Sienna1 },
	{ szSienna2, COXColor::m_Sienna2 },
	{ szSienna3, COXColor::m_Sienna3 },
	{ szSienna4, COXColor::m_Sienna4 },
	{ szSkyBlue, COXColor::m_SkyBlue },
	{ szSkyBlue1, COXColor::m_SkyBlue1 },
	{ szSkyBlue2, COXColor::m_SkyBlue2 },
	{ szSkyBlue3, COXColor::m_SkyBlue3 },
	{ szSkyBlue4, COXColor::m_SkyBlue4 },
	{ szSlateBlue, COXColor::m_SlateBlue },
	{ szSlateBlue1, COXColor::m_SlateBlue1 },
	{ szSlateBlue2, COXColor::m_SlateBlue2 },
	{ szSlateBlue3, COXColor::m_SlateBlue3 },
	{ szSlateBlue4, COXColor::m_SlateBlue4 },
	{ szSlateGray, COXColor::m_SlateGray },
	{ szSlateGray1, COXColor::m_SlateGray1 },
	{ szSlateGray2, COXColor::m_SlateGray2 },
	{ szSlateGray3, COXColor::m_SlateGray3 },
	{ szSlateGray4, COXColor::m_SlateGray4 },
	{ szSnow, COXColor::m_Snow },
	{ szSnow1, COXColor::m_Snow1 },
	{ szSnow2, COXColor::m_Snow2 },
	{ szSnow3, COXColor::m_Snow3 },
	{ szSnow4, COXColor::m_Snow4 },
	{ szSpringGreen, COXColor::m_SpringGreen },
	{ szSpringGreen1, COXColor::m_SpringGreen1 },
	{ szSpringGreen2, COXColor::m_SpringGreen2 },
	{ szSpringGreen3, COXColor::m_SpringGreen3 },
	{ szSpringGreen4, COXColor::m_SpringGreen4 },
	{ szSteelBlue, COXColor::m_SteelBlue },
	{ szSteelBlue1, COXColor::m_SteelBlue1 },
	{ szSteelBlue2, COXColor::m_SteelBlue2 },
	{ szSteelBlue3, COXColor::m_SteelBlue3 },
	{ szSteelBlue4, COXColor::m_SteelBlue4 },
	{ szTan, COXColor::m_Tan },
	{ szTan1, COXColor::m_Tan1 },
	{ szTan2, COXColor::m_Tan2 },
	{ szTan3, COXColor::m_Tan3 },
	{ szTan4, COXColor::m_Tan4 },
	{ szTeal, COXColor::m_Teal },
	{ szThistle, COXColor::m_Thistle },
	{ szThistle1, COXColor::m_Thistle1 },
	{ szThistle2, COXColor::m_Thistle2 },
	{ szThistle3, COXColor::m_Thistle3 },
	{ szThistle4, COXColor::m_Thistle4 },
	{ szTomato, COXColor::m_Tomato },
	{ szTomato1, COXColor::m_Tomato1 },
	{ szTomato2, COXColor::m_Tomato2 },
	{ szTomato3, COXColor::m_Tomato3 },
	{ szTomato4, COXColor::m_Tomato4 },
	{ szTurquoise, COXColor::m_Turquoise },
	{ szTurquoise1, COXColor::m_Turquoise1 },
	{ szTurquoise2, COXColor::m_Turquoise2 },
	{ szTurquoise3, COXColor::m_Turquoise3 },
	{ szTurquoise4, COXColor::m_Turquoise4 },
	{ szVeryDarkGray, COXColor::m_VeryDarkGray },
	{ szVeryLightGray, COXColor::m_VeryLightGray },
	{ szViolet, COXColor::m_Violet },
	{ szVioletRed, COXColor::m_VioletRed },
	{ szVioletRed1, COXColor::m_VioletRed1 },
	{ szVioletRed2, COXColor::m_VioletRed2 },
	{ szVioletRed3, COXColor::m_VioletRed3 },
	{ szVioletRed4, COXColor::m_VioletRed4 },
	{ szWheat, COXColor::m_Wheat },
	{ szWheat1, COXColor::m_Wheat1 },
	{ szWheat2, COXColor::m_Wheat2 },
	{ szWheat3, COXColor::m_Wheat3 },
	{ szWheat4, COXColor::m_Wheat4 },
	{ szWhite, COXColor::m_White },
	{ szWhiteSmoke, COXColor::m_WhiteSmoke },
	{ szYellow, COXColor::m_Yellow },
	{ szYellow1, COXColor::m_Yellow1 },
	{ szYellow2, COXColor::m_Yellow2 },
	{ szYellow3, COXColor::m_Yellow3 },
	{ szYellow4, COXColor::m_Yellow4 },
	{ szYellowGreen, COXColor::m_YellowGreen },
	{NULL, 0},
};

const int COXColor::m_nNumberOfColors = OX_NUM_COLORS;
#endif // OX_COLORS_NO_NAMES 

// Data members -------------------------------------------------------------
// protected:

// private:
	
// Member functions ---------------------------------------------------------
// public:
// protected:
COXColor::COXColor()
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Constructs the object
{
}

COXColor::~COXColor()
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of the object
{
}

COLORREF COXColor::HSBtoRGB(float fHue, float fSaturation, float fBrightness)
{
	int r = 0, g = 0, b = 0;
    if (fSaturation == 0)
	{
		r = g = b = (int) (fBrightness * 255);
	}
	else
	{
		double h = fHue * 6.0;
		double f = h - floor(h);
		double p = fBrightness * (1.0 - fSaturation);
		double q = fBrightness * (1.0 - fSaturation * f);
		double t = fBrightness * (1.0 - (fSaturation * (1.0 - f)));

		switch ((int) h)
		{
			case 0:
				r = (int) (fBrightness * 255);
				g = (int) (t * 255);
				b = (int) (p * 255);
				break;
			case 1:
				r = (int) (q * 255);
				g = (int) (fBrightness * 255);
				b = (int) (p * 255);
				break;
			case 2:
				r = (int) (p * 255);
				g = (int) (fBrightness * 255);
				b = (int) (t * 255);
				break;
			case 3:
				r = (int) (p * 255);
				g = (int) (q * 255);
				b = (int) (fBrightness * 255);
				break;
			case 4:
				r = (int) (t * 255);
				g = (int) (p * 255);
				b = (int) (fBrightness * 255);
				break;
			case 5:
				r = (int) (fBrightness * 255);
				g = (int) (p * 255);
				b = (int) (q * 255);
				break;
		}
	}
	
	return (r << 0) | (g << 8) | (b << 16);
}

void COXColor::RGBtoHSBFloat(int r, int g, int b, float* pHSBVals)
{
	float fHue, fSaturation, fBrightness;
   
	int cmax = (r > g) ? r : g;
	if (b > cmax)
		cmax = b;
	int cmin = (r < g) ? r : g;
	if (b < cmin)
		cmin = b;

	fBrightness = ((float) cmax) / 255.0f;
	if (cmax != 0)
	    fSaturation = ((float) (cmax - cmin)) / ((float) cmax);
	else
	    fSaturation = (float)0;
	if (fSaturation == 0)
	    fHue = (float)0;
	else
	{
	    float redc = ((float) (cmax - r)) / ((float) (cmax - cmin));
	    float greenc = ((float) (cmax - g)) / ((float) (cmax - cmin));
	    float bluec = ((float) (cmax - b)) / ((float) (cmax - cmin));
	    if (r == cmax)
			fHue = bluec - greenc;
	    else if (g == cmax)
				fHue = 2.0f + redc - bluec;
            else
				fHue = 4.0f + greenc - redc;
	    fHue = fHue / 6.0f;
	    if (fHue < 0)
			fHue = fHue + 1.0f;
	}
	
	pHSBVals[0] = fHue;
	pHSBVals[1] = fSaturation;
	pHSBVals[2] = fBrightness;
}

void COXColor::ColorrefToHSB(COLORREF clrRGB, float* pHSBVals)
{
	RGBtoHSBFloat(GetRValue(clrRGB), GetGValue(clrRGB), GetBValue(clrRGB), pHSBVals);
}

void COXColor::ColorrefToHSB(COLORREF clrRGB, BYTE* pHSBVals)
{
	RGBtoHSBInt(GetRValue(clrRGB), GetGValue(clrRGB), GetBValue(clrRGB), pHSBVals);
}

void COXColor::RGBtoHSBInt(BYTE R, BYTE G, BYTE B, BYTE* pHSBVals)
{
	BYTE cMax,cMin;      // max and min RGB values
	WORD  Rdelta,Gdelta,Bdelta; // intermediate value: % of spread from max

	// calculate lightness
	cMax = __max( __max(R,G), B);
	cMin = __min( __min(R,G), B);
	pHSBVals[2] = (BYTE)((((cMax+cMin)*HLSMAX) + RGBMAX )/(2*RGBMAX));

	if (cMax == cMin)
		// r=g=b --> achromatic case
	{           
		pHSBVals[1] = 0;                     // saturation
		pHSBVals[0] = UNDEFINED;             // hue
	}
	else
        // chromatic case
	{
		// saturation
		if (pHSBVals[2] <= (HLSMAX/2))
			pHSBVals[1] = (BYTE)((((cMax-cMin)*HLSMAX) + ((cMax+cMin)/2) ) / (cMax+cMin));
		else
			pHSBVals[1] = (BYTE)((((cMax-cMin)*HLSMAX) + ((2*RGBMAX-cMax-cMin)/2) ) / (2*RGBMAX-cMax-cMin));

		// hue
		Rdelta = (BYTE)((((cMax-R)*(HLSMAX/6)) + ((cMax-cMin)/2) ) / (cMax-cMin));
		Gdelta = (BYTE)((((cMax-G)*(HLSMAX/6)) + ((cMax-cMin)/2) ) / (cMax-cMin));
		Bdelta = (BYTE)((((cMax-B)*(HLSMAX/6)) + ((cMax-cMin)/2) ) / (cMax-cMin));

		if (R == cMax)
			pHSBVals[0] = (BYTE)((Bdelta-Gdelta+HLSMAX)%HLSMAX);
		else if (G == cMax)		                 
			pHSBVals[0] = (BYTE)((Rdelta-Bdelta+HLSMAX+HLSMAX*1/3)%HLSMAX);
		else // B == cMax		                 			          
			pHSBVals[0] = (BYTE)((Gdelta-Rdelta+HLSMAX+HLSMAX*2/3)%HLSMAX);
	}
} 	

BYTE COXColor::HueToRGB(WORD n1, WORD n2, BYTE hue)
{
	// range check: note values passed add/subtract thirds of range
	if (hue < 0)
		hue += HLSMAX;

	if (hue > HLSMAX)
		hue -= HLSMAX;

	// return r,g, or b value from this tridrant
	if (hue < (HLSMAX / 6))
		return (BYTE)(n1 + (((n2 - n1) * hue + (HLSMAX / 12)) / (HLSMAX / 6)));
	if (hue < (HLSMAX / 2))
		return(BYTE)(n2);

	if (hue < ((HLSMAX * 2) / 3))
		return (BYTE)(n1 + (((n2 - n1) * (((HLSMAX * 2) / 3) - hue) + 
			(HLSMAX / 12)) / (HLSMAX / 6))); 
	else
		return(BYTE)(n1);
}
	
COLORREF COXColor::HSBtoRGB(BYTE hue, BYTE saturation, BYTE brightness)
{
	WORD R,G,B;                // RGB component values 
	WORD  Magic1,Magic2;       // calculated magic numbers (really!)

	if (saturation == 0)
	{            // achromatic case 
		R = G = B = (WORD)((brightness * RGBMAX) / HLSMAX);
		if (hue != UNDEFINED)
		{
			// ERROR
		}
	}
	else
	{                    // chromatic case
		// set up magic numbers
		if (brightness <= (HLSMAX / 2))
			Magic2 = (WORD)((brightness * (HLSMAX + saturation) + (HLSMAX / 2)) / HLSMAX);
		else
			Magic2 = (WORD)(brightness + saturation - ((brightness * saturation) + (HLSMAX / 2)) / HLSMAX);
	
		Magic1 = (WORD)(2 * brightness - Magic2);

		// get RGB, change units from HLSMAX to RGBMAX
		R = (WORD)((HueToRGB(Magic1, Magic2,(BYTE)((hue+HLSMAX*1/3)%HLSMAX))*RGBMAX+
			(HLSMAX/2))/HLSMAX); 
		G = (WORD)((HueToRGB(Magic1,Magic2,(BYTE)((hue)))*RGBMAX+(HLSMAX/2))/HLSMAX);
		B = (WORD)((HueToRGB(Magic1,Magic2,(BYTE)((hue+HLSMAX*2/3)%HLSMAX))*RGBMAX+
			(HLSMAX/2))/HLSMAX); 
	}

	return(RGB(R,G,B));
}

COLORREF COXColor::RGBtoGrayscale(COLORREF clr)
{
	int average=GetRValue(clr);
    average+=GetGValue(clr);
    average+=GetBValue(clr);
    average/=3;
    average&=0xff;

	COLORREF clrGrayscale;
    clrGrayscale=average<<16;
    clrGrayscale+=average<<8;
    clrGrayscale+=average;

	return clrGrayscale;
}

COLORREF COXColor::CMYKtoRGB(WORD cyan, WORD magenta, WORD yellow, WORD black)
{
	WORD R,G,B;                // RGB component values 

	R=(WORD)(cyan&black);
	B=(WORD)(magenta&(~R));
	G=(WORD)(yellow&(~R));

	return RGB(R,G,B);

//	return ((COLORREF)((((BYTE)(black)|((WORD)((BYTE)(yellow))<<8))|
//		(((DWORD)(BYTE)(magenta))<<16))|(((DWORD)(BYTE)(cyan))<<24)));
}

COLORREF COXColor::CMYKtoRGB(COLORREF clrCMYK)
{
	return clrCMYK;
}

// private:

// ==========================================================================
