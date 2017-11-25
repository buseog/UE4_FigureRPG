// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Button.h"
#include "FP_MainUI.generated.h"



/**
 * 
 */
UCLASS()
class FIGUREPROJECT_API UFP_MainUI : public UUserWidget
{
	GENERATED_BODY()
public:
	enum BUTTONID { STAT, SKILL, RUNE, REV };
	enum STATE {START, IDLE , END};


	TArray<UButton*> ButtonArray;
	STATE eState = IDLE;

public:
	virtual void NativeConstruct() override;
	virtual bool Initialize() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;
	void SetMyVisibility(ESlateVisibility _visibility);
	
	float TimeAcc = 0.f;

	UFUNCTION()
	void Button_Stat();
	UFUNCTION()
	void Button_Skill();
	UFUNCTION()
	void Button_Rev();
	UFUNCTION()
	void Button_Rune();
	UFUNCTION()
	void Button_Exit();

	void OpenInventoryFromSkill(UFP_InventoryWidget::SORTORDER _order);
	

	template <typename T>
	void ResetSocket()
	{
		UClass* Class = T::StaticClass();
		T* Skill_CDO = Class->GetDefaultObject<T>();

		Skill_CDO->Stat.ActiveSocketNum = 0;

		for (int i = 0; i < Skill_CDO->Sockets.Num(); ++i)
		{
			if (Skill_CDO->Sockets[i].Rune == nullptr)
				continue;

			Skill_CDO->Sockets[i].Rune->bEquiped = false;
		}
		Skill_CDO->Sockets.Empty();
	}
};
