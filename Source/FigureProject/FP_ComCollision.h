// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FP_ComCollision.generated.h"

UCLASS()
class FIGUREPROJECT_API AFP_ComCollision : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFP_ComCollision();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	template<typename A, typename B>
	static B* Collision(A* InputComponent)
	{
		TArray<AActor*> Actors;
		InputComponent->GetOverlappingActors(Actors);

		for (int i = 0; i < Actors.Num(); ++i)
		{
			B* Target = Cast<B>(Actors[i]);
			if (Target == NULL)
				continue;

			return Target;
		}
		return NULL;
		
	}


	template<typename A, typename B>
	static void CollisionWithMulti(A* InputComponent, TArray<B*>& _Array)
	{
		TArray<AActor*> Actors;
		InputComponent->GetOverlappingActors(Actors);

		for (int i = 0; i < Actors.Num(); ++i)
		{
			B* Target = Cast<B>(Actors[i]);
			if (Target != NULL)
			{
				_Array.Add(Target);
			}
		}
	}


};
