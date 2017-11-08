// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FP_ComCalculator.generated.h"

class AFP_Player;
class AFP_Skill;
class AFP_Monster;
UCLASS()
class FIGUREPROJECT_API AFP_ComCalculator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFP_ComCalculator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	static float CalculateFinalDamage(AFP_Player* _player, AFP_Skill* _skill, AFP_Monster* _monster);
	static float CalculateFinalRange(AFP_Player* _player, AFP_Skill* _skill, AFP_Monster* _monster);
	static float CalculateFinalSpeed(AFP_Player* _player, AFP_Skill* _skill, AFP_Monster* _monster);
	static float CalculateFinalCoolTime(AFP_Player* _player, AFP_Skill* _skill, AFP_Monster* _monster);
};
