#ifndef __FIGHTER_DATA_H__
#define __FIGHTER_DATA_H__

#include <string>

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
	int getFocus();
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
	C_Status* getStatus(int z);

	virtual void reciveCustomData(void* data);

protected:

	int m_hp;
	int m_previousHP;
	//int m_maxHP;
	std::string m_name;
	int m_focus;
	int m_maxFocus;
	int m_previousFocus;
	bool m_knockedDown;
	//void* m_pStatus;
	C_Status* m_pStatuses[3];
};

#endif // !__FIGHTER_DATA_H__

