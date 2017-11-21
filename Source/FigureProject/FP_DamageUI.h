// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "FP_DamageUI.generated.h"

/**
 * 
 */
UCLASS()
class FIGUREPROJECT_API UFP_DamageUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

public:
	TArray<class UTextBlock*> TextArray;
	TArray<float> LifeTimeArray;
	TArray<FVector2D> OriginLocation;
	TArray<FColor> ColorArray;
	TArray<float> FontArray;
	void ShowDamage(float _damage, FVector2D _uilocation, int fontsize, FColor color);
	bool bDestroy = false;
};
