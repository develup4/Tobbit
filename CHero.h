#pragma once
#include "CCharacter.h"
#include "CInputListener.h"

#define	MAX_HP		3

class CHero : public CCharacter
{
private:
	int				m_nHP;

protected:

public:
	CHero(HINSTANCE hInst, int nX, int nSpeed, int nJumpHeight, int nFloor, int nHP, std::wstring strImageDirectory);
	~CHero(void);
	
	void			Action();
	void			Draw(HDC hDC, HDC hMemoryDC);

	int				GetHP() const			{	return m_nHP;			}
	void			SetHP(int nHP)			{	m_nHP	= nHP;			}
	void			IncreaseHP();
	void			DecreaseHP();

	void			Init();
};
