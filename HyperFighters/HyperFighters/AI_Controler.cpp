#include "AI_Controler.h"

#include <conio.h>
#include <iostream>
#include <fstream>

C_AI_Controler::C_AI_Controler()
{
	for (int z = 0; z < AI_TYPE_TOTAL; z++)
	{
		for (int x = 0; x < AI_RES_TOTAL; x++)
		{
			for (int c = 0; c < AI_TYPE_TOTAL; c++)
			{
				m_data[z][x][c] = 0;
			}
		}
	}

	m_previousResult = AI_RES_NULL;
	m_previousType = AI_TYPE_NULL;

	m_defaultMove = 1;


	std::ifstream file("scores.txt");
	std::string line;

	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			std::cout << line << "\n";
		}

		file.close();
	}
}

C_AI_Controler::~C_AI_Controler()
{
	std::ofstream file("scores.txt");

	for (int z = 0; z < AI_TYPE_TOTAL; z++)
	{
		for (int x = 0; x < AI_RES_TOTAL; x++)
		{
			for (int c = 0; c < AI_TYPE_TOTAL; c++)
			{
				file << m_data[z][x][c] << "\n";
			}
		}
	}
}

C_Move * C_AI_Controler::input(C_Move ** moves)
{
	C_Move* toReturn = nullptr;

	int predictions = predictMoveConfidence();

	showOptions(moves);

	if (predictions == 3)
	{
		toReturn = moves[m_defaultMove];
	}
	else if (predictions == 2)
	{
		eAI_Type lowest = findLowest();

		if (lowest == AI_ATTACK)
		{
			toReturn = useThrow(moves);
		}
		else if (lowest == AI_BLOCK)
		{
			toReturn = useAttack(moves);
		}
		else if (lowest == AI_THROW)
		{
			toReturn = useBlock(moves);
		}
	}
	else if (predictions == 1)
	{
		eAI_Type highist = findHighest();

		if (highist == AI_ATTACK)
		{
			toReturn = useBlock(moves);
		}
		else if (highist == AI_BLOCK)
		{
			toReturn = useThrow(moves);
		}
		else if (highist == AI_THROW)
		{
			toReturn = useAttack(moves);
		}
	}

	std::cout << "...Decideing.\n>";
	_getch();

	return toReturn;
}

void C_AI_Controler::result(eResult res, C_Move * vsMove)
{
	m_eResults.push_back(res);
	m_moves.push_back(vsMove);
}

void C_AI_Controler::receveResult(eAI_Result res, eAI_Type type)
{
	if (m_previousType != AI_TYPE_NULL && m_previousResult != AI_RES_NULL)
	{
		m_data[m_previousType][m_previousResult][type]++;
	}

	m_previousResult = res;
	m_previousType = type;
}

int C_AI_Controler::predictMoveConfidence()
{
	int _attacks = m_data[m_previousType][m_previousResult][AI_ATTACK];
	int _blocks = m_data[m_previousType][m_previousResult][AI_BLOCK];
	int _throws = m_data[m_previousType][m_previousResult][AI_THROW];

	if (_attacks == _blocks && _blocks == _throws)
	{
		return 3;
	}
	else if (_attacks != _blocks && _blocks != _throws && _throws != _attacks)
	{
		return 1;
	}
	else
	{
		return 2;
	}

	return 0;
}

eAI_Type C_AI_Controler::findLowest()
{
	eAI_Type lowest = AI_ATTACK;

	for (int z = 1; z < AI_TYPE_TOTAL; z++)
	{
		if (m_data[m_previousType][m_previousResult][z] < m_data[m_previousType][m_previousResult][lowest])
		{
			lowest = (eAI_Type)z;
		}
	}

	return lowest;
}

eAI_Type C_AI_Controler::findHighest()
{
	eAI_Type highest = AI_ATTACK;

	for (int z = 1; z < AI_TYPE_TOTAL; z++)
	{
		if (m_data[m_previousType][m_previousResult][z] > m_data[m_previousType][m_previousResult][highest])
		{
			highest = (eAI_Type)z;
		}
	}

	return highest;
}

C_Move* C_AI_Controler::useAttack(C_Move ** moves)
{
	if (m_pPlayer->canUseHyperSkill())
	{
		if (moves[0]->getType() == L_ATTACK || moves[0]->getType() == H_ATTACK)
		{
			return moves[0];
		}
	}

	return moves[(rand() % 2) + 1];
}

C_Move * C_AI_Controler::useBlock(C_Move ** moves)
{
	if (m_pPlayer->canUseHyperSkill())
	{
		if (moves[0]->getType() == BLOCK || moves[0]->getType() == DODGE)
		{
			return moves[0];
		}
	}

	return moves[(rand() % 2) + 4];
}

C_Move * C_AI_Controler::useThrow(C_Move ** moves)
{
	if (m_pPlayer->canUseHyperSkill())
	{
		if (moves[0]->getType() == THROW)
		{
			return moves[0];
		}
	}

	return moves[3];
}
