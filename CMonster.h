#pragma once
#include "CCowardly.h"
#include "CCharacter.h"
#define ALPABET_FRAME_LENGTH	80

class CMonster : public CCharacter
{
private:
	CMonsterAI*		pAI;					// �ΰ����� ��ü
	std::wstring	m_strWord;				// ���� �ܾ�
	HBITMAP			m_hBitmapAlphabet;		// ���ĺ� �̹���
	CHero*			m_ptrHero;

protected:

public:
	CMonster(HINSTANCE hInst, int nX, int nSpeed, int nJumpHeight, int nFloor, std::wstring strImageDirectory, std::wstring strWord, CHero* ptrHero);
	~CMonster(void);
	
	void			Action();
	void			Draw(HDC hDC, HDC hMemoryDC);
};
