// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FP_PlayerController.generated.h"

/**
 * 
 */

enum eSTAT { HP, HPREGEN, ATTACK, ATTACKRANGE, ATTACKSPEED };

class UFP_StatusWidget;

UCLASS()
class FIGUREPROJECT_API AFP_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AFP_PlayerController();

public:
	virtual void BeginPlay() override;
	
private:
	bool	bShowStatus;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = StatusUI)
	TSubclassOf<UFP_StatusWidget> StatusUI;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = StatusUI)
	UFP_StatusWidget* StatusWidget;

public:
	UFUNCTION(BlueprintCallable, Category = UI)
	void ToggleStatus();
	UFUNCTION(BlueprintCallable, Category = UI)
	void StatusLevelUp(int _Type);
};
