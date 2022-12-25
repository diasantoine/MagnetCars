// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerMagnetCar.h"

void APlayerControllerMagnetCar::NotifyLoadedWorld(FName WorldPackageName, bool bFinalDest)
{
    Super::NotifyLoadedWorld(WorldPackageName, bFinalDest);

    // Call custom ServerNotifyLoadedWorld
    ServerNotifyLoadedWorldWorkaround(WorldPackageName);
}

bool APlayerControllerMagnetCar::ServerNotifyLoadedWorldWorkaround_Validate(FName WorldPackageName)
{
    RPC_VALIDATE(WorldPackageName.IsValid());
    return true;
}

void APlayerControllerMagnetCar::ServerNotifyLoadedWorldWorkaround_Implementation(FName WorldPackageName)
{
    UE_LOG(LogPlayerController, Verbose, TEXT("APlayerControllerMagnetCar::ServerNotifyLoadedWorldWorkaround_Implementation: Client loaded %s"), *WorldPackageName.ToString());

    UWorld* CurWorld = GetWorld();

    // Only valid for calling, for PC's in the process of seamless traveling
    // NOTE: SeamlessTravelCount tracks client seamless travel, through the serverside gameplay code; this should not be replaced.
    if (CurWorld != NULL && !CurWorld->IsNetMode(NM_Client) && SeamlessTravelCount > 0 && LastCompletedSeamlessTravelCount < SeamlessTravelCount)
    {
        // Update our info on what world the client is in
        UNetConnection* const Connection = Cast<UNetConnection>(Player);

        if (Connection != NULL)
        {
            Connection->SetClientWorldPackageName(WorldPackageName);
        }

        // if both the server and this client have completed the transition, handle it
        FSeamlessTravelHandler& SeamlessTravelHandler = GEngine->SeamlessTravelHandlerForWorld(CurWorld);
        AGameModeBase* CurGameMode = CurWorld->GetAuthGameMode();

        if (!SeamlessTravelHandler.IsInTransition() && WorldPackageName == CurWorld->GetOutermost()->GetFName() && CurGameMode != NULL)
        {
            AController* TravelPlayer = this;
            CurGameMode->HandleSeamlessTravelPlayer(TravelPlayer);
        }
        else
        {
            // This is the seamless travel fix for client loading before server and softlocking
            // Skip this for TransitionMapName
            FString TransitionMapString = GetDefault<UGameMapsSettings>()->TransitionMap.GetLongPackageName();
            FName TransitionMapName(*TransitionMapString);
            if (TransitionMapName != WorldPackageName)
            {
                LastCompletedSeamlessTravelCount = SeamlessTravelCount;
            }
        }
    }
}