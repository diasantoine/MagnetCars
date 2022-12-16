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
UCLASS()
class MAGNETCARS_API UWidgetChoiceMap : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly, meta = (BindWidget))
	UButton* MapChoice1;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, meta = (BindWidget))
	UButton* MapChoice2;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, meta = (BindWidget))
	UButton* MapChoice3;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, meta = (BindWidget))
	UButton* MapChoice4;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, meta = (BindWidget))
	UButton* MapGeneration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ALoadCircuit* LoadCircuit = nullptr;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FLinearColor SnowPartCirtcuit = FLinearColor::White;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FLinearColor SandPartCirtcuit = FLinearColor::Yellow;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FLinearColor CityPartCirtcuit = FLinearColor::Black;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FLinearColor InnerCityPartCirtcuit = FLinearColor::Gray;
	
	UFUNCTION(BlueprintNativeEvent,Category = "Map")
	void MapButtonEffect(UButton* WhichButton);
	
	UFUNCTION(BlueprintNativeEvent,Category = "Map")
	void MapButton1Clicked();

	UFUNCTION(BlueprintNativeEvent,Category = "Map")
	void MapButton2Clicked();

	UFUNCTION(BlueprintNativeEvent,Category = "Map")
	void MapButton3Clicked();

	UFUNCTION(BlueprintNativeEvent,Category = "Map")
	void MapButton4Clicked();

	UFUNCTION(BlueprintNativeEvent,Category = "Map")
	void LaunchGenerationMap();
	
private:
	virtual void NativeConstruct() override;	

	int WhichPart1 = 0;
	int WhichPart2 = 0;
	int WhichPart3 = 0;
	int WhichPart4 = 0;
};
