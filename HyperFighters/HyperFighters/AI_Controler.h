// AI_Controler.h
// This uses past results to predict what the opponent will do and give the counter move to the charicter 
// it is controling (past results are stored in "scores.txt")

#ifndef __AI_CONTROLER_H__
#define __AI_CONTROLER_H__

#include "Controler.h"
#include "Move.h"

#include <list>

class C_AI_Controler : public C_Controler
{
public:
	C_AI_Controler();
	~C_AI_Controler();

	C_Move* input(C_Move** moves);
	void result(e_Turn_Result res, C_Move * vsMove);
	void receveResult(e_AI_Turn_Result res, e_AI_Type type);

protected:

	int predictMoveConfidence();

	e_AI_Type findLowest();
	e_AI_Type findHighest();

	C_Move* useAttack(C_Move** moves);
	C_Move* useBlock(C_Move** moves);
	C_Move* useThrow(C_Move** moves);

	// TODO change these to arrays
	std::list <e_Turn_Result> m_eResults;
	std::list <C_Move*> m_moves;

	e_AI_Type m_previousType;
	e_AI_Turn_Result m_previousResult;

	int m_defaultMove;

	int m_data[AI_TYPE_TOTAL][AI_ATTACK_TYPE_TOTAL][AI_TYPE_TOTAL];
};

#endif // !__AI_CONTROLER_H__

