#ifndef __LANCE_H__
#define __LANCE_H__

#include "FighterBase.h"

#include "ExtraFighterData.h"

/*class C_LanceCharge
{
public:
	C_LanceCharge();

	void charge();
	void uncharge();
	bool getCharged();
	std::string getChargeString();

private:
	int m_charged;
};*/

class C_LanceBase : public C_FighterBase
{
public:
	C_LanceBase(e_Player_Type controler);
	~C_LanceBase();

	std::string status();
	void input();

private:
	C_LanceCharge* m_charge;
};

class C_LanceData : public C_FighterData
{
public:
	C_LanceData();
	~C_LanceData();

	bool canUseHyperSkill();

	void reciveCustomData(void* data);

private:
	C_LanceCharge* m_charge;
};

#endif // !__LANCE_H__

