#pragma once
#include "CItem.h"
#include "CMonster.h"

#define EMPTY_TILE		0
#define EXIST_TILE		1
#define ITEM_CODE		2

class CGameMap : public CGameObject
{
private:
	CHero*						m_ptrHero;							// 주인공 객체 포인터

	std::vector<int>			m_vecTileOnTheFloor[NUM_FLOOR];		// 타일맵 배열
	int							m_nTileWidth;						// 타일 가로길이
	int							m_nStage;							// 스테이지 번호

	int							m_nForegroundImageWidth;			// 전경 이미지 너비
	int							m_nBackgroundImageWidth;			// 배경 이미지 너비
	int							m_nScrollSpeedDifference;			// 스크롤 속도차

	HBITMAP						m_hBitmapFixedBackground;			// 고정 배경 비트맵 핸들러
	HBITMAP						m_hBitmapBackground;				// 배경 비트맵 핸들러
	HBITMAP						m_hBitmapForeground;				// 전경 비트맵 핸들러
	HBITMAP						m_hBitmapLogTree;					// 통나무 비트맵 핸들러

	std::vector<CItem*>			m_vecItem;							// 아이템 객체 컨테이너
	std::vector<CMonster*>		m_vecMonster;						// 몬스터 객체 컨테이너
	
protected:

public:
	CGameMap(CHero* pHero, HINSTANCE hInst);
	~CGameMap(void);
	
	void						Action();
	void						Draw(HDC hDC, HDC hMemoryDC);

	bool						LoadMapScript(HINSTANCE hInst);
	bool						IsStageClear();
	
	void						SetStage(int nStage)				{	m_nStage = nStage;		}
	int							GetStage() const					{	return m_nStage;		}
};