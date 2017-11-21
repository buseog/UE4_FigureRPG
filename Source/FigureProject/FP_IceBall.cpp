// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_IceBall.h"


AFP_IceBall::AFP_IceBall()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystem(TEXT("ParticleSystem'/Game/Effect/Skill/Ice/FP_IceBall.FP_IceBall'"));
	Particle->SetTemplate(ParticleSystem.Object);


	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetSphereRadius(1.f);
	CollisionSphere->SetupAttachment(RootComponent);

	Stat.Speed = 1.f;
	Stat.CoolTimeRatio = 0.8f;
	Stat.Damage = 1.5f;
	Stat.Range = 1.f;

	SkillInfo.AtkSpdPerLv = 0.025f;
	SkillInfo.DmgPerLv = 15.f;

	SkillInfo.Name = "IceBall";

	Debuff = AFP_Monster::FROZEN;
	DebuffDuration = 1.f;
	DebuffProbability = 30.f;
}

void AFP_IceBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AFP_ComProjectile::MoveToTarget(this, TargetDirection, Player->GetStatus().BulletSpeed * Stat.Speed * DeltaTime);

	AFP_Monster* TargetMonster = AFP_ComCollision::Collision<USphereComponent, AFP_Monster>(CollisionSphere);
	if (TargetMonster != nullptr)
	{

		AFP_ComMonsterStateMgr::StateControl(this, TargetMonster);

		TargetMonster->MyTakeDamage(AFP_ComCalculator::CalculateFinalDamage(Player, this, TargetMonster));
		if (TargetMonster->GetisDestory() == true)
			Weapon->DeleteTargetMonsterInArray(TargetMonster);
		
		Destroy();
	}
}

void AFP_IceBall::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	AFP_Impact* Impact = GetWorld()->SpawnActor<AFP_Impact>(this->GetActorLocation(), FRotator(0.f, 0.f, 0.f));
	if (Impact == nullptr)
		return;

	Impact->SetImpact(AFP_Impact::ICEBALLIMPACT);

	
}