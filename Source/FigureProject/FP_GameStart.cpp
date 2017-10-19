// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_GameStart.h"
#include "Button.h"
#include "Engine.h"
#include "FP_Weapon.h"
#include "FP_ProximityWeapon.h"
#include "FP_MonsterMgr.h"
#include "FP_PlayerController.h"
#include "FP_Player.h"
#include "FP_StageWidget.h"
#include "FP_StatusWidget.h"

void UFP_GameStart::NativeConstruct()
{
	Super::NativeConstruct();

	UButton* MeleeButton = (UButton*)GetWidgetFromName(TEXT("Melee"));
	MeleeButton->OnClicked.AddDynamic(this, &UFP_GameStart::ChooseMelee);

	UButton* RangeButton = (UButton*)GetWidgetFromName(TEXT("Range"));
	RangeButton->OnClicked.AddDynamic(this, &UFP_GameStart::ChooseRange);
}

void UFP_GameStart::ChooseMelee() 
{
	GetWorld()->SpawnActor<AFP_MonsterMgr>(FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f));

	FName Path = TEXT("Blueprint'/Game/FP_ProximityWeapon_BP.FP_ProximityWeapon_BP_C'");
	UClass* WeaponBP = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
	GetWorld()->SpawnActor<AFP_ProximityWeapon>(WeaponBP);

	AFP_PlayerController* PlayerController = Cast<AFP_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PlayerController->SetVisibility(0, ESlateVisibility::Hidden);
	PlayerController->SetVisibility(1, ESlateVisibility::Visible);

	UUserWidget* UserWidget = (PlayerController->GetWidgetMap(1));
	Cast<UFP_StageWidget>(UserWidget)->StageText = FText::FromString(TEXT("BABO"));


	Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0))->SetActorHiddenInGame(false);


}

void UFP_GameStart::ChooseRange()
{
	GetWorld()->SpawnActor<AFP_MonsterMgr>(FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f));
	GetWorld()->SpawnActor<AFP_Weapon>(FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f));

	AFP_PlayerController* PlayerController = Cast<AFP_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PlayerController->SetVisibility(0, ESlateVisibility::Hidden);
	PlayerController->SetVisibility(1, ESlateVisibility::Visible);

	UUserWidget* UserWidget = (PlayerController->GetWidgetMap(1));
	Cast<UFP_StageWidget>(UserWidget)->StageText = FText::FromString(TEXT("BABO"));


	Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0))->SetActorHiddenInGame(false);
}