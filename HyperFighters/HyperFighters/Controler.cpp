#include "Controler.h"

#include <iostream>

C_Controler::C_Controler()
{
}

C_Controler::~C_Controler()
{
}

void C_Controler::result(e_Turn_Result res, C_Move * vsMove)
{
}

void C_Controler::setFighter(C_FighterData * player)
{
	m_pPlayer = player;
}

void C_Controler::receveResult(e_AI_Turn_Result res, e_AI_Type type)
{
}

void C_Controler::showOptions(C_Move** moves)
{
	std::cout << m_pPlayer->getName() << ":\n";

	for (int z = 0; z < 6; z++)
	{
		std::cout << std::to_string(z) << ": " << moves[z]->getInfo() << "\n";
	}
}

