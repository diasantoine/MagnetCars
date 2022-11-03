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
	MAGNETCARS_API UScriptStruct* Z_Construct_UScriptStruct_FCar();
	MAGNETCARS_API UClass* Z_Construct_UClass_AMyCar_NoRegister();
	MAGNETCARS_API UClass* Z_Construct_UClass_AMyCar();
	ENGINE_API UClass* Z_Construct_UClass_ACharacter();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
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
		{ "VerticalDirection", (int64)VerticalDirection },
		{ "HorizontalDirection", (int64)HorizontalDirection },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_MagnetCars_EWhichDirection_Statics::Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "HorizontalDirection.Name", "HorizontalDirection" },
		{ "ModuleRelativePath", "Public/MyCar.h" },
		{ "VerticalDirection.Name", "VerticalDirection" },
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
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_Car;
class UScriptStruct* FCar::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_Car.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_Car.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FCar, Z_Construct_UPackage__Script_MagnetCars(), TEXT("Car"));
	}
	return Z_Registration_Info_UScriptStruct_Car.OuterSingleton;
}
template<> MAGNETCARS_API UScriptStruct* StaticStruct<FCar>()
{
	return FCar::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FCar_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_isGrounded_MetaData[];
#endif
		static void NewProp_isGrounded_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_isGrounded;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_isOnReverseGravity_MetaData[];
#endif
		static void NewProp_isOnReverseGravity_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_isOnReverseGravity;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_respawnTiming_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_respawnTiming;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_containerRespawnTiming_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_containerRespawnTiming;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_acceleration_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_acceleration;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_maxSpeed_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_maxSpeed;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_amountRotationCar_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_amountRotationCar;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_maxAmountRotationCar_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_maxAmountRotationCar;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_amountOfLean_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_amountOfLean;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_maxLean_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_maxLean;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_groundFiction_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_groundFiction;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCar_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/MyCar.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FCar_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FCar>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCar_Statics::NewProp_isGrounded_MetaData[] = {
		{ "Category", "Car Bool" },
		{ "ModuleRelativePath", "Public/MyCar.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FCar_Statics::NewProp_isGrounded_SetBit(void* Obj)
	{
		((FCar*)Obj)->isGrounded = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FCar_Statics::NewProp_isGrounded = { "isGrounded", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FCar), &Z_Construct_UScriptStruct_FCar_Statics::NewProp_isGrounded_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FCar_Statics::NewProp_isGrounded_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCar_Statics::NewProp_isGrounded_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCar_Statics::NewProp_isOnReverseGravity_MetaData[] = {
		{ "Category", "Car Bool" },
		{ "ModuleRelativePath", "Public/MyCar.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FCar_Statics::NewProp_isOnReverseGravity_SetBit(void* Obj)
	{
		((FCar*)Obj)->isOnReverseGravity = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FCar_Statics::NewProp_isOnReverseGravity = { "isOnReverseGravity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FCar), &Z_Construct_UScriptStruct_FCar_Statics::NewProp_isOnReverseGravity_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FCar_Statics::NewProp_isOnReverseGravity_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCar_Statics::NewProp_isOnReverseGravity_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCar_Statics::NewProp_respawnTiming_MetaData[] = {
		{ "Category", "Car Respawn" },
		{ "ModuleRelativePath", "Public/MyCar.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FCar_Statics::NewProp_respawnTiming = { "respawnTiming", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FCar, respawnTiming), METADATA_PARAMS(Z_Construct_UScriptStruct_FCar_Statics::NewProp_respawnTiming_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCar_Statics::NewProp_respawnTiming_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCar_Statics::NewProp_containerRespawnTiming_MetaData[] = {
		{ "Category", "Car Respawn" },
		{ "ModuleRelativePath", "Public/MyCar.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FCar_Statics::NewProp_containerRespawnTiming = { "containerRespawnTiming", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FCar, containerRespawnTiming), METADATA_PARAMS(Z_Construct_UScriptStruct_FCar_Statics::NewProp_containerRespawnTiming_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCar_Statics::NewProp_containerRespawnTiming_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCar_Statics::NewProp_acceleration_MetaData[] = {
		{ "Category", "Car Speed" },
		{ "ModuleRelativePath", "Public/MyCar.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FCar_Statics::NewProp_acceleration = { "acceleration", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FCar, acceleration), METADATA_PARAMS(Z_Construct_UScriptStruct_FCar_Statics::NewProp_acceleration_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCar_Statics::NewProp_acceleration_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCar_Statics::NewProp_maxSpeed_MetaData[] = {
		{ "Category", "Car Speed" },
		{ "ModuleRelativePath", "Public/MyCar.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FCar_Statics::NewProp_maxSpeed = { "maxSpeed", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FCar, maxSpeed), METADATA_PARAMS(Z_Construct_UScriptStruct_FCar_Statics::NewProp_maxSpeed_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCar_Statics::NewProp_maxSpeed_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCar_Statics::NewProp_amountRotationCar_MetaData[] = {
		{ "Category", "Car Rotation" },
		{ "ModuleRelativePath", "Public/MyCar.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FCar_Statics::NewProp_amountRotationCar = { "amountRotationCar", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FCar, amountRotationCar), METADATA_PARAMS(Z_Construct_UScriptStruct_FCar_Statics::NewProp_amountRotationCar_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCar_Statics::NewProp_amountRotationCar_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCar_Statics::NewProp_maxAmountRotationCar_MetaData[] = {
		{ "Category", "Car Rotation" },
		{ "ModuleRelativePath", "Public/MyCar.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FCar_Statics::NewProp_maxAmountRotationCar = { "maxAmountRotationCar", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FCar, maxAmountRotationCar), METADATA_PARAMS(Z_Construct_UScriptStruct_FCar_Statics::NewProp_maxAmountRotationCar_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCar_Statics::NewProp_maxAmountRotationCar_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCar_Statics::NewProp_amountOfLean_MetaData[] = {
		{ "Category", "Car Lean" },
		{ "ModuleRelativePath", "Public/MyCar.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FCar_Statics::NewProp_amountOfLean = { "amountOfLean", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FCar, amountOfLean), METADATA_PARAMS(Z_Construct_UScriptStruct_FCar_Statics::NewProp_amountOfLean_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCar_Statics::NewProp_amountOfLean_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCar_Statics::NewProp_maxLean_MetaData[] = {
		{ "Category", "Car Lean" },
		{ "ModuleRelativePath", "Public/MyCar.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FCar_Statics::NewProp_maxLean = { "maxLean", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FCar, maxLean), METADATA_PARAMS(Z_Construct_UScriptStruct_FCar_Statics::NewProp_maxLean_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCar_Statics::NewProp_maxLean_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCar_Statics::NewProp_groundFiction_MetaData[] = {
		{ "Category", "Car Physics" },
		{ "ModuleRelativePath", "Public/MyCar.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FCar_Statics::NewProp_groundFiction = { "groundFiction", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FCar, groundFiction), METADATA_PARAMS(Z_Construct_UScriptStruct_FCar_Statics::NewProp_groundFiction_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCar_Statics::NewProp_groundFiction_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FCar_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCar_Statics::NewProp_isGrounded,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCar_Statics::NewProp_isOnReverseGravity,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCar_Statics::NewProp_respawnTiming,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCar_Statics::NewProp_containerRespawnTiming,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCar_Statics::NewProp_acceleration,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCar_Statics::NewProp_maxSpeed,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCar_Statics::NewProp_amountRotationCar,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCar_Statics::NewProp_maxAmountRotationCar,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCar_Statics::NewProp_amountOfLean,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCar_Statics::NewProp_maxLean,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCar_Statics::NewProp_groundFiction,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FCar_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_MagnetCars,
		nullptr,
		&NewStructOps,
		"Car",
		sizeof(FCar),
		alignof(FCar),
		Z_Construct_UScriptStruct_FCar_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCar_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FCar_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCar_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FCar()
	{
		if (!Z_Registration_Info_UScriptStruct_Car.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_Car.InnerSingleton, Z_Construct_UScriptStruct_FCar_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_Car.InnerSingleton;
	}
	DEFINE_FUNCTION(AMyCar::execLastPosition)
	{
		P_GET_STRUCT(FVector,Z_Param_lastPositionReturned);
		P_GET_OBJECT(AActor,Z_Param_roadExit);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->LastPosition(Z_Param_lastPositionReturned,Z_Param_roadExit);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AMyCar::execCarRespawn)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->CarRespawn();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AMyCar::execResetScene)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->ResetScene();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AMyCar::execCarGravity)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->CarGravity();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AMyCar::execCarDrift)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_value);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->CarDrift(Z_Param_value);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AMyCar::execRightMovement)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_axisValue);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->RightMovement(Z_Param_axisValue);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AMyCar::execForwardMovement)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_axisValue);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->ForwardMovement(Z_Param_axisValue);
		P_NATIVE_END;
	}
	void AMyCar::StaticRegisterNativesAMyCar()
	{
		UClass* Class = AMyCar::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "CarDrift", &AMyCar::execCarDrift },
			{ "CarGravity", &AMyCar::execCarGravity },
			{ "CarRespawn", &AMyCar::execCarRespawn },
			{ "ForwardMovement", &AMyCar::execForwardMovement },
			{ "LastPosition", &AMyCar::execLastPosition },
			{ "ResetScene", &AMyCar::execResetScene },
			{ "RightMovement", &AMyCar::execRightMovement },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_AMyCar_CarDrift_Statics
	{
		struct MyCar_eventCarDrift_Parms
		{
			float value;
		};
		static const UECodeGen_Private::FFloatPropertyParams NewProp_value;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AMyCar_CarDrift_Statics::NewProp_value = { "value", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(MyCar_eventCarDrift_Parms, value), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMyCar_CarDrift_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyCar_CarDrift_Statics::NewProp_value,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AMyCar_CarDrift_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/MyCar.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCar_CarDrift_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AMyCar, nullptr, "CarDrift", nullptr, nullptr, sizeof(Z_Construct_UFunction_AMyCar_CarDrift_Statics::MyCar_eventCarDrift_Parms), Z_Construct_UFunction_AMyCar_CarDrift_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCar_CarDrift_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AMyCar_CarDrift_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCar_CarDrift_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AMyCar_CarDrift()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCar_CarDrift_Statics::FuncParams);
		}
		return ReturnFunction;
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
	struct Z_Construct_UFunction_AMyCar_ForwardMovement_Statics
	{
		struct MyCar_eventForwardMovement_Parms
		{
			float axisValue;
		};
		static const UECodeGen_Private::FFloatPropertyParams NewProp_axisValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AMyCar_ForwardMovement_Statics::NewProp_axisValue = { "axisValue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(MyCar_eventForwardMovement_Parms, axisValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMyCar_ForwardMovement_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyCar_ForwardMovement_Statics::NewProp_axisValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AMyCar_ForwardMovement_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/MyCar.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCar_ForwardMovement_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AMyCar, nullptr, "ForwardMovement", nullptr, nullptr, sizeof(Z_Construct_UFunction_AMyCar_ForwardMovement_Statics::MyCar_eventForwardMovement_Parms), Z_Construct_UFunction_AMyCar_ForwardMovement_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCar_ForwardMovement_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AMyCar_ForwardMovement_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCar_ForwardMovement_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AMyCar_ForwardMovement()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCar_ForwardMovement_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AMyCar_LastPosition_Statics
	{
		struct MyCar_eventLastPosition_Parms
		{
			FVector lastPositionReturned;
			AActor* roadExit;
		};
		static const UECodeGen_Private::FStructPropertyParams NewProp_lastPositionReturned;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_roadExit;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AMyCar_LastPosition_Statics::NewProp_lastPositionReturned = { "lastPositionReturned", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(MyCar_eventLastPosition_Parms, lastPositionReturned), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AMyCar_LastPosition_Statics::NewProp_roadExit = { "roadExit", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(MyCar_eventLastPosition_Parms, roadExit), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMyCar_LastPosition_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyCar_LastPosition_Statics::NewProp_lastPositionReturned,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyCar_LastPosition_Statics::NewProp_roadExit,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AMyCar_LastPosition_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/MyCar.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCar_LastPosition_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AMyCar, nullptr, "LastPosition", nullptr, nullptr, sizeof(Z_Construct_UFunction_AMyCar_LastPosition_Statics::MyCar_eventLastPosition_Parms), Z_Construct_UFunction_AMyCar_LastPosition_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCar_LastPosition_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04820401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AMyCar_LastPosition_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCar_LastPosition_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AMyCar_LastPosition()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCar_LastPosition_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AMyCar_ResetScene_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AMyCar_ResetScene_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/MyCar.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCar_ResetScene_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AMyCar, nullptr, "ResetScene", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AMyCar_ResetScene_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCar_ResetScene_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AMyCar_ResetScene()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCar_ResetScene_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AMyCar_RightMovement_Statics
	{
		struct MyCar_eventRightMovement_Parms
		{
			float axisValue;
		};
		static const UECodeGen_Private::FFloatPropertyParams NewProp_axisValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AMyCar_RightMovement_Statics::NewProp_axisValue = { "axisValue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(MyCar_eventRightMovement_Parms, axisValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMyCar_RightMovement_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyCar_RightMovement_Statics::NewProp_axisValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AMyCar_RightMovement_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/MyCar.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCar_RightMovement_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AMyCar, nullptr, "RightMovement", nullptr, nullptr, sizeof(Z_Construct_UFunction_AMyCar_RightMovement_Statics::MyCar_eventRightMovement_Parms), Z_Construct_UFunction_AMyCar_RightMovement_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCar_RightMovement_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AMyCar_RightMovement_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCar_RightMovement_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AMyCar_RightMovement()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCar_RightMovement_Statics::FuncParams);
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
		static const UECodeGen_Private::FMetaDataPairParam NewProp_carStruct_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_carStruct;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_lastCarPositionOnRoad_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_lastCarPositionOnRoad;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_middleOfTheRoad_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_middleOfTheRoad;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AMyCar_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ACharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_MagnetCars,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_AMyCar_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_AMyCar_CarDrift, "CarDrift" }, // 3574860688
		{ &Z_Construct_UFunction_AMyCar_CarGravity, "CarGravity" }, // 307229539
		{ &Z_Construct_UFunction_AMyCar_CarRespawn, "CarRespawn" }, // 3289337858
		{ &Z_Construct_UFunction_AMyCar_ForwardMovement, "ForwardMovement" }, // 1472687407
		{ &Z_Construct_UFunction_AMyCar_LastPosition, "LastPosition" }, // 345743193
		{ &Z_Construct_UFunction_AMyCar_ResetScene, "ResetScene" }, // 4204734250
		{ &Z_Construct_UFunction_AMyCar_RightMovement, "RightMovement" }, // 1859946717
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMyCar_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "MyCar.h" },
		{ "ModuleRelativePath", "Public/MyCar.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMyCar_Statics::NewProp_carStruct_MetaData[] = {
		{ "Category", "MyCar" },
		{ "ModuleRelativePath", "Public/MyCar.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AMyCar_Statics::NewProp_carStruct = { "carStruct", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AMyCar, carStruct), Z_Construct_UScriptStruct_FCar, METADATA_PARAMS(Z_Construct_UClass_AMyCar_Statics::NewProp_carStruct_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AMyCar_Statics::NewProp_carStruct_MetaData)) }; // 1044547513
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMyCar_Statics::NewProp_lastCarPositionOnRoad_MetaData[] = {
		{ "Category", "MyCar" },
		{ "ModuleRelativePath", "Public/MyCar.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AMyCar_Statics::NewProp_lastCarPositionOnRoad = { "lastCarPositionOnRoad", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AMyCar, lastCarPositionOnRoad), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UClass_AMyCar_Statics::NewProp_lastCarPositionOnRoad_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AMyCar_Statics::NewProp_lastCarPositionOnRoad_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMyCar_Statics::NewProp_middleOfTheRoad_MetaData[] = {
		{ "Category", "MyCar" },
		{ "ModuleRelativePath", "Public/MyCar.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AMyCar_Statics::NewProp_middleOfTheRoad = { "middleOfTheRoad", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AMyCar, middleOfTheRoad), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UClass_AMyCar_Statics::NewProp_middleOfTheRoad_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AMyCar_Statics::NewProp_middleOfTheRoad_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AMyCar_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCar_Statics::NewProp_carStruct,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCar_Statics::NewProp_lastCarPositionOnRoad,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCar_Statics::NewProp_middleOfTheRoad,
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
		static const FStructRegisterCompiledInInfo ScriptStructInfo[];
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FEnumRegisterCompiledInInfo Z_CompiledInDeferFile_FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_Statics::EnumInfo[] = {
		{ EWhichDirection_StaticEnum, TEXT("EWhichDirection"), &Z_Registration_Info_UEnum_EWhichDirection, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2455543830U) },
	};
	const FStructRegisterCompiledInInfo Z_CompiledInDeferFile_FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_Statics::ScriptStructInfo[] = {
		{ FCar::StaticStruct, Z_Construct_UScriptStruct_FCar_Statics::NewStructOps, TEXT("Car"), &Z_Registration_Info_UScriptStruct_Car, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FCar), 1044547513U) },
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AMyCar, AMyCar::StaticClass, TEXT("AMyCar"), &Z_Registration_Info_UClass_AMyCar, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMyCar), 3039635580U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_1613209231(TEXT("/Script/MagnetCars"),
		Z_CompiledInDeferFile_FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_Statics::ClassInfo),
		Z_CompiledInDeferFile_FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_Statics::ScriptStructInfo),
		Z_CompiledInDeferFile_FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_Statics::EnumInfo));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
