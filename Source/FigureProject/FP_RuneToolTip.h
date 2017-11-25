// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Button.h"
#include "FP_Rune.h"
#include "FP_Skill.h"
#include "FP_RuneToolTip.generated.h"

/**
 * 
 */
UCLASS()
class FIGUREPROJECT_API UFP_RuneToolTip : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
	FText Option1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
	FText Option2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
	FText Option3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
	FText Option4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
	TArray<FText> Option;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
	FText Val1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
	FText Val2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
	FText Val3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
	FText Val4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color")
	FColor Color = FColor(1.f, 1.f, 1.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tier")
	FText Tier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button")
	UButton* EquipButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button")
	UButton* DeleteButton;

	AFP_Skill* SelectedSkill = nullptr;
	static AFP_Rune* SelectedRune;

	UPROPERTY()
	TArray<UButton*> PropButtonArray;
	
public:
	void ToggleToolTip(AFP_Rune* _rune, bool _fromInventory = true, AFP_Skill* _skill = nullptr);
	void InitializeToolTip();

	UFUNCTION()
	void EquipRune();

	UFUNCTION()
	void DeleteRune();

	UFUNCTION()
	void Gamble();

	UFUNCTION()
	void ChangeOptionRune();
};
