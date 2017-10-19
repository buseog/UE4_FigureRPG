// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_Skill.h"
#include "Engine.h"
#include "FP_ComProjectile.h"
#include "FP_ComCollision.h"
#include "FP_Player.h"
#include "FP_Monster.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"

// Sets default values
AFP_Skill::AFP_Skill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MonsterMesh(TEXT("StaticMesh'/Game/Box_StaticMesh1.Box_StaticMesh1'"));
	StaticMesh->SetStaticMesh(MonsterMesh.Object);

	ProxBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxProx"));
	ProxBox->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AFP_Skill::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFP_Skill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AFP_ComProjectile::MoveToTarget(this, FVector(0,0,0), 10 * DeltaTime);

	AFP_Monster* TargetMonster = AFP_ComCollision::Collision<UBoxComponent,AFP_Monster>(ProxBox);
	if (TargetMonster != nullptr)
		UE_LOG(LogClass, Log, TEXT("%s"), *TargetMonster->GetName());
}

