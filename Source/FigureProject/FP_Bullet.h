// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "FP_Bullet.generated.h"

UCLASS()
class FIGUREPROJECT_API AFP_Bullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFP_Bullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	UPROPERTY()
	UStaticMeshComponent* StaticMesh;
	USphereComponent* SphereComponent;

	inline void SetTargetDir(FVector _targetdir) { TargetDir = _targetdir; }

public:
	float BulletSpeed = 100.f;
	float TimeAcc = 0.f;
	FVector TargetDir = FVector(1.f,0.f,0.f);

	
	
};
