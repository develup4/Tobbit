#include "CCowardly.h"

CCowardly::CCowardly(CHero* ptrHero, int* pX, int nFloor, std::wstring strWord) : CMonsterAI(ptrHero, pX, nFloor, strWord)
{

}

CCowardly::~CCowardly(void)
{

}

int CCowardly::GetNextAction(int nCurrentAction)
{
	int nNextAction = 0;

	// ���ΰ��� �þ߿� ��������
	if (abs(*m_pX - m_ptrHero->GetX()) < MONSTER_SIGHT_RANGE && IsApproach() && m_ptrHero->GetCurrentAction() != RIGHT_DIE && m_ptrHero->GetCurrentAction() != LEFT_DIE)
	{
		// �ϴ� ����
		if (m_ptrHero->GetX() < *m_pX)
		{
			nNextAction = LEFT_MOVE;
		}
		else
		{
			nNextAction = RIGHT_MOVE;
		}

		// ���ΰ� �׼ǿ� ���� ���׼�
		switch (m_ptrHero->GetCurrentAction())
		{
			case RIGHT_LANDING:
			{
				// ���Ͱ� �������� üũ
				if (abs(*m_pX - m_ptrHero->GetX()) <= FRAME_WIDTH / 2)
				{
					// �ܾ� ���� ���
					TCHAR	wszPath[64];
					wsprintf(wszPath, TEXT("Sound\\Pronounce\\%s.wav"), m_strWord.c_str());
					PlaySound(wszPath, NULL, SND_ASYNC);

					return RIGHT_DIE;
				}		
			}
			case LEFT_LANDING:
			{
				// ���Ͱ� �������� üũ
				if (abs(*m_pX - m_ptrHero->GetX()) <= FRAME_WIDTH / 2)
				{
					// �ܾ� ���� ���
					TCHAR	wszPath[64];
					wsprintf(wszPath, TEXT("Sound\\Pronounce\\%s.wav"), m_strWord.c_str());
					PlaySound(wszPath, NULL, SND_ASYNC);

					return LEFT_DIE;
				}		
			}
			case RIGHT_IDLE:
			case RIGHT_MOVE:
			{
				// ���ΰ� �״��� üũ
				if (abs(m_ptrHero->GetX() - *m_pX) <= FRAME_WIDTH / 2)
				{
					m_ptrHero->ChangeAction(RIGHT_STUN);
					m_ptrHero->DecreaseHP();
				}
				break;
			}
			case LEFT_IDLE:
			case LEFT_MOVE:
			{
				// ���ΰ� �״��� üũ
				if (abs(m_ptrHero->GetX() - *m_pX) <= FRAME_WIDTH / 2)
				{
					m_ptrHero->ChangeAction(LEFT_STUN);
					m_ptrHero->DecreaseHP();
				}
				break;
			}
			
			// �����̰ų� �������϶�(¥��������) ����������
			case RIGHT_STUN:
			case RIGHT_UNBEATABLE:
			case JUMP_RIGHT:
			case LEFT_STUN:
			case LEFT_UNBEATABLE:
			case JUMP_LEFT:
			{
				if (m_ptrHero->GetX() < *m_pX)
				{
					nNextAction = RIGHT_MOVE;
				}
				else
				{
					nNextAction = LEFT_MOVE;
				}
				break;
			}
			// �ڽ������� �����Ҷ��� ����
			case LEFT_JUMP:
			{
				if (m_ptrHero->GetX() > *m_pX)
				{
					nNextAction = LEFT_MOVE;
				}
				break;
			}
			case RIGHT_JUMP:
			{
				if (m_ptrHero->GetX() < *m_pX)
				{
					nNextAction = RIGHT_MOVE;
				}
				break;
			}
		}
	}

	// �þ߿� ������ �ΰ����� FSM
	else
	{
		int nRandomNumber = 0;

		switch (nCurrentAction)
		{
			case RIGHT_MOVE:
			{
				nRandomNumber = rand() % (FRAMERATE * 2);	// 2�ʿ� �ѹ�����

				if (nRandomNumber == 0)
				{
					nNextAction = RIGHT_IDLE;
					break;
				}
				nNextAction = RIGHT_MOVE;
				break;
			}
			case LEFT_MOVE:
			{
				nRandomNumber = rand() % (FRAMERATE * 2);

				if (nRandomNumber == 0)
				{
					nNextAction = LEFT_IDLE;
					break;
				}
				nNextAction = LEFT_MOVE;
				break;
			}
			case RIGHT_IDLE:
			{
				nRandomNumber = rand() % FRAMERATE;

				if (nRandomNumber == 0)
				{
					nNextAction = RIGHT_MOVE;
					break;
				}
				if (nRandomNumber == 1)
				{
					nNextAction = LEFT_MOVE;
					break;
				}
				nNextAction = RIGHT_IDLE;
				break;
			}
			case LEFT_IDLE:
			{
				nRandomNumber = rand() % FRAMERATE;

				if (nRandomNumber == 0)
				{
					nNextAction = RIGHT_MOVE;
					break;
				}
				if (nRandomNumber == 1)
				{
					nNextAction = LEFT_MOVE;
					break;
				}
				nNextAction = LEFT_IDLE;
				break;
			}
		}
	}

	// �볪������ �ȶ���������
	if (m_nFloor > 0)
	{
		if (nNextAction == LEFT_MOVE && m_ptrHero->GetMapInfo(m_nFloor).at((*m_pX / TILE_PIXEL) - 1) == 0)
		{
			return RIGHT_MOVE;
		}
		if (m_ptrHero->GetMapInfo(m_nFloor).at((*m_pX / TILE_PIXEL) + 1) == 0)
		{
			return LEFT_MOVE;
		}
	}
	return nNextAction;
}

bool CCowardly::IsApproach()
{
	// �ϴ� ���� ���ƾ�
	if (m_ptrHero->GetFloor() != m_nFloor)
	{
		return false;
	}
	// 1���̸� ����
	else if (m_nFloor == 0)
	{
		return true;
	}
	
	// �볪���� ������ ���� ������
	if (m_ptrHero->GetX() < *m_pX)
	{
		for (int i = m_ptrHero->GetX() / TILE_PIXEL; i < *m_pX / TILE_PIXEL; i++)
		{
			if (m_ptrHero->GetMapInfo(m_nFloor).at(i) == 0)
			{
				return false;
			}
		}
	}
	else
	{
		for (int i = *m_pX / TILE_PIXEL; i < m_ptrHero->GetX() / TILE_PIXEL; i++)
		{
			if (m_ptrHero->GetMapInfo(m_nFloor).at(i) == 0)
			{
				return false;
			}
		}
	}
	return true;
}