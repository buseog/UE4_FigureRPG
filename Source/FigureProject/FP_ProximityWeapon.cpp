// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_ProximityWeapon.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "FP_Player.h"

// Sets default values
AFP_ProximityWeapon::AFP_ProximityWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	Particle->SetupAttachment(RootComponent);

	ProxBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxProx"));
	ProxBox->SetupAttachment(Particle);
}

// Called when the game starts or when spawned
void AFP_ProximityWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFP_ProximityWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Collision(DeltaTime);
}

void AFP_ProximityWeapon::Collision(float _DeltaTime)
{
	TArray<AActor*> Actors;
	ProxBox->GetOverlappingActors(Actors);

	AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	for (int i = 0; i < Actors.Num(); ++i)
	{
		if (Actors[i] == pPlayer)
			continue;

		Actors[i]->Destroy();
	}
}
