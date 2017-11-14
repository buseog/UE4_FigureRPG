// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_HUD.h"
#include "FP_Inventory.h"
#include "Engine/Canvas.h"
#include "FP_PlayerController.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Engine.h"
#include "FP_Item_PowerUp.h"
#include "FP_Item_AttackSpeedUp.h"
#include "FP_Player.h"
#include "FP_InventoryWidget.h"


AFP_HUD::AFP_HUD()
{
	ConstructorHelpers::FObjectFinder<UFont> FontObject(TEXT("Font'/Game/NanumPen_Font.NanumPen_Font'"));
	
	HudFont = FontObject.Object;
}

void AFP_HUD::BeginPlay()
{
	Inventory = GetWorld()->SpawnActor<AFP_Inventory>();
	PController = GetWorld()->GetFirstPlayerController();

	PController->InputComponent->BindAction("ToggleInventory", IE_Released, this, &AFP_HUD::OpenInventory);
	PController->InputComponent->BindAction("AddItem", IE_Released, this, &AFP_HUD::PickupItem);
	PController->InputComponent->BindAction("LeftClick", IE_Released, this, &AFP_HUD::Clicked);

	KillCount = 0;
	PreKillCount = 0;
	Stage = 1;
}

void AFP_HUD::DrawHUD()
{
	Super::DrawHUD();

	CanvasSizeX = Canvas->SizeX;

	DrawWidgets();
	//DrawKillCount();
	//DrawStage();
}

void AFP_HUD::OpenInventory()
{
	//Inventory->ToggleInventory(CanvasSizeX);

	AFP_Player* player = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	AFP_PlayerController* PC = Cast<AFP_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	player->Inventory.Empty();

}

void AFP_HUD::PickupItem()
{
	Item = GetWorld()->SpawnActor<AFP_Item>();
	Inventory->AddItem(Item);
}

void AFP_HUD::DrawWidgets()
{
	TArray<Widget> Widgets = Inventory->GetWidgets();
	
	for (int i = 0; i < Widgets.Num(); ++i)
	{
		DrawTexture((UTexture*)(Widgets[i].ItemIcon.Texture), Widgets[i].Pos.X, Widgets[i].Pos.Y, Widgets[i].Pos.X, Widgets[i].Pos.Y, 0, 0, 1, 1, FLinearColor::White, BLEND_Translucent, 0.5f);
		DrawText(Widgets[i].ItemIcon.Name, FLinearColor::Black, Widgets[i].Pos.X, Widgets[i].Pos.Y, HudFont, 2.f, false);
	}
}

void AFP_HUD::Clicked()
{
	TArray<Widget> Widgets = Inventory->GetWidgets();

	FVector2D MousePosition;

	PController->GetMousePosition(MousePosition.X, MousePosition.Y);

	for (int i = 0; i < Widgets.Num(); ++i)
	{
		if (Widgets[i].Clicked(MousePosition))
		{
			UE_LOG(LogClass, Log, TEXT("Clicked"));
		}
	}
}

void AFP_HUD::IncreaseKillCount()
{
	++KillCount;
}

void AFP_HUD::DrawKillCount()
{
	FString Count = FString::FromInt(KillCount) + FString(" Kill");
	DrawText(Count, FLinearColor::Red, 10.f, 10.f, HudFont, 2.f, false);
}

void AFP_HUD::DrawStage()
{
	if (KillCount % 10 == 0 && KillCount != 0 && PreKillCount != KillCount)
	{
		++Stage;
	}

	PreKillCount = KillCount;

	const FVector2D ViewportSize = GEngine->GameViewport->Viewport->GetSizeXY();
	
	FString Count = FString::FromInt(Stage) + FString(" Stage");
	DrawText(Count, FLinearColor::Red, ViewportSize.X / 2.f, 10.f, HudFont, 2.f, false);
}

int AFP_HUD::GetStage()
{
	return Stage;
}