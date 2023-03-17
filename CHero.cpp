#include "CHero.h"
CHero::CHero(HINSTANCE hInst, int nX, int nSpeed, int nJumpHeight, int nFloor, int nHP, std::wstring strImageDirectory) : CCharacter(nX, nSpeed, nJumpHeight, nFloor, strImageDirectory)
{
	// 액션 객체 생성											<NumAction>	<NumFrame>
	m_aAction[RIGHT_MOVE]		= new CRightMove		(	this,	8,			4,		hInst, this	);
	m_aAction[LEFT_MOVE]		= new CLeftMove			(	this,	8,			4,		hInst, this	);
	m_aAction[JUMP_RIGHT]		= new CJumpRight		(	this,	30,			1,		hInst, this	);
	m_aAction[JUMP_LEFT]		= new CJumpLeft			(	this,	30,			1,		hInst, this	);
	m_aAction[RIGHT_JUMP]		= new CRightJump		(	this,	15,			1,		hInst, this	);
	m_aAction[LEFT_JUMP]		= new CLeftJump			(	this,	15,			1,		hInst, this	);
	m_aAction[RIGHT_LANDING]	= new CRightLanding		(	this,	1,			1,		hInst, this	);
	m_aAction[LEFT_LANDING]		= new CLeftLanding		(	this,	1,			1,		hInst, this	);
	m_aAction[RIGHT_IDLE]		= new CRightIdle		(	this,	24,			8,		hInst, this	);
	m_aAction[LEFT_IDLE]		= new CLeftIdle			(	this,	24,			8,		hInst, this	);
	m_aAction[RIGHT_DIE]		= new CRightDie			(	this,	60,			5,		hInst, this	);
	m_aAction[LEFT_DIE]			= new CLeftDie			(	this,	60,			5,		hInst, this	);
	m_aAction[RIGHT_STUN]		= new CRightStun		(	this,	30,			5,		hInst, this	);
	m_aAction[LEFT_STUN]		= new CLeftStun			(	this,	30,			5,		hInst, this	);
	m_aAction[RIGHT_FALL]		= new CRightFall		(	this,	7,			1,		hInst, this	);
	m_aAction[LEFT_FALL]		= new CLeftFall			(	this,	7,			1,		hInst, this	);
	m_aAction[RIGHT_UNBEATABLE]	= new CRightUnbeatable	(	this,	120,		5,		hInst, this	);
	m_aAction[LEFT_UNBEATABLE]	= new CLeftUnbeatable	(	this,	120,		5,		hInst, this	);

	// 행동 결정자
	m_pActionDicider			= new CInputListener();

	// 주인공 고유 데이터 초기화
	m_nHP						= nHP;
	m_pActionState				= m_aAction[RIGHT_IDLE];
	m_nCurrentAction			= RIGHT_IDLE;
}

CHero::~CHero(void)
{
	delete m_pActionDicider;
}

void CHero::Action()
{
	m_pActionState->Action();
}

void CHero::Draw(HDC hDC, HDC hMemoryDC)
{
	m_pActionState->Draw(hDC, hMemoryDC);
}

void CHero::IncreaseHP()
{
	if (m_nHP < MAX_HP)
	{
		m_nHP++;
	}
}

void CHero::DecreaseHP()
{
	m_nHP--;

	if (m_nHP == 0)
	{
		ChangeAction(RIGHT_DIE);
	}
}

void CHero::Init()
{
	m_nHP		= MAX_HP;
	m_nX		= 0;
	m_nFloor	= 0;
}
