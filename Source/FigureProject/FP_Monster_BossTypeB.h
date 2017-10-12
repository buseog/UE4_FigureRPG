// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FP_Monster.h"
#include "FP_Monster_BossTypeB.generated.h"

/**
 * 
 */
UCLASS()
class FIGUREPROJECT_API AFP_Monster_BossTypeB : public AFP_Monster
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void DecreaseSplit();
	void SetLife(int32 _life) { Life = _life; }
	void SetScale();

	float TimeAcc = 0.f;
	int32 Life = 2;
	
};
