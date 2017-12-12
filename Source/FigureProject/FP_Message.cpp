// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_Message.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"

bool UFP_Message::Initialize()
{
	Super::Initialize();

	Text = (UTextBlock*)GetWidgetFromName(TEXT("Message"));

	return true;
}

void UFP_Message::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	TimeAcc += DeltaTime;

	FLinearColor CurrentColor = Text->ColorAndOpacity.GetSpecifiedColor();
	FLinearColor NewColor = FLinearColor(CurrentColor.R, CurrentColor.G, CurrentColor.B, 1 - (TimeAcc / TimeLimit));
	Text->SetColorAndOpacity(NewColor);

	if (TimeAcc > TimeLimit)
	{
		this->RemoveFromViewport();
		TimeAcc = 0.f;
		return;
	}

}

void UFP_Message::ShowMessage(FText msg, int _font, float fTime, FColor _color)
{
	Text->SetText(msg);
	//Text->SetRenderTranslation(_uilocation);
	
	FSlateFontInfo NewInfo = Text->Font;
	NewInfo.Size = _font;
	Text->SetFont(NewInfo);
	
	FLinearColor color = _color;
	Text->SetColorAndOpacity(color);

	TimeLimit = fTime;
}