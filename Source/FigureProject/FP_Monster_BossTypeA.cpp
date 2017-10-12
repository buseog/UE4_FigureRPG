// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_Monster_BossTypeA.h"
#include "FP_Weapon.h"

void AFP_Monster_BossTypeA::BeginPlay()
{
	Super::BeginPlay();

	FVector NewScale = FVector(2.f, 2.f, 2.f);
	SetActorScale3D(NewScale);


	Distance = GetActorLocation().Size();
}

void AFP_Monster_BossTypeA::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isDestroy == true)
	{
		
		isDestroy = false;
		Destroy();
		return;
	}

	TimeAcc += DeltaTime;
	float fNewDist = Distance + cosf(TimeAcc);

	FVector NewLocation = GetActorLocation();
	NewLocation.X = cosf(TimeAcc) * fNewDist;
	NewLocation.Y = sinf(TimeAcc) * fNewDist;
	//x*x + y*y = d*d
	SetActorLocation(NewLocation);
		

	GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Blue, TEXT("Test"));
}