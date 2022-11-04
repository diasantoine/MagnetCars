// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCar.generated.h"

UENUM(BlueprintType)
enum EWhichDirection
{
	VerticalDirection,
	HorizontalDirection
};

USTRUCT(BlueprintType)
struct FCarOld
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Bool")
	bool isGrounded = false;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Bool")
	bool isOnReverseGravity = false;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Respawn")
	float respawnTiming = 2.0f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Respawn")
	float containerRespawnTiming = 2.0f;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Speed")
	float acceleration = 20.f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Speed")
	float maxSpeed = 1000.f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Rotation")
	float amountRotationCar = 20.f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Rotation")
	float maxAmountRotationCar = 90.f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Lean")
	float amountOfLean = 5.f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Lean")
	float maxLean = 45.f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Car Physics")
	float groundFiction = 1000.f;
};

DECLARE_DELEGATE_TwoParams(FDirection,EWhichDirection,float);

UCLASS()
class MAGNETCARS_API AMyCar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCar();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	UFUNCTION(BlueprintCallable)
	void ForwardMovement(float axisValue);
	UFUNCTION(BlueprintCallable)
	void RightMovement(float axisValue);
	UFUNCTION(BlueprintCallable)
	void CarDrift(float value);
	UFUNCTION(BlueprintCallable)
	void CarGravity();
	UFUNCTION(BlueprintCallable)
	void ResetScene();
	UFUNCTION(BlueprintCallable)
	void CarRespawn();
	UFUNCTION(BlueprintCallable)
	void LastPosition(FVector lastPositionReturned, AActor* roadExit);

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FCarOld carStruct;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FVector lastCarPositionOnRoad = FVector::Zero();
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FVector middleOfTheRoad;

private:
	UCharacterMovementComponent* componentMovement;
};
