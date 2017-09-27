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

UCLASS()
class FIGUREPROJECT_API AFP_Player : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AFP_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Status)
	struct FSTATUS Status;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Player)
	class USphereComponent* Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Player)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Player)
	class USpringArmComponent* CameraSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Player)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Player)
	class USphereComponent* Sight;
};
