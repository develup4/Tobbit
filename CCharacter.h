#pragma once
#include "CGameObject.h"
#include "CActionDicider.h"
#define	  ACTION_END		-1

class CAction;
class CCharacter : public CGameObject
{
private:

protected:
	int					m_nX;									// x��ǥ
	int					m_nY;									// y��ǥ
	int					m_nSpeed;								// �̵� �ӷ�
	int					m_nFloor;								// ���� ����
	int					m_nCurrentAction;						// ���� �׼�
	int					m_nJumpHeight;							// ���� �ִ� ����
	int					m_nFrameCount;							// ���� ��������Ʈ ������ ��ȣ
	int					m_nActionCount;							// ���� �������� �׼� ī��Ʈ
	int					m_nJumpStartHeight;						// ���� ���۽� ����
	std::vector<int>*	m_pMapInfo;								// �� Ÿ�� ����
	std::wstring		m_strImageDirectory;					// �̹������� �ִ� �����̸�

	CAction*			m_pActionState;							// ���� ĳ���� ����
	CAction*			m_aAction[NUM_STATE];					// �׼� ��ü
	CActionDicider*		m_pActionDicider;						// �ൿ ������

public:
	CCharacter(int nX, int nSpeed, int nJumpHeight, int nFloor, std::wstring strImageDirectory);
	~CCharacter(void);
	
	virtual void		Action() = 0;
	virtual void		Draw(HDC hDC, HDC hMemoryDC) = 0;

	// ���� �Լ�
	void				SetX(int nX)							{	m_nX			= nX;			}
	void				SetY(int nY)							{	m_nY			= nY;			}
	void				SetSpeed(int nSpeed)					{	m_nSpeed		= nSpeed;		}
	void				SetJumpHeight(int nJumpHeight)			{	m_nJumpHeight	= nJumpHeight;	}
	void				SetFloor(int nFloor)					{	m_nFloor		= nFloor;		}
	void				SetJumpStartHeight(int nHeight)			{	m_nJumpStartHeight = nHeight;	}
	void				SetMapInfo(std::vector<int>* pMapInfo)	{	m_pMapInfo		= pMapInfo;		}
	int					GetX() const							{	return m_nX;					}
	int					GetY() const							{	return m_nY;					}
	int					GetSpeed() const						{	return m_nSpeed;				}
	int					GetJumpHeight() const					{	return m_nJumpHeight;			}
	int					GetFloor() const						{	return m_nFloor;				}
	int					GetJumpStartHeight() const				{	return m_nJumpStartHeight;		}
	std::vector<int>	GetMapInfo(int nFloor) const			{	return m_pMapInfo[nFloor];		}

	// ������ ����
	std::wstring		GetImageDirectory()						{	return m_strImageDirectory;		}
	int					IncreaseActionCount();
	void				IncreaseFrameCount();
	int					GetActionCount()						{	return m_nActionCount;			}
	int					GetFrameCount()							{	return m_nFrameCount;			}

	// �׼� ���� ����
	void				ChangeAction(int nAction);
	int					FindNextAction(int nCurrentAction);
	int					GetCurrentAction();
};











class CAction
{
protected:
	int				m_nNumAction;
	int				m_nNumFrame;
	HBITMAP			m_hBitmap;
	CCharacter*		m_ptrCharacter;
	CCharacter*		m_ptrTargetCharacter;

public:
	CAction(CCharacter* pCharacter, int nNumAction, int nNumFrame, CCharacter* pTargetCharacter);
	~CAction(void);

	int				GetNumAction()						{	return m_nNumAction;			}
	int				GetNumFrame()						{	return m_nNumFrame;				}
	virtual void	Action()							{									}
	void			Draw(HDC hDC, HDC hMemoryDC);		// ����ó���� ���� '��'�����Լ�
};

// Right Move Action Class
class CRightMove : public CAction
{
public:
	CRightMove(CCharacter* pCharacter, int nNumAction, int nNumFrame, HINSTANCE hInst, CCharacter* pTargetCharacter);
	~CRightMove(void);

	void	Action();
};

// Left Move Action Class
class CLeftMove : public CAction
{
public:
	CLeftMove(CCharacter* pCharacter, int nNumAction, int nNumFrame, HINSTANCE hInst, CCharacter* pTargetCharacter);
	~CLeftMove(void);

	void	Action();
};

// Jump Right Action Class
class CJumpRight : public CAction
{
public:
	CJumpRight(CCharacter* pCharacter, int nNumAction, int nNumFrame, HINSTANCE hInst, CCharacter* pTargetCharacter);
	~CJumpRight(void);

	void	Action();
};

// Jump Left Action Class
class CJumpLeft : public CAction
{
public:
	CJumpLeft(CCharacter* pCharacter, int nNumAction, int nNumFrame, HINSTANCE hInst, CCharacter* pTargetCharacter);
	~CJumpLeft(void);

	void	Action();
};

// Right Jump Action Class
class CRightJump : public CAction
{
public:
	CRightJump(CCharacter* pCharacter, int nNumAction, int nNumFrame, HINSTANCE hInst, CCharacter* pTargetCharacter);
	~CRightJump(void);

	void	Action();
};

// Left Jump Action Class
class CLeftJump : public CAction
{
public:
	CLeftJump(CCharacter* pCharacter, int nNumAction, int nNumFrame, HINSTANCE hInst, CCharacter* pTargetCharacter);
	~CLeftJump(void);

	void	Action();
};

// Right Landing Action Class
class CRightLanding : public CAction
{
public:
	CRightLanding(CCharacter* pCharacter, int nNumAction, int nNumFrame, HINSTANCE hInst, CCharacter* pTargetCharacter);
	~CRightLanding(void);

	void	Action();
};

// Left Landing Action Class
class CLeftLanding : public CAction
{
public:
	CLeftLanding(CCharacter* pCharacter, int nNumAction, int nNumFrame, HINSTANCE hInst, CCharacter* pTargetCharacter);
	~CLeftLanding(void);

	void	Action();
};

// Right Idle Action Class
class CRightIdle : public CAction
{
public:
	CRightIdle(CCharacter* pCharacter, int nNumAction, int nNumFrame, HINSTANCE hInst, CCharacter* pTargetCharacter);
	~CRightIdle(void);

	void	Action();
};

// Left Idle Action Class
class CLeftIdle : public CAction
{
public:
	CLeftIdle(CCharacter* pCharacter, int nNumAction, int nNumFrame, HINSTANCE hInst, CCharacter* pTargetCharacter);
	~CLeftIdle(void);

	void	Action();
};

// Right Die Action Class
class CRightDie : public CAction
{
public:
	CRightDie(CCharacter* pCharacter, int nNumAction, int nNumFrame, HINSTANCE hInst, CCharacter* pTargetCharacter);
	~CRightDie(void);

	void	Action();
};

// Left Die Action Class
class CLeftDie : public CAction
{
public:
	CLeftDie(CCharacter* pCharacter, int nNumAction, int nNumFrame, HINSTANCE hInst, CCharacter* pTargetCharacter);
	~CLeftDie(void);

	void	Action();
};

// Right Stun Action Class
class CRightStun : public CAction
{
public:
	CRightStun(CCharacter* pCharacter, int nNumAction, int nNumFrame, HINSTANCE hInst, CCharacter* pTargetCharacter);
	~CRightStun(void);

	void	Action();
};

// Left Stun Action Class
class CLeftStun : public CAction
{
public:
	CLeftStun(CCharacter* pCharacter, int nNumAction, int nNumFrame, HINSTANCE hInst, CCharacter* pTargetCharacter);
	~CLeftStun(void);

	void	Action();
};

// Right Fall Action Class
class CRightFall : public CAction
{
public:
	CRightFall(CCharacter* pCharacter, int nNumAction, int nNumFrame, HINSTANCE hInst, CCharacter* pTargetCharacter);
	~CRightFall(void);

	void	Action();
};

// Left Fall Action Class
class CLeftFall : public CAction
{
public:
	CLeftFall(CCharacter* pCharacter, int nNumAction, int nNumFrame, HINSTANCE hInst, CCharacter* pTargetCharacter);
	~CLeftFall(void);

	void	Action();
};

// Right Unbeatable Action Class
class CRightUnbeatable : public CAction
{
public:
	CRightUnbeatable(CCharacter* pCharacter, int nNumAction, int nNumFrame, HINSTANCE hInst, CCharacter* pTargetCharacter);
	~CRightUnbeatable(void);

	void	Action();
};

// Left Unbeatable Action Class
class CLeftUnbeatable : public CAction
{
public:
	CLeftUnbeatable(CCharacter* pCharacter, int nNumAction, int nNumFrame, HINSTANCE hInst, CCharacter* pTargetCharacter);
	~CLeftUnbeatable(void);

	void	Action();
};