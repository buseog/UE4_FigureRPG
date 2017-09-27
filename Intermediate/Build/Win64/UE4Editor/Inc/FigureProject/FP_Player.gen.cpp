// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "FP_Player.h"
PRAGMA_DISABLE_OPTIMIZATION
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFP_Player() {}
// Cross Module References
	FIGUREPROJECT_API UClass* Z_Construct_UClass_AFP_Player_NoRegister();
	FIGUREPROJECT_API UClass* Z_Construct_UClass_AFP_Player();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_FigureProject();
// End Cross Module References
	void AFP_Player::StaticRegisterNativesAFP_Player()
	{
	}
	UClass* Z_Construct_UClass_AFP_Player_NoRegister()
	{
		return AFP_Player::StaticClass();
	}
	UClass* Z_Construct_UClass_AFP_Player()
	{
		static UClass* OuterClass = NULL;
		if (!OuterClass)
		{
			Z_Construct_UClass_AActor();
			Z_Construct_UPackage__Script_FigureProject();
			OuterClass = AFP_Player::StaticClass();
			if (!(OuterClass->ClassFlags & CLASS_Constructed))
			{
				UObjectForceRegistration(OuterClass);
				OuterClass->ClassFlags |= (EClassFlags)0x20900080u;


				static TCppClassTypeInfo<TCppClassTypeTraits<AFP_Player> > StaticCppClassTypeInfo;
				OuterClass->SetCppTypeInfo(&StaticCppClassTypeInfo);
				OuterClass->StaticLink();
#if WITH_METADATA
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
				MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("FP_Player.h"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("FP_Player.h"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
	IMPLEMENT_CLASS(AFP_Player, 95660205);
	static FCompiledInDefer Z_CompiledInDefer_UClass_AFP_Player(Z_Construct_UClass_AFP_Player, &AFP_Player::StaticClass, TEXT("/Script/FigureProject"), TEXT("AFP_Player"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AFP_Player);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
PRAGMA_ENABLE_OPTIMIZATION
