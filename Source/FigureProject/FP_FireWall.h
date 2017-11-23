// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FP_Skill.h"
#include "FP_FireWall.generated.h"

/**
 * 
 */
UCLASS()
class FIGUREPROJECT_API AFP_FireWall : public AFP_Skill
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AFP_FireWall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Particle)
	class USphereComponent* ProxSphere;

	float LifeTime = 5.f;
	float CurrentTime = 0.f;
	TArray<AFP_Monster*> Targets;
	float Scale = 1.f;
	bool bStart = true;
};
