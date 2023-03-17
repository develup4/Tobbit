#include "CCharacter.h"

CCharacter::CCharacter(int nX, int nSpeed, int nJumpHeight, int nFloor, std::wstring strImageDirectory)
{
	m_nX				= nX;
	m_nY				= LAND_HEIGHT - nFloor * FLOOR_HEIGHT - FRAME_HEIGHT + 40;	// �̹��� ���鶧���� ����
	m_nFloor			= nFloor;
	m_nSpeed			= nSpeed;
	m_nFrameCount		= 0;
	m_nActionCount		= 0;
	m_nJumpHeight		= nJumpHeight;
	m_nJumpStartHeight	= m_nY;
	m_strImageDirectory = strImageDirectory;
}

CCharacter::~CCharacter(void)
{
	for (int i = 0; i < NUM_STATE; i++)
	{
		delete m_aAction[i];
	}
}

int CCharacter::IncreaseActionCount()
{
	m_nActionCount++;
	if (m_nActionCount == m_pActionState->GetNumAction())
	{
		m_nActionCount = ACTION_END;
	}
	return m_nActionCount;
}

void CCharacter::IncreaseFrameCount()
{
	m_nFrameCount++;
	if (m_nFrameCount == m_pActionState->GetNumFrame())
	{
		m_nFrameCount = 0;
	}
}

void CCharacter::ChangeAction( int nAction )
{
	// ������ ī��Ʈ �ʱ�ȭ
	m_nActionCount = 0;
	m_nFrameCount = 0;

	// �׼� ����
	if (nAction >= 0 && nAction < NUM_STATE)
	{
		m_pActionState		= m_aAction[nAction];
		m_nCurrentAction	= nAction;
	}
}

int CCharacter::FindNextAction(int nCurrentAction)
{
	return m_pActionDicider->GetNextAction(nCurrentAction);
}

int CCharacter::GetCurrentAction()
{
	return m_nCurrentAction;
}














// CAction //
CAction::CAction(CCharacter* pCharacter, int nNumAction, int nNumFrame, CCharacter* pTargetCharacter)
{
	m_ptrCharacter			= pCharacter;
	m_nNumAction			= nNumAction;
	m_nNumFrame				= nNumFrame;
	m_ptrTargetCharacter	= pTargetCharacter;
}

CAction::~CAction(void)
{
	DeleteObject(m_hBitmap);
}

void CAction::Draw(HDC hDC, HDC hMemoryDC)
{
	// ����
	HDC hObjectDC = CreateCompatibleDC(hDC);
	SelectObject(hObjectDC, m_hBitmap);
	TransparentBlt(hMemoryDC, m_ptrCharacter->GetX() - m_ptrTargetCharacter->GetX() + WIN_WIDTH / 2 - FRAME_WIDTH / 2, m_ptrCharacter->GetY(), FRAME_WIDTH, FRAME_HEIGHT, hObjectDC, m_ptrCharacter->GetFrameCount() * FRAME_WIDTH, 0, FRAME_WIDTH, FRAME_HEIGHT, TRANSPARNET_COLOR);
	DeleteDC(hObjectDC);
}
















// CRightMove
CRightMove::CRightMove(CCharacter* pCharacter, int nNumAction, int nNumFrame, HINSTANCE hInst, CCharacter* pTargetCharacter) : CAction(pCharacter, nNumAction, nNumFrame, pTargetCharacter)
{
	// �̹��� ���
	TCHAR szImagePath[64];
	wsprintf(szImagePath, TEXT("Image\\%s\\RightMove.bmp"), m_ptrCharacter->GetImageDirectory().c_str());

	// ��Ʈ�� �ε�
	m_hBitmap = (HBITMAP)LoadImage(hInst, szImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void CRightMove::Action()
{
	m_ptrCharacter->SetX(m_ptrCharacter->GetX() + m_ptrCharacter->GetSpeed());

	// ���� ũ�⸦ ����� �ʾҴ��� �˻�
	if (m_ptrCharacter->GetX() > m_ptrCharacter->GetMapInfo(0).size() * TILE_PIXEL + WIN_WIDTH / 2)
	{
		m_ptrCharacter->SetX(m_ptrCharacter->GetMapInfo(0).size() * TILE_PIXEL + WIN_WIDTH / 2);
	}

	// �������� �ʴ��� üũ(������ ���Ͱ� �������� ���� �������� �����Ƿ� ���ǵ�� �ӽ÷� ���ΰ� üũ)
	if (m_ptrCharacter->GetSpeed() > 10 && m_ptrCharacter->GetFloor() > 0)
	{
		// �볪���� ������
		if (m_ptrCharacter->GetMapInfo(m_ptrCharacter->GetFloor()).at(m_ptrCharacter->GetX() / TILE_PIXEL) == 0)
		{
			m_ptrCharacter->ChangeAction(RIGHT_FALL);
			
			return;
		}
	}

	// ���� �׼� �˻�
	int nNextAction = m_ptrCharacter->FindNextAction(RIGHT_MOVE);
	if (nNextAction != RIGHT_MOVE)
	{
		m_ptrCharacter->ChangeAction(nNextAction);
	}

	// �׼ǿ� ���� ������ ��ȭ
	if (m_ptrCharacter->IncreaseActionCount() % 2 == 1)
	{
		m_ptrCharacter->IncreaseFrameCount();
	}
}

// CLeftMove
CLeftMove::CLeftMove(CCharacter* pCharacter, int nNumAction, int nNumFrame, HINSTANCE hInst, CCharacter* pTargetCharacter) : CAction(pCharacter, nNumAction, nNumFrame, pTargetCharacter)
{
	// �̹��� ���
	TCHAR szImagePath[64];
	wsprintf(szImagePath, TEXT("Image\\%s\\LeftMove.bmp"), m_ptrCharacter->GetImageDirectory().c_str());

	// ��Ʈ�� �ε�
	m_hBitmap = (HBITMAP)LoadImage(hInst, szImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void CLeftMove::Action()
{
	m_ptrCharacter->SetX(m_ptrCharacter->GetX() - m_ptrCharacter->GetSpeed());
	// ���� ũ�⸦ ����� �ʾҴ��� �˻�
	if (m_ptrCharacter->GetX() < 0)
	{
		m_ptrCharacter->SetX(0);
	}

	// �������� �ʴ��� üũ
	if (m_ptrCharacter->GetSpeed() > 10 && m_ptrCharacter->GetFloor() > 0)
	{
		// �볪���� ������
		if (m_ptrCharacter->GetMapInfo(m_ptrCharacter->GetFloor()).at(m_ptrCharacter->GetX() / TILE_PIXEL) == 0)
		{
			m_ptrCharacter->ChangeAction(LEFT_FALL);
			return;
		}
	}

	// ���� �׼� �˻�
	int nNextAction = m_ptrCharacter->FindNextAction(LEFT_MOVE);
	if (nNextAction != LEFT_MOVE)
	{
		m_ptrCharacter->ChangeAction(nNextAction);
	}

	// �׼ǿ� ���� ������ ��ȭ
	if (m_ptrCharacter->IncreaseActionCount() % 2 == 1)
	{
		m_ptrCharacter->IncreaseFrameCount();
	}
}

// CJumpRight
CJumpRight::CJumpRight(CCharacter* pCharacter, int nNumAction, int nNumFrame, HINSTANCE hInst, CCharacter* pTargetCharacter) : CAction(pCharacter, nNumAction, nNumFrame, pTargetCharacter)
{
	// �̹��� ���
	TCHAR szImagePath[64];
	wsprintf(szImagePath, TEXT("Image\\%s\\RightJump.bmp"), m_ptrCharacter->GetImageDirectory().c_str());

	// ��Ʈ�� �ε�
	m_hBitmap = (HBITMAP)LoadImage(hInst, szImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void CJumpRight::Action()
{
	// ������ �Ʒ����� �ٽ� ���ŵǹǷ� ��꿡 ���� ����
	m_ptrCharacter->SetY(m_ptrCharacter->GetJumpStartHeight());

	// �׼ǿ� ���� ������ ��ȭ
	if (m_ptrCharacter->IncreaseActionCount() == ACTION_END)
	{
		m_ptrCharacter->ChangeAction(RIGHT_LANDING);
	}

	// ��ǥ �̵�
	m_ptrCharacter->SetY(m_ptrCharacter->GetY() - (int)(m_ptrCharacter->GetJumpHeight() * sin(m_ptrCharacter->GetActionCount() * (PIE / m_nNumAction))));

	// ������ �ö� �� �ִ°�?
	if (m_ptrCharacter->GetFloor() != 2)
	{
		// ������ �볪���� �ִ°�?
		if (m_ptrCharacter->GetMapInfo(m_ptrCharacter->GetFloor() + 1).at(m_ptrCharacter->GetX() / TILE_PIXEL))
		{
			// �������� ���̰� �볪������ �������ٸ�
			if (m_ptrCharacter->GetActionCount() > m_nNumAction / 2 && m_ptrCharacter->GetY() > LAND_HEIGHT - (m_ptrCharacter->GetFloor() + 1) * FLOOR_HEIGHT - FLOOR_HEIGHT)
			{
				m_ptrCharacter->SetFloor(m_ptrCharacter->GetFloor() + 1);

				// y��ǥ ����
				m_ptrCharacter->SetY(LAND_HEIGHT - m_ptrCharacter->GetFloor() * FLOOR_HEIGHT - FRAME_HEIGHT + 40);
				m_ptrCharacter->SetJumpStartHeight(m_ptrCharacter->GetY());

				m_ptrCharacter->ChangeAction(RIGHT_LANDING);
			}
		}
	}
}

// CJumpLeft
CJumpLeft::CJumpLeft(CCharacter* pCharacter, int nNumAction, int nNumFrame, HINSTANCE hInst, CCharacter* pTargetCharacter) : CAction(pCharacter, nNumAction, nNumFrame, pTargetCharacter)
{
	// �̹��� ���
	TCHAR szImagePath[64];
	wsprintf(szImagePath, TEXT("Image\\%s\\LeftJump.bmp"), m_ptrCharacter->GetImageDirectory().c_str());

	// ��Ʈ�� �ε�
	m_hBitmap = (HBITMAP)LoadImage(hInst, szImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void CJumpLeft::Action()
{
	// ������ �Ʒ����� �ٽ� ���ŵǹǷ� ��꿡 ���� ����
	m_ptrCharacter->SetY(m_ptrCharacter->GetJumpStartHeight());

	// �׼ǿ� ���� ������ ��ȭ
	if (m_ptrCharacter->IncreaseActionCount() == ACTION_END)
	{
		m_ptrCharacter->ChangeAction(LEFT_LANDING);
	}

	// ��ǥ �̵�
	m_ptrCharacter->SetY(m_ptrCharacter->GetY() - (int)(m_ptrCharacter->GetJumpHeight() * sin(m_ptrCharacter->GetActionCount() * (PIE / m_nNumAction))));

	// ������ �ö� �� �ִ°�?
	if (m_ptrCharacter->GetFloor() != 2)
	{
		// ������ �볪���� �ִ°�?
		if (m_ptrCharacter->GetMapInfo(m_ptrCharacter->GetFloor() + 1).at(m_ptrCharacter->GetX() / TILE_PIXEL))
		{
			// �������� ���̰� �볪������ �������ٸ�
			if (m_ptrCharacter->GetActionCount() > m_nNumAction / 2 && m_ptrCharacter->GetY() > LAND_HEIGHT - (m_ptrCharacter->GetFloor() + 1) * FLOOR_HEIGHT - FLOOR_HEIGHT)
			{
				m_ptrCharacter->SetFloor(m_ptrCharacter->GetFloor() + 1);

				// y��ǥ ����
				m_ptrCharacter->SetY(LAND_HEIGHT - m_ptrCharacter->GetFloor() * FLOOR_HEIGHT - FRAME_HEIGHT + 40);
				m_ptrCharacter->SetJumpStartHeight(m_ptrCharacter->GetY());

				m_ptrCharacter->ChangeAction(LEFT_LANDING);
			}
		}
	}
}

// CRightJump
CRightJump::CRightJump(CCharacter* pCharacter, int nNumAction, int nNumFrame, HINSTANCE hInst, CCharacter* pTargetCharacter) : CAction(pCharacter, nNumAction, nNumFrame, pTargetCharacter)
{
	// �̹��� ���
	TCHAR szImagePath[64];
	wsprintf(szImagePath, TEXT("Image\\%s\\RightJump.bmp"), m_ptrCharacter->GetImageDirectory().c_str());

	// ��Ʈ�� �ε�
	m_hBitmap = (HBITMAP)LoadImage(hInst, szImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void CRightJump::Action()
{	
	// ������ �Ʒ����� �ٽ� ���ŵǹǷ� ��꿡 ���� ����
	m_ptrCharacter->SetY(m_ptrCharacter->GetJumpStartHeight());

	// �׼ǿ� ���� ������ ��ȭ
	if (m_ptrCharacter->IncreaseActionCount() == ACTION_END)
	{
		// �������� �ʴ��� üũ(������ ���Ͱ� �������� ���� �������� �����Ƿ� ���ǵ�� �ӽ÷� ���ΰ� üũ)
		if (m_ptrCharacter->GetSpeed() > 10 && m_ptrCharacter->GetFloor() > 0)
		{
			// �볪���� ������
			if (m_ptrCharacter->GetMapInfo(m_ptrCharacter->GetFloor()).at(m_ptrCharacter->GetX() / TILE_PIXEL) == 0)
			{
				m_ptrCharacter->ChangeAction(RIGHT_FALL);
				return;
			}
		}

		// ���º�ȭ
		m_ptrCharacter->ChangeAction(RIGHT_LANDING);
	}

	// ��ǥ �̵�
	m_ptrCharacter->SetX(m_ptrCharacter->GetX() + m_ptrCharacter->GetSpeed() / 2);
	m_ptrCharacter->SetY(m_ptrCharacter->GetY() - (int)(m_ptrCharacter->GetJumpHeight() / 2 * sin(m_ptrCharacter->GetActionCount() * (PIE / m_nNumAction))));

	// ���� ũ�⸦ ����� �ʾҴ��� �˻�
	if (m_ptrCharacter->GetX() > m_ptrCharacter->GetMapInfo(0).size() * TILE_PIXEL + WIN_WIDTH / 2)
	{
		m_ptrCharacter->SetX(m_ptrCharacter->GetMapInfo(0).size() * TILE_PIXEL + WIN_WIDTH / 2);
	}
}

// CLeftJump
CLeftJump::CLeftJump(CCharacter* pCharacter, int nNumAction, int nNumFrame, HINSTANCE hInst, CCharacter* pTargetCharacter) : CAction(pCharacter, nNumAction, nNumFrame, pTargetCharacter)
{
	// �̹��� ���
	TCHAR szImagePath[64];
	wsprintf(szImagePath, TEXT("Image\\%s\\LeftJump.bmp"), m_ptrCharacter->GetImageDirectory().c_str());

	// ��Ʈ�� �ε�
	m_hBitmap = (HBITMAP)LoadImage(hInst, szImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void CLeftJump::Action()
{
	// ������ �Ʒ����� �ٽ� ���ŵǹǷ� ��꿡 ���� ����
	m_ptrCharacter->SetY(m_ptrCharacter->GetJumpStartHeight());

	// �׼ǿ� ���� ������ ��ȭ
	if (m_ptrCharacter->IncreaseActionCount() == ACTION_END)
	{
		// �������� �ʴ��� üũ(������ ���Ͱ� �������� ���� �������� �����Ƿ� ���ǵ�� �ӽ÷� ���ΰ� üũ)
		if (m_ptrCharacter->GetSpeed() > 10 && m_ptrCharacter->GetFloor() > 0)
		{
			// �볪���� ������
			if (m_ptrCharacter->GetMapInfo(m_ptrCharacter->GetFloor()).at(m_ptrCharacter->GetX() / TILE_PIXEL) == 0)
			{
				m_ptrCharacter->ChangeAction(LEFT_FALL);
				return;
			}
		}

		// ���º�ȭ
		m_ptrCharacter->ChangeAction(LEFT_LANDING);
	}

	// ��ǥ �̵�
	m_ptrCharacter->SetX(m_ptrCharacter->GetX() - m_ptrCharacter->GetSpeed() / 2);
	m_ptrCharacter->SetY(m_ptrCharacter->GetY() - (int)(m_ptrCharacter->GetJumpHeight() / 2 * sin(m_ptrCharacter->GetActionCount() * (PIE / m_nNumAction))));
	
	// ���� ũ�⸦ ����� �ʾҴ��� �˻�
	if (m_ptrCharacter->GetX() < 0)
	{
		m_ptrCharacter->SetX(0);
	}
}

// CRightLanding
CRightLanding::CRightLanding(CCharacter* pCharacter, int nNumAction, int nNumFrame, HINSTANCE hInst, CCharacter* pTargetCharacter) : CAction(pCharacter, nNumAction, nNumFrame, pTargetCharacter)
{
	// �̹��� ���
	TCHAR szImagePath[64];
	wsprintf(szImagePath, TEXT("Image\\%s\\RightJump.bmp"), m_ptrCharacter->GetImageDirectory().c_str());

	// ��Ʈ�� �ε�
	m_hBitmap = (HBITMAP)LoadImage(hInst, szImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void CRightLanding::Action()
{
	// �׼ǿ� ���� ������ ��ȭ
	if (m_ptrCharacter->IncreaseActionCount() == ACTION_END)
	{
		m_ptrCharacter->ChangeAction(RIGHT_IDLE);
	}
}

// CLeftLanding
CLeftLanding::CLeftLanding(CCharacter* pCharacter, int nNumAction, int nNumFrame, HINSTANCE hInst, CCharacter* pTargetCharacter) : CAction(pCharacter, nNumAction, nNumFrame, pTargetCharacter)
{
	// �̹��� ���
	TCHAR szImagePath[64];
	wsprintf(szImagePath, TEXT("Image\\%s\\LeftJump.bmp"), m_ptrCharacter->GetImageDirectory().c_str());

	// ��Ʈ�� �ε�
	m_hBitmap = (HBITMAP)LoadImage(hInst, szImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void CLeftLanding::Action()
{
	// �׼ǿ� ���� ������ ��ȭ
	if (m_ptrCharacter->IncreaseActionCount() == ACTION_END)
	{
		m_ptrCharacter->ChangeAction(LEFT_IDLE);
	}
}

// CRightIdle
CRightIdle::CRightIdle(CCharacter* pCharacter, int nNumAction, int nNumFrame, HINSTANCE hInst, CCharacter* pTargetCharacter) : CAction(pCharacter, nNumAction, nNumFrame, pTargetCharacter)
{
	// �̹��� ���
	TCHAR szImagePath[64];
	wsprintf(szImagePath, TEXT("Image\\%s\\RightIdle.bmp"), m_ptrCharacter->GetImageDirectory().c_str());

	// ��Ʈ�� �ε�
	m_hBitmap = (HBITMAP)LoadImage(hInst, szImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void CRightIdle::Action()
{
	// ���� �׼� �˻�
	int nNextAction = m_ptrCharacter->FindNextAction(RIGHT_IDLE);
	if (nNextAction != RIGHT_IDLE)
	{
		m_ptrCharacter->ChangeAction(nNextAction);
	}

	// �׼ǿ� ���� ������ ��ȭ
	if (m_ptrCharacter->IncreaseActionCount() % 3 == 2)
	{
		m_ptrCharacter->IncreaseFrameCount();
	}
}

// CLeftIdle
CLeftIdle::CLeftIdle(CCharacter* pCharacter, int nNumAction, int nNumFrame, HINSTANCE hInst, CCharacter* pTargetCharacter) : CAction(pCharacter, nNumAction, nNumFrame, pTargetCharacter)
{
	// �̹��� ���
	TCHAR szImagePath[64];
	wsprintf(szImagePath, TEXT("Image\\%s\\LeftIdle.bmp"), m_ptrCharacter->GetImageDirectory().c_str());

	// ��Ʈ�� �ε�
	m_hBitmap = (HBITMAP)LoadImage(hInst, szImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void CLeftIdle::Action()
{
	// ���� �׼� �˻�
	int nNextAction = m_ptrCharacter->FindNextAction(LEFT_IDLE);
	if (nNextAction != LEFT_IDLE)
	{
		m_ptrCharacter->ChangeAction(nNextAction);
	}

	// �׼ǿ� ���� ������ ��ȭ
	if (m_ptrCharacter->IncreaseActionCount() % 3 == 2)
	{
		m_ptrCharacter->IncreaseFrameCount();
	}
}


// CRightDie
CRightDie::CRightDie(CCharacter* pCharacter, int nNumAction, int nNumFrame, HINSTANCE hInst, CCharacter* pTargetCharacter) : CAction(pCharacter, nNumAction, nNumFrame, pTargetCharacter)
{
	// �̹��� ���
	TCHAR szImagePath[64];
	wsprintf(szImagePath, TEXT("Image\\%s\\RightDie.bmp"), m_ptrCharacter->GetImageDirectory().c_str());

	// ��Ʈ�� �ε�
	m_hBitmap = (HBITMAP)LoadImage(hInst, szImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void CRightDie::Action()
{
	// �׼ǿ� ���� ������ ��ȭ
	int nActionCount = m_ptrCharacter->IncreaseActionCount();
	if (nActionCount == ACTION_END)
	{
		m_ptrCharacter->SetEnable(false);
	}
	else if (nActionCount % 2 == 1)
	{
		m_ptrCharacter->IncreaseFrameCount();
	}
}

// CLeftDie
CLeftDie::CLeftDie(CCharacter* pCharacter, int nNumAction, int nNumFrame, HINSTANCE hInst, CCharacter* pTargetCharacter) : CAction(pCharacter, nNumAction, nNumFrame, pTargetCharacter)
{
	// �̹��� ���
	TCHAR szImagePath[64];
	wsprintf(szImagePath, TEXT("Image\\%s\\LeftDie.bmp"), m_ptrCharacter->GetImageDirectory().c_str());

	// ��Ʈ�� �ε�
	m_hBitmap = (HBITMAP)LoadImage(hInst, szImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void CLeftDie::Action()
{
	// �׼ǿ� ���� ������ ��ȭ
	int nActionCount = m_ptrCharacter->IncreaseActionCount();
	if (nActionCount == ACTION_END)
	{
		m_ptrCharacter->SetEnable(false);
	}
	else if (nActionCount % 2 == 1)
	{
		m_ptrCharacter->IncreaseFrameCount();
	}
}

// CRightStun
CRightStun::CRightStun(CCharacter* pCharacter, int nNumAction, int nNumFrame, HINSTANCE hInst, CCharacter* pTargetCharacter) : CAction(pCharacter, nNumAction, nNumFrame, pTargetCharacter)
{
	// �̹��� ���
	TCHAR szImagePath[64];
	wsprintf(szImagePath, TEXT("Image\\%s\\RightStun.bmp"), m_ptrCharacter->GetImageDirectory().c_str());

	// ��Ʈ�� �ε�
	m_hBitmap = (HBITMAP)LoadImage(hInst, szImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void CRightStun::Action()
{
	// �׼ǿ� ���� ������ ��ȭ
	int nActionCount = m_ptrCharacter->IncreaseActionCount();
	if (nActionCount == ACTION_END)
	{
		m_ptrCharacter->ChangeAction(RIGHT_UNBEATABLE);
	}
	else if (nActionCount % 2 == 1)
	{
		m_ptrCharacter->IncreaseFrameCount();
	}
}

// CLeftStun
CLeftStun::CLeftStun(CCharacter* pCharacter, int nNumAction, int nNumFrame, HINSTANCE hInst, CCharacter* pTargetCharacter) : CAction(pCharacter, nNumAction, nNumFrame, pTargetCharacter)
{
	// �̹��� ���
	TCHAR szImagePath[64];
	wsprintf(szImagePath, TEXT("Image\\%s\\LeftStun.bmp"), m_ptrCharacter->GetImageDirectory().c_str());

	// ��Ʈ�� �ε�
	m_hBitmap = (HBITMAP)LoadImage(hInst, szImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void CLeftStun::Action()
{
	// �׼ǿ� ���� ������ ��ȭ
	int nActionCount = m_ptrCharacter->IncreaseActionCount();
	if (nActionCount == ACTION_END)
	{
		m_ptrCharacter->ChangeAction(LEFT_UNBEATABLE);
	}
	else if (nActionCount % 2 == 1)
	{
		m_ptrCharacter->IncreaseFrameCount();
	}
}

CRightFall::CRightFall(CCharacter* pCharacter, int nNumAction, int nNumFrame, HINSTANCE hInst, CCharacter* pTargetCharacter) : CAction(pCharacter, nNumAction, nNumFrame, pTargetCharacter)
{
	// �̹��� ���
	TCHAR szImagePath[64];
	wsprintf(szImagePath, TEXT("Image\\%s\\RightJump.bmp"), m_ptrCharacter->GetImageDirectory().c_str());

	// ��Ʈ�� �ε�
	m_hBitmap = (HBITMAP)LoadImage(hInst, szImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void CRightFall::Action()
{
	m_ptrCharacter->SetX(m_ptrCharacter->GetX() + 5);
	m_ptrCharacter->SetY(m_ptrCharacter->GetY() + FLOOR_HEIGHT / 7);
	
	// �׼ǿ� ���� ������ ��ȭ
	if (m_ptrCharacter->IncreaseActionCount() == ACTION_END)
	{
		m_ptrCharacter->SetFloor(m_ptrCharacter->GetFloor() - 1);
		m_ptrCharacter->SetY(LAND_HEIGHT - m_ptrCharacter->GetFloor() * FLOOR_HEIGHT - FRAME_HEIGHT + 40);
		m_ptrCharacter->SetJumpStartHeight(m_ptrCharacter->GetY());
		
		// ���� �� �������� �Ѵٸ�
		if (m_ptrCharacter->GetSpeed() > 10 && m_ptrCharacter->GetFloor() > 0)
		{
			// �볪���� ������
			if (m_ptrCharacter->GetMapInfo(m_ptrCharacter->GetFloor()).at(m_ptrCharacter->GetX() / TILE_PIXEL) == 0)
			{
				m_ptrCharacter->ChangeAction(RIGHT_FALL);
				return;
			}
		}

		// ���� ��ȭ
		m_ptrCharacter->ChangeAction(RIGHT_LANDING);
	}
}

CLeftFall::CLeftFall(CCharacter* pCharacter, int nNumAction, int nNumFrame, HINSTANCE hInst, CCharacter* pTargetCharacter) : CAction(pCharacter, nNumAction, nNumFrame, pTargetCharacter)
{
	// �̹��� ���
	TCHAR szImagePath[64];
	wsprintf(szImagePath, TEXT("Image\\%s\\LeftJump.bmp"), m_ptrCharacter->GetImageDirectory().c_str());

	// ��Ʈ�� �ε�
	m_hBitmap = (HBITMAP)LoadImage(hInst, szImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void CLeftFall::Action()
{
	m_ptrCharacter->SetX(m_ptrCharacter->GetX() - 5);
	m_ptrCharacter->SetY(m_ptrCharacter->GetY() + FLOOR_HEIGHT / 7);

	// �׼ǿ� ���� ������ ��ȭ
	if (m_ptrCharacter->IncreaseActionCount() == ACTION_END)
	{
		m_ptrCharacter->SetFloor(m_ptrCharacter->GetFloor() - 1);
		m_ptrCharacter->SetY(LAND_HEIGHT - m_ptrCharacter->GetFloor() * FLOOR_HEIGHT - FRAME_HEIGHT + 40);
		m_ptrCharacter->SetJumpStartHeight(m_ptrCharacter->GetY());

		// ���� �� �������� �Ѵٸ�
		if (m_ptrCharacter->GetSpeed() > 10 && m_ptrCharacter->GetFloor() > 0)
		{
			// �볪���� ������
			if (m_ptrCharacter->GetMapInfo(m_ptrCharacter->GetFloor()).at(m_ptrCharacter->GetX() / TILE_PIXEL) == 0)
			{
				m_ptrCharacter->ChangeAction(LEFT_FALL);
				return;
			}
		}

		// ���� ��ȭ
		m_ptrCharacter->ChangeAction(LEFT_IDLE);
	}
}

CRightUnbeatable::CRightUnbeatable(CCharacter* pCharacter, int nNumAction, int nNumFrame, HINSTANCE hInst, CCharacter* pTargetCharacter) : CAction(pCharacter, nNumAction, nNumFrame, pTargetCharacter)
{
	// �̹��� ���
	TCHAR szImagePath[64];
	wsprintf(szImagePath, TEXT("Image\\%s\\RightUnbeatable.bmp"), m_ptrCharacter->GetImageDirectory().c_str());

	// ��Ʈ�� �ε�
	m_hBitmap = (HBITMAP)LoadImage(hInst, szImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void CRightUnbeatable::Action()
{
	// ���� �׼� �˻�
	int nNextAction = m_ptrCharacter->FindNextAction(RIGHT_UNBEATABLE);
	if (nNextAction != RIGHT_UNBEATABLE)
	{
		m_ptrCharacter->ChangeAction(nNextAction);
		return;
	}

	// �׼ǿ� ���� ������ ��ȭ
	int nActionCount = m_ptrCharacter->IncreaseActionCount();
	if (nActionCount == ACTION_END)
	{
		m_ptrCharacter->ChangeAction(RIGHT_IDLE);
	}
	else if (nActionCount % 2 == 1)
	{
		m_ptrCharacter->IncreaseFrameCount();
	}
}

CLeftUnbeatable::CLeftUnbeatable(CCharacter* pCharacter, int nNumAction, int nNumFrame, HINSTANCE hInst, CCharacter* pTargetCharacter) : CAction(pCharacter, nNumAction, nNumFrame, pTargetCharacter)
{
	// �̹��� ���
	TCHAR szImagePath[64];
	wsprintf(szImagePath, TEXT("Image\\%s\\LeftUnbeatable.bmp"), m_ptrCharacter->GetImageDirectory().c_str());

	// ��Ʈ�� �ε�
	m_hBitmap = (HBITMAP)LoadImage(hInst, szImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void CLeftUnbeatable::Action()
{
	// ���� �׼� �˻�
	int nNextAction = m_ptrCharacter->FindNextAction(LEFT_UNBEATABLE);
	if (nNextAction != LEFT_UNBEATABLE)
	{
		m_ptrCharacter->ChangeAction(nNextAction);
		return;
	}

	// �׼ǿ� ���� ������ ��ȭ
	int nActionCount = m_ptrCharacter->IncreaseActionCount();
	if (nActionCount == ACTION_END)
	{
		m_ptrCharacter->ChangeAction(LEFT_IDLE);
	}
	else if (nActionCount % 2 == 1)
	{
		m_ptrCharacter->IncreaseFrameCount();
	}
}