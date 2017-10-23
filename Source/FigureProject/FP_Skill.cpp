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