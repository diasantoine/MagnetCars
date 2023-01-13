// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyPawnCar.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "MyCarUi.generated.h"

/**
 * 
 */
UCLASS()
class MAGNETCARS_API UMyCarUi : public UUserWidget
{
 GENERATED_BODY()
private:
 virtual void NativeConstruct() override;	
 
public:

 UPROPERTY(BlueprintReadWrite,EditAnywhere,meta =(BindWidget))
 UImage* StartMap = __nullptr;
 UPROPERTY(BlueprintReadWrite,EditAnywhere,meta =(BindWidget))
 UImage* EndMap = __nullptr;
 UPROPERTY(BlueprintReadWrite,EditAnywhere,meta =(BindWidget))
 UImage* Map = __nullptr;

 UPROPERTY(BlueprintReadWrite,EditAnywhere,meta =(BindWidget))
 UImage* MapPositionPlayer1 = __nullptr;
 UPROPERTY(BlueprintReadWrite,EditAnywhere,meta =(BindWidget))
 UImage* MapPositionPlayer2 = __nullptr;
 UPROPERTY(BlueprintReadWrite,EditAnywhere,meta =(BindWidget))
 UImage* MapPositionPlayer3 = __nullptr;
 UPROPERTY(BlueprintReadWrite,EditAnywhere,meta =(BindWidget))
 UImage* MapPositionPlayer4 = __nullptr;

 UPROPERTY(BlueprintReadWrite,EditAnywhere,meta =(BindWidget))
 UImage* ClassementPlayer1 = __nullptr;
 UPROPERTY(BlueprintReadWrite,EditAnywhere,meta =(BindWidget))
 UImage* ClassementPlayer2 = __nullptr;
 UPROPERTY(BlueprintReadWrite,EditAnywhere,meta =(BindWidget))
 UImage* ClassementPlayer3 = __nullptr;
 UPROPERTY(BlueprintReadWrite,EditAnywhere,meta =(BindWidget))
 UImage* ClassementPlayer4 = __nullptr;

 UPROPERTY(BlueprintReadWrite,EditAnywhere)
 FVector2D PositionClassement1 = FVector2D::Zero();
 UPROPERTY(BlueprintReadWrite,EditAnywhere)
 FVector2D  PositionClassement2 = FVector2D::Zero();
 UPROPERTY(BlueprintReadWrite,EditAnywhere)
 FVector2D  PositionClassement3 = FVector2D::Zero();
 UPROPERTY(BlueprintReadWrite,EditAnywhere)
 FVector2D  PositionClassement4 = FVector2D::Zero();

 UPROPERTY(BlueprintReadWrite,EditAnywhere,meta =(BindWidget))
 UImage* BehindPlayer2 = __nullptr;
 UPROPERTY(BlueprintReadWrite,EditAnywhere,meta =(BindWidget))
 UImage* BehindPlayer3 = __nullptr;
 UPROPERTY(BlueprintReadWrite,EditAnywhere,meta =(BindWidget))
 UImage* BehindPlayer4 = __nullptr;

 UPROPERTY(BlueprintReadWrite,EditAnywhere)
 float MinDistanceForArrowToSpawn = 200.f;
 UPROPERTY(BlueprintReadWrite,EditAnywhere)
 FLinearColor ColorOpositeGravity = FLinearColor::Red;
 UPROPERTY(BlueprintReadWrite,EditAnywhere)
 FLinearColor ColorSameGravity = FLinearColor::White;

 
 UPROPERTY(BlueprintReadWrite,EditAnywhere,meta =(BindWidget))
 UImage* NumberOfLapImage = __nullptr;
 UPROPERTY(BlueprintReadWrite,EditAnywhere,meta =(BindWidget))
 UTextBlock* NumberOfLapText = __nullptr;

 UPROPERTY(BlueprintReadWrite,EditAnywhere,meta =(BindWidget))
 UImage* SpeedMeterImage = __nullptr;
 UPROPERTY(BlueprintReadWrite,EditAnywhere,meta =(BindWidget))
 UTextBlock* SpeedMeterText = __nullptr;
 UPROPERTY(BlueprintReadWrite,EditAnywhere)
 float DivsionSpeedForUI = 10.f;

 UPROPERTY(BlueprintReadWrite,EditAnywhere)
 TArray<AMyPawnCar*> ArrayPlayer;

 UPROPERTY(BlueprintReadWrite,EditAnywhere)
 TArray<AMyPawnCar*> PlayerPositionOnMap;

 UPROPERTY(BlueprintReadWrite,EditAnywhere)
 FVector StartLine = FVector::Zero();
 
 UPROPERTY(BlueprintReadWrite,EditAnywhere)
 FVector EndLine = FVector::Zero();

 UPROPERTY(BlueprintReadWrite,EditAnywhere)
 float DistanceMap = 500.f;

 UPROPERTY(BlueprintReadWrite,EditAnywhere)
 int NumberOfLap = 0;

private:

 TMap<AMyPawnCar*,UImage*> MapImagePlayer;
 TMap<AMyPawnCar*,UImage*> MapClassementPlayer;

 
public:

 UFUNCTION(BlueprintCallable)
 void SetUpClassementSetUpMap();

 UFUNCTION(BlueprintCallable)
 TArray<AMyPawnCar*> PositionPlayerMap(TArray<AMyPawnCar*> PlayerArray);

 UFUNCTION(BlueprintCallable)
 void UpdateMap(TArray<AMyPawnCar*> PlayerArray);

 UFUNCTION(BlueprintCallable)
 void UpdateClassement(TArray<AMyPawnCar*> PlayerArray);

 UFUNCTION(BlueprintCallable)
 void UpdateLap();

 UFUNCTION(BlueprintCallable)
 void UpdateSpeed();

 UFUNCTION(BlueprintCallable)
 void UpdateArrow();
};