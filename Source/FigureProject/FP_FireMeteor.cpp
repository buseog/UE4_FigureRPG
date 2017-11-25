// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_FireMeteor.h"


// Sets default values
AFP_FireMeteor::AFP_FireMeteor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProxSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereProx"));
	ProxSphere->SetSphereRadius(100.f);
	ProxSphere->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystem(TEXT("ParticleSystem'/Game/Effect/Skill/Fire/FP_FireMeteor.FP_FireMeteor'"));
	Particle->SetTemplate(ParticleSystem.Object);

	SkillInfo.Name = "FireUltimate";
	SkillName = "Meteor";

	Stat.Speed = 1.f;
	Stat.CoolTimeRatio = 1.f;
	Stat.Damage = 1.f;
	Stat.Range = 1.f;

	SkillInfo.AtkSpdPerLv = 0.f;
	SkillInfo.DmgPerLv = 25.f;

	InitStat = Stat;
}

// Called when the game starts or when spawned
void AFP_FireMeteor::BeginPlay()
{
	Super::BeginPlay();

	ProxSphere->SetSphereRadius(Player->Status.AttackRange);
	Particle->SetWorldScale3D(FVector(ProxSphere->GetScaledSphereRadius() * 0.002f, ProxSphere->GetScaledSphereRadius() * 0.002f, 1.f));
}

// Called every frame
void AFP_FireMeteor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentTime += DeltaTime;

	if (CurrentTime >= LifeTime)
		Destroy();

	if (Particle->AccumTickTime < 2.f)
		return;

	Targets.Empty();
	AFP_ComCollision::CollisionWithMulti<USphereComponent, AFP_Monster>(ProxSphere, Targets);
	if (Targets.Num() != 0)
	{
		TimelimitForDot -= DeltaTime;
		if (TimelimitForDot > 0.f)
			return;
	}

	for (int i = 0; i < Targets.Num(); ++i)
	{
		Targets[i]->ExpBonus = AFP_ComCalculator::CalculateExpBonus(this);
		AFP_ComMonsterStateMgr::StateControl(this, Targets[i]);

		Stat.Damage = Targets[i]->MaxHP * 0.4f;

		Targets[i]->MyTakeDamage(AFP_ComCalculator::CalculateFinalDamage(Player, this, Targets[i]));

		TimelimitForDot = 1.f;
	}
}

