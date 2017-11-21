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
	prop_name.Add(Red.DAMAGEUP, Red.NAME_DAMAGEUP);
	RedRuneOption.Add(Red.DAMAGEUP, Red.NAME_DAMAGEUP);
	option.Add("DAMAGE UP", prop_name);
	prop_name.Empty();

	prop_name.Add(Red.PIERCE, Red.NAME_PIERCE);
	RedRuneOption.Add(Red.PIERCE, Red.NAME_PIERCE);
	option.Add("PIERCE", prop_name);
	prop_name.Empty();

	prop_name.Add(Red.IGNITE, Red.NAME_IGNITE);
	RedRuneOption.Add(Red.IGNITE, Red.NAME_IGNITE);
	option.Add("IGNITE", prop_name);
	prop_name.Empty();

	/*prop_name.Add(Red.RANDOMEFFECT, Red.NAME_RANDOMEFFECT);
	RedRuneOption.Add(Red.RANDOMEFFECT, Red.NAME_RANDOMEFFECT);
	option.Add("RANDOMEFFECT", prop_name);
	prop_name.Empty();*/

	/*prop_name.Add(Red.LIFESTEAL, Red.NAME_LIFESTEAL);
	RedRuneOption.Add(Red.LIFESTEAL, Red.NAME_LIFESTEAL);
	option.Add("LIFESTEAL", prop_name);
	prop_name.Empty();*/

	/*prop_name.Add(Red.DAMAGEUPONIGNITE, Red.NAME_DAMAGEUPONIGNITE);
	RedRuneOption.Add(Red.DAMAGEUPONIGNITE, Red.NAME_DAMAGEUPONIGNITE);
	option.Add("DAMAGEUPONIGNITE", prop_name);
	prop_name.Empty();*/

	/*prop_name.Add(Red.DAMAGEUPTOCIRCLE, Red.NAME_DAMAGEUPTOCIRCLE);
	RedRuneOption.Add(Red.DAMAGEUPTOCIRCLE, Red.NAME_DAMAGEUPTOCIRCLE);
	option.Add("DAMAGEUPTOCIRCLE", prop_name);
	prop_name.Empty();*/

	RuneProperty.Add(FColor::Red, option);
	option.Empty();

	//GREEN
	prop_name.Add(Green.ATTACKSPEEDUP, Green.NAME_ATTACKSPEEDUP);
	GreenRuneOption.Add(Green.ATTACKSPEEDUP, Green.NAME_ATTACKSPEEDUP);
	option.Add("ATTACK SPEED UP", prop_name);
	prop_name.Empty();

	prop_name.Add(Green.BULLETSPEEDUP, Green.NAME_BULLETSPEEDUP);
	GreenRuneOption.Add(Green.BULLETSPEEDUP, Green.NAME_BULLETSPEEDUP);
	option.Add("BULLET SPEED UP", prop_name);
	prop_name.Empty();

	prop_name.Add(Green.STUN, Green.NAME_STUN);
	GreenRuneOption.Add(Green.STUN, Green.NAME_STUN);
	option.Add("STUN", prop_name);
	prop_name.Empty();

	/*prop_name.Add(Green.KNOCKBACK, Green.NAME_KNOCKBACK);
	GreenRuneOption.Add(Green.KNOCKBACK, Green.NAME_KNOCKBACK);
	option.Add("KNOCKBACK", prop_name);
	prop_name.Empty();*/

	/*prop_name.Add(Green.DAMAGEUPTOSQARE, Green.NAME_DAMAGEUPTOSQARE);
	GreenRuneOption.Add(Green.DAMAGEUPTOSQARE, Green.NAME_DAMAGEUPTOSQARE);
	option.Add("DAMAGEUPTOSQARE", prop_name);
	prop_name.Empty();*/

	/*prop_name.Add(Green.ATTACKTWICE, Green.NAME_ATTACKTWICE);
	GreenRuneOption.Add(Green.ATTACKTWICE, Green.NAME_ATTACKTWICE);
	option.Add("DAMAGEUPTOSQARE", prop_name);
	prop_name.Empty();*/

	/*prop_name.Add(Green.DOTDAMAGEUP, Green.NAME_DOTDAMAGEUP);
	GreenRuneOption.Add(Green.DOTDAMAGEUP, Green.NAME_DOTDAMAGEUP);
	option.Add("DOTDAMAGEUP", prop_name);
	prop_name.Empty();*/

	RuneProperty.Add(FColor::Green, option);
	option.Empty();


	//BLUE
	prop_name.Add(Blue.RANGEUP, Blue.NAME_RANGEUP);
	BlueRuneOption.Add(Blue.RANGEUP, Blue.NAME_RANGEUP);
	option.Add("RANGE UP", prop_name);
	prop_name.Empty();

	prop_name.Add(Blue.EXPUP, Blue.NAME_EXPUP);
	BlueRuneOption.Add(Blue.EXPUP, Blue.NAME_EXPUP);
	option.Add("EXP UP", prop_name);
	prop_name.Empty();

	prop_name.Add(Blue.SLOW, Blue.NAME_SLOW);
	BlueRuneOption.Add(Blue.SLOW, Blue.NAME_SLOW);
	option.Add("SLOW", prop_name);
	prop_name.Empty();

	/*prop_name.Add(Blue.GUIDED, Blue.NAME_GUIDED);
	BlueRuneOption.Add(Blue.GUIDED, Blue.NAME_GUIDED);
	option.Add("GUIDED", prop_name);
	prop_name.Empty();*/

	/*prop_name.Add(Blue.FREEZEONSLOW, Blue.NAME_FREEZEONSLOW);
	BlueRuneOption.Add(Blue.FREEZEONSLOW, Blue.NAME_FREEZEONSLOW);
	option.Add("FREEZEONSLOW", prop_name);
	prop_name.Empty();*/

	/*prop_name.Add(Blue.AREAUP, Blue.NAME_AREAUP);
	BlueRuneOption.Add(Blue.AREAUP, Blue.NAME_AREAUP);
	option.Add("AREAUP", prop_name);
	prop_name.Empty();*/

	/*prop_name.Add(Blue.DAMAGEUPTOTRIANGLE, Blue.NAME_DAMAGEUPTOTRIANGLE);
	BlueRuneOption.Add(Blue.DAMAGEUPTOTRIANGLE, Blue.NAME_DAMAGEUPTOTRIANGLE);
	option.Add("DAMAGEUPTOTRIANGLE", prop_name);
	prop_name.Empty();*/

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

	stat.Add("MIN", RuneStatRange.Tier1.KNOCKBACK_MIN);
	stat.Add("MAX", RuneStatRange.Tier1.KNOCKBACK_MAX);
	_option.Add("KNOCKBACK", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier1.LIFESTEAL_MIN);
	stat.Add("MAX", RuneStatRange.Tier1.LIFESTEAL_MAX);
	_option.Add("LIFESTEAL", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier1.IGNITE_MIN);
	stat.Add("MAX", RuneStatRange.Tier1.IGNITE_MAX);
	_option.Add("IGNITE", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier1.DAMAGEUPONIGNITE_MIN);
	stat.Add("MAX", RuneStatRange.Tier1.DAMAGEUPONIGNITE_MAX);
	_option.Add("DAMAGEUPONIGNITE", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier1.DAMAGEUPTOCIRCLE_MIN);
	stat.Add("MAX", RuneStatRange.Tier1.DAMAGEUPTOCIRCLE_MAX);
	_option.Add("DAMAGEUPTOCIRCLE", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier1.ATTACKSPEEDUP_MIN);
	stat.Add("MAX", RuneStatRange.Tier1.ATTACKSPEEDUP_MAX);
	_option.Add("ATTACK SPEED UP", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier1.BULLETSPEEDUP_MIN);
	stat.Add("MAX", RuneStatRange.Tier1.BULLETSPEEDUP_MAX);
	_option.Add("BULLET SPEED UP", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier1.DAMAGEUP_MIN);
	stat.Add("MAX", RuneStatRange.Tier1.DAMAGEUP_MAX);
	_option.Add("DAMAGE UP", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier1.DAMAGEUPTOSQARE_MIN);
	stat.Add("MAX", RuneStatRange.Tier1.DAMAGEUPTOSQARE_MAX);
	_option.Add("DAMAGEUPTOSQARE", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier1.ATTACKTWICE_MIN);
	stat.Add("MAX", RuneStatRange.Tier1.ATTACKTWICE_MAX);
	_option.Add("ATTACKTWICE", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier1.PIERCE_MIN);
	stat.Add("MAX", RuneStatRange.Tier1.PIERCE_MAX);
	_option.Add("PIERCE", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier1.DOTDAMAGEUP_MIN);
	stat.Add("MAX", RuneStatRange.Tier1.DOTDAMAGEUP_MAX);
	_option.Add("DOTDAMAGEUP", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier1.RANGEUP_MIN);
	stat.Add("MAX", RuneStatRange.Tier1.RANGEUP_MAX);
	_option.Add("RANGE UP", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier1.EXPUP_MIN);
	stat.Add("MAX", RuneStatRange.Tier1.EXPUP_MAX);
	_option.Add("EXP UP", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier1.GUIDED_MIN);
	stat.Add("MAX", RuneStatRange.Tier1.GUIDED_MAX);
	_option.Add("GUIDED", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier1.SLOW_MIN);
	stat.Add("MAX", RuneStatRange.Tier1.SLOW_MAX);
	_option.Add("SLOW", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier1.FREEZEONSLOW_MIN);
	stat.Add("MAX", RuneStatRange.Tier1.FREEZEONSLOW_MAX);
	_option.Add("FREEZEONSLOW", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier1.AREAUP_MIN);
	stat.Add("MAX", RuneStatRange.Tier1.AREAUP_MAX);
	_option.Add("AREAUP", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier1.DAMAGEUPTOTRIANGLE_MIN);
	stat.Add("MAX", RuneStatRange.Tier1.DAMAGEUPTOTRIANGLE_MAX);
	_option.Add("DAMAGEUPTOTRIANGLE", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier1.DEBUFFDURATION_MIN);
	stat.Add("MAX", RuneStatRange.Tier1.DEBUFFDURATION_MAX);
	_option.Add("DEBUFFDURATION", stat);
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

	stat.Add("MIN", RuneStatRange.Tier2.KNOCKBACK_MIN);
	stat.Add("MAX", RuneStatRange.Tier2.KNOCKBACK_MAX);
	_option.Add("KNOCKBACK", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier2.LIFESTEAL_MIN);
	stat.Add("MAX", RuneStatRange.Tier2.LIFESTEAL_MAX);
	_option.Add("LIFESTEAL", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier2.IGNITE_MIN);
	stat.Add("MAX", RuneStatRange.Tier2.IGNITE_MAX);
	_option.Add("IGNITE", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier2.DAMAGEUPONIGNITE_MIN);
	stat.Add("MAX", RuneStatRange.Tier2.DAMAGEUPONIGNITE_MAX);
	_option.Add("DAMAGEUPONIGNITE", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier2.DAMAGEUPTOCIRCLE_MIN);
	stat.Add("MAX", RuneStatRange.Tier2.DAMAGEUPTOCIRCLE_MAX);
	_option.Add("DAMAGEUPTOCIRCLE", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier2.ATTACKSPEEDUP_MIN);
	stat.Add("MAX", RuneStatRange.Tier2.ATTACKSPEEDUP_MAX);
	_option.Add("ATTACK SPEED UP", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier2.BULLETSPEEDUP_MIN);
	stat.Add("MAX", RuneStatRange.Tier2.BULLETSPEEDUP_MAX);
	_option.Add("BULLET SPEED UP", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier2.DAMAGEUP_MIN);
	stat.Add("MAX", RuneStatRange.Tier2.DAMAGEUP_MAX);
	_option.Add("DAMAGE UP", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier2.DAMAGEUPTOSQARE_MIN);
	stat.Add("MAX", RuneStatRange.Tier2.DAMAGEUPTOSQARE_MAX);
	_option.Add("DAMAGEUPTOSQARE", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier2.ATTACKTWICE_MIN);
	stat.Add("MAX", RuneStatRange.Tier2.ATTACKTWICE_MAX);
	_option.Add("ATTACKTWICE", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier2.PIERCE_MIN);
	stat.Add("MAX", RuneStatRange.Tier2.PIERCE_MAX);
	_option.Add("PIERCE", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier2.DOTDAMAGEUP_MIN);
	stat.Add("MAX", RuneStatRange.Tier2.DOTDAMAGEUP_MAX);
	_option.Add("DOTDAMAGEUP", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier2.RANGEUP_MIN);
	stat.Add("MAX", RuneStatRange.Tier2.RANGEUP_MAX);
	_option.Add("RANGE UP", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier2.EXPUP_MIN);
	stat.Add("MAX", RuneStatRange.Tier2.EXPUP_MAX);
	_option.Add("EXP UP", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier2.GUIDED_MIN);
	stat.Add("MAX", RuneStatRange.Tier2.GUIDED_MAX);
	_option.Add("GUIDED", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier2.SLOW_MIN);
	stat.Add("MAX", RuneStatRange.Tier2.SLOW_MAX);
	_option.Add("SLOW", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier2.FREEZEONSLOW_MIN);
	stat.Add("MAX", RuneStatRange.Tier2.FREEZEONSLOW_MAX);
	_option.Add("FREEZEONSLOW", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier2.AREAUP_MIN);
	stat.Add("MAX", RuneStatRange.Tier2.AREAUP_MAX);
	_option.Add("AREAUP", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier2.DAMAGEUPTOTRIANGLE_MIN);
	stat.Add("MAX", RuneStatRange.Tier2.DAMAGEUPTOTRIANGLE_MAX);
	_option.Add("DAMAGEUPTOTRIANGLE", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier2.DEBUFFDURATION_MIN);
	stat.Add("MAX", RuneStatRange.Tier2.DEBUFFDURATION_MAX);
	_option.Add("DEBUFFDURATION", stat);
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

	stat.Add("MIN", RuneStatRange.Tier3.KNOCKBACK_MIN);
	stat.Add("MAX", RuneStatRange.Tier3.KNOCKBACK_MAX);
	_option.Add("KNOCKBACK", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier3.LIFESTEAL_MIN);
	stat.Add("MAX", RuneStatRange.Tier3.LIFESTEAL_MAX);
	_option.Add("LIFESTEAL", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier3.IGNITE_MIN);
	stat.Add("MAX", RuneStatRange.Tier3.IGNITE_MAX);
	_option.Add("IGNITE", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier3.DAMAGEUPONIGNITE_MIN);
	stat.Add("MAX", RuneStatRange.Tier3.DAMAGEUPONIGNITE_MAX);
	_option.Add("DAMAGEUPONIGNITE", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier3.DAMAGEUPTOCIRCLE_MIN);
	stat.Add("MAX", RuneStatRange.Tier3.DAMAGEUPTOCIRCLE_MAX);
	_option.Add("DAMAGEUPTOCIRCLE", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier3.ATTACKSPEEDUP_MIN);
	stat.Add("MAX", RuneStatRange.Tier3.ATTACKSPEEDUP_MAX);
	_option.Add("ATTACK SPEED UP", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier3.BULLETSPEEDUP_MIN);
	stat.Add("MAX", RuneStatRange.Tier3.BULLETSPEEDUP_MAX);
	_option.Add("BULLET SPEED UP", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier3.DAMAGEUP_MIN);
	stat.Add("MAX", RuneStatRange.Tier3.DAMAGEUP_MAX);
	_option.Add("DAMAGE UP", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier3.DAMAGEUPTOSQARE_MIN);
	stat.Add("MAX", RuneStatRange.Tier3.DAMAGEUPTOSQARE_MAX);
	_option.Add("DAMAGEUPTOSQARE", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier3.ATTACKTWICE_MIN);
	stat.Add("MAX", RuneStatRange.Tier3.ATTACKTWICE_MAX);
	_option.Add("ATTACKTWICE", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier3.PIERCE_MIN);
	stat.Add("MAX", RuneStatRange.Tier3.PIERCE_MAX);
	_option.Add("PIERCE", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier3.DOTDAMAGEUP_MIN);
	stat.Add("MAX", RuneStatRange.Tier3.DOTDAMAGEUP_MAX);
	_option.Add("DOTDAMAGEUP", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier3.RANGEUP_MIN);
	stat.Add("MAX", RuneStatRange.Tier3.RANGEUP_MAX);
	_option.Add("RANGE UP", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier3.EXPUP_MIN);
	stat.Add("MAX", RuneStatRange.Tier3.EXPUP_MAX);
	_option.Add("EXPUP", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier3.GUIDED_MIN);
	stat.Add("MAX", RuneStatRange.Tier3.GUIDED_MAX);
	_option.Add("GUIDED", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier3.SLOW_MIN);
	stat.Add("MAX", RuneStatRange.Tier3.SLOW_MAX);
	_option.Add("SLOW", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier3.FREEZEONSLOW_MIN);
	stat.Add("MAX", RuneStatRange.Tier3.FREEZEONSLOW_MAX);
	_option.Add("FREEZEONSLOW", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier3.AREAUP_MIN);
	stat.Add("MAX", RuneStatRange.Tier3.AREAUP_MAX);
	_option.Add("AREAUP", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier3.DAMAGEUPTOTRIANGLE_MIN);
	stat.Add("MAX", RuneStatRange.Tier3.DAMAGEUPTOTRIANGLE_MAX);
	_option.Add("DAMAGEUPTOTRIANGLE", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier3.DEBUFFDURATION_MIN);
	stat.Add("MAX", RuneStatRange.Tier3.DEBUFFDURATION_MAX);
	_option.Add("DEBUFFDURATION", stat);
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

AFP_Rune* AFP_ComRuneGenerator::GenerateRune(TMap<FColor, TMap<FString, TMap<uint64, FString>>> _runeProperty, TMap<uint64, FString> _redRuneOption, TMap<uint64, FString> _greenRuneOption, TMap<uint64, FString> _blueRuneOption, TMap<int, TMap<FString, TMap<FString, float>>> _runeStat, AFP_Rune* _rune, int _stage)
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
	int random = FMath::RandRange(0, 2);
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
				random = int(FMath::RandRange(0, _runeProperty[FColor::Red].Num() - 1));
				hex = (uint64)FMath::Pow(16, random);
				
				if ((_rune->Property & hex) == 0)
					break;
			}
		
			_rune->Name += _redRuneOption[hex].Left(_redRuneOption[hex].Find(TEXT(":"))) + " ";
			_rune->Option.Add(_redRuneOption[hex].Left(_redRuneOption[hex].Find(TEXT(":"))));
			_rune->Property = _rune->Property | hex;

			if (_redRuneOption[hex].Contains("STAT"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::STAT);

			if (_redRuneOption[hex].Contains("PROBABILITY"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::PROBABILITY);

			if (_redRuneOption[hex].Contains("FIXED"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::FIXED);

			if (_redRuneOption[hex].Contains("PROJECTILE"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::PROJECTILE);

			if (_redRuneOption[hex].Contains("AOE"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::AOE);

			if (_redRuneOption[hex].Contains("DOT"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::DOT);

			if (_redRuneOption[hex].Contains("EXP"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::EXP);

			if (_redRuneOption[hex].Contains("DEBUFF"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::DEBUFF);

			if (_redRuneOption[hex].Contains("ETC"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::ETC);
		}
		break;

	case 1:
		_rune->Color = FColor::Green;
		for (i = 0; i < _rune->Stat.Tier; ++i)
		{
			while (1)
			{
				random = FMath::RandRange(0, _runeProperty[FColor::Green].Num() - 1);
				hex = (uint64)pow(16, random);
				
				if ((_rune->Property & hex) == 0)
					break;
			}
			
			_rune->Name += _greenRuneOption[hex].Left(_greenRuneOption[hex].Find(TEXT(":"))) + " ";
			_rune->Option.Add(_greenRuneOption[hex].Left(_greenRuneOption[hex].Find(TEXT(":"))));
			_rune->Property = _rune->Property | hex;

			if (_greenRuneOption[hex].Contains("STAT"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::STAT);

			if (_greenRuneOption[hex].Contains("PROBABILITY"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::PROBABILITY);

			if (_greenRuneOption[hex].Contains("FIXED"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::FIXED);

			if (_greenRuneOption[hex].Contains("PROJECTILE"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::PROJECTILE);

			if (_greenRuneOption[hex].Contains("AOE"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::AOE);

			if (_greenRuneOption[hex].Contains("DOT"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::DOT);

			if (_greenRuneOption[hex].Contains("EXP"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::EXP);

			if (_greenRuneOption[hex].Contains("DEBUFF"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::DEBUFF);

			if (_greenRuneOption[hex].Contains("ETC"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::ETC);
		}
		break;

	case 2:
		_rune->Color = FColor::Blue;
		for (i = 0; i < _rune->Stat.Tier; ++i)
		{
			while (1)
			{
				random = FMath::RandRange(0, _runeProperty[FColor::Blue].Num() - 1);
				hex = (uint64)pow(16, random);
				
				if ((_rune->Property & hex) == 0)
					break;
			}
			
			_rune->Name += _blueRuneOption[hex].Left(_blueRuneOption[hex].Find(TEXT(":"))) + " ";
			_rune->Option.Add(_blueRuneOption[hex].Left(_blueRuneOption[hex].Find(TEXT(":"))));
			_rune->Property = _rune->Property | hex;

			if (_blueRuneOption[hex].Contains("STAT"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::STAT);

			if (_blueRuneOption[hex].Contains("PROBABILITY"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::PROBABILITY);

			if (_blueRuneOption[hex].Contains("FIXED"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::FIXED);

			if (_blueRuneOption[hex].Contains("PROJECTILE"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::PROJECTILE);

			if (_blueRuneOption[hex].Contains("AOE"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::AOE);

			if (_blueRuneOption[hex].Contains("DOT"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::DOT);

			if (_blueRuneOption[hex].Contains("EXP"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::EXP);

			if (_blueRuneOption[hex].Contains("DEBUFF"))
				_rune->Stat.Type.Add(AFP_Rune::TYPE::DEBUFF);

			if (_blueRuneOption[hex].Contains("ETC"))
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
					_rune->Stat.Damage = FMath::RandRange(_runeStat[_rune->Stat.Tier]["DAMAGE UP"]["MIN"], _runeStat[_rune->Stat.Tier]["DAMAGE UP"]["MAX"]);
					_rune->OptionVal[j] = _rune->Stat.Damage;
				}
				else if (_rune->Option[j].Contains("RANGE"))
				{
					_rune->Stat.Range = FMath::RandRange(_runeStat[_rune->Stat.Tier]["RANGE UP"]["MIN"], _runeStat[_rune->Stat.Tier]["RANGE UP"]["MAX"]);
					_rune->OptionVal[j] = _rune->Stat.Range;
				}
				else if (_rune->Option[j].Contains("ATTACK SPEED"))
				{
					_rune->Stat.CoolTimeRatio = FMath::RandRange(_runeStat[_rune->Stat.Tier]["ATTACK SPEED UP"]["MIN"], _runeStat[_rune->Stat.Tier]["ATTACK SPEED UP"]["MAX"]);
					_rune->OptionVal[j] = _rune->Stat.CoolTimeRatio;
				}
				else if (_rune->Option[j].Contains("BULLET SPEED"))
				{
					_rune->Stat.Speed = FMath::RandRange(_runeStat[_rune->Stat.Tier]["BULLET SPEED UP"]["MIN"], _runeStat[_rune->Stat.Tier]["BULLET SPEED UP"]["MAX"]);
					_rune->OptionVal[j] = _rune->Stat.Speed;
				}
			}
		}

		/*if (_rune->Stat.Type[i] == AFP_Rune::TYPE::PROBABILITY)
		{

		}*/

		if (_rune->Stat.Type[i] == AFP_Rune::TYPE::FIXED)
		{
			for (int j = 0; j < _rune->Option.Num(); ++j)
			{
				if (_rune->Option[j].Contains("IGNITE"))
				{
					_rune->OptionVal[j] = FMath::RandRange(_runeStat[_rune->Stat.Tier]["IGNITE"]["MIN"], _runeStat[_rune->Stat.Tier]["IGNITE"]["MAX"]);
					_rune->Ignite.Damage = _rune->OptionVal[j];
					_rune->Ignite.Duration = FMath::RandRange(_runeStat[_rune->Stat.Tier]["DEBUFFDURATION"]["MIN"], _runeStat[_rune->Stat.Tier]["DEBUFFDURATION"]["MAX"]);
				}
			}

			for (int j = 0; j < _rune->Option.Num(); ++j)
			{
				if (_rune->Option[j].Contains("SLOW"))
				{
					_rune->OptionVal[j] = FMath::RandRange(_runeStat[_rune->Stat.Tier]["SLOW"]["MIN"], _runeStat[_rune->Stat.Tier]["SLOW"]["MAX"]);
					_rune->Ignite.Damage = _rune->OptionVal[j];
					_rune->Ignite.Duration = FMath::RandRange(_runeStat[_rune->Stat.Tier]["DEBUFFDURATION"]["MIN"], _runeStat[_rune->Stat.Tier]["DEBUFFDURATION"]["MAX"]);
				}
			}
		}

		/*if (_rune->Stat.Type[i] == AFP_Rune::TYPE::PROJECTILE)
		{

		}*/

		/*if (_rune->Stat.Type[i] == AFP_Rune::TYPE::AOE)
		{

		}*/

		/*if (_rune->Stat.Type[i] == AFP_Rune::TYPE::DOT)
		{

		}*/

		/*if (_rune->Stat.Type[i] == AFP_Rune::TYPE::EXP)
		{

		}*/

		/*if (_rune->Stat.Type[i] == AFP_Rune::TYPE::ETC)
		{

		}*/
	}

	//UE_LOG(LogClass, Log, TEXT("========================================================"));
	//UE_LOG(LogClass, Log, TEXT("Tier : %d"), _rune->Stat.Tier);
	//UE_LOG(LogClass, Log, TEXT("Color : %f, %f, %f"), (float)_rune->Color.R, (float)_rune->Color.G, (float)_rune->Color.B);
	//UE_LOG(LogClass, Log, TEXT("%s"), *_rune->Icon->GetName());
	//UE_LOG(LogClass, Log, TEXT("Property : %x"), _rune->Property);
	//UE_LOG(LogClass, Log, TEXT("Name : %s"), *_rune->Name);

	return _rune;
}