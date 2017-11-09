// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_MainUI.h"
#include "FP_PlayerController.h"
#include "Engine.h"
#include "FP_SkillUI.h"
#include "FP_InventoryWidget.h"


void UFP_MainUI::NativeConstruct()
{
	Super::NativeConstruct();


	
	
}

bool UFP_MainUI::Initialize()
{
	Super::Initialize();

	UE_LOG(LogClass, Log, TEXT("INIT"));

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
			float Radius = TimeAcc * 200.f;
			Radius = FMath::Clamp(Radius, 0.f, 100.f);

			float AngleOffSet = 2 * PI / ButtonArray.Num();

			NewLocation.X = Radius * cosf(TimeAcc * -5.f + AngleOffSet * i) - 32.5f;
			NewLocation.Y = Radius * sinf(TimeAcc * -5.f + AngleOffSet * i) - 32.5f;
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
	UUserWidget* StatWidget = PC->GetWidgetMap(AFP_PlayerController::STATUS);

	if (StatWidget->IsValidLowLevel() == false)
	{
		FName Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_StatusWidget_BP.FP_StatusWidget_BP_C'");
		TSubclassOf<UFP_StatusWidget> Widget = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
		UFP_StatusWidget* StatusWidget = CreateWidget<UFP_StatusWidget>(PC, Widget);
		PC->WidgetMap.Add(AFP_PlayerController::STATUS, StatusWidget);
	}

	PC->GetWidgetMap(AFP_PlayerController::STATUS)->AddToViewport();
	
}


void UFP_MainUI::Button_Skill()
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AFP_PlayerController* PC = Cast<AFP_PlayerController>(Controller);
	UUserWidget* SkillWidget = PC->GetWidgetMap(AFP_PlayerController::SKILLUI);

	if (SkillWidget->IsValidLowLevel() == false)
	{
		FName Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_SkillUI.FP_SkillUI_C'");
		TSubclassOf<UFP_SkillUI> SkillUI = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
		UFP_SkillUI* SkillUIWidget = CreateWidget<UFP_SkillUI>(PC, SkillUI);
		PC->WidgetMap.Add(AFP_PlayerController::SKILLUI, SkillUIWidget);
	}


	PC->GetWidgetMap(AFP_PlayerController::SKILLUI)->AddToViewport();
	
}

void UFP_MainUI::Button_Rev()
{
	AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (nullptr == pPlayer)
		return;

	pPlayer->Status.Attack = 1.f;
	pPlayer->Status.AttackRange = 50.f;
	pPlayer->Status.AttackSpeed = 1.f;
	pPlayer->Status.BulletSpeed = 100.f;
	
		APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	Cast<AFP_PlayerController>(Controller)->RestartLevel();
	
}

void UFP_MainUI::Button_Rune()
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AFP_PlayerController* PC = Cast<AFP_PlayerController>(Controller);
	UUserWidget* RuneWidget = PC->GetWidgetMap(AFP_PlayerController::INVENTORY);

	if (RuneWidget->IsValidLowLevel() == false)
	{
		FName Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_Inventory_BP.FP_Inventory_BP_C'");
		TSubclassOf<UFP_InventoryWidget> Inventory = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
		UFP_InventoryWidget* InventoryWidget = CreateWidget<UFP_InventoryWidget>(PC, Inventory);
		InventoryWidget->ViewAllSortByTier();
		PC->WidgetMap.Add(AFP_PlayerController::INVENTORY, InventoryWidget);
	}



	PC->GetWidgetMap(AFP_PlayerController::INVENTORY)->AddToViewport();

}