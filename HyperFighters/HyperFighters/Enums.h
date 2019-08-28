// Enums.h
// These are all the enums used throughtout the games code.

#ifndef __ENUMS_H__
#define __ENUMS_H__

const int NUMBER_OF_STATUSES = 3;

enum e_Turn_Result
{
	SPECIAL_LOSE,
	LOSE,
	WIN,
	SPECIAL_WIN
};

enum e_Attack_Type
{
	LIGHT_ATTACK,
	HEAVY_ATTACK,
	THROW,
	BLOCK,
	DODGE
};

enum e_AI_Turn_Result
{
	AI_LOSE,
	AI_DRAW,
	AI_WIN,
	AI_ATTACK_TYPE_TOTAL,
	AI_ATTACK_TYPE_NULL
};

enum e_AI_Type
{
	AI_ATTACK,
	AI_BLOCK,
	AI_THROW,
	AI_TYPE_TOTAL,
	AI_TYPE_NULL
};

enum e_Player_Type
{
	TYPE_PLAYER,
	TYPE_AI
};

enum e_Charicter_Type
{
	TYPE_RUSH,
	TYPE_LANCE,
	TYPE_WAVE,
	TYPE_DSPD_017,
	TYPE_DASH,
	TYPE_TARJA,
	TYPE_FENRIR
};

enum e_Turn_Results
{
	// These are given to the AI once the turn ends so it can predict better
	BIT_USE_L_ATTACK			= 1 << 0,
	BIT_USE_H_ATTACK			= 1 << 1,
	BIT_USE_THROW				= 1 << 2,
	BIT_USE_BLOCK				= 1 << 3,
	BIT_USE_COUNTER				= 1 << 4,
	BIT_USE_ARMOUR				= 1 << 5,

	BIT_WIN_DAMAGE				= 1 << 6,
	BIT_WIN_FOCUS_GAIN			= 1 << 7,
	BIT_WIN_BLOCK_FOCUS_GAIN	= 1 << 8,

	BIT_KNOCKDOWN				= 1 << 9,
	BIT_INSTANT					= 1 << 10,
	BIT_DISALLOW_FOCUS			= 1 << 11
};

#endif // !__ENUMS_H__
