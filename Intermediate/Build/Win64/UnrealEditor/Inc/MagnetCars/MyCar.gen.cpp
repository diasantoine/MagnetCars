// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MagnetCars/Public/MyCar.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMyCar() {}
// Cross Module References
	MAGNETCARS_API UClass* Z_Construct_UClass_AMyCar_NoRegister();
	MAGNETCARS_API UClass* Z_Construct_UClass_AMyCar();
	ENGINE_API UClass* Z_Construct_UClass_ACharacter();
	UPackage* Z_Construct_UPackage__Script_MagnetCars();
// End Cross Module References
	void AMyCar::StaticRegisterNativesAMyCar()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AMyCar);
	UClass* Z_Construct_UClass_AMyCar_NoRegister()
	{
		return AMyCar::StaticClass();
	}
	struct Z_Construct_UClass_AMyCar_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AMyCar_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ACharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_MagnetCars,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMyCar_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "MyCar.h" },
		{ "ModuleRelativePath", "Public/MyCar.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AMyCar_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMyCar>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AMyCar_Statics::ClassParams = {
		&AMyCar::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AMyCar_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AMyCar_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AMyCar()
	{
		if (!Z_Registration_Info_UClass_AMyCar.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AMyCar.OuterSingleton, Z_Construct_UClass_AMyCar_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AMyCar.OuterSingleton;
	}
	template<> MAGNETCARS_API UClass* StaticClass<AMyCar>()
	{
		return AMyCar::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AMyCar);
	struct Z_CompiledInDeferFile_FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AMyCar, AMyCar::StaticClass, TEXT("AMyCar"), &Z_Registration_Info_UClass_AMyCar, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMyCar), 1113190357U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_3575138519(TEXT("/Script/MagnetCars"),
		Z_CompiledInDeferFile_FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
