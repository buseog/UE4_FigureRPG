#include "CoreMinimal.h"

//ù��° �ڸ��� Ȯ��
 //�ι��� �ڸ��� FIXED


struct RED {
	const uint64 RANDOMEFFECT		= 0x00000001;	// Ȯ��
	const uint64 STUN				= 0x00000010;	// Ȯ��
	const uint64 KNOCKBACK			= 0x00000100;	// �Ÿ�
	const uint64 LIFESTEAL			= 0x00001000;	// Ȯ��, �ۼ�Ʈ
	const uint64 IGNITE				= 0x00010000;	// Ȯ��, ��� ü���� �ۼ�Ʈ
	const uint64 DAMAGEUPONIGNITE	= 0x00100000;	// Ȯ��, �ۼ�Ʈ
	const uint64 DAMAGEUPTOCIRCLE	= 0x01000000;	// Ȯ��, �ۼ�Ʈ

	const FString NAME_RANDOMEFFECT = "RANDOM EFFECT:PROBABILITY";
	const FString NAME_STUN = "STUN:PROBABILITY";
	const FString NAME_KNOCKBACK = "KNOCK BACK:FIXED";
	const FString NAME_LIFESTEAL = "LIFE STEAL:FIXED";
	const FString NAME_IGNITE = "IGNITE:FIXED";
	const FString NAME_DAMAGEUPONIGNITE = "DAMAGE UP ON IGNITE:FIXED";
	const FString NAME_DAMAGEUPTOCIRCLE = "DAMAGE UP TO CIRCLE:FIXED";
};

struct GREEN {
	const uint64 ATTACKSPEEDUP		= 0x00000001;	// ����, �ۼ�Ʈ
	const uint64 BULLETSPEEDUP		= 0x00000010;	// ����, �ۼ�Ʈ
	const uint64 DAMAGEUP			= 0x00000100;	// ����, �ۼ�Ʈ
	const uint64 DAMAGEUPTOSQARE	= 0x00001000;	// Ȯ��, �ۼ�Ʈ
	const uint64 ATTACKTWICE		= 0x00010000;	// Ȯ��
	const uint64 PIERCE				= 0x00100000;	// Ȯ��, PROJECTILE
	const uint64 DOTDAMAGEUP		= 0x01000000;	// ��Ʈ ������ ����(��ų)

	const FString NAME_ATTACKSPEEDUP = "ATTACK SPEED UP:STAT";
	const FString NAME_BULLETSPEEDUP = "BULLET SPEED UP:STAT";
	const FString NAME_DAMAGEUP = "DAMAGE UP:STAT";
	const FString NAME_DAMAGEUPTOSQARE = "DAMAGE UP TO SQARE:FIXED";
	const FString NAME_ATTACKTWICE = "ATTACK TWICE:PROBABILITY";
	const FString NAME_PIERCE = "PIERCE:FIXED_PROJECTILE";
	const FString NAME_DOTDAMAGEUP = "DOT DAMAGE UP:DOT";
};

struct BLUE {
	const uint64 RANGEUP			= 0x00000001;	// ����, �ۼ�Ʈ
	const uint64 EXPUP				= 0x00000010;	// ȹ�� ����ġ ����, �ۼ�Ʈ
	const uint64 GUIDED				= 0x00000100;	// Ȯ��, PROJECTILE
	const uint64 SLOW				= 0x00001000;	// Ȯ��, �ۼ�Ʈ
	const uint64 FREEZEONSLOW		= 0x00010000;	// Ȯ��
	const uint64 AREAUP				= 0x00100000;	// AOE, �ۼ�Ʈ
	const uint64 DAMAGEUPTOTRIANGLE	= 0x01000000;	// Ȯ��, �ۼ�Ʈ

	const FString NAME_RANGEUP = "RANGE UP:STAT";
	const FString NAME_EXPUP = "EXP UP:EXP";
	const FString NAME_GUIDED = "GUIDED:FIXED_PROJECTILE";
	const FString NAME_SLOW = "SLOW:FIXED";
	const FString NAME_FREEZEONSLOW = "FREEZE ON SLOW:PROBABILITY";
	const FString NAME_AREAUP = "AREA UP:AOE";
	const FString NAME_DAMAGEUPTOTRIANGLE = "DAMAGE UP TO TRIANGLE:FIXED";
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