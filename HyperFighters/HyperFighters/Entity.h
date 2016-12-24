#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Enums.h"

class C_Entity
{
public:
	C_Entity();
	~C_Entity();

	void InitializeControler(e_controlerType type);
	void InitializeCharicter(e_charicterType type);

};

#endif // !__ENTITY_H__

