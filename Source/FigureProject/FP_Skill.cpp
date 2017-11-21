// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_Skill.h"
#include "Engine.h"
#include "FP_Weapon.h"
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


	static ConstructorHelpers::FObjectFinder<UTexture2D> RedSocket(TEXT("Texture2D'/Game/Icon/RedSocket.RedSocket'"));
	RedSocketIcon = RedSocket.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D> GreenSocket(TEXT("Texture2D'/Game/Icon/GreenSocket.GreenSocket'"));
	GreenSocketIcon = GreenSocket.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D> BlueSocket(TEXT("Texture2D'/Game/Icon/BlueSocket.BlueSocket'"));
	BlueSocketIcon = BlueSocket.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D> EmptySocket(TEXT("Texture2D'/Game/Icon/EmptySocket.EmptySocket'"));
	EmptySocketIcon = EmptySocket.Object;

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
	Sockets[0].EquipRune(rune);*/
}

// Called every frame
void AFP_Skill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//·é ¹Ù²î¸é ·é ¿É¼Ç °Ë»ç
	if (RuneChanged)
	{
		Stat.EnablePierce = false;

		for (int i = 0; i < this->Sockets.Num(); ++i)
		{
			if (this->Sockets[i].Rune == nullptr || !this->Sockets[i].Rune->IsValidLowLevel())
				continue;

			//ÇÇ¾î½º °Ë»ç
			if (this->Sockets[i].Rune->Name.Contains("PIERCE"))
				Stat.EnablePierce = true;
		}

		RuneChanged = false;
	}
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

