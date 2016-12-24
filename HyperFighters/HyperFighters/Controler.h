#ifndef __CONTROLER_H__
#define __CONTROLER_H__

#include "Move.h"
#include "Enums.h"

class C_Controler
{
public:

	C_Controler();
	~C_Controler();

	virtual C_Move* input(C_Move** moves) = 0;
	virtual void result(eResult res, C_Move * vsMove);
	void setFighter(C_FighterData* player);
	virtual void receveResult(eAI_Result res, eAI_Type type);

protected:

	void showOptions(C_Move** moves);

	C_FighterData* m_pPlayer;
};

#endif // !__CONTROLER_H__

