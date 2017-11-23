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
	
	float distance = FVector::Dist(this->GetActorLocation(), Player->GetActorLocation());

	AFP_ComProjectile::MoveToTarget(this, TargetDirection, 100.f * DeltaTime);

	CurrentTime += DeltaTime;
	Scale += DeltaTime;
	FireWallProxScale += DeltaTime * 0.8f;

	if (CurrentTime >= SpawnDelay)
	{
		if (distance >= AttackRange)
		{
			Destroy();
			return;
		}

		CurrentTime = 0.f;
		FVector Location = this->GetActorLocation();

		if (SkillName == "FireWall")
		{
			FireSkill = Weapon->CustomSpawn<AFP_FireWall>(this->GetActorLocation(), this->GetActorRotation());
			Cast<AFP_FireWall>(FireSkill)->SetActorScale3D(FVector(0.1f + Scale * 0.3f, 0.1f + Scale * 0.3f, 0.1f));
			Cast<AFP_FireWall>(FireSkill)->Scale = FireWallProxScale;
		}
	}
}

void AFP_FireBlastSpawnPoint::SetSkill(FString _skillName, float _spawnDelay, float _attRange, float _speed)
{
	SkillName = _skillName;
	SpawnDelay = _spawnDelay;
	CurrentTime = SpawnDelay;
	AttackRange = _attRange;
	Stat.Speed = _speed;

	if (SkillName == "FireWall")
	{
		FireSkill = GetWorld()->SpawnActor<AFP_FireWall>(AFP_FireWall::StaticClass(), FTransform(FRotator(0.f, 0.f, 0.f), this->GetActorLocation(), FVector(0.1f + Scale * 0.3f, 0.1f + Scale * 0.3f, 0.1f)));
		Cast<AFP_FireWall>(FireSkill)->Scale = FireWallProxScale;
	}
}