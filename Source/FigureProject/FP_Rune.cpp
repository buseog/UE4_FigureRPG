// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_Rune.h"
//#include "FP_RuneTable.h"
#include "FP_MonsterMgr.h"


// Sets default values
AFP_Rune::AFP_Rune()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UTexture2D> RedTier1(TEXT("Texture2D'/Game/Icon/RedTriangleRune.RedTriangleRune'"));
	RedTier1Icon = RedTier1.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D> RedTier2(TEXT("Texture2D'/Game/Icon/RedSquareRune.RedSquareRune'"));
	RedTier2Icon = RedTier2.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D> RedTier3(TEXT("Texture2D'/Game/Icon/RedPentagonRune.RedPentagonRune'"));
	RedTier3Icon = RedTier3.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D> RedTier4(TEXT("Texture2D'/Game/Icon/RedCircleRune.RedCircleRune'"));
	RedTier4Icon = RedTier4.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D> GreenTier1(TEXT("Texture2D'/Game/Icon/GreenTriangleRune.GreenTriangleRune'"));
	GreenTier1Icon = GreenTier1.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D> GreenTier2(TEXT("Texture2D'/Game/Icon/GreenSquareRune.GreenSquareRune'"));
	GreenTier2Icon = GreenTier2.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D> GreenTier3(TEXT("Texture2D'/Game/Icon/GreenPentagonRune.GreenPentagonRune'"));
	GreenTier3Icon = GreenTier3.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D> GreenTier4(TEXT("Texture2D'/Game/Icon/GreenCircleRune.GreenCircleRune'"));
	GreenTier4Icon = GreenTier4.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D> BlueTier1(TEXT("Texture2D'/Game/Icon/BlueTriangleRune.BlueTriangleRune'"));
	BlueTier1Icon = BlueTier1.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D> BlueTier2(TEXT("Texture2D'/Game/Icon/BlueSquareRune.BlueSquareRune'"));
	BlueTier2Icon = BlueTier2.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D> BlueTier3(TEXT("Texture2D'/Game/Icon/BluePentagonRune.BluePentagonRune'"));
	BlueTier3Icon = BlueTier3.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D> BlueTier4(TEXT("Texture2D'/Game/Icon/BlueCircleRune.BlueCircleRune'"));
	BlueTier4Icon = BlueTier4.Object;

	OptionVal.Init(NULL, 4);
}

// Called when the game starts or when spawned
void AFP_Rune::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFP_Rune::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogClass, Log, TEXT("%d"), Stat.Tier);
}

AFP_Rune* AFP_Rune::Initiate(FColor _color, uint64 _property, RuneStat _stat, FString _name, TArray<FString> _option, TArray<float> _optionVal)
{
	if (_stat.Tier == 1)
	{
		if (_color == FColor::Red)
			Icon = RedTier1Icon;
		else if (_color == FColor::Green)
			Icon = GreenTier1Icon;
		else
			Icon = BlueTier1Icon;
	}
	else if (_stat.Tier == 2)
	{
		if (_color == FColor::Red)
			Icon = RedTier2Icon;
		else if (_color == FColor::Green)
			Icon = GreenTier2Icon;
		else
			Icon = BlueTier2Icon;
	}
	else if (_stat.Tier == 3)
	{
		if (_color == FColor::Red)
			Icon = RedTier3Icon;
		else if (_color == FColor::Green)
			Icon = GreenTier3Icon;
		else
			Icon = BlueTier3Icon;
	}

	Color = _color;
	Property = _property;
	Name = _name;
	Option = _option;
	OptionVal = _optionVal;
	Stat = _stat;

	return this;
}