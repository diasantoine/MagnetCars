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

	UFUNCTION(BlueprintCallable)
	void CarMovement(FVector newInputDirection);
	UFUNCTION(BlueprintCallable)
	void ForwardMovement(float axisValue);
	UFUNCTION(BlueprintCallable)
	void BackwardMovement(float axisValue);
	UFUNCTION(BlueprintCallable)
	void LeftMovement(float axisValue);
	UFUNCTION(BlueprintCallable)
	void RightMovement(float axisValue);
	UFUNCTION(BlueprintCallable)
	void CarDrift(float value);
	UFUNCTION(BlueprintCallable)
	void CarGravity();
	UFUNCTION(BlueprintCallable)
	void CarRespawn();

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool isGrounded = false;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool isOnReverseGravity = false;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float respawnTiming = 2.0f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float containerRespawnTiming = 2.0f;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float acceleration = 20.f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float maxSpeed = 1000.f;

private:
	UCharacterMovementComponent* componentMovement;
};
