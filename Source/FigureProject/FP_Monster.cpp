// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_Monster.h"
#include "FP_Weapon.h"
#include "Engine.h"

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
}

// Called when the game starts or when spawned
void AFP_Monster::BeginPlay()
{
	Super::BeginPlay();


	
}

// Called every frame
void AFP_Monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}
