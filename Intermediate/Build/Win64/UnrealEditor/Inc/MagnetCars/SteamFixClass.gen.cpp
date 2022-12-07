// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MagnetCars/Public/SteamFixClass.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSteamFixClass() {}
// Cross Module References
	MAGNETCARS_API UClass* Z_Construct_UClass_USteamFixClass_NoRegister();
	MAGNETCARS_API UClass* Z_Construct_UClass_USteamFixClass();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	UPackage* Z_Construct_UPackage__Script_MagnetCars();
// End Cross Module References
	void USteamFixClass::StaticRegisterNativesUSteamFixClass()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(USteamFixClass);
	UClass* Z_Construct_UClass_USteamFixClass_NoRegister()
	{
		return USteamFixClass::StaticClass();
	}
	struct Z_Construct_UClass_USteamFixClass_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_USteamFixClass_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
		(UObject* (*)())Z_Construct_UPackage__Script_MagnetCars,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USteamFixClass_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "SteamFixClass.h" },
		{ "ModuleRelativePath", "Public/SteamFixClass.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_USteamFixClass_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USteamFixClass>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_USteamFixClass_Statics::ClassParams = {
		&USteamFixClass::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_USteamFixClass_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_USteamFixClass_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_USteamFixClass()
	{
		if (!Z_Registration_Info_UClass_USteamFixClass.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_USteamFixClass.OuterSingleton, Z_Construct_UClass_USteamFixClass_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_USteamFixClass.OuterSingleton;
	}
	template<> MAGNETCARS_API UClass* StaticClass<USteamFixClass>()
	{
		return USteamFixClass::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(USteamFixClass);
	struct Z_CompiledInDeferFile_FID_MagnetCars_Source_MagnetCars_Public_SteamFixClass_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_MagnetCars_Source_MagnetCars_Public_SteamFixClass_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_USteamFixClass, USteamFixClass::StaticClass, TEXT("USteamFixClass"), &Z_Registration_Info_UClass_USteamFixClass, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(USteamFixClass), 1464833980U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_MagnetCars_Source_MagnetCars_Public_SteamFixClass_h_2504992803(TEXT("/Script/MagnetCars"),
		Z_CompiledInDeferFile_FID_MagnetCars_Source_MagnetCars_Public_SteamFixClass_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_MagnetCars_Source_MagnetCars_Public_SteamFixClass_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
