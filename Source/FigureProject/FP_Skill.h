// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "FP_ComProjectile.h"
#include "FP_ComCollision.h"
#include "FP_Player.h"
#include "FP_Monster.h"
#include "FP_Weapon.h"
#include "FP_Skill.generated.h"

UCLASS()
class FIGUREPROJECT_API AFP_Skill : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFP_Skill();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetTargetDirection(FVector _location);

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Particle)
	class UParticleSystemComponent* Particle;

	//FVector TargetLocation = FVector(0.f,0.f,0.f);
	FVector TargetDirection = FVector(0.f, 0.f, 0.f);
	AFP_Player* Player;
	AFP_Weapon* Weapon;
	float Damage = 1.f;
	
};
