// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FP_SkillUI.generated.h"

/**
 * 
 */
class FP_Tooltip;

UCLASS()
class FIGUREPROJECT_API UFP_SkillUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

	UFUNCTION()
	void ActiveFireBall();
	UFUNCTION()
	void ActiveFireBlast();
	UFUNCTION()
	void ActiveFireWall();
	UFUNCTION()
	void ActiveIceBall();
	UFUNCTION()
	void ActiveIceBlast();
	UFUNCTION()
	void ActiveIceOrb();


	UFUNCTION()
	void LvUpFireBall();
	UFUNCTION()
	void LvUpFireBlast();
	UFUNCTION()
	void LvUpFireWall();
	UFUNCTION()
	void LvUpIceBall();
	UFUNCTION()
	void LvUpIceBlast();
	UFUNCTION()
	void LvUpIceOrb();

	int SizeY = 320;
	int SkillCnt = 6;

	class UCircularThrobber* Throbber;
	bool isSkillClicked = false;
	
	template<typename T>
	void UpdateTooltip(int SkillLv)
	{
		AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		AFP_PlayerController* PC = Cast<AFP_PlayerController>(Controller);
		UUserWidget* ToolTip = PC->GetWidgetMap(AFP_PlayerController::SKILLTOOLTIP);
		UFP_Tooltip* ToolTipClass = Cast<UFP_Tooltip>(ToolTip);

		UClass* Class = T::StaticClass();
		T* SKill = Class->GetDefaultObject<T>();

		float DamageLv = SKill->SkillInfo.DmgPerLv;
		float AttackSpeedLv = SKill->SkillInfo.AtkSpdPerLv;

		ToolTipClass->CurrentLevel = FText::FromString(FString::FromInt(SkillLv));
		ToolTipClass->CurrentDamage = FText::FromString(FString::FromInt(SKill->Stat.Damage*100.f) + "%");
		ToolTipClass->CurrentAtkSpeed = FText::FromString(FString::SanitizeFloat(FMath::RoundHalfToEven((1 / (SKill->Stat.CoolTimeRatio)) * 100) / 100) + "/sec");

		ToolTipClass->NextLevel = FText::FromString(FString::FromInt(SkillLv + 1));
		ToolTipClass->NextDamage = FText::FromString(FString::FromInt(SKill->Stat.Damage*100.f + DamageLv) + "%");
		ToolTipClass->NextAtkSpeed = FText::FromString(FString::SanitizeFloat(FMath::RoundHalfToEven((1 / (SKill->Stat.CoolTimeRatio - AttackSpeedLv)) * 100) / 100) + "/sec");

	}

	template<typename T>
	void PrepareTooltip(AFP_PlayerController::eWIDGET _widgetName, FName _path, FText Skillname, float SkillLv)
	{
		if (SkillLv == 0.f)
			return;

		APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		AFP_PlayerController* PC = Cast<AFP_PlayerController>(Controller);
		UUserWidget* ToolTip = PC->GetWidgetMap(_widgetName);

		if (ToolTip->IsValidLowLevel() == false)
		{
			RecreateWidget<UFP_Tooltip>(_path, PC, _widgetName);
			ToolTip = PC->GetWidgetMap(_widgetName);
			Cast<UFP_Tooltip>(ToolTip)->SetSKillUI(this);
		}

		if (isSkillClicked == false)
		{
			FVector2D MousePosition;
			Controller->GetMousePosition(MousePosition.X, MousePosition.Y);
			ToolTip->SetRenderTranslation(MousePosition);

			UFP_Tooltip* ToolTipClass = Cast<UFP_Tooltip>(ToolTip);
			ToolTipClass->SkillName = Skillname;// FText::FromString(TEXT("FireBall"));

			UClass* Class = T::StaticClass();
			T* SKill = Class->GetDefaultObject<T>();
			ToolTipClass->CurrentSkill = SKill;
			
			float DamageLv = SKill->SkillInfo.DmgPerLv;
			float AttackSpeedLv = SKill->SkillInfo.AtkSpdPerLv;

			ToolTipClass->CurrentLevel = FText::FromString(FString::FromInt(SkillLv));
			ToolTipClass->CurrentDamage = FText::FromString(FString::FromInt(SKill->Stat.Damage*100.f) + "%");
			ToolTipClass->CurrentAtkSpeed = FText::FromString(FString::SanitizeFloat(FMath::RoundHalfToEven((1 / (SKill->Stat.CoolTimeRatio))*100)/100) + "/sec");

			ToolTipClass->NextLevel = FText::FromString(FString::FromInt(SkillLv + 1));
			ToolTipClass->NextDamage = FText::FromString(FString::FromInt(SKill->Stat.Damage*100.f + DamageLv) + "%");
			ToolTipClass->NextAtkSpeed = FText::FromString(FString::SanitizeFloat(FMath::RoundHalfToEven((1 / (SKill->Stat.CoolTimeRatio - AttackSpeedLv))*100)/100) + "/sec");

			ToolTip->AddToViewport();
			isSkillClicked = true;
		}
		else
		{
			ToolTip->RemoveFromViewport();
			isSkillClicked = false;
		}
	}

	template<typename T>
	void RecreateWidget(FName _path, AFP_PlayerController* _pc, AFP_PlayerController::eWIDGET _widgetname)
	{
		TSubclassOf<T> Widget = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *_path.ToString()));
		T* SkillWidget = CreateWidget<T>(_pc, Widget);
		_pc->WidgetMap.Add(_widgetname, SkillWidget);
	}
};
