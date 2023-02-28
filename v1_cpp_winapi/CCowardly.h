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
	bool	IsApproach();		// 통나무 사이가 떨어져있던지 해서 접근이 불가능하진 않은지 체크
};
