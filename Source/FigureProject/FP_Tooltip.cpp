// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_Tooltip.h"
#include "FP_PlayerController.h"
#include "FP_Player.h"
#include "FP_Weapon.h"
#include "FP_MainUI.h"
#include "FP_InventoryWidget.h"
#include "FP_Skill.h"
#include "FP_FireBall.h"
#include "VerticalBox.h"

bool UFP_Tooltip::Initialize()
{
	Super::Initialize();

	UButton* Button = (UButton*)GetWidgetFromName(TEXT("ActiveButton"));
	Button->OnClicked.AddDynamic(this, &UFP_Tooltip::ActiveSkill);

	Button = (UButton*)GetWidgetFromName(TEXT("Socket0"));
	Button->OnClicked.AddDynamic(this, &UFP_Tooltip::SocketButtonClick);
	Button->SetBackgroundColor(FColor::Black);
	SocketButton.Add(Button);
	Button = (UButton*)GetWidgetFromName(TEXT("Socket1"));
	Button->OnClicked.AddDynamic(this, &UFP_Tooltip::SocketButtonClick);
	Button->SetBackgroundColor(FColor::Black);
	SocketButton.Add(Button);
	Button = (UButton*)GetWidgetFromName(TEXT("Socket2"));
	Button->OnClicked.AddDynamic(this, &UFP_Tooltip::SocketButtonClick);
	Button->SetBackgroundColor(FColor::Black);
	SocketButton.Add(Button);
	Button = (UButton*)GetWidgetFromName(TEXT("Socket3"));
	Button->OnClicked.AddDynamic(this, &UFP_Tooltip::SocketButtonClick);
	Button->SetBackgroundColor(FColor::Black);
	SocketButton.Add(Button);

	Button = (UButton*)GetWidgetFromName(TEXT("Create"));
	Button->OnClicked.AddDynamic(this, &UFP_Tooltip::CreateSocket);
	Button = (UButton*)GetWidgetFromName(TEXT("ChangeColor"));
	Button->OnClicked.AddDynamic(this, &UFP_Tooltip::ChangeColor);
	Button = (UButton*)GetWidgetFromName(TEXT("Equip"));
	Button->OnClicked.AddDynamic(this, &UFP_Tooltip::EquipRune);


	SocketBox = (UVerticalBox*)GetWidgetFromName(TEXT("SocketButtonBox"));
	
	return true;
}


void UFP_Tooltip::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AFP_PlayerController* PC = Cast<AFP_PlayerController>(Controller);

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
			SocketButton[i]->SetBackgroundColor(FColor::Black);
		}
	}
	else
	{
		for (size_t i = 0; i < CurrentSkill->Sockets.Num(); ++i)
		{
			SocketButton[i]->SetBackgroundColor(CurrentSkill->Sockets[i].Color);
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


		SkillUI->Throbber->SetRenderTranslation(FVector2D(0.f, (int)AFP_Weapon::FIREBALL * (SkillUI->SizeY / SkillUI->SkillCnt)));

		TArray<AActor*> FoundActor;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFP_Weapon::StaticClass(), FoundActor);
		if (FoundActor[0] == nullptr)
			return;

		Cast<AFP_Weapon>(FoundActor[0])->SetActiveSkill(AFP_Weapon::FIREBALL);
	}
	else if (SkillName.ToString() == "FireBlast")
	{
		if (pPlayer->SkillLv.FireBlast == 0)
			return;


		SkillUI->Throbber->SetRenderTranslation(FVector2D(0.f, (int)AFP_Weapon::FIREBLAST * (SkillUI->SizeY / SkillUI->SkillCnt)));

		TArray<AActor*> FoundActor;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFP_Weapon::StaticClass(), FoundActor);
		if (FoundActor[0] == nullptr)
			return;

		Cast<AFP_Weapon>(FoundActor[0])->SetActiveSkill(AFP_Weapon::FIREBLAST);

	}
	else if (SkillName.ToString() == "FireWall")
	{
		if (pPlayer->SkillLv.FireWall == 0)
			return;


		SkillUI->Throbber->SetRenderTranslation(FVector2D(0.f, (int)AFP_Weapon::FIREWALL * (SkillUI->SizeY / SkillUI->SkillCnt)));

		TArray<AActor*> FoundActor;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFP_Weapon::StaticClass(), FoundActor);
		if (FoundActor[0] == nullptr)
			return;

		Cast<AFP_Weapon>(FoundActor[0])->SetActiveSkill(AFP_Weapon::FIREWALL);
	}
	else if (SkillName.ToString() == "IceBall")
	{
		if (pPlayer->SkillLv.IceBall == 0)
			return;


		SkillUI->Throbber->SetRenderTranslation(FVector2D(0.f, (int)AFP_Weapon::ICEBALL * (SkillUI->SizeY / SkillUI->SkillCnt)));

		TArray<AActor*> FoundActor;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFP_Weapon::StaticClass(), FoundActor);
		if (FoundActor[0] == nullptr)
			return;

		Cast<AFP_Weapon>(FoundActor[0])->SetActiveSkill(AFP_Weapon::ICEBALL);
	}
	else if (SkillName.ToString() == "IceBlast")
	{
		if (pPlayer->SkillLv.IceBlast == 0)
			return;


		SkillUI->Throbber->SetRenderTranslation(FVector2D(0.f, (int)AFP_Weapon::ICEBLAST * (SkillUI->SizeY / SkillUI->SkillCnt)));

		TArray<AActor*> FoundActor;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFP_Weapon::StaticClass(), FoundActor);
		if (FoundActor[0] == nullptr)
			return;

		Cast<AFP_Weapon>(FoundActor[0])->SetActiveSkill(AFP_Weapon::ICEBLAST);
	}
	else if (SkillName.ToString() == "IceOrb")
	{
		if (pPlayer->SkillLv.IceOrb == 0)
			return;


		SkillUI->Throbber->SetRenderTranslation(FVector2D(0.f, (int)AFP_Weapon::ICEORB * (SkillUI->SizeY / SkillUI->SkillCnt)));

		TArray<AActor*> FoundActor;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFP_Weapon::StaticClass(), FoundActor);
		if (FoundActor[0] == nullptr)
			return;

		Cast<AFP_Weapon>(FoundActor[0])->SetActiveSkill(AFP_Weapon::ICEORB);

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
	if (pPlayer->Gem >= RequiredGem)
	{
		FColor color = CurrentSkill->AddSocket();
		pPlayer->Gem -= RequiredGem;
		//SocketButton[iSocketIndex]->SetBackgroundColor(color);
	}

	SocketBox->SetVisibility(ESlateVisibility::Hidden);
}
void UFP_Tooltip::ChangeColor()
{
	if (CurrentSkill->Sockets.Num() < iSocketIndex + 1)
		return;

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

	SocketButton[iSocketIndex]->SetBackgroundColor(color);
	CurrentSkill->Sockets[iSocketIndex].Color = color;


	SocketBox->SetVisibility(ESlateVisibility::Hidden);
}
void UFP_Tooltip::EquipRune()
{
	if (CurrentSkill->Sockets.Num() < iSocketIndex + 1)
		return;

	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AFP_PlayerController* PC = Cast<AFP_PlayerController>(Controller);

	UFP_InventoryWidget* Inventory = Cast<UFP_InventoryWidget>(PC->GetWidgetMap(AFP_PlayerController::INVENTORY));

	//open inventory
	if (Inventory->IsInViewport() == false)
	{
		Inventory->bFromMain = false;
		
		FColor color = CurrentSkill->Sockets[iSocketIndex].Color;

		if (color == FColor::Red)
			Inventory->Order = UFP_InventoryWidget::SORTORDER::RED;
		else if (color == FColor::Green)
			Inventory->Order = UFP_InventoryWidget::SORTORDER::GREEN;
		else
			Inventory->Order = UFP_InventoryWidget::SORTORDER::BLUE;

		Inventory->SelectedSkill = CurrentSkill;

		Cast<UFP_MainUI>(PC->GetWidgetMap(AFP_PlayerController::MAINUI))->OpenInventoryFromSkill();
	}
		

	SocketBox->SetVisibility(ESlateVisibility::Hidden);
}