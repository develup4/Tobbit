#include "CPlay.h"

CPlay::CPlay(HWND hWnd, HINSTANCE hInst) : CScene(hWnd, hInst)
{
	// 멤버변수 초기화
	m_nEndImageIndex = 0;

	// 이미지 로딩
	TCHAR szImagePath[32];
	wsprintf(szImagePath, TEXT("Image\\UI\\GameOver.bmp"));
	m_hBitmapGameOver	= (HBITMAP)LoadImage(hInst, szImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	wsprintf(szImagePath, TEXT("Image\\UI\\StageClear.bmp"));
	m_hBitmapStageClear = (HBITMAP)LoadImage(hInst, szImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	// 게임 객체 생성
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

	// 스테이지 클리어
	if (m_pGameMap->IsStageClear())
	{
		m_nEndImageIndex += 10;

		if (m_nEndImageIndex > END_IMAGE_WIDTH + 600)
		{
			// 초기화
			m_pGameUI->Init();
			m_pHero->Init();

			m_nNextScene = CScene::STAGE_SELECT;

			// 이전 배경음악 중단
			TCHAR	wszPath[32];
			wsprintf(wszPath, TEXT("stop Sound\\BGM\\%d.mp3"), m_pGameMap->GetStage());
			mciSendString(wszPath, NULL, 0, NULL);
		}
	}

	// 게임오버
	if (m_pHero->GetEnable() == false)
	{
		m_nEndImageIndex += 10;

		if (m_nEndImageIndex > END_IMAGE_WIDTH + 600)
		{
			m_nNextScene = CScene::ENDING;

			// 이전 배경음악 중단
			TCHAR	wszPath[32];
			wsprintf(wszPath, TEXT("stop Sound\\BGM\\%d.mp3"), m_pGameMap->GetStage());
			mciSendString(wszPath, NULL, 0, NULL);
		}
	}
}

void CPlay::Render()
{
	// 그리기 준비
	m_hBitmap		= NULL;
	m_hDC			= GetDC(m_hWindow);
	GetClientRect(m_hWindow, &m_rectClient);
	m_hBitmap		= CreateCompatibleBitmap(m_hDC, m_rectClient.right, m_rectClient.bottom);
	m_hMemoryDC		= CreateCompatibleDC(m_hDC);
	m_hOldBitmap	= (HBITMAP)SelectObject(m_hMemoryDC, m_hBitmap);
	FillRect(m_hMemoryDC, &m_rectClient, GetSysColorBrush(COLOR_WINDOW));

	// 개별 객체 렌더링
	m_pGameMap->Draw(m_hDC, m_hMemoryDC);
	m_pHero->Draw(m_hDC, m_hMemoryDC);
	m_pGameUI->Draw(m_hDC, m_hMemoryDC);

	// 스테이지 클리어 체크
	if (m_pGameMap->IsStageClear())
	{
		HDC hObjectDC = CreateCompatibleDC(m_hDC);
		SelectObject(hObjectDC, m_hBitmapStageClear);
		TransparentBlt(m_hMemoryDC, 110, 200, END_IMAGE_WIDTH, END_IMAGE_HEIGHT, hObjectDC, 0, 0, m_nEndImageIndex > END_IMAGE_WIDTH ? END_IMAGE_WIDTH : m_nEndImageIndex, END_IMAGE_HEIGHT, TRANSPARNET_COLOR);
		DeleteDC(hObjectDC);
	}

	// 게임오버 이미지 출력
	if (m_pHero->GetEnable() == false)
	{
		HDC hObjectDC = CreateCompatibleDC(m_hDC);
		SelectObject(hObjectDC, m_hBitmapGameOver);
		TransparentBlt(m_hMemoryDC, 110, 200, END_IMAGE_WIDTH, END_IMAGE_HEIGHT, hObjectDC, 0, 0, m_nEndImageIndex > END_IMAGE_WIDTH ? END_IMAGE_WIDTH : m_nEndImageIndex, END_IMAGE_HEIGHT, TRANSPARNET_COLOR);
		DeleteDC(hObjectDC);
	}

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

void CPlay::InitScene()
{
	m_nNextScene = MAINTAIN;

	// 이전 배경음악 중단
	PlaySound(NULL, NULL, SND_PURGE | SND_NOWAIT | SND_ASYNC);

	// 배경음악 재생
	TCHAR	wszPath[32];
	wsprintf(wszPath, TEXT("play Sound\\BGM\\%d.mp3"), m_pGameMap->GetStage());
	mciSendString(wszPath, NULL, 0, NULL);
}