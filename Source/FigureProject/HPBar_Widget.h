// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HPBar_Widget.generated.h"

/**
 * 
 */
UCLASS()
class FIGUREPROJECT_API UHPBar_Widget : public UUserWidget
{
	GENERATED_BODY()

	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progress")
	float Progress = 1.f;


};
