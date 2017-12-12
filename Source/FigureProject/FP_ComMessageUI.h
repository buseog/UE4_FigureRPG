// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FP_ComMessageUI.generated.h"

UCLASS()
class FIGUREPROJECT_API AFP_ComMessageUI : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFP_ComMessageUI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	static void ShowMessage(class AFP_PlayerController* pc, FText msg , float _time , FColor color = FColor::Black);
	static void ShowTouched(class AFP_PlayerController* pc);

	static class UFP_Message* Message;
	static class UFP_Alarm* Touch;
};
