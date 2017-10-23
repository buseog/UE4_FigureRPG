// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "FP_Impact.generated.h"

UCLASS()
class FIGUREPROJECT_API AFP_Impact : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFP_Impact();
	enum IMPACTTYPE{FIREBALLIMPACT, ICEBALLIMPACT};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Particle)
	class UParticleSystemComponent* Particle;

	UFUNCTION()
	void OnFinished(UParticleSystemComponent* _particle);


	TMap<IMPACTTYPE, UParticleSystem*> ParticleMap;

public:
	void SetImpact(IMPACTTYPE _type);

	
	
};
