#include "CGameMap.h"

CGameMap::CGameMap(CHero* pHero, HINSTANCE hInst)
{
	// 멤버변수 초기화
	m_ptrHero					= pHero;
	m_nTileWidth				= 0;
	m_nStage					= 1;
	m_nForegroundImageWidth		= 0;
	m_nBackgroundImageWidth		= 0;
	m_nScrollSpeedDifference	= 3;
	
	// 최초 스테이지 로딩
	LoadMapScript(hInst);
}

CGameMap::~CGameMap(void)
{
	DeleteObject(m_hBitmapFixedBackground);
	DeleteObject(m_hBitmapForeground);
	DeleteObject(m_hBitmapBackground);
	DeleteObject(m_hBitmapLogTree);

	// 맵 오브젝트 해제
	for (int i = 0; i < m_vecItem.size(); i++)
	{
		delete m_vecItem[i];
	}
	for (int i = 0; i < m_vecMonster.size(); i++)
	{
		delete m_vecMonster[i];
	}
}

void CGameMap::Action()
{
	// 맵 오브젝트 Action
	for (int i = 0; i < m_vecItem.size(); i++)
	{
		m_vecItem[i]->Action();
	}
	for (int i = 0; i < m_vecMonster.size(); i++)
	{
		m_vecMonster[i]->Action();
	}
}

bool CGameMap::IsStageClear()
{
	// 스테이지 클리어 체크
	for (int i = 0; i < m_vecMonster.size(); i++)
	{
		if (m_vecMonster[i]->GetEnable())
		{
			return false;
		}
	}
	return true;
}

void CGameMap::Draw(HDC hDC, HDC hMemoryDC)
{
	int nLastWidth = 0;

	// 고정 배경 렌더링
	HDC hFixedBackgroundDC = CreateCompatibleDC(hDC);
	SelectObject(hFixedBackgroundDC, m_hBitmapFixedBackground);
	BitBlt(hMemoryDC, 0, 0, WIN_WIDTH, WIN_HEIGHT, hFixedBackgroundDC, 0, 0, SRCCOPY);
	DeleteDC(hFixedBackgroundDC);

	// 배경 렌더링(스크롤링)
	HDC hBackgroundDC = CreateCompatibleDC(hDC);
	SelectObject(hBackgroundDC, m_hBitmapBackground);
	nLastWidth = (m_ptrHero->GetX() / m_nScrollSpeedDifference) % m_nBackgroundImageWidth;
	TransparentBlt(hMemoryDC, 0, 0, m_nBackgroundImageWidth - nLastWidth, WIN_HEIGHT, hBackgroundDC, nLastWidth, 0, m_nBackgroundImageWidth - nLastWidth, WIN_HEIGHT, TRANSPARNET_COLOR);
	if (m_nBackgroundImageWidth - nLastWidth < WIN_WIDTH)
	{
		TransparentBlt(hMemoryDC, m_nBackgroundImageWidth - nLastWidth, 0, WIN_WIDTH - (m_nBackgroundImageWidth - nLastWidth), WIN_HEIGHT, hBackgroundDC, 0, 0, WIN_WIDTH - (m_nBackgroundImageWidth - nLastWidth), WIN_HEIGHT, TRANSPARNET_COLOR);
	}
	DeleteDC(hBackgroundDC);

	// 전경 렌더링(스크롤링)
	HDC hForegroundDC = CreateCompatibleDC(hDC);
	SelectObject(hForegroundDC, m_hBitmapForeground);
	nLastWidth = m_ptrHero->GetX() % m_nForegroundImageWidth;
	TransparentBlt(hMemoryDC, 0, 0, m_nForegroundImageWidth - nLastWidth, WIN_HEIGHT, hForegroundDC, nLastWidth, 0, m_nForegroundImageWidth - nLastWidth, WIN_HEIGHT, TRANSPARNET_COLOR);
	if (m_nForegroundImageWidth - nLastWidth < WIN_WIDTH)
	{
		TransparentBlt(hMemoryDC, m_nForegroundImageWidth - nLastWidth, 0, WIN_WIDTH - (m_nForegroundImageWidth - nLastWidth), WIN_HEIGHT, hForegroundDC, 0, 0, WIN_WIDTH - (m_nForegroundImageWidth - nLastWidth), WIN_HEIGHT, TRANSPARNET_COLOR);
	}
	DeleteDC(hForegroundDC);

	// 통나무 Draw
	for (int nFloor = 1; nFloor < NUM_FLOOR; nFloor++)
	{
		for (int nIndex = 0; nIndex < m_vecTileOnTheFloor[nFloor].size(); nIndex++)
		{
			if (m_vecTileOnTheFloor[nFloor].at(nIndex) > 0)
			{
				HDC hLogTreeDC = CreateCompatibleDC(hDC);
				SelectObject(hLogTreeDC, m_hBitmapLogTree);

				// 좌우 모서리 고려해서 타일 그리기
				if (m_vecTileOnTheFloor[nFloor].at(nIndex - 1) == 0)
				{
					TransparentBlt(hMemoryDC, nIndex * TILE_PIXEL - m_ptrHero->GetX() + WIN_WIDTH / 2, LAND_HEIGHT - nFloor * FLOOR_HEIGHT + TILE_PIXEL / 4, TILE_PIXEL, TILE_PIXEL, hLogTreeDC, 0, 0,				TILE_PIXEL, TILE_PIXEL, TRANSPARNET_COLOR);
				}
				else if(m_vecTileOnTheFloor[nFloor].at(nIndex + 1) == 0)
				{
					TransparentBlt(hMemoryDC, nIndex * TILE_PIXEL - m_ptrHero->GetX() + WIN_WIDTH / 2, LAND_HEIGHT - nFloor * FLOOR_HEIGHT + TILE_PIXEL / 4, TILE_PIXEL, TILE_PIXEL, hLogTreeDC, TILE_PIXEL * 2, 0,	TILE_PIXEL, TILE_PIXEL, TRANSPARNET_COLOR);
				}
				else
				{
					TransparentBlt(hMemoryDC, nIndex * TILE_PIXEL - m_ptrHero->GetX() + WIN_WIDTH / 2, LAND_HEIGHT - nFloor * FLOOR_HEIGHT + TILE_PIXEL / 4, TILE_PIXEL, TILE_PIXEL, hLogTreeDC, TILE_PIXEL, 0,		TILE_PIXEL, TILE_PIXEL, TRANSPARNET_COLOR);
				}
				
				DeleteDC(hLogTreeDC);
			}
		}
	}


	// 맵 오브젝트 Draw
	for (int i = 0; i < m_vecItem.size(); i++)
	{
		m_vecItem[i]->Draw(hDC, hMemoryDC);
	}
	for (int i = 0; i < m_vecMonster.size(); i++)
	{
		m_vecMonster[i]->Draw(hDC, hMemoryDC);
	}
}

bool CGameMap::LoadMapScript(HINSTANCE hInst)
{
	FILE*	pFilePointer;
	char	szPath[32];
	TCHAR	wszPath[32];

	// 컨테이너 초기화
	for (int nFloor = 0; nFloor < NUM_FLOOR; nFloor++)
	{
		m_vecTileOnTheFloor[nFloor].clear();
	}
	m_vecItem.clear();
	m_vecMonster.clear();

	// 스크립트 파일 오픈
	sprintf(szPath, "Script\\%d.tsr", m_nStage);
	pFilePointer = fopen(szPath,"r");
	if (pFilePointer == NULL)
	{
		return false;
	}

	// 몬스터 정보 로드
	int nMonsterKind = 0;
	fscanf(pFilePointer, "%d", &nMonsterKind);

	std::vector<std::wstring> vecMonsterName;
	for (int i = 0; i < nMonsterKind; i++)
	{
		TCHAR wszTemp[64];
		fwscanf(pFilePointer, TEXT("%s"), wszTemp);
		vecMonsterName.push_back(wszTemp);
	}

	// 타일 가로 길이 읽어오기
	fscanf(pFilePointer, "%d", &m_nTileWidth);

	// 타일 정보 입력
	for (int nFloor = NUM_FLOOR - 1; nFloor >= 0; nFloor--)
	{
		for (int nIndex = 0; nIndex < m_nTileWidth; nIndex++)
		{
			int nTile = 0;
			fscanf(pFilePointer, "%d", &nTile);
			if (nTile > 0)
			{
				// 타일 생성
				m_vecTileOnTheFloor[nFloor].push_back(EXIST_TILE);

				// 아이템 객체 생성
				if (nTile == ITEM_CODE)
				{
					CItem* pItem = new CItem(m_ptrHero, hInst, nIndex * TILE_PIXEL, nFloor);
					m_vecItem.push_back(pItem);
				}

				// 몬스터 객체 생성
				if (nTile > ITEM_CODE)
				{
					wsprintf(wszPath, TEXT("Monster\\%s"), vecMonsterName[nTile - ITEM_CODE - 1].c_str());
					CMonster* pMonster = new CMonster(hInst, nIndex * TILE_PIXEL, 3 + rand() % 5, 100, nFloor, wszPath, vecMonsterName[nTile - ITEM_CODE - 1], m_ptrHero);
					m_vecMonster.push_back(pMonster);
				}
			}
			else
			{
				m_vecTileOnTheFloor[nFloor].push_back(EMPTY_TILE);
			}
		}
	}

	// 캐릭터들에게 맵의 정보 전달
	m_ptrHero->SetMapInfo(m_vecTileOnTheFloor);
	for (int nFloor = 0; nFloor < m_vecMonster.size(); nFloor++)
	{
		m_vecMonster[nFloor]->SetMapInfo(m_vecTileOnTheFloor);
	}

	// 파일 클로즈
	fclose(pFilePointer);
	
	// 배경 이미지 로드
	wsprintf(wszPath, TEXT("Image\\Map\\%d\\Fixed.bmp"), m_nStage);
	m_hBitmapFixedBackground	= (HBITMAP)LoadImage(hInst, wszPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	wsprintf(wszPath, TEXT("Image\\Map\\%d\\Foreground.bmp"), m_nStage);
	m_hBitmapForeground			= (HBITMAP)LoadImage(hInst, wszPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	wsprintf(wszPath, TEXT("Image\\Map\\%d\\Background.bmp"), m_nStage);
	m_hBitmapBackground			= (HBITMAP)LoadImage(hInst, wszPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	wsprintf(wszPath, TEXT("Image\\Map\\%d\\LogTree.bmp"), m_nStage);
	m_hBitmapLogTree			= (HBITMAP)LoadImage(hInst, wszPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	// 배경 이미지 크기 알아내기
	BITMAP Bitmap;
	GetObject(m_hBitmapForeground, sizeof(BITMAP), &Bitmap);
	m_nForegroundImageWidth = Bitmap.bmWidth;
	GetObject(m_hBitmapBackground, sizeof(BITMAP), &Bitmap);
	m_nBackgroundImageWidth = Bitmap.bmWidth;

	return true;
}