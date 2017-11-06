// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_StatusWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Engine.h"
#include "FP_PlayerController.h"
#include "FP_Player.h"
#include "FP_MainUI.h"

void UFP_StatusWidget::NativeConstruct()
{
	Super::NativeConstruct();

}
bool UFP_StatusWidget::Initialize()
{
	Super::Initialize();

	UButton* Button = (UButton*)GetWidgetFromName(TEXT("Button_HP"));
	Button->OnClicked.AddDynamic(this, &UFP_StatusWidget::Button_HP);

	Button = (UButton*)GetWidgetFromName(TEXT("Button_HpRegen"));
	Button->OnClicked.AddDynamic(this, &UFP_StatusWidget::Button_HpRegen);

	Button = (UButton*)GetWidgetFromName(TEXT("Button_Attack"));
	Button->OnClicked.AddDynamic(this, &UFP_StatusWidget::Button_Attack);

	Button = (UButton*)GetWidgetFromName(TEXT("Button_AttackRange"));
	Button->OnClicked.AddDynamic(this, &UFP_StatusWidget::Button_AttackRange);

	Button = (UButton*)GetWidgetFromName(TEXT("Button_AttackSpeed"));
	Button->OnClicked.AddDynamic(this, &UFP_StatusWidget::Button_AttackSpeed);

	Button = (UButton*)GetWidgetFromName(TEXT("Button_BulletSpeed"));
	Button->OnClicked.AddDynamic(this, &UFP_StatusWidget::Button_BulletSpeed);

	Button = (UButton*)GetWidgetFromName(TEXT("Button_Critical"));
	Button->OnClicked.AddDynamic(this, &UFP_StatusWidget::Button_Critical);

	Button = (UButton*)GetWidgetFromName(TEXT("Button_CriticalDamage"));
	Button->OnClicked.AddDynamic(this, &UFP_StatusWidget::Button_CriticalDamage);

	Button = (UButton*)GetWidgetFromName(TEXT("Button_Splash"));
	Button->OnClicked.AddDynamic(this, &UFP_StatusWidget::Button_Splash);

	return true;
}
void UFP_StatusWidget::Button_HP()
{
	AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
	if (nullptr == pPlayer)
		return;

	pPlayer->StatusLevelUp(0);
}

void UFP_StatusWidget::Button_HpRegen()
{
	AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (nullptr == pPlayer)
		return;

	pPlayer->StatusLevelUp(1);
}

void UFP_StatusWidget::Button_Attack()
{
	AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (nullptr == pPlayer)
		return;

	pPlayer->StatusLevelUp(2);
}

void UFP_StatusWidget::Button_AttackRange()
{
	AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (nullptr == pPlayer)
		return;

	pPlayer->StatusLevelUp(3);
}

void UFP_StatusWidget::Button_AttackSpeed()
{
	AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (nullptr == pPlayer)
		return;

	pPlayer->StatusLevelUp(4);
}

void UFP_StatusWidget::Button_BulletSpeed()
{
	AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (nullptr == pPlayer)
		return;

	pPlayer->StatusLevelUp(5);
}

void UFP_StatusWidget::Button_Critical()
{
	AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (nullptr == pPlayer)
		return;

	pPlayer->StatusLevelUp(6);
}

void UFP_StatusWidget::Button_CriticalDamage()
{
	AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (nullptr == pPlayer)
		return;

	pPlayer->StatusLevelUp(7);
}

void UFP_StatusWidget::Button_Splash()
{
	AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (nullptr == pPlayer)
		return;

	pPlayer->StatusLevelUp(8);
}

void UFP_StatusWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AFP_PlayerController* PC = Cast<AFP_PlayerController>(Controller);

	

}