#pragma once
#include "CScene.h"

class CEnding : public CScene
{
private:
	HBITMAP		m_hBitmapEnding;
	int			m_nMusicStartTick;

protected:

public:
	CEnding(HWND hWnd, HINSTANCE hInst);
	~CEnding(void);

	void		FrameMove();
	void		Render();

	void		InitScene();
};
