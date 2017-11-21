// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "FP_Item.h"
#include "HPBar_Widget.h"
#include "FP_Monster.generated.h"

class AFP_Weapon;
UCLASS()
class FIGUREPROJECT_API AFP_Monster : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFP_Monster();

	enum MSTATE { NORMAL, SLOW, IGNITE , FROZEN};

	struct MonsterState
	{
		float Duration = 0.f;
		float SpeedOffset = 0.5f;
		float Damage = 0.f;
		MSTATE eState = NORMAL;
		float TimelimitForIgnite = 0.f;
	};

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
	float Exp = 15.f;
	float HPShowTime = 0.f;
	TArray<MonsterState> StateMgr;
	bool isTargeting = false;
	
public:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(EditAnywhere)
	USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere)
	UHPBar_Widget* HP_UI;

	UPROPERTY(EditAnywhere)
	class UFP_DamageUI* DamageUI;


	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Particle)
	class UParticleSystemComponent* Particle;

	
	bool isDestroy = false;
	AFP_Item* Item;
	AFP_Weapon* Weapon;

public:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void DropItem();
	void MyTakeDamage(float _damage, int fontsize = 40, FColor color = FColor::White);

	void ChangeState(float _delta);
	
};
