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

	enum MSTATE { NORMAL, SLOW, IGNITE };

	struct MonsterState
	{
		float Duration = 0.f;
		float SpeedOffset = 0.5f;
		float Damage = 0.f;
		MSTATE eState = NORMAL;
		AFP_Monster* Monster = nullptr;
		float TimelimitForIgnite = 0.f;

		void SetState(MSTATE _state, float _duration)
		{
			eState = _state;
			Duration = _duration;
		}

		void CustomTick(float _delta)
		{
			if (Duration <= 0.f)
			{
				eState = NORMAL;
				SpeedOffset = 1.f;
				Monster->PointLight->SetIntensity(0.f);
			}

			if (eState == SLOW)
			{
				SpeedOffset = 0.5f;
				Duration -= _delta;	
				Monster->PointLight->SetLightColor(FColor::Blue);
				Monster->PointLight->SetIntensity(150.f);
			}

			if (eState == IGNITE)
			{
				Duration -= _delta;
				Monster->PointLight->SetLightColor(FColor::Red);
				Monster->PointLight->SetIntensity(150.f);
			}
		}
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
	MonsterState StateMgr;
	bool isTargeting = false;
	
public:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(EditAnywhere)
	USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* WidgetComponent;

	UPROPERTY(EditAnywhere)
	UHPBar_Widget* HPBar_Widget;

	UPROPERTY(EditAnywhere)
	class UFP_DamageUI* DamageUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	UPointLightComponent* PointLight;
	
	bool isDestroy = false;
	AFP_Item* Item;
	AFP_Weapon* Weapon;

public:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void DropItem();
	void MyTakeDamage(float _damage);
};
