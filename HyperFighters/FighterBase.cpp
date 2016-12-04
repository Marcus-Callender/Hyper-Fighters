#include "FighterBase.h"

#include "AI_Controler.h"
#include "PlayerControler.h"

#include <iostream>

C_FighterBase::C_FighterBase(e_controlerType controler)
{
	if (controler == TYPE_PLAYER) {
		m_pControler = new C_PlayerControler();
	}
	else if (controler == TYPE_AI) {
		m_pControler = new C_AI_Controler();
	}
}

C_FighterBase::~C_FighterBase()
{
	if (m_pControler != nullptr)
		delete m_pControler;
}

void C_FighterBase::initialize()
{
	m_pControler->setFighter(m_pFighterData);
}

std::string C_FighterBase::status()
{
	std::string statString;
	statString += m_pFighterData->getName();
	statString += ": ";
	statString += std::to_string(m_pFighterData->getHp());

	/*if (m_hp != m_previousHP)
	{
		statString += "(- ";
		statString += std::to_string(m_previousHP - m_hp);
		statString += ")";
	}*/

	statString += " (";
	statString += std::to_string(m_pFighterData->getFocus());

	/*if (m_focus != m_previousFocus)
	{
		statString += "(+ ";
		statString += std::to_string(m_focus - m_previousFocus);
		statString += ")";
	}*/

	statString += "/100)";

	//for (int z = 0; z < 3; z++)
	//{
	//	if (m_pStatuses[z] != nullptr) {
	//		statString += m_pStatuses[z]->giveSymbol();
	//	}
	//}

	if (m_pFighterData->getKnockedDown())
	{
		statString += " KD";
	}

	return statString;
}

void C_FighterBase::win(C_FighterData * vs, C_Move* vsMove)
{
	m_pCurrentMove->win(vs, vsMove);

	m_pControler->result(WIN, vsMove);
}

void C_FighterBase::lose(C_FighterData * vs, C_Move* vsMove)
{
	m_pCurrentMove->lose(vs, vsMove);

	m_pControler->result(LOSE, vsMove);
}

void C_FighterBase::giveResult(eAI_Result res, eType type)
{
	eAI_Type convertedType = AI_TYPE_NULL;

	if (type == L_ATTACK || type == H_ATTACK)
	{
		convertedType = AI_ATTACK;
	}
	else if (type == BLOCK || type == DODGE)
	{
		convertedType = AI_BLOCK;
	}
	else if (type == THROW)
	{
		convertedType = AI_THROW;
	}

	m_pControler->receveResult(res, convertedType);
}

eResult C_FighterBase::use(C_FighterData * vs, C_Move* vsMove)
{
	return m_pCurrentMove->use(vs, vsMove);
}

void C_FighterBase::showInput()
{
	std::cout << m_pFighterData->getName() << " used " << m_pCurrentMove->getInfo() << ".\n";
}

void C_FighterBase::input()
{
	m_pCurrentMove = m_pControler->input(m_pMoves);
}

void C_FighterBase::giveStatus(/*C_Status * pStatus*/)
{
	C_Status* pStatus = static_cast<C_Status*>(m_pFighterData->getStatus());

	if (pStatus != nullptr)
	{
		bool alreadyGot = false;

		for (int z = 0; z < 3; z++)
		{
			if (m_pStatuses[z] == pStatus)
			{
				alreadyGot = true;
			}
		}

		if (!alreadyGot)
		{
			for (int z = 0; z < 3; z++)
			{
				if (m_pStatuses[z] == nullptr)
				{
					m_pStatuses[z] = pStatus;
					break;
				}
			}
		}
	}
}

void C_FighterBase::removeStatus(C_Status * pStatus)
{
	for (int z = 0; z < 3; z++)
	{
		if (m_pStatuses[z] == pStatus)
		{
			m_pStatuses[z] = nullptr;
		}
	}
}

void C_FighterBase::rest()
{
	giveStatus();

	m_pFighterData->rest();

	/*for (int z = 0; z < 3; z++)
	{
		if (m_pStatuses[z] != nullptr)
		{
			m_pStatuses[z]->effect(m_pFighterData);
		}
	}*/
}

C_FighterData * C_FighterBase::getFighterData()
{
	return m_pFighterData;
}

C_Move * C_FighterBase::getCurrentMove()
{
	return m_pCurrentMove;
}

