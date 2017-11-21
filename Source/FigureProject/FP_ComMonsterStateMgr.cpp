// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_ComMonsterStateMgr.h"


// Sets default values
AFP_ComMonsterStateMgr::AFP_ComMonsterStateMgr()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFP_ComMonsterStateMgr::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFP_ComMonsterStateMgr::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFP_ComMonsterStateMgr::StateControl(AFP_Skill* _skill, AFP_Monster* _monster)
{
	float igniteDamage = 0.f;
	float igniteDuration = 0.f;
	float slowDamage = 0.f;
	float slowDuration = 0.f;
	float frozenDuration = 0.f;
	float frozenProbability = 0.f;

	if (_monster->StateMgr.Num() == 0)
	{
		for (int i = 0; i < _skill->Sockets.Num(); ++i)
		{
			if (_skill->Sockets[i].Rune == nullptr || _skill->Sockets[i].Rune->IsValidLowLevel() == false)
				continue;

			igniteDuration = FMath::Max<float>(igniteDuration, _skill->Sockets[i].Rune->Ignite.Duration);
			slowDuration = FMath::Max<float>(slowDuration, _skill->Sockets[i].Rune->Slow.Duration);
			frozenDuration = FMath::Max<float>(slowDuration, _skill->Sockets[i].Rune->Frozen.Duration);

			if (_skill->Sockets[i].Rune->Ignite.Duration != 0)
				igniteDamage += _skill->Sockets[i].Rune->Ignite.Damage;
			else if (_skill->Sockets[i].Rune->Slow.Duration != 0)
				slowDamage += _skill->Sockets[i].Rune->Slow.Damage;
		
		}

		if (_skill->Debuff == AFP_Monster::IGNITE)
		{
			igniteDamage += _skill->DebuffDamage;
			igniteDuration = FMath::Max<float>(igniteDuration, _skill->DebuffDuration);
		}
			
		if (_skill->Debuff == AFP_Monster::SLOW)
			slowDuration = _skill->DebuffDuration;
		if (_skill->Debuff == AFP_Monster::FROZEN)
		{
			frozenDuration = _skill->DebuffDuration;
			frozenProbability = _skill->DebuffProbability;
		}


		if (igniteDuration != 0 && !_skill->SkillInfo.Name.Contains("Ice"))
		{
			AFP_Monster::MonsterState state;
			state.Damage = igniteDamage;
			state.Duration = igniteDuration;
			state.eState = AFP_Monster::IGNITE;
			_monster->StateMgr.Add(state);
		}

		if (slowDuration != 0)
		{
			AFP_Monster::MonsterState state;

			state.Damage = slowDamage;
			state.Duration = slowDuration;
			state.eState = AFP_Monster::SLOW;
			_monster->StateMgr.Add(state);
		}

		if (frozenDuration != 0)
		{
			if (FMath::FRandRange(0.f, 100.f) <= frozenProbability)
			{
				AFP_Monster::MonsterState state;
				state.Duration = frozenDuration;
				state.eState = AFP_Monster::FROZEN;
				_monster->StateMgr.Add(state);
			}
		}
	}
	else
	{
		for (int i = 0; i < _skill->Sockets.Num(); ++i)
		{
			if (_skill->Sockets[i].Rune == nullptr || _skill->Sockets[i].Rune->IsValidLowLevel() == false)
				continue;

			igniteDuration = FMath::Max<float>(igniteDuration, _skill->Sockets[i].Rune->Ignite.Duration);
			slowDuration = FMath::Max<float>(slowDuration, _skill->Sockets[i].Rune->Slow.Duration);

			if (_skill->Sockets[i].Rune->Ignite.Duration != 0)
				igniteDamage += _skill->Sockets[i].Rune->Ignite.Damage;
			else if (_skill->Sockets[i].Rune->Slow.Duration != 0)
				slowDamage += _skill->Sockets[i].Rune->Slow.Damage;
		}
		if (_skill->Debuff == AFP_Monster::IGNITE)
			igniteDamage += _skill->DebuffDamage;



		if (igniteDuration != 0)
		{
			int isIgnite = 0;
			for (int j = 0; j < _monster->StateMgr.Num(); ++j)
			{
				if (_monster->StateMgr[j].eState == AFP_Monster::IGNITE)
				{
					_monster->StateMgr[j].Damage = igniteDamage;
					_monster->StateMgr[j].Duration = FMath::Max<float>(_monster->StateMgr[j].Duration, igniteDuration);
					++isIgnite;
				}
			}

			if (isIgnite == 0 && !_skill->SkillInfo.Name.Contains("Ice"))
			{
				AFP_Monster::MonsterState state;
				state.Damage = igniteDamage;
				state.Duration = igniteDuration;
				state.eState = AFP_Monster::IGNITE;
				_monster->StateMgr.Add(state);
			}

		}

		if (slowDuration != 0)
		{
			int isSlow = 0;
			for (int j = 0; j < _monster->StateMgr.Num(); ++j)
			{
				if (_monster->StateMgr[j].eState == AFP_Monster::SLOW)
				{
					_monster->StateMgr[j].Damage = slowDamage;
					_monster->StateMgr[j].Duration = FMath::Max<float>(_monster->StateMgr[j].Duration, slowDuration);
					++isSlow;
				}
			}

			if (isSlow == 0)
			{
				AFP_Monster::MonsterState state;
				state.Damage = slowDamage;
				state.Duration = slowDuration;
				state.eState = AFP_Monster::SLOW;
				_monster->StateMgr.Add(state);
			}
		}
	}
}
