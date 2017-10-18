// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "FP_Item.h"
#include "HPBar_Widget.h"
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
	bool GetisDestory(void) { return isDestroy;  }

public:
	float HP;
	float MaxHP;
	float Damage;
	float DropRate;
	float Speed = 10.f;
	float Exp = 5.f;
	float HPShowTime = 0.f;
	
public:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(EditAnywhere)
	USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* WidgetComponent;

	UPROPERTY(EditAnywhere)
	UHPBar_Widget* HPBar_Widget;
	
	bool isDestroy = false;
	AFP_Item* Item;

public:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void DropItem();
	void MyTakeDamage(float _damage);
};
