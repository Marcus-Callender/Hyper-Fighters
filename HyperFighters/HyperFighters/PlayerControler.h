#ifndef __PLAYER_CONTROLER_H__
#define __PLAYER_CONTROLER_H__

#include "Controler.h"
#include "Move.h"

class C_PlayerControler : public C_Controler
{
public:
	
	C_PlayerControler();
	~C_PlayerControler();

	C_Move* input(C_Move ** moves);

protected:

	int findInputID(char z);

	char m_inputs[6];
};

#endif // !__PLAYER_CONTROLER_H__

