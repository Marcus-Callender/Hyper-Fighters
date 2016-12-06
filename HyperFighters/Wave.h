#ifndef __WAVE_H__
#define __WAVE_H__

#include "FighterBase.h"

class C_WaveBase : public C_FighterBase
{
public:
	C_WaveBase(e_controlerType controler);
	~C_WaveBase();
};

class C_WaveData : public C_FighterData
{
public:
	C_WaveData();
	~C_WaveData();

	void takeDamage(int ammount, bool gainMeter = true);
};

#endif // !__WAVE_H__

