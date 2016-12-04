#ifndef __DASH_H__
#define __DASH_H__

#include "FighterBase.h"

class C_DashLuckyMoves
{
public:
	C_DashLuckyMoves();

	void Reset();
	void SetLuckyMove();
	int GetLuckyMove();
	C_Move** SetMoves(C_Move** normal, C_Move** lucky);

private:
	int m_luckyMove;
};

class C_DashBase : public C_FighterBase
{
public:
	C_DashBase(e_controlerType controler);
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

private:
	C_DashLuckyMoves* m_pLuckyData;
};

#endif // !__DASH_H__

