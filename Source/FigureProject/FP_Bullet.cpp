// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_Bullet.h"


// Sets default values
AFP_Bullet::AFP_Bullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

}

