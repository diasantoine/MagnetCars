// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MagnetCars/Public/GMGravityCars.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGMGravityCars() {}
// Cross Module References
	MAGNETCARS_API UClass* Z_Construct_UClass_AGMGravityCars_NoRegister();
	MAGNETCARS_API UClass* Z_Construct_UClass_AGMGravityCars();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_MagnetCars();
// End Cross Module References
	void AGMGravityCars::StaticRegisterNativesAGMGravityCars()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AGMGravityCars);
	UClass* Z_Construct_UClass_AGMGravityCars_NoRegister()
	{
		return AGMGravityCars::StaticClass();
	}
	struct Z_Construct_UClass_AGMGravityCars_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Bonsoir_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_Bonsoir;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AGMGravityCars_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_MagnetCars,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGMGravityCars_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "GMGravityCars.h" },
		{ "ModuleRelativePath", "Public/GMGravityCars.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGMGravityCars_Statics::NewProp_Bonsoir_MetaData[] = {
		{ "Category", "GMGravityCars" },
		{ "ModuleRelativePath", "Public/GMGravityCars.h" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_AGMGravityCars_Statics::NewProp_Bonsoir = { "Bonsoir", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AGMGravityCars, Bonsoir), METADATA_PARAMS(Z_Construct_UClass_AGMGravityCars_Statics::NewProp_Bonsoir_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AGMGravityCars_Statics::NewProp_Bonsoir_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AGMGravityCars_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGMGravityCars_Statics::NewProp_Bonsoir,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AGMGravityCars_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AGMGravityCars>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AGMGravityCars_Statics::ClassParams = {
		&AGMGravityCars::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AGMGravityCars_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AGMGravityCars_Statics::PropPointers),
		0,
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_AGMGravityCars_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AGMGravityCars_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AGMGravityCars()
	{
		if (!Z_Registration_Info_UClass_AGMGravityCars.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AGMGravityCars.OuterSingleton, Z_Construct_UClass_AGMGravityCars_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AGMGravityCars.OuterSingleton;
	}
	template<> MAGNETCARS_API UClass* StaticClass<AGMGravityCars>()
	{
		return AGMGravityCars::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AGMGravityCars);
	struct Z_CompiledInDeferFile_FID_MagnetCars_Source_MagnetCars_Public_GMGravityCars_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_MagnetCars_Source_MagnetCars_Public_GMGravityCars_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AGMGravityCars, AGMGravityCars::StaticClass, TEXT("AGMGravityCars"), &Z_Registration_Info_UClass_AGMGravityCars, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AGMGravityCars), 2430817021U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_MagnetCars_Source_MagnetCars_Public_GMGravityCars_h_3467437374(TEXT("/Script/MagnetCars"),
		Z_CompiledInDeferFile_FID_MagnetCars_Source_MagnetCars_Public_GMGravityCars_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_MagnetCars_Source_MagnetCars_Public_GMGravityCars_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
