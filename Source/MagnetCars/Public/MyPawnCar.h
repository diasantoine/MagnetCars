// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "MyPawnCar.generated.h"

USTRUCT(BlueprintType)
struct FCar
 {
 	GENERATED_BODY()
 	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Bool")
 	bool IsGrounded = false;
 	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Bool")
 	bool IsOnReverseGravity = false;
 	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Respawn")
 	float RespawnTiming = 2.0f;
 	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Respawn")
 	float ContainerRespawnTiming = 2.0f;

 	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Speed")
 	float Acceleration = 20.f;
 	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Speed")
 	float MaxSpeed = 1000.f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Speed")
	float AccelerationNotGrounded = 20.f;
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
 	float GroundFiction = 1000.f;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	float DistanceGround = 0.5f;
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
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	//virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UFUNCTION(BlueprintCallable)
	void ForwardMovement(float axisValue);
	UFUNCTION(BlueprintCallable)
	void RightMovement(float axisValue);
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

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float GravityMultiplier = 500.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float GravityMultiplierWhenInversed = 500.f;
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
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	class UBoxComponent* CarGroundCollision;
};
