// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FP_Player.h"
#include "FP_Player_Circle.generated.h"

/**
 * 
 */
UCLASS()
class FIGUREPROJECT_API AFP_Player_Circle : public AFP_Player
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AFP_Player_Circle();

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
};
