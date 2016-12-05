#include "FighterData.h"

#include <iostream>

C_FighterData::C_FighterData()
{
	m_name = "Terriermon";
	m_hp = 4;

	m_focus = 4;
	m_knockedDown = false;
	m_maxFocus = 100;

	m_previousHP = m_hp;
	m_previousFocus = m_focus;
}

C_FighterData::~C_FighterData()
{
}

bool C_FighterData::isKOd()
{
	if (m_hp <= 0)
	{
		return true;
	}

	return false;
}

void C_FighterData::knockDown()
{
	m_knockedDown = true;
	std::cout << m_name << " got knocked down.\n";
}

void C_FighterData::gainHp(int ammount)
{
	m_hp += ammount;
}

void C_FighterData::rest()
{
	m_previousHP = m_hp;
	m_previousFocus = m_focus;

	m_knockedDown = false;
}

int C_FighterData::getHp()
{
	return m_hp;
}

int C_FighterData::getFocus()
{
	return m_focus;
}

int& C_FighterData::getFocusRef()
{
	return m_focus;
}

void C_FighterData::takeDamage(int ammount, bool gainMeter)
{
	m_hp -= ammount;

	if (gainMeter)
	{
		gainFocus((int)(ammount * 0.2f));
	}
}

std::string C_FighterData::getName()
{
	return m_name;
}

bool C_FighterData::canUseHyperSkill()
{
	if (m_focus == 100)
	{
		return true;
	}

	return false;
}

void C_FighterData::addToName(std::string add)
{
	m_name += add;
}

bool C_FighterData::getKnockedDown()
{
	return m_knockedDown;
}

void C_FighterData::useHyper()
{
	m_focus = 0;
}

void C_FighterData::takeFocusDamage(int ammount)
{
	m_focus -= ammount;

	if (m_focus < 0)
	{
		m_focus = 0;
	}
}

void C_FighterData::gainFocus(int ammount)
{
	m_focus += ammount;

	if (m_focus > m_maxFocus)
	{
		m_focus = m_maxFocus;
	}
}

void C_FighterData::giveStatus(C_Status * pStatus)
{
	bool alreadyHaveStatus = false;

	for (int z = 0; z < 3; z++)
	{
		if (m_pStatuses[z] == pStatus)
		{
			alreadyHaveStatus = true;
			break;
		}
	}

	if (!alreadyHaveStatus)
	{
		for (int z = 0; z < 3; z++)
		{
			if (m_pStatuses[z] == nullptr)
			{
				m_pStatuses[z] = pStatus;
				break;
			}
		}
	}
}

C_Status * C_FighterData::getStatus(int z)
{
	/*void* toReturn = m_pStatus;

	m_pStatus = nullptr;

	return toReturn;*/

	if (z >= 0 && z < 3)
	{
		return m_pStatuses[z];
	}

	return nullptr;
}

void C_FighterData::reciveCustomData(void *)
{
}

