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

void ALoadCircuit::LoadMapType_Implementation()
{
	MapCircuit[0].CircuitPart[0] = OrderPartCircuit[0];
	for (int i = 0; i < MapCircuit.Num(); i++)
	{
		for (int j = 0; j < MapCircuit[i].CircuitPart.Num(); j++)
		{
			MapCircuit[i].CircuitPart[j] = OrderPartCircuit[j];
		}
	}
}


void ALoadCircuit::LoadCircuit_Implementation()
// Function which generate the map in function of the OrderPartCircuit and the MapCircuit
{
	this->UnLoadCircuit();
	this->LoadMapType();
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
				AMyPartCircuit* Container = this->GetWorld()->SpawnActor<AMyPartCircuit>(CircuitPart,this->FirstPartCircuitPosition,FRotator::ZeroRotator,ActorSpawnParams);
				this->PartCircuitGenerated.Add(Container);
				First = true;
				this->LastEndPosition = Container->EndPartCircuit->GetComponentLocation();
			}
			else
			{
				FVector SpawnPosition;
				AMyPartCircuit* Container = this->GetWorld()->SpawnActor<AMyPartCircuit>(CircuitPart,FVector::Zero(),FRotator::ZeroRotator,ActorSpawnParams);
				FVector StartPartCircuit = Container->StartPartCircuit->GetComponentLocation();
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
				Container->SetActorLocation(SpawnPosition);
				this->PartCircuitGenerated.Add(Container);
				this->LastEndPosition = Container->EndPartCircuit->GetComponentLocation();
			}
		}
		this->FirstPartCircuitPosition = this->LastEndPosition;
	}
	this->FirstPartCircuitPosition = this->GetActorLocation();
}


void ALoadCircuit::UnLoadCircuit_Implementation()
{
	if(this->PartCircuitGenerated.Num() == 0) return;
	for (AMyPartCircuit* PartCircuit : this->PartCircuitGenerated)
	{
		PartCircuit->Destroy();
	}
	this->PartCircuitGenerated.Empty();
}


