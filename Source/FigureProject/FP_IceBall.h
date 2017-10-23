// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FP_Skill.h"
#include "FP_IceBall.generated.h"

/**
 * 
 */
UCLASS()
class FIGUREPROJECT_API AFP_IceBall : public AFP_Skill
{
	GENERATED_BODY()

public:
	AFP_IceBall();
	
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Player)
	class USphereComponent* CollisionSphere;
};
