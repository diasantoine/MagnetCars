// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LoadCircuit.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "WidgetChoiceMap.generated.h"

/**
 * 
 */

UENUM()
enum ETypeOfPartCircuitWidget
{
	Sand,
	City,
	InnerCity,
	Canyon
};
UCLASS()
class MAGNETCARS_API UWidgetChoiceMap : public UUserWidget
{
	GENERATED_BODY()
public:
	// Button choice part one
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta = (BindWidget))
	UButton* MapChoice1;
	// Button choice part two
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta = (BindWidget))
	UButton* MapChoice2;
	// Button choice part three
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta = (BindWidget))
	UButton* MapChoice3;
	// Button choice part four
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta = (BindWidget))
	UButton* MapChoice4;

	// Button to start the generation
	UPROPERTY(EditAnywhere,BlueprintReadOnly, meta = (BindWidget))
	UButton* MapGeneration;

	// Blueprint which create the circuit
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ALoadCircuit* LoadCircuit = nullptr;

	// Color of the Canyon
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FLinearColor CanyonPartCirtcuit = FLinearColor::White;
	// Color of the Sand
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FLinearColor SandPartCirtcuit = FLinearColor::Yellow;
	// Color of the City
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FLinearColor CityPartCirtcuit = FLinearColor::Black;
	// Color of the Inner City
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FLinearColor InnerCityPartCirtcuit = FLinearColor::Gray;

	// Randomize the map generation
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool RandomMap = false;
	// Randomize which part of the circuit the player can modify
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool RandomPartForPlayer = false;

	// Type of circuit
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TEnumAsByte<ETypeOfPartCircuitWidget> WhichBasePartCircuit = Sand;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int WhichPartYouCanModif0 = 0;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int WhichPartYouCanModif1 = 0;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int WhichPartYouCanModif2 = 0;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int WhichPartYouCanModif3 = 0;

	// Initialisation Button in case the player doesn't hit a button and start generation
	UFUNCTION(BlueprintNativeEvent,Category = "Map")
	void MapButtonInitialisation();

	// This is the function which permit to modify the generation of the circuit, each color represent a part of circuit
	UFUNCTION(BlueprintNativeEvent,Category = "Map")
	void MapButtonEffect(UButton* WhichButton);

	// Function linked to the click of the button1, it create an event which can be used in the blueprint
	UFUNCTION(BlueprintNativeEvent,Category = "Map")
	void MapButton1Clicked();

	// Function linked to the click of the button2, it create an event which can be used in the blueprint
	UFUNCTION(BlueprintNativeEvent,Category = "Map")
	void MapButton2Clicked();

	// Function linked to the click of the button3, it create an event which can be used in the blueprint
	UFUNCTION(BlueprintNativeEvent,Category = "Map")
	void MapButton3Clicked();

	// Function linked to the click of the button4, it create an event which can be used in the blueprint
	UFUNCTION(BlueprintNativeEvent,Category = "Map")
	void MapButton4Clicked();

	// Function linked to the click of the button which start the generation, it create an event which can be used in the blueprint
	UFUNCTION(BlueprintNativeEvent,Category = "Map")
	void LaunchGenerationMap();
	
private:
	virtual void NativeConstruct() override;	

	int WhichPart1 = 0;
	int WhichPart2 = 0;
	int WhichPart3 = 0;
	int WhichPart4 = 0;
};
