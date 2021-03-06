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
	enum TYPE{STAT, PROBABILITY, FIXED, PROJECTILE, AOE, DOT, EXP, DEBUFF, ETC};

public:
	struct RuneStat
	{
		float Damage = 1.f;
		float Speed = 1.f; //bullet speed
		float CoolTimeRatio = 1.f; // attack speed
		float Range = 1.f;
		int Tier = 1;
		//TArray<TYPE> Type;
		TMultiMap<FString, TYPE> Type;
	};

	struct DebuffStat
	{
		float Damage = 0.f;
		float Duration = 0.f;
		float Probability = 100.f;
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
	DebuffStat Ignite;
	DebuffStat Slow;
	DebuffStat Frozen;
	uint64 Property;
	float Tier3DropRate = 0.1f;
	float Tier2DropRate = 1.f;
	float Tier1DropRate = 3.5f;
	float Tier3MaxDropRate = 10.f;
	float Tier2MaxDropRate = 30.f;
	float Tier1MaxDropRate = 100.f;
	FString Name = "";
	TArray<FString> Option;
	TArray<float> OptionVal;
	bool bEquiped = false;
	float ExpBonus = 1.f;
	TArray<FString> Discription;

	//�·��߰�
	int iSkillIndex;
	int iSocketIndex;

public:	
	// Sets default values for this actor's properties
	AFP_Rune();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	AFP_Rune* Initiate(FColor _color, uint64 _property, RuneStat _stat, DebuffStat _ignite, DebuffStat _slow, DebuffStat _frozen, FString _name, TArray<FString> _option, TArray<float> _optionVal);
};
