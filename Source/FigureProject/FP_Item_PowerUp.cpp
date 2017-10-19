// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_Item_PowerUp.h"
#include "FP_Player.h"

AFP_Item_PowerUp::AFP_Item_PowerUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LightColor = FColor(255, 0, 0);
	ChangeMesh(FString("StaticMesh'/Game/Mesh/FP_Item_PowerUp.FP_Item_PowerUp'"), StaticMesh);
	ChangeLight(LightColor);
}

void AFP_Item_PowerUp::BeginPlay()
{
	Super::BeginPlay();

}

void AFP_Item_PowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFP_Item_PowerUp::OnProxOverlapBegin(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetName().Contains("Player"))
	{
		Cast<AFP_Player>(OtherActor)->SetStat(2, 10.f, 3.f, LightColor);
		Destroy();
	}
}