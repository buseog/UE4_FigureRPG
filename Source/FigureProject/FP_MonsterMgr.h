// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "FP_Monster.h"
#include "GameFramework/Actor.h"
#include "FP_MonsterMgr.generated.h"

UCLASS()
class FIGUREPROJECT_API AFP_MonsterMgr : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFP_MonsterMgr();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	TArray<AFP_Monster*> MonsterArray;

	float TimeAcc = 0.f;
	float MonsterSpawnTime = 1.f;
	
	
};
