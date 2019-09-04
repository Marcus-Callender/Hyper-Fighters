#include "Wave.h"

C_WaveBase::C_WaveBase(e_Player_Type controler) : C_FighterBase::C_FighterBase(controler)
{
	m_pFighterData = new C_WaveData();

	C_Status* m_pToxic = new C_Toxic();
	C_Status* m_pVenom = new C_Venom();

	m_pMoves[0] = new C_counter(65, 0.0f, true, 20.0, "1000 eyes moon storm", m_pFighterData);
	m_pMoves[1] = new C_ToxicAttack(12, 0.8f, false, 9.0, "Quick jab", m_pFighterData, m_pToxic);
	m_pMoves[2] = new C_VenomAttack(18, 1.8f, false, 16.0, "Strong stab", m_pFighterData, m_pVenom);
	m_pMoves[3] = new C_throw(20, 2.8f, true, 16.0, "Shove", m_pFighterData);
	m_pMoves[4] = new C_block(0, 0.0f, true, 2.0, "Guard", m_pFighterData);
	m_pMoves[5] = new C_dodge(8, 0.0f, false, 0.2, "Roll", m_pFighterData);

	m_pCurrentMove = m_pMoves[1];
}

C_WaveData::C_WaveData()
{
	m_name = "Wave";
	m_hp = 90;

	C_FighterData();
}
