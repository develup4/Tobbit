#pragma once
#include "CCowardly.h"
#include "CCharacter.h"
#define ALPABET_FRAME_LENGTH	80

class CMonster : public CCharacter
{
private:
	CMonsterAI*		pAI;					// 인공지능 객체
	std::wstring	m_strWord;				// 몬스터 단어
	HBITMAP			m_hBitmapAlphabet;		// 알파벳 이미지
	CHero*			m_ptrHero;

protected:

public:
	CMonster(HINSTANCE hInst, int nX, int nSpeed, int nJumpHeight, int nFloor, std::wstring strImageDirectory, std::wstring strWord, CHero* ptrHero);
	~CMonster(void);
	
	void			Action();
	void			Draw(HDC hDC, HDC hMemoryDC);
};
