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

	// 주인공이 시야에 들어왔을때
	if (abs(*m_pX - m_ptrHero->GetX()) < MONSTER_SIGHT_RANGE && IsApproach() && m_ptrHero->GetCurrentAction() != RIGHT_DIE && m_ptrHero->GetCurrentAction() != LEFT_DIE)
	{
		// 일단 돌격
		if (m_ptrHero->GetX() < *m_pX)
		{
			nNextAction = LEFT_MOVE;
		}
		else
		{
			nNextAction = RIGHT_MOVE;
		}

		// 주인공 액션에 따른 리액션
		switch (m_ptrHero->GetCurrentAction())
		{
			case RIGHT_LANDING:
			{
				// 몬스터가 밟혔는지 체크
				if (abs(*m_pX - m_ptrHero->GetX()) <= FRAME_WIDTH / 2)
				{
					// 단어 발음 재생
					TCHAR	wszPath[64];
					wsprintf(wszPath, TEXT("Sound\\Pronounce\\%s.wav"), m_strWord.c_str());
					PlaySound(wszPath, NULL, SND_ASYNC);

					return RIGHT_DIE;
				}		
			}
			case LEFT_LANDING:
			{
				// 몬스터가 밟혔는지 체크
				if (abs(*m_pX - m_ptrHero->GetX()) <= FRAME_WIDTH / 2)
				{
					// 단어 발음 재생
					TCHAR	wszPath[64];
					wsprintf(wszPath, TEXT("Sound\\Pronounce\\%s.wav"), m_strWord.c_str());
					PlaySound(wszPath, NULL, SND_ASYNC);

					return LEFT_DIE;
				}		
			}
			case RIGHT_IDLE:
			case RIGHT_MOVE:
			{
				// 주인공 죽는지 체크
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
				// 주인공 죽는지 체크
				if (abs(m_ptrHero->GetX() - *m_pX) <= FRAME_WIDTH / 2)
				{
					m_ptrHero->ChangeAction(LEFT_STUN);
					m_ptrHero->DecreaseHP();
				}
				break;
			}
			
			// 무적이거나 점프중일때(짜증나도록) 도망가도록
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
			// 자신쪽으로 점프할때만 도망
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

	// 시야에 없을때 인공지능 FSM
	else
	{
		int nRandomNumber = 0;

		switch (nCurrentAction)
		{
			case RIGHT_MOVE:
			{
				nRandomNumber = rand() % (FRAMERATE * 2);	// 2초에 한번정도

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

	// 통나무에서 안떨어지도록
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
	// 일단 층이 같아야
	if (m_ptrHero->GetFloor() != m_nFloor)
	{
		return false;
	}
	// 1층이면 가능
	else if (m_nFloor == 0)
	{
		return true;
	}
	
	// 통나무가 떨어져 있지 않은지
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