// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_Monster.h"
#include "FP_Weapon.h"
#include "Engine.h"
#include "FP_HUD.h"
#include "FP_ItemDropRate.h"

// Sets default values
AFP_Monster::AFP_Monster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MonsterMesh(TEXT("StaticMesh'/Game/Sphere_Monster.Sphere_Monster'"));
	StaticMesh->SetStaticMesh(MonsterMesh.Object);


	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SphereComponent->InitSphereRadius(5.0f);
	SphereComponent->SetupAttachment(RootComponent);

	SetActorEnableCollision(true);
	SphereComponent->bGenerateOverlapEvents = true;
	SphereComponent->SetNotifyRigidBodyCollision(true);

	HP = 2.f;
	Damage = 1.f;
}

// Called when the game starts or when spawned
void AFP_Monster::BeginPlay()
{
	Super::BeginPlay();

	DropRate = FMath::FRandRange(0.f, 100.f);
	IncreaseStage();
}

// Called every frame
void AFP_Monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	if (CurrentLocation.Size() < 1)
	{
		TArray<AActor*> FoundActor;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFP_Weapon::StaticClass(), FoundActor);
		Cast<AFP_Weapon>(FoundActor[0])->DeleteTargetMonsterInArray(this);
		Destroy();
		return;
	}

	FVector Direction = CurrentLocation * -1.f;
	Direction.Normalize();

	FVector NewLocation = CurrentLocation + Direction * DeltaTime * Speed;
	SetActorLocation(NewLocation);
}

void AFP_Monster::BeginDestroy()
{
	Super::BeginDestroy();

}

void AFP_Monster::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	DropItem();
}

float AFP_Monster::TakeDamage(float Damage, struct FDamageEvent const &DamageEvent, class AController* EventIntigator, class AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventIntigator, DamageCauser);

	if (ActualDamage > 0.f)
	{
		HP -= ActualDamage;

		if (HP <= 0.f)
			bDestroy = true;
	}

	return ActualDamage;
}

void AFP_Monster::IncreaseStage()
{
	int Stage = Cast<AFP_HUD>(GetWorld()->GetFirstPlayerController()->GetHUD())->GetStage();

	HP = Stage + 1;
	Damage = Stage;
}

void AFP_Monster::DropItem()
{
	float ItemDropRate = 100.f * ITEMNAME_DropRate;
	
	if (DropRate <= ItemDropRate && bDestroy)
		Cast<AFP_HUD>(GetWorld()->GetFirstPlayerController()->GetHUD())->DropItem(this->GetActorLocation());

	bDestroy = false;
}