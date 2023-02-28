#include "CEnding.h"

CEnding::CEnding(HWND hWnd, HINSTANCE hInst) : CScene(hWnd, hInst)
{
	TCHAR szImagePath[64];
	wsprintf(szImagePath, TEXT("Image\\UI\\Ending\\Ending.bmp"));
	m_hBitmapEnding	= (HBITMAP)LoadImage(hInst, szImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

CEnding::~CEnding(void)
{
	DeleteObject(m_hBitmapEnding);
}

void CEnding::FrameMove()
{
	if (GetTickCount() > m_nMusicStartTick + 115000)
	{
		PlaySound(NULL, NULL, SND_PURGE | SND_NOWAIT | SND_ASYNC);
		PostQuitMessage(0);
	}
}

void CEnding::Render()
{
	// �׸��� �غ�
	m_hBitmap		= NULL;
	m_hDC			= GetDC(m_hWindow);
	GetClientRect(m_hWindow, &m_rectClient);
	m_hBitmap		= CreateCompatibleBitmap(m_hDC, m_rectClient.right, m_rectClient.bottom);
	m_hMemoryDC		= CreateCompatibleDC(m_hDC);
	m_hOldBitmap	= (HBITMAP)SelectObject(m_hMemoryDC, m_hBitmap);
	FillRect(m_hMemoryDC, &m_rectClient, GetSysColorBrush(COLOR_WINDOW));

	// �̹��� �׸���
	HDC hObjectDC = CreateCompatibleDC(m_hDC);
	SelectObject(hObjectDC, m_hBitmapEnding);
	BitBlt(m_hMemoryDC, 0, 0, WIN_WIDTH, WIN_HEIGHT, hObjectDC, 0, 0, SRCCOPY);
	DeleteDC(hObjectDC);

	// ���� ���۸�
	BitBlt(m_hDC, 0, 0, m_rectClient.right, m_rectClient.bottom, m_hMemoryDC, 0, 0, SRCCOPY);

	// �׸��� ���� ����
	SelectObject(m_hMemoryDC, m_hOldBitmap);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemoryDC);
	ReleaseDC(m_hWindow, m_hDC);

	// ȭ�� ����
	InvalidateRect(m_hWindow, NULL, FALSE);
}

void CEnding::InitScene()
{
	// �뷡 ����� �ð�
	m_nMusicStartTick = GetTickCount();

	// ������� ���
	PlaySound(TEXT("Sound\\BGM\\Ending.wav"), NULL, SND_ASYNC);

	m_nNextScene = MAINTAIN;
}
