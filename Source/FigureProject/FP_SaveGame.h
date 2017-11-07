// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		uint32 UserIndex;
	
	
};
