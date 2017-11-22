// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_Player.h"
#include "FP_PlayerController.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "FP_MainUI.h"
#include "FP_MonsterMgr.h"
#include "Engine.h"
#include "FP_SaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "FP_StageWidget.h"
#include "FP_Tooltip.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"


// Sets default values
AFP_Player::AFP_Player()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraSpringArm->SetupAttachment(RootComponent);
	CameraSpringArm->TargetArmLength = 150.0f;
	CameraSpringArm->bAbsoluteRotation = true;
	CameraSpringArm->SetWorldLocation(FVector(0.f, 0.f, -10.f));
	CameraSpringArm->SetWorldRotation(FRotator(90.f, -90.f, 0.f));
	
	//this->SetActorHiddenInGame(true);
	//CameraSpringArm->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);
	Camera->PostProcessSettings.AutoExposureMaxBrightness = 1.f;
	Camera->PostProcessSettings.AutoExposureMinBrightness = 1.f;
	Camera->PostProcessSettings.AutoExposureBias = 0.f;
	Camera->PostProcessSettings.bOverride_AutoExposureBias = true;
	Camera->PostProcessSettings.bOverride_AutoExposureMaxBrightness = true;
	Camera->PostProcessSettings.bOverride_AutoExposureMinBrightness = true;
	
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetSphereRadius(12.f);
	CollisionSphere->SetupAttachment(RootComponent);
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AFP_Player::OnProxOverlapBegin);
	
	
	//MouseSphere = CreateDefaultSubobject<USphereComponent>(TEXT("MouseSphere"));
	//MouseSphere->SetSphereRadius(10.f);
	////MouseSphere->SetupAttachment(RootComponent);
	//MouseSphere->OnClicked.AddDynamic(this, &AFP_Player::ToggleStatus);
	//MouseSphere->SetCollisionProfileName("BlockAll");
	


	/*FName Path = TEXT("Blueprint'/Game/FP_ProximityWeapon_BP.FP_ProximityWeapon_BP_C'");
	UClass* WeaponBP = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
	Weapon = WeaponBP;*/

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"), true);
	PointLight->Intensity = 0.f;
	PointLight->AttenuationRadius = 10.f;
	PointLight->MoveComponent(FVector(this->GetActorLocation().X, this->GetActorLocation().Y, this->GetActorLocation().Z - 10.f), FRotator(), false);
	PointLight->SetupAttachment(RootComponent);

	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	Particle->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystem(TEXT("ParticleSystem'/Game/Effect/Player/P_Player.P_Player'"));
	Particle->SetTemplate(ParticleSystem.Object);
	
	Particle->SetVisibility(false);


	PaperSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PaperSprite"));
	

	static ConstructorHelpers::FObjectFinder<UPaperSprite> Sprite1(TEXT("PaperSprite'/Game/Icon/Player/FirePlayerNormal_Sprite.FirePlayerNormal_Sprite'"));
	FirePlayerIcon.Add(Sprite1.Object);
	static ConstructorHelpers::FObjectFinder<UPaperSprite> Sprite2(TEXT("PaperSprite'/Game/Icon/Player/FirePlayerBuff_Sprite.FirePlayerBuff_Sprite'"));
	FirePlayerIcon.Add(Sprite2.Object);
	static ConstructorHelpers::FObjectFinder<UPaperSprite> Sprite3(TEXT("PaperSprite'/Game/Icon/Player/FirePlayerHit_Sprite.FirePlayerHit_Sprite'"));
	FirePlayerIcon.Add(Sprite3.Object);
	static ConstructorHelpers::FObjectFinder<UPaperSprite> Sprite4(TEXT("PaperSprite'/Game/Icon/Player/FirePlayerAtt_Sprite.FirePlayerAtt_Sprite'"));
	FirePlayerIcon.Add(Sprite4.Object);
	
	static ConstructorHelpers::FObjectFinder<UPaperSprite> Sprite5(TEXT("PaperSprite'/Game/Icon/Player/IcePlayerNormal_Sprite.IcePlayerNormal_Sprite'"));
	IcePlayerIcon.Add(Sprite5.Object);
	static ConstructorHelpers::FObjectFinder<UPaperSprite> Sprite6(TEXT("PaperSprite'/Game/Icon/Player/IcePlayerBuff_Sprite.IcePlayerBuff_Sprite'"));
	IcePlayerIcon.Add(Sprite6.Object);
	static ConstructorHelpers::FObjectFinder<UPaperSprite> Sprite7(TEXT("PaperSprite'/Game/Icon/Player/IcePlayerHit_Sprite.IcePlayerHit_Sprite'"));
	IcePlayerIcon.Add(Sprite7.Object);
	static ConstructorHelpers::FObjectFinder<UPaperSprite> Sprite8(TEXT("PaperSprite'/Game/Icon/Player/IcePlayerAtt_Sprite.IcePlayerAtt_Sprite'"));
	IcePlayerIcon.Add(Sprite8.Object);

	PaperSprite->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	PaperSprite->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
	PaperSprite->SetVisibility(false);

	
	
}


// Called when the game starts or when spawned
void AFP_Player::BeginPlay()
{
	Super::BeginPlay();

	if (MyType == FIRE)
		PaperSprite->SetSprite(FirePlayerIcon[0]);
	else
		PaperSprite->SetSprite(IcePlayerIcon[0]);

	Particle->EmitterInstances[1]->bEnabled = false;
	Particle->EmitterInstances[2]->bEnabled = false;
	Particle->EmitterInstances[3]->bEnabled = false;
	Particle->EmitterInstances[4]->bEnabled = false;
	Particle->EmitterInstances[5]->bEnabled = false;
	Particle->EmitterInstances[6]->bEnabled = false;
	
}

// Called every frame
void AFP_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AFP_PlayerController* PC = Cast<AFP_PlayerController>(Controller);

	//Regeneration(DeltaTime);

	StateChanger(DeltaTime);
	
	/*TimeAcc += DeltaTime;
	UUserWidget* Test = PC->GetWidgetMap(AFP_PlayerController::MAINUI);
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::FromInt(int(Test->IsValidLowLevel())));*/
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::SanitizeFloat(TimeAcc));
	
	CheckLevelUp();
	//Level.Exp += 1.f;

	//철의 추가
	/*if (bIsBuffed)
	{
		if (BuffTime >= BuffDuration)
			SetStat(BuffType, BuffDiff, BuffDuration);

		BuffTime += DeltaTime;
	}*/

	CheckBuff(DeltaTime);
}

void AFP_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AFP_Player::TakeDamage(float _Damage, struct FDamageEvent const& _DamageEvent, class AController* _EventInstigator, class AActor* _DamageCauser)
{
	HitTime = 1.f;

	return Status.Hp;
}

void AFP_Player::Regeneration(float DeltaTime)
{
	HitTime -= DeltaTime;

	if (HitTime >= 0.f)
		return;

	Status.Hp += Status.HpRegen * DeltaTime;
	if (Status.Hp >= Status.MaxHp)
		Status.Hp = Status.MaxHp;
}


void AFP_Player::StatusLevelUp(int _Type)
{
	if (Level.Point <= 0)
		return;

	switch (_Type)
	{
	case 0:
		Status.MaxHp += 10.f;
		Status.Hp += 10.f;
		break;

	case 1:
		Status.HpRegen += 1.f;
		break;

	case 2:
		Status.Attack += 0.5f;
		break;

	case 3:
		Status.AttackRange += 1.f;
		break;

	case 4:
		if (Status.AttackSpeed >= 0.75)
			Status.AttackSpeed -= 0.005f;
		else
			return;

		break;

	case 5:
		Status.BulletSpeed += 10.f;
		break;

	case 6:
		Status.Critical += 1.f;
		break;

	case 7:
		Status.CriticalDamage += 1.f;
		break;

	case 8:
		Status.Splash += 1.f;
		break;
	}

	Level.Point--;
}

void AFP_Player::CheckLevelUp()
{
	if (Level.Exp >= Level.FullExp)
	{
		++Level.Level;
		Level.Point += 1;
		Level.Exp -= Level.FullExp;
		Level.FullExp = FMath::Pow(2, Level.Level) * 50.f; // 승렬수정
		Status.Hp = Status.MaxHp;

		if (Level.Level % 5 == 0)
			SkillLv.SkillPoint++;
	}
	
}
void AFP_Player::OnProxOverlapBegin(UPrimitiveComponent* _HitComp, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _SweepResult)
{
	
}

//철의 추가
//void AFP_Player::SetStat(int Type, float Diff, float Duration, FColor Color) //Duration이 0이면 영구 적용
//{
//	if (Duration == 0)
//	{
//		BuffTime = 0.f;
//		bIsBuffed = false;
//		return;
//	}
//
//	if (BuffTime >= Duration)
//	{
//		BuffTime = 0.f;
//		bIsBuffed = false;
//		PointLight->SetIntensity(0.f);
//		Particle->EmitterInstances[1]->bEnabled = false;
//		Particle->EmitterInstances[2]->bEnabled = false;
//		Particle->EmitterInstances[3]->bEnabled = false;
//		Particle->EmitterInstances[4]->bEnabled = false;
//		Particle->EmitterInstances[5]->bEnabled = false;
//		Particle->EmitterInstances[6]->bEnabled = false;
//
//		switch (Type)
//		{
//		case 0:
//			Status.MaxHp -= Diff;
//			break;
//
//		case 1:
//			Status.HpRegen -= Diff;
//			break;
//
//		case 2:
//			Status.Attack /= Diff;
//			break;
//
//		case 3:
//			Status.AttackRange -= Diff;
//			break;
//
//		case 4:
//			Status.AttackSpeed += Diff;
//			break;
//
//		case 5:
//			Status.BulletSpeed -= Diff;
//			break;
//
//		case 6:
//			Status.Critical -= Diff;
//			break;
//
//		case 7:
//			Status.CriticalDamage -= Diff;
//			break;
//
//		case 8:
//			Status.Splash -= Diff;
//			break;
//		}
//
//		return;
//	}
//
//	bIsBuffed = true;
//	BuffDuration = Duration;
//	BuffDiff = Diff;
//	BuffType = Type;
//	PointLight->SetLightColor(Color);
//	PointLight->SetIntensity(500.f);
//
//	FVector color;
//
//	switch (Type)
//	{
//	case 0:
//		Status.MaxHp += Diff;
//		break;
//
//	case 1:
//		Status.HpRegen += Diff;
//		break;
//
//	case 2:
//		Status.Attack *= Diff;
//		Particle->EmitterInstances[1]->bEnabled = true;
//		Particle->EmitterInstances[2]->bEnabled = true;
//		Particle->EmitterInstances[3]->bEnabled = true;
//		break;
//
//	case 3:
//		Status.AttackRange += Diff;
//		break;
//
//	case 4:
//		Status.AttackSpeed -= Diff;
//		Particle->EmitterInstances[4]->bEnabled = true;
//		Particle->EmitterInstances[5]->bEnabled = true;
//		Particle->EmitterInstances[6]->bEnabled = true;
//		break;
//
//	case 5:
//		Status.BulletSpeed += Diff;
//		break;
//
//	case 6:
//		Status.Critical += Diff;
//		break;
//
//	case 7:
//		Status.CriticalDamage += Diff;
//		break;
//
//	case 8:
//		Status.Splash += Diff;
//		break;
//	}
//}

void AFP_Player::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	UFP_SaveGame* SaveGameInstance = Cast<UFP_SaveGame>(UGameplayStatics::CreateSaveGameObject(UFP_SaveGame::StaticClass()));
	
	SaveGameInstance->Hp = Status.Hp;
	SaveGameInstance->MaxHp = Status.MaxHp;
	SaveGameInstance->Attack = Status.Attack;
	SaveGameInstance->AttackSpeed = Status.AttackSpeed;
	SaveGameInstance->AttackRange = Status.AttackRange;
	SaveGameInstance->BulletSpeed = Status.BulletSpeed;

	SaveGameInstance->FireBall = SkillLv.FireBall;
	SaveGameInstance->FireBlast = SkillLv.FireBlast;
	SaveGameInstance->FireWall = SkillLv.FireWall;
	SaveGameInstance->IceBall = SkillLv.IceBall;
	SaveGameInstance->IceBlast = SkillLv.IceBlast;
	SaveGameInstance->IceOrb = SkillLv.IceOrb;
	SaveGameInstance->SkillPoint = SkillLv.SkillPoint;

	SaveGameInstance->Level = Level.Level;
	SaveGameInstance->Exp = Level.Exp;
	SaveGameInstance->FullExp = Level.FullExp;
	SaveGameInstance->Point = Level.Point;
	SaveGameInstance->ActiveSkill = int(AFP_Weapon::ActiveSkill);
	SaveGameInstance->PlayerType = int(MyType);

	SaveGameInstance->Stage = AFP_MonsterMgr::Stage;
	SaveGameInstance->MonsterKillCnt = AFP_MonsterMgr::MonsterKillCnt;
	SaveGameInstance->Gem = Gem;

	SaveGameInstance->Inventory.Empty();

	for (int i = 0; i < Inventory.Num(); ++i)
	{
		FInventoryLoad inventory;

		inventory.Color = Inventory[i]->Color;
		inventory.Property = Inventory[i]->Property;
		inventory.Damage = Inventory[i]->Stat.Damage;
		inventory.Speed = Inventory[i]->Stat.Speed;
		inventory.CoolTimeRatio = Inventory[i]->Stat.CoolTimeRatio;
		inventory.Range = Inventory[i]->Stat.Range;
		inventory.Tier = Inventory[i]->Stat.Tier;
		inventory.IgniteDamage = Inventory[i]->Ignite.Damage;
		inventory.IgniteDuration = Inventory[i]->Ignite.Duration;
		inventory.SlowDamage = Inventory[i]->Slow.Damage;
		inventory.SlowDuration = Inventory[i]->Slow.Duration;

		inventory.FreezeProbability = Inventory[i]->Frozen.Probability;
		inventory.FreezeDuration = Inventory[i]->Frozen.Duration;

		inventory.ExpBonus = Inventory[i]->ExpBonus;

		inventory.Name = Inventory[i]->Name;

		inventory.bEquiped = Inventory[i]->bEquiped;
		inventory.SkillIndex = Inventory[i]->iSkillIndex;
		inventory.SocketIndex = Inventory[i]->iSocketIndex;
		
		for (int j = 0; j < Inventory[i]->Stat.Type.Num(); ++j)
			inventory.Type.Add(Inventory[i]->Stat.Type[j]);

		for (int j = 0; j < Inventory[i]->Option.Num(); ++j)
		{
			switch (j)
			{
			case 0:
				inventory.Option1 = Inventory[i]->Option[j];
				break;
			case 1:
				inventory.Option2 = Inventory[i]->Option[j];
				break;
			case 2:
				inventory.Option3 = Inventory[i]->Option[j];
				break;
			}
		}

		for (int j = 0; j < Inventory[i]->OptionVal.Num(); ++j)
		{
			switch (j)
			{
			case 0:
				inventory.OptionVal1 = Inventory[i]->OptionVal[j];
				break;
			case 1:
				inventory.OptionVal2 = Inventory[i]->OptionVal[j];
				break;
			case 2:
				inventory.OptionVal3 = Inventory[i]->OptionVal[j];
				break;
			}
		}

		SaveGameInstance->Inventory.Add(inventory);
	}

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
}

void AFP_Player::RestartStage()
{
	//UE_LOG(LogClass, Log, TEXT("DEAD"));
	Status.Hp = Status.MaxHp;
	/*if (BuffTime < BuffDuration)
	{
		BuffTime += BuffDuration;
		SetStat(BuffType, BuffDiff, BuffDuration);
	}*/

	Buff = NORMAL;
	TimeAccForBuff = 0.f;

	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AFP_PlayerController* PC = Cast<AFP_PlayerController>(Controller);
	Cast<UFP_StageWidget>(PC->GetWidgetMap(AFP_PlayerController::STAGE))->CountTime = 5.9f;

	PC->SetPause(true);
	
}

void AFP_Player::CheckBuff(float _deltaTime)
{
	if (TimeAccForBuff >= Duration)
	{
		TimeAccForBuff = 0.f;
		Buff = NORMAL;
	}

	switch (Buff)
	{
	case DMGUP:
		TimeAccForBuff += _deltaTime;
		Particle->EmitterInstances[1]->bEnabled = true;
		Particle->EmitterInstances[2]->bEnabled = true;
		Particle->EmitterInstances[3]->bEnabled = true;
		bIsBuffed = true;
		break;

	case ATTSPDUP:
		TimeAccForBuff += _deltaTime;
		Particle->EmitterInstances[4]->bEnabled = true;
		Particle->EmitterInstances[5]->bEnabled = true;
		Particle->EmitterInstances[6]->bEnabled = true;
		bIsBuffed = true;
		break;

	case NORMAL:
		Particle->EmitterInstances[1]->bEnabled = false;
		Particle->EmitterInstances[2]->bEnabled = false;
		Particle->EmitterInstances[3]->bEnabled = false;
		Particle->EmitterInstances[4]->bEnabled = false;
		Particle->EmitterInstances[5]->bEnabled = false;
		Particle->EmitterInstances[6]->bEnabled = false;
		bIsBuffed = false;
		break;
	}
}

void AFP_Player::SetBuff(BUFFTYPE _buff, float _multiplier, float _duration)
{
	Buff = _buff;
	Multiplier = _multiplier;
	Duration = _duration;
}

void AFP_Player::StateChanger(float _deltaTime)
{
	TArray<UPaperSprite*> PaperSpriteArray;
	if (MyType == FIRE)
		PaperSpriteArray = FirePlayerIcon;
	else
		PaperSpriteArray = IcePlayerIcon;


	if (Buff == NORMAL)
	{
		if (MyState == BUFF)
			MyState = IDLE;
		else if (MyState != IDLE)
		{
			StateTimeAcc += _deltaTime;
			if (StateTimeAcc > 0.5f)
			{
				MyState = IDLE;
				StateTimeAcc = 0.f;
			}
		}
	}
	else
	{
		if (MyState == IDLE)
			MyState = BUFF;
		else if (MyState != BUFF) // BUFF, ATTACK , HIT
		{
			StateTimeAcc += _deltaTime;
			if (StateTimeAcc > 0.5f)
			{
				MyState = BUFF;
				StateTimeAcc = 0.f;
			}
		}
	}

	//if (MyState != IDLE && MyState != BUFF)
	//{
	//	StateTimeAcc += _deltaTime;
	//	if (StateTimeAcc > 0.5f)
	//	{
	//		MyState = IDLE;
	//		StateTimeAcc = 0.f;
	//	}
	//}
	
	switch (MyState)
	{
	case IDLE:
		PaperSprite->SetSprite(PaperSpriteArray[IDLE]);
		break;
	case BUFF:
		PaperSprite->SetSprite(PaperSpriteArray[BUFF]);
		break;
	case HIT:
		PaperSprite->SetSprite(PaperSpriteArray[HIT]);
		break;
	case ATTACK:
		PaperSprite->SetSprite(PaperSpriteArray[ATTACK]);
		break;
	}


}