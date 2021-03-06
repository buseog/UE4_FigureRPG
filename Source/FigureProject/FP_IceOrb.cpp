// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_IceOrb.h"


AFP_IceOrb::AFP_IceOrb()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystem(TEXT("ParticleSystem'/Game/Effect/Skill/Ice/P_ProjectileLob_Source_Ice_03.P_ProjectileLob_Source_Ice_03'"));
	Particle->SetTemplate(ParticleSystem.Object);
	Particle->SetWorldScale3D(FVector(0.1f, 0.1f, 0.1f));

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetSphereRadius(4.f);
	CollisionSphere->SetupAttachment(RootComponent);

	SkillInfo.Name = "IceOrb";

	Stat.Speed = 0.2f;
	Stat.CoolTimeRatio = 1.f;
	Stat.Damage = 1.f;
	Stat.Range = 1.f;

	SkillInfo.AtkSpdPerLv = 0.015f;
	SkillInfo.DmgPerLv = 25.f;

	InitStat = Stat;
}

void AFP_IceOrb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Particle->AccumTickTime > 5.f)
		Destroy();

	AFP_ComProjectile::MoveToTarget(this, TargetDirection, AFP_ComCalculator::CalculateFinalSpeed(Player, this, DeltaTime));




	AFP_Monster* TargetMonster = AFP_ComCollision::Collision<USphereComponent, AFP_Monster>(CollisionSphere);
	if (TargetMonster != nullptr)
	{
		TargetMonster->ExpBonus = AFP_ComCalculator::CalculateExpBonus(this);

		TimelimitForDot -= DeltaTime;
		if (TimelimitForDot > 0.f)
			return;

		AFP_ComMonsterStateMgr::StateControl(this, TargetMonster);

		TargetMonster->MyTakeDamage(AFP_ComCalculator::CalculateFinalDamage(Player, this, TargetMonster));

		TimelimitForDot = 0.25f;

		//Destroy();
	}
	
}

void AFP_IceOrb::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	//AFP_Impact* Impact = GetWorld()->SpawnActor<AFP_Impact>(this->GetActorLocation(), FRotator(0.f, 0.f, 0.f));
	//if (Impact == nullptr)
	//	return;

	//Impact->SetImpact(AFP_Impact::ICEBALLIMPACT);


}