// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_IceBall.h"


AFP_IceBall::AFP_IceBall()
{
	PrimaryActorTick.bCanEverTick = true;

	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	Particle->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystem(TEXT("ParticleSystem'/Game/Effect/Skill/Ice/FP_IceBall.FP_IceBall'"));
	Particle->SetTemplate(ParticleSystem.Object);


	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetSphereRadius(3.f);
	CollisionSphere->SetupAttachment(RootComponent);
}

void AFP_IceBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AFP_ComProjectile::MoveToTarget(this, TargetDirection, Player->GetStatus().BulletSpeed * DeltaTime);

	AFP_Monster* TargetMonster = AFP_ComCollision::Collision<USphereComponent, AFP_Monster>(CollisionSphere);
	if (TargetMonster != nullptr)
	{
		TargetMonster->MyTakeDamage(Damage);
		if (TargetMonster->GetisDestory() == true)
			Weapon->DeleteTargetMonsterInArray(TargetMonster);
		
		Destroy();
	}
}

void AFP_IceBall::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	
}