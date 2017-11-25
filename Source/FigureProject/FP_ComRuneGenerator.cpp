// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_ComRuneGenerator.h"
#include "FP_RuneTable.h"
#include "FP_Monster.h"
#include "FP_RuneToolTip.h"


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

	prop_name.Add(Green.SLOW, Green.NAME_SLOW);
	GreenRuneOption.Add(Green.SLOW, Green.NAME_SLOW);
	option.Add("SLOW", prop_name);
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

	prop_name.Add(Blue.FREEZE, Blue.NAME_FREEZE);
	BlueRuneOption.Add(Blue.FREEZE, Blue.NAME_FREEZE);
	option.Add("FREEZE", prop_name);
	prop_name.Empty();

	/*prop_name.Add(Green.STUN, Blue.NAME_STUN);
	BlueRuneOption.Add(Green.STUN, Blue.NAME_STUN);
	option.Add("STUN", prop_name);
	prop_name.Empty();*/

	/*prop_name.Add(Blue.GUIDED, Blue.NAME_GUIDED);
	BlueRuneOption.Add(Blue.GUIDED, Blue.NAME_GUIDED);
	option.Add("GUIDED", prop_name);
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

	stat.Add("MIN", RuneStatRange.Tier1.FREEZE_MIN);
	stat.Add("MAX", RuneStatRange.Tier1.FREEZE_MAX);
	_option.Add("FREEZE", stat);
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

	stat.Add("MIN", RuneStatRange.Tier2.FREEZE_MIN);
	stat.Add("MAX", RuneStatRange.Tier2.FREEZE_MAX);
	_option.Add("FREEZE", stat);
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
	_option.Add("EXP UP", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier3.GUIDED_MIN);
	stat.Add("MAX", RuneStatRange.Tier3.GUIDED_MAX);
	_option.Add("GUIDED", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier3.SLOW_MIN);
	stat.Add("MAX", RuneStatRange.Tier3.SLOW_MAX);
	_option.Add("SLOW", stat);
	stat.Empty();

	stat.Add("MIN", RuneStatRange.Tier3.FREEZE_MIN);
	stat.Add("MAX", RuneStatRange.Tier3.FREEZE_MAX);
	_option.Add("FREEZE", stat);
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

bool AFP_ComRuneGenerator::GenerateRune(TMap<FColor, TMap<FString, TMap<uint64, FString>>> _runeProperty, TMap<uint64, FString> _redRuneOption, TMap<uint64, FString> _greenRuneOption, TMap<uint64, FString> _blueRuneOption, TMap<int, TMap<FString, TMap<FString, float>>> _runeStat, AFP_Rune* _rune, int _stage, int _tier)
{
	//Tier
	_rune->Tier3DropRate = (float)_stage * _rune->Tier3DropRate;
	_rune->Tier2DropRate = (float)_stage * _rune->Tier2DropRate;
	_rune->Tier1DropRate = (float)_stage * _rune->Tier1DropRate;

	if (_rune->Tier3DropRate >= _rune->Tier3MaxDropRate)
		_rune->Tier3DropRate = _rune->Tier3MaxDropRate;

	if (_rune->Tier2DropRate >= _rune->Tier2MaxDropRate)
		_rune->Tier2DropRate = _rune->Tier2MaxDropRate;

	if (_rune->Tier1DropRate >= _rune->Tier1MaxDropRate)
		_rune->Tier1DropRate = _rune->Tier1MaxDropRate;

	if (_tier == 3)
		_rune->Tier3DropRate = 100.f;
	else if (_tier == 2)
		_rune->Tier2DropRate = 100.f;
	else if (_tier == 1)
		_rune->Tier1DropRate = 100.f;


	float DropRate = FMath::FRandRange(0.f, 100.f);
	if (DropRate <= _rune->Tier3DropRate)
		_rune->Stat.Tier = 3;
	else if (DropRate <= _rune->Tier2DropRate)
		_rune->Stat.Tier = 2;
	else if (DropRate <= _rune->Tier1DropRate)
		_rune->Stat.Tier = 1;
	else
	{
		_rune->Destroy();
		return false;
	}

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
				_rune->Stat.Type.Add(_rune->Option.Last(), AFP_Rune::TYPE::STAT);

			if (_redRuneOption[hex].Contains("DEBUFF"))
				_rune->Stat.Type.Add(_rune->Option.Last(), AFP_Rune::TYPE::DEBUFF);

			if (_redRuneOption[hex].Contains("PROBABILITY"))
				_rune->Stat.Type.Add(_rune->Option.Last(), AFP_Rune::TYPE::PROBABILITY);

			if (_redRuneOption[hex].Contains("FIXED"))
				_rune->Stat.Type.Add(_rune->Option.Last(), AFP_Rune::TYPE::FIXED);

			if (_redRuneOption[hex].Contains("PROJECTILE"))
				_rune->Stat.Type.Add(_rune->Option.Last(), AFP_Rune::TYPE::PROJECTILE);

			if (_redRuneOption[hex].Contains("AOE"))
				_rune->Stat.Type.Add(_rune->Option.Last(), AFP_Rune::TYPE::AOE);

			if (_redRuneOption[hex].Contains("DOT"))
				_rune->Stat.Type.Add(_rune->Option.Last(), AFP_Rune::TYPE::DOT);

			if (_redRuneOption[hex].Contains("EXP"))
				_rune->Stat.Type.Add(_rune->Option.Last(), AFP_Rune::TYPE::EXP);

			if (_redRuneOption[hex].Contains("ETC"))
				_rune->Stat.Type.Add(_rune->Option.Last(), AFP_Rune::TYPE::ETC);
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
				_rune->Stat.Type.Add(_rune->Option.Last(), AFP_Rune::TYPE::STAT);

			if (_greenRuneOption[hex].Contains("DEBUFF"))
				_rune->Stat.Type.Add(_rune->Option.Last(), AFP_Rune::TYPE::DEBUFF);

			if (_greenRuneOption[hex].Contains("PROBABILITY"))
				_rune->Stat.Type.Add(_rune->Option.Last(), AFP_Rune::TYPE::PROBABILITY);

			if (_greenRuneOption[hex].Contains("FIXED"))
				_rune->Stat.Type.Add(_rune->Option.Last(), AFP_Rune::TYPE::FIXED);

			if (_greenRuneOption[hex].Contains("PROJECTILE"))
				_rune->Stat.Type.Add(_rune->Option.Last(), AFP_Rune::TYPE::PROJECTILE);

			if (_greenRuneOption[hex].Contains("AOE"))
				_rune->Stat.Type.Add(_rune->Option.Last(), AFP_Rune::TYPE::AOE);

			if (_greenRuneOption[hex].Contains("DOT"))
				_rune->Stat.Type.Add(_rune->Option.Last(), AFP_Rune::TYPE::DOT);

			if (_greenRuneOption[hex].Contains("EXP"))
				_rune->Stat.Type.Add(_rune->Option.Last(), AFP_Rune::TYPE::EXP);

			if (_greenRuneOption[hex].Contains("ETC"))
				_rune->Stat.Type.Add(_rune->Option.Last(), AFP_Rune::TYPE::ETC);
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
				_rune->Stat.Type.Add(_rune->Option.Last(), AFP_Rune::TYPE::STAT);

			if (_blueRuneOption[hex].Contains("DEBUFF"))
				_rune->Stat.Type.Add(_rune->Option.Last(), AFP_Rune::TYPE::DEBUFF);

			if (_blueRuneOption[hex].Contains("PROBABILITY"))
				_rune->Stat.Type.Add(_rune->Option.Last(), AFP_Rune::TYPE::PROBABILITY);

			if (_blueRuneOption[hex].Contains("FIXED"))
				_rune->Stat.Type.Add(_rune->Option.Last(), AFP_Rune::TYPE::FIXED);

			if (_blueRuneOption[hex].Contains("PROJECTILE"))
				_rune->Stat.Type.Add(_rune->Option.Last(), AFP_Rune::TYPE::PROJECTILE);

			if (_blueRuneOption[hex].Contains("AOE"))
				_rune->Stat.Type.Add(_rune->Option.Last(), AFP_Rune::TYPE::AOE);

			if (_blueRuneOption[hex].Contains("DOT"))
				_rune->Stat.Type.Add(_rune->Option.Last(), AFP_Rune::TYPE::DOT);

			if (_blueRuneOption[hex].Contains("EXP"))
				_rune->Stat.Type.Add(_rune->Option.Last(), AFP_Rune::TYPE::EXP);

			if (_blueRuneOption[hex].Contains("ETC"))
				_rune->Stat.Type.Add(_rune->Option.Last(), AFP_Rune::TYPE::ETC);
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
	for (const auto& Entry : _rune->Stat.Type)
	{
		if (Entry.Value == AFP_Rune::TYPE::STAT)
		{
			for (int j = 0; j < _rune->Option.Num(); ++j)
			{
				if (_rune->Discription.Num() >= _rune->Option.Num())
					break;

				if (_rune->Option[j].Contains("DAMAGE") && !_rune->Option[j].Contains("TO"))
				{
					_rune->Stat.Damage = FMath::RandRange(_runeStat[_rune->Stat.Tier]["DAMAGE UP"]["MIN"], _runeStat[_rune->Stat.Tier]["DAMAGE UP"]["MAX"]);
					_rune->OptionVal[j] = _rune->Stat.Damage;
					_rune->Discription.Add("Increase Damage By " + FString::FromInt(FMath::RoundHalfToEven(FMath::RoundHalfToEven((_rune->OptionVal[j] - 1) * 1000.f) / 10)) + "%");
				}
				else if (_rune->Option[j].Contains("RANGE"))
				{
					_rune->Stat.Range = FMath::RandRange(_runeStat[_rune->Stat.Tier]["RANGE UP"]["MIN"], _runeStat[_rune->Stat.Tier]["RANGE UP"]["MAX"]);
					_rune->OptionVal[j] = _rune->Stat.Range;
					_rune->Discription.Add("Increase Range By " + FString::FromInt(FMath::RoundHalfToEven(FMath::RoundHalfToEven((_rune->OptionVal[j] - 1) * 1000.f) / 10)) + "%");
				}
				else if (_rune->Option[j].Contains("ATTACK SPEED"))
				{
					_rune->Stat.CoolTimeRatio = FMath::RandRange(_runeStat[_rune->Stat.Tier]["ATTACK SPEED UP"]["MIN"], _runeStat[_rune->Stat.Tier]["ATTACK SPEED UP"]["MAX"]);
					_rune->OptionVal[j] = _rune->Stat.CoolTimeRatio;
					_rune->Discription.Add("Increase Attack Speed By " + FString::FromInt(FMath::RoundHalfToEven(FMath::RoundHalfToEven((_rune->OptionVal[j] - 1) * 1000.f) / 10)) + "%");
				}
				else if (_rune->Option[j].Contains("BULLET SPEED"))
				{
					_rune->Stat.Speed = FMath::RandRange(_runeStat[_rune->Stat.Tier]["BULLET SPEED UP"]["MIN"], _runeStat[_rune->Stat.Tier]["BULLET SPEED UP"]["MAX"]);
					_rune->OptionVal[j] = _rune->Stat.Speed;
					_rune->Discription.Add("Increase Bullet Speed By " + FString::FromInt(FMath::RoundHalfToEven(FMath::RoundHalfToEven((_rune->OptionVal[j] - 1) * 1000.f) / 10)) + "%");
				}
			}
		}

		if (Entry.Value == AFP_Rune::TYPE::PROBABILITY)
		{
			for (int j = 0; j < _rune->Option.Num(); ++j)
			{
				if (_rune->Discription.Num() >= _rune->Option.Num())
					break;

				if (_rune->Option[j].Contains("FREEZE"))
				{
					_rune->OptionVal[j] = FMath::RandRange(_runeStat[_rune->Stat.Tier]["FREEZE"]["MIN"], _runeStat[_rune->Stat.Tier]["FREEZE"]["MAX"]);
					_rune->Frozen.Probability = _rune->OptionVal[j];
					_rune->Frozen.Duration = FMath::RandRange(_runeStat[_rune->Stat.Tier]["DEBUFFDURATION"]["MIN"], _runeStat[_rune->Stat.Tier]["DEBUFFDURATION"]["MAX"]);
					_rune->Discription.Add("Freeze Enemy With " + FString::FromInt(_rune->Frozen.Probability) + "% Chance For " + FString::FromInt(_rune->Frozen.Duration) + "Sec");
				}
			}
		}

		if (Entry.Value == AFP_Rune::TYPE::FIXED)
		{
			for (int j = 0; j < _rune->Option.Num(); ++j)
			{
				if (_rune->Discription.Num() >= _rune->Option.Num())
					break;

				if (_rune->Option[j].Contains("IGNITE"))
				{
					_rune->OptionVal[j] = FMath::RandRange(_runeStat[_rune->Stat.Tier]["IGNITE"]["MIN"], _runeStat[_rune->Stat.Tier]["IGNITE"]["MAX"]);
					_rune->Ignite.Damage = _rune->OptionVal[j];
					_rune->Ignite.Duration = FMath::RandRange(_runeStat[_rune->Stat.Tier]["DEBUFFDURATION"]["MIN"], _runeStat[_rune->Stat.Tier]["DEBUFFDURATION"]["MAX"]);
					_rune->Discription.Add("Deal " + FString::SanitizeFloat(FMath::RoundHalfToEven(_rune->Ignite.Damage * 5.f * 10) / 10.f) + "%/sec of Enemy's Health For " + FString::FromInt(_rune->Ignite.Duration) + " Sec");
				}
			}

			for (int j = 0; j < _rune->Option.Num(); ++j)
			{
				if (_rune->Discription.Num() >= _rune->Option.Num())
					break;

				if (_rune->Option[j].Contains("SLOW"))
				{
					_rune->OptionVal[j] = FMath::RandRange(_runeStat[_rune->Stat.Tier]["SLOW"]["MIN"], _runeStat[_rune->Stat.Tier]["SLOW"]["MAX"]);
					_rune->Slow.Damage = _rune->OptionVal[j];
					_rune->Slow.Duration = FMath::RandRange(_runeStat[_rune->Stat.Tier]["DEBUFFDURATION"]["MIN"], _runeStat[_rune->Stat.Tier]["DEBUFFDURATION"]["MAX"]);
					_rune->Discription.Add("Slow Enemy For " + FString::FromInt(_rune->Slow.Duration) + " Sec ");
				}
			}
		}

		if (Entry.Value == AFP_Rune::TYPE::PROJECTILE)
		{
			for (int j = 0; j < _rune->Option.Num(); ++j)
			{
				if (_rune->Discription.Num() >= _rune->Option.Num())
					break;

				if (_rune->Option[j].Contains("PIERCE"))
				{
					_rune->Discription.Add("Projectiles Pierce Enemies");
				}
			}
		}

		/*if (Entry.Value == AFP_Rune::TYPE::AOE)
		{

		}*/

		/*if (Entry.Value == AFP_Rune::TYPE::DOT)
		{

		}*/

		if (Entry.Value == AFP_Rune::TYPE::EXP)
		{
			for (int j = 0; j < _rune->Option.Num(); ++j)
			{
				if (_rune->Discription.Num() >= _rune->Option.Num())
					break;

				if (_rune->Option[j].Contains("EXP"))
				{
					_rune->OptionVal[j] = FMath::RandRange(_runeStat[_rune->Stat.Tier]["EXP UP"]["MIN"], _runeStat[_rune->Stat.Tier]["EXP UP"]["MAX"]);
					_rune->Discription.Add("Gain " + FString::FromInt(FMath::RoundHalfToEven(FMath::RoundHalfToEven((_rune->OptionVal[j] - 1) * 1000.f) / 10)) + "% Increased Exp");
					_rune->ExpBonus = _rune->OptionVal[j];
				}
			}
		}

		/*if (Entry.Value == AFP_Rune::TYPE::ETC)
		{

		}*/
	}


	//for (i = 0; i < _rune->Stat.Type.Num(); ++i)
	//{
	//	if (_rune->Stat.Type[i] == AFP_Rune::TYPE::STAT)
	//	{
	//		for (int j = 0; j < _rune->Option.Num(); ++j)
	//		{
	//			if (_rune->Option[j].Contains("DAMAGE") && !_rune->Option[j].Contains("TO"))
	//			{
	//				_rune->Stat.Damage = FMath::RandRange(_runeStat[_rune->Stat.Tier]["DAMAGE UP"]["MIN"], _runeStat[_rune->Stat.Tier]["DAMAGE UP"]["MAX"]);
	//				_rune->OptionVal[j] = _rune->Stat.Damage;
	//			}
	//			else if (_rune->Option[j].Contains("RANGE"))
	//			{
	//				_rune->Stat.Range = FMath::RandRange(_runeStat[_rune->Stat.Tier]["RANGE UP"]["MIN"], _runeStat[_rune->Stat.Tier]["RANGE UP"]["MAX"]);
	//				_rune->OptionVal[j] = _rune->Stat.Range;
	//			}
	//			else if (_rune->Option[j].Contains("ATTACK SPEED"))
	//			{
	//				_rune->Stat.CoolTimeRatio = FMath::RandRange(_runeStat[_rune->Stat.Tier]["ATTACK SPEED UP"]["MIN"], _runeStat[_rune->Stat.Tier]["ATTACK SPEED UP"]["MAX"]);
	//				_rune->OptionVal[j] = _rune->Stat.CoolTimeRatio;
	//			}
	//			else if (_rune->Option[j].Contains("BULLET SPEED"))
	//			{
	//				_rune->Stat.Speed = FMath::RandRange(_runeStat[_rune->Stat.Tier]["BULLET SPEED UP"]["MIN"], _runeStat[_rune->Stat.Tier]["BULLET SPEED UP"]["MAX"]);
	//				_rune->OptionVal[j] = _rune->Stat.Speed;
	//			}
	//		}
	//	}

	//	if (_rune->Stat.Type[i] == AFP_Rune::TYPE::PROBABILITY)
	//	{
	//		for (int j = 0; j < _rune->Option.Num(); ++j)
	//		{
	//			if (_rune->Option[j].Contains("FREEZE"))
	//			{
	//				_rune->OptionVal[j] = FMath::RandRange(_runeStat[_rune->Stat.Tier]["FREEZE"]["MIN"], _runeStat[_rune->Stat.Tier]["FREEZE"]["MAX"]);
	//				_rune->Frozen.Probability = _rune->OptionVal[j];
	//				_rune->Frozen.Duration = FMath::RandRange(_runeStat[_rune->Stat.Tier]["DEBUFFDURATION"]["MIN"], _runeStat[_rune->Stat.Tier]["DEBUFFDURATION"]["MAX"]);
	//			}
	//		}
	//	}

	//	if (_rune->Stat.Type[i] == AFP_Rune::TYPE::FIXED)
	//	{
	//		for (int j = 0; j < _rune->Option.Num(); ++j)
	//		{
	//			if (_rune->Option[j].Contains("IGNITE"))
	//			{
	//				_rune->OptionVal[j] = FMath::RandRange(_runeStat[_rune->Stat.Tier]["IGNITE"]["MIN"], _runeStat[_rune->Stat.Tier]["IGNITE"]["MAX"]);
	//				_rune->Ignite.Damage = _rune->OptionVal[j];
	//				_rune->Ignite.Duration = FMath::RandRange(_runeStat[_rune->Stat.Tier]["DEBUFFDURATION"]["MIN"], _runeStat[_rune->Stat.Tier]["DEBUFFDURATION"]["MAX"]);
	//			}
	//		}

	//		for (int j = 0; j < _rune->Option.Num(); ++j)
	//		{
	//			if (_rune->Option[j].Contains("SLOW"))
	//			{
	//				_rune->OptionVal[j] = FMath::RandRange(_runeStat[_rune->Stat.Tier]["SLOW"]["MIN"], _runeStat[_rune->Stat.Tier]["SLOW"]["MAX"]);
	//				_rune->Slow.Damage = _rune->OptionVal[j];
	//				_rune->Slow.Duration = FMath::RandRange(_runeStat[_rune->Stat.Tier]["DEBUFFDURATION"]["MIN"], _runeStat[_rune->Stat.Tier]["DEBUFFDURATION"]["MAX"]);
	//			}
	//		}
	//	}

	//	/*if (_rune->Stat.Type[i] == AFP_Rune::TYPE::PROJECTILE)
	//	{

	//	}*/

	//	/*if (_rune->Stat.Type[i] == AFP_Rune::TYPE::AOE)
	//	{

	//	}*/

	//	/*if (_rune->Stat.Type[i] == AFP_Rune::TYPE::DOT)
	//	{

	//	}*/

	//	if (_rune->Stat.Type[i] == AFP_Rune::TYPE::EXP)
	//	{
	//		for (int j = 0; j < _rune->Option.Num(); ++j)
	//		{
	//			if (_rune->Option[j].Contains("EXP"))
	//			{
	//				_rune->OptionVal[j] = FMath::RandRange(_runeStat[_rune->Stat.Tier]["EXP UP"]["MIN"], _runeStat[_rune->Stat.Tier]["EXP UP"]["MAX"]);
	//			}
	//		}
	//	}

	//	/*if (_rune->Stat.Type[i] == AFP_Rune::TYPE::ETC)
	//	{

	//	}*/
	//}

	//UE_LOG(LogClass, Log, TEXT("========================================================"));
	//UE_LOG(LogClass, Log, TEXT("Tier : %d"), _rune->Stat.Tier);
	//UE_LOG(LogClass, Log, TEXT("Color : %f, %f, %f"), (float)_rune->Color.R, (float)_rune->Color.G, (float)_rune->Color.B);
	//UE_LOG(LogClass, Log, TEXT("%s"), *_rune->Icon->GetName());
	//UE_LOG(LogClass, Log, TEXT("Property : %x"), _rune->Property);
	//UE_LOG(LogClass, Log, TEXT("Name : %s"), *_rune->Name);

	return true;
}

void AFP_ComRuneGenerator::ChangeOption(/*AFP_Rune* _rune, */int _index, TMap<FColor, TMap<FString, TMap<uint64, FString>>> _runeProperty, TMap<uint64, FString> _redRuneOption, TMap<uint64, FString> _greenRuneOption, TMap<uint64, FString> _blueRuneOption, TMap<int, TMap<FString, TMap<FString, float>>> _runeStat)
{
	uint64 hex = 0;

	uint64 property = 0;

	if (UFP_RuneToolTip::SelectedRune->Color == FColor::Red)
	{

		for (const auto& Entry : _redRuneOption)
		{
			if (Entry.Value.Contains(UFP_RuneToolTip::SelectedRune->Option[_index]))
				property = Entry.Key;
		}
	}
	else if (UFP_RuneToolTip::SelectedRune->Color == FColor::Green)
	{
		for (const auto& Entry : _greenRuneOption)
		{
			if (Entry.Value.Contains(UFP_RuneToolTip::SelectedRune->Option[_index]))
				property = Entry.Key;
		}
	}
	else
	{
		for (const auto& Entry : _blueRuneOption)
		{
			if (Entry.Value.Contains(UFP_RuneToolTip::SelectedRune->Option[_index]))
				property = Entry.Key;
		}
	}

	UE_LOG(LogClass, Log, TEXT("%s"), *UFP_RuneToolTip::SelectedRune->Name);
	UE_LOG(LogClass, Log, TEXT("Origin Property : %d"), property);

	UFP_RuneToolTip::SelectedRune->Property -= property;

	UE_LOG(LogClass, Log, TEXT("Property after - : %d"), UFP_RuneToolTip::SelectedRune->Property);
	UFP_RuneToolTip::SelectedRune->Name.Empty();
	UFP_RuneToolTip::SelectedRune->Stat.Type.Empty();
	//UFP_RuneToolTip::SelectedRune->Option.RemoveAt(_index);
	//UFP_RuneToolTip::SelectedRune->OptionVal.RemoveAt(_index);
	//UFP_RuneToolTip::SelectedRune->OptionVal.Add(0.f);
	//UFP_RuneToolTip::SelectedRune->OptionVal.Init(0.f, 4);
	//UFP_RuneToolTip::SelectedRune->Discription.Empty();

	if (UFP_RuneToolTip::SelectedRune->Color == FColor::Red)
	{
		while (1)
		{
			int random = int(FMath::RandRange(0, _runeProperty[FColor::Red].Num() - 1));
			hex = (uint64)FMath::Pow(16, random);

			/*UE_LOG(LogClass, Log, TEXT("random : %d"), random);
			UE_LOG(LogClass, Log, TEXT("hex : %d"), hex);
			UE_LOG(LogClass, Log, TEXT("property : %d"), UFP_RuneToolTip::SelectedRune->Property);*/

			if ((UFP_RuneToolTip::SelectedRune->Property & hex) == 0)
				break;
		}
		UE_LOG(LogClass, Log, TEXT("hex : %d"), hex);
		UFP_RuneToolTip::SelectedRune->Property = UFP_RuneToolTip::SelectedRune->Property | hex;
		UE_LOG(LogClass, Log, TEXT("Property after | : %d"), UFP_RuneToolTip::SelectedRune->Property);

		UFP_RuneToolTip::SelectedRune->Option[_index] = _redRuneOption[hex].Left(_redRuneOption[hex].Find(TEXT(":")));
		
		for (int i = 0; i < UFP_RuneToolTip::SelectedRune->Option.Num(); ++i)
		{
			UFP_RuneToolTip::SelectedRune->Name += UFP_RuneToolTip::SelectedRune->Option[i];
			int key;

			for (const auto& Entry : _redRuneOption)
			{
				if (Entry.Value.Contains(UFP_RuneToolTip::SelectedRune->Option[i]))
					key = Entry.Key;
			}

			if (_redRuneOption[key].Contains("STAT"))
				UFP_RuneToolTip::SelectedRune->Stat.Type.Add(UFP_RuneToolTip::SelectedRune->Option.Last(), AFP_Rune::TYPE::STAT);

			if (_redRuneOption[key].Contains("DEBUFF"))
				UFP_RuneToolTip::SelectedRune->Stat.Type.Add(UFP_RuneToolTip::SelectedRune->Option.Last(), AFP_Rune::TYPE::DEBUFF);

			if (_redRuneOption[key].Contains("PROBABILITY"))
				UFP_RuneToolTip::SelectedRune->Stat.Type.Add(UFP_RuneToolTip::SelectedRune->Option.Last(), AFP_Rune::TYPE::PROBABILITY);

			if (_redRuneOption[key].Contains("FIXED"))
				UFP_RuneToolTip::SelectedRune->Stat.Type.Add(UFP_RuneToolTip::SelectedRune->Option.Last(), AFP_Rune::TYPE::FIXED);

			if (_redRuneOption[key].Contains("PROJECTILE"))
				UFP_RuneToolTip::SelectedRune->Stat.Type.Add(UFP_RuneToolTip::SelectedRune->Option.Last(), AFP_Rune::TYPE::PROJECTILE);

			if (_redRuneOption[key].Contains("AOE"))
				UFP_RuneToolTip::SelectedRune->Stat.Type.Add(UFP_RuneToolTip::SelectedRune->Option.Last(), AFP_Rune::TYPE::AOE);

			if (_redRuneOption[key].Contains("DOT"))
				UFP_RuneToolTip::SelectedRune->Stat.Type.Add(UFP_RuneToolTip::SelectedRune->Option.Last(), AFP_Rune::TYPE::DOT);

			if (_redRuneOption[key].Contains("EXP"))
				UFP_RuneToolTip::SelectedRune->Stat.Type.Add(UFP_RuneToolTip::SelectedRune->Option.Last(), AFP_Rune::TYPE::EXP);

			if (_redRuneOption[key].Contains("ETC"))
				UFP_RuneToolTip::SelectedRune->Stat.Type.Add(UFP_RuneToolTip::SelectedRune->Option.Last(), AFP_Rune::TYPE::ETC);
		}
	}
	else if (UFP_RuneToolTip::SelectedRune->Color == FColor::Green)
	{
		while (1)
		{
			int random = int(FMath::RandRange(0, _runeProperty[FColor::Green].Num() - 1));
			hex = (uint64)FMath::Pow(16, random);

			if ((UFP_RuneToolTip::SelectedRune->Property & hex) == 0)
				break;
		}

		TMap<uint64, FString>::TIterator iter = _greenRuneOption.CreateIterator();

		UFP_RuneToolTip::SelectedRune->Property = UFP_RuneToolTip::SelectedRune->Property | hex;

		UFP_RuneToolTip::SelectedRune->Option[_index] = _greenRuneOption[hex].Left(_greenRuneOption[hex].Find(TEXT(":")));

		for (int i = 0; i < UFP_RuneToolTip::SelectedRune->Option.Num(); ++i)
		{
			UFP_RuneToolTip::SelectedRune->Name += UFP_RuneToolTip::SelectedRune->Option[i];
			int key;

			for (const auto& Entry : _greenRuneOption)
			{
				if (Entry.Value.Contains(UFP_RuneToolTip::SelectedRune->Option[i]))
					key = Entry.Key;
			}

			if (_greenRuneOption[key].Contains("STAT"))
				UFP_RuneToolTip::SelectedRune->Stat.Type.Add(UFP_RuneToolTip::SelectedRune->Option.Last(), AFP_Rune::TYPE::STAT);

			if (_greenRuneOption[key].Contains("DEBUFF"))
				UFP_RuneToolTip::SelectedRune->Stat.Type.Add(UFP_RuneToolTip::SelectedRune->Option.Last(), AFP_Rune::TYPE::DEBUFF);

			if (_greenRuneOption[key].Contains("PROBABILITY"))
				UFP_RuneToolTip::SelectedRune->Stat.Type.Add(UFP_RuneToolTip::SelectedRune->Option.Last(), AFP_Rune::TYPE::PROBABILITY);

			if (_greenRuneOption[key].Contains("FIXED"))
				UFP_RuneToolTip::SelectedRune->Stat.Type.Add(UFP_RuneToolTip::SelectedRune->Option.Last(), AFP_Rune::TYPE::FIXED);

			if (_greenRuneOption[key].Contains("PROJECTILE"))
				UFP_RuneToolTip::SelectedRune->Stat.Type.Add(UFP_RuneToolTip::SelectedRune->Option.Last(), AFP_Rune::TYPE::PROJECTILE);

			if (_greenRuneOption[key].Contains("AOE"))
				UFP_RuneToolTip::SelectedRune->Stat.Type.Add(UFP_RuneToolTip::SelectedRune->Option.Last(), AFP_Rune::TYPE::AOE);

			if (_greenRuneOption[key].Contains("DOT"))
				UFP_RuneToolTip::SelectedRune->Stat.Type.Add(UFP_RuneToolTip::SelectedRune->Option.Last(), AFP_Rune::TYPE::DOT);

			if (_greenRuneOption[key].Contains("EXP"))
				UFP_RuneToolTip::SelectedRune->Stat.Type.Add(UFP_RuneToolTip::SelectedRune->Option.Last(), AFP_Rune::TYPE::EXP);

			if (_greenRuneOption[key].Contains("ETC"))
				UFP_RuneToolTip::SelectedRune->Stat.Type.Add(UFP_RuneToolTip::SelectedRune->Option.Last(), AFP_Rune::TYPE::ETC);
		}
	}
	else
	{
		while (1)
		{
			int random = int(FMath::RandRange(0, _runeProperty[FColor::Blue].Num() - 1));
			hex = (uint64)FMath::Pow(16, random);

			if ((UFP_RuneToolTip::SelectedRune->Property & hex) == 0)
				break;
		}

		TMap<uint64, FString>::TIterator iter = _blueRuneOption.CreateIterator();

		UFP_RuneToolTip::SelectedRune->Property = UFP_RuneToolTip::SelectedRune->Property | hex;

		UFP_RuneToolTip::SelectedRune->Option[_index] = _blueRuneOption[hex].Left(_blueRuneOption[hex].Find(TEXT(":")));

		for (int i = 0; i < UFP_RuneToolTip::SelectedRune->Option.Num(); ++i)
		{
			UFP_RuneToolTip::SelectedRune->Name += UFP_RuneToolTip::SelectedRune->Option[i];
			int key;

			for (const auto& Entry : _blueRuneOption)
			{
				if (Entry.Value.Contains(UFP_RuneToolTip::SelectedRune->Option[i]))
					key = Entry.Key;
			}

			if (_blueRuneOption[key].Contains("STAT"))
				UFP_RuneToolTip::SelectedRune->Stat.Type.Add(UFP_RuneToolTip::SelectedRune->Option.Last(), AFP_Rune::TYPE::STAT);

			if (_blueRuneOption[key].Contains("DEBUFF"))
				UFP_RuneToolTip::SelectedRune->Stat.Type.Add(UFP_RuneToolTip::SelectedRune->Option.Last(), AFP_Rune::TYPE::DEBUFF);

			if (_blueRuneOption[key].Contains("PROBABILITY"))
				UFP_RuneToolTip::SelectedRune->Stat.Type.Add(UFP_RuneToolTip::SelectedRune->Option.Last(), AFP_Rune::TYPE::PROBABILITY);

			if (_blueRuneOption[key].Contains("FIXED"))
				UFP_RuneToolTip::SelectedRune->Stat.Type.Add(UFP_RuneToolTip::SelectedRune->Option.Last(), AFP_Rune::TYPE::FIXED);

			if (_blueRuneOption[key].Contains("PROJECTILE"))
				UFP_RuneToolTip::SelectedRune->Stat.Type.Add(UFP_RuneToolTip::SelectedRune->Option.Last(), AFP_Rune::TYPE::PROJECTILE);

			if (_blueRuneOption[key].Contains("AOE"))
				UFP_RuneToolTip::SelectedRune->Stat.Type.Add(UFP_RuneToolTip::SelectedRune->Option.Last(), AFP_Rune::TYPE::AOE);

			if (_blueRuneOption[key].Contains("DOT"))
				UFP_RuneToolTip::SelectedRune->Stat.Type.Add(UFP_RuneToolTip::SelectedRune->Option.Last(), AFP_Rune::TYPE::DOT);

			if (_blueRuneOption[key].Contains("EXP"))
				UFP_RuneToolTip::SelectedRune->Stat.Type.Add(UFP_RuneToolTip::SelectedRune->Option.Last(), AFP_Rune::TYPE::EXP);

			if (_blueRuneOption[key].Contains("ETC"))
				UFP_RuneToolTip::SelectedRune->Stat.Type.Add(UFP_RuneToolTip::SelectedRune->Option.Last(), AFP_Rune::TYPE::ETC);
		}
	}

	if (UFP_RuneToolTip::SelectedRune->Option[_index].Contains("DAMAGE") && !UFP_RuneToolTip::SelectedRune->Option[_index].Contains("TO"))
	{
		UFP_RuneToolTip::SelectedRune->Stat.Damage = FMath::RandRange(_runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["DAMAGE UP"]["MIN"], _runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["DAMAGE UP"]["MAX"]);
		UFP_RuneToolTip::SelectedRune->OptionVal[_index] = UFP_RuneToolTip::SelectedRune->Stat.Damage;
		UFP_RuneToolTip::SelectedRune->Discription[_index] = ("Increase Damage By " + FString::FromInt(FMath::RoundHalfToEven(FMath::RoundHalfToEven((UFP_RuneToolTip::SelectedRune->OptionVal[_index] - 1) * 1000.f) / 10)) + "%");
	}
	else if (UFP_RuneToolTip::SelectedRune->Option[_index].Contains("RANGE"))
	{
		UFP_RuneToolTip::SelectedRune->Stat.Range = FMath::RandRange(_runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["RANGE UP"]["MIN"], _runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["RANGE UP"]["MAX"]);
		UFP_RuneToolTip::SelectedRune->OptionVal[_index] = UFP_RuneToolTip::SelectedRune->Stat.Range;
		UFP_RuneToolTip::SelectedRune->Discription[_index] = ("Increase Range By " + FString::FromInt(FMath::RoundHalfToEven(FMath::RoundHalfToEven((UFP_RuneToolTip::SelectedRune->OptionVal[_index] - 1) * 1000.f) / 10)) + "%");
	}
	else if (UFP_RuneToolTip::SelectedRune->Option[_index].Contains("ATTACK SPEED"))
	{
		UFP_RuneToolTip::SelectedRune->Stat.CoolTimeRatio = FMath::RandRange(_runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["ATTACK SPEED UP"]["MIN"], _runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["ATTACK SPEED UP"]["MAX"]);
		UFP_RuneToolTip::SelectedRune->OptionVal[_index] = UFP_RuneToolTip::SelectedRune->Stat.CoolTimeRatio;
		UFP_RuneToolTip::SelectedRune->Discription[_index] = ("Increase Attack Speed By " + FString::FromInt(FMath::RoundHalfToEven(FMath::RoundHalfToEven((UFP_RuneToolTip::SelectedRune->OptionVal[_index] - 1) * 1000.f) / 10)) + "%");
	}
	else if (UFP_RuneToolTip::SelectedRune->Option[_index].Contains("BULLET SPEED"))
	{
		UFP_RuneToolTip::SelectedRune->Stat.Speed = FMath::RandRange(_runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["BULLET SPEED UP"]["MIN"], _runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["BULLET SPEED UP"]["MAX"]);
		UFP_RuneToolTip::SelectedRune->OptionVal[_index] = UFP_RuneToolTip::SelectedRune->Stat.Speed;
		UFP_RuneToolTip::SelectedRune->Discription[_index] = ("Increase Bullet Speed By " + FString::FromInt(FMath::RoundHalfToEven(FMath::RoundHalfToEven((UFP_RuneToolTip::SelectedRune->OptionVal[_index] - 1) * 1000.f) / 10)) + "%");
	}
	else if (UFP_RuneToolTip::SelectedRune->Option[_index].Contains("FREEZE"))
	{
		UFP_RuneToolTip::SelectedRune->OptionVal[_index] = FMath::RandRange(_runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["FREEZE"]["MIN"], _runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["FREEZE"]["MAX"]);
		UFP_RuneToolTip::SelectedRune->Frozen.Probability = UFP_RuneToolTip::SelectedRune->OptionVal[_index];
		UFP_RuneToolTip::SelectedRune->Frozen.Duration = FMath::RandRange(_runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["DEBUFFDURATION"]["MIN"], _runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["DEBUFFDURATION"]["MAX"]);
		UFP_RuneToolTip::SelectedRune->Discription[_index] = ("Freeze Enemy With " + FString::FromInt(UFP_RuneToolTip::SelectedRune->Frozen.Probability) + "% Chance For " + FString::FromInt(UFP_RuneToolTip::SelectedRune->Frozen.Duration) + "Sec");
	}
	else if (UFP_RuneToolTip::SelectedRune->Option[_index].Contains("IGNITE"))
	{
		UFP_RuneToolTip::SelectedRune->OptionVal[_index] = FMath::RandRange(_runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["IGNITE"]["MIN"], _runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["IGNITE"]["MAX"]);
		UFP_RuneToolTip::SelectedRune->Ignite.Damage = UFP_RuneToolTip::SelectedRune->OptionVal[_index];
		UFP_RuneToolTip::SelectedRune->Ignite.Duration = FMath::RandRange(_runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["DEBUFFDURATION"]["MIN"], _runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["DEBUFFDURATION"]["MAX"]);
		UFP_RuneToolTip::SelectedRune->Discription[_index] = ("Deal " + FString::SanitizeFloat(FMath::RoundHalfToEven(UFP_RuneToolTip::SelectedRune->Ignite.Damage * 5.f * 10) / 10.f) + "%/sec of Enemy's Health For " + FString::FromInt(UFP_RuneToolTip::SelectedRune->Ignite.Duration) + " Sec");
	}
	else if (UFP_RuneToolTip::SelectedRune->Option[_index].Contains("SLOW"))
	{
		UFP_RuneToolTip::SelectedRune->OptionVal[_index] = FMath::RandRange(_runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["SLOW"]["MIN"], _runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["SLOW"]["MAX"]);
		UFP_RuneToolTip::SelectedRune->Slow.Damage = UFP_RuneToolTip::SelectedRune->OptionVal[_index];
		UFP_RuneToolTip::SelectedRune->Slow.Duration = FMath::RandRange(_runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["DEBUFFDURATION"]["MIN"], _runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["DEBUFFDURATION"]["MAX"]);
		UFP_RuneToolTip::SelectedRune->Discription[_index] = ("Slow Enemy For " + FString::FromInt(UFP_RuneToolTip::SelectedRune->Slow.Duration) + " Sec ");
	}
	else if (UFP_RuneToolTip::SelectedRune->Option[_index].Contains("PIERCE"))
	{
		UFP_RuneToolTip::SelectedRune->Discription[_index] = ("Projectiles Pierce Enemies");
	}
	else if (UFP_RuneToolTip::SelectedRune->Option[_index].Contains("EXP"))
	{
		UFP_RuneToolTip::SelectedRune->OptionVal[_index] = FMath::RandRange(_runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["EXP UP"]["MIN"], _runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["EXP UP"]["MAX"]);
		UFP_RuneToolTip::SelectedRune->Discription[_index] = ("Gain " + FString::FromInt(FMath::RoundHalfToEven(FMath::RoundHalfToEven((UFP_RuneToolTip::SelectedRune->OptionVal[_index] - 1) * 1000.f) / 10)) + "% Increased Exp");
		UFP_RuneToolTip::SelectedRune->ExpBonus = UFP_RuneToolTip::SelectedRune->OptionVal[_index];
	}


	//for (const auto& Entry : UFP_RuneToolTip::SelectedRune->Stat.Type)
	//{
	//	if (Entry.Value == AFP_Rune::TYPE::STAT)
	//	{
	//		for (int j = 0; j < UFP_RuneToolTip::SelectedRune->Option.Num(); ++j)
	//		{
	//			if (UFP_RuneToolTip::SelectedRune->Option[j].Contains("DAMAGE") && !UFP_RuneToolTip::SelectedRune->Option[j].Contains("TO"))
	//			{
	//				if (UFP_RuneToolTip::SelectedRune->Discription.Num() >= UFP_RuneToolTip::SelectedRune->Option.Num())
	//					break;

	//				
	//			}
	//			else if (UFP_RuneToolTip::SelectedRune->Option[j].Contains("RANGE"))
	//			{
	//				if (UFP_RuneToolTip::SelectedRune->Discription.Num() >= UFP_RuneToolTip::SelectedRune->Option.Num())
	//					break;

	//				if (UFP_RuneToolTip::SelectedRune->OptionVal[j] != 0.f)
	//				{
	//					UFP_RuneToolTip::SelectedRune->Discription.Add("Increase Range By " + FString::FromInt(FMath::RoundHalfToEven(FMath::RoundHalfToEven((UFP_RuneToolTip::SelectedRune->OptionVal[j] - 1) * 1000.f) / 10)) + "%");
	//					continue;
	//				}

	//				UFP_RuneToolTip::SelectedRune->Stat.Range = FMath::RandRange(_runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["RANGE UP"]["MIN"], _runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["RANGE UP"]["MAX"]);
	//				UFP_RuneToolTip::SelectedRune->OptionVal[j] = UFP_RuneToolTip::SelectedRune->Stat.Range;
	//				UFP_RuneToolTip::SelectedRune->Discription.Add("Increase Range By " + FString::FromInt(FMath::RoundHalfToEven(FMath::RoundHalfToEven((UFP_RuneToolTip::SelectedRune->OptionVal[j] - 1) * 1000.f) / 10)) + "%");
	//			}
	//			else if (UFP_RuneToolTip::SelectedRune->Option[j].Contains("ATTACK SPEED"))
	//			{
	//				if (UFP_RuneToolTip::SelectedRune->Discription.Num() >= UFP_RuneToolTip::SelectedRune->Option.Num())
	//					break;

	//				if (UFP_RuneToolTip::SelectedRune->OptionVal[j] != 0.f)
	//				{
	//					UFP_RuneToolTip::SelectedRune->Discription.Add("Increase Attack Speed By " + FString::FromInt(FMath::RoundHalfToEven(FMath::RoundHalfToEven((UFP_RuneToolTip::SelectedRune->OptionVal[j] - 1) * 1000.f) / 10)) + "%");
	//					continue;
	//				}

	//				UFP_RuneToolTip::SelectedRune->Stat.CoolTimeRatio = FMath::RandRange(_runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["ATTACK SPEED UP"]["MIN"], _runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["ATTACK SPEED UP"]["MAX"]);
	//				UFP_RuneToolTip::SelectedRune->OptionVal[j] = UFP_RuneToolTip::SelectedRune->Stat.CoolTimeRatio;
	//				UFP_RuneToolTip::SelectedRune->Discription.Add("Increase Attack Speed By " + FString::FromInt(FMath::RoundHalfToEven(FMath::RoundHalfToEven((UFP_RuneToolTip::SelectedRune->OptionVal[j] - 1) * 1000.f) / 10)) + "%");
	//			}
	//			else if (UFP_RuneToolTip::SelectedRune->Option[j].Contains("BULLET SPEED"))
	//			{
	//				if (UFP_RuneToolTip::SelectedRune->Discription.Num() >= UFP_RuneToolTip::SelectedRune->Option.Num())
	//					break;

	//				if (UFP_RuneToolTip::SelectedRune->OptionVal[j] != 0.f)
	//				{
	//					UFP_RuneToolTip::SelectedRune->Discription.Add("Increase Bullet Speed By " + FString::FromInt(FMath::RoundHalfToEven(FMath::RoundHalfToEven((UFP_RuneToolTip::SelectedRune->OptionVal[j] - 1) * 1000.f) / 10)) + "%");
	//					continue;
	//				}

	//				UFP_RuneToolTip::SelectedRune->Stat.Speed = FMath::RandRange(_runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["BULLET SPEED UP"]["MIN"], _runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["BULLET SPEED UP"]["MAX"]);
	//				UFP_RuneToolTip::SelectedRune->OptionVal[j] = UFP_RuneToolTip::SelectedRune->Stat.Speed;
	//				UFP_RuneToolTip::SelectedRune->Discription.Add("Increase Bullet Speed By " + FString::FromInt(FMath::RoundHalfToEven(FMath::RoundHalfToEven((UFP_RuneToolTip::SelectedRune->OptionVal[j] - 1) * 1000.f) / 10)) + "%");
	//			}
	//		}
	//	}

	//	if (Entry.Value == AFP_Rune::TYPE::PROBABILITY)
	//	{
	//		for (int j = 0; j < UFP_RuneToolTip::SelectedRune->Option.Num(); ++j)
	//		{
	//			if (UFP_RuneToolTip::SelectedRune->Option[j].Contains("FREEZE"))
	//			{
	//				if (UFP_RuneToolTip::SelectedRune->Discription.Num() >= UFP_RuneToolTip::SelectedRune->Option.Num())
	//					break;

	//				if (UFP_RuneToolTip::SelectedRune->OptionVal[j] != 0.f)
	//				{
	//					UFP_RuneToolTip::SelectedRune->Discription.Add("Freeze Enemy With " + FString::FromInt(UFP_RuneToolTip::SelectedRune->Frozen.Probability) + "% Chance For " + FString::FromInt(UFP_RuneToolTip::SelectedRune->Frozen.Duration) + "Sec");
	//					continue;
	//				}

	//				UFP_RuneToolTip::SelectedRune->OptionVal[j] = FMath::RandRange(_runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["FREEZE"]["MIN"], _runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["FREEZE"]["MAX"]);
	//				UFP_RuneToolTip::SelectedRune->Frozen.Probability = UFP_RuneToolTip::SelectedRune->OptionVal[j];
	//				UFP_RuneToolTip::SelectedRune->Frozen.Duration = FMath::RandRange(_runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["DEBUFFDURATION"]["MIN"], _runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["DEBUFFDURATION"]["MAX"]);
	//				UFP_RuneToolTip::SelectedRune->Discription.Add("Freeze Enemy With " + FString::FromInt(UFP_RuneToolTip::SelectedRune->Frozen.Probability) + "% Chance For " + FString::FromInt(UFP_RuneToolTip::SelectedRune->Frozen.Duration) + "Sec");
	//			}
	//		}
	//	}

	//	if (Entry.Value == AFP_Rune::TYPE::FIXED)
	//	{
	//		for (int j = 0; j < UFP_RuneToolTip::SelectedRune->Option.Num(); ++j)
	//		{
	//			if (UFP_RuneToolTip::SelectedRune->Option[j].Contains("IGNITE"))
	//			{
	//				if (UFP_RuneToolTip::SelectedRune->Discription.Num() >= UFP_RuneToolTip::SelectedRune->Option.Num())
	//					break;

	//				if (UFP_RuneToolTip::SelectedRune->OptionVal[j] != 0.f)
	//				{
	//					UFP_RuneToolTip::SelectedRune->Discription.Add("Deal " + FString::SanitizeFloat(FMath::RoundHalfToEven(UFP_RuneToolTip::SelectedRune->Ignite.Damage * 5.f * 10) / 10.f) + "%/sec of Enemy's Health For " + FString::FromInt(UFP_RuneToolTip::SelectedRune->Ignite.Duration) + " Sec");
	//					continue;
	//				}

	//				UFP_RuneToolTip::SelectedRune->OptionVal[j] = FMath::RandRange(_runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["IGNITE"]["MIN"], _runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["IGNITE"]["MAX"]);
	//				UFP_RuneToolTip::SelectedRune->Ignite.Damage = UFP_RuneToolTip::SelectedRune->OptionVal[j];
	//				UFP_RuneToolTip::SelectedRune->Ignite.Duration = FMath::RandRange(_runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["DEBUFFDURATION"]["MIN"], _runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["DEBUFFDURATION"]["MAX"]);
	//				UFP_RuneToolTip::SelectedRune->Discription.Add("Deal " + FString::SanitizeFloat(FMath::RoundHalfToEven(UFP_RuneToolTip::SelectedRune->Ignite.Damage * 5.f * 10) / 10.f) + "%/sec of Enemy's Health For " + FString::FromInt(UFP_RuneToolTip::SelectedRune->Ignite.Duration) + " Sec");
	//			}
	//		}

	//		for (int j = 0; j < UFP_RuneToolTip::SelectedRune->Option.Num(); ++j)
	//		{
	//			if (UFP_RuneToolTip::SelectedRune->Option[j].Contains("SLOW"))
	//			{
	//				if (UFP_RuneToolTip::SelectedRune->Discription.Num() >= UFP_RuneToolTip::SelectedRune->Option.Num())
	//					break;

	//				if (UFP_RuneToolTip::SelectedRune->OptionVal[j] != 0.f)
	//				{
	//					UFP_RuneToolTip::SelectedRune->Discription.Add("Slow Enemy For " + FString::FromInt(UFP_RuneToolTip::SelectedRune->Slow.Duration) + " Sec ");
	//					continue;
	//				}

	//				UFP_RuneToolTip::SelectedRune->OptionVal[j] = FMath::RandRange(_runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["SLOW"]["MIN"], _runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["SLOW"]["MAX"]);
	//				UFP_RuneToolTip::SelectedRune->Slow.Damage = UFP_RuneToolTip::SelectedRune->OptionVal[j];
	//				UFP_RuneToolTip::SelectedRune->Slow.Duration = FMath::RandRange(_runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["DEBUFFDURATION"]["MIN"], _runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["DEBUFFDURATION"]["MAX"]);
	//				UFP_RuneToolTip::SelectedRune->Discription.Add("Slow Enemy For " + FString::FromInt(UFP_RuneToolTip::SelectedRune->Slow.Duration) + " Sec ");
	//			}
	//		}
	//	}

	//	if (Entry.Value == AFP_Rune::TYPE::PROJECTILE)
	//	{
	//		for (int j = 0; j < UFP_RuneToolTip::SelectedRune->Option.Num(); ++j)
	//		{
	//			if (UFP_RuneToolTip::SelectedRune->Discription.Num() >= UFP_RuneToolTip::SelectedRune->Option.Num())
	//				break;

	//			if (UFP_RuneToolTip::SelectedRune->Option[j].Contains("PIERCE"))
	//			{
	//				UFP_RuneToolTip::SelectedRune->Discription.Add("Projectiles Pierce Enemies");
	//			}
	//		}
	//	}

	//	/*if (Entry.Value == AFP_Rune::TYPE::AOE)
	//	{

	//	}*/

	//	/*if (Entry.Value == AFP_Rune::TYPE::DOT)
	//	{

	//	}*/

	//	if (Entry.Value == AFP_Rune::TYPE::EXP)
	//	{
	//		for (int j = 0; j < UFP_RuneToolTip::SelectedRune->Option.Num(); ++j)
	//		{
	//			if (UFP_RuneToolTip::SelectedRune->Option[j].Contains("EXP"))
	//			{
	//				if (UFP_RuneToolTip::SelectedRune->Discription.Num() >= UFP_RuneToolTip::SelectedRune->Option.Num())
	//					break;

	//				if (UFP_RuneToolTip::SelectedRune->OptionVal[j] != 0.f)
	//				{
	//					UFP_RuneToolTip::SelectedRune->ExpBonus = UFP_RuneToolTip::SelectedRune->OptionVal[j];
	//					continue;
	//				}

	//				UFP_RuneToolTip::SelectedRune->OptionVal[j] = FMath::RandRange(_runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["EXP UP"]["MIN"], _runeStat[UFP_RuneToolTip::SelectedRune->Stat.Tier]["EXP UP"]["MAX"]);
	//				UFP_RuneToolTip::SelectedRune->Discription.Add("Gain " + FString::FromInt(FMath::RoundHalfToEven(FMath::RoundHalfToEven((UFP_RuneToolTip::SelectedRune->OptionVal[j] - 1) * 1000.f) / 10)) + "% Increased Exp");
	//				UFP_RuneToolTip::SelectedRune->ExpBonus = UFP_RuneToolTip::SelectedRune->OptionVal[j];
	//			}
	//		}
	//	}
	//		
	//	/*if (Entry.Value == AFP_Rune::TYPE::ETC)
	//	{

	//	}*/
	//}
}