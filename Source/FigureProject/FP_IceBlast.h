// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FP_Skill.h"
#include "FP_IceBlast.generated.h"

/**
 * 
 */
UCLASS()
class FIGUREPROJECT_API AFP_IceBlast : public AFP_Skill
{
	GENERATED_BODY()
	
public:
	AFP_IceBlast();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


	UPROPERTY(EditAnywhere)
	class UBoxComponent* CollisionBox;
	
	UFUNCTION()
	void OnFinished(UParticleSystemComponent* _particle);
	
	TArray<AFP_Monster*> Targets;

	void SetAttackArea();
};
