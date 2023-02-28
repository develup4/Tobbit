#pragma once
#include "CGameObject.h"
#include "CGameMap.h"

class CScene
{
private:

protected:
	int				m_nNextScene;

	// ������ �ڵ� ����
	HWND			m_hWindow;
	HINSTANCE		m_hInstance;

	// �׸��� ���� ����
	RECT			m_rectClient;
	HDC				m_hDC;
	HDC				m_hMemoryDC;
	HBITMAP			m_hBitmap;
	HBITMAP			m_hOldBitmap;

public:
	enum{
					TITLE,
					STAGE_SELECT,
					PLAY,
					ENDING,
					NUM_SCENEKIND,
					MAINTAIN
		};

	CScene(HWND hWnd, HINSTANCE hInst);
	~CScene(void);

	virtual void	FrameMove();
	virtual void	Render();

	virtual void	InitScene();
	int				GetNextScene();
};