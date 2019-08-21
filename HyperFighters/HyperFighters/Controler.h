// Controler.h
// This script is a base for passing player/AI iniputs to the charicter they are using.

#ifndef __CONTROLER_H__
#define __CONTROLER_H__

#include "Move.h"
#include "Enums.h"

class C_Controler
{
public:

	C_Controler();
	virtual ~C_Controler();

	virtual C_Move* input(C_Move** moves) = 0;
	virtual void result(e_Turn_Result res, C_Move * vsMove);
	void setFighter(C_FighterData* player);
	virtual void receveResult(e_AI_Turn_Result res, e_AI_Attack_Type type);

protected:

	void showOptions(C_Move** moves);

	C_FighterData* m_pPlayer;
};

#endif // !__CONTROLER_H__

