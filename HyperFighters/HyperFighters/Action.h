#ifndef __ACTION_H__
#define __ACTION_H__

#include "FighterData.h"
#include "Status.h"
#include "Enums.h"

#include <string>

class C_Action
{
public:
	C_Action(int damage, float speed, double focusGain, std::string name, C_FighterData* pMe, e_Attack_Type type, unsigned int flag);
	~C_Action();

	virtual e_Turn_Result use(C_FighterData* vs, C_Action* vsMove);
	virtual void win(C_FighterData* vs, C_Action* vsMove);
	virtual void lose(C_FighterData* vs, C_Action* vsMove);

	std::string getInfo();
	int	getDamage();
	virtual float getSpeed();
	e_Attack_Type getType();

protected:
	e_Turn_Result UseLAttack(C_FighterData * vs, C_Action * vsMove);
	e_Turn_Result UseHAttack(C_FighterData * vs, C_Action * vsMove);
	e_Turn_Result UseThrow(C_FighterData * vs, C_Action * vsMove);
	e_Turn_Result UseBlock(C_FighterData * vs, C_Action * vsMove);
	e_Turn_Result UseCounter(C_FighterData * vs, C_Action * vsMove);
	e_Turn_Result UseArmour(C_FighterData * vs, C_Action * vsMove);

	unsigned int m_myFlag;

	int m_damage;
	float m_speed;
	double m_FocusGain;
	std::string m_name;
	e_Attack_Type m_type;
	C_FighterData* m_pMe;
};

class C_Parry : C_Action
{

protected:
	e_Attack_Type m_beats;
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

