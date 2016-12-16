#include "Dash.h"

#include <conio.h>

C_DashBase::C_DashBase(e_controlerType controler) : C_FighterBase::C_FighterBase(controler)
{
	m_pLuckyData = new C_DashLuckyMoves();

	m_pFighterData = new C_DashData();

	m_pFighterData->reciveCustomData(m_pLuckyData);

	m_pMoves[0] = new C_throw			(80, 2.2f, 10.0, "Ultimate dynamic finish", m_pFighterData);
	m_pMoves[1] = new C_L_attack		(14, 1.0f, 5.0, "Quick kick", m_pFighterData);
	m_pMoves[2] = new C_KD_H_attack		(20, 2.0f, 15.0, "Strong punch", m_pFighterData);
	m_pMoves[3] = new C_throw			(14, 3.0f, 20.0, "Hurl", m_pFighterData);
	m_pMoves[4] = new C_block			(0, 0.0f, 2.0, "Block", m_pFighterData);
	m_pMoves[5] = new C_parry			(9, 0.0f, 2.0, "Light parry", m_pFighterData, L_ATTACK);

	m_pLuckyMoves[0] = nullptr;
	m_pLuckyMoves[1] = new C_L_attack	(21, 1.0f, 8.0, ">> Quick kick <<", m_pFighterData);
	m_pLuckyMoves[2] = new C_KD_H_attack(30, 2.0f, 23.0, ">> Strong punch <<", m_pFighterData);
	m_pLuckyMoves[3] = new C_throw		(21, 3.0f, 30.0, ">> Hurl <<", m_pFighterData);
	m_pLuckyMoves[4] = new C_block		(0, 0.0f, 3.0, ">> Block <<", m_pFighterData);
	m_pLuckyMoves[5] = new C_parry		(14, 0.0f, 3.0, ">> Light parry <<", m_pFighterData, L_ATTACK);

	m_pCurrentMove = m_pMoves[1];
}

void C_DashBase::win(C_FighterData * vs, C_Move * vsMove)
{
	C_FighterBase::win(vs, vsMove);

	m_pLuckyData->Reset();
}

void C_DashBase::input()
{
	m_pControler->input(m_pLuckyData->SetMoves(m_pMoves, m_pLuckyMoves));
}

C_DashData::C_DashData()
{
	m_name = "Dash";
	m_hp = 95;

	m_focus = 0;
	m_knockedDown = false;
	m_maxFocus = 100;

	m_previousHP = m_hp;
	m_previousFocus = m_focus;

	for (int z = 0; z < 3; z++) {
		m_pStatuses[z] = nullptr;
	}
}

void C_DashData::takeDamage(int ammount, bool gainMeter)
{
	C_FighterData::takeDamage(ammount, gainMeter);

	m_pLuckyData->SetLuckyMove();
}

void C_DashData::reciveCustomData(void * data)
{
	m_pLuckyData = (C_DashLuckyMoves*)data;
}

C_DashLuckyMoves::C_DashLuckyMoves()
{
	m_luckyMove = -1;
}

void C_DashLuckyMoves::Reset()
{
	m_luckyMove = -1;
}

void C_DashLuckyMoves::SetLuckyMove()
{
	m_luckyMove = (rand() % 5) + 1;
}

int C_DashLuckyMoves::GetLuckyMove()
{
	return m_luckyMove;
}

C_Move ** C_DashLuckyMoves::SetMoves(C_Move ** normal, C_Move ** lucky)
{
	C_Move* toReturn[6];

	for (int z = 0; z < 6; z++)
	{
		if (z == m_luckyMove)
		{
			toReturn[z] = lucky[z];
		}
		else
		{
			toReturn[z] = normal[z];
		}
	}

	return toReturn;
}

