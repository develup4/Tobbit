#pragma once
#include "CScene.h"

#define TOROSHI_CHANGE_FRAME	13
#define TOBBIT_CHANGE_FRAME		15
#define STATE_BACK_FRAME		18
#define OPENING_END_FRAME		21

class CTitle : public CScene
{
private:
	int			m_nTobbitState;
	int			m_nToroshiState;
	int			m_nFrameCount;
	int			m_aTimeCut[OPENING_END_FRAME];
	bool		m_bDrawPressEnterKey;

	HBITMAP		m_hBitmapTobbit;
	HBITMAP		m_hBitmapToroshi;
	HBITMAP		m_hBitmapTobbitTalkBallon;
	HBITMAP		m_hBitmapToroshiTalkBallon;
	HBITMAP		m_hBitmapBackground;
	HBITMAP		m_hBitmapTitle;
	HBITMAP		m_hBitmapPressEnterKey;

protected:

public:
	CTitle(HWND hWnd, HINSTANCE hInst);
	~CTitle(void);

	void		FrameMove();
	void		Render();

	void		InitScene();
};
