// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "FP_Monster.h"
#include "FP_Skill.h"
#include "GameFramework/Actor.h"
#include "FP_Weapon.generated.h"





UCLASS()
class FIGUREPROJECT_API AFP_Weapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFP_Weapon();

	enum SKILLTYPE { FIREBALL, FIREBLAST, FIREWALL, ICEBALL , ICEBLAST, ICEORB};


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
	float GetStatfromSkill(FString _stat);
	inline void SetActiveSkill(SKILLTYPE _type) { ActiveSkill = _type; }
	
	//UStaticMeshComponent* StaticMesh;
	UPROPERTY()
	USphereComponent* SphereComponent;

	float AngleZ = 0.f;
	float TimeAcc = 0.f;
	FVector FirePoint = FVector(0.f,0.f,0.f);
	float Damage = 1.f;
	float ReloadTime = 1.f;

	UPROPERTY()
	TArray<AFP_Monster*> TargetMonsters;


	SKILLTYPE ActiveSkill;
	class AFP_Skill* Skill;
	//UStaticMesh* Mesh;


	template<typename T>
	T* CustomSpawn(FVector SpawnLocation, FRotator SpawnRotator)
	{
		UClass*  Class = AFP_Skill::StaticClass();
		AFP_Skill* Skill_CDO = Class->GetDefaultObject<AFP_Skill>();
		
		FTransform transform = FTransform(SpawnRotator, SpawnLocation);


		T* Skill = GetWorld()->SpawnActorDeferred<T>(T::StaticClass(), transform);

		Skill->Sockets = Skill_CDO->Sockets;
		
		UGameplayStatics::FinishSpawningActor(Skill, transform);

		return Skill;
	}

	
};


