// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_DamageUI.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"

bool UFP_DamageUI::Initialize()
{
	Super::Initialize();

	for (int i = 1; i <= 10; ++i)
	{
		FString Name = "Text" + FString::FromInt(i);
		UTextBlock* Text = (UTextBlock*)GetWidgetFromName(FName(*Name));
		Text->SetVisibility(ESlateVisibility::Hidden);
		TextArray.Add(Text);

		float LifeTime = 1.f;
		LifeTimeArray.Add(LifeTime);

		FVector2D Origin = FVector2D(0.f, 0.f);
		OriginLocation.Add(Origin);

		FColor OriginColor = FColor::White;
		ColorArray.Add(OriginColor);

		FontArray.Add(40.f);
	}
	
	return true;
}


void UFP_DamageUI::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	int iIndex = 0;
	for (size_t i = 0; i < TextArray.Num(); ++i)
	{
		if (TextArray[i]->GetVisibility() == ESlateVisibility::Visible)
		{
			LifeTimeArray[i] -= DeltaTime;
			FLinearColor color = FLinearColor(ColorArray[i].R, ColorArray[i].G, ColorArray[i].B, LifeTimeArray[i]);
			TextArray[i]->SetColorAndOpacity(color);

			float NewY = (LifeTimeArray[i] * -1.f + 1.f) * -20.f;
			TextArray[i]->SetRenderTranslation(FVector2D(OriginLocation[i].X - 50, OriginLocation[i].Y + NewY - 50));


			if (LifeTimeArray[i] < 0)
			{
				TextArray[i]->SetVisibility(ESlateVisibility::Hidden);
				LifeTimeArray[i] = 1.f;
			}
		}
		else
			++iIndex;
	}

	if (iIndex == TextArray.Num() && bDestroy == true)
		this->RemoveFromViewport();
}


void UFP_DamageUI::ShowDamage(float _damage, FVector2D _uilocation,int fontsize,  FColor color, bool isminus)
{
	for (size_t i = 0; i < TextArray.Num(); ++i)
	{
		if (TextArray[i]->GetVisibility() == ESlateVisibility::Visible)
			continue;

		TextArray[i]->SetVisibility(ESlateVisibility::Visible);
		ColorArray[i] = color;

		FSlateFontInfo NewInfo = TextArray[i]->Font;
		NewInfo.Size = fontsize;
		TextArray[i]->SetFont(NewInfo);

		//UE_LOG(LogClass, Log, TEXT("%d"), fontsize);
		
		FString Damage;
		if(isminus == true)
			Damage = "-" + FString::FromInt(FMath::RoundHalfToZero(_damage));
		else
			Damage = "+" + FString::FromInt(FMath::RoundHalfToZero(_damage));

		TextArray[i]->SetText(FText::FromString(Damage));

		OriginLocation[i] = _uilocation;
		break;

	}
}