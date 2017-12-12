// Fill out your copyright notice in the Description page of Project Settings.


#include "FP_ComMessageUI.h"
#include "Engine.h"
#include "UserWidget.h"
#include "FP_PlayerController.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Runtime/Engine/Classes/Engine/UserInterfaceSettings.h"
#include "FP_Message.h"
#include "FP_Alarm.h"

//bool AFP_ComMessageUI::bShowMessage = false;
//float AFP_ComMessageUI::Time = 0.f;
//UTextBlock* AFP_ComMessageUI::Text = nullptr;

UFP_Message* AFP_ComMessageUI::Message = nullptr;
UFP_Alarm* AFP_ComMessageUI::Touch = nullptr;
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

}

void AFP_ComMessageUI::ShowMessage(AFP_PlayerController* pc, FText msg, float _time, FColor color)
{
	if (Message == nullptr || Message->IsValidLowLevel() == false)
	{
		FName Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_Message.FP_Message_C'");
		TSubclassOf<UFP_Message> MessageUIClass = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
		Message = CreateWidget<UFP_Message>(pc, MessageUIClass);
		Message->AddToViewport(1);
	}
	if (Message->IsInViewport() == false)
	{
		Message->AddToViewport(1);
	}

	//const FVector2D viewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	//const float viewportScale = GetDefault<UUserInterfaceSettings>(UUserInterfaceSettings::StaticClass())->GetDPIScaleBasedOnSize(FIntPoint(viewportSize.X, viewportSize.Y));

	/*FVector2D location;

	float MouseX;
	float MouseY;
	pc->GetMousePosition(MouseX, MouseY);
	location = FVector2D(MouseX, MouseY);
	
	location.X /= viewportScale;
	location.Y /= viewportScale;*/

	Message->ShowMessage(msg, 100,_time , FColor::Red);
}

void AFP_ComMessageUI::ShowTouched(AFP_PlayerController* pc)
{
	if (Touch == nullptr || Touch->IsValidLowLevel() == false)
	{
		FName Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_Touched.FP_Touched_C'");
		TSubclassOf<UFP_Alarm> TouchUIClass = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
		Touch = CreateWidget<UFP_Alarm>(pc, TouchUIClass);
		Touch->AddToViewport(1);
	}
	if (Touch->IsInViewport() == false)
	{
		Touch->AddToViewport(1);
	}
}