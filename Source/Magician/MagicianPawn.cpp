// Fill out your copyright notice in the Description page of Project Settings.

#include "MagicianPawn.h"
#include "Skills.h"
#include "MyHUD.h"


// Sets default values
AMagicianPawn::AMagicianPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create Component
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	m_CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	m_CameraSpringArm->SetupAttachment(RootComponent);
	m_CameraSpringArm->SetRelativeLocationAndRotation(FVector(50.0f, 0.0f, 50.0f), FRotator(-90.0f, 0.0f, 0.0f));
	//m_CameraSpringArm->SetWorldLocationAndRotation(FVector(0.0f, 0.0f, 120.0f), FRotator(0.0f, 0.0f, 0.0f));

	m_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	m_Camera->SetupAttachment(m_CameraSpringArm, USpringArmComponent::SocketName);

	//StaticMesh
	m_StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	m_StaticMesh->SetupAttachment(RootComponent);

	//StaticMesh'/Game/Box_Brush_StaticMesh.Box_Brush_StaticMesh'
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("StaticMesh'/Game/Box_Brush_StaticMesh.Box_Brush_StaticMesh'"));
	m_StaticMesh->SetStaticMesh(Cube.Object);
	
}

// Called when the game starts or when spawned
void AMagicianPawn::BeginPlay()
{
	Super::BeginPlay();

	m_pHUD = Cast<AMyHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
	
}

// Called every frame
void AMagicianPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_isBattle == true)
	{
		m_fTimeAcc += DeltaTime;
		if (m_fTimeAcc > 1.f)
		{
			UWorld* MyWorld = GetWorld();
			MyWorld->SpawnActor<ASkills>(FVector(5.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f));

			m_fTimeAcc = 0.f;
		}
	}
		
	if (m_isBattle == false)
		m_pHUD->SetDistance(DeltaTime * 5.f);

	if (m_isBattle == false && m_pHUD->GetDistance() >= 10 && int(m_pHUD->GetDistance()) % 10 == 0)
		m_isBattle = true;


}

// Called to bind functionality to input
void AMagicianPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

