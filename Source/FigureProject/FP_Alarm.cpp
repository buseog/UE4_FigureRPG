// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_Alarm.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "FP_Player.h"


bool UFP_Alarm::Initialize()
{
	Super::Initialize();

	Touch = (UTextBlock*)GetWidgetFromName(TEXT("Touch"));

	return true;
}

void UFP_Alarm::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	TimeAcc += DeltaTime;
	float fAlpha = cosf(TimeAcc*5.f) * 0.5f + 0.5f;

	FLinearColor CurrentColor = Touch->ColorAndOpacity.GetSpecifiedColor();
	FLinearColor NewColor = FLinearColor(CurrentColor.R, CurrentColor.G, CurrentColor.B, fAlpha);
	Touch->SetColorAndOpacity(NewColor);

	AFP_Player* Player = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Player == nullptr)
		return;

	if (Player->isPressedUI == false)
		this->RemoveFromViewport();

}
