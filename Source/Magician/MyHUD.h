// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class MAGICIAN_API AMyHUD : public AHUD
{
	GENERATED_BODY()
	
	
public:
	void DrawHUD() override;

public:
	//store total score
	void SetDistance(float _dist) { m_fTotalDistance += _dist; }
	float GetDistance() { return m_fTotalDistance; }

private:
	float m_fTotalDistance = 0.f;
	
};
