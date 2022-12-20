// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LoadCircuit.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "MyPawnCar.generated.h"



UENUM(BlueprintType)
enum EPhysiqueReaction
{
	OutsideCircuit,
	GroundedXYZ,
	GroundedXY,
	GroundedXZ,
	GroundedYZ,
	GroundedX,
	GroundedY,
	GroundedZ,
	Grounded,
	FlyingCircuitXYZ,
	FlyingCircuitXY,
	FlyingCircuitXZ,
	FlyingCircuitYZ,
	FlyingCircuitX,
	FlyingCircuitY,
	FlyingCircuitZ,
	FlyingCircuit
};

USTRUCT(BlueprintType)
struct FCar
 {
 	GENERATED_BODY()
 	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Bool")
 	bool IsGrounded = false;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Bool")
	bool IsLeanCreateRotation = false;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Bool")
	bool IsLeanCreateSlow = false;
 	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Bool")
 	bool IsOnReverseGravity = false;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Bool")
	bool InstantReverseGravity = false;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Bool")
	bool DragWholeBodyWhenLean = true;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Bool")
	bool IsBoosted = true;
 	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Respawn")
 	float RespawnTiming = 2.0f;
 	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Respawn")
 	float ContainerRespawnTiming = 2.0f;

 	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Speed")
 	float Acceleration = 20.f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Speed")
	float AccelerationNotGrounded = 20.f;
 	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Speed")
 	float MaxSpeed = 1000.f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Speed")
	float MaxSpeedWithBoost = 10000.f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Speed")
	float ActualMaxSpeedUnderBoost = 1000.f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Speed")
	float SpeedResetMaxSpeed = 1000.f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Speed")
	float AccelerationLean = 20.f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Speed")
	float AccelerationLeanNotGrounded = 20.f;
	
 	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Rotation")
 	float AmountRotationCar = 20.f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Rotation")
	float AmountRotationCarNotGrounded = 20.f;
 	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Rotation")
 	float MaxAmountRotationCar = 90.f;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Rotation")
	float MinSlopeCar = 5.f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Rotation")
	float SpeedForSlopeAdjustement = 5.f;
	
 	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Lean")
 	float AmountOfLean = 5.f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Lean")
	float SpeedResetLeanGrounded = 50.f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Lean")
	float SpeedResetLeanNotGrounded = 50.f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Lean")
	float AmountOfRotationWithLean = 5.f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Lean")
	float AmountOfLeanNotGrounded = 5.f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Lean")
	float AmountOfLeanToStartSlow = 5.f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Lean")
	float LeanSlowGrounded = 5.f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Lean")
	float LeanSlowAir = 5.f;
 	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Lean")
 	float MaxLean = 45.f;
	
 	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
 	float GroundFriction = 1000.f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	float AngularGroundFriction = 1000.f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	float AirFriction = 1000.f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	float AngularAirFriction = 1000.f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	float CarMassGround = 100.f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	float CarMassNotGrounded = 100.f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	float CarMassGroundInversedGravity = 100.f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	float CarMassNotGroundedInversedGravity = 100.f;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	float DistanceWithTheGround = 200.f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	FVector HalfSizeBoxGroundDetection = FVector(200,200,300);
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	FVector StartBoxGroundDetection = FVector(0,0,100);
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	FVector EndBoxGroundDetection = FVector(0,0,300);
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	bool BoxFollowRotationPitch = false;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	bool BoxFollowRotationYaw = false;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	bool BoxFollowRotationRoll = false;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	TEnumAsByte<EPhysiqueReaction> PhysiqueReactionStatus = EPhysiqueReaction::FlyingCircuit;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	TEnumAsByte<EPhysiqueReaction> PhysiqueReactionGround = EPhysiqueReaction::Grounded;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	TEnumAsByte<EPhysiqueReaction> PhysiqueReactionFly = EPhysiqueReaction::FlyingCircuit;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	TEnumAsByte<EPhysiqueReaction> PhysiqueReactionCollisionEnvironnement = EPhysiqueReaction::FlyingCircuitXY;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	TEnumAsByte<EPhysiqueReaction> PhysiqueReactionCollisionCar = EPhysiqueReaction::FlyingCircuitXY;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	TEnumAsByte<EPhysiqueReaction> PhysiqueReactionOutsideCirtcuit = EPhysiqueReaction::OutsideCircuit;
 };



UCLASS()
class MAGNETCARS_API AMyPawnCar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawnCar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//Notify any physical collision, it will be useful later for behaviour between vehicles collision
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

private: // Private function
	// This function is the physical update of the car, every force should be used there to have the smoothness physics possible
	void PhysicalCarMovement(FPhysScene_Chaos *_PhysScene,float DeltaTime);
public:
	// Get the axis for the forward movement (physical movement)
	UFUNCTION(BlueprintCallable)
	void ForwardMovement(float AxisValue);
	// Get the axis for the rotation movement (local rotation)
	UFUNCTION(BlueprintCallable)
	void RightMovement(float AxisValue);
	// Function which take care of the lean of the vehicles. A force is going to be add to the vehicles depending on the quantity of lean.
	// If the vehicles have too much lean, it will start to slow down
	UFUNCTION(BlueprintCallable)
	void CarDrift(float Value);
	// Simulate gravity behaviour
	UFUNCTION(BlueprintCallable)
	void CarGravity();
	// Simulate invert gravity behaviour
	UFUNCTION(BlueprintCallable)
	void InvertGravity() const;
	// Not finish, it's a special ground which add a boost to the vehicle. During this boost the vehicle can break the max speed
	UFUNCTION(BlueprintCallable)
	void BoostPlate(float Boost);
	// Reset the actual scene (level)
	UFUNCTION(BlueprintCallable)
	void ResetScene();
	// Reset the vehicles to it's start position
	UFUNCTION(BlueprintCallable)
	void CarRespawn();
	// Not finish, it will choose the place where the vehicle should respawn after falling out of the circuit
	UFUNCTION(BlueprintCallable)
	void LastPosition(FVector LastPositionReturned, AActor* RoadExit);
	// This function get the impact normal of the ground detected, it use it to make the car flying at X high
	UFUNCTION(BlueprintCallable)
	void FlyingCar(FHitResult ImpactPoint);
	// Detection Ground with raycast
	UFUNCTION(BlueprintCallable)
	void DetectGround();
	// Detection slope, value which will be used to adjust the rotation of the car since it's not on the ground
	UFUNCTION(BlueprintCallable)
	FRotator DetectSlope(FVector FloorNormal) const;
	// Rotate the car with the new rotation created with the DetectSlope
	UFUNCTION(BlueprintCallable)
	void RotateCarForSlope(FRotator NewRotation);
	// Event trigger once the car got grounded, executed once each ground
	UFUNCTION(BlueprintNativeEvent, Category = "Car Event")
	void CarGotGrounded();
	// Event trigger once the car change gravity
	UFUNCTION(BlueprintNativeEvent, Category = "Car Event")
	void CarReverseGravity();
	// Event trigger once the car fall on another car, but it's not implemented YET
	UFUNCTION(BlueprintNativeEvent, Category = "Car Event")
	void CarFallOnAnotherCar();
	// Event trigger once the car collide with another car
	UFUNCTION(BlueprintNativeEvent, Category = "Car Event")
	void CarCollisionWithAnotherCar();
	// Event trigger once the car collide with another the decor
	UFUNCTION(BlueprintNativeEvent, Category = "Car Event")
	void CarCollisionWithDecor();
	// Event trigger once when the car start to slow because she leaned too much
	UFUNCTION(BlueprintNativeEvent, Category = "Car Event")
	void SlowLeanActivate();
	// Event trigger once when the car take the boost
	UFUNCTION(BlueprintNativeEvent, Category = "Car Event")
	void CarBoost();

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Car Parameter")
	FCar CarStruct;
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Car Parameter")
	UCurveFloat* SpeedCurve;
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Car Parameter")
	UCurveFloat* RotationCurve;
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Car Collision")
	FName CarTag;
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Car Collision")
	FName DecorTag;
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Car Collision")
	FName BoostTag;
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Car Collision")
	float TimeBeforeCarFall = 0.5f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Car Collision")
	float MagneticForceTowardGround = 500.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Car Collision")
	float MagneticForceTowardUp = 500.f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Car Collision")
	TEnumAsByte<ETraceTypeQuery> TraceChannel;
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Car Collision")
	TEnumAsByte<ECollisionChannel> CollisionTraceChannel;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Car Reset")
	FVector ResetPosition = FVector::Zero();
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Car Reset")
	FVector LastCarPositionOnRoad = FVector::Zero();
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Car Reset")
	FVector MiddleOfTheRoad;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Car Bool For Test")
	bool BlockSlope = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Car Bool For Test")
	bool ResetGravityInstant = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Car Bool For Test")
	bool Keyboard = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Car Bool For Test")
    bool CodeInputEnable = true;
	
	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car Component")
	class UBoxComponent* CarCollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car Component")
	class USceneComponent* TemporaryScene;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere, Category = "Car Debug")
	AActor* LastGroundDetected = nullptr;

private:
	float ContainerTimeBeforeCarFall = 0;
	float ContainerAcceleration;
	float ContainerForwardAxis;
	FCalculateCustomPhysics OnCalculateCustomPhysics;// Pour le tick physics
};
