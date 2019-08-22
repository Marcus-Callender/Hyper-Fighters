#ifndef __DASH_H__
#define __DASH_H__

#include "FighterBase.h"
#include "ExtraFighterData.h"

class C_DashBase : public C_FighterBase
{
public:
	C_DashBase(e_Player_Type controler);
	~C_DashBase();

	void win(C_FighterData* vs, C_Move* vsMove);
	void input();

private:
	C_Move* m_pLuckyMoves[6];
	C_DashLuckyMoves* m_pLuckyData;
};

class C_DashData : public C_FighterData
{
public:
	C_DashData();
	~C_DashData();

	void takeDamage(int ammount, bool gainMeter = true);

	void reciveCustomData(void* data);

	void rest();

private:
	C_DashLuckyMoves* m_pLuckyData;
};

#endif // !__DASH_H__

