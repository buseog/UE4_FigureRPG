// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_MonsterMgr.h"
#include "FP_Monster_Normal.h"
#include "FP_Monster_BossTypeA.h"
#include "FP_Monster_BossTypeB.h"

// Sets default values
AFP_MonsterMgr::AFP_MonsterMgr()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFP_MonsterMgr::BeginPlay()
{
	Super::BeginPlay();
	
	AFP_Monster* SpawnedMonster = GetWorld()->SpawnActor<AFP_Monster_BossTypeA>(FVector(20.f, 20.f, 0.f), FRotator(0.f, 0.f, 0.f));
}

// Called every frame
void AFP_MonsterMgr::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//return;
	TimeAcc += DeltaTime;
	if (TimeAcc > MonsterSpawnTime)
	{
		TimeAcc = 0.f;

		//FVector2D ViewportSize = GEngine->GameViewport->Viewport->GetSizeXY();
		int32 iSpawnX = rand() % 50 * (rand() % 2 - 0.5) * 2;
		int32 iSpawnY = rand() % 70 * (rand() % 2 - 0.5) * 2;
		AFP_Monster* SpawnedMonster = GetWorld()->SpawnActor<AFP_Monster_BossTypeA>(FVector(iSpawnX, iSpawnY, 0.f), FRotator(0.f, 0.f, 0.f));
		//MonsterArray.Add(SpawnedMonster);
	}

}

