// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FP_Item.h"
#include "FP_Item_PowerUp.generated.h"

/**
 * 
 */
UCLASS()
class FIGUREPROJECT_API AFP_Item_PowerUp : public AFP_Item
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AFP_Item_PowerUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnProxOverlapBegin(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
