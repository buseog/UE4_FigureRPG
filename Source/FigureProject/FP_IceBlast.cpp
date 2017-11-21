// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_IceBlast.h"
#include "FP_Weapon.h"



AFP_IceBlast::AFP_IceBlast()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystem(TEXT("ParticleSystem'/Game/Effect/Skill/Ice/FP_IceBlast.FP_IceBlast'"));
	Particle->SetTemplate(ParticleSystem.Object);


	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->InitBoxExtent(FVector(30.f, 30.f, 1.f));
	CollisionBox->SetRelativeLocation(FVector(30.f, 0.f, 0.f));
	CollisionBox->SetupAttachment(RootComponent);
	//CollisionBox->SetHiddenInGame(false);

	Particle->OnSystemFinished.AddDynamic(this, &AFP_IceBlast::OnFinished);

	Particle->SetVectorParameter(TEXT("AttackRange"), FVector(0.1f, 0.1f, 0.1f));
	SkillInfo.Name = "IceBlast";

	Stat.Speed = 1.f;
	Stat.CoolTimeRatio = 1.2f;
	Stat.Damage = 1.f;
	Stat.Range = 0.8f;

	SkillInfo.AtkSpdPerLv = 0.02f;
	SkillInfo.DmgPerLv = 15.f;
	Debuff = AFP_Monster::SLOW;

}

void AFP_IceBlast::BeginPlay()
{
	Super::BeginPlay();

	Debuff = AFP_Monster::SLOW;
	DebuffDuration = 0.5f;
}

void AFP_IceBlast::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetAttackArea();

	if (Particle->GetNumActiveParticles() <= 0 && Particle->AccumTickTime > 0.3f)
		Destroy();

	
	Targets.Empty();
	AFP_ComCollision::CollisionWithMulti<UBoxComponent, AFP_Monster>(CollisionBox, Targets);
	if (Targets.Num() != 0)
	{
		TimelimitForDot -= DeltaTime;
		if (TimelimitForDot > 0.f)
			return;
	}

	for (size_t i = 0; i < Targets.Num(); ++i)
	{
		AFP_ComMonsterStateMgr::StateControl(this, Targets[i]);

		Targets[i]->MyTakeDamage(AFP_ComCalculator::CalculateFinalDamage(Player, this, Targets[i]));
		if (Targets[i]->GetisDestory() == true)
			Weapon->DeleteTargetMonsterInArray(Targets[i]);

		//UE_LOG(LogClass, Log, TEXT("%s"), *Targets[i]->GetName());
		
		if (int(Particle->AccumTickTime * 10) % 10 == 0)
		{
			AFP_Impact* Impact = GetWorld()->SpawnActor<AFP_Impact>(Targets[i]->GetActorLocation(), FRotator(0.f, 0.f, 0.f));
			if (Impact == nullptr)
				continue;
			Impact->SetImpact(AFP_Impact::ICEBLASTIMPACT);

			//state slow
			//Targets[i]->StateMgr.SetState(Debuff, DebuffDuration);
		}
		TimelimitForDot = 1.f;
	}
	
	
}

void AFP_IceBlast::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	//AFP_ComCollision::CollisionWithMulti<UBoxComponent, AFP_Monster>(CollisionBox, Targets);
	//for (size_t i = 0; i < Targets.Num(); ++i)
	//{
	//	AFP_Impact* Impact = GetWorld()->SpawnActor<AFP_Impact>(Targets[i]->GetActorLocation(), FRotator(0.f, 0.f, 0.f));
	//	if (Impact == nullptr)
	//		continue;
	//	Impact->SetImpact(AFP_Impact::ICEBLASTIMPACT);
	//}
	

}

void AFP_IceBlast::OnFinished(UParticleSystemComponent* _particle)
{


	Destroy();
}

void AFP_IceBlast::SetAttackArea()
{
	TArray<AActor*> FoundActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFP_Weapon::StaticClass(), FoundActor);
	if (FoundActor[0] == nullptr)
		return;

	Weapon = Cast<AFP_Weapon>(FoundActor[0]);
	float Radius = Weapon->SphereComponent->GetScaledSphereRadius();
	CollisionBox->SetBoxExtent(FVector(Radius*0.5f, 30.f, 1.f));
	CollisionBox->SetRelativeLocation(FVector(Radius*0.5f, 0.f, 0.f));
	Particle->SetVectorParameter(TEXT("AttackRange"), FVector(0.1f + Radius*0.001f, 0.1f, 0.1f));

}