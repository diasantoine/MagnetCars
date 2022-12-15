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

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Parameter PartCircuit")
	FVector StartPartCircuit = {0,0,0};

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Parameter PartCircuit")
	FVector EndPartCircuit = {0,0,0};

	UFUNCTION(BlueprintCallable)
	void UpdateStartAndEndCircuit(FVector Start, FVector End);
};
