#include "Lance.h"

C_LanceBase::C_LanceBase(e_Player_Type controler) : C_FighterBase::C_FighterBase(controler)
{
	m_charge = new C_LanceCharge();

	m_pFighterData = new C_LanceData();

	m_pFighterData->reciveCustomData(m_charge);

	m_pMoves[0] = new C_instantAttack(50, 0.0f, true, 20.0, "Blinding cannon", m_pFighterData);
	m_pMoves[1] = new C_L_attack(18, 1.0f, false, 6.0, "Weak punch", m_pFighterData);
	m_pMoves[2] = new C_H_attack(23, 2.0f, false, 15.0, "Strong kick", m_pFighterData);
	m_pMoves[3] = new C_throw(27, 3.0f, true, 13.0, "Grab", m_pFighterData);
	m_pMoves[4] = new C_block(0, 0.0f, false, 2.0, "Block", m_pFighterData);
	m_pMoves[5] = new C_dodge(0, 0.0f, false, 0.2, "Evade", m_pFighterData);

	m_pCurrentMove = m_pMoves[5];
}

std::string C_LanceBase::status()
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

	statString += m_charge->getChargeString();

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

void C_LanceBase::input()
{
	C_FighterBase::input();

	if (m_pCurrentMove == m_pMoves[5])
		m_charge->charge();
	else
		m_charge->uncharge();
}

C_LanceData::C_LanceData() : C_FighterData::C_FighterData()
{
	m_name = "Lance";
	m_hp = 110;

	m_focus = 0;
	m_knockedDown = false;
	m_maxFocus = 100;

	m_previousHP = m_hp;
	m_previousFocus = m_focus;

	for (int z = 0; z < NUMBER_OF_STATUSES; z++) {
		m_pStatuses[z] = nullptr;
	}
}

bool C_LanceData::canUseHyperSkill()
{
	if ((m_focus == 100) && m_charge->getCharged())
		return true;

	return false;
}

void C_LanceData::reciveCustomData(void * data)
{
	m_charge = (C_LanceCharge*) data;
}

