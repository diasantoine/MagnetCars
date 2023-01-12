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

	UFUNCTION(BlueprintCallable)
	void SetUpLastPart();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Parameter PartCircuit")
	bool IsLastPartCircuit = false;
	
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
};
