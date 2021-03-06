// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_Item_AttackSpeedUp.h"
#include "FP_Player.h"

AFP_Item_AttackSpeedUp::AFP_Item_AttackSpeedUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	/*LightColor = FColor(0, 255, 0);
	ChangeMesh(FString("StaticMesh'/Game/Mesh/FP_Item_AttackSpeedUp.FP_Item_AttackSpeedUp'"), StaticMesh);
	ChangeLight(LightColor);*/

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystem(TEXT("ParticleSystem'/Game/Effect/Item/FP_AttackSpeedUp.FP_AttackSpeedUp'"));
	Particle->SetTemplate(ParticleSystem.Object);
	Particle->SetWorldScale3D(FVector(0.4f, 0.4f, 0.4f));
}

void AFP_Item_AttackSpeedUp::BeginPlay()
{
	Super::BeginPlay();

}

void AFP_Item_AttackSpeedUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFP_Item_AttackSpeedUp::OnProxOverlapBegin(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetName().Contains("Player"))
	{
		//Cast<AFP_Player>(OtherActor)->SetStat(4, 0.2f, 3.f, LightColor);
		Cast<AFP_Player>(OtherActor)->SetBuff(AFP_Player::ATTSPDUP, 0.5f, 3.f);
		Destroy();
	}
}