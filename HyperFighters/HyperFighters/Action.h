#ifndef __ACTION_H__
#define __ACTION_H__

#include "FighterData.h"
#include "Status.h"
#include "Enums.h"

#include <string>

class C_Action
{
public:
	C_Action(int damage, float speed, double focusGain, std::string name, C_FighterData* pMe, eType type, unsigned int flag);
	~C_Action();

	virtual eResult use(C_FighterData* vs, C_Action* vsMove);
	virtual void win(C_FighterData* vs, C_Action* vsMove);
	virtual void lose(C_FighterData* vs, C_Action* vsMove);

	std::string getInfo();
	int	getDamage();
	virtual float getSpeed();
	eType getType();

protected:
	eResult UseLAttack(C_FighterData * vs, C_Action * vsMove);
	eResult UseHAttack(C_FighterData * vs, C_Action * vsMove);
	eResult UseThrow(C_FighterData * vs, C_Action * vsMove);
	eResult UseBlock(C_FighterData * vs, C_Action * vsMove);
	eResult UseCounter(C_FighterData * vs, C_Action * vsMove);
	eResult UseArmour(C_FighterData * vs, C_Action * vsMove);

	unsigned int m_myFlag;

	int m_damage;
	float m_speed;
	double m_FocusGain;
	std::string m_name;
	eType m_type;
	C_FighterData* m_pMe;
};

class C_Parry : C_Action
{

protected:
	eType m_beats;
};

class C_VampireMove : C_Action
{

protected:
	int m_lifeSteal;
};

class C_StatusMove : C_Action
{

protected:
	C_Status* m_pStatus;
};

#endif // !__ACTION_H__

