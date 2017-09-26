// Fill out your copyright notice in the Description page of Project Settings.

#include "Skills.h"


// Sets default values
ASkills::ASkills()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	//StaticMesh
	m_StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	m_StaticMesh->SetupAttachment(RootComponent);

	//StaticMesh'/Game/Box_Brush_StaticMesh.Box_Brush_StaticMesh'
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Sphere(TEXT("StaticMesh'/Game/Sphere_Brush_StaticMesh.Sphere_Brush_StaticMesh'"));
	m_StaticMesh->SetStaticMesh(Sphere.Object);
	m_StaticMesh->SetRelativeScale3D(FVector(3.f, 3.f, 1.f));

	m_SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	m_SphereComponent->InitSphereRadius(4.0f);
	m_SphereComponent->SetupAttachment(RootComponent);

	SetActorEnableCollision(true);
	m_SphereComponent->bGenerateOverlapEvents = true;
	m_SphereComponent->SetNotifyRigidBodyCollision(true);
}

// Called when the game starts or when spawned
void ASkills::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkills::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_fTimeAcc += DeltaTime;
	if (m_fTimeAcc > 3.f)
		Destroy();

	FVector CurrentLocation = GetActorLocation();
	SetActorLocation(CurrentLocation + FVector(DeltaTime*150.f, 0.f, 0.f));

}

