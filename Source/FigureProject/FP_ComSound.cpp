// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_ComSound.h"


// Sets default values
AFP_ComSound::AFP_ComSound()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USoundCue> ButtonCue(TEXT("SoundCue'/Game/Sound/SoundCue_Button.SoundCue_Button'"));

	ButtonAudioCue = ButtonCue.Object;

	ButtonAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("ButtonAudioComp"));
	ButtonAudioComponent->bAutoActivate = false;
	ButtonAudioComponent->SetRelativeLocation(FVector(0, 0, 0));
}

void AFP_ComSound::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (ButtonAudioCue->IsValidLowLevel())
		ButtonAudioComponent->SetSound(ButtonAudioCue);
}

// Called when the game starts or when spawned
void AFP_ComSound::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFP_ComSound::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

void AFP_ComSound::PlaySound(FString _name, float _fadeTime, float _volume, float _startTime)
{
	if (_name == "Button")
	{
		ButtonAudioComponent->FadeIn(_fadeTime, _volume, _startTime);
		ButtonAudioComponent->SetUISound(true);
		ButtonAudioComponent->Play();
	}
}