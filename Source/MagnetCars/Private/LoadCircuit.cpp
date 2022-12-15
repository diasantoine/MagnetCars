// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadCircuit.h"

// Sets default values
ALoadCircuit::ALoadCircuit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALoadCircuit::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALoadCircuit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALoadCircuit::LoadCircuit_Implementation()
{
	UE_LOG(LogTemp,Warning,TEXT("Prout"));
	bool First = false;
	for (auto Circuit : MapCircuit)
	{
		for (const TSubclassOf<AMyPartCircuit> CircuitPart : Circuit.Value.CircuitPart)
		{
			if(CircuitPart == nullptr) continue;
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			if(!First)
			{
				this->GetWorld()->SpawnActor<AMyPartCircuit>(CircuitPart,this->FirstPartCircuitPosition,FRotator::ZeroRotator,ActorSpawnParams);
				First = true;
				this->LastEndPosition = CircuitPart.GetDefaultObject()->EndPartCircuit;
			}
			else
			{
				FVector SpawnPosition;
				FVector StartPartCircuit = CircuitPart.GetDefaultObject()->StartPartCircuit;
				switch (WhichAxisAccounted)
				{
				case XYZ:
					default:
					SpawnPosition = LastEndPosition - StartPartCircuit;
					break;
				case XY:
					SpawnPosition = LastEndPosition;
					SpawnPosition.X -= StartPartCircuit.X;
					SpawnPosition.Y -= StartPartCircuit.Y;
					break;
				case XZ:
					SpawnPosition = LastEndPosition;
					SpawnPosition.X -= StartPartCircuit.X;
					SpawnPosition.Z -= StartPartCircuit.Z;
					break;
				case YZ:
					SpawnPosition = LastEndPosition;
					SpawnPosition.Y -= StartPartCircuit.Y;
					SpawnPosition.Z -= StartPartCircuit.Z;
					break;
				case X:
					SpawnPosition = LastEndPosition;
					SpawnPosition.X -= StartPartCircuit.X;
					break;
				case Y:
					SpawnPosition = LastEndPosition;
					SpawnPosition.Y -= StartPartCircuit.Y;
					break;
				case Z:
					SpawnPosition = LastEndPosition;
					SpawnPosition.Z -= StartPartCircuit.Z;
					break;
				}
				this->GetWorld()->SpawnActor<AMyPartCircuit>(CircuitPart,SpawnPosition,FRotator::ZeroRotator,ActorSpawnParams);
			}
			this->LastEndPosition = CircuitPart.GetDefaultObject()->EndPartCircuit;
		}
	}
}


