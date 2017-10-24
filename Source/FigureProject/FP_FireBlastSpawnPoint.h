// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "GameFramework/Actor.h"
#include "FP_Skill.h"
#include "FP_Player.h"
#include "FP_FireBlast.h"
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
	AFP_FireBlast* FireBlast;
	float SpawnDelay = 0.3f;
	float CurrentTime = 0.3f;
	int MaxFireBlastNum = 4;
	int CurrentFireBlastNum = 0;
};
