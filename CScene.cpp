#include "CScene.h"

CScene::CScene(HWND hWnd, HINSTANCE hInst)
{
	m_nNextScene	= MAINTAIN;
	m_hWindow		= hWnd;
	m_hInstance		= hInst;
}

CScene::~CScene(void)
{

}

// 공통적인 처리가 있다면 구현해보는 것도 좋을 것 같다
void CScene::FrameMove()
{

}

void CScene::Render()
{

}

void CScene::InitScene()
{

}

int CScene::GetNextScene()
{
	return m_nNextScene;
}