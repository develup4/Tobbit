#pragma once
#include "CScene.h"
#include "CGameUI.h"

#define END_IMAGE_WIDTH	803
#define END_IMAGE_HEIGHT	149

class CPlay : public CScene
{
private:
	int				m_nEndImageIndex;
	HBITMAP			m_hBitmapGameOver;
	HBITMAP			m_hBitmapStageClear;

	// Game Objects
	CHero*			m_pHero;
	CGameUI*		m_pGameUI;
	CGameMap*		m_pGameMap;

protected:

public:
	CPlay(HWND hWnd, HINSTANCE hInst);
	~CPlay(void);

	void			FrameMove();
	void			Render();

	CGameMap*		GetGameMapPointer()		{	return m_pGameMap;		}
	void			InitScene();
};