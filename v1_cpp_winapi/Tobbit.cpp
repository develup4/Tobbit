#include "CGame.h"

void				FPSFreeze();
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	// ������ ���� ����
	HWND					hWnd;
	WNDCLASS				WndClass;
	LPCTSTR					lpszWinName	= TEXT("��� : ����� ����");
	HINSTANCE				hInstance	= NULL;

	// ������ ���� ����
	hInstance				= hInst;
	WndClass.cbClsExtra		= 0;
	WndClass.cbWndExtra		= 0;
	WndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance		= hInst;
	WndClass.lpfnWndProc	= WndProc;
	WndClass.lpszClassName	= lpszWinName;
	WndClass.lpszMenuName	= NULL;
	WndClass.style			= CS_HREDRAW | CS_VREDRAW;

	// ������ ����
	RegisterClass(&WndClass);
	hWnd = CreateWindow(lpszWinName, lpszWinName, WS_CAPTION | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, WIN_WIDTH, WIN_HEIGHT, NULL, (HMENU)NULL, hInst, NULL);
	ShowWindow(hWnd, nCmdShow);

	// ���� Ŭ���� ����
	CGame*	pGame		= new CGame(hWnd, hInstance);
	bool	bRunning	= true;

	// �޽��� ����
	while(bRunning)
	{ 
		MSG msg;
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// FPS ����
			FPSFreeze();

			// ���� �õ� ��ȭ
			srand(GetTickCount());

			// ���� ����
			pGame->FrameMove();
			pGame->Render();
		}
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch(iMessage)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);

			return 0;
		}
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void FPSFreeze()
{
	static int	nOldTime	= GetTickCount();
	int			nNowTime	= GetTickCount();
	double		dDeltaTime	= nNowTime - nOldTime;

	while(dDeltaTime < 1000 / FRAMERATE)
	{
		nNowTime	= GetTickCount();
		dDeltaTime	= nNowTime - nOldTime;
	}
	nOldTime = nNowTime;
}