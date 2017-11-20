// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProgressBar.h"
#include "HPBar_Widget.generated.h"


/**
 * 
 */
UCLASS()
class FIGUREPROJECT_API UHPBar_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progress")
	float Progress = 1.f;

	UPROPERTY()
	UProgressBar* ProgressBar;
};
