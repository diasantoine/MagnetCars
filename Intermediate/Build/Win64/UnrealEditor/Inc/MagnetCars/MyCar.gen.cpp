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
	MAGNETCARS_API UEnum* Z_Construct_UEnum_MagnetCars_EWhichDirection();
	UPackage* Z_Construct_UPackage__Script_MagnetCars();
	MAGNETCARS_API UClass* Z_Construct_UClass_AMyCar_NoRegister();
	MAGNETCARS_API UClass* Z_Construct_UClass_AMyCar();
	ENGINE_API UClass* Z_Construct_UClass_ACharacter();
// End Cross Module References
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_EWhichDirection;
	static UEnum* EWhichDirection_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_EWhichDirection.OuterSingleton)
		{
			Z_Registration_Info_UEnum_EWhichDirection.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_MagnetCars_EWhichDirection, Z_Construct_UPackage__Script_MagnetCars(), TEXT("EWhichDirection"));
		}
		return Z_Registration_Info_UEnum_EWhichDirection.OuterSingleton;
	}
	template<> MAGNETCARS_API UEnum* StaticEnum<EWhichDirection>()
	{
		return EWhichDirection_StaticEnum();
	}
	struct Z_Construct_UEnum_MagnetCars_EWhichDirection_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_MagnetCars_EWhichDirection_Statics::Enumerators[] = {
		{ "ForwardDirection", (int64)ForwardDirection },
		{ "BackwardDirection", (int64)BackwardDirection },
		{ "RightDirection", (int64)RightDirection },
		{ "LeftDirection", (int64)LeftDirection },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_MagnetCars_EWhichDirection_Statics::Enum_MetaDataParams[] = {
		{ "BackwardDirection.Name", "BackwardDirection" },
		{ "BlueprintType", "true" },
		{ "ForwardDirection.Name", "ForwardDirection" },
		{ "LeftDirection.Name", "LeftDirection" },
		{ "ModuleRelativePath", "Public/MyCar.h" },
		{ "RightDirection.Name", "RightDirection" },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_MagnetCars_EWhichDirection_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_MagnetCars,
		nullptr,
		"EWhichDirection",
		"EWhichDirection",
		Z_Construct_UEnum_MagnetCars_EWhichDirection_Statics::Enumerators,
		UE_ARRAY_COUNT(Z_Construct_UEnum_MagnetCars_EWhichDirection_Statics::Enumerators),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::Regular,
		METADATA_PARAMS(Z_Construct_UEnum_MagnetCars_EWhichDirection_Statics::Enum_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UEnum_MagnetCars_EWhichDirection_Statics::Enum_MetaDataParams))
	};
	UEnum* Z_Construct_UEnum_MagnetCars_EWhichDirection()
	{
		if (!Z_Registration_Info_UEnum_EWhichDirection.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EWhichDirection.InnerSingleton, Z_Construct_UEnum_MagnetCars_EWhichDirection_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_EWhichDirection.InnerSingleton;
	}
	DEFINE_FUNCTION(AMyCar::execCarRespawn)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->CarRespawn();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AMyCar::execCarGravity)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->CarGravity();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AMyCar::execCarMovement)
	{
		P_GET_PROPERTY(FByteProperty,Z_Param_Direction);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->CarMovement(EWhichDirection(Z_Param_Direction));
		P_NATIVE_END;
	}
	void AMyCar::StaticRegisterNativesAMyCar()
	{
		UClass* Class = AMyCar::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "CarGravity", &AMyCar::execCarGravity },
			{ "CarMovement", &AMyCar::execCarMovement },
			{ "CarRespawn", &AMyCar::execCarRespawn },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_AMyCar_CarGravity_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AMyCar_CarGravity_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/MyCar.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCar_CarGravity_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AMyCar, nullptr, "CarGravity", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AMyCar_CarGravity_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCar_CarGravity_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AMyCar_CarGravity()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCar_CarGravity_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AMyCar_CarMovement_Statics
	{
		struct MyCar_eventCarMovement_Parms
		{
			TEnumAsByte<EWhichDirection> Direction;
		};
		static const UECodeGen_Private::FBytePropertyParams NewProp_Direction;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_AMyCar_CarMovement_Statics::NewProp_Direction = { "Direction", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(MyCar_eventCarMovement_Parms, Direction), Z_Construct_UEnum_MagnetCars_EWhichDirection, METADATA_PARAMS(nullptr, 0) }; // 94340657
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMyCar_CarMovement_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyCar_CarMovement_Statics::NewProp_Direction,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AMyCar_CarMovement_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/MyCar.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCar_CarMovement_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AMyCar, nullptr, "CarMovement", nullptr, nullptr, sizeof(Z_Construct_UFunction_AMyCar_CarMovement_Statics::MyCar_eventCarMovement_Parms), Z_Construct_UFunction_AMyCar_CarMovement_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCar_CarMovement_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AMyCar_CarMovement_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCar_CarMovement_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AMyCar_CarMovement()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCar_CarMovement_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AMyCar_CarRespawn_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AMyCar_CarRespawn_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/MyCar.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCar_CarRespawn_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AMyCar, nullptr, "CarRespawn", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AMyCar_CarRespawn_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCar_CarRespawn_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AMyCar_CarRespawn()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCar_CarRespawn_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AMyCar);
	UClass* Z_Construct_UClass_AMyCar_NoRegister()
	{
		return AMyCar::StaticClass();
	}
	struct Z_Construct_UClass_AMyCar_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Grounded_MetaData[];
#endif
		static void NewProp_Grounded_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_Grounded;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OnGravity_MetaData[];
#endif
		static void NewProp_OnGravity_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_OnGravity;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_RespawnTiming_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_RespawnTiming;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ContainerRespawnTiming_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_ContainerRespawnTiming;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Acceleration_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_Acceleration;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MaxSpeed_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxSpeed;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AMyCar_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ACharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_MagnetCars,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_AMyCar_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_AMyCar_CarGravity, "CarGravity" }, // 307229539
		{ &Z_Construct_UFunction_AMyCar_CarMovement, "CarMovement" }, // 1155068503
		{ &Z_Construct_UFunction_AMyCar_CarRespawn, "CarRespawn" }, // 3289337858
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMyCar_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "MyCar.h" },
		{ "ModuleRelativePath", "Public/MyCar.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMyCar_Statics::NewProp_Grounded_MetaData[] = {
		{ "Category", "MyCar" },
		{ "ModuleRelativePath", "Public/MyCar.h" },
	};
#endif
	void Z_Construct_UClass_AMyCar_Statics::NewProp_Grounded_SetBit(void* Obj)
	{
		((AMyCar*)Obj)->Grounded = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AMyCar_Statics::NewProp_Grounded = { "Grounded", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(AMyCar), &Z_Construct_UClass_AMyCar_Statics::NewProp_Grounded_SetBit, METADATA_PARAMS(Z_Construct_UClass_AMyCar_Statics::NewProp_Grounded_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AMyCar_Statics::NewProp_Grounded_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMyCar_Statics::NewProp_OnGravity_MetaData[] = {
		{ "Category", "MyCar" },
		{ "ModuleRelativePath", "Public/MyCar.h" },
	};
#endif
	void Z_Construct_UClass_AMyCar_Statics::NewProp_OnGravity_SetBit(void* Obj)
	{
		((AMyCar*)Obj)->OnGravity = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AMyCar_Statics::NewProp_OnGravity = { "OnGravity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(AMyCar), &Z_Construct_UClass_AMyCar_Statics::NewProp_OnGravity_SetBit, METADATA_PARAMS(Z_Construct_UClass_AMyCar_Statics::NewProp_OnGravity_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AMyCar_Statics::NewProp_OnGravity_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMyCar_Statics::NewProp_RespawnTiming_MetaData[] = {
		{ "Category", "MyCar" },
		{ "ModuleRelativePath", "Public/MyCar.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMyCar_Statics::NewProp_RespawnTiming = { "RespawnTiming", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AMyCar, RespawnTiming), METADATA_PARAMS(Z_Construct_UClass_AMyCar_Statics::NewProp_RespawnTiming_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AMyCar_Statics::NewProp_RespawnTiming_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMyCar_Statics::NewProp_ContainerRespawnTiming_MetaData[] = {
		{ "Category", "MyCar" },
		{ "ModuleRelativePath", "Public/MyCar.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMyCar_Statics::NewProp_ContainerRespawnTiming = { "ContainerRespawnTiming", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AMyCar, ContainerRespawnTiming), METADATA_PARAMS(Z_Construct_UClass_AMyCar_Statics::NewProp_ContainerRespawnTiming_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AMyCar_Statics::NewProp_ContainerRespawnTiming_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMyCar_Statics::NewProp_Acceleration_MetaData[] = {
		{ "Category", "MyCar" },
		{ "ModuleRelativePath", "Public/MyCar.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMyCar_Statics::NewProp_Acceleration = { "Acceleration", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AMyCar, Acceleration), METADATA_PARAMS(Z_Construct_UClass_AMyCar_Statics::NewProp_Acceleration_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AMyCar_Statics::NewProp_Acceleration_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMyCar_Statics::NewProp_MaxSpeed_MetaData[] = {
		{ "Category", "MyCar" },
		{ "ModuleRelativePath", "Public/MyCar.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMyCar_Statics::NewProp_MaxSpeed = { "MaxSpeed", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AMyCar, MaxSpeed), METADATA_PARAMS(Z_Construct_UClass_AMyCar_Statics::NewProp_MaxSpeed_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AMyCar_Statics::NewProp_MaxSpeed_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AMyCar_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCar_Statics::NewProp_Grounded,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCar_Statics::NewProp_OnGravity,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCar_Statics::NewProp_RespawnTiming,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCar_Statics::NewProp_ContainerRespawnTiming,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCar_Statics::NewProp_Acceleration,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCar_Statics::NewProp_MaxSpeed,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AMyCar_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMyCar>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AMyCar_Statics::ClassParams = {
		&AMyCar::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_AMyCar_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_AMyCar_Statics::PropPointers),
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
		static const FEnumRegisterCompiledInInfo EnumInfo[];
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FEnumRegisterCompiledInInfo Z_CompiledInDeferFile_FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_Statics::EnumInfo[] = {
		{ EWhichDirection_StaticEnum, TEXT("EWhichDirection"), &Z_Registration_Info_UEnum_EWhichDirection, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 94340657U) },
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AMyCar, AMyCar::StaticClass, TEXT("AMyCar"), &Z_Registration_Info_UClass_AMyCar, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMyCar), 1616294672U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_3635406863(TEXT("/Script/MagnetCars"),
		Z_CompiledInDeferFile_FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_Statics::ClassInfo),
		nullptr, 0,
		Z_CompiledInDeferFile_FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_Statics::EnumInfo));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
