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
	TArray<TSubclassOf<AMyPartCircuit>> CircuitPart;
};

UENUM(BlueprintType)
enum EAXisAccountedForPlacement
{
	XYZ,
	XY,
	XZ,
	YZ,
	X,
	Y,
	Z
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

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,CallInEditor)
	void LoadCircuit();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,CallInEditor)
	void UnLoadCircuit();

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere, Category = "Load Circuit Parameter")
	TArray<AMyPartCircuit*> ArrayPartCircuit;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Load Circuit Parameter")
	TEnumAsByte<EAXisAccountedForPlacement> WhichAxisAccounted = XY;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Load Circuit Parameter")
	FVector FirstPartCircuitPosition = FVector::Zero();
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Load Circuit Parameter")
	TMap<int,FCircuit> MapCircuit;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere, Category = "Load Circuit Var")
	FVector LastEndPosition = FVector::Zero();
};
