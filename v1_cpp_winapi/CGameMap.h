#pragma once
#include "CItem.h"
#include "CMonster.h"

#define EMPTY_TILE		0
#define EXIST_TILE		1
#define ITEM_CODE		2

class CGameMap : public CGameObject
{
private:
	CHero*						m_ptrHero;							// ���ΰ� ��ü ������

	std::vector<int>			m_vecTileOnTheFloor[NUM_FLOOR];		// Ÿ�ϸ� �迭
	int							m_nTileWidth;						// Ÿ�� ���α���
	int							m_nStage;							// �������� ��ȣ

	int							m_nForegroundImageWidth;			// ���� �̹��� �ʺ�
	int							m_nBackgroundImageWidth;			// ��� �̹��� �ʺ�
	int							m_nScrollSpeedDifference;			// ��ũ�� �ӵ���

	HBITMAP						m_hBitmapFixedBackground;			// ���� ��� ��Ʈ�� �ڵ鷯
	HBITMAP						m_hBitmapBackground;				// ��� ��Ʈ�� �ڵ鷯
	HBITMAP						m_hBitmapForeground;				// ���� ��Ʈ�� �ڵ鷯
	HBITMAP						m_hBitmapLogTree;					// �볪�� ��Ʈ�� �ڵ鷯

	std::vector<CItem*>			m_vecItem;							// ������ ��ü �����̳�
	std::vector<CMonster*>		m_vecMonster;						// ���� ��ü �����̳�
	
protected:

public:
	CGameMap(CHero* pHero, HINSTANCE hInst);
	~CGameMap(void);
	
	void						Action();
	void						Draw(HDC hDC, HDC hMemoryDC);

	bool						LoadMapScript(HINSTANCE hInst);
	bool						IsStageClear();
	
	void						SetStage(int nStage)				{	m_nStage = nStage;		}
	int							GetStage() const					{	return m_nStage;		}
};