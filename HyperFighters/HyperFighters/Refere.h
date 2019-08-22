// Refere.h
// This is the script that handles the combat logic between the two charicters,
// e.g. finding the results of two actions or if a player has won
// This script also writes the results of a turn to the screen

#ifndef __REFERE_H__
#define __REFERE_H__

#include "FighterBase.h"

#include <string>

class C_Refere
{
public:
	C_Refere();
	~C_Refere();

	void Start();

	void InitializeControlers(e_Player_Type type0, e_Player_Type type1);
	void InitializeCharicter(int z, e_Charicter_Type charicter);

private:
	std::string UI();
	void HUD();
	void evaluate();
	void end();

	e_Player_Type m_controler[2];
	C_FighterBase* m_pFighters[2];
};

#endif // !__REFERE_H__

