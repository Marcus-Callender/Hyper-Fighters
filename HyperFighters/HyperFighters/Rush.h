#ifndef __RUSH_H__
#define __RUSH_H__

#include "FighterBase.h"
#include "ExtraFighterData.h"

class C_RushBase : public C_FighterBase
{
public:
	C_RushBase(e_Player_Type controler);
	~C_RushBase();

	std::string status();
	void win(C_FighterData* vs, C_Move* vsMove);

private:
	C_RushHeatLevel* m_heatLevel;
};

class C_RushData : public C_FighterData
{
public:
	C_RushData();
	~C_RushData();

	void takeDamage(int ammount, bool gainMeter = true);
	void gainFocus(int ammount);

	void reciveCustomData(void* data);

private:
	C_RushHeatLevel* m_heatLevel;
};

#endif // !__RUSH_H__

