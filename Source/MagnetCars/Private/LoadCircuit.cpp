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
				FVector SpawnPosition = this->FirstPartCircuitPosition + (this->FirstPartCircuitPosition - Container->StartPartCircuit->GetComponentLocation());
				Container->SetActorLocation(SpawnPosition);
				this->PartCircuitGenerated.Add(Container);
				First = true;
				this->LastEndSceneComponent = Container->EndPartCircuit;//->GetComponentLocation();
			}
			else
			{
				if(this->LastEndSceneComponent == nullptr)continue;
				FVector LastEndPosition = this->LastEndSceneComponent->GetComponentLocation();
				FVector SpawnPosition;
				AMyPartCircuit* Container = this->GetWorld()->SpawnActor<AMyPartCircuit>(CircuitPart,FVector::Zero(),
					this->LastEndSceneComponent->GetComponentRotation(),ActorSpawnParams);
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
				this->LastEndSceneComponent = Container->EndPartCircuit;
			}
		}
		if(this->LastEndSceneComponent == nullptr)continue;
		this->FirstPartCircuitPosition = this->LastEndSceneComponent->GetComponentLocation();
	}
	this->FirstPartCircuitPosition = this->GetActorLocation();
	if(PartCircuitGenerated.Num() == 0)return;
	if(this->PartCircuitGenerated[0] == nullptr)return;
	this->PartCircuitGenerated[0]->SetUpFirstPart();
	if(this->PartCircuitGenerated[this->PartCircuitGenerated.Num()-1] == nullptr)return;
	this->PartCircuitGenerated[this->PartCircuitGenerated.Num()-1]->SetUpLastPart();
}


void ALoadCircuit::UnLoadCircuit_Implementation()
{
	if(this->PartCircuitGenerated.Num() == 0) return;
	for (AMyPartCircuit* PartCircuit : this->PartCircuitGenerated)
	{
		if(PartCircuit == nullptr)continue;
		PartCircuit->Destroy();
	}
	this->PartCircuitGenerated.Empty();
}


