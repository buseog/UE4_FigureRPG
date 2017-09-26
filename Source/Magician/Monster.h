// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "MonsterCreator.h"
#include "GameFramework/Actor.h"
#include "Monster.generated.h"

UCLASS()
class MAGICIAN_API AMonster : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	UStaticMeshComponent* m_StaticMesh;
	UPROPERTY(VisibleAnywhere)
	USphereComponent* m_SphereComponent;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



	void SetMonsterCreator(AMonsterCreator* pMonsterCreator) { m_pMonsterCreator = pMonsterCreator; }

private:
	UPROPERTY()
	AMonsterCreator* m_pMonsterCreator;

};
