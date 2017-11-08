// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_SkillUI.h"
#include "Button.h"
#include "Engine.h"
#include "FP_PlayerController.h"
#include "FP_Player.h"
#include "FP_MainUI.h"
#include "CircularThrobber.h"
#include "FP_Weapon.h"
#include "FP_Tooltip.h"
#include "FP_FireBall.h"
#include "FP_FireBlast.h"
#include "FP_FireWall.h"
#include "FP_IceBall.h"
#include "FP_IceBlast.h"
#include "FP_IceOrb.h"

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



}


void UFP_SkillUI::ActiveFireBall()
{
	AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (nullptr == pPlayer)
		return;

	FName Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_ToolTip_BP.FP_ToolTip_BP_C'");
	PrepareTooltip<AFP_FireBall>(AFP_PlayerController::SKILLTOOLTIP, Path, FText::FromString(TEXT("FireBall")), pPlayer->SkillLv.FireBall);
	
}
void UFP_SkillUI::ActiveFireBlast()
{
	AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (nullptr == pPlayer)
		return;

	FName Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_ToolTip_BP.FP_ToolTip_BP_C'");
	PrepareTooltip<AFP_FireBlast>(AFP_PlayerController::SKILLTOOLTIP, Path, FText::FromString(TEXT("FireBlast")), pPlayer->SkillLv.FireBlast);

}
void UFP_SkillUI::ActiveFireWall()
{
	AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (nullptr == pPlayer)
		return;

	FName Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_ToolTip_BP.FP_ToolTip_BP_C'");
	PrepareTooltip<AFP_FireWall>(AFP_PlayerController::SKILLTOOLTIP, Path, FText::FromString(TEXT("FireWall")), pPlayer->SkillLv.FireWall);

}

void UFP_SkillUI::ActiveIceBall()
{
	AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (nullptr == pPlayer)
		return;

	FName Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_ToolTip_BP.FP_ToolTip_BP_C'");
	PrepareTooltip<AFP_IceBall>(AFP_PlayerController::SKILLTOOLTIP, Path, FText::FromString(TEXT("IceBall")), pPlayer->SkillLv.IceBall);

}
void UFP_SkillUI::ActiveIceBlast()
{
	AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (nullptr == pPlayer)
		return;

	FName Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_ToolTip_BP.FP_ToolTip_BP_C'");
	PrepareTooltip<AFP_IceBlast>(AFP_PlayerController::SKILLTOOLTIP, Path, FText::FromString(TEXT("IceBlast")), pPlayer->SkillLv.IceBlast);

}
void UFP_SkillUI::ActiveIceOrb()
{
	AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (nullptr == pPlayer)
		return;

	FName Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_ToolTip_BP.FP_ToolTip_BP_C'");
	PrepareTooltip<AFP_IceOrb>(AFP_PlayerController::SKILLTOOLTIP, Path, FText::FromString(TEXT("IceOrb")), pPlayer->SkillLv.IceOrb);

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

	UClass* Class = AFP_FireBall::StaticClass();
	AFP_FireBall* Skill = Class->GetDefaultObject<AFP_FireBall>();
	Skill->Stat.Damage += Skill->SkillInfo.DmgPerLv*0.01f;
	Skill->Stat.CoolTimeRatio -= Skill->SkillInfo.AtkSpdPerLv;
	UpdateTooltip<AFP_FireBall>(pPlayer->SkillLv.FireBall);
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

	UClass* Class = AFP_FireBlast::StaticClass();
	AFP_FireBlast* Skill = Class->GetDefaultObject<AFP_FireBlast>();
	Skill->Stat.Damage += Skill->SkillInfo.DmgPerLv*0.01f;
	Skill->Stat.CoolTimeRatio -= Skill->SkillInfo.AtkSpdPerLv;
	UpdateTooltip<AFP_FireBlast>(pPlayer->SkillLv.FireBlast);
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

	UClass* Class = AFP_FireWall::StaticClass();
	AFP_FireWall* Skill = Class->GetDefaultObject<AFP_FireWall>();
	Skill->Stat.Damage += Skill->SkillInfo.DmgPerLv*0.01f;
	Skill->Stat.CoolTimeRatio -= Skill->SkillInfo.AtkSpdPerLv;
	UpdateTooltip<AFP_FireWall>(pPlayer->SkillLv.FireWall);
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

	UClass* Class = AFP_IceBall::StaticClass();
	AFP_IceBall* Skill = Class->GetDefaultObject<AFP_IceBall>();
	Skill->Stat.Damage += Skill->SkillInfo.DmgPerLv*0.01f;
	Skill->Stat.CoolTimeRatio -= Skill->SkillInfo.AtkSpdPerLv;
	UpdateTooltip<AFP_IceBall>(pPlayer->SkillLv.IceBall);
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

	UClass* Class = AFP_IceBlast::StaticClass();
	AFP_IceBlast* Skill = Class->GetDefaultObject<AFP_IceBlast>();
	Skill->Stat.Damage += Skill->SkillInfo.DmgPerLv*0.01f;
	Skill->Stat.CoolTimeRatio -= Skill->SkillInfo.AtkSpdPerLv;
	UpdateTooltip<AFP_IceBlast>(pPlayer->SkillLv.IceBlast);
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

	UClass* Class = AFP_IceOrb::StaticClass();
	AFP_IceOrb* Skill = Class->GetDefaultObject<AFP_IceOrb>();
	Skill->Stat.Damage += Skill->SkillInfo.DmgPerLv*0.01f;
	Skill->Stat.CoolTimeRatio -= Skill->SkillInfo.AtkSpdPerLv;
	UpdateTooltip<AFP_IceOrb>(pPlayer->SkillLv.IceOrb);
}

