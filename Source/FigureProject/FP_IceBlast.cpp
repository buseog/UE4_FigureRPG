// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_IceBlast.h"




AFP_IceBlast::AFP_IceBlast()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystem(TEXT("ParticleSystem'/Game/Effect/Skill/Ice/FP_IceBlast.FP_IceBlast'"));
	Particle->SetTemplate(ParticleSystem.Object);


	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->InitBoxExtent(FVector(20.f, 30.f, 1.f));
	CollisionBox->SetRelativeLocation(FVector(20.f, 0.f, 0.f));
	CollisionBox->SetupAttachment(RootComponent);
	//CollisionBox->SetHiddenInGame(false);

	Particle->OnSystemFinished.AddDynamic(this, &AFP_IceBlast::OnFinished);
	Stat.Damage = 0.005f;


}

void AFP_IceBlast::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Particle->GetNumActiveParticles() <= 0 && Particle->AccumTickTime > 0.3f)
		Destroy();
	
	Targets.Empty();
	AFP_ComCollision::CollisionWithMulti<UBoxComponent, AFP_Monster>(CollisionBox, Targets);
	for (size_t i = 0; i < Targets.Num(); ++i)
	{
		Targets[i]->MyTakeDamage(Player->Status.Attack * Stat.Damage);
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
			Targets[i]->StateMgr.SetState(AFP_Monster::MonsterState::SLOW, 0.5f);
		}
		
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