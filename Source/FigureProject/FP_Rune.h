// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine.h"
#include "FP_Rune.generated.h"

UCLASS()
class FIGUREPROJECT_API AFP_Rune : public AActor
{
	GENERATED_BODY()

public:
	struct RuneStat
	{
		float Damage = 0.f;
		float Speed = 0.f; //bullet speed
		float CoolTimeRatio = 0.f; // attack speed
		float Range = 0.f;
		int Tier = 1;
	};
	
public:
	UTexture2D* RedTier1Icon;
	UTexture2D* RedTier2Icon;
	UTexture2D* RedTier3Icon;
	UTexture2D* RedTier4Icon;
	UTexture2D* GreenTier1Icon;
	UTexture2D* GreenTier2Icon;
	UTexture2D* GreenTier3Icon;
	UTexture2D* GreenTier4Icon;
	UTexture2D* BlueTier1Icon;
	UTexture2D* BlueTier2Icon;
	UTexture2D* BlueTier3Icon;
	UTexture2D* BlueTier4Icon;
	UTexture2D* Icon;
	FColor Color;
	RuneStat Stat;
	uint64 Property;
	float Tier3DropRate = 30.f;
	float Tier2DropRate = 60.f;
	float Tier3MaxDropRate = 30.f;
	float Tier2MaxDropRate = 60.f;
	FString Name = "";
	TArray<FString> Option;

public:	
	// Sets default values for this actor's properties
	AFP_Rune();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
