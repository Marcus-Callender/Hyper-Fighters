// FighterData.h
// This class stores the values the charicters use and is called to edit the values.

#ifndef __FIGHTER_DATA_H__
#define __FIGHTER_DATA_H__

#include <string>
#include "Enums.h"

class C_Status;

class C_FighterData
{
public:

	C_FighterData();
	~C_FighterData();

	bool isKOd();
	void knockDown();
	void gainHp(int ammount);
	virtual void rest();
	int getHp();
	int getPreviousHp();
	int getFocus();
	int getPreviousFocus();
	int& getFocusRef();
	virtual void takeDamage(int ammount, bool gainMeter = true);
	std::string getName();
	virtual bool canUseHyperSkill();
	void addToName(std::string add);
	bool getKnockedDown();
	virtual void useHyper();
	void takeFocusDamage(int ammount);
	virtual void gainFocus(int ammount);
	void giveStatus(C_Status* pStatus);
	void removeStatus(int z);
	C_Status* getStatus(int z);

	virtual void reciveCustomData(void* data);

protected:

	int m_hp;
	int m_previousHP;
	std::string m_name;
	int m_focus;
	int m_maxFocus;
	int m_previousFocus;
	bool m_knockedDown;
	C_Status* m_pStatuses[NUMBER_OF_STATUSES];
};

#endif // !__FIGHTER_DATA_H__

