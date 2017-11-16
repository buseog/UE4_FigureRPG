// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_MonsterMgr.h"
#include "FP_Monster_Normal.h"
#include "FP_Monster_BossTypeA.h"
#include "FP_Monster_BossTypeB.h"

// Sets default values
int32 AFP_MonsterMgr::MonsterKillCnt = 0;
int32 AFP_MonsterMgr::Stage = 1;
AFP_MonsterMgr::AFP_MonsterMgr()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFP_MonsterMgr::BeginPlay()
{
	Super::BeginPlay();
	
	//AFP_Monster* SpawnedMonster = GetWorld()->SpawnActor<AFP_Monster_BossTypeA>(FVector(20.f, 20.f, 0.f), FRotator(0.f, 0.f, 0.f));
}

// Called every frame
void AFP_MonsterMgr::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	TimeAcc += DeltaTime;

	Stage = (MonsterKillCnt / 10) + 1;

	if (TimeAcc > MonsterSpawnTime)
	{
		TimeAcc = 0.f;

		FVector2D ViewportSize = GEngine->GameViewport->Viewport->GetSizeXY();

		int32 X = (ViewportSize.X / 2.f);
		int32 Y = (ViewportSize.Y / 2.f);

		int32 iSpawnX = FMath::RandRange(100, X) * (rand() % 2 - 0.5);
		int32 iSpawnY = FMath::RandRange(100, Y) * (rand() % 2 - 0.5);
		
		AFP_Monster* SpawnedMonster = nullptr;
		int iRand = rand() % 2;
		if(iRand == 0)
			SpawnedMonster = GetWorld()->SpawnActor<AFP_Monster_BossTypeA>(FVector(iSpawnX, iSpawnY, 0.f), FRotator(0.f, 0.f, 0.f));
		else
			SpawnedMonster = GetWorld()->SpawnActor<AFP_Monster_Normal>(FVector(iSpawnX, iSpawnY, 0.f), FRotator(0.f, 0.f, 0.f));


		//FVector2D ViewportSize = GEngine->GameViewport->Viewport->GetSizeXY();
		
		SpawnedMonster->HP = Stage * Stage + 3;
		SpawnedMonster->MaxHP = SpawnedMonster->HP;
		SpawnedMonster->Exp = SpawnedMonster->HP * 5;

		
		//MonsterArray.Add(SpawnedMonster);
	}

}

