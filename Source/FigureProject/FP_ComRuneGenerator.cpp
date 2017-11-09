// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_ComRuneGenerator.h"
#include "FP_RuneTable.h"
#include "FP_Monster.h"


// Sets default values
AFP_ComRuneGenerator::AFP_ComRuneGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TMap<uint64, FString> prop_name;
	TMap<FString, TMap<uint64, FString>> option;
	TMap<FString, float> stat;
	TMap<FString, TMap<FString, float>> _option;
	
	//RED
	prop_name.Add(Red.RANDOMEFFECT, Red.NAME_RANDOMEFFECT);
	RuneOption.Add(Red.RANDOMEFFECT, Red.NAME_RANDOMEFFECT);
	option.Add("RANDOMEFFECT", prop_name);
	prop_name.Empty();

	prop_name.Add(Red.STUN, Red.NAME_STUN);
	RuneOption.Add(Red.STUN, Red.NAME_STUN);
	option.Add("STUN", prop_name);
	prop_name.Empty();

	prop_name.Add(Red.KNOCKBACK, Red.NAME_KNOCKBACK);
	RuneOption.Add(Red.KNOCKBACK, Red.NAME_KNOCKBACK);
	option.Add("KNOCKBACK", prop_name);
	prop_name.Empty();

	prop_name.Add(Red.LIFESTEAL, Red.NAME_LIFESTEAL);
	RuneOption.Add(Red.LIFESTEAL, Red.NAME_LIFESTEAL);
	option.Add("LIFESTEAL", prop_name);
	prop_name.Empty();

	prop_name.Add(Red.IGNITE, Red.NAME_IGNITE);
	RuneOption.Add(Red.IGNITE, Red.NAME_IGNITE);
	option.Add("IGNITE", prop_name);
	prop_name.Empty();

	RuneProperty.Add(FColor::Red, option);
	option.Empty();


	//GREEN
	prop_name.Add(Green.ATTACKSPEEDUP, Green.NAME_ATTACKSPEEDUP);
	RuneOption.Add(Green.ATTACKSPEEDUP, Green.NAME_ATTACKSPEEDUP);
	option.Add("ATTACKSPEEDUP", prop_name);
	prop_name.Empty();

	prop_name.Add(Green.BULLETSPEEDUP, Green.NAME_BULLETSPEEDUP);
	RuneOption.Add(Green.BULLETSPEEDUP, Green.NAME_BULLETSPEEDUP);
	option.Add("BULLETSPEEDUP", prop_name);
	prop_name.Empty();

	prop_name.Add(Green.DAMAGEUP, Green.NAME_DAMAGEUP);
	RuneOption.Add(Green.DAMAGEUP, Green.NAME_DAMAGEUP);
	option.Add("DAMAGEUP", prop_name);
	prop_name.Empty();

	prop_name.Add(Green.DAMAGEUPTOSQARE, Green.NAME_DAMAGEUPTOSQARE);
	RuneOption.Add(Green.DAMAGEUPTOSQARE, Green.NAME_DAMAGEUPTOSQARE);
	option.Add("DAMAGEUPTOSQARE", prop_name);
	prop_name.Empty();

	RuneProperty.Add(FColor::Green, option);
	option.Empty();


	//BLUE
	prop_name.Add(Blue.RANGEUP, Blue.NAME_RANGEUP);
	RuneOption.Add(Blue.RANGEUP, Blue.NAME_RANGEUP);
	option.Add("RANGEUP", prop_name);
	prop_name.Empty();

	prop_name.Add(Blue.EXPUP, Blue.NAME_EXPUP);
	RuneOption.Add(Blue.EXPUP, Blue.NAME_EXPUP);
	option.Add("EXPUP", prop_name);
	prop_name.Empty();

	prop_name.Add(Blue.GUIDED, Blue.NAME_GUIDED);
	RuneOption.Add(Blue.GUIDED, Blue.NAME_GUIDED);
	option.Add("GUIDED", prop_name);
	prop_name.Empty();

	prop_name.Add(Blue.AREAUP, Blue.NAME_AREAUP);
	RuneOption.Add(Blue.AREAUP, Blue.NAME_AREAUP);
	option.Add("AREAUP", prop_name);
	prop_name.Empty();

	RuneProperty.Add(FColor::Blue, option);
	option.Empty();


	//RuneStatRange Tier1
	stat.Add("MIN", RuneStatRange.Tier1.RANDOMEFFECT_MIN);
	stat.Add("MAX", RuneStatRange.Tier1.RANDOMEFFECT_MAX);
	_option.Add("RANDOMEFFECT", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier1.STUN_MIN);
	stat.Add("MAX", RuneStatRange.Tier1.STUN_MAX);
	_option.Add("STUN", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier1.LIFESTEAL_MIN);
	stat.Add("MAX", RuneStatRange.Tier1.LIFESTEAL_MAX);
	_option.Add("LIFESTEAL", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier1.IGNITE_MIN);
	stat.Add("MAX", RuneStatRange.Tier1.IGNITE_MAX);
	_option.Add("IGNITE", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier1.AREAUP_MIN);
	stat.Add("MAX", RuneStatRange.Tier1.AREAUP_MAX);
	_option.Add("AREAUP", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier1.ATTACKSPEEDUP_MIN);
	stat.Add("MAX", RuneStatRange.Tier1.ATTACKSPEEDUP_MAX);
	_option.Add("ATTACKSPEEDUP", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier1.BULLETSPEEDUP_MIN);
	stat.Add("MAX", RuneStatRange.Tier1.BULLETSPEEDUP_MAX);
	_option.Add("BULLETSPEEDUP", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier1.DAMAGEUP_MIN);
	stat.Add("MAX", RuneStatRange.Tier1.DAMAGEUP_MAX);
	_option.Add("DAMAGEUP", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier1.DAMAGEUPTOSQARE_MIN);
	stat.Add("MAX", RuneStatRange.Tier1.DAMAGEUPTOSQARE_MAX);
	_option.Add("DAMAGEUPTOSQARE", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier1.RANGEUP_MIN);
	stat.Add("MAX", RuneStatRange.Tier1.RANGEUP_MAX);
	_option.Add("RANGEUP", stat);
	stat.Empty();

	RuneStat.Add(1, _option);
	_option.Empty();

	//RuneStatRange Tier2
	stat.Add("MIN", RuneStatRange.Tier2.RANDOMEFFECT_MIN);
	stat.Add("MAX", RuneStatRange.Tier2.RANDOMEFFECT_MAX);
	_option.Add("RANDOMEFFECT", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier2.STUN_MIN);
	stat.Add("MAX", RuneStatRange.Tier2.STUN_MAX);
	_option.Add("STUN", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier2.LIFESTEAL_MIN);
	stat.Add("MAX", RuneStatRange.Tier2.LIFESTEAL_MAX);
	_option.Add("LIFESTEAL", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier2.IGNITE_MIN);
	stat.Add("MAX", RuneStatRange.Tier2.IGNITE_MAX);
	_option.Add("IGNITE", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier2.AREAUP_MIN);
	stat.Add("MAX", RuneStatRange.Tier2.AREAUP_MAX);
	_option.Add("AREAUP", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier2.ATTACKSPEEDUP_MIN);
	stat.Add("MAX", RuneStatRange.Tier2.ATTACKSPEEDUP_MAX);
	_option.Add("ATTACKSPEEDUP", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier2.BULLETSPEEDUP_MIN);
	stat.Add("MAX", RuneStatRange.Tier2.BULLETSPEEDUP_MAX);
	_option.Add("BULLETSPEEDUP", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier2.DAMAGEUP_MIN);
	stat.Add("MAX", RuneStatRange.Tier2.DAMAGEUP_MAX);
	_option.Add("DAMAGEUP", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier2.DAMAGEUPTOSQARE_MIN);
	stat.Add("MAX", RuneStatRange.Tier2.DAMAGEUPTOSQARE_MAX);
	_option.Add("DAMAGEUPTOSQARE", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier2.RANGEUP_MIN);
	stat.Add("MAX", RuneStatRange.Tier2.RANGEUP_MAX);
	_option.Add("RANGEUP", stat);
	stat.Empty();

	RuneStat.Add(2, _option);
	_option.Empty();

	//RuneStatRange Tier3
	stat.Add("MIN", RuneStatRange.Tier3.RANDOMEFFECT_MIN);
	stat.Add("MAX", RuneStatRange.Tier3.RANDOMEFFECT_MAX);
	_option.Add("RANDOMEFFECT", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier3.STUN_MIN);
	stat.Add("MAX", RuneStatRange.Tier3.STUN_MAX);
	_option.Add("STUN", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier3.LIFESTEAL_MIN);
	stat.Add("MAX", RuneStatRange.Tier3.LIFESTEAL_MAX);
	_option.Add("LIFESTEAL", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier3.IGNITE_MIN);
	stat.Add("MAX", RuneStatRange.Tier3.IGNITE_MAX);
	_option.Add("IGNITE", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier3.AREAUP_MIN);
	stat.Add("MAX", RuneStatRange.Tier3.AREAUP_MAX);
	_option.Add("AREAUP", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier3.ATTACKSPEEDUP_MIN);
	stat.Add("MAX", RuneStatRange.Tier3.ATTACKSPEEDUP_MAX);
	_option.Add("ATTACKSPEEDUP", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier3.BULLETSPEEDUP_MIN);
	stat.Add("MAX", RuneStatRange.Tier3.BULLETSPEEDUP_MAX);
	_option.Add("BULLETSPEEDUP", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier3.DAMAGEUP_MIN);
	stat.Add("MAX", RuneStatRange.Tier3.DAMAGEUP_MAX);
	_option.Add("DAMAGEUP", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier3.DAMAGEUPTOSQARE_MIN);
	stat.Add("MAX", RuneStatRange.Tier3.DAMAGEUPTOSQARE_MAX);
	_option.Add("DAMAGEUPTOSQARE", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier3.RANGEUP_MIN);
	stat.Add("MAX", RuneStatRange.Tier3.RANGEUP_MAX);
	_option.Add("RANGEUP", stat);
	stat.Empty();

	RuneStat.Add(3, _option);
	_option.Empty();
}

// Called when the game starts or when spawned
void AFP_ComRuneGenerator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFP_ComRuneGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AFP_Rune* AFP_ComRuneGenerator::GenerateRune(TMap<FColor, TMap<FString, TMap<uint64, FString>>> _runeProperty, TMap<uint64, FString> _runeOption, TMap<int, TMap<FString, TMap<FString, float>>> _runeStat, AFP_Rune* _rune, int _stage)
{
	//Tier
	_rune->Tier3DropRate = (float)_stage * _rune->Tier3DropRate;
	_rune->Tier2DropRate = (float)_stage * _rune->Tier2DropRate;

	if (_rune->Tier3DropRate >= _rune->Tier3MaxDropRate)
		_rune->Tier3DropRate = _rune->Tier3MaxDropRate;

	if (_rune->Tier2DropRate >= _rune->Tier2MaxDropRate)
		_rune->Tier2DropRate = _rune->Tier2MaxDropRate;

	float DropRate = FMath::FRandRange(0.f, 101.f);

	if (DropRate <= _rune->Tier3DropRate)
		_rune->Stat.Tier = 3;
	else if (DropRate <= _rune->Tier2DropRate)
		_rune->Stat.Tier = 2;
	else
		_rune->Stat.Tier = 1;


	//Color, Property, Name, Type
	int random = FMath::FRandRange(0, 3);
	int i = 0;
	uint64 hex = 0;

	switch (random)
	{
	case 0:
		_rune->Color = FColor::Red;
		for (i = 0; i < _rune->Stat.Tier; ++i)
		{
			while (1)
			{
				random = FMath::FRandRange(0, _runeProperty[FColor::Red].Num());
				hex = (uint64)pow(16, random);

				if ((_rune->Property & hex) == 0 || random == _runeProperty[FColor::Red].Num())
					break;
			}

			_rune->Name += _runeOption[hex].Left(_runeOption[hex].Find(TEXT(":"))) + " ";
			_rune->Option.Add(_runeOption[hex].Left(_runeOption[hex].Find(TEXT(":"))));
			_rune->Property = _rune->Property | hex;

			if (_runeOption[hex].Contains("STAT"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::STAT);

			if (_runeOption[hex].Contains("PROBABILITY"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::PROBABILITY);

			if (_runeOption[hex].Contains("FIXED"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::FIXED);

			if (_runeOption[hex].Contains("PROJECTILE"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::PROJECTILE);

			if (_runeOption[hex].Contains("AOE"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::AOE);

			if (_runeOption[hex].Contains("DOT"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::DOT);

			if (_runeOption[hex].Contains("EXP"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::EXP);

			if (_runeOption[hex].Contains("ETC"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::ETC);
		}
		break;

	case 1:
		_rune->Color = FColor::Green;
		for (i = 0; i < _rune->Stat.Tier; ++i)
		{
			while (1)
			{
				random = FMath::FRandRange(0, _runeProperty[FColor::Green].Num());
				hex = (uint64)pow(16, random);

				if ((_rune->Property & hex) == 0 || random == _runeProperty[FColor::Green].Num())
					break;
			}

			_rune->Name += _runeOption[hex].Left(_runeOption[hex].Find(TEXT(":"))) + " ";
			_rune->Option.Add(_runeOption[hex].Left(_runeOption[hex].Find(TEXT(":"))));
			_rune->Property = _rune->Property | hex;

			if (_runeOption[hex].Contains("STAT"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::STAT);

			if (_runeOption[hex].Contains("PROBABILITY"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::PROBABILITY);

			if (_runeOption[hex].Contains("FIXED"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::FIXED);

			if (_runeOption[hex].Contains("PROJECTILE"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::PROJECTILE);

			if (_runeOption[hex].Contains("AOE"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::AOE);

			if (_runeOption[hex].Contains("DOT"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::DOT);

			if (_runeOption[hex].Contains("EXP"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::EXP);

			if (_runeOption[hex].Contains("ETC"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::ETC);
		}
		break;

	case 2:
		_rune->Color = FColor::Blue;
		for (i = 0; i < _rune->Stat.Tier; ++i)
		{
			while (1)
			{
				random = FMath::FRandRange(0, _runeProperty[FColor::Blue].Num());
				hex = (uint64)pow(16, random);

				if ((_rune->Property & hex) == 0 || random == _runeProperty[FColor::Blue].Num())
					break;
			}

			_rune->Name += _runeOption[hex].Left(_runeOption[hex].Find(TEXT(":"))) + " ";
			_rune->Option.Add(_runeOption[hex].Left(_runeOption[hex].Find(TEXT(":"))));
			_rune->Property = _rune->Property | hex;

			if (_runeOption[hex].Contains("STAT"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::STAT);

			if (_runeOption[hex].Contains("PROBABILITY"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::PROBABILITY);

			if (_runeOption[hex].Contains("FIXED"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::FIXED);

			if (_runeOption[hex].Contains("PROJECTILE"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::PROJECTILE);

			if (_runeOption[hex].Contains("AOE"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::AOE);

			if (_runeOption[hex].Contains("DOT"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::DOT);

			if (_runeOption[hex].Contains("EXP"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::EXP);

			if (_runeOption[hex].Contains("ETC"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::ETC);
		}
		break;
	}

	//icon
	if (_rune->Color == FColor::Red)
	{
		if (_rune->Stat.Tier == 1)
			_rune->Icon = _rune->RedTier1Icon;
		else if (_rune->Stat.Tier == 2)
			_rune->Icon = _rune->RedTier2Icon;
		else if (_rune->Stat.Tier == 3)
			_rune->Icon = _rune->RedTier3Icon;
		else
			_rune->Icon = _rune->RedTier4Icon;
	}
	else if (_rune->Color == FColor::Green)
	{
		if (_rune->Stat.Tier == 1)
			_rune->Icon = _rune->GreenTier1Icon;
		else if (_rune->Stat.Tier == 2)
			_rune->Icon = _rune->GreenTier2Icon;
		else if (_rune->Stat.Tier == 3)
			_rune->Icon = _rune->GreenTier3Icon;
		else
			_rune->Icon = _rune->GreenTier4Icon;
	}
	else
	{
		if (_rune->Stat.Tier == 1)
			_rune->Icon = _rune->BlueTier1Icon;
		else if (_rune->Stat.Tier == 2)
			_rune->Icon = _rune->BlueTier2Icon;
		else if (_rune->Stat.Tier == 3)
			_rune->Icon = _rune->BlueTier3Icon;
		else
			_rune->Icon = _rune->BlueTier4Icon;
	}


	//Stat
	for (i = 0; i < _rune->Stat.Type.Num(); ++i)
	{
		if (_rune->Stat.Type[i] == AFP_Rune::TYPE::STAT)
		{
			for (int j = 0; j < _rune->Option.Num(); ++j)
			{
				if (_rune->Option[j].Contains("DAMAGE") && !_rune->Option[j].Contains("TO"))
				{
					_rune->Stat.Damage = FMath::RandRange(_runeStat[_rune->Stat.Tier]["DAMAGEUP"]["MIN"], _runeStat[_rune->Stat.Tier]["DAMAGEUP"]["MAX"]);
					_rune->OptionVal[j] = _rune->Stat.Damage;
				}
				else if (_rune->Option[j].Contains("RANGE"))
				{
					_rune->Stat.Range = FMath::RandRange(_runeStat[_rune->Stat.Tier]["RANGEUP"]["MIN"], _runeStat[_rune->Stat.Tier]["RANGEUP"]["MAX"]);
					_rune->OptionVal[j] = _rune->Stat.Range;
				}
				else if (_rune->Option[j].Contains("ATTACKSPEED"))
				{
					_rune->Stat.CoolTimeRatio = FMath::RandRange(_runeStat[_rune->Stat.Tier]["ATTACKSPEEDUP"]["MIN"], _runeStat[_rune->Stat.Tier]["ATTACKSPEEDUP"]["MAX"]);
					_rune->OptionVal[j] = _rune->Stat.CoolTimeRatio;
				}
				else if (_rune->Option[j].Contains("BULLETSPEED"))
				{
					_rune->Stat.Speed = FMath::RandRange(_runeStat[_rune->Stat.Tier]["BULLETSPEEDUP"]["MIN"], _runeStat[_rune->Stat.Tier]["BULLETSPEEDUP"]["MAX"]);
					_rune->OptionVal[j] = _rune->Stat.Speed;
				}
			}
		}

		if (_rune->Stat.Type[i] == AFP_Rune::TYPE::PROBABILITY)
		{

		}

		if (_rune->Stat.Type[i] == AFP_Rune::TYPE::FIXED)
		{

		}

		if (_rune->Stat.Type[i] == AFP_Rune::TYPE::PROJECTILE)
		{

		}

		if (_rune->Stat.Type[i] == AFP_Rune::TYPE::AOE)
		{

		}

		if (_rune->Stat.Type[i] == AFP_Rune::TYPE::DOT)
		{

		}

		if (_rune->Stat.Type[i] == AFP_Rune::TYPE::EXP)
		{

		}

		if (_rune->Stat.Type[i] == AFP_Rune::TYPE::ETC)
		{

		}
	}

	//UE_LOG(LogClass, Log, TEXT("========================================================"));
	//UE_LOG(LogClass, Log, TEXT("Tier : %d"), _rune->Stat.Tier);
	//UE_LOG(LogClass, Log, TEXT("Color : %f, %f, %f"), (float)_rune->Color.R, (float)_rune->Color.G, (float)_rune->Color.B);
	//UE_LOG(LogClass, Log, TEXT("%s"), *_rune->Icon->GetName());
	//UE_LOG(LogClass, Log, TEXT("Property : %x"), _rune->Property);
	//UE_LOG(LogClass, Log, TEXT("Name : %s"), *_rune->Name);

	return _rune;
}