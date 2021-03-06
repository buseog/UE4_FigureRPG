// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_FireWall.h"

AFP_FireWall::AFP_FireWall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProxSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereProx"));
	ProxSphere->SetSphereRadius(70.f);
	ProxSphere->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystem(TEXT("ParticleSystem'/Game/Effect/Skill/Fire/FP_FireWall.FP_FireWall'"));
	Particle->SetTemplate(ParticleSystem.Object);
	//Particle->SetWorldScale3D(FVector(0.3f, 0.3f, 0.3f));

	SkillInfo.Name = "FireWall";

	Stat.Speed = 1.f;
	Stat.CoolTimeRatio = 3.f;
	Stat.Damage = 0.3f;
	Stat.Range = 1.f;

	SkillInfo.AtkSpdPerLv = 0.f;
	SkillInfo.DmgPerLv = 25.f;

	InitStat = Stat;
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

	CurrentTime += DeltaTime;

	if (bStart)
	{
		ProxSphere->SetRelativeScale3D(FVector(Scale, Scale, Scale));
		bStart = false;
	}

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
		Targets[i]->ExpBonus = AFP_ComCalculator::CalculateExpBonus(this);
		AFP_ComMonsterStateMgr::StateControl(this, Targets[i]);

		Targets[i]->MyTakeDamage(AFP_ComCalculator::CalculateFinalDamage(Player, this, Targets[i]));

		/*AFP_Impact* Impact = GetWorld()->SpawnActor<AFP_Impact>(this->GetActorLocation(), FRotator(0.f, 0.f, 0.f));
		if (Impact == nullptr)
			return;

		Impact->SetImpact(AFP_Impact::FIREBALLIMPACT);*/

		TimelimitForDot = 0.5f;
	}



	
}

void AFP_FireWall::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}