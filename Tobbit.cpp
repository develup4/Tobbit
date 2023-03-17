#include "CGame.h"

void				FPSFreeze();
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	// 윈도우 관련 변수
	HWND					hWnd;
	WNDCLASS				WndClass;
	LPCTSTR					lpszWinName	= TEXT("토빗 : 뜻밖의 여정");
	HINSTANCE				hInstance	= NULL;

	// 윈도우 설정 세팅
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

	// 윈도우 생성
	RegisterClass(&WndClass);
	hWnd = CreateWindow(lpszWinName, lpszWinName, WS_CAPTION | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, WIN_WIDTH, WIN_HEIGHT, NULL, (HMENU)NULL, hInst, NULL);
	ShowWindow(hWnd, nCmdShow);

	// 게임 클래스 생성
	CGame*	pGame		= new CGame(hWnd, hInstance);
	bool	bRunning	= true;

	// 메시지 루프
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
			// FPS 고정
			FPSFreeze();

			// 랜덤 시드 변화
			srand(GetTickCount());

			// 게임 루프
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