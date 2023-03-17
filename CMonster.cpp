#include "CMonster.h"

CMonster::CMonster(HINSTANCE hInst, int nX, int nSpeed, int nJumpHeight, int nFloor, std::wstring strImageDirectory, std::wstring strWord, CHero* ptrHero) : CCharacter(nX, nSpeed, nJumpHeight, nFloor, strImageDirectory)
{
	// 액션 객체 생성							<NumAction>	<NumFrame>
	m_aAction[RIGHT_MOVE]	= new CRightMove(this,	8,			4,		hInst, ptrHero);
	m_aAction[LEFT_MOVE]	= new CLeftMove	(this,	8,			4,		hInst, ptrHero);
	m_aAction[RIGHT_IDLE]	= new CRightIdle(this,	24,			8,		hInst, ptrHero);
	m_aAction[LEFT_IDLE]	= new CLeftIdle	(this,	24,			8,		hInst, ptrHero);
	m_aAction[RIGHT_DIE]	= new CRightDie	(this,	60,			1,		hInst, ptrHero);
	m_aAction[LEFT_DIE]		= new CLeftDie	(this,	60,			1,		hInst, ptrHero);

	m_pActionDicider		= new CCowardly(ptrHero, &m_nX, nFloor, strWord);
	m_pActionState			= m_aAction[RIGHT_IDLE];
	m_nCurrentAction		= RIGHT_IDLE;

	m_strWord				= strWord;
	m_ptrHero				= ptrHero;

	// 알파벳 이미지
	TCHAR szImagePath[32];
	wsprintf(szImagePath, TEXT("Image\\UI\\Alphabet.bmp"));
	m_hBitmapAlphabet		= (HBITMAP)LoadImage(hInst, szImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

CMonster::~CMonster(void)
{
	DeleteObject(m_hBitmapAlphabet);
	delete m_pActionDicider;
}

void CMonster::Action()
{
	if (GetEnable())
	{
		m_pActionState->Action();
	}
}

void CMonster::Draw(HDC hDC, HDC hMemoryDC)
{
	if (GetEnable())
	{
		m_pActionState->Draw(hDC, hMemoryDC);

		// 죽었을때 처리
		if ((GetCurrentAction() == RIGHT_DIE || GetCurrentAction() == LEFT_DIE))
		{
			// 스펠링 출력
			for (int i = 0; i < m_strWord.size(); i++)
			{
				HDC hObjectDC = CreateCompatibleDC(hDC);
				SelectObject(hObjectDC, m_hBitmapAlphabet);
				TransparentBlt(hMemoryDC, m_nX - (ALPABET_FRAME_LENGTH - 20) * m_strWord.size() / 2 + i * (ALPABET_FRAME_LENGTH - 20) - m_ptrHero->GetX() + WIN_WIDTH / 2, m_nY - 50, ALPABET_FRAME_LENGTH, ALPABET_FRAME_LENGTH, hObjectDC, (m_strWord.at(i) - 'A') * ALPABET_FRAME_LENGTH, 0, ALPABET_FRAME_LENGTH, ALPABET_FRAME_LENGTH, TRANSPARNET_COLOR);
				DeleteDC(hObjectDC);
			}
		}
	}
}
