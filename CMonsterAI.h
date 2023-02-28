#pragma once
#include "CActionDicider.h"
#include "CHero.h"

class CMonsterAI : public CActionDicider
{
private:

protected:
	CHero*				m_ptrHero;
	int*				m_pX;
	int					m_nFloor;
	std::wstring		m_strWord;

public:
	CMonsterAI(CHero* ptrHero, int* pX, int nFloor, std::wstring strWord);
	~CMonsterAI(void);

	virtual int			GetNextAction(int nCurrentAction) = 0;		// 순수가상함수(추상클래스)
};
