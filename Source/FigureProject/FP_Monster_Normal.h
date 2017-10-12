// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FP_Monster.h"
#include "FP_Monster_Normal.generated.h"

/**
 * 
 */
UCLASS()
class FIGUREPROJECT_API AFP_Monster_Normal : public AFP_Monster
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
};
