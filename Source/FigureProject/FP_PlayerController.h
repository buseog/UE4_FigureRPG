// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FP_PlayerController.generated.h"

/**
 * 
 */



class UFP_StatusWidget;

UCLASS()
class FIGUREPROJECT_API AFP_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	enum eSTAT { HP, HPREGEN, ATTACK, ATTACKRANGE, ATTACKSPEED };
	enum eWIDGET { GAMESTART, STAGE, STATUS, MAINUI, SKILLUI, SKILLTOOLTIP, INVENTORY, RUNETOOLTIP};
	

	AFP_PlayerController();

public:
	virtual void BeginPlay() override;
	
public:
	bool	bShowMainUI;
	static bool    isRev;
	static bool		isDead;
public:
	/*UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = StatusUI)
	TSubclassOf<UFP_StatusWidget> StatusUI;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = StatusUI)
	UFP_StatusWidget* StatusWidget;*/
	
	//TMap<eWIDGET, UUserWidget*> WidgetMap;
	UPROPERTY()
	TArray<UUserWidget*> WidgetArray;

	UUserWidget* GetWidgetMap(eWIDGET _key);

public:
	UFUNCTION(BlueprintCallable, Category = UI)
	void ToggleMainUI();

	void SetVisibility(eWIDGET _WidgetNum, bool _isvisible);
	bool Load();


	template<typename T>
	void SetSkillDetail(int iSkillLv)
	{
		UClass* Class = T::StaticClass();
		T* SkillCDO = Class->GetDefaultObject<T>();

		SkillCDO->Stat.Damage = 1.f + SkillCDO->SkillInfo.DmgPerLv*0.01f * iSkillLv;
		SkillCDO->Stat.CoolTimeRatio = 1.f - SkillCDO->SkillInfo.AtkSpdPerLv * iSkillLv;
	}

	template<typename T>
	void LoadRuneInfoIntoSocket(int _socketIndex, class AFP_Rune* _rune);

};
