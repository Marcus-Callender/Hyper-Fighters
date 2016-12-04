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
	// TODO make the inputs an array

	char in = ' ';

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

