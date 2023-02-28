#include "CItem.h"

CItem::CItem(CHero* pHero, HINSTANCE hInst, int nX, int nFloor)
{
	TCHAR szImagePath[32];
	wsprintf(szImagePath, TEXT("Image\\UI\\Carrot.bmp"));
	m_hBitmapCarrot = (HBITMAP)LoadImage(hInst, szImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	m_ptrHero	= pHero;
	m_nX		= nX;
	m_nFloor	= nFloor;
}

CItem::~CItem(void)
{
	DeleteObject(m_hBitmapCarrot);
}

void CItem::Action()
{
	// 활성화 상태에서만 작동
	if (GetEnable() == false)
	{
		return;
	}

	if (m_ptrHero->GetFloor() == m_nFloor)
	{
		if (abs(m_ptrHero->GetX() - m_nX) < CARROT_WIDTH / 2)
		{
			if (abs(m_ptrHero->GetY() - (LAND_HEIGHT - m_nFloor * FLOOR_HEIGHT)) < FRAME_HEIGHT)
			{
				m_ptrHero->IncreaseHP();
				SetEnable(false);
			}
		}
	}
}

void CItem::Draw(HDC hDC, HDC hMemoryDC)
{
	// 활성화 상태에서만 작동
	if (GetEnable() == false)
	{
		return;
	}

	HDC hObjectDC = CreateCompatibleDC(hDC);
	SelectObject(hObjectDC, m_hBitmapCarrot);
	TransparentBlt(hMemoryDC, m_nX - m_ptrHero->GetX() + WIN_WIDTH / 2, LAND_HEIGHT - m_nFloor * FLOOR_HEIGHT - CARROT_HEIGHT / 2, CARROT_WIDTH, CARROT_HEIGHT, hObjectDC, 0, 0, CARROT_WIDTH, CARROT_HEIGHT, TRANSPARNET_COLOR);
	DeleteDC(hObjectDC);
}