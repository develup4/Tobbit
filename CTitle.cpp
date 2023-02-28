#include "CTitle.h"

CTitle::CTitle(HWND hWnd, HINSTANCE hInst) : CScene(hWnd, hInst)
{
	m_nTobbitState			= 0;
	m_nToroshiState			= 0;
	m_nFrameCount			= 0;
	m_bDrawPressEnterKey	= true;

	// ������ ���� ���� Ÿ��
	m_aTimeCut[0] = 2400;
	m_aTimeCut[1] = 2300;
	m_aTimeCut[2] = 1170;
	for (int i = 3; i < OPENING_END_FRAME; i++)
	{
		m_aTimeCut[i] = 850;
	}
	m_aTimeCut[19] = 350;

	TCHAR szImagePath[64];
	wsprintf(szImagePath, TEXT("Image\\UI\\Title\\Tobbit.bmp"));
	m_hBitmapTobbit				= (HBITMAP)LoadImage(hInst, szImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	wsprintf(szImagePath, TEXT("Image\\UI\\Title\\Toroshi.bmp"));
	m_hBitmapToroshi			= (HBITMAP)LoadImage(hInst, szImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	wsprintf(szImagePath, TEXT("Image\\UI\\Title\\TobbitTalkBallon.bmp"));
	m_hBitmapTobbitTalkBallon	= (HBITMAP)LoadImage(hInst, szImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	wsprintf(szImagePath, TEXT("Image\\UI\\Title\\ToroshiTalkBallon.bmp"));
	m_hBitmapToroshiTalkBallon	= (HBITMAP)LoadImage(hInst, szImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	wsprintf(szImagePath, TEXT("Image\\UI\\Title\\Background.bmp"));
	m_hBitmapBackground			= (HBITMAP)LoadImage(hInst, szImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	wsprintf(szImagePath, TEXT("Image\\UI\\Title\\Title.bmp"));
	m_hBitmapTitle				= (HBITMAP)LoadImage(hInst, szImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	wsprintf(szImagePath, TEXT("Image\\UI\\Title\\PressEnterKey.bmp"));
	m_hBitmapPressEnterKey		= (HBITMAP)LoadImage(hInst, szImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

CTitle::~CTitle(void)
{
	DeleteObject(m_hBitmapTobbit);
	DeleteObject(m_hBitmapToroshi);
	DeleteObject(m_hBitmapTobbitTalkBallon);
	DeleteObject(m_hBitmapToroshiTalkBallon);
	DeleteObject(m_hBitmapBackground);
	DeleteObject(m_hBitmapTitle);
	DeleteObject(m_hBitmapPressEnterKey);
}

void CTitle::FrameMove()
{
	if (m_nFrameCount < OPENING_END_FRAME)
	{
		m_nFrameCount++;
	}

	// ĳ���� ǥ�� ��ȭ
	if (m_nFrameCount == TOBBIT_CHANGE_FRAME)
	{
		m_nTobbitState++;
	}
	if (m_nFrameCount == TOROSHI_CHANGE_FRAME)
	{
		m_nToroshiState++;
	}
	if (m_nFrameCount == STATE_BACK_FRAME)
	{
		m_nTobbitState--;
		m_nToroshiState--;
	}

	// ����Ű �Է� üũ
	if (GetAsyncKeyState(VK_RETURN))
	{
		m_nNextScene = CScene::STAGE_SELECT;
	}

	if (m_nFrameCount >= OPENING_END_FRAME)
	{
		// Press Enter Key ���� ����
		if (m_bDrawPressEnterKey)
		{
			m_bDrawPressEnterKey = false;
		}
		else
		{
			m_bDrawPressEnterKey = true;
		}
	}
}

void CTitle::Render()
{
	// �׸��� �غ�
	m_hBitmap		= NULL;
	m_hDC			= GetDC(m_hWindow);
	GetClientRect(m_hWindow, &m_rectClient);
	m_hBitmap		= CreateCompatibleBitmap(m_hDC, m_rectClient.right, m_rectClient.bottom);
	m_hMemoryDC		= CreateCompatibleDC(m_hDC);
	m_hOldBitmap	= (HBITMAP)SelectObject(m_hMemoryDC, m_hBitmap);
	FillRect(m_hMemoryDC, &m_rectClient, GetSysColorBrush(COLOR_WINDOW));

	HDC hObjectDC;

	if (m_nFrameCount < OPENING_END_FRAME)
	{
		if (m_nFrameCount > 1)
		{
			// ��׶��� �׸���
			hObjectDC = CreateCompatibleDC(m_hDC);
			SelectObject(hObjectDC, m_hBitmapBackground);
			BitBlt(m_hMemoryDC, 0, 0, WIN_WIDTH, WIN_HEIGHT, hObjectDC, 0, 0, SRCCOPY);
			DeleteDC(hObjectDC);
		}

		if (m_nFrameCount > 2)
		{
			// ���
			hObjectDC = CreateCompatibleDC(m_hDC);
			SelectObject(hObjectDC, m_hBitmapTobbit);
			TransparentBlt(m_hMemoryDC, 100, 300, 180, 380, hObjectDC, m_nTobbitState * 180, 0, 180, 380, TRANSPARNET_COLOR);
			DeleteDC(hObjectDC);

			//��ν�
			hObjectDC = CreateCompatibleDC(m_hDC);
			SelectObject(hObjectDC, m_hBitmapToroshi);
			TransparentBlt(m_hMemoryDC, 730, 300, 180, 380, hObjectDC, m_nToroshiState * 180, 0, 180, 380, TRANSPARNET_COLOR);
			DeleteDC(hObjectDC);
		}

		if (m_nFrameCount > 3)
		{
			// ��� ��ǳ��
			hObjectDC = CreateCompatibleDC(m_hDC);
			SelectObject(hObjectDC, m_hBitmapTobbitTalkBallon);	
			TransparentBlt(m_hMemoryDC, 280, 320, 210, 180, hObjectDC, 210 * (m_nFrameCount - 4), 0, 210, 180, TRANSPARNET_COLOR);
			DeleteDC(hObjectDC);

			// ��ν� ��ǳ��
			hObjectDC = CreateCompatibleDC(m_hDC);
			SelectObject(hObjectDC, m_hBitmapToroshiTalkBallon);
			TransparentBlt(m_hMemoryDC, 500, 400, 210, 180, hObjectDC, 210 * (m_nFrameCount - 4), 0, 210, 180, TRANSPARNET_COLOR);
			Sleep(1500);
			DeleteDC(hObjectDC);
		}
	}
	else
	{
		// ��׶��� �׸���
		hObjectDC = CreateCompatibleDC(m_hDC);
		SelectObject(hObjectDC, m_hBitmapBackground);
		BitBlt(m_hMemoryDC, 0, 0, WIN_WIDTH, WIN_HEIGHT, hObjectDC, 0, 0, SRCCOPY);
		DeleteDC(hObjectDC);

		//������ �ΰ�
		hObjectDC = CreateCompatibleDC(m_hDC);
		SelectObject(hObjectDC, m_hBitmapTitle);
		BitBlt(m_hMemoryDC, 206, 170, 600, 341, hObjectDC, 0, 0, SRCCOPY);
		DeleteDC(hObjectDC);

		// Press enter key(��������)
		if (m_bDrawPressEnterKey)
		{
			hObjectDC = CreateCompatibleDC(m_hDC);
			SelectObject(hObjectDC, m_hBitmapPressEnterKey);
			BitBlt(m_hMemoryDC, 387, 570, 250, 30, hObjectDC, 0, 0, SRCCOPY);
			DeleteDC(hObjectDC);
		}
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

	// �ð�����
	Sleep(m_aTimeCut[m_nFrameCount - 1]);
}

void CTitle::InitScene()
{
	m_nNextScene = MAINTAIN;

	// ������� ���
	PlaySound(TEXT("Sound\\BGM\\Title.wav"), NULL, SND_ASYNC);
}
