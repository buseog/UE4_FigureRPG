// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "FP_ComProjectile.h"
#include "FP_ComCollision.h"
#include "FP_Player.h"
#include "FP_Monster.h"
#include "FP_Weapon.h"
#include "FP_Impact.h"
#include "FP_Rune.h"
#include "FP_Skill.generated.h"

UCLASS()
class FIGUREPROJECT_API AFP_Skill : public AActor
{
	GENERATED_BODY()
public:
	struct SkillInfo
	{
		float DmgPerLv = 10.f;
		float AtkSpdPerLv = 0.05f;
	};

public:	
	// Sets default values for this actor's properties

	struct Socket
	{
		AFP_Rune* Rune = nullptr;
		FColor Color;

		void EpuipRune(AFP_Rune* _rune)
		{
			if (Color != _rune->Color)
				return;

			Rune = _rune;
		}
	};

	struct SkillStat
	{
		float Damage = 1.f;
		float Speed = 1.f; //bullet speed
		float CoolTimeRatio = 1.f; // attack speed
		float Range = 1.f;
		int ActiveSocketNum = 1;
	};

	AFP_Skill();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetTargetDirection(FVector _location);
	FColor AddSocket();
	void EquipRune(AFP_Rune* _rune);


	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Particle)
	class UParticleSystemComponent* Particle;

	//FVector TargetLocation = FVector(0.f,0.f,0.f);
	FVector TargetDirection = FVector(0.f, 0.f, 0.f);
	AFP_Player* Player;
	AFP_Weapon* Weapon;

	SkillStat Stat;
	SkillInfo SkillInfo;

	/*-----Debuff-------------------*/
	AFP_Monster::MonsterState::MSTATE Debuff = AFP_Monster::MonsterState::NORMAL;
	float DebuffDamage = 0.f;
	float DebuffDuration = 0.f;
	/*------------------------------*/



	/*-----Socket-------------------*/
	
	int MaxSocketNum = 4;
	int EquipedRuneNum = 0;
	TArray<Socket> Sockets;
	/*------------------------------*/
	

	
};
