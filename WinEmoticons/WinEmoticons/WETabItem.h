#include "WEPaintUint.h"
#pragma once

class CWETabItem : public CWEPaintUint
{
	DECLARE_DYNCREATE(CWETabItem)
public:
	CWETabItem(CRect rcThis = CRect(),CWEPaintUint *pParent = NULL);
	~CWETabItem(void);

	// Attributes:
public:
	int		nIndex;
	CString	strContent;
	int		*pnItemPadding;
	// Methods:
public:
	void Draw(CDC *pDC);
	void MoveRect(CRect rcNew);
	// hit test
	CWEPaintUint *HitTest(CPoint ptHit,MouseEvent meMouse = NOTHING);

	void GetItemRect( CRect &rcThis );
	

};
