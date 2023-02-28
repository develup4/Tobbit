#pragma once
#include "CHero.h"
#define CARROT_WIDTH	60
#define	CARROT_HEIGHT	90

class CItem : public CGameObject
{
private:
	CHero*		m_ptrHero;
	int			m_nX;
	int			m_nFloor;
	HBITMAP		m_hBitmapCarrot;

protected:

public:
	CItem(CHero* pHero, HINSTANCE hInst, int nX, int nFloor);
	~CItem(void);

	void		Action();
	void		Draw(HDC hDC, HDC hMemoryDC);
};