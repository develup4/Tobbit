#pragma once
#include "CMonsterAI.h"
#define MONSTER_SIGHT_RANGE	(WIN_WIDTH / 3)

class CCowardly : public CMonsterAI
{
private:

protected:

public:
	CCowardly(CHero* ptrHero, int* pX, int nFloor, std::wstring strWord);
	~CCowardly(void);

	int		GetNextAction(int nCurrentAction);
	bool	IsApproach();		// �볪�� ���̰� �������ִ��� �ؼ� ������ �Ұ������� ������ üũ
};
