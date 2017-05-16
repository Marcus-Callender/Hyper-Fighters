#ifndef __EXTRA_FIGHTER_DATA__
#define __EXTRA_FIGHTER_DATA__

#include <string>

class C_LanceCharge
{
public:
	C_LanceCharge();

	void charge();
	void uncharge();
	bool getCharged();
	std::string getChargeString();

private:
	int m_charged;
};

class C_RushHeatLevel
{
public:
	C_RushHeatLevel();

	void win();
	void lose();
	float focusMultiplyer();
	int getHeatLevel();
	std::string getHeatString();

	//int getHeatLevel();

private:
	int m_heatLevel;
	int m_maxHeat;

	float m_heatFocusGain = 0.2f;
};

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

class C_DashLuckyMoves
{
public:
	C_DashLuckyMoves();

	void Reset();
	void SetLuckyMove();
	int GetLuckyMove();
	//C_Move** SetMoves(C_Move** normal, C_Move** lucky);

private:
	int m_luckyMove;
};

#endif // !__EXTRA_FIGHTER_DATA__

