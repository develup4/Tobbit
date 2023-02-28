#include "CGame.h"

CGame::CGame(HWND hWnd, HINSTANCE hInst)
{
	m_pScene[CScene::TITLE]			= new CTitle(hWnd, hInst);
	m_pScene[CScene::PLAY]			= new CPlay(hWnd, hInst);
	m_pScene[CScene::STAGE_SELECT]	= new CStageSelect(hWnd, hInst, ((CPlay*)m_pScene[CScene::PLAY])->GetGameMapPointer());
	m_pScene[CScene::ENDING]		= new CEnding(hWnd, hInst);

	// �ϴ� ù ���� Ÿ��Ʋ ȭ��
	m_pCurrentScene = m_pScene[CScene::TITLE];
	m_pCurrentScene->InitScene();
}

CGame::~CGame(void)
{
	for (int i = 0; i < CScene::NUM_SCENEKIND; i++)
	{
		delete m_pScene[i];
	}
}

void CGame::FrameMove()
{
	// �� ��ȭ üũ �� ����
	if (m_pCurrentScene->GetNextScene() != CScene::MAINTAIN)
	{
		m_pCurrentScene = m_pScene[m_pCurrentScene->GetNextScene()];
		m_pCurrentScene->InitScene();
	}

	m_pCurrentScene->FrameMove();
}

void CGame::Render()
{
	m_pCurrentScene->Render();
}