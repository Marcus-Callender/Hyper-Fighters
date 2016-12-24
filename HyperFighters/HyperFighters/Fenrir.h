#ifndef __FENRIR_H__
#define __FENRIR_H__

#include "FighterBase.h"

class C_FenrirBase : public C_FighterBase
{
public:
	C_FenrirBase(e_controlerType controler);
	~C_FenrirBase();
};

class C_FenrirData : public C_FighterData
{
public:
	C_FenrirData();
	~C_FenrirData();
};

#endif // !__FENRIR_H__

