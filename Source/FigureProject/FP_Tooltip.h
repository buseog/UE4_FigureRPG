// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FP_Tooltip.generated.h"

/**
 * 
 */
UCLASS()
class FIGUREPROJECT_API UFP_Tooltip : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
		FText CurrentLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
		FText CurrentDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
		FText CurrentAtkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
		FText CurrentCurse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
		FText NextLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
		FText NextDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
		FText NextAtkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
		FText NextCurse;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
		FText SkillName;
	
	
};
