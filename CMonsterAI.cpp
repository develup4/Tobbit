#include "CMonsterAI.h"

CMonsterAI::CMonsterAI(CHero* ptrHero, int* pX, int nFloor, std::wstring strWord)
{
	m_ptrHero	= ptrHero;
	m_pX		= pX;
	m_nFloor	= nFloor;
	m_strWord	= strWord;
}

CMonsterAI::~CMonsterAI(void)
{

}
