// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_Monster_Normal.h"
#include "FP_Weapon.h"

void AFP_Monster_Normal::BeginPlay()
{
	Super::BeginPlay();

	MaxHP = 2.f;
	HP = MaxHP;
}

void AFP_Monster_Normal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	/*if (CurrentLocation.Size() < 1)
	{
		TArray<AActor*> FoundActor;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFP_Weapon::StaticClass(), FoundActor);
		Cast<AFP_Weapon>(FoundActor[0])->DeleteTargetMonsterInArray(this);
		Destroy();
		return;
	}*/

	FVector Direction = CurrentLocation * -1.f;
	Direction.Normalize();

	int index = 0;
	float speedOffset = 1.f;

	for (int i = 0; i < StateMgr.Num(); ++i)
	{
		if (StateMgr[i].eState == SLOW)
		{
			speedOffset = StateMgr[i].SpeedOffset;
			break;
		}
	}

	FVector NewLocation = CurrentLocation + Direction * DeltaTime * Speed * speedOffset;
	SetActorLocation(NewLocation);
}