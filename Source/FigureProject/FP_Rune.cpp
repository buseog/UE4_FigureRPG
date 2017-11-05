// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_Rune.h"
#include "FP_RuneTable.h"
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
}

// Called when the game starts or when spawned
void AFP_Rune::BeginPlay()
{
	Super::BeginPlay();
	
	InitiateRune();
}

// Called every frame
void AFP_Rune::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFP_Rune::InitiateRune()
{
	//Tier
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFP_MonsterMgr::StaticClass(), FoundActors);

	int stage = Cast<AFP_MonsterMgr>(FoundActors[0])->Stage;

	Tier3DropRate = (float)stage * Tier3DropRate;
	Tier2DropRate = (float)stage * Tier2DropRate;

	if (Tier3DropRate >= Tier3MaxDropRate)
		Tier3DropRate = Tier3MaxDropRate;

	if (Tier2DropRate >= Tier2MaxDropRate)
		Tier2DropRate = Tier2MaxDropRate;

	float DropRate = FMath::FRandRange(0.f, 101.f);

	if (DropRate <= Tier3DropRate)
		Stat.Tier = 3;
	else if (DropRate <= Tier2DropRate)
		Stat.Tier = 2;
	else
		Stat.Tier = 1;

	//Color, Property
	int random = FMath::FRandRange(0, 3);
	int i = 0;
	
	switch (random)
	{
	case 0:
		Color = FColor::Red;
		for (i = 0; i < Stat.Tier; ++i)
		{
			while (1)
			{
				random = FMath::FRandRange(0, Red.MaxNum);

				if (!(Property & (uint64)pow(16, random)))
					break;
			}

			Property = Property | (uint64)pow(16, random);
			/*UE_LOG(LogClass, Log, TEXT("random : %d"), random);
			UE_LOG(LogClass, Log, TEXT("Property : %d"), Property);
			UE_LOG(LogClass, Log, TEXT("%s"), *Name);*/
		}
		break;

	case 1:
		Color = FColor::Green;
		for (i = 0; i < Stat.Tier; ++i)
		{
			while (1)
			{
				random = FMath::FRandRange(0, Red.MaxNum);

				if (!(Property & (uint64)pow(16, random)))
					break;
			}

			Property = Property | (uint64)pow(16, random);
			/*UE_LOG(LogClass, Log, TEXT("random : %d"), random);
			UE_LOG(LogClass, Log, TEXT("Property : %d"), Property);
			UE_LOG(LogClass, Log, TEXT("%s"), *Name);*/
		}
		break;

	case 2:
		Color = FColor::Blue;
		for (i = 0; i < Stat.Tier; ++i)
		{
			while (1)
			{
				random = FMath::FRandRange(0, Red.MaxNum);

				if (!(Property & (uint64)pow(16, random)))
					break;
			}

			Property = Property | (uint64)pow(16, random);
			/*UE_LOG(LogClass, Log, TEXT("random : %d"), random);
			UE_LOG(LogClass, Log, TEXT("Property : %d"), Property);
			UE_LOG(LogClass, Log, TEXT("%s"), *Name);*/
		}
		break;
	}

	//icon, name
	if (Color == FColor::Red)
	{
		if (Stat.Tier == 1)
			Icon = RedTier1Icon;
		else if (Stat.Tier == 2)
			Icon = RedTier2Icon;
		else if (Stat.Tier == 3)
			Icon = RedTier3Icon;
		else
			Icon = RedTier4Icon;

		if (Property & Red.GUIDED)
			Name += Red.NAME_GUIDED;
		if (Property & Red.STUN)
			Name += Red.NAME_STUN;
		if (Property & Red.KNOCKBACK)
			Name += Red.NAME_KNOCKBACK;
		if (Property & Red.LIFESTEAL)
			Name += Red.NAME_LIFESTEAL;
		if (Property & Red.IGNITE)
			Name += Red.NAME_IGNITE;
		if (Property & Red.AREAUP)
			Name += Red.NAME_AREAUP;
		if (Property & Red.RANDOMEFFECT)
			Name += Red.NAME_RANDOMEFFECT;
	}
	else if (Color == FColor::Green)
	{
		if (Stat.Tier == 1)
			Icon = GreenTier1Icon;
		else if (Stat.Tier == 2)
			Icon = GreenTier2Icon;
		else if (Stat.Tier == 3)
			Icon = GreenTier3Icon;
		else
			Icon = GreenTier4Icon;

		if (Property & Green.ATTACKSPEEDUP)
			Name += Green.NAME_ATTACKSPEEDUP;
		if (Property & Green.BULLETSPEEDUP)
			Name += Green.NAME_BULLETSPEEDUP;
		if (Property & Green.DAMAGEUP)
			Name += Green.NAME_DAMAGEUP;
		if (Property & Green.DAMAGEUPTOSQARE)
			Name += Green.NAME_DAMAGEUPTOSQARE;
		if (Property & Green.N)
			Name += Green.NAME_N;
		if (Property & Green.O)
			Name += Green.NAME_O;
		if (Property & Green.P)
			Name += Green.NAME_P;
	}
	else
	{
		if (Stat.Tier == 1)
			Icon = BlueTier1Icon;
		else if (Stat.Tier == 2)
			Icon = BlueTier2Icon;
		else if (Stat.Tier == 3)
			Icon = BlueTier3Icon;
		else
			Icon = BlueTier4Icon;

		if (Property & Blue.RANGEUP)
			Name += Blue.NAME_RANGEUP;
		if (Property & Blue.BULLETSPEEDUP)
			Name += Blue.NAME_BULLETSPEEDUP;
		if (Property & Blue.C)
			Name += Blue.NAME_C;
		if (Property & Blue.D)
			Name += Blue.NAME_D;
		if (Property & Blue.E)
			Name += Blue.NAME_E;
		if (Property & Blue.F)
			Name += Blue.NAME_F;
		if (Property & Blue.G)
			Name += Blue.NAME_G;
	}

	

	//UE_LOG(LogClass, Log, TEXT("%d"), Stat.Tier);
	//UE_LOG(LogClass, Log, TEXT("%f, %f, %f"), (float)Color.R, (float)Color.G, (float)Color.B);
	//UE_LOG(LogClass, Log, TEXT("%s"), *Icon->GetName());
	//UE_LOG(LogClass, Log, TEXT("Property : %d"), Property);
	//UE_LOG(LogClass, Log, TEXT("Name : %s"), *Name);
}