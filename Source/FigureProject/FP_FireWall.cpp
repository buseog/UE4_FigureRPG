// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_FireWall.h"

AFP_FireWall::AFP_FireWall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProxSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereProx"));
	ProxSphere->SetSphereRadius(50.f);
	ProxSphere->SetupAttachment(RootComponent);
	ProxSphere->SetHiddenInGame(false);
	Stat.Damage = 0.005f;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystem(TEXT("ParticleSystem'/Game/Effect/Skill/Fire/FP_FireWall.FP_FireWall'"));
	Particle->SetTemplate(ParticleSystem.Object);
	//Particle->SetWorldScale3D(FVector(0.3f, 0.3f, 0.3f));
}

// Called when the game starts or when spawned
void AFP_FireWall::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFP_FireWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentScale = Particle->RelativeScale3D;
	//Particle->SetWorldScale3D(FVector(CurrentScale.X - CurrentTime * 0.1f, CurrentScale.Y - CurrentTime * 0.1f, CurrentScale.Z - CurrentTime * 0.1f));

	CurrentTime += DeltaTime;

	AFP_ComProjectile::MoveToTarget(this, TargetDirection, Player->GetStatus().BulletSpeed * Stat.Speed * DeltaTime);

	Targets.Empty();
	AFP_ComCollision::CollisionWithMulti<USphereComponent, AFP_Monster>(ProxSphere, Targets);

	for (int i = 0; i < Targets.Num(); ++i)
	{
		Targets[i]->MyTakeDamage(Player->Status.Attack * Stat.Damage);

		/*AFP_Impact* Impact = GetWorld()->SpawnActor<AFP_Impact>(this->GetActorLocation(), FRotator(0.f, 0.f, 0.f));
		if (Impact == nullptr)
			return;

		Impact->SetImpact(AFP_Impact::FIREBALLIMPACT);*/

		if(Targets[i]->GetisDestory())
			Cast<AFP_Weapon>(Weapon)->DeleteTargetMonsterInArray(Targets[i]);
	}

	if (CurrentTime >= LifeTime)
		Destroy();
}

void AFP_FireWall::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}