#pragma once
#pragma warning(disable : 4018)
#pragma warning(disable : 4996)

// 최상위 헤더파일이므로 라이브러리 헤더 및 공통 상수 포함
#include <Windows.h>
#include <mmsystem.h>
#include <math.h>
#include <string>
#include <vector>

#define	FRAMERATE			30
#define	PIE					3.14
#define FRAME_WIDTH			113
#define FRAME_HEIGHT		190
#define WIN_WIDTH			1024
#define WIN_HEIGHT			768
#define	FIRST_FLOOR_HEIGHT	283
#define TILE_PIXEL			64
#define NUM_FLOOR			3
#define	LAND_HEIGHT			640
#define FLOOR_HEIGHT		160
#define TRANSPARNET_COLOR	RGB(95, 95, 95)

class CGameObject
{
private:
	bool					m_bEnable;

protected:
public:
	CGameObject(void);
	~CGameObject(void);

	virtual void			Action() = 0;
	virtual void			Draw(HDC hDC, HDC hMemoryDC) = 0;

	bool					GetEnable() const			{	return m_bEnable;		}
	void					SetEnable(bool bEnable)		{	m_bEnable = bEnable;	}
};