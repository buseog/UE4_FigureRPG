// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "GameFramework/Actor.h"
#include "FP_ProximityWeapon.generated.h"

UCLASS()
class FIGUREPROJECT_API AFP_ProximityWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFP_ProximityWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Particle)
	class UParticleSystemComponent* Particle;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Particle)
	class UBoxComponent* ProxBox;

public:
	void Collision(float _DeltaTime);

};
