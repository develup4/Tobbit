#include "CGameUI.h"

CGameUI::CGameUI(CHero* pHero, HINSTANCE hInst)
{
	m_ptrHero		= pHero;
	m_nLimitTime	= LIMIT_TIME;
	m_nTickCount	= GetTickCount();

	TCHAR szImagePath[32];
	wsprintf(szImagePath, TEXT("Image\\UI\\Carrot.bmp"));
	m_hBitmapCarrot = (HBITMAP)LoadImage(hInst, szImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	wsprintf(szImagePath, TEXT("Image\\UI\\Arabic.bmp"));
	m_hBitmapTime   = (HBITMAP)LoadImage(hInst, szImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

CGameUI::~CGameUI(void)
{
	DeleteObject(m_hBitmapCarrot);
	DeleteObject(m_hBitmapTime);
}

void CGameUI::Action()
{
	// 제한시간 감소
	int nCurrentTime = GetTickCount();

	if(nCurrentTime - m_nTickCount >= 1000)
	{
		m_nTickCount = GetTickCount();
		m_nLimitTime--;

		// 타임오버 체크
		if (m_nLimitTime < 0)
		{
			m_nLimitTime = 0;
			m_ptrHero->SetEnable(false);
		}
	}
}

void CGameUI::Draw(HDC hDC, HDC hMemoryDC)
{
	HDC hObjectDC;

	// HP 당근 그리기
	hObjectDC = CreateCompatibleDC(hDC);
	SelectObject(hObjectDC, m_hBitmapCarrot);
	for(int i = 0; i < m_ptrHero->GetHP(); i++)
	{
		TransparentBlt(hMemoryDC, CARROT_IMAGE_LAST_X - (i * UI_IMAGE_WIDTH), 0, UI_IMAGE_WIDTH, UI_IMAGE_HEIGHT, hObjectDC, 0, 0, UI_IMAGE_WIDTH, UI_IMAGE_HEIGHT, TRANSPARNET_COLOR);
	}
	DeleteDC(hObjectDC);

	// 제한시간 그리기
	hObjectDC = CreateCompatibleDC(hDC);
	SelectObject(hObjectDC, m_hBitmapTime);
	TransparentBlt(hMemoryDC, (WIN_WIDTH / 2) - 80,	45, UI_IMAGE_WIDTH, UI_IMAGE_HEIGHT, hObjectDC, (m_nLimitTime / ONE_MINUTE) * UI_IMAGE_WIDTH,		0, UI_IMAGE_WIDTH,	UI_IMAGE_HEIGHT,	TRANSPARNET_COLOR);
	TransparentBlt(hMemoryDC, (WIN_WIDTH / 2),		45, UI_IMAGE_WIDTH, UI_IMAGE_HEIGHT, hObjectDC, (m_nLimitTime % ONE_MINUTE) / 10 * UI_IMAGE_WIDTH,	0, UI_IMAGE_WIDTH,	UI_IMAGE_HEIGHT,	TRANSPARNET_COLOR);
	TransparentBlt(hMemoryDC, (WIN_WIDTH / 2) + 60,	45, UI_IMAGE_WIDTH, UI_IMAGE_HEIGHT, hObjectDC, (m_nLimitTime % 10) * UI_IMAGE_WIDTH,				0, UI_IMAGE_WIDTH,	UI_IMAGE_HEIGHT,	TRANSPARNET_COLOR);
	TransparentBlt(hMemoryDC, (WIN_WIDTH / 2) - 20,	45, 20,				90,				 hObjectDC, 600,												0, 20,				90,					TRANSPARNET_COLOR);
	DeleteDC(hObjectDC);
}

void CGameUI::Init()
{
	m_nLimitTime = LIMIT_TIME;
	m_nTickCount = GetTickCount();
}
