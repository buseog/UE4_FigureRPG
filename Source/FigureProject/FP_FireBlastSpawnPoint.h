// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "GameFramework/Actor.h"
#include "FP_Skill.h"
#include "FP_Player.h"
#include "FP_FireBlastSpawnPoint.generated.h"

UCLASS()
class FIGUREPROJECT_API AFP_FireBlastSpawnPoint : public AFP_Skill
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFP_FireBlastSpawnPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
public:
	AFP_Skill* FireSkill;
	float SpawnDelay = 0.3f;
	float CurrentTime = 0.3f;
	int MaxSpawnNum = 2;
	int CurrentSpawnNum = 0;
	FString SkillName = "FireBlast";
	float Scale = 0.f;

public:
	void SetSkill(FString _skillName, float _spawnDelay = 0.3f, int _maxSpawnNum = 4, float _speed = 1.f);
};
