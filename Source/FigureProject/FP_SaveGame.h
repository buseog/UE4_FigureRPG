// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FP_Player.h"
#include "GameFramework/SaveGame.h"
#include "FP_SaveGame.generated.h"


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
	
	
};
