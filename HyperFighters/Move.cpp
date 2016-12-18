#include "Move.h"

#include "ExtraFighterData.h"

#include <iostream>
#include <math.h>

C_Move::C_Move()
{
}

C_Move::C_Move(int damage, float speed, double focusGain, std::string name, C_FighterData * pMe)
{
	m_damage = damage;
	m_speed = speed;
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
	return m_speed;
}

eType C_Move::getType()
{
	return m_type;
}

C_L_attack::C_L_attack(int damage, float speed, double focusGain, std::string name, C_FighterData * pMe) : C_Move(damage, speed, focusGain, name, pMe)
{
	m_type = L_ATTACK;
}

eResult C_L_attack::use(C_FighterData * vs, C_Move * vsMove)
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
	else if (vsMove->getType() == L_ATTACK || vsMove->getType() == H_ATTACK)
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
}

void C_L_attack::lose(C_FighterData * vs, C_Move* vsMove)
{
}

C_H_attack::C_H_attack(int damage, float speed, double focusGain, std::string name, C_FighterData * pMe) : C_Move(damage, speed, focusGain, name, pMe)
{
	m_type = H_ATTACK;
}

eResult C_H_attack::use(C_FighterData * vs, C_Move * vsMove)
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
	else if (vsMove->getType() == L_ATTACK || vsMove->getType() == H_ATTACK)
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
}

void C_H_attack::lose(C_FighterData * vs, C_Move* vsMove)
{
}

C_throw::C_throw(int damage, float speed, double focusGain, std::string name, C_FighterData * pMe) : C_Move(damage, speed, focusGain, name, pMe)
{
	m_type = THROW;
}

eResult C_throw::use(C_FighterData * vs, C_Move * vsMove)
{
	if (vsMove->getType() == BLOCK || vsMove->getType() == DODGE)
	{
		std::cout << m_pMe->getName() << " threw " << vs->getName() << " through there defence!\n";
		return WIN;
	}
	else if (vsMove->getType() == L_ATTACK || vsMove->getType() == H_ATTACK)
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
}

void C_throw::lose(C_FighterData * vs, C_Move* vsMove)
{
}

C_block::C_block()
{
	m_type = BLOCK;
}

C_block::C_block(int damage, float speed, double focusGain, std::string name, C_FighterData * pMe) : C_Move(damage, speed, focusGain, name, pMe)
{
	m_type = BLOCK;
}

eResult C_block::use(C_FighterData * vs, C_Move * vsMove)
{
	if (vsMove->getType() == L_ATTACK || vsMove->getType() == H_ATTACK)
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
}

void C_block::lose(C_FighterData * vs, C_Move* vsMove)
{
}

C_dodge::C_dodge(int damage, float speed, double focusGain, std::string name, C_FighterData * pMe) : C_Move(damage, speed, focusGain, name, pMe)
{
	m_type = DODGE;
}

eResult C_dodge::use(C_FighterData * vs, C_Move * vsMove)
{
	if (vsMove->getType() == L_ATTACK || vsMove->getType() == H_ATTACK)
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
}

void C_dodge::lose(C_FighterData * vs, C_Move * vsMove)
{
}

C_parry::C_parry(int damage, float speed, double focusGain, std::string name, C_FighterData * pMe, eType parries) : C_Move(damage, speed, focusGain, name, pMe)
{
	m_beats = parries;
	m_type = BLOCK;
}

eResult C_parry::use(C_FighterData * vs, C_Move * vsMove)
{
	if ((vsMove->getType() == L_ATTACK) || (vsMove->getType() == H_ATTACK))
	{
		if (vsMove->getType() == m_beats)
		{
			std::cout << m_pMe->getName() << " parried " << vs->getName() << "'s attack, then retaliated with a counter attack.\n";
			return WIN;
		}
		else
		{
			std::cout << m_pMe->getName() << " miss timed there parry againsed " << vs->getName() << "'s attack.\n";
			return SP_LOSE;
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
}

void C_parry::lose(C_FighterData * vs, C_Move * vsMove)
{
}

C_KD_throw::C_KD_throw(int damage, float speed, double focusGain, std::string name, C_FighterData * pMe) : C_throw(damage, speed, focusGain, name, pMe)
{
}

void C_KD_throw::win(C_FighterData * vs, C_Move * vsMove)
{
	C_throw::win(vs, vsMove);
	vs->knockDown();
}

C_instantAttack::C_instantAttack(int damage, float speed, double focusGain, std::string name, C_FighterData * pMe) : C_H_attack(damage, speed, focusGain, name, pMe)
{
	m_type = H_ATTACK;
}

float C_instantAttack::getSpeed()
{
	return m_speed;
}

C_KD_instantAttack::C_KD_instantAttack(int damage, float speed, double focusGain, std::string name, C_FighterData * pMe) : C_instantAttack(damage, speed, focusGain, name, pMe)
{
}

void C_KD_instantAttack::win(C_FighterData * vs, C_Move * vsMove)
{
	C_instantAttack::win(vs, vsMove);
	vs->knockDown();
}

C_KD_H_attack::C_KD_H_attack(int damage, float speed, double focusGain, std::string name, C_FighterData * pMe) : C_H_attack(damage, speed, focusGain, name, pMe)
{
}

void C_KD_H_attack::win(C_FighterData * vs, C_Move * vsMove)
{
	C_H_attack::win(vs, vsMove);
	vs->knockDown();
}

C_counter::C_counter(int damage, float speed, double focusGain, std::string name, C_FighterData * pMe) : C_Move(damage, speed, focusGain, name, pMe)
{
	m_type = BLOCK;
}

eResult C_counter::use(C_FighterData * vs, C_Move * vsMove)
{
	if (vsMove->getType() == L_ATTACK || vsMove->getType() == H_ATTACK)
	{
		std::cout << m_pMe->getName() << " blocked and counterd " << vs->getName() << "'s attack!\n";
		return SP_WIN;
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
	vs->knockDown();
}

void C_counter::lose(C_FighterData * vs, C_Move * vsMove)
{
}

C_vampireGrab::C_vampireGrab(int damage, float speed, double focusGain, std::string name, C_FighterData * pMe, int lifeSteal) : C_throw(damage, speed, focusGain, name, pMe)
{
	m_lifeSteal = lifeSteal;
}

eResult C_vampireGrab::use(C_FighterData * vs, C_Move * vsMove)
{
	if (vsMove->getType() == BLOCK || vsMove->getType() == DODGE)
	{
		std::cout << m_pMe->getName() << " threw " << vs->getName() << " through there defence!\n";
		return WIN;
	}
	else if (vsMove->getType() == L_ATTACK)
	{
		std::cout << m_pMe->getName() << " ploughed through " << vs->getName() << "'s act.\n";
		return WIN;
	}
	else if (vsMove->getType() == H_ATTACK)
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
	vs->knockDown();
}

void C_vampireGrab::lose(C_FighterData * vs, C_Move * vsMove)
{
}

C_ToxicAttack::C_ToxicAttack(int damage, float speed, double focusGain, std::string name, C_FighterData * pMe, C_Status * pStatus) : C_L_attack(damage, speed, focusGain, name, pMe)
{
	m_pStatus = pStatus;
}

void C_ToxicAttack::win(C_FighterData * vs, C_Move* vsMove)
{
	C_L_attack::win(vs, vsMove);

	vs->giveStatus(m_pStatus);
}

C_VenomAttack::C_VenomAttack(int damage, float speed, double focusGain, std::string name, C_FighterData * pMe, C_Status * pStatus) : C_H_attack(damage, speed, focusGain, name, pMe)
{
	m_pStatus = pStatus;
}

void C_VenomAttack::win(C_FighterData * vs, C_Move * vsMove)
{
	C_H_attack::win(vs, vsMove);

	vs->giveStatus(m_pStatus);
}

C_ModeOn::C_ModeOn(int damage, float speed, double focusGain, std::string name, C_FighterData * pMe) : C_Move(damage, speed, focusGain, name, pMe)
{
	m_type = BLOCK;
}

eResult C_ModeOn::use(C_FighterData* vs, C_Move* vsMove)
{
	if ((vsMove->getType() == BLOCK) || (vsMove->getType() == DODGE))
	{
		std::cout << m_name << " overloaded while " << vs->getName() << " was defending.\n";
		return SP_WIN;
	}
	else
	{
		//std::cout << m_name << " coulden't overloaded as " << vs->getName() << " attacked them.\n";
		std::cout << m_name << " overloaded before " << vs->getName() << " attacked them.\n";
		return SP_LOSE;
	}

	return SP_LOSE;
}

void C_ModeOn::win(C_FighterData* vs, C_Move* vsMove)
{
	//m_pMe->misc(true);
}

void C_ModeOn::lose(C_FighterData* vs, C_Move* vsMove)
{
}

C_ModeOff::C_ModeOff(int damage, float speed, double focusGain, std::string name, C_FighterData * pMe) : C_Move(damage, speed, focusGain, name, pMe)
{
	m_type = BLOCK;
}

eResult C_ModeOff::use(C_FighterData* vs, C_Move* vsMove)
{
	if ((vsMove->getType() == BLOCK) || (vsMove->getType() == DODGE))
	{
		std::cout << m_name << " vented while " << vs->getName() << " was defending.\n";
		return SP_WIN;
	}
	else
	{
		std::cout << m_name << " vented and got hit by " << vs->getName() << ".\n";
		return SP_LOSE;
	}

	return SP_LOSE;
}

void C_ModeOff::win(C_FighterData* vs, C_Move* vsMove)
{
	//m_pMe->misc(false);
}

void C_ModeOff::lose(C_FighterData* vs, C_Move* vsMove)
{
	//m_pMe->misc(false);
}

C_heatAttack::C_heatAttack(int damage, float speed, double focusGain, std::string name, C_FighterData * pMe, C_RushHeatLevel * pHeatLevel) : C_L_attack(damage, speed, focusGain, name, pMe)
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
}

int C_heatAttack::getDamage()
{
	return m_damage + (m_pHeatLevel->getHeatLevel() * 5);
}
