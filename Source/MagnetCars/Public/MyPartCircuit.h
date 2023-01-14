// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "MyPartCircuit.generated.h"

UCLASS()
class MAGNETCARS_API AMyPartCircuit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyPartCircuit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Set Up Finish Line
	UFUNCTION(BlueprintCallable)
	void SetUpLastPart();

	// Set Up a respawn wall at the start of the circuit
	UFUNCTION(BlueprintCallable)
	void SetUpFirstPart();

	// Set Up a respawn wall at the start of the circuit
	UFUNCTION(BlueprintCallable)
	void SetUpHalfCircuit();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Parameter PartCircuit")
	bool IsLastPartCircuit = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Parameter PartCircuit")
	bool IsFirstPartCircuit = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Parameter PartCircuit")
	bool IsHalfCircuit = false;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Parameter PartCircuit")
	float BoostPower = 2000.f;

	// Scene used to create the root component
	UPROPERTY(VisibleAnywhere, Category = "Parameter PartCircuit")
	USceneComponent* NewRootComponent = nullptr;

	// Scene used to get the start of the part of the circuit
	UPROPERTY(VisibleAnywhere, Category = "Parameter PartCircuit")
	USceneComponent* StartPartCircuit = nullptr;

	// Scene used to get the end of the part of the circuit
	UPROPERTY(VisibleAnywhere, Category = "Parameter PartCircuit")
	USceneComponent* EndPartCircuit = nullptr;

	// Scene used to get the end of the part of the circuit
	UPROPERTY(VisibleAnywhere, Category = "Parameter PartCircuit")
	UBoxComponent* TriggerEndPartCircuit = nullptr;

	// Scene used to show we made one lap
	UPROPERTY(VisibleAnywhere, Category = "Parameter PartCircuit")
	UBoxComponent* TriggerOneLap = nullptr;

	// Scene used to stop the player from falling at the first part
	UPROPERTY(VisibleAnywhere, Category = "Parameter PartCircuit")
	UBoxComponent* StopFallFirstPartCircuit = nullptr;
};
