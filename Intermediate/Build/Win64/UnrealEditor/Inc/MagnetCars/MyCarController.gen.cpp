// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MagnetCars/Public/MyCarController.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMyCarController() {}
// Cross Module References
	MAGNETCARS_API UClass* Z_Construct_UClass_AMyCarController_NoRegister();
	MAGNETCARS_API UClass* Z_Construct_UClass_AMyCarController();
	ENGINE_API UClass* Z_Construct_UClass_APlayerController();
	UPackage* Z_Construct_UPackage__Script_MagnetCars();
// End Cross Module References
	void AMyCarController::StaticRegisterNativesAMyCarController()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AMyCarController);
	UClass* Z_Construct_UClass_AMyCarController_NoRegister()
	{
		return AMyCarController::StaticClass();
	}
	struct Z_Construct_UClass_AMyCarController_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AMyCarController_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APlayerController,
		(UObject* (*)())Z_Construct_UPackage__Script_MagnetCars,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMyCarController_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "MyCarController.h" },
		{ "ModuleRelativePath", "Public/MyCarController.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AMyCarController_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMyCarController>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AMyCarController_Statics::ClassParams = {
		&AMyCarController::StaticClass,
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
		0x009002A4u,
		METADATA_PARAMS(Z_Construct_UClass_AMyCarController_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AMyCarController_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AMyCarController()
	{
		if (!Z_Registration_Info_UClass_AMyCarController.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AMyCarController.OuterSingleton, Z_Construct_UClass_AMyCarController_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AMyCarController.OuterSingleton;
	}
	template<> MAGNETCARS_API UClass* StaticClass<AMyCarController>()
	{
		return AMyCarController::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AMyCarController);
	struct Z_CompiledInDeferFile_FID_MagnetCars_Source_MagnetCars_Public_MyCarController_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_MagnetCars_Source_MagnetCars_Public_MyCarController_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AMyCarController, AMyCarController::StaticClass, TEXT("AMyCarController"), &Z_Registration_Info_UClass_AMyCarController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMyCarController), 2065435194U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_MagnetCars_Source_MagnetCars_Public_MyCarController_h_2374790395(TEXT("/Script/MagnetCars"),
		Z_CompiledInDeferFile_FID_MagnetCars_Source_MagnetCars_Public_MyCarController_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_MagnetCars_Source_MagnetCars_Public_MyCarController_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
