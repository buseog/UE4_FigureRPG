// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_ComProjectile.h"


// Sets default values
AFP_ComProjectile::AFP_ComProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFP_ComProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFP_ComProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFP_ComProjectile::MoveToTarget(AActor* InputActor, FVector Target, float Speed)
{
	FVector CurrentLocation = InputActor->GetActorLocation();
	/*FVector Direction = Target - CurrentLocation;
	Direction.Normalize();*/

	FVector NewLocation = CurrentLocation + Target * Speed;
	InputActor->SetActorLocation(NewLocation);
}