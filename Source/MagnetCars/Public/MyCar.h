// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCar.generated.h"

UENUM(BlueprintType)
enum EWhichDirection
{
	ForwardDirection,
	BackwardDirection,
	RightDirection,
	LeftDirection
};
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
	void CarMovement(EWhichDirection Direction);
	UFUNCTION(BlueprintCallable)
	void CarGravity();
	UFUNCTION(BlueprintCallable)
	void CarRespawn();

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool Grounded = false;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool OnGravity = false;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float RespawnTiming = 2.0f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float ContainerRespawnTiming = 2.0f;
};
