// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "FP_Monster.h"
#include "GameFramework/Actor.h"
#include "FP_Weapon.generated.h"





UCLASS()
class FIGUREPROJECT_API AFP_Weapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFP_Weapon();
	enum SKILLTYPE { FIREBALL, FIREBLAST, FIREWALL, ICEBALL , ICEBLAST};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void DeleteTargetMonsterInArray(AFP_Monster* _monster);
	void SpawnSkill();
	inline void SetActiveSkill(SKILLTYPE _type) { ActiveSkill = _type; }
	
	//UStaticMeshComponent* StaticMesh;
	UPROPERTY()
	USphereComponent* SphereComponent;

	float AngleZ = 0.f;
	float TimeAcc = 0.f;
	FVector FirePoint = FVector(0.f,0.f,0.f);
	float Damage = 1.f;

	UPROPERTY()
	TArray<AFP_Monster*> TargetMonsters;


	SKILLTYPE ActiveSkill;
	//UStaticMesh* Mesh;

	
};


