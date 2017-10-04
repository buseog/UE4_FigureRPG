// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_Player.h"
#include "FP_PlayerController.h"


// Sets default values
AFP_Player::AFP_Player()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraSpringArm->SetupAttachment(RootComponent);
	CameraSpringArm->TargetArmLength = 500.0f;
	CameraSpringArm->bAbsoluteRotation = true;
	//CameraSpringArm->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetupAttachment(RootComponent);

	SightSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SightSphere"));
	SightSphere->SetupAttachment(RootComponent);
	SightSphere->SetSphereRadius(Status.AttackRange);

	OnClicked.AddDynamic(this, &AFP_Player::ToggleStatus);

	Level.Level = 1;
	Level.Exp = 0.f;
	Level.FullExp = 100.f;
	Level.Point = 5;
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
	Level.Exp += 1.f;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("%f"), Status.Hp), true, FVector2D(5.f, 5.f));
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

	Status.Hp += Status.HpRegen;
}


void AFP_Player::StatusLevelUp(int _Type)
{
	if (Level.Point <= 0)
		return;

	Level.DecreasePoint();

	switch (_Type)
	{
	case 0:
		Status.Hp += 1.f;
		break;

	case 1:
		Status.HpRegen += 1.f;
		break;

	case 2:
		Status.Attack += 1.f;
		break;

	case 3:
		Status.AttackRange += 1.f;
		break;

	case 4:
		Status.AttackSpeed += 1.f;
		break;

	case 5:
		Status.BulletSpeed += 1.f;
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


void AFP_Player::ToggleStatus(AActor* AActor, FKey Button)
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	Cast<AFP_PlayerController>(Controller)->ToggleStatus();
}

void AFP_Player::OnProxOverlapBegin(UPrimitiveComponent* _HitComp, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _SweepResult)
{
	
}