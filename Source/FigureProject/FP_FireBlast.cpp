// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_FireBlast.h"
#include "FP_ComCollision.h"

AFP_FireBlast::AFP_FireBlast()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProxSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereProx"));
	ProxSphere->SetSphereRadius(20.f);
	ProxSphere->SetupAttachment(RootComponent);
	Stat.Damage = 1.f;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystem(TEXT("ParticleSystem'/Game/Effect/Skill/Fire/FP_FireBlastImpact.FP_FireBlastImpact'"));
	Particle->SetTemplate(ParticleSystem.Object);
	Particle->SetupAttachment(RootComponent);
	Particle->SetWorldScale3D(FVector(0.7f, 0.7f, 0.7f));

	SkillInfo.Name = "FireBlast";
	Debuff = AFP_Monster::IGNITE;
	DebuffDamage = 0.01f;
	DebuffDuration = 2.f;

	Stat.Speed = 1.f;
	Stat.CoolTimeRatio = 2.f;
	Stat.Damage = 1.f;
	Stat.Range = 1.f;

	SkillInfo.AtkSpdPerLv = 0.015f;
	SkillInfo.DmgPerLv = 30.f;
}

// Called when the game starts or when spawned
void AFP_FireBlast::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFP_FireBlast::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Particle->GetNumActiveParticles() <= 0 && Particle->AccumTickTime > 0.3f)
		Destroy();

	if (bActivated)
		return;

	if (Particle->AccumTickTime < 1.f)
		return;

	Targets.Empty();

	AFP_ComCollision::CollisionWithMulti<USphereComponent, AFP_Monster>(ProxSphere, Targets);
	for (size_t i = 0; i < Targets.Num(); ++i)
	{
		Targets[i]->MyTakeDamage(AFP_ComCalculator::CalculateFinalDamage(Player, this, Targets[i]));
		if (Targets[i]->GetisDestory() == true)
			Weapon->DeleteTargetMonsterInArray(Targets[i]);

		AFP_Impact* Impact = GetWorld()->SpawnActor<AFP_Impact>(Targets[i]->GetActorLocation(), FRotator(0.f, 0.f, 0.f));
		if (Impact == nullptr)
			continue;
		Impact->SetImpact(AFP_Impact::FIREBALLIMPACT);
	}

	bActivated = true;
}

void AFP_FireBlast::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}