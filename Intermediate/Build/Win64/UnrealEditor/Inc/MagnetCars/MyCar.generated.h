// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
#ifdef MAGNETCARS_MyCar_generated_h
#error "MyCar.generated.h already included, missing '#pragma once' in MyCar.h"
#endif
#define MAGNETCARS_MyCar_generated_h

#define FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_19_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FCarOld_Statics; \
	MAGNETCARS_API static class UScriptStruct* StaticStruct();


template<> MAGNETCARS_API UScriptStruct* StaticStruct<struct FCarOld>();

#define FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_50_SPARSE_DATA
#define FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_50_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execLastPosition); \
	DECLARE_FUNCTION(execCarRespawn); \
	DECLARE_FUNCTION(execResetScene); \
	DECLARE_FUNCTION(execCarGravity); \
	DECLARE_FUNCTION(execCarDrift); \
	DECLARE_FUNCTION(execRightMovement); \
	DECLARE_FUNCTION(execForwardMovement);


#define FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_50_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execLastPosition); \
	DECLARE_FUNCTION(execCarRespawn); \
	DECLARE_FUNCTION(execResetScene); \
	DECLARE_FUNCTION(execCarGravity); \
	DECLARE_FUNCTION(execCarDrift); \
	DECLARE_FUNCTION(execRightMovement); \
	DECLARE_FUNCTION(execForwardMovement);


#define FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_50_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAMyCar(); \
	friend struct Z_Construct_UClass_AMyCar_Statics; \
public: \
	DECLARE_CLASS(AMyCar, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/MagnetCars"), NO_API) \
	DECLARE_SERIALIZER(AMyCar)


#define FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_50_INCLASS \
private: \
	static void StaticRegisterNativesAMyCar(); \
	friend struct Z_Construct_UClass_AMyCar_Statics; \
public: \
	DECLARE_CLASS(AMyCar, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/MagnetCars"), NO_API) \
	DECLARE_SERIALIZER(AMyCar)


#define FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_50_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AMyCar(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AMyCar) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AMyCar); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AMyCar); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AMyCar(AMyCar&&); \
	NO_API AMyCar(const AMyCar&); \
public:


#define FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_50_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AMyCar(AMyCar&&); \
	NO_API AMyCar(const AMyCar&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AMyCar); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AMyCar); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AMyCar)


#define FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_47_PROLOG
#define FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_50_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_50_SPARSE_DATA \
	FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_50_RPC_WRAPPERS \
	FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_50_INCLASS \
	FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_50_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_50_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_50_SPARSE_DATA \
	FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_50_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_50_INCLASS_NO_PURE_DECLS \
	FID_MagnetCars_Source_MagnetCars_Public_MyCar_h_50_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> MAGNETCARS_API UClass* StaticClass<class AMyCar>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_MagnetCars_Source_MagnetCars_Public_MyCar_h


#define FOREACH_ENUM_EWHICHDIRECTION(op) \
	op(VerticalDirection) \
	op(HorizontalDirection) 
PRAGMA_ENABLE_DEPRECATION_WARNINGS
