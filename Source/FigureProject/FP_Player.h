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
	float AttackRange = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	float AttackSpeed = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	float BulletSpeed = 100.f;
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	struct FSTATUS Status;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	float TEST;

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
	void StatusLevelUp(int _Type);


public:
	UFUNCTION(BlueprintCallable, Category = UI)
	void ToggleStatus(AActor* p, FKey Button);

	UFUNCTION(BlueprintCallable, Category = Status)
	struct FSTATUS GetStatus() { return Status; }

	UFUNCTION()
	void OnProxOverlapBegin(UPrimitiveComponent* _HitComp, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _SweepResult);
};
