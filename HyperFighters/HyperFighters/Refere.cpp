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
	// this sets the fighters so if they aren't created they don't get deleted.
	m_pFighters[0] = nullptr;
	m_pFighters[1] = nullptr;
}

C_Refere::~C_Refere()
{
	for (int z = 0; z < 2; z++)
	{
		if (m_pFighters[z] != nullptr)
			delete m_pFighters[z];
	}
}

void C_Refere::Start()
{
	// This is run at the start of the battle and differentiates two charicetrs if they are the same by adding a colour to the end of there name.
	if (m_pFighters[0] && m_pFighters[1])
	{
		if (m_pFighters[0]->getFighterData()->getName() == m_pFighters[1]->getFighterData()->getName())
		{
			std::string colours[6] = { " (Turquoise)", " (Purple)", " (Yellow)", " (Orange)", " (Lime)", " (Pink)" };

			int roll = rand() % 6;

			colours[roll] = colours[5];

			int roll2 = rand() % 5;

			m_pFighters[0]->getFighterData()->addToName(colours[roll]);
			m_pFighters[1]->getFighterData()->addToName(colours[roll2]);
		}
	}

	// This loops turns for the fight until one charicters hp reaches 0.
	while (!m_pFighters[0]->getFighterData()->isKOd() && !m_pFighters[1]->getFighterData()->isKOd())
	{
		system("cls");

		HUD();
		m_pFighters[0]->input();

		system("cls");

		HUD();
		m_pFighters[1]->input();

		system("cls");

		evaluate();

		std::cout << "\n";
		system("pause");
		system("cls");
	}

	end();
}

void C_Refere::InitializeControlers(e_Player_Type type0, e_Player_Type type1)
{
	m_controler[0] = type0;
	m_controler[1] = type1;
}

void C_Refere::InitializeCharicter(int z, e_Charicter_Type charicter)
{
	if (charicter == TYPE_RUSH)
	{
		m_pFighters[z] = new C_RushBase(m_controler[z]);
	}
	else if (charicter == TYPE_LANCE)
	{
		m_pFighters[z] = new C_LanceBase(m_controler[z]);
	}
	else if (charicter == TYPE_WAVE)
	{
		m_pFighters[z] = new C_WaveBase(m_controler[z]);
	}
	else if (charicter == TYPE_DSPD_017)
	{
		m_pFighters[z] = new C_DSPD_017_Base(m_controler[z]);
	}
	else if (charicter == TYPE_DASH)
	{
		m_pFighters[z] = new C_DashBase(m_controler[z]);
	}
	else if (charicter == TYPE_TARJA)
	{
		m_pFighters[z] = new C_TarjaBase(m_controler[z]);
	}
	else if (charicter == TYPE_FENRIR)
	{
		m_pFighters[z] = new C_FenrirBase(m_controler[z]);
	}

	m_pFighters[z]->initialize();
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
	std::cout << m_pFighters[0]->status() << "   vs   " << m_pFighters[1]->status() << "\n\n";
}

// This is executed at the end of a turn to calculate results 
void C_Refere::evaluate()
{
	m_pFighters[0]->showInput();
	m_pFighters[1]->showInput();
	std::cout << "\n";

	e_Turn_Result resOne = m_pFighters[0]->use(m_pFighters[1]->getFighterData(), m_pFighters[1]->getCurrentMove());
	e_Turn_Result resTwo = m_pFighters[1]->use(m_pFighters[0]->getFighterData(), m_pFighters[0]->getCurrentMove());

	// Lets boath charicters know there move has been registered
	m_pFighters[0]->rest();
	m_pFighters[1]->rest();

	if (resOne != resTwo)
	{
		int Winner = resOne > resTwo ? 0 : 1;
		int Looser = resOne > resTwo ? 1 : 0;

		m_pFighters[Winner]->win(m_pFighters[Looser]->getFighterData(), m_pFighters[Looser]->getCurrentMove());
		m_pFighters[Looser]->lose(m_pFighters[Winner]->getFighterData(), m_pFighters[Winner]->getCurrentMove());

		// giveResult is called so the AI knows the outcome of the previous turn
		m_pFighters[Winner]->giveResult(AI_WIN, m_pFighters[Looser]->getCurrentMove()->getType());
		m_pFighters[Looser]->giveResult(AI_LOSE, m_pFighters[Winner]->getCurrentMove()->getType());
	}
	else if (resTwo == resOne)
	{
		if ((resOne == LOSE) || (resOne == SPECIAL_LOSE))
		{
			m_pFighters[0]->lose(m_pFighters[1]->getFighterData(), m_pFighters[1]->getCurrentMove());
			m_pFighters[1]->lose(m_pFighters[0]->getFighterData(), m_pFighters[0]->getCurrentMove());
		}
		else if ((resOne == WIN) || (resOne == SPECIAL_WIN))
		{
			m_pFighters[0]->win(m_pFighters[1]->getFighterData(), m_pFighters[1]->getCurrentMove());
			m_pFighters[1]->win(m_pFighters[0]->getFighterData(), m_pFighters[0]->getCurrentMove());
		}

		m_pFighters[0]->giveResult(AI_DRAW, m_pFighters[1]->getCurrentMove()->getType());
		m_pFighters[1]->giveResult(AI_DRAW, m_pFighters[0]->getCurrentMove()->getType());
	}

	m_pFighters[0]->RunStatus();
	m_pFighters[1]->RunStatus();
}

void C_Refere::end()
{
	system("cls");

	if (m_pFighters[0]->getFighterData()->getHp() > 0)
	{
		std::cout << "\n--- " << m_pFighters[0]->getFighterData()->getName() << " wins!! ---\n\n";
	}
	else if (m_pFighters[1]->getFighterData()->getHp() > 0)
	{
		std::cout << m_pFighters[1]->getFighterData()->getName() << " wins!!\n";
	}
	else
	{
		std::cout << "The match was a draw.\n";
	}

	//std::cout << "\nPress any key to continue.\n";
	system("pause");
}

