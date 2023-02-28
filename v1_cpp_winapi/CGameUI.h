#pragma once
#include "CHero.h"

#define ONE_MINUTE				60
#define UI_IMAGE_WIDTH			60
#define UI_IMAGE_HEIGHT			90
#define LIMIT_TIME				180
#define CARROT_IMAGE_LAST_X		950

class CGameUI :	public CGameObject
{
private:
	CHero*		m_ptrHero;
	
	int			m_nLimitTime;
	int			m_nTickCount;		// 1초 계산용

	HBITMAP		m_hBitmapCarrot;
	HBITMAP		m_hBitmapTime;

protected:

public:
	CGameUI(CHero* pHero, HINSTANCE hInst);
	~CGameUI(void);

	void		Action();
	void		Draw(HDC hDC, HDC hMemoryDC);

	void		Init();
};