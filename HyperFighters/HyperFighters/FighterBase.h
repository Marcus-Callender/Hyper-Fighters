#ifndef __FIGHTER_BASE_H__
#define __FIGHTER_BASE_H__

#include "Controler.h"
#include "Move.h"
#include "Status.h"

#include "Enums.h"

#include <string>

class C_FighterBase
{
public:
	C_FighterBase(e_Player_Type controler);
	~C_FighterBase();

	virtual void initialize();

	virtual std::string status();
	virtual void win(C_FighterData* vs, C_Move* vsMove);
	virtual void lose(C_FighterData* vs, C_Move* vsMove);
	void giveResult(e_AI_Turn_Result res, e_Attack_Type type);
	e_Turn_Result use(C_FighterData* vs, C_Move* vsMove);
	void showInput();
	virtual void input();
	void giveStatus(C_Status* pStatus);
	void removeStatus(C_Status* pStatus);
	void rest();
	void RunStatus();
	void SyncStatuses();

	C_Move* getCurrentMove();
	C_FighterData* getFighterData();

protected:

	C_Controler* m_pControler;
	C_FighterData* m_pFighterData;

	C_Move* m_pMoves[6];
	C_Move* m_pCurrentMove;
	C_Status* m_pStatuses[3];
};

#endif // !__FIGHTER_BASE_H__

