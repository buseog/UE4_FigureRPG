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
	
	void SetisDestroy(bool _isDestroy) { isDestroy = _isDestroy; }
	
	
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(EditAnywhere)
	USphereComponent* SphereComponent;

	float Speed = 10.f;
	bool isDestroy = false;

};
