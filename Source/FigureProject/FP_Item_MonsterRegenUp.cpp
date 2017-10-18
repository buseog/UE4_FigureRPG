// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_Item_MonsterRegenUp.h"

AFP_Item_MonsterRegenUp::AFP_Item_MonsterRegenUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AFP_Item_MonsterRegenUp::BeginPlay()
{
	Super::BeginPlay();

	ChangeLight(FColor(255, 0, 0));
}

void AFP_Item_MonsterRegenUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFP_Item_MonsterRegenUp::OnProxOverlapBegin(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}