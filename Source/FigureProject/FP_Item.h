// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/PointLightComponent.h"
#include "FP_Item.generated.h"

UCLASS()
class FIGUREPROJECT_API AFP_Item : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFP_Item();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	float Speed;
	FColor LightColor;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void MoveToPlayer(float DeltaTime);
	void ChangeLight(FColor Color = FColor(255, 255, 255), float Intensity = 500.f, float Radious = 10.f);
	void ChangeMesh(FString Ref, UStaticMeshComponent* _StaticMesh);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int Quantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	UStaticMeshComponent* StaticMesh;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	USphereComponent* CollisionSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	UPointLightComponent* PointLight;
	
	UFUNCTION()
	virtual void OnProxOverlapBegin(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
