// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FP_Skill.h"
#include "FP_GlacialSpike.generated.h"

/**
 * 
 */
UCLASS()
class FIGUREPROJECT_API AFP_GlacialSpike : public AFP_Skill
{
	GENERATED_BODY()

public:
		AFP_GlacialSpike();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Particle)
	class USphereComponent* ProxSphere;

	TArray<AFP_Monster*> Targets;
	bool isOnce = false;

};
