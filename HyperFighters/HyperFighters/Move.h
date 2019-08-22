// Move.h
// This script contains the base class C_Move and all classes that are derived from it.

#ifndef __MOVE_H__
#define __MOVE_H__

#include "FighterData.h"
#include "Enums.h"
#include "Status.h"
#include "ExtraFighterData.h"

class C_Move
{
public:
	C_Move();
	C_Move(int damage, float speed, bool knockDown, double focusGain, std::string name, C_FighterData* pMe);
	~C_Move();

	virtual e_Turn_Result use(C_FighterData* vs, C_Move* vsMove) = 0;
	virtual void win(C_FighterData* vs, C_Move* vsMove) = 0;
	virtual void lose(C_FighterData* vs, C_Move* vsMove) = 0;

	std::string getInfo();
	int	getDamage();
	virtual float getSpeed();
	e_Attack_Type getType();

protected:
	int m_damage;
	float m_speed;
	bool m_knockDown;
	double m_FocusGain;
	std::string m_name;
	e_Attack_Type m_type;
	C_FighterData* m_pMe;
};

class C_L_attack : public C_Move
{
public:

	C_L_attack(int damage, float speed, bool knockDown, double focusGain, std::string name, C_FighterData* pMe);

	e_Turn_Result use(C_FighterData* vs, C_Move* vsMove);

protected:

	void	win(C_FighterData* vs, C_Move* vsMove);
	void	lose(C_FighterData* vs, C_Move* vsMove);
};

class C_H_attack : public C_Move
{
public:
	C_H_attack(int damage, float speed, bool knockDown, double focusGain, std::string name, C_FighterData* pMe);

	e_Turn_Result use(C_FighterData* vs, C_Move* vsMove);

protected:
	void	win(C_FighterData* vs, C_Move* vsMove);
	void	lose(C_FighterData* vs, C_Move* vsMove);
};

class C_throw : public C_Move
{
public:
	C_throw(int damage, float speed, bool knockDown, double focusGain, std::string name, C_FighterData* pMe);

	e_Turn_Result use(C_FighterData* vs, C_Move* vsMove);

protected:
	void	win(C_FighterData* vs, C_Move* vsMove);
	void	lose(C_FighterData* vs, C_Move* vsMove);
};

class C_block : public C_Move
{
public:
	C_block();
	C_block(int damage, float speed, bool knockDown, double focusGain, std::string name, C_FighterData* pMe);

	e_Turn_Result use(C_FighterData* vs, C_Move* vsMove);

protected:
	void	win(C_FighterData* vs, C_Move* vsMove);
	void	lose(C_FighterData* vs, C_Move* vsMove);
};

class C_dodge : public C_Move
{
public:
	C_dodge(int damage, float speed, bool knockDown, double focusGain, std::string name, C_FighterData* pMe);

	e_Turn_Result use(C_FighterData* vs, C_Move* vsMove);

protected:
	void	win(C_FighterData* vs, C_Move* vsMove);
	void	lose(C_FighterData* vs, C_Move* vsMove);
};

// Used by Dash and Rush
// This move can only counter one speed of move (light or heavy)
class C_parry : public C_Move
{
public:
	C_parry(int damage, float speed, bool knockDown, double focusGain, std::string name, C_FighterData* pMe, e_Attack_Type parries);

	e_Turn_Result use(C_FighterData* vs, C_Move* vsMove);

protected:
	void	win(C_FighterData* vs, C_Move* vsMove);
	void	lose(C_FighterData* vs, C_Move* vsMove);

	e_Attack_Type m_beats;
};

// Used by Fenrir and Lance
// This move always has a speed of 0
class C_instantAttack : public C_H_attack
{
public:
	C_instantAttack(int damage, float speed, bool knockDown, double focusGain, std::string name, C_FighterData* pMe);

	float getSpeed();
};

// Used by Wave
// A special defencive move 
class C_counter : public C_Move
{
public:
	C_counter(int damage, float speed, bool knockDown, double focusGain, std::string name, C_FighterData* pMe);

	e_Turn_Result use(C_FighterData* vs, C_Move* vsMove);

protected:
	void	win(C_FighterData* vs, C_Move* vsMove);
	void	lose(C_FighterData* vs, C_Move* vsMove);
};

// Used by Tarja
// A throw move that heals on hit and will draw with light attacks
class C_vampireGrab :public C_throw
{
public:
	C_vampireGrab(int damage, float speed, bool knockDown, double focusGain, std::string name, C_FighterData* pMe, int lifeSteal);

	e_Turn_Result use(C_FighterData* vs, C_Move* vsMove);

protected:
	void	win(C_FighterData* vs, C_Move* vsMove);
	void	lose(C_FighterData* vs, C_Move* vsMove);

	int m_lifeSteal;
};

// Used by Wave
// Gives toxic status on hit
class C_ToxicAttack : public C_L_attack
{
public:
	C_ToxicAttack(int damage, float speed, bool knockDown, double focusGain, std::string name, C_FighterData* pMe, C_Status* pStatus);

protected:

	void win(C_FighterData* vs, C_Move* vsMove);

	C_Status* m_pStatus;
};

// Used by Wave
// Gives venom status on hit
class C_VenomAttack : public C_H_attack
{
public:
	C_VenomAttack(int damage, float speed, bool knockDown, double focusGain, std::string name, C_FighterData* pMe, C_Status* pStatus);

protected:

	void win(C_FighterData* vs, C_Move* vsMove);

	C_Status* m_pStatus;
};

// Used by DSPD_017
// Unique move that turns on a special form
class C_ModeOn : public C_Move
{
public:
	C_ModeOn(int damage, float speed, bool knockDown, double focusGain, std::string name, C_FighterData* pMe);

	e_Turn_Result use(C_FighterData* vs, C_Move* vsMove);

protected:
	void	win(C_FighterData* vs, C_Move* vsMove);
	void	lose(C_FighterData* vs, C_Move* vsMove);
};


// Used by DSPD_017
// Unique move that turns off a special form
class C_ModeOff : public C_Move
{
public:
	C_ModeOff(int damage, float speed, bool knockDown, double focusGain, std::string name, C_FighterData* pMe);

	e_Turn_Result use(C_FighterData* vs, C_Move* vsMove);

protected:
	void	win(C_FighterData* vs, C_Move* vsMove);
	void	lose(C_FighterData* vs, C_Move* vsMove);
};

// Used by Rush
// Damage increses with heat level
class C_heatAttack : public C_L_attack
{
public:
	C_heatAttack(int damage, float speed, bool knockDown, double focusGain, std::string name, C_FighterData* pMe, C_RushHeatLevel* pHeatLevel);
	~C_heatAttack();

	void win(C_FighterData* vs, C_Move* vsMove);

	int	getDamage();

private:
	C_RushHeatLevel* m_pHeatLevel;
};

#endif // !__MOVE_H__

