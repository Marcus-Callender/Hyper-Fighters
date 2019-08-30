#include "Tarja.h"

C_TarjaBase::C_TarjaBase(e_Player_Type controler) : C_FighterBase::C_FighterBase(controler)
{
	m_pFighterData = new C_TarjaData();

	m_pMoves[0] = new C_vampireGrab(30, 1.5f, true, 15.0, "Savage tornado", m_pFighterData, 15);
	m_pMoves[1] = new C_L_attack(18, 1.2f, false, 6.0, "Weak jab", m_pFighterData);
	m_pMoves[2] = new C_H_attack(24, 2.2f, true, 13.0, "Heavy rush", m_pFighterData);
	m_pMoves[3] = new C_throw(26, 3.2f, true, 14.0, "Grasp", m_pFighterData);
	m_pMoves[4] = new C_block(0, 0.2f, false, 2.0, "Defend", m_pFighterData);
	m_pMoves[5] = new C_dodge(7, 0.2f, false, 6.0, "Side step", m_pFighterData);

	m_pCurrentMove = m_pMoves[1];
}

C_TarjaData::C_TarjaData()
{
	m_name = "Tarja";
	m_hp = 105;
	
	C_FighterData();
}
