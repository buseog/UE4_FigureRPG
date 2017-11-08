#include "CoreMinimal.h"

//첫번째 자리수 확률
 //두번쨰 자리수 FIXED


struct RED {
	const uint64 RANDOMEFFECT		= 0x00000001;	// 확률
	const uint64 STUN				= 0x00000010;	// 확률
	const uint64 KNOCKBACK			= 0x00000100;	// 거리
	const uint64 LIFESTEAL			= 0x00001000;	// 확정, 퍼센트
	const uint64 IGNITE				= 0x00010000;	// 확정, 상대 체력의 퍼센트
	const uint64 DAMAGEUPONIGNITE	= 0x00100000;	// 확정, 퍼센트
	const uint64 DAMAGEUPTOCIRCLE	= 0x01000000;	// 확정, 퍼센트

	const FString NAME_RANDOMEFFECT = "RANDOMEFFECT__PROBABILITY";
	const FString NAME_STUN = "STUN__PROBABILITY";
	const FString NAME_KNOCKBACK = "KNOCKBACK__FIXED";
	const FString NAME_LIFESTEAL = "LIFESTEAL__FIXED";
	const FString NAME_IGNITE = "IGNIT__FIXED";
	const FString NAME_DAMAGEUPONIGNITE = "DAMAGEUPONIGNITE__FIXED";
	const FString NAME_DAMAGEUPTOCIRCLE = "DAMAGEUPTOCIRCLE__FIXED";
};

struct GREEN {
	const uint64 ATTACKSPEEDUP		= 0x00000001;	// 스탯, 퍼센트
	const uint64 BULLETSPEEDUP		= 0x00000010;	// 스탯, 퍼센트
	const uint64 DAMAGEUP			= 0x00000100;	// 스탯, 퍼센트
	const uint64 DAMAGEUPTOSQARE	= 0x00001000;	// 확정, 퍼센트
	const uint64 ATTACKTWICE		= 0x00010000;	// 확률
	const uint64 PIERCE				= 0x00100000;	// 확정, PROJECTILE
	const uint64 DOTDAMAGEUP		= 0x01000000;	// 도트 데미지 증가(스킬)

	const FString NAME_ATTACKSPEEDUP = "ATTACKSPEEDUP__STAT";
	const FString NAME_BULLETSPEEDUP = "BULLETSPEEDUP__STAT";
	const FString NAME_DAMAGEUP = "DAMAGEUP__STAT";
	const FString NAME_DAMAGEUPTOSQARE = "DAMAGEUPTOSQARE__FIXED";
	const FString NAME_ATTACKTWICE = "ATTACKTWICE__PROBABILITY";
	const FString NAME_PIERCE = "PIERCE__FIXED_PROJECTILE";
	const FString NAME_DOTDAMAGEUP = "DOTDAMAGEUP__DOT";
};

struct BLUE {
	const uint64 RANGEUP			= 0x00000001;	// 스탯, 퍼센트
	const uint64 EXPUP				= 0x00000010;	// 획득 경험치 증가, 퍼센트
	const uint64 GUIDED				= 0x00000100;	// 확정, PROJECTILE
	const uint64 SLOW				= 0x00001000;	// 확정, 퍼센트
	const uint64 FREEZEONSLOW		= 0x00010000;	// 확률
	const uint64 AREAUP				= 0x00100000;	// AOE, 퍼센트
	const uint64 DAMAGEUPTOTRIANGLE	= 0x01000000;	// 확정, 퍼센트

	const FString NAME_RANGEUP = "RANGEUP__STAT";
	const FString NAME_EXPUP = "EXPUP__EXP";
	const FString NAME_GUIDED = "GUIDED__FIXED_PROJECTILE";
	const FString NAME_SLOW = "SLOW__FIXED";
	const FString NAME_FREEZEONSLOW = "FREEZEONSLOW__PROBABILITY";
	const FString NAME_AREAUP = "AREAUP__AOE";
	const FString NAME_DAMAGEUPTOTRIANGLE = "DAMAGEUPTOTRIANGLE__FIXED";
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