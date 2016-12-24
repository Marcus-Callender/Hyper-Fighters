#include "Fenrir.h"

C_FenrirBase::C_FenrirBase(e_controlerType controler) : C_FighterBase::C_FighterBase(controler)
{
	m_pFighterData = new C_FenrirData();

	m_pMoves[0] = new C_instantAttack(30, 0.0f, false, 10.0, "Midnight howl", m_pFighterData);
	m_pMoves[1] = new C_L_attack(15, 1.0f, false, 8.0, "Light jab", m_pFighterData);
	m_pMoves[2] = new C_H_attack(27, 2.0f, false, 21.0, "Heavy slash", m_pFighterData);
	m_pMoves[3] = new C_throw(24, 3.0f, true, 17.0, "Grab", m_pFighterData);
	m_pMoves[4] = new C_block(0, 0.0f, false, 2.0, "Guard", m_pFighterData);
	m_pMoves[5] = new C_dodge(8, 0.0f, false, 0.2, "Dodge", m_pFighterData);

	m_pCurrentMove = m_pMoves[1];
}

C_FenrirData::C_FenrirData()
{
	m_name = "Fenrir";
	m_hp = 100;

	m_focus = 0;
	m_knockedDown = false;
	m_maxFocus = 100;

	m_previousHP = m_hp;
	m_previousFocus = m_focus;

	for (int z = 0; z < 3; z++) {
		m_pStatuses[z] = nullptr;
	}
}

