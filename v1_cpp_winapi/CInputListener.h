#pragma once
#include <Windows.h>
#include "CActionDicider.h"

class CInputListener : public CActionDicider
{
private:

protected:

public:
	CInputListener(void);
	~CInputListener(void);

	int GetNextAction(int nCurrentAction);
};
