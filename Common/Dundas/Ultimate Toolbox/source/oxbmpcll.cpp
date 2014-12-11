// =============================================================================
// 							Class Implementation : COXBitmapCell
// =============================================================================
//
// Source file : 		oxbmcll.cpp

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved 
                     
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "oxbmpcll.h"

/////////////////////////////////////////////////////////////////////////////
// Definition of static members

// Data members -------------------------------------------------------------
// protected:

	// CBitmap m_Bitmap;		
	// --- bitmap that will be drawn in this cell

// private:
	
// Member functions ---------------------------------------------------------
// public:

COXBitmapCell::COXBitmapCell(UINT nIDResource, EBMPAlignment eAlign /* = BA_Center */,
							 COLORREF clrMask /* = CLR_NONE */)
	: COXCell(BITMAPCELL),
	m_eBMPAlignment(eAlign)
	{
	ASSERT((BA_FIRST <= (int)eAlign) && ((int) eAlign <= BA_LAST));
	VERIFY(m_Bitmap.LoadBitmap(nIDResource));
	BITMAP bm;
	m_Bitmap.GetObject(sizeof(bm), &bm);
	m_Bitmap.SetBitmapDimension(bm.bmWidth,bm.bmHeight);

	// Set the mask color
	m_clrMask = clrMask;

	}

COXBitmapCell::COXBitmapCell(CBitmap* pBitmap, EBMPAlignment eAlign /* = BA_Center */,
							 COLORREF clrMask /* = CLR_NONE */)
	: COXCell(BITMAPCELL),
	m_eBMPAlignment(eAlign)
	{
	ASSERT(pBitmap != NULL);
	ASSERT(pBitmap->m_hObject != NULL);
	ASSERT((BA_FIRST <= (int)eAlign) && ((int) eAlign <= BA_LAST));

	BITMAP bm;
	::GetObject(pBitmap->m_hObject, sizeof(BITMAP), &bm);

	DWORD dwCount = bm.bmHeight * bm.bmWidthBytes * bm.bmPlanes;
	BYTE* byteArray = new BYTE[dwCount];

	VERIFY(pBitmap->GetBitmapBits(dwCount, byteArray));
	m_Bitmap.CreateBitmapIndirect(&bm);
	m_Bitmap.SetBitmapBits(dwCount, byteArray);
	m_Bitmap.SetBitmapDimension(bm.bmWidth,bm.bmHeight);

	// Set the mask color
	m_clrMask = clrMask;

	delete[] byteArray; 
	}

COXBitmapCell::~COXBitmapCell()
	{
	}

void COXBitmapCell::DrawUnconstrained(CDC* pDC, int x, int y,
									  UINT nCellState, COXHintInfo* /*pInfo*/)
	{
	CSize size = GetExtent(pDC, nCellState);
	DrawBitmap(pDC, x, y, size.cx, size.cy);
	}

void COXBitmapCell::DrawConstrained(CDC* pDC, int x, int y, int cx, int cy,
									UINT /*nCellState*/, COXHintInfo* /*pInfo*/)
	{
	DrawBitmap(pDC, x, y, cx, cy);
	}

void COXBitmapCell::DrawBitmap(CDC* pDC, int x, int y, int cx, int cy)
	// --- In  : pDC : the device context to draw on
	// --- Out : 
	// --- Returns :
	// --- Effect : Draws a Bitmap with the specified coordinates and size
	{
	ASSERT(pDC->m_hDC != NULL);

	CRect rectCell(x, y, x + cx, y + cy);
	CSize szSourceBMP = GetExtent(pDC, GDS_DEFAULT);

	// Calculate origin of bitmap drawing within the cell
	int WidthDiff = cx - szSourceBMP.cx;
	int HeightDiff = cy - szSourceBMP.cy;
	CSize BMPDrawSize (WidthDiff > 0 ? szSourceBMP.cx : cx, HeightDiff > 0 ? szSourceBMP.cy : cy);

	y = HeightDiff > 0 ? y + HeightDiff / 2 : y;
	CRect rcDestBMP(CPoint(x, y), BMPDrawSize);

	switch(m_eBMPAlignment)
		{
		case BA_Stretch:
			rcDestBMP = rectCell;
			break;
		case BA_CenterClip:
			szSourceBMP = rcDestBMP.Size();
		case BA_CenterFit:
			rcDestBMP.OffsetRect(WidthDiff > 0 ? WidthDiff / 2 : 0, 0);
			break;
		case BA_RightClip:
			szSourceBMP = rcDestBMP.Size();
		case BA_RightFit:
			rcDestBMP.OffsetRect(WidthDiff > 0 ? WidthDiff : 0, 0);
			break;
		case BA_LeftClip:
			szSourceBMP = rcDestBMP.Size();
		case BA_LeftFit:
			break;
		default:
			ASSERT(FALSE);
		}

	if (m_clrMask != CLR_NONE)
		DrawTranspBitmap(pDC, rcDestBMP, szSourceBMP);
	else
		// if we don't want transparency, just do a stretchblit.
		{
		CDC memDC;
		memDC.CreateCompatibleDC(pDC);
		CBitmap* oldBM = memDC.SelectObject((CBitmap*) &m_Bitmap);

		// Copy the destination to the screen.
		pDC->StretchBlt(rcDestBMP.left, rcDestBMP.top, rcDestBMP.Width(), rcDestBMP.Height(), 
			&memDC, 0, 0 ,szSourceBMP.cx, szSourceBMP.cy, SRCCOPY);
	
		memDC.SelectObject(oldBM);
		}

	}

void COXBitmapCell::DrawTranspBitmap(CDC* pDC, CRect& rcDrawBMP, CSize& szSrcBMP)
	{
	ASSERT(pDC != NULL);

	CBitmap    bmAndBack, bmAndObject, bmAndMem, bmSave;
	CDC        dcMem, dcBack, dcObject, dcTemp, dcSave;

	VERIFY(dcTemp.CreateCompatibleDC(pDC));
	dcTemp.SelectObject(&m_Bitmap);   // Select the bitmap

	CSize TempSize = GetExtent(pDC, GDS_DEFAULT);
	dcTemp.DPtoLP(&TempSize);     // Convert from device
		   						  // to logical points

	// Create some DCs to hold temporary data.
	VERIFY(dcBack.CreateCompatibleDC(pDC));
	VERIFY(dcObject.CreateCompatibleDC(pDC));
	VERIFY(dcMem.CreateCompatibleDC(pDC));
	VERIFY(dcSave.CreateCompatibleDC(pDC));

	// Create a bitmap for each DC. DCs are required for a number of
	// GDI functions.

	// Monochrome DC
	VERIFY(bmAndBack.CreateBitmap(TempSize.cx, TempSize.cy, 1, 1, NULL));

	// Monochrome DC
	VERIFY(bmAndObject.CreateBitmap(TempSize.cx, TempSize.cy, 1, 1, NULL));

	VERIFY(bmAndMem.CreateCompatibleBitmap(pDC, TempSize.cx, TempSize.cy));
	VERIFY(bmSave.CreateCompatibleBitmap(pDC, TempSize.cx, TempSize.cy));

	// Each DC must select a bitmap object to store pixel data.
	CBitmap* pbmBackOld   = dcBack.SelectObject(&bmAndBack);
	CBitmap* pbmObjectOld = dcObject.SelectObject(&bmAndObject);
	CBitmap* pbmMemOld    = dcMem.SelectObject(&bmAndMem);
	CBitmap* pbmSaveOld   = dcSave.SelectObject(&bmSave);

	// Set proper mapping mode.
	dcTemp.SetMapMode(pDC->GetMapMode());

	// Save the bitmap sent here, because it will be overwritten.
	dcSave.BitBlt(0, 0, TempSize.cx, TempSize.cy, &dcTemp, 0, 0, SRCCOPY);

	// Set the background color of the source DC to the color.
	// contained in the parts of the bitmap that should be transparent
	COLORREF clrOldBkColor = dcTemp.SetBkColor(m_clrMask);

	// Create the object mask for the bitmap by performing a BitBlt
	// from the source bitmap to a monochrome bitmap.
	dcObject.BitBlt(0, 0, TempSize.cx, TempSize.cy, &dcTemp, 0, 0, SRCCOPY);

	// Set the background color of the source DC back to the original
	// color.
	dcTemp.SetBkColor(clrOldBkColor);

	// Create the inverse of the object mask.
	dcBack.BitBlt(0, 0, TempSize.cx, TempSize.cy, &dcObject, 0, 0, NOTSRCCOPY);

	// Copy the background of the main DC to the destination.
	dcMem.BitBlt(0, 0, TempSize.cx, TempSize.cy, pDC, rcDrawBMP.left, rcDrawBMP.top, SRCCOPY);

	// Mask out the places where the bitmap will be placed.
	dcMem.BitBlt(0, 0, TempSize.cx, TempSize.cy, &dcObject, 0, 0, SRCAND);

	// Mask out the transparent colored pixels on the bitmap.
	dcTemp.BitBlt(0, 0, TempSize.cx, TempSize.cy, &dcBack, 0, 0, SRCAND);

	// XOR the bitmap with the background on the destination DC.
	dcMem.BitBlt(0, 0, TempSize.cx, TempSize.cy, &dcTemp, 0, 0, SRCPAINT);

	// Copy the destination to the screen.
	pDC->StretchBlt(rcDrawBMP.left, rcDrawBMP.top, rcDrawBMP.Width(), rcDrawBMP.Height(), 
		&dcMem, 0, 0 ,szSrcBMP.cx, szSrcBMP.cy, SRCCOPY);

	// Place the original bitmap back into the bitmap sent here.
	dcTemp.BitBlt(0, 0, TempSize.cx, TempSize.cy, &dcSave, 0, 0, SRCCOPY);

	// Delete the memory bitmaps.
	CBitmap* pTempBmp = NULL;
	pTempBmp = dcBack.SelectObject(pbmBackOld);
	ASSERT(pTempBmp != NULL);
	pTempBmp->DeleteObject();
	pTempBmp = dcObject.SelectObject(pbmObjectOld);
	ASSERT(pTempBmp != NULL);
	pTempBmp->DeleteObject();
	pTempBmp = dcMem.SelectObject(pbmMemOld);
	ASSERT(pTempBmp != NULL);
	pTempBmp->DeleteObject();
	pTempBmp = dcSave.SelectObject(pbmSaveOld);
	ASSERT(pTempBmp != NULL);
	pTempBmp->DeleteObject();

	// Delete the memory DCs.
	dcMem.DeleteDC();
	dcBack.DeleteDC();
	dcObject.DeleteDC();
	dcSave.DeleteDC();
	dcTemp.DeleteDC();
	}

BOOL COXBitmapCell::SetBMPAlignment(EBMPAlignment eAlign)
	{
	ASSERT((BA_FIRST <= (int)eAlign) && ((int) eAlign <= BA_LAST));
	m_eBMPAlignment = eAlign;

	return TRUE;
	}

EBMPAlignment COXBitmapCell::GetBMPAlignment()
	{
	return m_eBMPAlignment;
	}


BOOL COXBitmapCell::SetBitmap(UINT nIDResource, COLORREF clrMask /* = CLR_NONE */)
	{
	CRect rect;
	
	m_Bitmap.DeleteObject();
	if (!m_Bitmap.LoadBitmap(nIDResource))
		{
		TRACE0("In COXBitmapCell::SetBitmap : Loadbitmap failed");
		return FALSE;
		}

	BITMAP bm;
	m_Bitmap.GetObject(sizeof(bm), &bm);
	m_Bitmap.SetBitmapDimension(bm.bmWidth,bm.bmHeight);
		
	// Set the mask color
	m_clrMask = clrMask;

	return TRUE;
	}

CSize COXBitmapCell::GetExtent(CDC* /*pDC*/, UINT /*nCellState*/) const
	{
	return m_Bitmap.GetBitmapDimension();
	}