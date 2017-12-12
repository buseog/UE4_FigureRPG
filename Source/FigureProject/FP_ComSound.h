// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundBase.h"
#include "FP_ComSound.generated.h"

UCLASS()
class FIGUREPROJECT_API AFP_ComSound : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFP_ComSound();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	USoundCue* ButtonAudioCue;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	USoundCue* BuffAudioCue;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	USoundCue* DieAudioCue;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	USoundCue* FireAudioCue;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	USoundCue* IceAudioCue;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	USoundCue* LevelUpAudioCue;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	UAudioComponent* ButtonAudioComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	UAudioComponent* BuffAudioComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	UAudioComponent* DieAudioComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	UAudioComponent* FireAudioComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	UAudioComponent* IceAudioComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	UAudioComponent* LevelUpAudioComponent;

public:
	void PlaySound(FString _name, float _fadeTime, float _volume, float _startTime);


	
};
