#include "Rush.h"

C_RushBase::C_RushBase(e_Player_Type controler) : C_FighterBase::C_FighterBase(controler)
{
	m_heatLevel = new C_RushHeatLevel();

	m_pFighterData = new C_RushData();

	m_pFighterData->reciveCustomData(m_heatLevel);

	m_pMoves[0] = new C_heatAttack(30, 0.5f, false, 12.0, "Reverse meteor cannon", m_pFighterData, m_heatLevel);
	m_pMoves[1] = new C_L_attack(15, 1.0f, false, 8.0, "Light attack", m_pFighterData);
	m_pMoves[2] = new C_H_attack(23, 2.0f, false, 13.0, "Heavy attack", m_pFighterData);
	m_pMoves[3] = new C_throw(25, 3.0f, true, 18.0, "Throw", m_pFighterData);
	m_pMoves[4] = new C_parry(10, 0.0f, false, 2.0, "Light parry", m_pFighterData, LIGHT_ATTACK);
	m_pMoves[5] = new C_parry(20, 0.0f, false, 2.2, "Heavy parry", m_pFighterData, HEAVY_ATTACK);

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
		if (m_pFighterData->getFocus() > m_pFighterData->getPreviousFocus())
		{
			statString += "(+ ";
			statString += std::to_string(m_pFighterData->getFocus() - m_pFighterData->getPreviousFocus());
		}
		else
		{
			statString += "(- ";
			statString += std::to_string(m_pFighterData->getPreviousFocus() - m_pFighterData->getFocus());
		}

		statString += ")";
	}

	statString += "/100)";

	statString += m_heatLevel->getHeatString();

	for (int z = 0; z < NUMBER_OF_STATUSES; z++)
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

C_RushData::C_RushData()
{
	m_name = "Rush";
	m_hp = 100;

	C_FighterData();
}

void C_RushData::takeDamage(int ammount, bool gainMeter)
{
	C_FighterData::takeDamage(ammount, gainMeter);

	m_heatLevel->lose();
}

void C_RushData::gainFocus(int ammount)
{
	m_focus += (int)((float)ammount * m_heatLevel->focusMultiplyer());

	if (m_focus > 100)
		m_focus = 100;
}

void C_RushData::reciveCustomData(void * data)
{
	m_heatLevel = (C_RushHeatLevel*) data;
}

