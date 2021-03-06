#include "DSPD_017.h"

C_DSPD_017_Base::C_DSPD_017_Base(e_Player_Type controler) : C_FighterBase::C_FighterBase(controler)
{
	m_pOverloadData = new C_DSPD_017_Overload();

	m_pFighterData = new C_DSPD_017_Data();

	m_pFighterData->reciveCustomData(m_pOverloadData);

	m_pMoves[0] = new C_ModeOn(0, 0.1f, false, 0.0, "Overload circuits", m_pFighterData);
	m_pMoves[1] = new C_L_attack(13, 1.0f, false, 7.0, "Light hit", m_pFighterData);
	m_pMoves[2] = new C_H_attack(18, 2.0f, false, 15.0, "Heavy hit", m_pFighterData);
	m_pMoves[3] = new C_throw(19, 3.0f, true, 15.0, "Suplex", m_pFighterData);
	m_pMoves[4] = new C_block(0, 0.0f, false, 2.0, "Defend", m_pFighterData);
	m_pMoves[5] = new C_dodge(5, 0.0f, false, 0.5, "Evade", m_pFighterData);

	m_pOverloadedMoves[0] = new C_ModeOff(0, 1.5f, false, 0.0, "Vent circuits", m_pFighterData);
	m_pOverloadedMoves[1] = new C_L_attack(18, 1.0f, false, 0.0, "Powered Light hit", m_pFighterData);
	m_pOverloadedMoves[2] = new C_H_attack(25, 2.0f, true, 0.0, "Powered Heavy hit", m_pFighterData);
	m_pOverloadedMoves[3] = new C_throw(23, 3.0f, true, 0.0, "Powered Suplex", m_pFighterData);
	m_pOverloadedMoves[4] = new C_block(0, 0.0f, false, 2.0, "Barier", m_pFighterData);
	m_pOverloadedMoves[5] = new C_dodge(8, 0.0f, false, 0.0, "Powered Counter", m_pFighterData);

	m_pCurrentMove = m_pMoves[1];
}

C_DSPD_017_Base::~C_DSPD_017_Base()
{
	C_FighterBase::~C_FighterBase();

	for (int z = 0; z < 6; z++)
		delete m_pOverloadedMoves[z];
}

void C_DSPD_017_Base::input()
{
	if (m_pOverloadData->Sustain(m_pFighterData->getFocusRef()))
	{
		if (m_pOverloadData->GetOverloaded())
		{
			m_pCurrentMove = m_pControler->input(m_pOverloadedMoves);
		}
		else
		{
			m_pCurrentMove = m_pControler->input(m_pMoves);
		}
	}
	else
	{
		m_pCurrentMove = m_pOverloadedMoves[0];
	}

	if (m_pCurrentMove == m_pMoves[0])
	{
		m_pOverloadData->Overload();
	}
	else if (m_pCurrentMove == m_pOverloadedMoves[0])
	{
		m_pOverloadData->VentHeat();
	}
}

C_DSPD_017_Data::C_DSPD_017_Data()
{
	m_name = "DSPD_017";
	m_hp = 115;

	C_FighterData();
}

void C_DSPD_017_Data::takeDamage(int ammount, bool gainMeter)
{
	m_hp -= (int) (ammount * m_pOverloadData->GetDamageMultiplier());
}

bool C_DSPD_017_Data::canUseHyperSkill()
{
	return m_pOverloadData->CanUseHyper(m_focus);
}

void C_DSPD_017_Data::useHyper()
{
}

void C_DSPD_017_Data::reciveCustomData(void * data)
{
	m_pOverloadData = (C_DSPD_017_Overload*)data;
}

