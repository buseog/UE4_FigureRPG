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
#include "FP_ComCollision.h"
#include "FP_MonsterMgr.h"
#include "FP_DamageUI.h"
#include "FP_PlayerController.h"
#include "Runtime/Engine/Classes/Engine/UserInterfaceSettings.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Runtime/Engine/Classes/Engine/RendererSettings.h"

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


	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	Particle->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystem(TEXT("ParticleSystem'/Game/Effect/Player/Debuf.Debuf'"));
	Particle->SetTemplate(ParticleSystem.Object);
	Particle->SetVisibility(false);

	
}

// Called when the game starts or when spawned
void AFP_Monster::BeginPlay()
{
	Super::BeginPlay();

	DropRate = FMath::FRandRange(0.f, 100.f);
	


	StateMgr.Monster = this;

	TArray<AActor*> FoundActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFP_Weapon::StaticClass(), FoundActor);
	if (FoundActor[0] == nullptr)
		return;

	Weapon = Cast<AFP_Weapon>(FoundActor[0]);
	
	HP_UI = nullptr;
	DamageUI = nullptr;
	
	
}

// Called every frame
void AFP_Monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (isDestroy == true)
	{
		if(HP_UI != nullptr)
			HP_UI->RemoveFromViewport();

		if (DamageUI != nullptr)
			DamageUI->bDestroy = true;
		//isDestroy = false;
		Destroy();
		return;
	}
	
	HPShowTime -= DeltaTime;
	if (HP_UI != nullptr)
	{
		if( HPShowTime > 0)
			HP_UI->SetVisibility(ESlateVisibility::Visible);
		else
			HP_UI->SetVisibility(ESlateVisibility::Hidden);

		APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		AFP_PlayerController* PC = Cast<AFP_PlayerController>(Controller);

		const FVector2D viewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
		const float viewportScale = GetDefault<UUserInterfaceSettings>(UUserInterfaceSettings::StaticClass())->GetDPIScaleBasedOnSize(FIntPoint(viewportSize.X, viewportSize.Y));

		FVector2D location;
		PC->ProjectWorldLocationToScreen(this->GetActorLocation(), location);
		location.X /= viewportScale;
		location.Y /= viewportScale;
		location.X -= 25.f;
		location.Y -= 45.f;

		HP_UI->ProgressBar->SetRenderTranslation(location);
	}
		


	AFP_Player* player = AFP_ComCollision::Collision<USphereComponent, AFP_Player>(SphereComponent);
	if (player != nullptr)
	{
		isDestroy = true;
		player->Status.Hp -= HP;
		if (player->Status.Hp < 1)
			player->RestartStage();

		return;

		//Weapon->DeleteTargetMonsterInArray(this);
	}
	//State Control
	StateMgr.CustomTick(DeltaTime);
	
		
	if (StateMgr.eState == IGNITE)
	{
		StateMgr.TimelimitForIgnite -= DeltaTime;
		if (StateMgr.TimelimitForIgnite > 0.f)
			return;

		MyTakeDamage(MaxHP * StateMgr.Damage, 30, FColor(255, 0, 0));

		//if (isDestroy)
			//Weapon->DeleteTargetMonsterInArray(this);
	}
	StateMgr.TimelimitForIgnite = 0.2f;
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
	
	AFP_MonsterMgr::MonsterKillCnt++;

}


void AFP_Monster::DropItem()
{	
	if(!isDestroy)
		return;

	AFP_Player* Player = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Player == nullptr)
		return;

	if (Player->bIsBuffed)
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

	//isDestroy = false;
}

void AFP_Monster::MyTakeDamage(float _damage, int fontsize, FColor color)
{
	if (isDestroy == true)
		return;
	
	HP -= _damage;
	HPShowTime = 1.f;

	if (HP <= 0)
		isDestroy = true;

	

	//show damage ui

	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AFP_PlayerController* PC = Cast<AFP_PlayerController>(Controller);

	if (DamageUI == nullptr)
	{
		FName Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_DamageNum.FP_DamageNum_C'");
		TSubclassOf<UFP_DamageUI> DamageUIClass = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
		DamageUI = CreateWidget<UFP_DamageUI>(PC, DamageUIClass);
		DamageUI->AddToViewport(-1);
	}
	if (HP_UI == nullptr)
	{
		FName Path = TEXT("WidgetBlueprint'/Game/WidgetBP/HealthBar.HealthBar_C'");
		TSubclassOf<UHPBar_Widget> HPUIClass = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
		HP_UI = CreateWidget<UHPBar_Widget>(PC, HPUIClass);
		//HP_UI->viewport
		HP_UI->AddToViewport(-1);
	}

	const FVector2D viewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	const float viewportScale = GetDefault<UUserInterfaceSettings>(UUserInterfaceSettings::StaticClass())->GetDPIScaleBasedOnSize(FIntPoint(viewportSize.X, viewportSize.Y));

	FVector2D location;
	PC->ProjectWorldLocationToScreen(this->GetActorLocation(), location);
	location.X /= viewportScale;
	location.Y /= viewportScale;

	DamageUI->ShowDamage(_damage, location, fontsize, color);

	HP_UI->Progress = (HP) / MaxHP;

	
	

	//GEngine->AddOnScreenDebugMessage(-1.f, 1.f, FColor::Blue, FString::SanitizeFloat(viewportScale));

	/*float Test = HP / MaxHP;
	UE_LOG(LogClass, Log, TEXT("%f"), Test);
	UE_LOG(LogClass, Log, TEXT("%f"), HPBar_Widget->Progress);*/
}