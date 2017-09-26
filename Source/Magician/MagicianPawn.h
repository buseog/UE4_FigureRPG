// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "GameFramework/Pawn.h"
#include "MagicianPawn.generated.h"

UCLASS()
class MAGICIAN_API AMagicianPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMagicianPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	bool GetisBattle() { return m_isBattle; }
	void SetisBattle(bool _isBattle) { m_isBattle = _isBattle; }


	UPROPERTY()
	USpringArmComponent* m_CameraSpringArm;
	UCameraComponent* m_Camera;
	UStaticMeshComponent* m_StaticMesh;


private:
	float m_fTimeAcc = 0.f;
	bool m_isBattle = false;
	
	class AMyHUD* m_pHUD;
};
