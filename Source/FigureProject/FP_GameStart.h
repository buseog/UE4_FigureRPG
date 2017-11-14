// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FP_GameStart.generated.h"

enum WEAPONTYPE {MELEE, RANGE, TYPE_END};

/**
 * 
 */
UCLASS()
class FIGUREPROJECT_API UFP_GameStart : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

public:
	UFUNCTION()
	void ChooseFire();

	UFUNCTION()
	void ChooseIce();

	void StartWithLoad();
private:

};
