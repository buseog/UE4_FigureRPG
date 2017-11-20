// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_Weapon.h"
#include "Engine.h"
#include "FP_Bullet.h"
#include "FP_Player.h"
#include "FP_Skill.h"
#include "FP_HUD.h"
#include "FP_FireBall.h"
#include "FP_IceBall.h"
#include "FP_IceBlast.h"
#include "FP_IceOrb.h"
#include "FP_FireBlastSpawnPoint.h"
#include "FP_FireBlast.h"
#include "FP_FireWall.h"
#include "FP_Tooltip.h"
#include "FP_PlayerController.h"
#include "FP_ComCalculator.h"
#include "FP_ComCollision.h"
#include "FP_Monster.h"

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
AFP_Weapon::SKILLTYPE AFP_Weapon::ActiveSkill = AFP_Weapon::FIREBALL;
AFP_Weapon::AFP_Weapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->InitSphereRadius(100.f);

	//SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AFP_Weapon::OnOverlapBegin);

	SetActorEnableCollision(true);
	//SphereComponent->bGenerateOverlapEvents = false;
	//SphereComponent->SetNotifyRigidBodyCollision(true);
}

// Called when the game starts or when spawned
void AFP_Weapon::BeginPlay()
{
	Super::BeginPlay();

	AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	TimeAcc = pPlayer->GetStatus().AttackSpeed;
}

// Called every frame
void AFP_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//SphereRadius
	AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (nullptr == pPlayer)
		return;

	//UE_LOG(LogClass, Log, TEXT("%d"), TargetMonsters.Num());

	SetAttSpdAndRange(pPlayer);

	TargetMonsters.Empty();
	AFP_ComCollision::CollisionWithMulti<USphereComponent, AFP_Monster>(SphereComponent, TargetMonsters);


	if(TargetMonsters.Num() >= 1)
	{
		TargetMonsters.Sort(CompareDist(FVector(0.f,0.f,0.f)));

		FVector TargetEnemy = TargetMonsters[0]->GetActorLocation();
		//DrawDebugLine(GetWorld(), FVector(0.f, 0.f, 0.f), TargetEnemy, FColor::Red);

		TargetEnemy.Normalize();

		float fCos = FVector::DotProduct(TargetEnemy, FVector(1.f, 0.f, 0.f));
		AngleZ = acosf(fCos);
		if(TargetEnemy.Y < 0)
			AngleZ = 2 * PI - acosf(fCos);

		SetActorRotation(FRotator(0.f, AngleZ * 180.f / PI, 0.f));

		float fYaw = GetActorRotation().Yaw;
		FirePoint.X = 12.f * cosf((fYaw * PI) / 180.f);
		FirePoint.Y = 12.f * sinf((fYaw * PI) / 180.f);

		//attack
		TimeAcc += DeltaTime;
			
		if (TimeAcc > ReloadTime)
		{
			TimeAcc = 0.f;
			SpawnSkill();
		}
	}
		
	//FString Test = FString::FromInt(TargetMonsters.Num());
	//GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Blue, Test);
	
}

void AFP_Weapon::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AFP_Monster* TargetMonster = Cast<AFP_Monster>(OtherActor);
	if (TargetMonster != NULL && TargetMonster->isTargeting == false && TargetMonsters.Num() <= 10)
	{
		TargetMonster->isTargeting = true;
		TargetMonsters.Add(TargetMonster);
	}
		
}


void AFP_Weapon::DeleteTargetMonsterInArray(AFP_Monster* _monster)
{
	TargetMonsters.Remove(_monster);

}

void AFP_Weapon::SpawnSkill()
{
	AFP_Player* player = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (player == nullptr)
		return;

	switch (ActiveSkill)
	{
	case FIREBALL:
		Skill = CustomSpawn<AFP_FireBall>(FirePoint, FRotator(0.f, AngleZ * 180.f / PI, 0.f));
		Skill->SetTargetDirection(TargetMonsters[0]->GetActorLocation());
		SphereComponent->SetSphereRadius(AFP_ComCalculator::CalculateFinalRange(player, Skill));
		ReloadTime = AFP_ComCalculator::CalculateFinalCoolTime(player, Skill);

		break;
	case FIREBLAST:
		Skill = CustomSpawn<AFP_FireBlast>(TargetMonsters[0]->GetActorLocation(), FRotator(0.f, AngleZ * 180.f / PI, 0.f));
		Skill->SetTargetDirection(TargetMonsters[0]->GetActorLocation());
		SphereComponent->SetSphereRadius(AFP_ComCalculator::CalculateFinalRange(player, Skill));
		ReloadTime = AFP_ComCalculator::CalculateFinalCoolTime(player, Skill);
		break;
	case FIREWALL:
		Skill = CustomSpawn<AFP_FireBlastSpawnPoint>(FirePoint, FRotator(0.f, AngleZ * 180.f / PI, 0.f));
		Skill->SetTargetDirection(TargetMonsters[0]->GetActorLocation());
		Cast<AFP_FireBlastSpawnPoint>(Skill)->SetSkill("FireWall", 0.1f, 7 , 0.75f);
		SphereComponent->SetSphereRadius(AFP_ComCalculator::CalculateFinalRange(player, Skill));
		ReloadTime = AFP_ComCalculator::CalculateFinalCoolTime(player, Skill);
		break;
	case ICEBALL:
		Skill = CustomSpawn<AFP_IceBall>(FirePoint, FRotator(0.f, AngleZ * 180.f / PI, 0.f));
		Skill->SetTargetDirection(TargetMonsters[0]->GetActorLocation());
		SphereComponent->SetSphereRadius(AFP_ComCalculator::CalculateFinalRange(player, Skill));
		ReloadTime = AFP_ComCalculator::CalculateFinalCoolTime(player, Skill);
		break;
	case ICEBLAST:
		Skill = CustomSpawn<AFP_IceBlast>(FirePoint, FRotator(0.f, AngleZ * 180.f / PI, 0.f));
		SphereComponent->SetSphereRadius(AFP_ComCalculator::CalculateFinalRange(player, Skill));
		ReloadTime = AFP_ComCalculator::CalculateFinalCoolTime(player, Skill);
		break;
	case ICEORB:
		Skill = CustomSpawn<AFP_IceOrb>(FirePoint, FRotator(0.f, AngleZ * 180.f / PI, 0.f));
		Skill->SetTargetDirection(TargetMonsters[0]->GetActorLocation());
		SphereComponent->SetSphereRadius(AFP_ComCalculator::CalculateFinalRange(player, Skill));
		ReloadTime = AFP_ComCalculator::CalculateFinalCoolTime(player, Skill);
		break;
	}	
}

float AFP_Weapon::GetStatfromSkill(FString _stat)
{
	UClass* SkillClass = nullptr;
	AFP_Skill* Skill = nullptr;
	switch (ActiveSkill)
	{
	case FIREBALL:
		SkillClass = AFP_FireBall::StaticClass();
		Skill = SkillClass->GetDefaultObject<AFP_FireBall>();

		if (_stat == "Damage")
			return Skill->Stat.Damage;
		else if (_stat == "Range")
			return Skill->Stat.Range;
		else if (_stat == "Speed")
			return Skill->Stat.Speed;
		else if (_stat == "AttackSpeed")
			return Skill->Stat.CoolTimeRatio;

	case FIREBLAST:
		SkillClass = AFP_FireBlast::StaticClass();
		Skill = SkillClass->GetDefaultObject<AFP_FireBlast>();
		
		if (_stat == "Damage")
			return Skill->Stat.Damage;
		else if (_stat == "Range")
			return Skill->Stat.Range;
		else if (_stat == "Speed")
			return Skill->Stat.Speed;
		else if (_stat == "AttackSpeed")
			return Skill->Stat.CoolTimeRatio;

	case FIREWALL:
		SkillClass = AFP_FireWall::StaticClass();
		Skill = SkillClass->GetDefaultObject<AFP_FireWall>();
		
		if (_stat == "Damage")
			return Skill->Stat.Damage;
		else if (_stat == "Range")
			return Skill->Stat.Range;
		else if (_stat == "Speed")
			return Skill->Stat.Speed;
		else if (_stat == "AttackSpeed")
			return Skill->Stat.CoolTimeRatio;

	case ICEBALL:
		SkillClass = AFP_IceBall::StaticClass();
		Skill = SkillClass->GetDefaultObject<AFP_IceBall>();
		
		if (_stat == "Damage")
			return Skill->Stat.Damage;
		else if (_stat == "Range")
			return Skill->Stat.Range;
		else if (_stat == "Speed")
			return Skill->Stat.Speed;
		else if (_stat == "AttackSpeed")
			return Skill->Stat.CoolTimeRatio;

	case ICEBLAST:
		SkillClass = AFP_IceBlast::StaticClass();
		Skill = SkillClass->GetDefaultObject<AFP_IceBlast>();
	
		if (_stat == "Damage")
			return Skill->Stat.Damage;
		else if (_stat == "Range")
			return Skill->Stat.Range;
		else if (_stat == "Speed")
			return Skill->Stat.Speed;
		else if (_stat == "AttackSpeed")
			return Skill->Stat.CoolTimeRatio;

	case ICEORB:
		SkillClass = AFP_IceOrb::StaticClass();
		Skill = SkillClass->GetDefaultObject<AFP_IceOrb>();
		
		if (_stat == "Damage")
			return Skill->Stat.Damage;
		else if (_stat == "Range")
			return Skill->Stat.Range;
		else if (_stat == "Speed")
			return Skill->Stat.Speed;
		else if (_stat == "AttackSpeed")
			return Skill->Stat.CoolTimeRatio;

	}
	return 0.f;
}

void AFP_Weapon::SetAttSpdAndRange(AFP_Player* _player)
{
	SphereComponent->SetSphereRadius(_player->GetStatus().AttackRange * GetStatfromSkill("Range"));

	if (ActiveSkill == FIREBALL)
	{
		UClass* Class = AFP_FireBall::StaticClass();
		AFP_FireBall* skill = Cast<AFP_FireBall>(Class->GetDefaultObject());

		SphereComponent->SetSphereRadius(AFP_ComCalculator::CalculateFinalRange(_player, skill));
		ReloadTime = AFP_ComCalculator::CalculateFinalCoolTime(_player, skill);
	}
	else if (ActiveSkill == FIREBLAST)
	{
		UClass* Class = AFP_FireBlast::StaticClass();
		AFP_FireBlast* skill = Cast<AFP_FireBlast>(Class->GetDefaultObject());

		SphereComponent->SetSphereRadius(AFP_ComCalculator::CalculateFinalRange(_player, skill));
		ReloadTime = AFP_ComCalculator::CalculateFinalCoolTime(_player, skill);
	}
	else if (ActiveSkill == FIREWALL)
	{
		UClass* Class = AFP_FireWall::StaticClass();
		AFP_FireWall* skill = Cast<AFP_FireWall>(Class->GetDefaultObject());

		SphereComponent->SetSphereRadius(AFP_ComCalculator::CalculateFinalRange(_player, skill));
		ReloadTime = AFP_ComCalculator::CalculateFinalCoolTime(_player, skill);
	}
	else if (ActiveSkill == ICEBALL)
	{
		UClass* Class = AFP_IceBall::StaticClass();
		AFP_IceBall* skill = Cast<AFP_IceBall>(Class->GetDefaultObject());

		SphereComponent->SetSphereRadius(AFP_ComCalculator::CalculateFinalRange(_player, skill));
		ReloadTime = AFP_ComCalculator::CalculateFinalCoolTime(_player, skill);
	}
	else if (ActiveSkill == ICEBLAST)
	{
		UClass* Class = AFP_IceBlast::StaticClass();
		AFP_IceBlast* skill = Cast<AFP_IceBlast>(Class->GetDefaultObject());

		SphereComponent->SetSphereRadius(AFP_ComCalculator::CalculateFinalRange(_player, skill));
		ReloadTime = AFP_ComCalculator::CalculateFinalCoolTime(_player, skill);
	}
	else if (ActiveSkill == ICEORB)
	{
		UClass* Class = AFP_IceOrb::StaticClass();
		AFP_IceOrb* skill = Cast<AFP_IceOrb>(Class->GetDefaultObject());

		SphereComponent->SetSphereRadius(AFP_ComCalculator::CalculateFinalRange(_player, skill));
		ReloadTime = AFP_ComCalculator::CalculateFinalCoolTime(_player, skill);
	}
}