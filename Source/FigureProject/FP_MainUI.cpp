// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_MainUI.h"
#include "FP_PlayerController.h"
#include "Engine.h"


void UFP_MainUI::NativeConstruct()
{
	Super::NativeConstruct();


	
	
}

bool UFP_MainUI::Initialize()
{
	Super::Initialize();

	UE_LOG(LogClass, Log, TEXT("INIT"));

	UButton* Button = (UButton*)GetWidgetFromName(TEXT("Stat"));
	Button->OnClicked.AddDynamic(this, &UFP_MainUI::Button_Stat);
	ButtonArray.Add(Button);

	Button = (UButton*)GetWidgetFromName(TEXT("Skill"));
	Button->OnClicked.AddDynamic(this, &UFP_MainUI::Button_Skill);
	ButtonArray.Add(Button);

	Button = (UButton*)GetWidgetFromName(TEXT("Rune"));
	ButtonArray.Add(Button);

	Button = (UButton*)GetWidgetFromName(TEXT("Rev"));
	ButtonArray.Add(Button);

	return true;
}

void UFP_MainUI::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	//UE_LOG(LogClass, Log, TEXT("%f"), (float)eState);

	if (eState == IDLE)
		return;

	if (eState == START)
		TimeAcc += DeltaTime;
	else
		TimeAcc -= DeltaTime;

	float Angle = TimeAcc * -1000.f;
	float NewScale = 0.f;
	int RotNum = 2;
	if (Angle > -360.f * RotNum && Angle < 0.f)
	{
		NewScale = TimeAcc * 1.5f;
		NewScale = FMath::Clamp(NewScale, 0.f, 1.f);

		

		for (size_t i = 0; i < ButtonArray.Num(); ++i)
		{
			ButtonArray[i]->SetRenderAngle(Angle);
			ButtonArray[i]->SetRenderScale(FVector2D(NewScale, NewScale));

			FVector2D NewLocation;
			float Radius = TimeAcc * 200.f;
			Radius = FMath::Clamp(Radius, 0.f, 100.f);

			float AngleOffSet = 2 * PI / ButtonArray.Num();

			NewLocation.X = Radius * cosf(TimeAcc * -5.f + AngleOffSet * i) - 32.5f;
			NewLocation.Y = Radius * sinf(TimeAcc * -5.f + AngleOffSet * i) - 32.5f;
			ButtonArray[i]->SetRenderTranslation(NewLocation);
		}
	}
	else
	{
		for (size_t i = 0; i < ButtonArray.Num(); ++i)
		{
			ButtonArray[i]->SetRenderAngle(0.f);
		}

		if(eState == START)
			eState = IDLE;
		else if (eState == END)
		{
			eState = IDLE;
			RemoveFromViewport();
		}
	}

	
}

void UFP_MainUI::Button_Stat()
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UUserWidget* StatWidget = Cast<AFP_PlayerController>(Controller)->GetWidgetMap(AFP_PlayerController::STATUS);

	if (isStatClicked == false)
	{
		StatWidget->AddToViewport();
		isStatClicked = true;
	}
	else
	{
		StatWidget->RemoveFromViewport();
		isStatClicked = false;
	}	
}

void UFP_MainUI::Button_Skill()
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UUserWidget* SkillWidget = Cast<AFP_PlayerController>(Controller)->GetWidgetMap(AFP_PlayerController::SKILLUI);

	if (isSkillClicked == false)
	{
		SkillWidget->AddToViewport();
		isSkillClicked = true;
	}
	else
	{
		SkillWidget->RemoveFromViewport();
		isSkillClicked = false;
	}
}