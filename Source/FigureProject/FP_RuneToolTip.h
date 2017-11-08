// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Button.h"
#include "FP_Rune.h"
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
	
public:
	void ToggleToolTip(AFP_Rune* _rune);
	void InitializeToolTip();
};
