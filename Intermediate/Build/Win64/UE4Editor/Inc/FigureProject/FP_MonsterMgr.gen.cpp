// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "FP_MonsterMgr.h"
PRAGMA_DISABLE_OPTIMIZATION
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFP_MonsterMgr() {}
// Cross Module References
	FIGUREPROJECT_API UClass* Z_Construct_UClass_AFP_MonsterMgr_NoRegister();
	FIGUREPROJECT_API UClass* Z_Construct_UClass_AFP_MonsterMgr();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_FigureProject();
// End Cross Module References
	void AFP_MonsterMgr::StaticRegisterNativesAFP_MonsterMgr()
	{
	}
	UClass* Z_Construct_UClass_AFP_MonsterMgr_NoRegister()
	{
		return AFP_MonsterMgr::StaticClass();
	}
	UClass* Z_Construct_UClass_AFP_MonsterMgr()
	{
		static UClass* OuterClass = NULL;
		if (!OuterClass)
		{
			Z_Construct_UClass_AActor();
			Z_Construct_UPackage__Script_FigureProject();
			OuterClass = AFP_MonsterMgr::StaticClass();
			if (!(OuterClass->ClassFlags & CLASS_Constructed))
			{
				UObjectForceRegistration(OuterClass);
				OuterClass->ClassFlags |= (EClassFlags)0x20900080u;


				static TCppClassTypeInfo<TCppClassTypeTraits<AFP_MonsterMgr> > StaticCppClassTypeInfo;
				OuterClass->SetCppTypeInfo(&StaticCppClassTypeInfo);
				OuterClass->StaticLink();
#if WITH_METADATA
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
				MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("FP_MonsterMgr.h"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("FP_MonsterMgr.h"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
	IMPLEMENT_CLASS(AFP_MonsterMgr, 1884468465);
	static FCompiledInDefer Z_CompiledInDefer_UClass_AFP_MonsterMgr(Z_Construct_UClass_AFP_MonsterMgr, &AFP_MonsterMgr::StaticClass, TEXT("/Script/FigureProject"), TEXT("AFP_MonsterMgr"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AFP_MonsterMgr);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
PRAGMA_ENABLE_OPTIMIZATION
