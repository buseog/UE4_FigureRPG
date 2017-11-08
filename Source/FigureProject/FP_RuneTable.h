#include "CoreMinimal.h"


struct RED {
	const uint64 RANDOMEFFECT		= 0x0000000000000001;
	const uint64 STUN				= 0x0000000000000010;
	const uint64 KNOCKBACK			= 0x0000000000000100;
	const uint64 LIFESTEAL			= 0x0000000000001000;
	const uint64 IGNITE				= 0x0000000000010000;
	const uint64 AREAUP				= 0x0000000000100000;

	const int MaxNum = 6;

	const FString NAME_RANDOMEFFECT = "RANDOMEFFECT";
	const FString NAME_STUN = "STUN";
	const FString NAME_KNOCKBACK = "KNOCKBACK";
	const FString NAME_LIFESTEAL = "LIFESTEAL";
	const FString NAME_IGNITE = "IGNIT ";
	const FString NAME_AREAUP = "AREAUP";
};

struct GREEN {
	const uint64 ATTACKSPEEDUP		= 0x0000000000000001;
	const uint64 BULLETSPEEDUP		= 0x0000000000000010;
	const uint64 DAMAGEUP			= 0x0000000000000100;
	const uint64 DAMAGEUPTOSQARE	= 0x0000000000001000;

	const FString NAME_ATTACKSPEEDUP = "ATTACKSPEEDUP";
	const FString NAME_BULLETSPEEDUP = "BULLETSPEEDUP";
	const FString NAME_DAMAGEUP = "DAMAGEUP";
	const FString NAME_DAMAGEUPTOSQARE = "DAMAGEUPTOSQARE";
};

struct BLUE {
	const uint64 RANGEUP			= 0x0000000000000001;
	const uint64 BULLETSPEEDUP		= 0x0000000000000010;
	const uint64 GUIDED				= 0x0000000000000100;

	const FString NAME_RANGEUP = "RANGEUP";
	const FString NAME_BULLETSPEEDUP = "BULLETSPEEDUP";
	const FString NAME_GUIDED = "GUIDED";
};

struct RUNESTATRANGE
{
	struct TIER1
	{
		const float RANDOMEFFECT_MIN = 0;
		const float RANDOMEFFECT_MAX = 1;
		const float STUN_MIN = 0.5f;
		const float STUN_MAX = 1.f;
		const float LIFESTEAL_MIN = 1.f;
		const float LIFESTEAL_MAX = 2.f;
		const float IGNITE_MIN = 1.f;
		const float IGNITE_MAX = 5.f;
		const float AREAUP_MIN = 1.f;
		const float AREAUP_MAX = 2.f;
		const float ATTACKSPEEDUP_MIN = 0.1f;
		const float ATTACKSPEEDUP_MAX = 0.2f;
		const float BULLETSPEEDUP_MIN = 1.f;
		const float BULLETSPEEDUP_MAX = 2.f;
		const float DAMAGEUP_MIN = 1.f;
		const float DAMAGEUP_MAX = 2.f;
		const float DAMAGEUPTOSQARE_MIN = 2.f;
		const float DAMAGEUPTOSQARE_MAX = 3.f;
		const float RANGEUP_MIN = 1.f;
		const float RANGEUP_MAX = 2.f;
	};

	struct TIER2
	{
		const float RANDOMEFFECT_MIN = 0;
		const float RANDOMEFFECT_MAX = 1;
		const float STUN_MIN = 0.5f;
		const float STUN_MAX = 1.f;
		const float LIFESTEAL_MIN = 1.f;
		const float LIFESTEAL_MAX = 2.f;
		const float IGNITE_MIN = 1.f;
		const float IGNITE_MAX = 5.f;
		const float AREAUP_MIN = 1.f;
		const float AREAUP_MAX = 2.f;
		const float ATTACKSPEEDUP_MIN = 0.1f;
		const float ATTACKSPEEDUP_MAX = 0.2f;
		const float BULLETSPEEDUP_MIN = 1.f;
		const float BULLETSPEEDUP_MAX = 2.f;
		const float DAMAGEUP_MIN = 1.f;
		const float DAMAGEUP_MAX = 2.f;
		const float DAMAGEUPTOSQARE_MIN = 2.f;
		const float DAMAGEUPTOSQARE_MAX = 3.f;
		const float RANGEUP_MIN = 1.f;
		const float RANGEUP_MAX = 2.f;
	};

	struct TIER3
	{
		const float RANDOMEFFECT_MIN = 0;
		const float RANDOMEFFECT_MAX = 1;
		const float STUN_MIN = 0.5f;
		const float STUN_MAX = 1.f;
		const float LIFESTEAL_MIN = 1.f;
		const float LIFESTEAL_MAX = 2.f;
		const float IGNITE_MIN = 1.f;
		const float IGNITE_MAX = 5.f;
		const float AREAUP_MIN = 1.f;
		const float AREAUP_MAX = 2.f;
		const float ATTACKSPEEDUP_MIN = 0.1f;
		const float ATTACKSPEEDUP_MAX = 0.2f;
		const float BULLETSPEEDUP_MIN = 1.f;
		const float BULLETSPEEDUP_MAX = 2.f;
		const float DAMAGEUP_MIN = 1.f;
		const float DAMAGEUP_MAX = 2.f;
		const float DAMAGEUPTOSQARE_MIN = 2.f;
		const float DAMAGEUPTOSQARE_MAX = 3.f;
		const float RANGEUP_MIN = 1.f;
		const float RANGEUP_MAX = 2.f;
	};

	TIER1 Tier1;
	TIER2 Tier2;
	TIER3 Tier3;
};

RED Red;
GREEN Green;
BLUE Blue;
RUNESTATRANGE RuneStatRange;