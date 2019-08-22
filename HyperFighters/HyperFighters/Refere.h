#ifndef __REFERE_H__
#define __REFERE_H__

#include "FighterBase.h"

#include <string>

class C_Refere
{
public:
	C_Refere();
	~C_Refere();

	//void SetFighters(C_Entity* pEntities[2]);
	void Start();

	void InitializeControlers(e_controlerType type0, e_controlerType type1);
	void InitializeCharicter(int z, e_charicterType charicter);

private:
	std::string UI();
	void HUD();
	void evaluate();
	void end();

	//C_Entity* m_pEntities[2];

	e_controlerType m_controler[2];
	C_FighterBase* m_pFighters[2];
};

#endif // !__REFERE_H__

