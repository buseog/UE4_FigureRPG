#include "CoreMinimal.h"

struct RED {
	const uint64 GUIDED				= 0x0000000000000001;
	const uint64 STUN				= 0x0000000000000010;
	const uint64 KNOCKBACK			= 0x0000000000000100;
	const uint64 LIFESTEAL			= 0x0000000000001000;
	const uint64 IGNITE				= 0x0000000000010000;
	const uint64 AREAUP				= 0x0000000000100000;
	const uint64 RANDOMEFFECT		= 0x0000000001000000;

	const int MaxNum = 7;

	const FString NAME_GUIDED = "GUIDED ";
	const FString NAME_STUN = "STUN ";
	const FString NAME_KNOCKBACK = "KNOCKBACK ";
	const FString NAME_LIFESTEAL = "LIFESTEAL ";
	const FString NAME_IGNITE = "IGNITE ";
	const FString NAME_AREAUP = "AREAUP ";
	const FString NAME_RANDOMEFFECT = "RANDOMEFFECT ";
};

struct GREEN {
	const uint64 ATTACKSPEEDUP		= 0x0000000000000001;
	const uint64 BULLETSPEEDUP		= 0x0000000000000010;
	const uint64 DAMAGEUP			= 0x0000000000000100;
	const uint64 DAMAGEUPTOSQARE	= 0x0000000000001000;
	const uint64 N					= 0x0000000000010000;
	const uint64 O					= 0x0000000000100000;
	const uint64 P					= 0x0000000001000000;

	const int MaxNum = 7;

	const FString NAME_ATTACKSPEEDUP = "ATTACKSPEEDUP ";
	const FString NAME_BULLETSPEEDUP = "BULLETSPEEDUP ";
	const FString NAME_DAMAGEUP = "DAMAGEUP ";
	const FString NAME_DAMAGEUPTOSQARE = "DAMAGEUPTOSQARE ";
	const FString NAME_N = "N ";
	const FString NAME_O = "O ";
	const FString NAME_P = "P ";
};

struct BLUE {
	const uint64 RANGEUP			= 0x0000000000000001;
	const uint64 BULLETSPEEDUP		= 0x0000000000000010;
	const uint64 C					= 0x0000000000000100;
	const uint64 D					= 0x0000000000001000;
	const uint64 E					= 0x0000000000010000;
	const uint64 F					= 0x0000000000100000;
	const uint64 G					= 0x0000000001000000;

	const int MaxNum = 7;

	const FString NAME_RANGEUP = "RANGEUP ";
	const FString NAME_BULLETSPEEDUP = "BULLETSPEEDUP ";
	const FString NAME_C = "C ";
	const FString NAME_D = "D ";
	const FString NAME_E = "E ";
	const FString NAME_F = "F ";
	const FString NAME_G = "G ";
};

RED Red;
GREEN Green;
BLUE Blue;