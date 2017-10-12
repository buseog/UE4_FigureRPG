// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_Weapon.h"
#include "Engine.h"
#include "FP_Bullet.h"
#include "FP_Player.h"
#include "FP_HUD.h"

struct CompareDist
{
	CompareDist(FVector _FirePoint) : FirePoint(_FirePoint) {};
	
	FVector FirePoint;

	bool operator()(const AFP_Monster& A, const AFP_Monster& B) const
	{
		FVector Avector = A.GetActorLocation() - FirePoint;
		FVector Bvector = B.GetActorLocation() - FirePoint;

		return Avector.Size() < Bvector.Size();
	}
};

// Sets default values
AFP_Weapon::AFP_Weapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MonsterMesh(TEXT("StaticMesh'/Game/Weapon_Mesh.Weapon_Mesh'"));
	//StaticMesh->SetStaticMesh(MonsterMesh.Object);
	Mesh = MonsterMesh.Object;


	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->InitSphereRadius(50.f);

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AFP_Weapon::OnOverlapBegin);

	SetActorEnableCollision(true);
	SphereComponent->bGenerateOverlapEvents = true;
	SphereComponent->SetNotifyRigidBodyCollision(true);
}

// Called when the game starts or when spawned
void AFP_Weapon::BeginPlay()
{
	Super::BeginPlay();

	StaticMesh->SetStaticMesh(Mesh);
}

// Called every frame
void AFP_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	float fYaw = GetActorRotation().Yaw;
	FirePoint.X = 10.f * cosf((fYaw * PI) / 180.f);
	FirePoint.Y = 10.f * sinf((fYaw * PI) / 180.f);
	
	//SphereRadius
	AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (nullptr == pPlayer)
		return;
	
	SphereComponent->SetSphereRadius(pPlayer->GetStatus().AttackRange);

	if(TargetMonsters.Num() >= 1)
	{
		TargetMonsters.Sort(CompareDist(FirePoint));

		FVector TargetEnemy = TargetMonsters[0]->GetActorLocation();
		//DrawDebugLine(GetWorld(), FVector(0.f, 0.f, 0.f), TargetEnemy, FColor::Red);

		TargetEnemy.Normalize();

		float fCos = FVector::DotProduct(TargetEnemy, FVector(1.f, 0.f, 0.f));
		float AngleZ = acosf(fCos);
		if(TargetEnemy.Y < 0)
			AngleZ = 2 * PI - acosf(fCos);

		SetActorRotation(FRotator(0.f, AngleZ * 180.f / PI, 0.f));

		//attack
		TimeAcc += DeltaTime;
		if (TimeAcc > pPlayer->GetStatus().AttackSpeed)
		{
			TimeAcc = 0.f;
			AFP_Bullet* Bullet = GetWorld()->SpawnActor<AFP_Bullet>(FirePoint, FRotator(0.f, AngleZ * 180.f / PI, 0.f));
			Bullet->SetTargetDir(TargetEnemy);
		}
	}
		

	//FString Test = FString::SanitizeFloat(FirePoint.X);
	//Test += FString(TEXT(" , "));
	//Test += FString::SanitizeFloat(FirePoint.Y);

	FString Test = FString::FromInt(TargetMonsters.Num());
	GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Blue, Test);
	

}

void AFP_Weapon::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AFP_Monster* TargetMonster = Cast<AFP_Monster>(OtherActor);
	if (TargetMonster != NULL)
		TargetMonsters.Add(TargetMonster);
}


void AFP_Weapon::DeleteTargetMonsterInArray(AFP_Monster* _monster)
{
	TargetMonsters.Remove(_monster);
	
	//APlayerController* PController = GetWorld()->GetFirstPlayerController();
	//TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
	//FDamageEvent DamageEvent(ValidDamageTypeClass);

	//_monster->TakeDamage(Damage, DamageEvent, PController, this);

	//if (_monster->isDestroy)
	//{
	//	Cast<AFP_HUD>(GetWorld()->GetFirstPlayerController()->GetHUD())->IncreaseKillCount();
	//	TargetMonsters.Remove(_monster);
	//	_monster->Destroy();
	//}
}