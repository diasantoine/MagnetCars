// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
 	bool IsOnReverseGravity = false;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Bool")
	bool InstantReverseGravity = false;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Bool")
	bool DragWholeBodyWhenLean = true;
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
	float AccelerationLean = 20.f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Speed")
	float AccelerationLeanNotGrounded = 20.f;
	
 	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Rotation")
 	float AmountRotationCar = 20.f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Rotation")
	float AmountRotationCarNotGrounded = 20.f;
 	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Rotation")
 	float MaxAmountRotationCar = 90.f;
	
 	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Lean")
 	float AmountOfLean = 5.f;
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
	float CarMass = 100.f;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	float MinDistanceWithTheGround = 50.f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	FVector HalfSizeBoxGroundDetection = FVector(50,50,50);
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	FVector StartBoxGroundDetection = FVector(0,0,100);
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	FVector EndBoxGroundDetection = FVector(0,0,100);
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
	//virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	/*virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;*/

	UFUNCTION(BlueprintCallable)
	void ForwardMovement(float axisValue);
	UFUNCTION(BlueprintCallable)
	void RightMovement(float axisValue);
	UFUNCTION(BlueprintCallable)
	void CarPhysiqueReaction(EPhysiqueReaction WhichPhysique);
	UFUNCTION(BlueprintCallable)
	void CarDrift(float value);
	UFUNCTION(BlueprintCallable)
	void CarGravity();
	UFUNCTION(BlueprintCallable)
	void InvertGravity();
	UFUNCTION(BlueprintCallable)
	void ResetScene();
	UFUNCTION(BlueprintCallable)
	void CarRespawn();
	UFUNCTION(BlueprintCallable)
	void LastPosition(FVector lastPositionReturned, AActor* roadExit);
	UFUNCTION(BlueprintCallable)
	void FlyingCar(float lowestZ);
	UFUNCTION(BlueprintCallable)
	void DetectGround();
	UFUNCTION(BlueprintCallable)
	void CarFall(float DeltaTime);

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<AActor*> ArrayOfGround;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float TimeBeforeCarFall = 0.5f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MagneticForce = 500.f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FCar CarStruct;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FVector LastCarPositionOnRoad = FVector::Zero();
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FVector MiddleOfTheRoad;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float LastZValue = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UBoxComponent* CarCollision;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class USceneComponent* TemporaryScene;
/*	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	class UBoxComponent* CarGroundCollision;*/

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TEnumAsByte<ETraceTypeQuery> TraceChannel;

private:
	float ContainerTimeBeforeCarFall = 0;
	bool first = false;
	FVector Velocity;
};
