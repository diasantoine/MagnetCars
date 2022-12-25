// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Net/UnrealNetwork.h"
#include "GameFramework/GameModeBase.h"
#include "GameMapsSettings.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerMagnetCar.generated.h"

/**
 * 
 */
UCLASS()
class MAGNETCARS_API APlayerControllerMagnetCar : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void NotifyLoadedWorld(FName WorldPackageName, bool bFinalDest) override;

	UFUNCTION(Reliable, Server, WithValidation, SealedEvent)
		void ServerNotifyLoadedWorldWorkaround(FName WorldPackageName);

	
	
};

