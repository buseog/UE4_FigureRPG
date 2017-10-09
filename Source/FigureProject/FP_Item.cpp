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

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ItemMesh(TEXT("StaticMesh'/Game/Item_Mesh.Item_Mesh'"));
	StaticMesh->SetStaticMesh(ItemMesh.Object);

	const ConstructorHelpers::FObjectFinder<UTexture2D> IconName(TEXT("/Game/item.item"));
	Icon = IconName.Object;
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

}

