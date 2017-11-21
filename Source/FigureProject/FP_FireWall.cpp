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

	SkillInfo.Name = "FireWall";
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

	if (CurrentTime >= LifeTime)
		Destroy();


	


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

		AFP_ComMonsterStateMgr::StateControl(this, Targets[i]);

		Targets[i]->MyTakeDamage(AFP_ComCalculator::CalculateFinalDamage(Player, this, Targets[i]));

		/*AFP_Impact* Impact = GetWorld()->SpawnActor<AFP_Impact>(this->GetActorLocation(), FRotator(0.f, 0.f, 0.f));
		if (Impact == nullptr)
			return;

		Impact->SetImpact(AFP_Impact::FIREBALLIMPACT);*/

		if(Targets[i]->GetisDestory())
			Cast<AFP_Weapon>(Weapon)->DeleteTargetMonsterInArray(Targets[i]);

		TimelimitForDot = 1.f;
	}



	
}

void AFP_FireWall::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}