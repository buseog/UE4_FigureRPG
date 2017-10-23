// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_Impact.h"


// Sets default values
AFP_Impact::AFP_Impact()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	
	ConstructorHelpers::FObjectFinder<UParticleSystem> FireBallImpact(TEXT("ParticleSystem'/Game/Effect/Skill/Fire/FP_FireBallHit.FP_FireBallHit'"));
	ParticleMap.Add(FIREBALLIMPACT, FireBallImpact.Object);

	ConstructorHelpers::FObjectFinder<UParticleSystem> IceBallImpact(TEXT("ParticleSystem'/Game/Effect/Skill/Ice/FP_Impact_Iceball.FP_Impact_Iceball'"));
	ParticleMap.Add(ICEBALLIMPACT, IceBallImpact.Object);
	
	
	Particle->SetupAttachment(RootComponent);
	Particle->OnSystemFinished.AddDynamic(this, &AFP_Impact::OnFinished);

}

// Called when the game starts or when spawned
void AFP_Impact::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFP_Impact::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFP_Impact::OnFinished(UParticleSystemComponent* _particle)
{
	Destroy();
}

void AFP_Impact::SetImpact(IMPACTTYPE _type)
{
	Particle->SetTemplate(ParticleMap[_type]);
}