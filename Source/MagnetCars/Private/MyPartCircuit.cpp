// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPartCircuit.h"

// Sets default values
AMyPartCircuit::AMyPartCircuit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->NewRootComponent = this->CreateDefaultSubobject<USceneComponent>("Root");// Creation des components
	this->StartPartCircuit = this->CreateDefaultSubobject<USceneComponent>("Start");
	this->EndPartCircuit = this->CreateDefaultSubobject<USceneComponent>("End");

	this->SetRootComponent(this->NewRootComponent);
	this->StartPartCircuit->SetupAttachment(this->NewRootComponent);
	this->EndPartCircuit->SetupAttachment(this->NewRootComponent);
}

// Called when the game starts or when spawned
void AMyPartCircuit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPartCircuit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


