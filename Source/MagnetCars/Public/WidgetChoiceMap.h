// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	
private:

	virtual void NativeConstruct() override;


};
