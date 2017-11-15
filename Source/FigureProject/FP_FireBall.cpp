// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_FireBall.h"
#include "FP_ComCalculator.h"


AFP_FireBall::AFP_FireBall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProxSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereProx"));
	ProxSphere->SetSphereRadius(1.f);
	ProxSphere->SetupAttachment(RootComponent);
	

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystem(TEXT("ParticleSystem'/Game/Effect/Skill/Fire/FP_FireBall.FP_FireBall'"));
	Particle->SetTemplate(ParticleSystem.Object);
}

// Called when the game starts or when spawned
void AFP_FireBall::BeginPlay()
{
	Super::BeginPlay();

	//Stat.Damage += SkillInfo.FireBallDmgLv * (Player->SkillLv.FireBall - 1);
	//Stat.CoolTimeRatio -= SkillInfo.FireBallAtkSpdLv * (Player->SkillLv.FireBall - 1);

	Stat.Damage = 1.f;
	Stat.Speed = 0.5f;
	Stat.Range = 2.f;
	Stat.CoolTimeRatio = 1.f;
	SkillInfo.Name = "FireBall";

}

// Called every frame
void AFP_FireBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogClass, Log, TEXT("bullet : %f"), AFP_ComCalculator::CalculateFinalSpeed(Player, this, DeltaTime));
	AFP_ComProjectile::MoveToTarget(this, TargetDirection, AFP_ComCalculator::CalculateFinalSpeed(Player, this, DeltaTime));

	AFP_Monster* TargetMonster = AFP_ComCollision::Collision<USphereComponent, AFP_Monster>(ProxSphere);
	if (TargetMonster != nullptr)
	{
		TargetMonster->MyTakeDamage(AFP_ComCalculator::CalculateFinalDamage(Player, this, TargetMonster));
		
		if (TargetMonster->GetisDestory() == true)
			Cast<AFP_Weapon>(Weapon)->DeleteTargetMonsterInArray(TargetMonster);

		Destroy();
	}
}

void AFP_FireBall::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	AFP_Impact* Impact = GetWorld()->SpawnActor<AFP_Impact>(this->GetActorLocation(), FRotator(0.f, 0.f, 0.f));
	if (Impact == nullptr)
		return;

	Impact->SetImpact(AFP_Impact::FIREBALLIMPACT);
}