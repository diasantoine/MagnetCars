// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GMGravityCars.generated.h"

/**
 * 
 */
UCLASS()
class MAGNETCARS_API AGMGravityCars : public AGameModeBase
{
	GENERATED_BODY()

public :
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int Bonsoir = 5;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int BONJOUR = 10;
	
};
