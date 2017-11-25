// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_GlacialSpike.h"




AFP_GlacialSpike::AFP_GlacialSpike()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProxSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereProx"));
	ProxSphere->SetSphereRadius(100.f);
	ProxSphere->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystem(TEXT("ParticleSystem'/Game/Effect/Skill/Ice/FP_GlacialSpike.FP_GlacialSpike'"));
	Particle->SetTemplate(ParticleSystem.Object);

	SkillInfo.Name = "IceUltimate";

	Stat.Speed = 1.f;
	Stat.CoolTimeRatio = 1.f;
	Stat.Damage = 1.f;
	Stat.Range = 1.f;

	Debuff = AFP_Monster::FROZEN;
	DebuffDuration = 5.f;
	DebuffProbability = 100.f;
}

void AFP_GlacialSpike::BeginPlay()
{
	Super::BeginPlay();

	ProxSphere->SetSphereRadius(Player->Status.AttackRange);
	Particle->SetWorldScale3D(FVector(ProxSphere->GetScaledSphereRadius() * 0.002f, ProxSphere->GetScaledSphereRadius() * 0.002f, 1.f));
}

void AFP_GlacialSpike::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogClass, Log, TEXT("%d"), int(Particle->IsActive()));
	if (Particle->IsActive() == false)
	{
		Destroy();
		return;
	}
		
	if (Particle->AccumTickTime > 1.f && isOnce == false)
	{
		isOnce = true;

		Targets.Empty();
		AFP_ComCollision::CollisionWithMulti<USphereComponent, AFP_Monster>(ProxSphere, Targets);


		for (int i = 0; i < Targets.Num(); ++i)
		{
			Targets[i]->ExpBonus = AFP_ComCalculator::CalculateExpBonus(this);
			AFP_ComMonsterStateMgr::StateControl(this, Targets[i]);

			Stat.Damage = Targets[i]->MaxHP * 0.5f;

			Targets[i]->MyTakeDamage(AFP_ComCalculator::CalculateFinalDamage(Player, this, Targets[i]));
		}
	}
}