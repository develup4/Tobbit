#pragma once
#include "CScene.h"
#define CURSOR_WIDTH	354
#define CURSOR_HEIGHT	154
#define ABSOLUTE_X		130
#define ABSOLUTE_Y		294
#define CURSOR_GAP_X	400
#define CURSOR_GAP_Y	200

class CStageSelect : public CScene
{
private:
	int			m_nSelectedIndex;
	HBITMAP		m_hBitmapBackground;
	HBITMAP		m_hBitmapSelect;
	CGameMap*	m_pGameMap;

protected:

public:
	CStageSelect(HWND hWnd, HINSTANCE hInst, CGameMap* pGameMap);
	~CStageSelect(void);

	void			FrameMove();
	void			Render();

	void			InitScene();
};
