// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_Bullet.h"
#include "FP_Monster.h"
#include "FP_Weapon.h"

// Sets default values
AFP_Bullet::AFP_Bullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MonsterMesh(TEXT("StaticMesh'/Game/Bullet_Mesh.Bullet_Mesh'"));
	StaticMesh->SetStaticMesh(MonsterMesh.Object);


	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SphereComponent->InitSphereRadius(2.f);
	SphereComponent->SetupAttachment(RootComponent);

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AFP_Bullet::OnOverlapBegin);

	SetActorEnableCollision(true);
	SphereComponent->bGenerateOverlapEvents = true;
	SphereComponent->SetNotifyRigidBodyCollision(true);

}

// Called when the game starts or when spawned
void AFP_Bullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFP_Bullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeAcc += DeltaTime;
	if (TimeAcc > 3.f)
		Destroy();

	FVector NewLocation = GetActorLocation() + TargetDir * BulletSpeed * DeltaTime;
	SetActorLocation(NewLocation);
}

void AFP_Bullet::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AFP_Monster* TargetMonster = Cast<AFP_Monster>(OtherActor);
	if (TargetMonster != NULL)
	{
		TArray<AActor*> FoundActor;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFP_Weapon::StaticClass(), FoundActor);
		Cast<AFP_Weapon>(FoundActor[0])->DeleteTargetMonsterInArray(TargetMonster);
		TargetMonster->Destroy();
	}
		

	//Destroy();
}