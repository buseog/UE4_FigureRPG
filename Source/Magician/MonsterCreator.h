// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "MonsterCreator.generated.h"

UCLASS()
class MAGICIAN_API AMonsterCreator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonsterCreator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MonsterDead(void);
	bool GetisSpawn(void) { return m_isSpawn; }

	
private:
	bool m_isSpawn = false;

	UPROPERTY()
	class AMagicianPawn* m_pMagicianPawn;

};
