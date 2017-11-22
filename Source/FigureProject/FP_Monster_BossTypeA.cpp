// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_Monster_BossTypeA.h"
#include "FP_Weapon.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"

void AFP_Monster_BossTypeA::BeginPlay()
{
	Super::BeginPlay();

	FVector NewScale = FVector(2.f, 2.f, 2.f);
	//SetActorScale3D(NewScale);

	

	Distance = GetActorLocation().Size();

	MaxHP = 4.f;
	HP = MaxHP;

	SphereComponent->SetSphereRadius(8.f);

	int iRand = FMath::RandRange(0, 3);
	PaperSprite->SetSprite(MonsterIconArray[iRand]);
	PaperSprite->SetRelativeScale3D(FVector(0.075f, 0.075f, 0.075f));
	OriginIcon = (AFP_Monster::MONSTERICON)iRand;

}

void AFP_Monster_BossTypeA::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float speedOffset = 1.f;

	for (int i = 0; i < StateMgr.Num(); ++i)
	{
		if (StateMgr[i].eState == FROZEN || StateMgr[i].eState == FROZEN)
		{
			speedOffset = StateMgr[i].SpeedOffset;
			break;
		}
	}

	TimeAcc += DeltaTime * speedOffset;
	Distance -= DeltaTime*3.f *speedOffset;
	float fNewDist = Distance + cosf(TimeAcc);

	FVector NewLocation = GetActorLocation();
	NewLocation.X = cosf(TimeAcc) * fNewDist;
	NewLocation.Y = sinf(TimeAcc) * fNewDist;
	//x*x + y*y = d*d
	SetActorLocation(NewLocation);
		

	//GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Blue, TEXT("Test"));
}