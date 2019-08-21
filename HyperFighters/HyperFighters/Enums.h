// Enums.h
// These are all the enums used throughtout the games code.

#ifndef __ENUMS_H__
#define __ENUMS_H__

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
	AI_RESULT_TOTAL,
	AI_RESULT_NULL
};

enum e_AI_Attack_Type
{
	AI_ATTACK,
	AI_BLOCK,
	AI_THROW,
	AI_ATTACK_TYPE_TOTAL,
	AI_ATTACK_TYPE_NULL
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

#endif // !__ENUMS_H__
