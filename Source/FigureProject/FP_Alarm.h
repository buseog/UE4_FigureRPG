// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FP_Alarm.generated.h"

/**
 * 
 */
UCLASS()
class FIGUREPROJECT_API UFP_Alarm : public UUserWidget
{
	GENERATED_BODY()
	
	
	virtual bool Initialize() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

	class UTextBlock* Touch;

	float TimeAcc = 0.f;
	
};
