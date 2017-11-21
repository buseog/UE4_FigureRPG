// Fill out your copyright notice in the Description page of Project Settings.


#include "FP_ComMessageUI.h"
#include "Engine.h"
#include "UserWidget.h"
#include "FP_PlayerController.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"

bool AFP_ComMessageUI::bShowMessage = false;
float AFP_ComMessageUI::Time = 0.f;
UTextBlock* AFP_ComMessageUI::Text = nullptr;
// Sets default values
AFP_ComMessageUI::AFP_ComMessageUI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFP_ComMessageUI::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AFP_ComMessageUI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShowMessage == true)
	{
		Time -= DeltaTime;
		if (Time < 0.f)
		{
			bShowMessage = false;
			Text->SetVisibility(ESlateVisibility::Hidden);
		}
	}

}

void AFP_ComMessageUI::ShowMessage(AFP_PlayerController* pc, FText msg, float _time)
{
	bShowMessage = true;
	
	UTextBlock* MyText = (UTextBlock*)pc->GetWidgetMap(AFP_PlayerController::STAGE)->GetWidgetFromName(TEXT("Count"));
	MyText->SetText(msg);
	MyText->SetVisibility(ESlateVisibility::Visible);
	Time = _time;

	Text = MyText;
}