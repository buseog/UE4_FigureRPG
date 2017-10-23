// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_FireBall.h"

AFP_FireBall::AFP_FireBall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProxSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereProx"));
	ProxSphere->SetSphereRadius(1.f);
	ProxSphere->SetupAttachment(RootComponent);
	Damage = 1.f;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystem(TEXT("ParticleSystem'/Game/Effect/Skill/Fire/FP_FireBall.FP_FireBall'"));
	Particle->SetTemplate(ParticleSystem.Object);

	Speed = 0.5f;
}

// Called when the game starts or when spawned
void AFP_FireBall::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFP_FireBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AFP_ComProjectile::MoveToTarget(this, TargetDirection, Player->GetStatus().BulletSpeed * Speed * DeltaTime);

	AFP_Monster* TargetMonster = AFP_ComCollision::Collision<USphereComponent, AFP_Monster>(ProxSphere);
	if (TargetMonster != nullptr)
	{
		TargetMonster->MyTakeDamage(Damage);

		if (TargetMonster->GetisDestory() == true)
			Cast<AFP_Weapon>(Weapon)->DeleteTargetMonsterInArray(TargetMonster);

		Destroy();
	}
}