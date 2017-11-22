// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FP_Player.h"
#include "GameFramework/SaveGame.h"
#include "FP_SaveGame.generated.h"

USTRUCT(BlueprintType)
struct FInventoryLoad
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, Category = Inventory)
	FColor Color;

	UPROPERTY(VisibleAnywhere, Category = Inventory)
	uint64 Property;

	UPROPERTY(VisibleAnywhere, Category = Inventory)
	float Damage;

	UPROPERTY(VisibleAnywhere, Category = Inventory)
	float Speed;

	UPROPERTY(VisibleAnywhere, Category = Inventory)
	float CoolTimeRatio;

	UPROPERTY(VisibleAnywhere, Category = Inventory)
	float Range;

	UPROPERTY(VisibleAnywhere, Category = Inventory)
	float IgniteDamage;

	UPROPERTY(VisibleAnywhere, Category = Inventory)
	float IgniteDuration;

	UPROPERTY(VisibleAnywhere, Category = Inventory)
	float SlowDamage;

	UPROPERTY(VisibleAnywhere, Category = Inventory)
	float SlowDuration;

	UPROPERTY(VisibleAnywhere, Category = Inventory)
	float FreezeProbability;

	UPROPERTY(VisibleAnywhere, Category = Inventory)
	float FreezeDuration;

	UPROPERTY(VisibleAnywhere, Category = Inventory)
	float ExpBonus;


	UPROPERTY(VisibleAnywhere, Category = Inventory)
	int Tier;

	UPROPERTY(VisibleAnywhere, Category = Inventory)
	TArray<int> Type;

	UPROPERTY(VisibleAnywhere, Category = Inventory)
	FString Name;

	UPROPERTY(VisibleAnywhere, Category = Inventory)
	FString Option1;

	UPROPERTY(VisibleAnywhere, Category = Inventory)
	FString Option2;

	UPROPERTY(VisibleAnywhere, Category = Inventory)
	FString Option3;

	UPROPERTY(VisibleAnywhere, Category = Inventory)
	float OptionVal1;

	UPROPERTY(VisibleAnywhere, Category = Inventory)
	float OptionVal2;

	UPROPERTY(VisibleAnywhere, Category = Inventory)
	float OptionVal3;

	UPROPERTY(VisibleAnywhere, Category = Inventory)
	bool bEquiped;

	UPROPERTY(VisibleAnywhere, Category = Inventory)
	int SkillIndex;

	UPROPERTY(VisibleAnywhere, Category = Inventory)
	int SocketIndex;
};

/**
 * 
 */
UCLASS()
class FIGUREPROJECT_API UFP_SaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UFP_SaveGame();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
		float Hp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
		float MaxHp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
		float HpRegen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
		float Attack = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
		float AttackRange = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
		float AttackSpeed = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
		float BulletSpeed = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
		float Critical;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
		float CriticalDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
		float Splash;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
		int PlayerType;

	//Skill
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillLv)
	int FireBall = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillLv)
	int FireBlast = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillLv)
	int FireWall = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillLv)
	int IceBall = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillLv)
	int IceBlast = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillLv)
	int IceOrb = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillLv)
	int SkillPoint = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillLv)
	int ActiveSkill;

	//Lv

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Level)
	int Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Level)
	float Exp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Level)
	float FullExp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Level)
	int Point;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gem)
	int Gem = 5;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stage)
	int Stage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stage)
	int MonsterKillCnt;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	uint32 UserIndex;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	TArray<FInventoryLoad> Inventory;
};
