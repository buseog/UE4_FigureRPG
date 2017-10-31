// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FP_SkillUI.generated.h"

/**
 * 
 */
UCLASS()
class FIGUREPROJECT_API UFP_SkillUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

	UFUNCTION()
	void ActiveFireBall();
	UFUNCTION()
	void ActiveFireBlast();
	UFUNCTION()
	void ActiveFireWall();
	UFUNCTION()
	void ActiveIceBall();
	UFUNCTION()
	void ActiveIceBlast();
	UFUNCTION()
	void ActiveIceOrb();


	UFUNCTION()
	void LvUpFireBall();
	UFUNCTION()
	void LvUpFireBlast();
	UFUNCTION()
	void LvUpFireWall();
	UFUNCTION()
	void LvUpIceBall();
	UFUNCTION()
	void LvUpIceBlast();
	UFUNCTION()
	void LvUpIceOrb();

	int SizeY = 320;
	int SkillCnt = 6;

	class UCircularThrobber* Throbber;
	
	
};
