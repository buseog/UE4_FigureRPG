// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FP_StatusWidget.generated.h"

/**
 * 
 */
class AFP_Player;

UCLASS()
class FIGUREPROJECT_API UFP_StatusWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;


public:
	UFUNCTION(BlueprintCallable, Category = Button)
	void Button_HP();

	UFUNCTION(BlueprintCallable, Category = Button)
	void Button_HpRegen();

	UFUNCTION(BlueprintCallable, Category = Button)
	void Button_Attack();

	UFUNCTION(BlueprintCallable, Category = Button)
	void Button_AttackRange();

	UFUNCTION(BlueprintCallable, Category = Button)
	void Button_AttackSpeed();

	UFUNCTION(BlueprintCallable, Category = Button)
	void Button_BulletSpeed();

	UFUNCTION(BlueprintCallable, Category = Button)
	void Button_Critical();

	UFUNCTION(BlueprintCallable, Category = Button)
	void Button_CriticalDamage();

	UFUNCTION(BlueprintCallable, Category = Button)
	void Button_Splash();
};
