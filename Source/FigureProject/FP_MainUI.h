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

	bool isStatClicked = false;
	bool isRuneClicked = false;

public:
	virtual void NativeConstruct() override;
	virtual bool Initialize() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;
	
	float TimeAcc = 0.f;

	UFUNCTION()
	void Button_Stat();
	UFUNCTION()
	void Button_Rune();
	
};
