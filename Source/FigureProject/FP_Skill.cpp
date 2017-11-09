// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_Skill.h"
#include "Engine.h"

#include "FP_Player.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"

// Sets default values
AFP_Skill::AFP_Skill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	
	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	Particle->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AFP_Skill::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (nullptr == Player)
		return;

	TArray<AActor*> FoundActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFP_Weapon::StaticClass(), FoundActor);
	if (FoundActor[0] == nullptr)
		return;

	Weapon = Cast<AFP_Weapon>(FoundActor[0]);

	/*AFP_Rune* rune = GetWorld()->SpawnActor<AFP_Rune>(FVector::ZeroVector, FRotator::ZeroRotator);
	Socket socket;
	socket.Color = rune->Color;
	Sockets.Add(socket);
	Sockets[0].EpuipRune(rune);*/
}

// Called every frame
void AFP_Skill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFP_Skill::SetTargetDirection(FVector _location)
{
	TargetDirection = _location - this->GetActorLocation();
	TargetDirection.Normalize();
}

FColor AFP_Skill::AddSocket()
{
	if (Stat.ActiveSocketNum >= MaxSocketNum)
		return FColor::White;

	++Stat.ActiveSocketNum;
	int color = FMath::FRandRange(1, 4);
	
	Socket socket;
	
	switch (color)
	{
	case 1:
		socket.Color = FColor::Red;
		break;
	case 2:
		socket.Color = FColor::Green;
		break;
	case 3:
		socket.Color = FColor::Blue;
		break;
	}

	Sockets.Add(socket);
	
	return socket.Color;
}

void AFP_Skill::EquipRune(AFP_Rune* _rune)
{
	if (Sockets.Num() == 0)
		return;

	if (EquipedRuneNum >= Stat.ActiveSocketNum)
		return;

	Sockets[Stat.ActiveSocketNum - 1].EpuipRune(_rune);

}