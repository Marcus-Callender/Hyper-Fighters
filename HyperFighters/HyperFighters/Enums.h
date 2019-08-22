#ifndef __ENUMS_H__
#define __ENUMS_H__

enum eResult
{
	SP_LOSE,
	LOSE,
	WIN,
	SP_WIN
};

enum eType
{
	L_ATTACK,
	H_ATTACK,
	THROW,
	BLOCK,
	DODGE
};

enum eAI_Result
{
	AI_LOSE,
	AI_DRAW,
	AI_WIN,
	AI_RES_TOTAL,
	AI_RES_NULL
};

enum eAI_Type
{
	AI_ATTACK,
	AI_BLOCK,
	AI_THROW,
	AI_TYPE_TOTAL,
	AI_TYPE_NULL
};

enum e_controlerType
{
	TYPE_PLAYER,
	TYPE_AI
};

enum e_charicterType
{
	TYPE_RUSH,
	TYPE_LANCE,
	TYPE_WAVE,
	TYPE_DSPD_017,
	TYPE_DASH,
	TYPE_TARJA,
	TYPE_FENRIR
};

enum e_bitTypes
{
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
