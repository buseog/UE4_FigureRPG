// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_FireBlastSpawnPoint.h"
#include "FP_ComProjectile.h"
#include "FP_FireBlast.h"
#include "FP_FireWall.h"


// Sets default values
AFP_FireBlastSpawnPoint::AFP_FireBlastSpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Stat.Speed = 0.1f;
}

// Called when the game starts or when spawned
void AFP_FireBlastSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
	Player = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (nullptr == Player)
		return;
}

// Called every frame
void AFP_FireBlastSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AFP_ComProjectile::MoveToTarget(this, TargetDirection, Player->GetStatus().BulletSpeed * Stat.Speed * DeltaTime);

	CurrentTime += DeltaTime;
	Scale += DeltaTime;

	if (CurrentTime >= SpawnDelay)
	{
		if (CurrentSpawnNum >= MaxSpawnNum)
		{
			Destroy();
			return;
		}

		++CurrentSpawnNum;
		CurrentTime = 0.f;
		FVector Location = this->GetActorLocation();

		if(SkillName == "FireBlast")
			FireSkill = GetWorld()->SpawnActor<AFP_FireBlast>(Location, FRotator(0.f, 0.f, 0.f));
		else if (SkillName == "FireWall")
		{
			
			FireSkill = GetWorld()->SpawnActor<AFP_FireWall>(AFP_FireWall::StaticClass(),FTransform(FRotator(0.f,0.f,0.f),Location, FVector(0.1f + Scale * 0.3f, 0.1f + Scale * 0.3f, 0.1f)));
			//FireSkill->SetActorScale3D(FVector(0.1f + Scale * 2.f, 0.1f + Scale * 2.f, 0.1f + Scale * 2.f));
		}
	}
}

void AFP_FireBlastSpawnPoint::SetSkill(FString _skillName, float _spawnDelay, int _maxSpawnNum, float _speed)
{
	SkillName = _skillName;
	SpawnDelay = _spawnDelay;
	CurrentTime = SpawnDelay;
	MaxSpawnNum = _maxSpawnNum;
	Stat.Speed = _speed;
}