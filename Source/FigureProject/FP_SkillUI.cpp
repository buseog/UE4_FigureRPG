// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_SkillUI.h"
#include "Button.h"
#include "Engine.h"
#include "FP_PlayerController.h"
#include "FP_Player.h"
#include "FP_MainUI.h"
#include "CircularThrobber.h"
#include "FP_Weapon.h"


bool UFP_SkillUI::Initialize()
{
	Super::Initialize();

	UButton* Button = (UButton*)GetWidgetFromName(TEXT("FireBall"));
	Button->OnClicked.AddDynamic(this, &UFP_SkillUI::ActiveFireBall);

	Button = (UButton*)GetWidgetFromName(TEXT("FireBlast"));
	Button->OnClicked.AddDynamic(this, &UFP_SkillUI::ActiveFireBlast);

	Button = (UButton*)GetWidgetFromName(TEXT("FireWall"));
	Button->OnClicked.AddDynamic(this, &UFP_SkillUI::ActiveFireWall);

	Button = (UButton*)GetWidgetFromName(TEXT("IceBall"));
	Button->OnClicked.AddDynamic(this, &UFP_SkillUI::ActiveIceBall);

	Button = (UButton*)GetWidgetFromName(TEXT("IceBlast"));
	Button->OnClicked.AddDynamic(this, &UFP_SkillUI::ActiveIceBlast);

	Button = (UButton*)GetWidgetFromName(TEXT("IceOrb"));
	Button->OnClicked.AddDynamic(this, &UFP_SkillUI::ActiveIceOrb);

	Throbber = (UCircularThrobber*)GetWidgetFromName(TEXT("Active"));


	Button = (UButton*)GetWidgetFromName(TEXT("Button_FireBall"));
	Button->OnClicked.AddDynamic(this, &UFP_SkillUI::LvUpFireBall);

	Button = (UButton*)GetWidgetFromName(TEXT("Button_FireBlast"));
	Button->OnClicked.AddDynamic(this, &UFP_SkillUI::LvUpFireBlast);

	Button = (UButton*)GetWidgetFromName(TEXT("Button_FireWall"));
	Button->OnClicked.AddDynamic(this, &UFP_SkillUI::LvUpFireWall);

	Button = (UButton*)GetWidgetFromName(TEXT("Button_IceBall"));
	Button->OnClicked.AddDynamic(this, &UFP_SkillUI::LvUpIceBall);

	Button = (UButton*)GetWidgetFromName(TEXT("Button_IceBlast"));
	Button->OnClicked.AddDynamic(this, &UFP_SkillUI::LvUpIceBlast);

	Button = (UButton*)GetWidgetFromName(TEXT("Button_IceOrb"));
	Button->OnClicked.AddDynamic(this, &UFP_SkillUI::LvUpIceOrb);





	return true;
}

void UFP_SkillUI::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AFP_PlayerController* PC = Cast<AFP_PlayerController>(Controller);

	if (PC->bShowMainUI == false)
	{
		RemoveFromViewport();
		Cast<UFP_MainUI>(PC->GetWidgetMap(AFP_PlayerController::MAINUI))->isSkillClicked = false;
	}


}

void UFP_SkillUI::ActiveFireBall()
{
	AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (nullptr == pPlayer)
		return;
	if (pPlayer->SkillLv.FireBall == 0)
		return;


	Throbber->SetRenderTranslation(FVector2D(0.f, (int)AFP_Weapon::FIREBALL * (SizeY / SkillCnt)));

	TArray<AActor*> FoundActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFP_Weapon::StaticClass(), FoundActor);
	if (FoundActor[0] == nullptr)
		return;

	Cast<AFP_Weapon>(FoundActor[0])->SetActiveSkill(AFP_Weapon::FIREBALL);
}
void UFP_SkillUI::ActiveFireBlast()
{
	AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (nullptr == pPlayer)
		return;
	if (pPlayer->SkillLv.FireBlast == 0)
		return;


	Throbber->SetRenderTranslation(FVector2D(0.f, (int)AFP_Weapon::FIREBLAST * (SizeY / SkillCnt)));

	TArray<AActor*> FoundActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFP_Weapon::StaticClass(), FoundActor);
	if (FoundActor[0] == nullptr)
		return;

	
	Cast<AFP_Weapon>(FoundActor[0])->SetActiveSkill(AFP_Weapon::FIREBLAST);
}
void UFP_SkillUI::ActiveFireWall()
{
	AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (nullptr == pPlayer)
		return;
	if (pPlayer->SkillLv.FireWall == 0)
		return;

	Throbber->SetRenderTranslation(FVector2D(0.f, (int)AFP_Weapon::FIREWALL * (SizeY / SkillCnt)));
	
	TArray<AActor*> FoundActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFP_Weapon::StaticClass(), FoundActor);
	if (FoundActor[0] == nullptr)
		return;

	
	Cast<AFP_Weapon>(FoundActor[0])->SetActiveSkill(AFP_Weapon::FIREWALL);
}

void UFP_SkillUI::ActiveIceBall()
{
	AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (nullptr == pPlayer)
		return;
	if (pPlayer->SkillLv.IceBall == 0)
		return;

	Throbber->SetRenderTranslation(FVector2D(0.f, (int)AFP_Weapon::ICEBALL * (SizeY / SkillCnt)));

	TArray<AActor*> FoundActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFP_Weapon::StaticClass(), FoundActor);
	if (FoundActor[0] == nullptr)
		return;

	
	Cast<AFP_Weapon>(FoundActor[0])->SetActiveSkill(AFP_Weapon::ICEBALL);
}
void UFP_SkillUI::ActiveIceBlast()
{
	AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (nullptr == pPlayer)
		return;
	if (pPlayer->SkillLv.IceBlast == 0)
		return;

	Throbber->SetRenderTranslation(FVector2D(0.f, (int)AFP_Weapon::ICEBLAST * (SizeY / SkillCnt)));

	TArray<AActor*> FoundActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFP_Weapon::StaticClass(), FoundActor);
	if (FoundActor[0] == nullptr)
		return;

	
	Cast<AFP_Weapon>(FoundActor[0])->SetActiveSkill(AFP_Weapon::ICEBLAST);
}
void UFP_SkillUI::ActiveIceOrb()
{
	AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (nullptr == pPlayer)
		return;
	if (pPlayer->SkillLv.IceOrb == 0)
		return;

	Throbber->SetRenderTranslation(FVector2D(0.f, (int)AFP_Weapon::ICEORB * (SizeY / SkillCnt)));

	TArray<AActor*> FoundActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFP_Weapon::StaticClass(), FoundActor);
	if (FoundActor[0] == nullptr)
		return;

	
	Cast<AFP_Weapon>(FoundActor[0])->SetActiveSkill(AFP_Weapon::ICEORB);
}

void UFP_SkillUI::LvUpFireBall()
{
	AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (nullptr == pPlayer)
		return;

	if (pPlayer->SkillLv.SkillPoint <= 0)
		return;

	pPlayer->SkillLv.FireBall += 1;
	pPlayer->SkillLv.SkillPoint -= 1;
}
void UFP_SkillUI::LvUpFireBlast()
{
	AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (nullptr == pPlayer)
		return;

	if (pPlayer->SkillLv.SkillPoint <= 0)
		return;

	pPlayer->SkillLv.FireBlast += 1;
	pPlayer->SkillLv.SkillPoint -= 1;
}
void UFP_SkillUI::LvUpFireWall()
{
	AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (nullptr == pPlayer)
		return;

	if (pPlayer->SkillLv.SkillPoint <= 0)
		return;

	pPlayer->SkillLv.FireWall += 1;
	pPlayer->SkillLv.SkillPoint -= 1;
}

void UFP_SkillUI::LvUpIceBall()
{
	AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (nullptr == pPlayer)
		return;

	if (pPlayer->SkillLv.SkillPoint <= 0)
		return;

	pPlayer->SkillLv.IceBall += 1;
	pPlayer->SkillLv.SkillPoint -= 1;
}
void UFP_SkillUI::LvUpIceBlast()
{
	AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (nullptr == pPlayer)
		return;

	if (pPlayer->SkillLv.SkillPoint <= 0)
		return;

	pPlayer->SkillLv.IceBlast += 1;
	pPlayer->SkillLv.SkillPoint -= 1;
}
void UFP_SkillUI::LvUpIceOrb()
{
	AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (nullptr == pPlayer)
		return;

	if (pPlayer->SkillLv.SkillPoint <= 0)
		return;

	pPlayer->SkillLv.IceOrb += 1;
	pPlayer->SkillLv.SkillPoint -= 1;
}