// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FP_Message.generated.h"

/**
 * 
 */
UCLASS()
class FIGUREPROJECT_API UFP_Message : public UUserWidget
{
	GENERATED_BODY()
	

public:
	virtual bool Initialize() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

	class UTextBlock* Text;
	

	void ShowMessage(FText msg, int _font, float fTime, FColor _color);
	
	float TimeAcc = 0.f;
	float TimeLimit = 0.f;
	
};
