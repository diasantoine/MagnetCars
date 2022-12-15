// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	UPROPERTY(VisibleAnywhere, Category = "Parameter PartCircuit")
	USceneComponent* NewRootComponent = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = "Parameter PartCircuit")
	USceneComponent* StartPartCircuit = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Parameter PartCircuit")
	USceneComponent* EndPartCircuit = nullptr;
};
