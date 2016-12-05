#include "Rush.h"

C_RushHeatLevel::C_RushHeatLevel()
{
	m_heatLevel = 0;
	m_maxHeat = 5;
}

void C_RushHeatLevel::win()
{
	m_heatLevel++;

	if (m_heatLevel > m_maxHeat)
		m_heatLevel = m_maxHeat;
}

void C_RushHeatLevel::lose()
{
	m_heatLevel = 0;
}

float C_RushHeatLevel::focusMultiplyer()
{
	return 1.0f + (m_heatFocusGain * m_heatLevel);
}

std::string C_RushHeatLevel::getHeatString()
{
	return " (heat: " + std::to_string(m_heatLevel) + ")";
}

C_RushBase::C_RushBase(e_controlerType controler) : C_FighterBase::C_FighterBase(controler)
{
	m_heatLevel = new C_RushHeatLevel();

	m_pFighterData = new C_RushData();

	m_pFighterData->reciveCustomData(m_heatLevel);

	m_pMoves[0] = new C_L_attack(30, 0.5f, 12.0, "Reverse meteor cannon", m_pFighterData);
	m_pMoves[1] = new C_L_attack(15, 1.0f, 8.0, "Light attack", m_pFighterData);
	m_pMoves[2] = new C_H_attack(23, 2.0f, 13.0, "Heavy attack", m_pFighterData);
	m_pMoves[3] = new C_KD_throw(25, 3.0f, 18.0, "Throw", m_pFighterData);
	m_pMoves[4] = new C_parry(10, 0.0f, 2.0, "Light parry", m_pFighterData, L_ATTACK);
	m_pMoves[5] = new C_parry(20, 0.0f, 2.2, "Heavy parry", m_pFighterData, H_ATTACK);

	m_pCurrentMove = m_pMoves[1];
}

std::string C_RushBase::status()
{
	std::string statString;
	statString += m_pFighterData->getName();
	statString += ": ";
	statString += std::to_string(m_pFighterData->getHp());

	if (m_pFighterData->getHp() != m_pFighterData->getPreviousHp())
	{
		statString += "(- ";
		statString += std::to_string(m_pFighterData->getPreviousHp() - m_pFighterData->getHp());
		statString += ")";
	}

	statString += " (";
	statString += std::to_string(m_pFighterData->getFocus());

	if (m_pFighterData->getFocus() != m_pFighterData->getPreviousFocus())
	{
		statString += "(+ ";
		statString += std::to_string(m_pFighterData->getFocus() - m_pFighterData->getPreviousFocus());
		statString += ")";
	}

	statString += "/100)";

	statString += m_heatLevel->getHeatString();

	for (int z = 0; z < 3; z++)
	{
		if (m_pStatuses[z] != nullptr) {
			statString += m_pStatuses[z]->giveSymbol();
		}
	}

	if (m_pFighterData->getKnockedDown())
	{
		statString += " KD";
	}

	return statString;
}

void C_RushBase::win(C_FighterData * vs, C_Move * vsMove)
{
	C_FighterBase::win(vs, vsMove);

	m_heatLevel->win();
}

C_RushData::C_RushData() : C_FighterData::C_FighterData()
{
	m_name = "Rush";
	m_hp = 100;

	m_focus = 0;
	m_knockedDown = false;
	m_maxFocus = 100;

	m_previousHP = m_hp;
	m_previousFocus = m_focus;

	/**/
	for (int z = 0; z < 3; z++) {
		m_pStatuses[z] = nullptr;
	}
}

void C_RushData::takeDamage(int ammount, bool gainMeter)
{
	C_FighterData::takeDamage(ammount, gainMeter);

	m_heatLevel->lose();
}

void C_RushData::gainFocus(int ammount)
{
	m_focus += ammount * m_heatLevel->focusMultiplyer();
}

void C_RushData::reciveCustomData(void * data)
{
	m_heatLevel = (C_RushHeatLevel*) data;
}

