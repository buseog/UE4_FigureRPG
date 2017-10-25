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

	AFP_ComProjectile::MoveToTarget(this, TargetDirection, Player->GetStatus().BulletSpeed * Speed * DeltaTime);

	CurrentTime += DeltaTime;

	if (CurrentTime >= SpawnDelay)
	{
		if (CurrentSpawnNum >= MaxSpawnNum)
			Destroy();

		++CurrentSpawnNum;
		CurrentTime = 0.f;
		FVector Location = this->GetActorLocation();

		if(SkillName == "FireBlast")
			FireSkill = GetWorld()->SpawnActor<AFP_FireBlast>(Location, FRotator(0.f, 0.f, 0.f));
		else if (SkillName == "FireWall")
		{
			FireSkill = GetWorld()->SpawnActor<AFP_FireWall>(Location, FRotator(0.f, 0.f, 0.f));
			FireSkill->SetActorScale3D(FVector(0.3f, 0.3f, 0.3f));
		}
	}
}

void AFP_FireBlastSpawnPoint::SetSkill(FString _skillName, float _spawnDelay, int _maxSpawnNum, float _speed)
{
	SkillName = _skillName;
	SpawnDelay = _spawnDelay;
	CurrentTime = SpawnDelay;
	MaxSpawnNum = _maxSpawnNum;
	Speed = _speed;
}