// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "FP_Rune.h"
#include "FP_Player.generated.h"

USTRUCT(BlueprintType)
struct FPlayerStatus
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	float Hp = 20;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	float MaxHp = 20;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	float HpRegen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	float Attack = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	float AttackRange = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	float AttackSpeed = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	float BulletSpeed = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	float Critical;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	float CriticalDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	float Splash;
};

USTRUCT(BlueprintType)
struct FPlayerSkillLv
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillLv)
	int FireBall = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillLv)
	int FireBlast = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillLv)
	int FireWall = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillLv)
	int IceBall = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillLv)
	int IceBlast = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillLv)
	int IceOrb = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillLv)
	int SkillPoint = 10;
};

USTRUCT(BlueprintType)
struct FPlayerLevel
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Level)
	int Level = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Level)
	float Exp = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Level)
	float FullExp = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Level)
	int Point = 5.f;
	


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
	virtual float TakeDamage(float _Damage, struct FDamageEvent const& _DamageEvent, class AController* _EventInstigator, class AActor* _DamageCauser) override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	void CheckLevelUp();
private:
	
	float	HitTime;

	//Ã¶ÀÇ Ãß°¡
	float	BuffTime = 0.f;
	float	BuffDuration = 0.f;
	float	BuffDiff;
	int		BuffType;

public:
	TArray<AFP_Rune*> Inventory;

public:
	bool	bIsBuffed = false;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	struct FPlayerStatus Status;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillLv)
	struct FPlayerSkillLv SkillLv;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Level)
	struct FPlayerLevel	Level;

	//init
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	struct FPlayerStatus InitStatus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillLv)
	struct FPlayerSkillLv InitSkillLv;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Level)
	struct FPlayerLevel	InitLevel;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Player)
	class UStaticMeshComponent* Mesh;*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Player)
	class USpringArmComponent* CameraSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Player)
	class UCameraComponent* Camera;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Player)
	class USphereComponent* CollisionSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	TSubclassOf<AFP_Weapon> Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	UPointLightComponent* PointLight;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Particle)
	class UParticleSystemComponent* Particle;

private:
	void Regeneration(float DeltaTime);

public:
	void StatusLevelUp(int _Type);
	void RestartStage(void);
public:

	UFUNCTION(BlueprintCallable, Category = Status)
	struct FPlayerStatus GetStatus() { return Status; }

	UFUNCTION(BlueprintCallable, Category = Status)
	struct FPlayerLevel	GetLevel() { return Level; }

	UFUNCTION()
	void OnProxOverlapBegin(UPrimitiveComponent* _HitComp, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _SweepResult);

	//Ã¶ÀÇ Ãß°¡
	void SetStat(int Type, float Diff, float Duration, FColor Color = FColor(0.f, 0.f, 0.f));

	FName Test;
	float TimeAcc = 0.f;

	//---------------------Gem-----------------------//
	int Gem = 5;
	//-----------------------------------------------//
};
