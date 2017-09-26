// Fill out your copyright notice in the Description page of Project Settings.

#include "MonsterCreator.h"
#include "MagicianPawn.h"
#include "Monster.h"
#include "MyHUD.h"

// Sets default values
AMonsterCreator::AMonsterCreator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMonsterCreator::BeginPlay()
{
	Super::BeginPlay();

	m_pMagicianPawn = Cast<AMagicianPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

// Called every frame
void AMonsterCreator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	


	if (m_isSpawn == false && m_pMagicianPawn->GetisBattle() == true)
	{
		AMonster* pMonster = GetWorld()->SpawnActor<AMonster>(FVector(200.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f));
		pMonster->SetMonsterCreator(this);
		m_isSpawn = true;
	}

}

void AMonsterCreator::MonsterDead(void)
{
	m_isSpawn = false;
	m_pMagicianPawn->SetisBattle(false);

	AMyHUD* MyHUD = Cast<AMyHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
	MyHUD->SetDistance(1.f);
}

