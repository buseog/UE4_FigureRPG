// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FP_Monster.h"
#include "FP_Skill.h"
#include "FP_ComMonsterStateMgr.generated.h"

UCLASS()
class FIGUREPROJECT_API AFP_ComMonsterStateMgr : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFP_ComMonsterStateMgr();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	static void StateControl(AFP_Skill* _skill, AFP_Monster* _monster);
	
};
