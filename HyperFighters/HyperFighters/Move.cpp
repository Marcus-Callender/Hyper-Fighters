#include "Move.h"

#include "ExtraFighterData.h"

#include <iostream>
#include <math.h>

C_Move::C_Move()
{
}

C_Move::C_Move(int damage, float speed, bool knockDown, double focusGain, std::string name, C_FighterData * pMe)
{
	m_damage = damage;
	m_speed = speed;
	m_knockDown = knockDown;
	m_FocusGain = focusGain;
	m_name = name;
	m_pMe = pMe;
}

C_Move::~C_Move()
{
}

std::string C_Move::getInfo()
{
	return m_name;
}

int C_Move::getDamage()
{
	return m_damage;
}

float C_Move::getSpeed()
{
	if (m_pMe->getKnockedDown()) {
		return m_speed + 1.0f; 
	}

	return m_speed;
}

e_Attack_Type C_Move::getType()
{
	return m_type;
}

C_L_attack::C_L_attack(int damage, float speed, bool knockDown, double focusGain, std::string name, C_FighterData * pMe) : C_Move(damage, speed, knockDown, focusGain, name, pMe)
{
	m_type = LIGHT_ATTACK;
}

e_Turn_Result C_L_attack::use(C_FighterData * vs, C_Move * vsMove)
{
	if (vsMove->getType() == THROW)
	{
		std::cout << m_pMe->getName() << " hit " << vs->getName() << "!\n";
		return WIN;
	}
	else if (vsMove->getType() == BLOCK || vsMove->getType() == DODGE)
	{
		std::cout << m_pMe->getName() << "'s move colden't hit " << vs->getName() << ".\n";
		return LOSE;
	}
	else if (vsMove->getType() == LIGHT_ATTACK || vsMove->getType() == HEAVY_ATTACK)
	{
		if (vsMove->getSpeed() < getSpeed())
		{
			std::cout << m_pMe->getName() << " got hit by " << vs->getName() << " before they could act.\n";
			return LOSE;
		}
		else if (vsMove->getSpeed() >= getSpeed())
		{
			std::cout << m_pMe->getName() << " hit " << vs->getName() << ".\n";
			return WIN;
		}
	}

	return LOSE;
}

void C_L_attack::win(C_FighterData * vs, C_Move* vsMove)
{
	vs->takeDamage(m_damage);
	m_pMe->gainFocus((int)m_FocusGain);

	if (m_knockDown)
		vs->knockDown();
}

void C_L_attack::lose(C_FighterData * vs, C_Move* vsMove)
{
}

C_H_attack::C_H_attack(int damage, float speed, bool knockDown, double focusGain, std::string name, C_FighterData * pMe) : C_Move(damage, speed, knockDown, focusGain, name, pMe)
{
	m_type = HEAVY_ATTACK;
}

e_Turn_Result C_H_attack::use(C_FighterData * vs, C_Move * vsMove)
{
	if (vsMove->getType() == THROW)
	{
		std::cout << m_pMe->getName() << " hit " << vs->getName() << "!\n";
		return WIN;
	}
	else if (vsMove->getType() == BLOCK || vsMove->getType() == DODGE)
	{
		std::cout << m_pMe->getName() << "'s move colden't hit " << vs->getName() << ".\n";
		return LOSE;
	}
	else if (vsMove->getType() == LIGHT_ATTACK || vsMove->getType() == HEAVY_ATTACK)
	{
		if (vsMove->getSpeed() < getSpeed())
		{
			std::cout << m_pMe->getName() << " got hit by " << vs->getName() << " before they could act.\n";
			return LOSE;
		}
		else if (vsMove->getSpeed() >= getSpeed())
		{
			std::cout << m_pMe->getName() << " hit " << vs->getName() << ".\n";
			return WIN;
		}
	}

	return LOSE;
}

void C_H_attack::win(C_FighterData * vs, C_Move* vsMove)
{
	vs->takeDamage(m_damage);
	m_pMe->gainFocus((int)m_FocusGain);

	if (m_knockDown)
		vs->knockDown();
}

void C_H_attack::lose(C_FighterData * vs, C_Move* vsMove)
{
}

C_throw::C_throw(int damage, float speed, bool knockDown, double focusGain, std::string name, C_FighterData * pMe) : C_Move(damage, speed, knockDown, focusGain, name, pMe)
{
	m_type = THROW;
}

e_Turn_Result C_throw::use(C_FighterData * vs, C_Move * vsMove)
{
	if (vsMove->getType() == BLOCK || vsMove->getType() == DODGE)
	{
		std::cout << m_pMe->getName() << " threw " << vs->getName() << " through there defence!\n";
		return WIN;
	}
	else if (vsMove->getType() == LIGHT_ATTACK || vsMove->getType() == HEAVY_ATTACK)
	{
		std::cout << m_pMe->getName() << " got hit by " << vs->getName() << " before they could act.\n";
		return LOSE;
	}
	else if (vsMove->getType() == THROW)
	{
		if (vsMove->getSpeed() <= getSpeed())
		{
			std::cout << m_pMe->getName() << " got hit by " << vs->getName() << " before they could act.\n";
			return LOSE;
		}
		else if (vsMove->getSpeed() > getSpeed())
		{
			std::cout << m_pMe->getName() << " threw " << vs->getName() << " before they could act.\n";
			return WIN;
		}
	}

	return LOSE;
}

void C_throw::win(C_FighterData * vs, C_Move* vsMove)
{
	vs->takeDamage(m_damage);
	m_pMe->gainFocus((int)m_FocusGain);

	if (m_knockDown)
		vs->knockDown();
}

void C_throw::lose(C_FighterData * vs, C_Move* vsMove)
{
}

C_block::C_block()
{
	m_type = BLOCK;
}

C_block::C_block(int damage, float speed, bool knockDown, double focusGain, std::string name, C_FighterData * pMe) : C_Move(damage, speed, knockDown, focusGain, name, pMe)
{
	m_type = BLOCK;
}

e_Turn_Result C_block::use(C_FighterData * vs, C_Move * vsMove)
{
	if (vsMove->getType() == LIGHT_ATTACK || vsMove->getType() == HEAVY_ATTACK)
	{
		std::cout << m_pMe->getName() << " blocked " << vs->getName() << "'s attack!\n";
		return WIN;
	}
	else if (vsMove->getType() == THROW)
	{
		std::cout << m_pMe->getName() << " got thrown by " << vs->getName() << ".\n";
		return LOSE;
	}
	else if (vsMove->getType() == BLOCK || vsMove->getType() == DODGE)
	{
		std::cout << m_pMe->getName() << " prepared for an attack from " << vs->getName() << ".\n";
		return LOSE;
	}

	return LOSE;
}

void C_block::win(C_FighterData * vs, C_Move* vsMove)
{
	m_pMe->gainFocus((int) ceil(vsMove->getDamage() * m_FocusGain));

	if (m_knockDown)
		vs->knockDown();
}

void C_block::lose(C_FighterData * vs, C_Move* vsMove)
{
}

C_dodge::C_dodge(int damage, float speed, bool knockDown, double focusGain, std::string name, C_FighterData * pMe) : C_Move(damage, speed, knockDown, focusGain, name, pMe)
{
	m_type = DODGE;
}

e_Turn_Result C_dodge::use(C_FighterData * vs, C_Move * vsMove)
{
	if (vsMove->getType() == LIGHT_ATTACK || vsMove->getType() == HEAVY_ATTACK)
	{
		std::cout << m_pMe->getName() << " dodged " << vs->getName() << "'s attack, then countered!\n";
		return WIN;
	}
	else if (vsMove->getType() == THROW)
	{
		std::cout << m_pMe->getName() << " got thrown by " << vs->getName() << ".\n";
		return LOSE;
	}
	else if (vsMove->getType() == BLOCK || vsMove->getType() == DODGE)
	{
		std::cout << m_pMe->getName() << " prepared for an attack from " << vs->getName() << ".\n";
		return LOSE;
	}

	return LOSE;
}

void C_dodge::win(C_FighterData * vs, C_Move * vsMove)
{
	vs->takeDamage(m_damage);
	m_pMe->gainFocus((int)m_FocusGain);

	if (m_knockDown)
		vs->knockDown();
}

void C_dodge::lose(C_FighterData * vs, C_Move * vsMove)
{
}

C_parry::C_parry(int damage, float speed, bool knockDown, double focusGain, std::string name, C_FighterData * pMe, e_Attack_Type parries) : C_Move(damage, speed, knockDown, focusGain, name, pMe)
{
	m_beats = parries;
	m_type = BLOCK;
}

e_Turn_Result C_parry::use(C_FighterData * vs, C_Move * vsMove)
{
	if ((vsMove->getType() == LIGHT_ATTACK) || (vsMove->getType() == HEAVY_ATTACK))
	{
		if (vsMove->getType() == m_beats)
		{
			std::cout << m_pMe->getName() << " parried " << vs->getName() << "'s attack, then retaliated with a counter attack.\n";
			return WIN;
		}
		else
		{
			std::cout << m_pMe->getName() << " miss timed there parry againsed " << vs->getName() << "'s attack.\n";
			return SPECIAL_LOSE;
		}
	}
	else if (vsMove->getType() == THROW)
	{
		std::cout << m_pMe->getName() << " got thrown by " << vs->getName() << ".\n";
		return LOSE;
	}
	else if ((vsMove->getType() == BLOCK) || (vsMove->getType() == DODGE))
	{
		std::cout << m_pMe->getName() << " prepared for an attack from " << vs->getName() << ".\n";
		return LOSE;
	}

	return LOSE;
}

void C_parry::win(C_FighterData * vs, C_Move * vsMove)
{
	m_pMe->gainFocus((int)(vsMove->getDamage() * m_FocusGain));
	vs->takeDamage(m_damage);

	if (m_knockDown)
		vs->knockDown();
}

void C_parry::lose(C_FighterData * vs, C_Move * vsMove)
{
}

C_instantAttack::C_instantAttack(int damage, float speed, bool knockDown, double focusGain, std::string name, C_FighterData * pMe) : C_H_attack(damage, speed, knockDown, focusGain, name, pMe)
{
	m_type = HEAVY_ATTACK;
}

float C_instantAttack::getSpeed()
{
	return m_speed;
}

C_counter::C_counter(int damage, float speed, bool knockDown, double focusGain, std::string name, C_FighterData * pMe) : C_Move(damage, speed, knockDown, focusGain, name, pMe)
{
	m_type = BLOCK;
}

e_Turn_Result C_counter::use(C_FighterData * vs, C_Move * vsMove)
{
	if (vsMove->getType() == LIGHT_ATTACK || vsMove->getType() == HEAVY_ATTACK)
	{
		std::cout << m_pMe->getName() << " blocked and counterd " << vs->getName() << "'s attack!\n";
		return SPECIAL_WIN;
	}
	else if (vsMove->getType() == THROW)
	{
		std::cout << m_pMe->getName() << " coulden't counter " << vs->getName() << "'s throw.\n";
		return LOSE;
	}
	else if (vsMove->getType() == BLOCK || vsMove->getType() == DODGE)
	{
		std::cout << m_pMe->getName() << " redied into a counter stance againsed " << vs->getName() << ".\n";
		return LOSE;
	}

	return LOSE;
}

void C_counter::win(C_FighterData * vs, C_Move * vsMove)
{
	vs->takeDamage(m_damage);
	m_pMe->gainFocus((int)m_FocusGain);

	if (m_knockDown)
		vs->knockDown();
}

void C_counter::lose(C_FighterData * vs, C_Move * vsMove)
{
}

C_vampireGrab::C_vampireGrab(int damage, float speed, bool knockDown, double focusGain, std::string name, C_FighterData * pMe, int lifeSteal) : C_throw(damage, speed, knockDown, focusGain, name, pMe)
{
	m_lifeSteal = lifeSteal;
}

e_Turn_Result C_vampireGrab::use(C_FighterData * vs, C_Move * vsMove)
{
	if (vsMove->getType() == BLOCK || vsMove->getType() == DODGE)
	{
		std::cout << m_pMe->getName() << " threw " << vs->getName() << " through there defence!\n";
		return WIN;
	}
	else if (vsMove->getType() == LIGHT_ATTACK)
	{
		std::cout << m_pMe->getName() << " ploughed through " << vs->getName() << "'s act.\n";
		return WIN;
	}
	else if (vsMove->getType() == HEAVY_ATTACK)
	{
		std::cout << m_pMe->getName() << " got hit by " << vs->getName() << " before they could act.\n";
		return LOSE;
	}
	else if (vsMove->getType() == THROW)
	{
		if (vsMove->getSpeed() <= getSpeed())
		{
			std::cout << m_pMe->getName() << " got hit by " << vs->getName() << " before they could act.\n";
			return LOSE;
		}
		else if (vsMove->getSpeed() > getSpeed())
		{
			std::cout << m_pMe->getName() << " threw " << vs->getName() << " before they could act.\n";
			return WIN;
		}
	}

	return LOSE;
}

void C_vampireGrab::win(C_FighterData * vs, C_Move * vsMove)
{
	C_throw::win(vs, vsMove);
	m_pMe->gainHp(m_lifeSteal);

	if (m_knockDown)
		vs->knockDown();
}

void C_vampireGrab::lose(C_FighterData * vs, C_Move * vsMove)
{
}

C_ToxicAttack::C_ToxicAttack(int damage, float speed, bool knockDown, double focusGain, std::string name, C_FighterData * pMe, C_Status * pStatus) : C_L_attack(damage, speed, knockDown, focusGain, name, pMe)
{
	m_pStatus = pStatus;
}

void C_ToxicAttack::win(C_FighterData * vs, C_Move* vsMove)
{
	C_L_attack::win(vs, vsMove);

	vs->giveStatus(m_pStatus);
}

C_VenomAttack::C_VenomAttack(int damage, float speed, bool knockDown, double focusGain, std::string name, C_FighterData * pMe, C_Status * pStatus) : C_H_attack(damage, speed, knockDown, focusGain, name, pMe)
{
	m_pStatus = pStatus;
}

void C_VenomAttack::win(C_FighterData * vs, C_Move * vsMove)
{
	C_H_attack::win(vs, vsMove);

	vs->giveStatus(m_pStatus);
}

C_ModeOn::C_ModeOn(int damage, float speed, bool knockDown, double focusGain, std::string name, C_FighterData * pMe) : C_Move(damage, speed, knockDown, focusGain, name, pMe)
{
	m_type = BLOCK;
}

e_Turn_Result C_ModeOn::use(C_FighterData* vs, C_Move* vsMove)
{
	if ((vsMove->getType() == BLOCK) || (vsMove->getType() == DODGE))
	{
		std::cout << m_name << " overloaded while " << vs->getName() << " was defending.\n";
		return SPECIAL_WIN;
	}
	else
	{
		std::cout << m_name << " overloaded before " << vs->getName() << " attacked them.\n";
		return SPECIAL_LOSE;
	}

	return SPECIAL_LOSE;
}

void C_ModeOn::win(C_FighterData* vs, C_Move* vsMove)
{
	//m_pMe->misc(true);
}

void C_ModeOn::lose(C_FighterData* vs, C_Move* vsMove)
{
}

C_ModeOff::C_ModeOff(int damage, float speed, bool knockDown, double focusGain, std::string name, C_FighterData * pMe) : C_Move(damage, speed, knockDown, focusGain, name, pMe)
{
	m_type = BLOCK;
}

e_Turn_Result C_ModeOff::use(C_FighterData* vs, C_Move* vsMove)
{
	if ((vsMove->getType() == BLOCK) || (vsMove->getType() == DODGE))
	{
		std::cout << m_name << " vented while " << vs->getName() << " was defending.\n";
		return SPECIAL_WIN;
	}
	else
	{
		std::cout << m_name << " vented and got hit by " << vs->getName() << ".\n";
		return SPECIAL_LOSE;
	}

	return SPECIAL_LOSE;
}

void C_ModeOff::win(C_FighterData* vs, C_Move* vsMove)
{
	//m_pMe->misc(false);
}

void C_ModeOff::lose(C_FighterData* vs, C_Move* vsMove)
{
	//m_pMe->misc(false);
}

C_heatAttack::C_heatAttack(int damage, float speed, bool knockDown, double focusGain, std::string name, C_FighterData * pMe, C_RushHeatLevel * pHeatLevel) : C_L_attack(damage, speed, knockDown, focusGain, name, pMe)
{
	m_pHeatLevel = pHeatLevel;
}

C_heatAttack::~C_heatAttack()
{
	m_pHeatLevel = nullptr;
}

void C_heatAttack::win(C_FighterData * vs, C_Move * vsMove)
{
	vs->takeDamage(getDamage());
	m_pMe->gainFocus((int)m_FocusGain);

	if (m_knockDown)
		vs->knockDown();
}

int C_heatAttack::getDamage()
{
	return m_damage + (m_pHeatLevel->getHeatLevel() * 5);
}
