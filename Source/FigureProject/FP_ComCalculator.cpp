// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_ComCalculator.h"
#include "FP_Player.h"
#include "FP_Skill.h"
#include "FP_Tooltip.h"

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

template<typename T>
float AFP_ComCalculator::CalculateFinalDamage(AFP_Player* _player, T* _skill, AFP_Monster* _monster, AFP_Monster::MSTATE _additionalDmgOn)
{
	float RuneDmg = 0.f;

	if (_skill->Sockets.Num() != 0)
	{
		for (int i = 0; i < _skill->Sockets.Num(); ++i)
		{
			if (!_skill->Sockets[i].Rune->IsValidLowLevel())
			{
				RuneDmg = 1.f;
				break;
			}

			RuneDmg += (_skill->Sockets[i].Rune->Stat.Damage - 1.f);

			for (int j = 0; j < _skill->Sockets[i].Rune->Option.Num(); ++j)
			{
				if (_skill->Sockets[i].Rune->Option[j].Contains("Ignite") && _monster->StateMgr.eState != AFP_Monster::IGNITE)
				{
					_monster->StateMgr.Damage += _skill->Sockets[i].Rune->OptionVal[j];
					_monster->StateMgr.eState = AFP_Monster::IGNITE;
				}
			}
		}
		RuneDmg += 1.f;
	}
	else
		RuneDmg = 1.f;

	if (_skill->Debuff == AFP_Monster::IGNITE && _monster->StateMgr.eState != AFP_Monster::IGNITE)
	{
		_monster->StateMgr.eState = AFP_Monster::IGNITE;
		_monster->StateMgr.Damage += _skill->DebuffDamage;
		_monster->StateMgr.Duration = _skill->DebuffDuration;
	}

	switch (_monster->StateMgr.eState)
	{
	case AFP_Monster::IGNITE:
		break;

	case AFP_Monster::SLOW:
		break;
	}

	if (RuneDmg == 0)
		RuneDmg = 1.f;
	//UE_LOG(LogClass, Error, TEXT("damage %f"), RuneDmg);
	//UE_LOG(LogClass, Error, TEXT("damage %f"), _player->Status.Attack * _skill->Stat.Damage * RuneDmg);
	return _player->Status.Attack * _skill->Stat.Damage * RuneDmg;
}

template<typename T>
float AFP_ComCalculator::CalculateFinalRange(AFP_Player* _player, T* _skill)
{
	float RuneRange = 0.f;

	if (_skill->Sockets.Num() != 0)
	{
		for (int i = 0; i < _skill->Sockets.Num(); ++i)
		{
			if (!_skill->Sockets[i].Rune->IsValidLowLevel())
			{
				RuneRange = 1.f;
				break;
			}

			RuneRange += (_skill->Sockets[i].Rune->Stat.Range - 1.f);
		}
		RuneRange += 1.f;
	}
	else
		RuneRange = 1.f;

	if (RuneRange == 0)
		RuneRange = 1.f;
	//UE_LOG(LogClass, Log, TEXT("range %f"), RuneRange);
	//UE_LOG(LogClass, Log, TEXT("range %f"), _player->Status.AttackRange * _skill->Stat.Range * RuneRange);
	return _player->Status.AttackRange * _skill->Stat.Range * RuneRange;
}

template<typename T>
float AFP_ComCalculator::CalculateFinalSpeed(AFP_Player* _player, T* _skill, float _deltaTime)
{
	float RuneSpeed = 0.f;

	if (_skill->Sockets.Num() != 0)
	{
		for (int i = 0; i < _skill->Sockets.Num(); ++i)
		{
			if (!_skill->Sockets[i].Rune->IsValidLowLevel())
			{
				RuneSpeed = 1.f;
				break;
			}

			RuneSpeed += (_skill->Sockets[i].Rune->Stat.Speed - 1.f);
		}
		RuneSpeed += 1.f;
	}
	else
		RuneSpeed = 1.f;

	if (RuneSpeed == 0)
		RuneSpeed = 1.f;
	//UE_LOG(LogClass, Log, TEXT("bullet speed %f"), RuneSpeed);
	//UE_LOG(LogClass, Log, TEXT("bullet speed %f"), _player->Status.BulletSpeed * _skill->Stat.Speed + RuneSpeed * _deltaTime);
	return _player->Status.BulletSpeed * _skill->Stat.Speed * RuneSpeed * _deltaTime;
}

template<typename T>
float AFP_ComCalculator::CalculateFinalCoolTime(AFP_Player* _player, T* _skill)
{
	float RuneCoolTime = 0.f;

	if (_skill->Sockets.Num() != 0)
	{
		for (int i = 0; i < _skill->Sockets.Num(); ++i)
		{
			if (!_skill->Sockets[i].Rune->IsValidLowLevel())
			{
				RuneCoolTime = 1.f;
				break;
			}

			RuneCoolTime += (_skill->Sockets[i].Rune->Stat.CoolTimeRatio - 1.f);
		}
		RuneCoolTime += 1.f;
	}
	else
		RuneCoolTime = 1.f;

	if (RuneCoolTime == 0)
		RuneCoolTime = 1.f;
	//UE_LOG(LogClass, Log, TEXT("att speed %f"), RuneCoolTime);
	//UE_LOG(LogClass, Log, TEXT("att speed %f"), _player->Status.AttackSpeed * _skill->Stat.CoolTimeRatio + RuneCoolTime);
	return _player->Status.AttackSpeed * _skill->Stat.CoolTimeRatio / RuneCoolTime;
}