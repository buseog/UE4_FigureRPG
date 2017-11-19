// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FP_StageWidget.generated.h"

/**
 * 
 */
UCLASS()
class FIGUREPROJECT_API UFP_StageWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
	FText StageText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
	FText LevelText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
	FText GemText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progress")
	float Progress = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progress")
	float PlayerHP = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
	FText PlayerHPText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
	FText SkillText;

	virtual bool Initialize() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;


	UFUNCTION()
	void Button_MainUI();

	UFUNCTION()
	void Button_Exit();


public:
	class UTextBlock* CountText;
	float CountTime = 10.f;
public:
	void DeadCount();
};
