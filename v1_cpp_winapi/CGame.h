#pragma once
#include "CTitle.h"
#include "CStageSelect.h"
#include "CPlay.h"
#include "CEnding.h"

class CGame
{
private:
	CScene*		m_pCurrentScene;
	CScene*		m_pScene[CScene::NUM_SCENEKIND];

protected:

public:
	CGame(HWND hWnd, HINSTANCE hInst);
	~CGame(void);

	void		FrameMove();
	void		Render();
};