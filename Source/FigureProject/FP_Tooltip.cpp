// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_Tooltip.h"
#include "FP_PlayerController.h"
#include "FP_Player.h"
#include "FP_Weapon.h"
#include "FP_MainUI.h"
#include "FP_InventoryWidget.h"
#include "FP_Skill.h"
#include "FP_FireBall.h"
#include "FP_SkillUI.h"
#include "VerticalBox.h"
#include "FP_ComMessageUI.h"

bool UFP_Tooltip::Initialize()
{
	Super::Initialize();

	UClass* Class = AFP_Skill::StaticClass();
	AFP_Skill* Skill_CDO = Class->GetDefaultObject<AFP_Skill>();

	UButton* Button = (UButton*)GetWidgetFromName(TEXT("ActiveButton"));
	//Button->OnClicked.AddDynamic(this, &UFP_Tooltip::ActiveSkill);

	Button = (UButton*)GetWidgetFromName(TEXT("Socket0"));
	Button->OnClicked.AddDynamic(this, &UFP_Tooltip::SocketButtonClick);
	Button->WidgetStyle.Normal.SetResourceObject(Skill_CDO->EmptySocketIcon);
	Button->WidgetStyle.Normal.ImageSize = FVector2D(20.f, 20.f);
	Button->WidgetStyle.Normal.Margin = 0;
	Button->WidgetStyle.Hovered.SetResourceObject(Skill_CDO->EmptySocketIcon);
	Button->WidgetStyle.Hovered.ImageSize = FVector2D(20.f, 20.f);
	Button->WidgetStyle.Hovered.Margin = 0;
	Button->WidgetStyle.Pressed.SetResourceObject(Skill_CDO->EmptySocketIcon);
	Button->WidgetStyle.Pressed.ImageSize = FVector2D(20.f, 20.f);
	Button->WidgetStyle.Pressed.Margin = 0;
	SocketButton.Add(Button);
	Button = (UButton*)GetWidgetFromName(TEXT("Socket1"));
	Button->OnClicked.AddDynamic(this, &UFP_Tooltip::SocketButtonClick);
	Button->WidgetStyle.Normal.SetResourceObject(Skill_CDO->EmptySocketIcon);
	Button->WidgetStyle.Normal.ImageSize = FVector2D(20.f, 20.f);
	Button->WidgetStyle.Normal.Margin = 0;
	Button->WidgetStyle.Hovered.SetResourceObject(Skill_CDO->EmptySocketIcon);
	Button->WidgetStyle.Hovered.ImageSize = FVector2D(20.f, 20.f);
	Button->WidgetStyle.Hovered.Margin = 0;
	Button->WidgetStyle.Pressed.SetResourceObject(Skill_CDO->EmptySocketIcon);
	Button->WidgetStyle.Pressed.ImageSize = FVector2D(20.f, 20.f);
	Button->WidgetStyle.Pressed.Margin = 0;
	SocketButton.Add(Button);
	Button = (UButton*)GetWidgetFromName(TEXT("Socket2"));
	Button->OnClicked.AddDynamic(this, &UFP_Tooltip::SocketButtonClick);
	Button->WidgetStyle.Normal.SetResourceObject(Skill_CDO->EmptySocketIcon);
	Button->WidgetStyle.Normal.ImageSize = FVector2D(20.f, 20.f);
	Button->WidgetStyle.Normal.Margin = 0;
	Button->WidgetStyle.Hovered.SetResourceObject(Skill_CDO->EmptySocketIcon);
	Button->WidgetStyle.Hovered.ImageSize = FVector2D(20.f, 20.f);
	Button->WidgetStyle.Hovered.Margin = 0;
	Button->WidgetStyle.Pressed.SetResourceObject(Skill_CDO->EmptySocketIcon);
	Button->WidgetStyle.Pressed.ImageSize = FVector2D(20.f, 20.f);
	Button->WidgetStyle.Pressed.Margin = 0;
	SocketButton.Add(Button);
	Button = (UButton*)GetWidgetFromName(TEXT("Socket3"));
	Button->OnClicked.AddDynamic(this, &UFP_Tooltip::SocketButtonClick);
	Button->WidgetStyle.Normal.SetResourceObject(Skill_CDO->EmptySocketIcon);
	Button->WidgetStyle.Normal.ImageSize = FVector2D(20.f, 20.f);
	Button->WidgetStyle.Normal.Margin = 0;
	Button->WidgetStyle.Hovered.SetResourceObject(Skill_CDO->EmptySocketIcon);
	Button->WidgetStyle.Hovered.ImageSize = FVector2D(20.f, 20.f);
	Button->WidgetStyle.Hovered.Margin = 0;
	Button->WidgetStyle.Pressed.SetResourceObject(Skill_CDO->EmptySocketIcon);
	Button->WidgetStyle.Pressed.ImageSize = FVector2D(20.f, 20.f);
	Button->WidgetStyle.Pressed.Margin = 0;
	SocketButton.Add(Button);

	Button = (UButton*)GetWidgetFromName(TEXT("Create"));
	Button->OnClicked.AddDynamic(this, &UFP_Tooltip::CreateSocket);
	Button = (UButton*)GetWidgetFromName(TEXT("ChangeColor"));
	Button->OnClicked.AddDynamic(this, &UFP_Tooltip::ChangeColor);
	Button = (UButton*)GetWidgetFromName(TEXT("Equip"));
	Button->OnClicked.AddDynamic(this, &UFP_Tooltip::EquipRune);
	Button = (UButton*)GetWidgetFromName(TEXT("Unequip"));
	Button->OnClicked.AddDynamic(this, &UFP_Tooltip::UnequipRune);


	SocketBox = (UVerticalBox*)GetWidgetFromName(TEXT("SocketButtonBox"));

	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PC = Cast<AFP_PlayerController>(Controller);



	PC->InputComponent->BindAction("TooltipUp", IE_Released, this, &UFP_Tooltip::PositionUp);

	
	
	return true;
}


void UFP_Tooltip::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);


	if(ingDebug == true)
		this->SetRenderTranslation(FVector2D(this->RenderTransform.Translation.X, -400));

	

	if (Cast<UFP_SkillUI>(PC->GetWidgetMap(AFP_PlayerController::SKILLUI))->IsInViewport() == false)
	{
		RemoveFromViewport();
		Cast<UFP_SkillUI>(PC->GetWidgetMap(AFP_PlayerController::SKILLUI))->isSkillClicked = false;
		SocketBox->SetVisibility(ESlateVisibility::Hidden);
	}


	if (CurrentSkill->Sockets.Num() == 0)
	{
		for (size_t i = 0; i < SocketButton.Num(); ++i)
		{
			SocketButton[i]->WidgetStyle.Normal.SetResourceObject(CurrentSkill->EmptySocketIcon);
			SocketButton[i]->WidgetStyle.Hovered.SetResourceObject(CurrentSkill->EmptySocketIcon);
			SocketButton[i]->WidgetStyle.Pressed.SetResourceObject(CurrentSkill->EmptySocketIcon);
		}
	}
	else
	{
		for (size_t i = 0; i < CurrentSkill->Sockets.Num(); ++i)
		{
			if (CurrentSkill->Sockets[i].Rune == nullptr || SocketButton[i]->WidgetStyle.Normal.GetResourceObject() == CurrentSkill->EmptySocketIcon)
			{
				UTexture2D* SocketIcon = nullptr;
				if (CurrentSkill->Sockets[i].Color == FColor::Red)
					SocketIcon = CurrentSkill->RedSocketIcon;
				else if (CurrentSkill->Sockets[i].Color == FColor::Green)
					SocketIcon = CurrentSkill->GreenSocketIcon;
				else
					SocketIcon = CurrentSkill->BlueSocketIcon;

				SocketButton[i]->WidgetStyle.Normal.SetResourceObject(SocketIcon);
				SocketButton[i]->WidgetStyle.Hovered.SetResourceObject(SocketIcon);
				SocketButton[i]->WidgetStyle.Pressed.SetResourceObject(SocketIcon);
			}
			else if (CurrentSkill->Sockets[i].Rune != nullptr && CurrentSkill->Sockets[i].Rune->IsValidLowLevel() == true)
			{
				UFP_Tooltip* SkillToolTip = Cast<UFP_Tooltip>(PC->GetWidgetMap(AFP_PlayerController::SKILLTOOLTIP));

				SkillToolTip->SocketButton[i]->WidgetStyle.Normal.SetResourceObject(CurrentSkill->Sockets[i].Rune->Icon);
				SkillToolTip->SocketButton[i]->WidgetStyle.Normal.ImageSize = FVector2D(20.f, 20.f);
				SkillToolTip->SocketButton[i]->WidgetStyle.Normal.Margin = 0;
				SkillToolTip->SocketButton[i]->WidgetStyle.Hovered.SetResourceObject(CurrentSkill->Sockets[i].Rune->Icon);
				SkillToolTip->SocketButton[i]->WidgetStyle.Hovered.ImageSize = FVector2D(20.f, 20.f);
				SkillToolTip->SocketButton[i]->WidgetStyle.Hovered.Margin = 0;
				SkillToolTip->SocketButton[i]->WidgetStyle.Pressed.SetResourceObject(CurrentSkill->Sockets[i].Rune->Icon);
				SkillToolTip->SocketButton[i]->WidgetStyle.Pressed.ImageSize = FVector2D(20.f, 20.f);
				SkillToolTip->SocketButton[i]->WidgetStyle.Pressed.Margin = 0;
			}
		}
	}

}

void UFP_Tooltip::ActiveSkill()
{
	AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (nullptr == pPlayer)
		return;

	if (SkillName.ToString() == "FireBall")
	{
		if (pPlayer->SkillLv.FireBall == 0)
			return;

		AFP_Weapon::ActiveSkill = AFP_Weapon::FIREBALL;
	}
	else if (SkillName.ToString() == "FireBlast")
	{
		if (pPlayer->SkillLv.FireBlast == 0)
			return;

		AFP_Weapon::ActiveSkill = AFP_Weapon::FIREBLAST;

	}
	else if (SkillName.ToString() == "FireWall")
	{
		if (pPlayer->SkillLv.FireWall == 0)
			return;

		AFP_Weapon::ActiveSkill = AFP_Weapon::FIREWALL;
	}
	else if (SkillName.ToString() == "IceBall")
	{
		if (pPlayer->SkillLv.IceBall == 0)
			return;

		AFP_Weapon::ActiveSkill = AFP_Weapon::ICEBALL;
	}
	else if (SkillName.ToString() == "IceBlast")
	{
		if (pPlayer->SkillLv.IceBlast == 0)
			return;

		AFP_Weapon::ActiveSkill = AFP_Weapon::ICEBLAST;
	}
	else if (SkillName.ToString() == "IceOrb")
	{
		if (pPlayer->SkillLv.IceOrb == 0)
			return;


		AFP_Weapon::ActiveSkill = AFP_Weapon::ICEORB;

	}
}

void UFP_Tooltip::SocketButtonClick()
{
	for (size_t i = 0; i < SocketButton.Num(); ++i)
	{
		if (SocketButton[i]->IsPressed() == true)
		{
			//UE_LOG(LogClass, Log, TEXT("%f"), float(i));
			iSocketIndex = i;
			FString target = TEXT("TargetSocket : ") + FString::FromInt(iSocketIndex+1);
			TargetSocket = FText::FromString(target);
			break;
		}
	}

	SocketBox->SetVisibility(ESlateVisibility::Visible);
}

void UFP_Tooltip::CreateSocket()
{
	AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (nullptr == pPlayer)
		return;

	
	int RequiredGem = FMath::Pow(2, iSocketIndex);
	if (pPlayer->Gem >= RequiredGem && CurrentSkill->Sockets.IsValidIndex(iSocketIndex) == false)
	{
		FColor color = CurrentSkill->AddSocket();
		pPlayer->Gem -= RequiredGem;
		//SocketButton[iSocketIndex]->SetBackgroundColor(color);
	}
	else if (pPlayer->Gem < RequiredGem)
		AFP_ComMessageUI::ShowMessage(PC, FText::FromString(TEXT("No Gems")), 2.f, FColor::Red);


	SocketBox->SetVisibility(ESlateVisibility::Hidden);
}
void UFP_Tooltip::ChangeColor()
{
	if (CurrentSkill->Sockets.Num() < iSocketIndex + 1)
		return;

	if (CurrentSkill->Sockets[iSocketIndex].Rune->IsValidLowLevel())
		return;

	AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (nullptr == pPlayer)
		return;

	if (pPlayer->Gem == 0)
	{
		AFP_ComMessageUI::ShowMessage(PC, FText::FromString(TEXT("No Gems")), 2.f, FColor::Red);
		return;
	}
	else
		pPlayer->Gem--;


	int icolor = FMath::FRandRange(1, 4);
	FColor color;
	switch (icolor)
	{
	case 1:
		color = FColor::Red;
		break;
	case 2:
		color = FColor::Green;
		break;
	case 3:
		color = FColor::Blue;
		break;
	}

	UTexture2D* SocketIcon = nullptr;
	if (color == FColor::Red)
		SocketIcon = CurrentSkill->RedSocketIcon;
	else if (color == FColor::Green)
		SocketIcon = CurrentSkill->GreenSocketIcon;
	else
		SocketIcon = CurrentSkill->BlueSocketIcon;

	SocketButton[iSocketIndex]->WidgetStyle.Normal.SetResourceObject(SocketIcon);
	SocketButton[iSocketIndex]->WidgetStyle.Hovered.SetResourceObject(SocketIcon);
	SocketButton[iSocketIndex]->WidgetStyle.Pressed.SetResourceObject(SocketIcon);

	CurrentSkill->Sockets[iSocketIndex].Color = color;
	SocketBox->SetVisibility(ESlateVisibility::Hidden);
}
void UFP_Tooltip::EquipRune()
{
	if (CurrentSkill->Sockets.Num() < iSocketIndex + 1)
		return;

	UFP_InventoryWidget* Inventory = Cast<UFP_InventoryWidget>(PC->GetWidgetMap(AFP_PlayerController::INVENTORY));
	
	//open inventory
	if (Inventory->IsInViewport() == false)
	{
		Inventory->bFromMain = false;
		
		FColor color = CurrentSkill->Sockets[iSocketIndex].Color;

		if (color == FColor::Red)
		{
			//Inventory->Order = UFP_InventoryWidget::SORTORDER::RED;
			Cast<UFP_MainUI>(PC->GetWidgetMap(AFP_PlayerController::MAINUI))->OpenInventoryFromSkill(UFP_InventoryWidget::SORTORDER::RED);
		}
		else if (color == FColor::Green)
		{
			//Inventory->Order = UFP_InventoryWidget::SORTORDER::GREEN;
			Cast<UFP_MainUI>(PC->GetWidgetMap(AFP_PlayerController::MAINUI))->OpenInventoryFromSkill(UFP_InventoryWidget::SORTORDER::GREEN);
		}
		else
		{
			//Inventory->Order = UFP_InventoryWidget::SORTORDER::BLUE;
			Cast<UFP_MainUI>(PC->GetWidgetMap(AFP_PlayerController::MAINUI))->OpenInventoryFromSkill(UFP_InventoryWidget::SORTORDER::BLUE);
		}

		Inventory->SelectedSkill = CurrentSkill;
	}
		
	SocketBox->SetVisibility(ESlateVisibility::Hidden);


	this->RemoveFromViewport();
	PC->GetWidgetMap(AFP_PlayerController::SKILLUI)->RemoveFromViewport();

}

void UFP_Tooltip::UnequipRune()
{
	if (CurrentSkill->Sockets.Num() < iSocketIndex + 1)
		return;

	if (CurrentSkill->Sockets[iSocketIndex].Rune == nullptr || CurrentSkill->Sockets[iSocketIndex].Rune->IsValidLowLevel() == false)
		return;

	CurrentSkill->Sockets[iSocketIndex].Rune->bEquiped = false;
	CurrentSkill->Sockets[iSocketIndex].Rune = nullptr;

	UUserWidget* InventoryWidget = PC->GetWidgetMap(AFP_PlayerController::INVENTORY);
	Cast<UFP_InventoryWidget>(InventoryWidget)->SortInventory();
	
	CurrentSkill->RuneChanged = true;

}

void UFP_Tooltip::PositionUp()
{
	ingDebug = true;
}