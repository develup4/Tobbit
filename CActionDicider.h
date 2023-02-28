#pragma once

// 액션 상수
enum
{
	RIGHT_MOVE,
	LEFT_MOVE,
	JUMP_RIGHT,
	JUMP_LEFT,
	RIGHT_JUMP,
	LEFT_JUMP,
	RIGHT_LANDING,
	LEFT_LANDING,
	RIGHT_IDLE,
	LEFT_IDLE,
	RIGHT_DIE,
	LEFT_DIE,
	RIGHT_STUN,
	LEFT_STUN,
	RIGHT_FALL,
	LEFT_FALL,
	RIGHT_UNBEATABLE,
	LEFT_UNBEATABLE,
	NUM_STATE,
};

// 순수가상함수(인터페이스)
class CActionDicider
{
private:
protected:

public:
	CActionDicider(void);
	~CActionDicider(void);

	virtual int GetNextAction(int nCurrentAction) = 0;
};
