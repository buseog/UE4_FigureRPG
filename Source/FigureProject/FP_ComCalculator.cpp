// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_ComCalculator.h"
#include "FP_Player.h"
#include "FP_Skill.h"
#include "FP_Monster.h"

// Sets default values
AFP_ComCalculator::AFP_ComCalculator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFP_ComCalculator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFP_ComCalculator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AFP_ComCalculator::CalculateFinalDamage(AFP_Player* _player, AFP_Skill* _skill, AFP_Monster* _monster)
{
	float RuneDmg = 1.f;

	if (_skill->Sockets.Num() != 0)
	{
		for (int i = 0; i < _skill->Sockets.Num(); ++i)
			RuneDmg += _skill->Sockets[i].Rune->Stat.Damage;
	}
	else
		RuneDmg = 1.f;

	/*switch (_monster->StateMgr.eState)
	{
	}*/
	
	return _player->Status.Attack * _skill->Stat.Damage * RuneDmg;
}

float AFP_ComCalculator::CalculateFinalRange(AFP_Player* _player, AFP_Skill* _skill, AFP_Monster* _monster)
{
	float RuneRange = 1.f;

	if (_skill->Sockets.Num() != 0)
	{
		for (int i = 0; i < _skill->Sockets.Num(); ++i)
			RuneRange += _skill->Sockets[i].Rune->Stat.Range;
	}
	else
		RuneRange = 1.f;

	return _player->Status.AttackRange * _skill->Stat.Range + RuneRange;
}

float AFP_ComCalculator::CalculateFinalSpeed(AFP_Player* _player, AFP_Skill* _skill, AFP_Monster* _monster)
{
	float RuneSpeed = 1.f;

	if (_skill->Sockets.Num() != 0)
	{
		for (int i = 0; i < _skill->Sockets.Num(); ++i)
			RuneSpeed += _skill->Sockets[i].Rune->Stat.Speed;
	}
	else
		RuneSpeed = 1.f;

	return _player->Status.BulletSpeed * _skill->Stat.Speed + RuneSpeed;
}

float AFP_ComCalculator::CalculateFinalCoolTime(AFP_Player* _player, AFP_Skill* _skill, AFP_Monster* _monster)
{
	float RuneCoolTime = 1.f;

	if (_skill->Sockets.Num() != 0)
	{
		for (int i = 0; i < _skill->Sockets.Num(); ++i)
			RuneCoolTime += _skill->Sockets[i].Rune->Stat.CoolTimeRatio;
	}
	else
		RuneCoolTime = 1.f;

	return _player->Status.AttackSpeed * _skill->Stat.CoolTimeRatio + RuneCoolTime;
}