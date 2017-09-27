// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "FP_Monster.h"
PRAGMA_DISABLE_OPTIMIZATION
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFP_Monster() {}
// Cross Module References
	FIGUREPROJECT_API UClass* Z_Construct_UClass_AFP_Monster_NoRegister();
	FIGUREPROJECT_API UClass* Z_Construct_UClass_AFP_Monster();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_FigureProject();
// End Cross Module References
	void AFP_Monster::StaticRegisterNativesAFP_Monster()
	{
	}
	UClass* Z_Construct_UClass_AFP_Monster_NoRegister()
	{
		return AFP_Monster::StaticClass();
	}
	UClass* Z_Construct_UClass_AFP_Monster()
	{
		static UClass* OuterClass = NULL;
		if (!OuterClass)
		{
			Z_Construct_UClass_AActor();
			Z_Construct_UPackage__Script_FigureProject();
			OuterClass = AFP_Monster::StaticClass();
			if (!(OuterClass->ClassFlags & CLASS_Constructed))
			{
				UObjectForceRegistration(OuterClass);
				OuterClass->ClassFlags |= (EClassFlags)0x20900080u;


				static TCppClassTypeInfo<TCppClassTypeTraits<AFP_Monster> > StaticCppClassTypeInfo;
				OuterClass->SetCppTypeInfo(&StaticCppClassTypeInfo);
				OuterClass->StaticLink();
#if WITH_METADATA
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
				MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("FP_Monster.h"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("FP_Monster.h"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
	IMPLEMENT_CLASS(AFP_Monster, 711942440);
	static FCompiledInDefer Z_CompiledInDefer_UClass_AFP_Monster(Z_Construct_UClass_AFP_Monster, &AFP_Monster::StaticClass, TEXT("/Script/FigureProject"), TEXT("AFP_Monster"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AFP_Monster);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
PRAGMA_ENABLE_OPTIMIZATION
