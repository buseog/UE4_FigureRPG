// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_FireBall.h"
#include "FP_ComCalculator.h"
#include "FP_ComMonsterStateMgr.h"

AFP_FireBall::AFP_FireBall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProxSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereProx"));
	ProxSphere->SetSphereRadius(1.f);
	ProxSphere->SetupAttachment(RootComponent);
	

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystem(TEXT("ParticleSystem'/Game/Effect/Skill/Fire/FP_FireBall.FP_FireBall'"));
	Particle->SetTemplate(ParticleSystem.Object);

	SkillInfo.Name = "FireBall";

	Stat.Speed = 0.5f;
	Stat.CoolTimeRatio = 1.5f;
	Stat.Damage = 1.f;
	Stat.Range = 1.f;

	SkillInfo.AtkSpdPerLv = 0.f;
	SkillInfo.DmgPerLv = 45.f;


	InitStat = Stat;
}

// Called when the game starts or when spawned
void AFP_FireBall::BeginPlay()
{
	Super::BeginPlay();

	//Stat.Damage += SkillInfo.FireBallDmgLv * (Player->SkillLv.FireBall - 1);
	//Stat.CoolTimeRatio -= SkillInfo.FireBallAtkSpdLv * (Player->SkillLv.FireBall - 1);


}

// Called every frame
void AFP_FireBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogClass, Log, TEXT("bullet : %f"), AFP_ComCalculator::CalculateFinalSpeed(Player, this, DeltaTime));
	AFP_ComProjectile::MoveToTarget(this, TargetDirection, AFP_ComCalculator::CalculateFinalSpeed(Player, this, DeltaTime));

	if (Particle->AccumTickTime > 5.f)
		Destroy();

	AFP_Monster* TargetMonster = AFP_ComCollision::Collision<USphereComponent, AFP_Monster>(ProxSphere);

	if (TargetMonster != nullptr)
	{
		TargetMonster->ExpBonus = AFP_ComCalculator::CalculateExpBonus(this);

		TimelimitForDot -= DeltaTime;
		if (TimelimitForDot > 0.f)
			return;

		AFP_ComMonsterStateMgr::StateControl(this, TargetMonster);
		TargetMonster->MyTakeDamage(AFP_ComCalculator::CalculateFinalDamage(Player, this, TargetMonster));	
		TimelimitForDot = 1.f;

		if (!Stat.EnablePierce)
			Destroy();
		else
		{
			AFP_Impact* Impact = GetWorld()->SpawnActor<AFP_Impact>(this->GetActorLocation(), FRotator(0.f, 0.f, 0.f));
			if (Impact == nullptr)
				return;

			Impact->SetImpact(AFP_Impact::FIREBALLIMPACT);
		}
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