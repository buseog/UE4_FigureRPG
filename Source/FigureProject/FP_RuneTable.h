#include "CoreMinimal.h"

struct RED {
	const uint64 GUIDED				= 0x0000000000000001;
	const uint64 STUN				= 0x0000000000000010;
	const uint64 KNOCKBACK			= 0x0000000000000100;
	const uint64 LIFESTEAL			= 0x0000000000001000;
	const uint64 IGNITE				= 0x0000000000010000;
	const uint64 AREAUP				= 0x0000000000100000;
	const uint64 RANDOMCURSE		= 0x0000000001000000;
	const uint64 DAMAGEUP			= 0x0000000010000000;
	const uint64 DAMAGEUPTOSQARE	= 0x0000000100000000;
	const uint64 BULLETSPEEDUP		= 0x0000001000000000;

	const int MaxNum = 10;
};

struct GREEN {
	const uint64 ATTACKSPEEDUP		= 0x0000000000000001;
	const uint64 BULLETSPEEDUP		= 0x0000000000000010;
	const uint64 L					= 0x0000000000000100;
	const uint64 M					= 0x0000000000001000;
	const uint64 N					= 0x0000000000010000;
	const uint64 O					= 0x0000000000100000;
	const uint64 P					= 0x0000000001000000;
	const uint64 Q					= 0x0000000010000000;
	const uint64 R					= 0x0000000100000000;

	const int MaxNum = 9;
};

struct BLUE {
	const uint64 RANGEUP			= 0x0000000000000001;
	const uint64 BULLETSPEEDUP		= 0x0000000000000010;
	const uint64 C					= 0x0000000000000100;
	const uint64 D					= 0x0000000000001000;
	const uint64 E					= 0x0000000000010000;
	const uint64 F					= 0x0000000000100000;
	const uint64 G					= 0x0000000001000000;
	const uint64 H					= 0x0000000010000000;
	const uint64 I					= 0x0000000100000000;

	const int MaxNum = 9;
};

RED Red;
GREEN Green;
BLUE Blue;