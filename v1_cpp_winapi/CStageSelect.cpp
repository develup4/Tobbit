#include "CStageSelect.h"

CStageSelect::CStageSelect(HWND hWnd, HINSTANCE hInst, CGameMap* pGameMap) : CScene(hWnd, hInst)
{
	m_nSelectedIndex	= 0;
	m_pGameMap			= pGameMap;

	TCHAR szImagePath[64];
	wsprintf(szImagePath, TEXT("Image\\UI\\StageSelect\\Background.bmp"));
	m_hBitmapBackground	= (HBITMAP)LoadImage(hInst, szImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	wsprintf(szImagePath, TEXT("Image\\UI\\StageSelect\\Select.bmp"));
	m_hBitmapSelect		= (HBITMAP)LoadImage(hInst, szImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

CStageSelect::~CStageSelect(void)
{
	DeleteObject(m_hBitmapBackground);
	DeleteObject(m_hBitmapSelect);
}

void CStageSelect::FrameMove()
{
	if (GetAsyncKeyState(VK_RETURN))
	{
		m_pGameMap->SetStage(m_nSelectedIndex + 1);
		m_pGameMap->LoadMapScript(m_hInstance);
		m_nNextScene = CScene::PLAY;
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		if (m_nSelectedIndex % 2 == 0)
		{
			m_nSelectedIndex++;
		}
	}
	else if (GetAsyncKeyState(VK_LEFT))
	{
		if (m_nSelectedIndex % 2 == 1)
		{
			m_nSelectedIndex--;
		}
	}
	else if (GetAsyncKeyState(VK_UP))
	{
		if (m_nSelectedIndex > 1)
		{
			m_nSelectedIndex -= 2;
		}
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		if (m_nSelectedIndex < 2)
		{
			m_nSelectedIndex += 2;
		}
	}
}

void CStageSelect::Render()
{
	// 그리기 준비
	m_hBitmap		= NULL;
	m_hDC			= GetDC(m_hWindow);
	GetClientRect(m_hWindow, &m_rectClient);
	m_hBitmap		= CreateCompatibleBitmap(m_hDC, m_rectClient.right, m_rectClient.bottom);
	m_hMemoryDC		= CreateCompatibleDC(m_hDC);
	m_hOldBitmap	= (HBITMAP)SelectObject(m_hMemoryDC, m_hBitmap);
	FillRect(m_hMemoryDC, &m_rectClient, GetSysColorBrush(COLOR_WINDOW));

	// 이미지 그리기
	HDC hObjectDC	= NULL;
	hObjectDC = CreateCompatibleDC(m_hDC);
	SelectObject(hObjectDC, m_hBitmapBackground);
	BitBlt(m_hMemoryDC, 0, 0, WIN_WIDTH, WIN_HEIGHT, hObjectDC, 0, 0, SRCCOPY);
	DeleteDC(hObjectDC);

	hObjectDC = CreateCompatibleDC(m_hDC);
	SelectObject(hObjectDC, m_hBitmapSelect);
	TransparentBlt(m_hMemoryDC, (m_nSelectedIndex % 2) * CURSOR_GAP_X + ABSOLUTE_X, (m_nSelectedIndex / 2) * CURSOR_GAP_Y + ABSOLUTE_Y, CURSOR_WIDTH, CURSOR_HEIGHT, hObjectDC, 0, 0, CURSOR_WIDTH, CURSOR_HEIGHT, TRANSPARNET_COLOR);
	DeleteDC(hObjectDC);

	// 더블 버퍼링
	BitBlt(m_hDC, 0, 0, m_rectClient.right, m_rectClient.bottom, m_hMemoryDC, 0, 0, SRCCOPY);

	// 그리기 도구 해제
	SelectObject(m_hMemoryDC, m_hOldBitmap);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemoryDC);
	ReleaseDC(m_hWindow, m_hDC);

	// 화면 갱신
	InvalidateRect(m_hWindow, NULL, FALSE);
}

void CStageSelect::InitScene()
{
	m_nNextScene = MAINTAIN;

	// 배경음악 재생
	PlaySound(TEXT("Sound\\BGM\\StageSelect.wav"), NULL, SND_ASYNC);
}
