// Status.h
// Contains the C_Status base class and classes that derive from it.
// These are conditions that are left by some of Waves attacks
// but could be used by other charicters in the future.

#ifndef __STATUS_H__
#define __STATUS_H__

#include <string>
#include "FighterData.h"

class C_Status
{
public:
	C_Status();
	~C_Status();

	virtual std::string giveSymbol() = 0;
	virtual void effect(C_FighterData* affected) = 0;
	virtual void remove() = 0;
};

class C_Toxic :public C_Status
{
public:
	C_Toxic();

	std::string giveSymbol();
	void effect(C_FighterData* affected);
	void remove();

protected:
	int m_damage;
};

class C_Venom :public C_Status
{
public:
	C_Venom();

	std::string giveSymbol();
	void effect(C_FighterData* affected);
	void remove();

protected:
	int m_damage;
};


#endif // !__STATUS_H__

