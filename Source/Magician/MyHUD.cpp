// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHUD.h"
#include "Engine.h"




void AMyHUD::DrawHUD()
{
	Super::DrawHUD();

	FString TextFront = TEXT("Distance : ");
	FString dist = FString::FromInt(m_fTotalDistance);
	FString TextEnd = TEXT("m");

	FVector2D Viewport = GEngine->GameViewport->Viewport->GetSizeXY();

	//Draw Text with Score
	DrawText(TextFront + dist + TextEnd, FLinearColor(0.2f, 0.2f, 0.2f), (Viewport.X)/3.f, 10.f, 0, 1.f);

	
}