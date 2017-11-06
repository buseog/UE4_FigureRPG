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
	enum eWIDGET { GAMESTART, STAGE, STATUS, MAINUI, SKILLUI, SKILLTOOLTIP };

	AFP_PlayerController();

public:
	virtual void BeginPlay() override;
	
public:
	bool	bShowMainUI;

public:
	/*UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = StatusUI)
	TSubclassOf<UFP_StatusWidget> StatusUI;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = StatusUI)
	UFP_StatusWidget* StatusWidget;*/
	
	TMap<eWIDGET, UUserWidget*> WidgetMap;

	inline UUserWidget* GetWidgetMap(eWIDGET _key) { return WidgetMap[_key]; }

public:
	UFUNCTION(BlueprintCallable, Category = UI)
	void ToggleMainUI();

	void SetVisibility(eWIDGET _WidgetNum, bool _isvisible);
};
