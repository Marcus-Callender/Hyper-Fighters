#ifndef __TARJA_H__
#define __TARJA_H__

#include "FighterBase.h"

class C_TarjaBase : public C_FighterBase
{
public:
	C_TarjaBase(e_Player_Type controler);
	~C_TarjaBase();
};

class C_TarjaData : public C_FighterData
{
public:
	C_TarjaData();
	~C_TarjaData();
};

#endif // !__TARJA_H__

