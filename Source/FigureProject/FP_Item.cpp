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
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	const ConstructorHelpers::FObjectFinder<UTexture2D> IconName(TEXT("/Game/item.item"));
	Icon = IconName.Object;
	RootComponent = Cast<USceneComponent>(Mesh);
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

