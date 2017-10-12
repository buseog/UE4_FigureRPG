// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FP_Item.generated.h"

UCLASS()
class FIGUREPROJECT_API AFP_Item : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFP_Item();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	float Speed;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void MoveToPlayer(float DeltaTime);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int Quantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	UTexture2D* Icon;
	
};
