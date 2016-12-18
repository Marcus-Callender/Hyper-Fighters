#include "PlayerControler.h"

#include <iostream>
#include <conio.h>

C_PlayerControler::C_PlayerControler()
{
	m_inputs[0] = '0';
	m_inputs[1] = '1';
	m_inputs[2] = '2';
	m_inputs[3] = '3';
	m_inputs[4] = '4';
	m_inputs[5] = '5';
}

C_PlayerControler::~C_PlayerControler()
{
}

C_Move* C_PlayerControler::input(C_Move ** moves)
{
	char in = ' ';

	C_Move* move0 = moves[0];
	C_Move* move1 = moves[1];
	C_Move* move2 = moves[2];
	C_Move* move3 = moves[3];
	C_Move* move4 = moves[4];
	C_Move* move5 = moves[5];

	do
	{
		showOptions(moves);

		std::cout << ">";
		in = _getch();

		system("cls");
	} while (findInputID(in) == -1);

	return moves[findInputID(in)];
}

int C_PlayerControler::findInputID(char in)
{
	for (int z = 0; z < 6; z++)
	{
		if (in == m_inputs[z])
		{
			return z;
		}
	}

	return -1;
}

