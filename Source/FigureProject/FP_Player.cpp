// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_Player.h"
#include "FP_PlayerController.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"


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
	
	
	MouseSphere = CreateDefaultSubobject<USphereComponent>(TEXT("MouseSphere"));
	MouseSphere->SetSphereRadius(10.f);
	//MouseSphere->SetupAttachment(RootComponent);
	MouseSphere->OnClicked.AddDynamic(this, &AFP_Player::ToggleStatus);
	MouseSphere->SetCollisionProfileName("BlockAll");
	
	Level.Level = 1;
	Level.Exp = 0.f;
	Level.FullExp = 100.f;
	Level.Point = 5;

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


}


// Called when the game starts or when spawned
void AFP_Player::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFP_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Regeneration(DeltaTime);
	
	Level.CheckLevelUp();
	//Level.Exp += 1.f;

	//철의 추가
	if (bIsBuffed)
	{
		if (BuffTime >= BuffDuration)
			SetStat(BuffType, BuffDiff, BuffDuration);

		BuffTime += DeltaTime;
	}
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

	Level.DecreasePoint();

	switch (_Type)
	{
	case 0:
		Status.MaxHp += 1.f;
		break;

	case 1:
		Status.HpRegen += 1.f;
		break;

	case 2:
		Status.Attack += 0.01f;
		break;

	case 3:
		Status.AttackRange += 1.f;
		break;

	case 4:
		Status.AttackSpeed -= 0.01f;
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
}


void AFP_Player::ToggleStatus(UPrimitiveComponent* AActor, FKey Button)
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AFP_PlayerController* PC = Cast<AFP_PlayerController>(Controller);
	
	PC->ToggleMainUI();
	
	

	UE_LOG(LogClass, Log, TEXT("HI"));
}

void AFP_Player::OnProxOverlapBegin(UPrimitiveComponent* _HitComp, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _SweepResult)
{
	
}

//철의 추가
void AFP_Player::SetStat(int Type, float Diff, float Duration, FColor Color) //Duration이 0이면 영구 적용
{
	if (Duration == 0)
	{
		BuffTime = 0.f;
		bIsBuffed = false;
		return;
	}

	if (BuffTime >= Duration)
	{
		BuffTime = 0.f;
		bIsBuffed = false;
		PointLight->SetIntensity(0.f);

		switch (Type)
		{
		case 0:
			Status.MaxHp -= Diff;
			break;

		case 1:
			Status.HpRegen -= Diff;
			break;

		case 2:
			Status.Attack -= Diff;
			break;

		case 3:
			Status.AttackRange -= Diff;
			break;

		case 4:
			Status.AttackSpeed += Diff;
			break;

		case 5:
			Status.BulletSpeed -= Diff;
			break;

		case 6:
			Status.Critical -= Diff;
			break;

		case 7:
			Status.CriticalDamage -= Diff;
			break;

		case 8:
			Status.Splash -= Diff;
			break;
		}

		return;
	}

	bIsBuffed = true;
	BuffDuration = Duration;
	BuffDiff = Diff;
	BuffType = Type;
	PointLight->SetLightColor(Color);
	PointLight->SetIntensity(500.f);

	switch (Type)
	{
	case 0:
		Status.MaxHp += Diff;
		break;

	case 1:
		Status.HpRegen += Diff;
		break;

	case 2:
		Status.Attack *= Diff;
		break;

	case 3:
		Status.AttackRange += Diff;
		break;

	case 4:
		Status.AttackSpeed -= Diff;
		break;

	case 5:
		Status.BulletSpeed += Diff;
		break;

	case 6:
		Status.Critical += Diff;
		break;

	case 7:
		Status.CriticalDamage += Diff;
		break;

	case 8:
		Status.Splash += Diff;
		break;
	}
}