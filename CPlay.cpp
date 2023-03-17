#include "CPlay.h"

CPlay::CPlay(HWND hWnd, HINSTANCE hInst) : CScene(hWnd, hInst)
{
	// ������� �ʱ�ȭ
	m_nEndImageIndex = 0;

	// �̹��� �ε�
	TCHAR szImagePath[32];
	wsprintf(szImagePath, TEXT("Image\\UI\\GameOver.bmp"));
	m_hBitmapGameOver	= (HBITMAP)LoadImage(hInst, szImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	wsprintf(szImagePath, TEXT("Image\\UI\\StageClear.bmp"));
	m_hBitmapStageClear = (HBITMAP)LoadImage(hInst, szImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	// ���� ��ü ����
	m_pHero		= new CHero(hInst, 0, 20, 200, 0, MAX_HP, TEXT("Hero"));
	m_pGameMap	= new CGameMap(m_pHero, hInst);
	m_pGameUI	= new CGameUI(m_pHero, hInst);
}

CPlay::~CPlay(void)
{
	delete m_pGameUI;
	delete m_pHero;
	delete m_pGameMap;
	
	DeleteObject(m_hBitmapGameOver);
	DeleteObject(m_hBitmapStageClear);
}

void CPlay::FrameMove()
{
	m_pGameMap->Action();
	m_pHero->Action();
	m_pGameUI->Action();

	// �������� Ŭ����
	if (m_pGameMap->IsStageClear())
	{
		m_nEndImageIndex += 10;

		if (m_nEndImageIndex > END_IMAGE_WIDTH + 600)
		{
			// �ʱ�ȭ
			m_pGameUI->Init();
			m_pHero->Init();

			m_nNextScene = CScene::STAGE_SELECT;

			// ���� ������� �ߴ�
			TCHAR	wszPath[32];
			wsprintf(wszPath, TEXT("stop Sound\\BGM\\%d.mp3"), m_pGameMap->GetStage());
			mciSendString(wszPath, NULL, 0, NULL);
		}
	}

	// ���ӿ���
	if (m_pHero->GetEnable() == false)
	{
		m_nEndImageIndex += 10;

		if (m_nEndImageIndex > END_IMAGE_WIDTH + 600)
		{
			m_nNextScene = CScene::ENDING;

			// ���� ������� �ߴ�
			TCHAR	wszPath[32];
			wsprintf(wszPath, TEXT("stop Sound\\BGM\\%d.mp3"), m_pGameMap->GetStage());
			mciSendString(wszPath, NULL, 0, NULL);
		}
	}
}

void CPlay::Render()
{
	// �׸��� �غ�
	m_hBitmap		= NULL;
	m_hDC			= GetDC(m_hWindow);
	GetClientRect(m_hWindow, &m_rectClient);
	m_hBitmap		= CreateCompatibleBitmap(m_hDC, m_rectClient.right, m_rectClient.bottom);
	m_hMemoryDC		= CreateCompatibleDC(m_hDC);
	m_hOldBitmap	= (HBITMAP)SelectObject(m_hMemoryDC, m_hBitmap);
	FillRect(m_hMemoryDC, &m_rectClient, GetSysColorBrush(COLOR_WINDOW));

	// ���� ��ü ������
	m_pGameMap->Draw(m_hDC, m_hMemoryDC);
	m_pHero->Draw(m_hDC, m_hMemoryDC);
	m_pGameUI->Draw(m_hDC, m_hMemoryDC);

	// �������� Ŭ���� üũ
	if (m_pGameMap->IsStageClear())
	{
		HDC hObjectDC = CreateCompatibleDC(m_hDC);
		SelectObject(hObjectDC, m_hBitmapStageClear);
		TransparentBlt(m_hMemoryDC, 110, 200, END_IMAGE_WIDTH, END_IMAGE_HEIGHT, hObjectDC, 0, 0, m_nEndImageIndex > END_IMAGE_WIDTH ? END_IMAGE_WIDTH : m_nEndImageIndex, END_IMAGE_HEIGHT, TRANSPARNET_COLOR);
		DeleteDC(hObjectDC);
	}

	// ���ӿ��� �̹��� ���
	if (m_pHero->GetEnable() == false)
	{
		HDC hObjectDC = CreateCompatibleDC(m_hDC);
		SelectObject(hObjectDC, m_hBitmapGameOver);
		TransparentBlt(m_hMemoryDC, 110, 200, END_IMAGE_WIDTH, END_IMAGE_HEIGHT, hObjectDC, 0, 0, m_nEndImageIndex > END_IMAGE_WIDTH ? END_IMAGE_WIDTH : m_nEndImageIndex, END_IMAGE_HEIGHT, TRANSPARNET_COLOR);
		DeleteDC(hObjectDC);
	}

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

void CPlay::InitScene()
{
	m_nNextScene = MAINTAIN;

	// ���� ������� �ߴ�
	PlaySound(NULL, NULL, SND_PURGE | SND_NOWAIT | SND_ASYNC);

	// ������� ���
	TCHAR	wszPath[32];
	wsprintf(wszPath, TEXT("play Sound\\BGM\\%d.mp3"), m_pGameMap->GetStage());
	mciSendString(wszPath, NULL, 0, NULL);
}