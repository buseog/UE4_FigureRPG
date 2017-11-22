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
#include "FP_ComCalculator.h"
#include "FP_DamageUI.h"
#include "FP_PlayerController.h"
#include "Runtime/Engine/Classes/Engine/UserInterfaceSettings.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Runtime/Engine/Classes/Engine/RendererSettings.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "FP_Tooltip.h"
#include "FP_Skill.h"

// Sets default values
AFP_Monster::AFP_Monster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SphereComponent->InitSphereRadius(3.0f);
	SphereComponent->SetupAttachment(RootComponent);

	SetActorEnableCollision(true);


	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	Particle->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystem(TEXT("ParticleSystem'/Game/Effect/Player/Debuf.Debuf'"));
	Particle->SetTemplate(ParticleSystem.Object);
	Particle->SetVisibility(false);



	PaperSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PaperSprite"));
	PaperSprite->SetupAttachment(RootComponent);
	PaperSprite->SetRelativeScale3D(FVector(0.05f, 0.05f, 0.05f));
	PaperSprite->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));

	static ConstructorHelpers::FObjectFinder<UPaperSprite> Sprite1(TEXT("PaperSprite'/Game/Icon/Monster/WhiteSqareMonsterA_Sprite.WhiteSqareMonsterA_Sprite'"));
	MonsterIconArray.Add(Sprite1.Object);
	static ConstructorHelpers::FObjectFinder<UPaperSprite> Sprite2(TEXT("PaperSprite'/Game/Icon/Monster/WhiteSqareMonsterB_Sprite.WhiteSqareMonsterB_Sprite'"));
	MonsterIconArray.Add(Sprite2.Object);
	static ConstructorHelpers::FObjectFinder<UPaperSprite> Sprite3(TEXT("PaperSprite'/Game/Icon/Monster/WhiteSqareMonsterC_Sprite.WhiteSqareMonsterC_Sprite'"));
	MonsterIconArray.Add(Sprite3.Object);
	static ConstructorHelpers::FObjectFinder<UPaperSprite> Sprite4(TEXT("PaperSprite'/Game/Icon/Monster/WhiteSqareMonsterD_Sprite.WhiteSqareMonsterD_Sprite'"));
	MonsterIconArray.Add(Sprite4.Object);
	static ConstructorHelpers::FObjectFinder<UPaperSprite> Sprite5(TEXT("PaperSprite'/Game/Icon/Monster/WhiteSqareMonsterHit_Sprite.WhiteSqareMonsterHit_Sprite'"));
	MonsterIconArray.Add(Sprite5.Object);
	static ConstructorHelpers::FObjectFinder<UPaperSprite> Sprite11(TEXT("PaperSprite'/Game/Icon/Monster/WhiteSqareMonsterDie_Sprite.WhiteSqareMonsterDie_Sprite'"));
	MonsterIconArray.Add(Sprite11.Object);

	static ConstructorHelpers::FObjectFinder<UPaperSprite> Sprite6(TEXT("PaperSprite'/Game/Icon/Monster/WhiteTriangleMonsterA_Sprite.WhiteTriangleMonsterA_Sprite'"));
	MonsterIconArray.Add(Sprite6.Object);
	static ConstructorHelpers::FObjectFinder<UPaperSprite> Sprite7(TEXT("PaperSprite'/Game/Icon/Monster/WhiteTriangleMonsterB_Sprite.WhiteTriangleMonsterB_Sprite'"));
	MonsterIconArray.Add(Sprite7.Object);
	static ConstructorHelpers::FObjectFinder<UPaperSprite> Sprite8(TEXT("PaperSprite'/Game/Icon/Monster/WhiteTriangleMonsterC_Sprite.WhiteTriangleMonsterC_Sprite'"));
	MonsterIconArray.Add(Sprite8.Object);
	static ConstructorHelpers::FObjectFinder<UPaperSprite> Sprite9(TEXT("PaperSprite'/Game/Icon/Monster/WhiteTriangleMonsterD_Sprite.WhiteTriangleMonsterD_Sprite'"));
	MonsterIconArray.Add(Sprite9.Object);
	static ConstructorHelpers::FObjectFinder<UPaperSprite> Sprite10(TEXT("PaperSprite'/Game/Icon/Monster/WhiteTriangleMonsterHit_Sprite.WhiteTriangleMonsterHit_Sprite'"));
	MonsterIconArray.Add(Sprite10.Object);
	static ConstructorHelpers::FObjectFinder<UPaperSprite> Sprite12(TEXT("PaperSprite'/Game/Icon/Monster/WhiteTriangleMonsterDie_Sprite.WhiteTriangleMonsterDie_Sprite'"));
	MonsterIconArray.Add(Sprite12.Object);
}

// Called when the game starts or when spawned
void AFP_Monster::BeginPlay()
{
	Super::BeginPlay();

	DropRate = FMath::FRandRange(0.f, 100.f);
	
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


		if (DamageUI != nullptr)
			DamageUI->bDestroy = true;
		//isDestroy = false;
		Destroy();
		return;
	}
	
	BehaviourChanger(DeltaTime);

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
		location.Y -= 80.f;

		HP_UI->ProgressBar->SetRenderTranslation(location);
	}
		


	AFP_Player* player = AFP_ComCollision::Collision<USphereComponent, AFP_Player>(SphereComponent);
	if (player != nullptr)
	{
		player->MyState = AFP_Player::HIT;
		MyBehaviour = DEAD;
		player->Status.Hp -= HP;
		if (player->Status.Hp < 1)
			player->RestartStage();


		return;

		//Weapon->DeleteTargetMonsterInArray(this);
	}
	//State Control

	ChangeState(DeltaTime);
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
	
	Player->Level.Exp += Exp * 	ExpBonus;
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
	if (isDestroy == true || MyBehaviour == DEAD)
		return;
	
	MyBehaviour = HIT;
	HP -= _damage;
	HPShowTime = 1.f;

	if (HP <= 0)
	{
		MyBehaviour = DEAD;

		if (HP_UI != nullptr)
			HP_UI->RemoveFromViewport();
	}
		
	

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

void AFP_Monster::ChangeState(float _delta)
{
	if (StateMgr.Num() == 0)
	{
		Particle->SetVisibility(false);
	}
	else
	{
		for (int i = 0; i < StateMgr.Num(); ++i)
		{
			StateMgr[i].Duration -= _delta;
			if (StateMgr[i].Duration < 0)
			{
				//StateMgr.Remove(StateMgr[i]);
				StateMgr.RemoveAt(i);
				continue;
			}

			if (StateMgr[i].eState == SLOW)
			{
				StateMgr[i].SpeedOffset = 0.5f;
				Particle->SetVisibility(true);
				Particle->SetVectorParameter("Color", FVector(0.f, 1.f, 0.f));
			}
			//damage
			else if (StateMgr[i].eState == IGNITE)
			{
				Particle->SetVisibility(true);
				Particle->SetVectorParameter("Color", FVector(1.f, 0.f, 0.f));

				StateMgr[i].TimelimitForIgnite -= _delta;
				if (StateMgr[i].TimelimitForIgnite > 0.f)
					return;

				MyTakeDamage(MaxHP * StateMgr[i].Damage, 30, FColor(255, 0, 0));
			}
			else if (StateMgr[i].eState == FROZEN)
			{
				Particle->SetVisibility(true);
				Particle->SetVectorParameter("Color", FVector(0.f, 0.f, 1.f));
				StateMgr[i].SpeedOffset = 0.f;
			}
			StateMgr[i].TimelimitForIgnite = 0.2f;
		}
	}
}
void AFP_Monster::BehaviourChanger(float _delta)
{
	if (MyBehaviour != IDLE && MyBehaviour != DEAD)
	{
		StateTimeAcc += _delta;
		if (StateTimeAcc > 0.5f)
		{
			MyBehaviour = IDLE;
			StateTimeAcc = 0.f;
		}
	}

	float Alpha;
	switch (MyBehaviour)
	{
	case IDLE:
		PaperSprite->SetSprite(MonsterIconArray[OriginIcon]);
		break;
	case HIT:
		if(OriginIcon < SQUARE_WHITE_HIT)
			PaperSprite->SetSprite(MonsterIconArray[SQUARE_WHITE_HIT]);
		else
			PaperSprite->SetSprite(MonsterIconArray[TRIANGLE_WHITE_HIT]);
		break;
	case DEAD:
		if (OriginIcon < SQUARE_WHITE_HIT)
			PaperSprite->SetSprite(MonsterIconArray[SQUARE_WHITE_DEAD]);
		else
			PaperSprite->SetSprite(MonsterIconArray[TRIANGLE_WHITE_DEAD]);

		DeadTimeAcc += _delta;

		Alpha = 1 - DeadTimeAcc;
		PaperSprite->SetSpriteColor(FLinearColor(PaperSprite->GetSpriteColor().R, PaperSprite->GetSpriteColor().G, PaperSprite->GetSpriteColor().B, Alpha));
		if (DeadTimeAcc > 1.f)
			isDestroy = true;


		
		break;
	}
}