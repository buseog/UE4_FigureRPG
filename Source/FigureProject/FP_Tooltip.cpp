// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_Tooltip.h"
#include "FP_PlayerController.h"
#include "FP_Player.h"
#include "FP_Weapon.h"
#include "FP_MainUI.h"
#include "FP_InventoryWidget.h"




bool UFP_Tooltip::Initialize()
{
	Super::Initialize();

	UButton* Button = (UButton*)GetWidgetFromName(TEXT("ActiveButton"));
	Button->OnClicked.AddDynamic(this, &UFP_Tooltip::ActiveSkill);

	Button = (UButton*)GetWidgetFromName(TEXT("Socket0"));
	Button->OnClicked.AddDynamic(this, &UFP_Tooltip::SocketButtonClick);
	SocketButton.Add(Button);
	Button = (UButton*)GetWidgetFromName(TEXT("Socket1"));
	Button->OnClicked.AddDynamic(this, &UFP_Tooltip::SocketButtonClick);
	SocketButton.Add(Button);
	Button = (UButton*)GetWidgetFromName(TEXT("Socket2"));
	Button->OnClicked.AddDynamic(this, &UFP_Tooltip::SocketButtonClick);
	SocketButton.Add(Button);
	Button = (UButton*)GetWidgetFromName(TEXT("Socket3"));
	Button->OnClicked.AddDynamic(this, &UFP_Tooltip::SocketButtonClick);
	SocketButton.Add(Button);

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
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AFP_PlayerController* PC = Cast<AFP_PlayerController>(Controller);

	for (size_t i = 0; i < SocketButton.Num(); ++i)
	{
		if (SocketButton[i]->IsPressed() == true)
		{
			//open inventory
			if(Cast<UFP_InventoryWidget>(PC->GetWidgetMap(AFP_PlayerController::INVENTORY))->IsInViewport()==false)
				Cast<UFP_MainUI>(PC->GetWidgetMap(AFP_PlayerController::MAINUI))->Button_Rune();
			
			UE_LOG(LogClass, Log, TEXT("%f"), float(i));
		}
	}
}