#include "Lance.h"

C_LanceCharge::C_LanceCharge()
{
	m_charged = 0;
}

void C_LanceCharge::charge()
{
	m_charged = 2;
}

void C_LanceCharge::uncharge()
{
	m_charged--;

	if (m_charged < 0)
		m_charged = 0;
}

bool C_LanceCharge::getCharged()
{
	if (m_charged > 0)
		return true;

	return false;
}

std::string C_LanceCharge::getChargeString()
{
	if (m_charged > 0)
	{
		return " (charged " + std::to_string(m_charged) + ")";
	}
	else
	{
		return " (uncharged)";
	}
}

C_LanceBase::C_LanceBase(e_controlerType controler) : C_FighterBase::C_FighterBase(controler)
{
	m_charge = new C_LanceCharge();

	m_pFighterData = new C_LanceData();

	m_pFighterData->reciveCustomData(m_charge);

	m_pMoves[0] = new C_KD_instantAttack(50, 0.0f, 20.0, "Blinding cannon", m_pFighterData);
	m_pMoves[1] = new C_L_attack(18, 1.0f, 6.0, "Weak punch", m_pFighterData);
	m_pMoves[2] = new C_H_attack(23, 2.0f, 15.0, "Strong kick", m_pFighterData);
	m_pMoves[3] = new C_KD_throw(27, 3.0f, 13.0, "Grab", m_pFighterData);
	m_pMoves[4] = new C_block(0.0f, 0.0f, 2.0, "Block", m_pFighterData);
	m_pMoves[5] = new C_dodge(7.0f, 0.0f, 0.2, "Evade", m_pFighterData);

	m_pCurrentMove = m_pMoves[5];
}

std::string C_LanceBase::status()
{
	std::string statString;
	statString += m_pFighterData->getName();
	statString += ": ";
	statString += std::to_string(m_pFighterData->getHp());

	/*if (m_hp != m_previousHP)
	{
	statString += "(- ";
	statString += std::to_string(m_previousHP - m_hp);
	statString += ")";
	}*/

	statString += " (";
	statString += std::to_string(m_pFighterData->getFocus());

	/*if (m_focus != m_previousFocus)
	{
	statString += "(+ ";
	statString += std::to_string(m_focus - m_previousFocus);
	statString += ")";
	}*/

	statString += "/100)";

	statString += m_charge->getChargeString();

	//for (int z = 0; z < 3; z++)
	//{
	//	if (m_pStatuses[z] != nullptr) {
	//		statString += m_pStatuses[z]->giveSymbol();
	//	}
	//}

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

	/*for (int z = 0; z < 3; z++) {
		m_pStatus[z] = nullptr;
	}*/
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

