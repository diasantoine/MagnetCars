// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCar.h"

#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMyCar::AMyCar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyCar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyCar::CarMovement(EWhichDirection Direction)
{
	UCharacterMovementComponent* ComponentMovement = GetCharacterMovement();
	switch (Direction)
	{
	case EWhichDirection::ForwardDirection:
		default:
		ComponentMovement->Velocity *= Acceleration * GetControlRotation().Vector().Normalize();
		break;
	case EWhichDirection::BackwardDirection:
		break;
	}
}

void AMyCar::CarGravity()
{
	OnGravity = !OnGravity;
	//Change Car Gravity to *-1 to make it go the other way, don't forget to rotate the camera x)
}

void AMyCar::CarRespawn()
{
	ContainerRespawnTiming += 0.01f; //Delta time hein avec le tick
	if(ContainerRespawnTiming>= RespawnTiming) ContainerRespawnTiming = 0;
}





