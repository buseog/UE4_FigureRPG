// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "FP_Player.generated.h"

USTRUCT(BlueprintType)
struct FSTATUS
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	float Hp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	float MaxHp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	float HpRegen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	float Attack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	float AttackRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	float AttackSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	float BulletSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	float Critical;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	float CriticalDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	float Splash;
};

class AFP_Weapon;

UCLASS()
class FIGUREPROJECT_API AFP_Player : public APawn
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AFP_Player();

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Status)
	struct FSTATUS Status;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Player)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Player)
	class USpringArmComponent* CameraSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Player)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Player)
	class USphereComponent* CollisionSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Player)
	class USphereComponent* SightSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	TSubclassOf<AFP_Weapon> Weapon;

public:
	void MouseLClick(void);
	void StatusLevelUp(int _Type);

public:
	virtual void Attack(void);

public:
	UFUNCTION(BlueprintCallable, Category = UI)
	void ToggleStatus();

	UFUNCTION()
	void OnProxOverlapBegin(UPrimitiveComponent* _HitComp, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _SweepResult);
};
