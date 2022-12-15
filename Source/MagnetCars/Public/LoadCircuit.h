// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyPartCircuit.h"
#include "GameFramework/Actor.h"
#include "LoadCircuit.generated.h"

USTRUCT(BlueprintType)
struct FCircuit
{
	GENERATED_BODY();
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Circuit Construction")
	TArray<AMyPartCircuit*> CircuitPart;
};

UCLASS()
class MAGNETCARS_API ALoadCircuit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALoadCircuit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void LoadCircuit();

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TMap<int,FCircuit> MapCircuit;
};
