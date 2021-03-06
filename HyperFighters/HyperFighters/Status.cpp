#include "Status.h"

C_Status::C_Status()
{
}

C_Status::~C_Status()
{
}

C_Toxic::C_Toxic()
{
	m_damage = 2;
}

std::string C_Toxic::giveSymbol()
{
	return " (T)";
}

void C_Toxic::effect(C_FighterData * affected)
{
	affected->takeFocusDamage(m_damage);
	m_damage *= 2;
}

void C_Toxic::remove()
{
	m_damage = 2;
}

C_Venom::C_Venom()
{
	m_damage = 2;
}

std::string C_Venom::giveSymbol()
{
	return " (V)";
}

void C_Venom::effect(C_FighterData * affected)
{
	affected->takeDamage(m_damage, false);
	m_damage *= 2;
}

void C_Venom::remove()
{
	m_damage = 2;
}

