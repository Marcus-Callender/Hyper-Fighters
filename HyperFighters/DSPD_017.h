#ifndef __DSPD_017_H__
#define __DSPD_017_H__

#include "FighterBase.h"

class C_DSPD_017_Overload
{
public:
	C_DSPD_017_Overload();

	void Overload();
	void VentHeat();
	bool Sustain(int& heat);
	bool GetOverloaded();
	float GetDamageMultiplier();
	bool CanUseHyper(int focus);

private:
	bool m_overloaded;
	int m_heatCost;
	float m_overloadedDamage;
};

class C_DSPD_017_Base : public C_FighterBase
{
public:
	C_DSPD_017_Base(e_controlerType controler);
	~C_DSPD_017_Base();

	void input();

private:
	C_Move* m_pOverloadedMoves[6];
	C_DSPD_017_Overload* m_pOverloadData;
};

class C_DSPD_017_Data : public C_FighterData
{
public:
	C_DSPD_017_Data();
	~C_DSPD_017_Data();

	void takeDamage(int ammount, bool gainMeter = true);
	bool canUseHyperSkill();
	void useHyper();

	void reciveCustomData(void* data);

private:
	C_DSPD_017_Overload* m_pOverloadData;
};

#endif // !__DSPD_017_H__

