#include "Action.h"

#include "Enums.h"

C_Action::C_Action(int damage, float speed, double focusGain, std::string name, C_FighterData* pMe, e_Attack_Type type, unsigned int flag)
{
	m_damage = damage;
	m_speed = speed;
	m_FocusGain = focusGain;
	m_name = name;
	m_pMe = pMe;
	m_type = type;

	m_myFlag = flag;
}

C_Action::~C_Action()
{
}

e_Turn_Result C_Action::use(C_FighterData * vs, C_Action * vsMove)
{
	if (m_myFlag & BIT_USE_L_ATTACK)
		return UseLAttack(vs, vsMove);

	else if (m_myFlag & BIT_USE_H_ATTACK)
		return UseHAttack(vs, vsMove);

	else if (m_myFlag & BIT_USE_THROW)
		return UseThrow(vs, vsMove);

	else if (m_myFlag & BIT_USE_BLOCK)
		return UseBlock(vs, vsMove);

	else if (m_myFlag & BIT_USE_COUNTER)
		return UseCounter(vs, vsMove);

	else if (m_myFlag & BIT_USE_ARMOUR)
		return UseArmour(vs, vsMove);

	return SP_LOSE;
}

void C_Action::win(C_FighterData * vs, C_Action * vsMove)
{
	if (m_myFlag & BIT_WIN_DAMAGE)
	{
		if (m_myFlag & BIT_DISALLOW_FOCUS)
			vs->takeDamage(m_damage, false);
		else
			vs->takeDamage(m_damage);
	}

	if (m_myFlag & BIT_WIN_FOCUS_GAIN)
		m_pMe->gainFocus((int)m_FocusGain);

	if (m_myFlag & BIT_WIN_BLOCK_FOCUS_GAIN)
		m_pMe->gainFocus((int)(vsMove->getDamage() * m_FocusGain));

	if (m_myFlag & BIT_KNOCKDOWN)
		vs->knockDown();

}

void C_Action::lose(C_FighterData * vs, C_Action * vsMove)
{
}

std::string C_Action::getInfo()
{
	return m_name;
}

int C_Action::getDamage()
{
	return m_damage;
}

float C_Action::getSpeed()
{
	if (m_pMe->getKnockedDown() && !(m_myFlag & BIT_INSTANT))
		return m_speed + 1.0f;

	return m_speed;
}

e_Attack_Type C_Action::getType()
{
	return m_type;
}

e_Turn_Result C_Action::UseLAttack(C_FighterData * vs, C_Action * vsMove)
{
	return e_Turn_Result();
}

e_Turn_Result C_Action::UseHAttack(C_FighterData * vs, C_Action * vsMove)
{
	return e_Turn_Result();
}

e_Turn_Result C_Action::UseThrow(C_FighterData * vs, C_Action * vsMove)
{
	return e_Turn_Result();
}

e_Turn_Result C_Action::UseBlock(C_FighterData * vs, C_Action * vsMove)
{
	return e_Turn_Result();
}

e_Turn_Result C_Action::UseCounter(C_FighterData * vs, C_Action * vsMove)
{
	return e_Turn_Result();
}

e_Turn_Result C_Action::UseArmour(C_FighterData * vs, C_Action * vsMove)
{
	return e_Turn_Result();
}

