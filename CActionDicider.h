#pragma once

// �׼� ���
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

// ���������Լ�(�������̽�)
class CActionDicider
{
private:
protected:

public:
	CActionDicider(void);
	~CActionDicider(void);

	virtual int GetNextAction(int nCurrentAction) = 0;
};
