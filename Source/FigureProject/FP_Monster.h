// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "FP_Monster.generated.h"

UCLASS()
class FIGUREPROJECT_API AFP_Monster : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFP_Monster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	float HP;
	float Damage;
	float Speed = 10.f;
	
public:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(EditAnywhere)
	USphereComponent* SphereComponent;

	bool bDestroy = false;

public:
	virtual void BeginDestroy() override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const &DamageEvent, class AController* EventIntigator, class AActor* DamageCauser) override;
	void IncreaseStage();
};
