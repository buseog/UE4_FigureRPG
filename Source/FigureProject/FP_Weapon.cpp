// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_Weapon.h"
#include "Engine.h"
#include "FP_Bullet.h"
#include "FP_Player.h"
#include "FP_FireBall.h"
#include "FP_Skill.h"
#include "FP_HUD.h"
#include "FP_IceBall.h"

struct CompareDist
{
	CompareDist(FVector _FirePoint) : FirePoint(_FirePoint) {};
	
	FVector FirePoint;

	bool operator()(const AFP_Monster& A, const AFP_Monster& B) const
	{
		FVector Avector = A.GetActorLocation() - FirePoint;
		FVector Bvector = B.GetActorLocation() - FirePoint;

		return Avector.Size() < Bvector.Size();
	}
};

// Sets default values
AFP_Weapon::AFP_Weapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->InitSphereRadius(50.f);

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AFP_Weapon::OnOverlapBegin);

	SetActorEnableCollision(true);
	SphereComponent->bGenerateOverlapEvents = true;
	SphereComponent->SetNotifyRigidBodyCollision(true);
}

// Called when the game starts or when spawned
void AFP_Weapon::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFP_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	float fYaw = GetActorRotation().Yaw;
	FirePoint.X = 10.f * cosf((fYaw * PI) / 180.f);
	FirePoint.Y = 10.f * sinf((fYaw * PI) / 180.f);
	
	//SphereRadius
	AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (nullptr == pPlayer)
		return;
	
	SphereComponent->SetSphereRadius(pPlayer->GetStatus().AttackRange);

	if(TargetMonsters.Num() >= 1)
	{
		TargetMonsters.Sort(CompareDist(FirePoint));

		FVector TargetEnemy = TargetMonsters[0]->GetActorLocation();
		//DrawDebugLine(GetWorld(), FVector(0.f, 0.f, 0.f), TargetEnemy, FColor::Red);

		TargetEnemy.Normalize();

		float fCos = FVector::DotProduct(TargetEnemy, FVector(1.f, 0.f, 0.f));
		AngleZ = acosf(fCos);
		if(TargetEnemy.Y < 0)
			AngleZ = 2 * PI - acosf(fCos);

		SetActorRotation(FRotator(0.f, AngleZ * 180.f / PI, 0.f));

		//attack
		TimeAcc += DeltaTime;
		if (TimeAcc > pPlayer->GetStatus().AttackSpeed)
		{
			TimeAcc = 0.f;
			SpawnSkill();
		}
	}
		
	//FString Test = FString::FromInt(TargetMonsters.Num());
	//GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Blue, Test);
	

}

void AFP_Weapon::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AFP_Monster* TargetMonster = Cast<AFP_Monster>(OtherActor);
	if (TargetMonster != NULL)
		TargetMonsters.Add(TargetMonster);
}


void AFP_Weapon::DeleteTargetMonsterInArray(AFP_Monster* _monster)
{
	TargetMonsters.Remove(_monster);

}

void AFP_Weapon::SpawnSkill()
{
	AFP_Skill* Skill = nullptr;
	switch (ActiveSkill)
	{
	case FIREBALL:
		Skill = GetWorld()->SpawnActor<AFP_FireBall>(FirePoint, FRotator(0.f, AngleZ * 180.f / PI, 0.f));
		Skill->SetTargetDirection(TargetMonsters[0]->GetActorLocation());
		break;
	case ICEBALL:
		Skill = GetWorld()->SpawnActor<AFP_IceBall>(FirePoint, FRotator(0.f, AngleZ * 180.f / PI, 0.f));
		Skill->SetTargetDirection(TargetMonsters[0]->GetActorLocation());
		break;
	}
	


	
}
