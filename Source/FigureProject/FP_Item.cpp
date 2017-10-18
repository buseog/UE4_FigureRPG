// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_Item.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

// Sets default values
AFP_Item::AFP_Item()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Name = "Item";
	Quantity = 1;
	Speed = 10.f;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UTexture2D> IconName(TEXT("Texture2D'/Game/item.item'"));
	Icon = IconName.Object;

	//ChangeMesh(FString("StaticMesh'/Game/FP_Item_MonsterRegenUp.FP_Item_MonsterRegenUp'"), StaticMesh);

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLight->Intensity = 500.f;
	//PointLight->LightColor = FColor(0, 0, 255);
	PointLight->AttenuationRadius = 10.f;
	PointLight->MoveComponent(FVector(this->GetActorLocation().X, this->GetActorLocation().Y, this->GetActorLocation().Z - 10.f), FRotator(), false);
	PointLight->SetupAttachment(RootComponent);

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetSphereRadius(4.f);
	/*SetActorEnableCollision(true);
	CollisionSphere->bGenerateOverlapEvents = true;
	CollisionSphere->SetNotifyRigidBodyCollision(true);*/
	CollisionSphere->SetupAttachment(RootComponent);
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AFP_Item::OnProxOverlapBegin);
}

// Called when the game starts or when spawned
void AFP_Item::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFP_Item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveToPlayer(DeltaTime);
}

void AFP_Item::MoveToPlayer(float DeltaTime)
{
	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FVector Dir = PlayerLocation - this->GetActorLocation();
	
	Dir.Normalize();

	this->SetActorLocation(this->GetActorLocation() + Dir * DeltaTime * Speed);
}

void AFP_Item::ChangeLight(FColor Color, float Intensity, float Radious)
{
	PointLight->LightColor = Color;
	PointLight->Intensity = Intensity;
	PointLight->AttenuationRadius = Radious;
}

void AFP_Item::ChangeMesh(FString Ref, UStaticMeshComponent* _StaticMesh)
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> ItemMesh(*Ref);
	_StaticMesh->SetStaticMesh(ItemMesh.Object);

}

void AFP_Item::OnProxOverlapBegin(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}