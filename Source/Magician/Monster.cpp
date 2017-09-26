// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster.h"


// Sets default values
AMonster::AMonster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	//StaticMesh
	m_StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	m_StaticMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Box(TEXT("StaticMesh'/Game/Box_Brush_StaticMesh.Box_Brush_StaticMesh'"));
	m_StaticMesh->SetStaticMesh(Box.Object);

	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/Red.Red'"));
	m_StaticMesh->SetMaterial(0, Material.Object);

	m_SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	m_SphereComponent->InitSphereRadius(20.0f);
	m_SphereComponent->SetupAttachment(RootComponent);

	m_SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AMonster::OnOverlapBegin);

	SetActorEnableCollision(true);
	m_SphereComponent->bGenerateOverlapEvents = true;
	m_SphereComponent->SetNotifyRigidBodyCollision(true);
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();

	
	
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonster::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (m_pMonsterCreator != NULL && m_pMonsterCreator->GetisSpawn() == true)
	{
		m_pMonsterCreator->MonsterDead();
		Destroy();
	}
}

