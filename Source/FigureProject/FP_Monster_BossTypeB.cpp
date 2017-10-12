// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_Monster_BossTypeB.h"


void AFP_Monster_BossTypeB::BeginPlay()
{
	Super::BeginPlay();
	SetScale();


}

void AFP_Monster_BossTypeB::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isDestroy == true)
	{
		DecreaseSplit();
		isDestroy = false;
		Destroy();
		return;
	}

}

void AFP_Monster_BossTypeB::DecreaseSplit()
{
	if (Life <= 0)
		return;

	--Life;
	AFP_Monster_BossTypeB* Boss = GetWorld()->SpawnActor<AFP_Monster_BossTypeB>(FVector(GetActorLocation().X + 5.f, 20.f, 0.f), FRotator(0.f, 0.f, 0.f));
	Boss->SetLife(Life);
	Boss->SetScale();
	Boss = GetWorld()->SpawnActor<AFP_Monster_BossTypeB>(FVector(GetActorLocation().X - 5.f, 20.f, 0.f), FRotator(0.f, 0.f, 0.f));
	Boss->SetLife(Life);
	Boss->SetScale();
}

void AFP_Monster_BossTypeB::SetScale()
{
	FVector Scale = FVector(1.f + Life*0.5f, 1.f + Life*0.5f, 1.f);
	SetActorScale3D(Scale);
}