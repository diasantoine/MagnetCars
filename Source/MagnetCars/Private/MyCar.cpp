// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCar.h"

#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

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
	componentMovement = this->GetCharacterMovement();
	componentMovement->MaxAcceleration = acceleration;
	componentMovement->MaxWalkSpeed = maxSpeed;
	componentMovement->GroundFriction = groundFiction;
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
	PlayerInputComponent->BindAxis("Forward",this,&AMyCar::ForwardMovement);
	PlayerInputComponent->BindAxis("Right",this,&AMyCar::RightMovement);
	PlayerInputComponent->BindAxis("Turn",this,&AMyCar::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp",this,&AMyCar::AddControllerPitchInput);
	
	PlayerInputComponent->BindAxis("RightLean",this,&AMyCar::CarDrift);
	PlayerInputComponent->BindAxis("LeftLean",this,&AMyCar::CarDrift);
	
	PlayerInputComponent->BindAction("ChangeGravity",IE_Pressed,this,&AMyCar::CarGravity);

	PlayerInputComponent->BindAction("Respawn",IE_Pressed,this,&AMyCar::CarRespawn);
}

void AMyCar::ForwardMovement(float axisValue)
{
	this->AddMovementInput(GetActorForwardVector(),axisValue);
}

void AMyCar::RightMovement(float axisValue)
{
	this->AddMovementInput(GetActorRightVector(),axisValue);
}

void AMyCar::CarDrift(float value)
{
	this->AddActorLocalRotation(FRotator(0,0,accelerationRotation * value));
	const FVector containerRotation = this->GetActorLocation();
	this->SetActorLocation(FVector(containerRotation.X,containerRotation.Y,FMath::Clamp(containerRotation.Z,0,maxRotation)));
}

void AMyCar::CarGravity()
{
	isOnReverseGravity = !isOnReverseGravity;
	this->componentMovement->GravityScale = -this->componentMovement->GravityScale;
	this->Jump();
	this->SetActorRotation(FRotator( isOnReverseGravity ? 180 : 0,0,0));
	//Change Car Gravity to *-1 to make it go the other way, don't forget to rotate the camera x)
}

void AMyCar::CarRespawn()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}
