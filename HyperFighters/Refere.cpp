#include "Refere.h"

#include <iostream>
#include <stdlib.h>

#include "Enums.h"

#include "Rush.h"
#include "Lance.h"
#include "Wave.h"
#include "DSPD_017.h"
#include "Dash.h"
#include "Tarja.h"
#include "Fenrir.h"

C_Refere::C_Refere()
{
}

C_Refere::~C_Refere()
{
	for (int z = 0; z < 2; z++)
	{
		if (m_pFighters[z] != nullptr)
			delete m_pFighters[z];
	}
}

/*void C_Refere::SetFighters(C_Entity * pEntities[2])
{
	//m_pEntities[0] = pEntities[0];
	//m_pEntities[1] = pEntities[1];
}*/

void C_Refere::Start()
{
	while (!m_pFighters[0]->getFighterData()->isKOd() && !m_pFighters[1]->getFighterData()->isKOd())
	{
		system("cls");

		HUD();
		m_pFighters[0]->input();

		//CHANGE
		/*
		do {
		HUD();
		} while(m_pFighters[0]->input());
		*/

		system("cls");

		HUD();
		m_pFighters[1]->input();

		system("cls");

		evaluate();

		system("pause");
		system("cls");
	}

	end();
}

void C_Refere::InitializeControlers(e_controlerType type0, e_controlerType type1)
{
	m_controler[0] = type0;
	m_controler[1] = type1;
}

void C_Refere::InitializeCharicter(int z, e_charicterType charicter)
{
	if (charicter == TYPE_RUSH)
	{
		m_pFighters[z] = new C_RushBase(m_controler[z]);
		m_pFighters[z]->initialize();
	}
	else if (charicter == TYPE_LANCE)
	{
		m_pFighters[z] = new C_LanceBase(m_controler[z]);
		m_pFighters[z]->initialize();
	}
	else if (charicter == TYPE_WAVE)
	{
		m_pFighters[z] = new C_WaveBase(m_controler[z]);
		m_pFighters[z]->initialize();
	}
	else if (charicter == TYPE_DSPD_017)
	{
		m_pFighters[z] = new C_DSPD_017_Base(m_controler[z]);
		m_pFighters[z]->initialize();
	}
	else if (charicter == TYPE_DASH)
	{
		m_pFighters[z] = new C_DashBase(m_controler[z]);
		m_pFighters[z]->initialize();
	}
	else if (charicter == TYPE_TARJA)
	{
		m_pFighters[z] = new C_TarjaBase(m_controler[z]);
		m_pFighters[z]->initialize();
	}
	else if (charicter == TYPE_FENRIR)
	{
		m_pFighters[z] = new C_FenrirBase(m_controler[z]);
		m_pFighters[z]->initialize();
	}
}

std::string C_Refere::UI()
{
	std::string toReturn = m_pFighters[0]->status();
	toReturn += " vs ";
	toReturn += m_pFighters[1]->status();
	toReturn += "\n";

	return toReturn;
}

void C_Refere::HUD()
{
	std::cout << m_pFighters[0]->status() << "   vs   " << m_pFighters[1]->status() << "\n";
}

void C_Refere::evaluate()
{
	m_pFighters[0]->showInput();
	m_pFighters[1]->showInput();
	std::cout << "\n";

	eResult resOne = m_pFighters[0]->use(m_pFighters[1]->getFighterData(), m_pFighters[1]->getCurrentMove());
	eResult resTwo = m_pFighters[1]->use(m_pFighters[0]->getFighterData(), m_pFighters[0]->getCurrentMove());

	m_pFighters[0]->rest();
	m_pFighters[1]->rest();

	if (resOne > resTwo)
	{
		m_pFighters[0]->win(m_pFighters[1]->getFighterData(), m_pFighters[1]->getCurrentMove());
		m_pFighters[1]->lose(m_pFighters[0]->getFighterData(), m_pFighters[0]->getCurrentMove());

		m_pFighters[0]->giveResult(AI_WIN, m_pFighters[1]->getCurrentMove()->getType());
		m_pFighters[1]->giveResult(AI_LOSE, m_pFighters[0]->getCurrentMove()->getType());
	}
	else if (resTwo > resOne)
	{
		m_pFighters[1]->win(m_pFighters[0]->getFighterData(), m_pFighters[0]->getCurrentMove());
		m_pFighters[0]->lose(m_pFighters[1]->getFighterData(), m_pFighters[1]->getCurrentMove());

		m_pFighters[0]->giveResult(AI_LOSE, m_pFighters[1]->getCurrentMove()->getType());
		m_pFighters[1]->giveResult(AI_WIN, m_pFighters[0]->getCurrentMove()->getType());
	}
	else if (resTwo == resOne)
	{
		if ((resOne == LOSE) || (resOne == SP_LOSE))
		{
			m_pFighters[0]->lose(m_pFighters[1]->getFighterData(), m_pFighters[1]->getCurrentMove());
			m_pFighters[1]->lose(m_pFighters[0]->getFighterData(), m_pFighters[0]->getCurrentMove());
		}
		else if ((resOne == WIN) || (resOne == SP_WIN))
		{
			m_pFighters[0]->win(m_pFighters[1]->getFighterData(), m_pFighters[1]->getCurrentMove());
			m_pFighters[1]->win(m_pFighters[0]->getFighterData(), m_pFighters[0]->getCurrentMove());
		}

		m_pFighters[0]->giveResult(AI_DRAW, m_pFighters[1]->getCurrentMove()->getType());
		m_pFighters[1]->giveResult(AI_DRAW, m_pFighters[0]->getCurrentMove()->getType());
	}
}

void C_Refere::end()
{
	system("cls");

	if (m_pFighters[0]->getFighterData()->getHp() > 0)
	{
		std::cout << m_pFighters[0]->getFighterData()->getName() << " wins!!\n";
	}
	else if (m_pFighters[1]->getFighterData()->getHp() > 0)
	{
		std::cout << m_pFighters[1]->getFighterData()->getName() << " wins!!\n";
	}
	else
	{
		std::cout << "The match was a draw.\n";
	}

	std::cout << "Press any key to continue.\n";
	system("pause");
}

