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
	for (auto Circuit : MapCircuit)
	{
		for (TSubclassOf<AMyPartCircuit> CircuitPart : Circuit.Value.CircuitPart)
		{
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			this->GetWorld()->SpawnActor<AMyPartCircuit>(CircuitPart,this->GetActorLocation(),this->GetActorRotation(),ActorSpawnParams);
		}
	}
}


