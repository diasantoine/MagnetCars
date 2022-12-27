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
	// Bool which show if we are grounded or not
 	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Bool")
 	bool IsGrounded = false;
	// Bool which permit the car to create rotation during lean
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Bool")
	bool IsLeanCreateRotation = false;
	// Bool which permit the car to be slowed, if the car have too much lean
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Bool")
	bool IsLeanCreateSlow = false;
	// Bool which show if the car is on reverse gravity
 	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Bool")
 	bool IsOnReverseGravity = false;
	// Bool which show if the car can instant reverse his gravity
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Bool")
	bool InstantReverseGravity = false;
	// Bool which show if the car will gain force toward the direction of the lean
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Bool")
	bool DragWholeBodyWhenLean = true;
	// Bool which show if the car is under a boost
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Bool")
	bool IsBoosted = true;
	// Bool which show if the car is under a slow
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Bool")
	bool IsSlowed = true;
	// The time before the respawn of the player
 	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Respawn")
 	float RespawnTiming = 2.0f;
	// The count down before the player respawn (read)
 	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Respawn")
 	float ContainerRespawnTiming = 2.0f;

	// The acceleration added to the player when going forward or backward on ground
 	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Speed")
 	float Acceleration = 20.f;
	// The acceleration added to the player when going forward or backward not on ground
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Speed")
	float AccelerationNotGrounded = 20.f;
	// Boost After Falling On Another Car
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category = "Parameter Boost")
	float PowerBoost = 5000.f;
	// The maximum speed on ground
 	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Speed")
 	float MaxSpeed = 1000.f;
	// The maximum speed with boost
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Speed")
	float MaxSpeedWithBoost = 10000.f;
	// The maximum speed after another car slowed it
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Speed")
	float MaxSpeedAfterSlowFromAnotherCar = 1000.f;
	// The speed used by the MaxSpeed to reset to his normal state after a slow
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Speed")
	float SpeedResetMaxSpeedAfterSlow = 1000.f;
	// The actual maximum speed after a boost going back to the normal MaxSpeed
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Speed")
	float ActualMaxSpeedUnderEffect = 1000.f;
	// The actual maximum speed after a slow going back to the normal MaxSpeed
	// The speed used by the MaxSpeed to reset to his normal state after a boost
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Speed")
	float SpeedResetMaxSpeedAfterBoost = 1000.f;
	// The acceleration added to the player by the lean grounded
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Speed")
	float AccelerationLean = 20.f;
	// The acceleration added to the player by the lean not grounded
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Speed")
	float AccelerationLeanNotGrounded = 20.f;

	// The amount of rotation the car get with the axis of rotation grounded
 	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Rotation")
 	float AmountRotationCar = 20.f;
	// The amount of rotation the car get with the axis of rotation not grounded
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Rotation")
	float AmountRotationCarNotGrounded = 20.f;
	// The maximum rotation the car can get (positive or negative)
 	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Rotation")
 	float MaxAmountRotationCar = 90.f;

	// The adjustment of the rotation of the car with the slope of the circuit
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Rotation")
	float SpeedForSlopeAdjustement = 5.f;

	// The amount of lean
 	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Lean")
 	float AmountOfLean = 5.f;
	// The speed to get back at 0 rotation Grounded
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Lean")
	float SpeedResetLeanGrounded = 50.f;
	// The speed to get back at 0 rotation Not Grounded
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Lean")
	float SpeedResetLeanNotGrounded = 50.f;
	// The amount of rotation adjusted by the amount of lean grounded
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Lean")
	float AmountOfRotationWithLean = 5.f;
	// The amount of rotation adjusted by the amount of lean not grounded
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Lean")
	float AmountOfLeanNotGrounded = 5.f;
	// The amount of rotation needed to make the car start to slow
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Lean")
	float AmountOfLeanToStartSlow = 5.f;
	// The amount of slow on ground
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Lean")
	float LeanSlowGrounded = 5.f;
	// The amount of slow on not grounded
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Lean")
	float LeanSlowAir = 5.f;
	// The max lean
 	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Lean")
 	float MaxLean = 45.f;

	// The ground friction which update the linear damping
 	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
 	float GroundFriction = 1000.f;
	// The ground friction which update the angular damping
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	float AngularGroundFriction = 1000.f;
	// The air friction which update the linear damping
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	float AirFriction = 1000.f;
	// The air friction which update the angular damping
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	float AngularAirFriction = 1000.f;
	// The mass of the vehicle which augment the gravity aswell on ground
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	float CarMassGround = 100.f;
	// The mass of the vehicle which augment the gravity aswell not grounded
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	float CarMassNotGrounded = 100.f;
	// The mass of the vehicle which augment the gravity aswell on ground if the car is on Inversed Gravity
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	float CarMassGroundInversedGravity = 100.f;
	// The mass of the vehicle which augment the gravity aswell on not grounde if the car is on Inversed Gravity
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	float CarMassNotGroundedInversedGravity = 100.f;

	// The distance between the car and the ground
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	float DistanceWithTheGround = 200.f;
	// Half size of the box which is used to detect the ground
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	FVector HalfSizeBoxGroundDetection = FVector(200,200,300);
	// Start position of the box which is used to detect the ground
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	FVector StartBoxGroundDetection = FVector(0,0,100);
	// End position of the box which is used to detect the ground
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	FVector EndBoxGroundDetection = FVector(0,0,300);
	// Parameter which permit or not the box to follow the pitch of the player
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	bool BoxFollowRotationPitch = false;
	// Parameter which permit or not the box to follow the Yaw of the player
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	bool BoxFollowRotationYaw = false;
	// Parameter which permit or not the box to follow the Roll of the player
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	bool BoxFollowRotationRoll = false;
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
	//Notify any Overlap on the Up Collision
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	//Notify end Overlap on the Up Collision
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

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
	// Behaviour after a car fall on the player
	UFUNCTION(BlueprintCallable)
	void CarFellOnMe(AMyPawnCar* CarHitting);
	// it's a special ground which add a boost to the vehicle. During this boost the vehicle can break the max speed
	UFUNCTION(BlueprintCallable)
	void BoostPlate(float Boost, bool Forward);
	// It's the function which reset the max speed to it's normal state after a boost
	UFUNCTION(BlueprintCallable)
	void BoostSpeedBehaviour();
	// It's the function which reset the max speed to it's normal state after a slow
	UFUNCTION(BlueprintCallable)
	void SlowSpeedBehaviour();
	// This function could be useful or not to back up the vehicle after a collision to a normal rotation
	UFUNCTION(BlueprintCallable)
	void ResetRotationAfterCrash();
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
	// Event trigger once the car fall on another car
	UFUNCTION(BlueprintNativeEvent, Category = "Car Event")
	void CarFallOnAnotherCar(AMyPawnCar* CarHit);
	// Event trigger once the car have another car falling on it
	UFUNCTION(BlueprintNativeEvent, Category = "Car Event")
	void CarFellOnMeEvent();
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

	// Structure for the preset of parameter for the car
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Car Parameter")
	FCar CarStruct;
	// Curve for speed
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Car Parameter")
	UCurveFloat* SpeedCurve;
	// Curve for Rotation
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Car Parameter")
	UCurveFloat* RotationCurve;
	// Car Tag for collision
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Car Collision")
	FName CarTag;
	// Decor Tag for collision
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Car Collision")
	FName DecorTag;
	// Boost Tag for collision
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Car Collision")
	FName BoostTag;
	// The time before the system detect the car is falling (not used)
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Car Collision")
	float TimeBeforeCarFall = 0.5f;
	// Channel for the raycast
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Car Collision")
	TEnumAsByte<ETraceTypeQuery> TraceChannel;
	// Collision Channel for the raycast
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Car Collision")
	TEnumAsByte<ECollisionChannel> CollisionTraceChannel;
	// Position where the player restart with the button
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Car Reset")
	FVector ResetPosition = FVector::Zero();
	// Position where the player respawn (not used)
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Car Reset")
	FVector LastCarPositionOnRoad = FVector::Zero();
	// Position where the player respawn (not used)
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Car Reset")
	FVector MiddleOfTheRoad;
	// Bool which block the rotation of the car on the slope of the circuit
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Car Bool For Test")
	bool BlockSlope = true;
	// Bool which will swap the gravity instant, no smoothness
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Car Bool For Test")
	bool ResetGravityInstant = false;
	// Bool which block the input of the keyboard to block some weird behaviour with the gamepad (not useful)
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Car Bool For Test")
	bool Keyboard = false;
	// Bool which block the input in the c++ for the network
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Car Bool For Test")
    bool CodeInputEnable = true;
	
	
	// Car collider
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car Component")
	class UBoxComponent* CarCollision;
	// Car collider Up
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car Component")
	class UBoxComponent* CarCollisionUp;
	// Temporary scene to make the car rotate
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car Component")
	class USceneComponent* TemporaryScene;
	UPROPERTY(VisibleAnywhere, Category = "Car Component")
	USceneComponent* RaycastPosition = nullptr;
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Car Component")
	float DistanceRaycast = 200.f;
	// Show which aactor was hit last for the ground
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere, Category = "Car Debug")
	AActor* LastGroundDetected = nullptr;

private:
	// Not used
	float ContainerTimeBeforeCarFall = 0;
	// Contain acceleration
	float ContainerAcceleration;
	// Forward Axis
	float ContainerForwardAxis;
	// Pour le tick physics
	FCalculateCustomPhysics OnCalculateCustomPhysics;
};
