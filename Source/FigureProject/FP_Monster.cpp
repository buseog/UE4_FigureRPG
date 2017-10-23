// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_Monster.h"
#include "FP_Weapon.h"
#include "Engine.h"
#include "FP_HUD.h"
#include "FP_ItemDropRate.h"
#include "FP_PlayerController.h"
#include "FP_Player.h"
#include "WidgetComponent.h"
#include "FP_Item_PowerUp.h"
#include "FP_Item_AttackSpeedUp.h"
#include "FP_Player.h"


// Sets default values
AFP_Monster::AFP_Monster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MonsterMesh(TEXT("StaticMesh'/Game/Mesh/Sphere_Monster.Sphere_Monster'"));
	StaticMesh->SetStaticMesh(MonsterMesh.Object);


	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SphereComponent->InitSphereRadius(3.0f);
	SphereComponent->SetupAttachment(RootComponent);

	SetActorEnableCollision(true);
	SphereComponent->bGenerateOverlapEvents = true;
	SphereComponent->SetNotifyRigidBodyCollision(true);

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	WidgetComponent->SetupAttachment(SphereComponent);
	
	FName Path = TEXT("WidgetBlueprint'/Game/WidgetBP/HealthBar.HealthBar_C'");
	UClass* Widget = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));

	WidgetComponent->SetWidgetClass(Widget);
	WidgetComponent->SetDrawSize(FVector2D(10.f, 1.f));
	WidgetComponent->SetBlendMode(EWidgetBlendMode::Opaque);
	WidgetComponent->SetRelativeRotation(FRotator(-90.f, 0.f, 90.f));
	WidgetComponent->SetRelativeLocation(FVector(0.f, 10.f, 0.f));
	WidgetComponent->bGenerateOverlapEvents = false;
	//WidgetComponent->SetRelativeScale3D(FVector(0.5f, 0.5f, 1.f));
	//WidgetComponent->SetupAttachment(RootComponent);
	WidgetComponent->SetVisibility(false);

	
}

// Called when the game starts or when spawned
void AFP_Monster::BeginPlay()
{
	Super::BeginPlay();

	DropRate = FMath::FRandRange(0.f, 100.f);
	HPBar_Widget = Cast<UHPBar_Widget>(WidgetComponent->GetUserWidgetObject());

}

// Called every frame
void AFP_Monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (isDestroy == true)
	{

		//isDestroy = false;
		Destroy();
		return;
	}
	
	HPShowTime -= DeltaTime;
	if (HPShowTime > 0)
		WidgetComponent->SetVisibility(true);
	else
		WidgetComponent->SetVisibility(false);


	
}

void AFP_Monster::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	DropItem();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController == nullptr)
		return;

	AFP_HUD* Hud = Cast<AFP_HUD>(PlayerController->GetHUD());
	if (Hud != nullptr)
		Hud->IncreaseKillCount();

	AFP_PlayerController* CustomPlayerController = Cast<AFP_PlayerController>(PlayerController);

	AFP_Player* Player = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	Player->Level.Exp += Exp;
	
}


void AFP_Monster::DropItem()
{	
	if(isDestroy && Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0))->bIsBuffed)
		return;

	TActorIterator<AFP_Item> ActorItr = TActorIterator<AFP_Item>(GetWorld());

	for (; ActorItr; ++ActorItr)
		return;

	if (DropRate <= 100.f * StatUp_DropRate && isDestroy)
	{
		int Type = FMath::FRandRange(1.f, 3.f);

		switch (Type)
		{
		case 1:
			Item = GetWorld()->SpawnActor<AFP_Item_PowerUp>(this->GetActorLocation(), FRotator());

			if (Item == NULL)
				return;

			break;

		case 2:
			Item = GetWorld()->SpawnActor<AFP_Item_AttackSpeedUp>(this->GetActorLocation(), FRotator());

			if (Item == NULL)
				return;

			break;

			/*case 3:
			Item = GetWorld()->SpawnActor<AFP_Item_PowerUp>();
			Item->SetActorLocation(DropLocation);*/
		}
	}

	isDestroy = false;
}

void AFP_Monster::MyTakeDamage(float _damage)
{
	HP -= _damage;
	HPBar_Widget->Progress = (HP) / MaxHP;
	HPShowTime = 1.f;

	if (HP <= 0)
		isDestroy = true;

	/*float Test = HP / MaxHP;
	UE_LOG(LogClass, Log, TEXT("%f"), Test);
	UE_LOG(LogClass, Log, TEXT("%f"), HPBar_Widget->Progress);*/
}