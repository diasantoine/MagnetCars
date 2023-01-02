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

	// Load a new set of map part
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,CallInEditor)
	void LoadMapType();

	// Load the circuit, can be called in the editor
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,CallInEditor)
	void LoadCircuit();

	// UnLoad the circuit, can be called in the editor
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,CallInEditor)
	void UnLoadCircuit();

	// Type Sand circuit
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Load Circuit Parameter")
	TSubclassOf<AMyPartCircuit> PartCircuitTypeSand;
	// Type City circuit
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Load Circuit Parameter")
	TSubclassOf<AMyPartCircuit> PartCircuitTypeCity;
	// Type City circuit
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Load Circuit Parameter")
	TSubclassOf<AMyPartCircuit> PartCircuitTypeInnerCity;
	// Type Inner Canyon circuit
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Load Circuit Parameter")
	TSubclassOf<AMyPartCircuit> PartCircuitTypeCanyon;

	// The order in which the circuit part will be used
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Load Circuit Parameter")
	TArray<TSubclassOf<AMyPartCircuit>> OrderPartCircuit;

	// An array containing the circuit generated
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere, Category = "Load Circuit Parameter")
	TArray<AMyPartCircuit*> PartCircuitGenerated;

	// In Which axis the circuit should be created
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Load Circuit Parameter")
	TEnumAsByte<EAXisAccountedForPlacement> WhichAxisAccounted = XY;

	// The start of the generation
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Load Circuit Parameter")
	FVector FirstPartCircuitPosition = FVector::Zero();

	// The map used for the generation
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Load Circuit Parameter")
	TMap<int,FCircuit> MapCircuit;

	// Last position of the last circuit, used for the generation
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere, Category = "Load Circuit Var")
	USceneComponent* LastEndSceneComponent = nullptr;
};
