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

// �������� ó���� �ִٸ� �����غ��� �͵� ���� �� ����
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