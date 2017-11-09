// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FP_Rune.h"
#include "FP_ComRuneGenerator.generated.h"

UCLASS()
class FIGUREPROJECT_API AFP_ComRuneGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFP_ComRuneGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	TMap<FColor, TMap<FString, TMap<uint64, FString>>> RuneProperty;
	TMap<uint64, FString> RedRuneOption;
	TMap<uint64, FString> GreenRuneOption;
	TMap<uint64, FString> BlueRuneOption;
	TMap<int, TMap<FString, TMap<FString, float>>> RuneStat;

public:
	static AFP_Rune* GenerateRune(TMap<FColor, TMap<FString, TMap<uint64, FString>>> _runeProperty, TMap<uint64, FString> _redRuneOption, TMap<uint64, FString> _greenRuneOption, TMap<uint64, FString> _blueRuneOption, TMap<int, TMap<FString, TMap<FString, float>>> _runeStat, AFP_Rune* _rune, int _stage);
};
