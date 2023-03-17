#include "CInputListener.h"

CInputListener::CInputListener(void)
{

}

CInputListener::~CInputListener(void)
{

}

int CInputListener::GetNextAction(int nCurrentAction)
{
	bool bRightKeydown	= false;
	bool bLeftKeydown	= false;
	bool bSpaceKeydown	= false;

	// 키 입력 체크
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		bRightKeydown = true;
	}
	if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && bRightKeydown == false)
	{
		bLeftKeydown = true;
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		bSpaceKeydown = true;
	}

	switch (nCurrentAction)
	{
		case RIGHT_IDLE:
		case RIGHT_MOVE:
		case RIGHT_UNBEATABLE:
		{
			if (bSpaceKeydown)
			{
				if (bRightKeydown)
				{
					return RIGHT_JUMP;
				}
				if (bLeftKeydown)
				{
					return LEFT_JUMP;
				}
				return JUMP_RIGHT;
			}
			else
			{
				if (bRightKeydown)
				{
					return RIGHT_MOVE;
				}
				if (bLeftKeydown)
				{
					return LEFT_MOVE;
				}
			}
			if (nCurrentAction == RIGHT_UNBEATABLE)
			{
				return RIGHT_UNBEATABLE;
			}
			return RIGHT_IDLE;
		}
		case LEFT_IDLE:
		case LEFT_MOVE:
		case LEFT_UNBEATABLE:
		{
			if (bSpaceKeydown)
			{
				if (bLeftKeydown)
				{
					return LEFT_JUMP;
				}
				if (bRightKeydown)
				{
					return RIGHT_JUMP;
				}
				return JUMP_LEFT;
			}
			else
			{
				if (bLeftKeydown)
				{
					return LEFT_MOVE;
				}
				if (bRightKeydown)
				{
					return RIGHT_MOVE;
				}
			}
			if (nCurrentAction == LEFT_UNBEATABLE)
			{
				return LEFT_UNBEATABLE;
			}
			return LEFT_IDLE;
		}
		default:
		{
			return nCurrentAction;
		}
	}
}