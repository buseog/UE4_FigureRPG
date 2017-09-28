// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_Player_Circle.h"

AFP_Player_Circle::AFP_Player_Circle()
{
	Status.Hp = 5.f;
	Status.MaxHp = 5.f;
	Status.HpRegen = 0.f;
	Status.Attack = 3.f;
	Status.AttackRange = 5.f;
	Status.AttackSpeed = 1.f;
	Status.BulletSpeed = 1.f;
	Status.Critical = 1.f;
	Status.CriticalDamage = 1.f;
	Status.Splash = 1.f;
}

void AFP_Player_Circle::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFP_Player_Circle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

