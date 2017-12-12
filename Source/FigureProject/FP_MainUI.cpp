// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_MainUI.h"
#include "FP_PlayerController.h"
#include "Engine.h"
#include "FP_SkillUI.h"
#include "FP_InventoryWidget.h"
#include "FP_MonsterMgr.h"
#include "FP_Skill.h"
#include "FP_Player.h"
#include "FP_FireBall.h"
#include "FP_FireBlast.h"
#include "FP_FireWall.h"
#include "FP_IceBall.h"
#include "FP_IceBlast.h"
#include "FP_IceOrb.h"
#include "FP_ComMessageUI.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformMisc.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"


void UFP_MainUI::NativeConstruct()
{
	Super::NativeConstruct();


	
	
}

bool UFP_MainUI::Initialize()
{
	Super::Initialize();

	//UE_LOG(LogClass, Log, TEXT("INIT"));

	UButton* Button = (UButton*)GetWidgetFromName(TEXT("Stat"));
	Button->OnClicked.AddDynamic(this, &UFP_MainUI::Button_Stat);
	ButtonArray.Add(Button);

	Button = (UButton*)GetWidgetFromName(TEXT("Skill"));
	Button->OnClicked.AddDynamic(this, &UFP_MainUI::Button_Skill);
	ButtonArray.Add(Button);

	Button = (UButton*)GetWidgetFromName(TEXT("Rune"));
	Button->OnClicked.AddDynamic(this, &UFP_MainUI::Button_Rune);
	ButtonArray.Add(Button);

	Button = (UButton*)GetWidgetFromName(TEXT("Rev"));
	Button->OnClicked.AddDynamic(this, &UFP_MainUI::Button_Rev);
	ButtonArray.Add(Button);


	Button = (UButton*)GetWidgetFromName(TEXT("Exit"));
	Button->OnClicked.AddDynamic(this, &UFP_MainUI::Button_Exit);
	ButtonArray.Add(Button);

	return true;
}

void UFP_MainUI::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	//UE_LOG(LogClass, Log, TEXT("%f"), (float)eState);

	if (eState == IDLE)
		return;

	if (eState == START)
		TimeAcc += DeltaTime;
	else
		TimeAcc -= DeltaTime;

	float Angle = TimeAcc * -1000.f;
	float NewScale = 0.f;
	int RotNum = 2;
	if (Angle > -360.f * RotNum && Angle < 0.f)
	{
		NewScale = TimeAcc * 1.5f;
		NewScale = FMath::Clamp(NewScale, 0.f, 1.f);

		

		for (size_t i = 0; i < ButtonArray.Num(); ++i)
		{
			ButtonArray[i]->SetRenderAngle(Angle);
			ButtonArray[i]->SetRenderScale(FVector2D(NewScale, NewScale));

			FVector2D NewLocation;
			float Radius = TimeAcc * 500.f;
			Radius = FMath::Clamp(Radius, 0.f, 500.f);

			float AngleOffSet = 2 * PI / ButtonArray.Num();

			NewLocation.X = Radius * cosf(TimeAcc * -5.f + AngleOffSet * i) - 100.f;
			NewLocation.Y = Radius * sinf(TimeAcc * -5.f + AngleOffSet * i) - 100.f;
			ButtonArray[i]->SetRenderTranslation(NewLocation);
		}
	}
	else
	{
		for (size_t i = 0; i < ButtonArray.Num(); ++i)
		{
			ButtonArray[i]->SetRenderAngle(0.f);
		}

		if(eState == START)
			eState = IDLE;
		else if (eState == END)
		{
			eState = IDLE;
			RemoveFromViewport();
		}
	}

	
}

void UFP_MainUI::Button_Stat()
{

	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AFP_PlayerController* PC = Cast<AFP_PlayerController>(Controller);
	PC->GetWidgetMap(AFP_PlayerController::STATUS)->AddToViewport();

	SetMyVisibility(ESlateVisibility::Hidden);
	
}


void UFP_MainUI::Button_Skill()
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AFP_PlayerController* PC = Cast<AFP_PlayerController>(Controller);
	PC->GetWidgetMap(AFP_PlayerController::SKILLUI)->AddToViewport();

	SetMyVisibility(ESlateVisibility::Hidden);
	
}

void UFP_MainUI::Button_Rev()
{
	if (AFP_MonsterMgr::Stage < 20)
	{
		APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		AFP_PlayerController* PC = Cast<AFP_PlayerController>(Controller);
		AFP_ComMessageUI::ShowMessage(PC, FText::FromString("available after 20 stages"), 2.f);
		return;
	}
		

	AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (nullptr == pPlayer)
		return;

	pPlayer->Status = pPlayer->InitStatus;
	pPlayer->SkillLv = pPlayer->InitSkillLv;
	pPlayer->Level = pPlayer->InitLevel;
	TSubclassOf<AFP_Player> PlayerClass = AFP_Player::StaticClass();
	AFP_Player* Player_CDO = PlayerClass->GetDefaultObject<AFP_Player>();
	//pPlayer->Gem = Player_CDO->Gem;
	
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AFP_PlayerController* PC = Cast<AFP_PlayerController>(Controller);

	ResetSocket<AFP_FireBall>();
	ResetSocket<AFP_FireBlast>();
	ResetSocket<AFP_FireWall>();
	ResetSocket<AFP_IceBall>();
	ResetSocket<AFP_IceBlast>();
	ResetSocket<AFP_IceOrb>();

	UFP_InventoryWidget* Inventory = Cast<UFP_InventoryWidget>(PC->GetWidgetMap(AFP_PlayerController::INVENTORY));
	Inventory->AddRune();
	pPlayer->Gem += (int)FMath::FRandRange(AFP_MonsterMgr::Stage * 0.1f, AFP_MonsterMgr::Stage * 0.15f);
	




	AFP_MonsterMgr::Stage = 1;
	AFP_MonsterMgr::MonsterKillCnt = 0;
	PC->RestartLevel();
	PC->isRev = true;
}

void UFP_MainUI::Button_Rune()
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AFP_PlayerController* PC = Cast<AFP_PlayerController>(Controller);
	
	Cast<UFP_InventoryWidget>(PC->GetWidgetMap(AFP_PlayerController::INVENTORY))->bFromMain = true;
	Cast<UFP_InventoryWidget>(PC->GetWidgetMap(AFP_PlayerController::INVENTORY))->Order = UFP_InventoryWidget::SORTORDER::COLOR;
	Cast<UFP_InventoryWidget>(PC->GetWidgetMap(AFP_PlayerController::INVENTORY))->SortInventory();

	PC->GetWidgetMap(AFP_PlayerController::INVENTORY)->AddToViewport();
	SetMyVisibility(ESlateVisibility::Hidden);

}

void UFP_MainUI::OpenInventoryFromSkill(UFP_InventoryWidget::SORTORDER _order)
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AFP_PlayerController* PC = Cast<AFP_PlayerController>(Controller);
	UUserWidget* RuneWidget = PC->GetWidgetMap(AFP_PlayerController::INVENTORY);

	if (RuneWidget->IsValidLowLevel() == false)
	{
		FName Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_Inventory_BP.FP_Inventory_BP_C'");
		TSubclassOf<UFP_InventoryWidget> Inventory = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
		UFP_InventoryWidget* InventoryWidget = CreateWidget<UFP_InventoryWidget>(PC, Inventory);
		PC->WidgetArray[AFP_PlayerController::INVENTORY] = InventoryWidget;
	}

	if (_order == Cast<UFP_InventoryWidget>(PC->GetWidgetMap(AFP_PlayerController::INVENTORY))->Order)
	{
		Cast<UFP_InventoryWidget>(PC->GetWidgetMap(AFP_PlayerController::INVENTORY))->CheckEquiped(_order);
		PC->GetWidgetMap(AFP_PlayerController::INVENTORY)->AddToViewport();
	}
	else
	{
		Cast<UFP_InventoryWidget>(PC->GetWidgetMap(AFP_PlayerController::INVENTORY))->Order = _order;
		Cast<UFP_InventoryWidget>(PC->GetWidgetMap(AFP_PlayerController::INVENTORY))->SortInventory();
		PC->GetWidgetMap(AFP_PlayerController::INVENTORY)->AddToViewport();
	}
}

void UFP_MainUI::SetMyVisibility(ESlateVisibility _visibility)
{
	for (int i = 0; i < ButtonArray.Num(); ++i)
	{
		ButtonArray[i]->SetVisibility(_visibility);
	}
}

void UFP_MainUI::Button_Exit()
{
	//FGenericPlatformMisc::RequestExit(true);

	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AFP_PlayerController* PC = Cast<AFP_PlayerController>(Controller);
	
	UKismetSystemLibrary::QuitGame(GetWorld(), PC, EQuitPreference::Quit);
}