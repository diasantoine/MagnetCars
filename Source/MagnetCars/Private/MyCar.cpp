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
	componentMovement->MaxAcceleration = carStruct.acceleration;
	componentMovement->MaxWalkSpeed = carStruct.maxSpeed;
	componentMovement->GroundFriction = carStruct.groundFiction;
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
	PlayerInputComponent->BindAxis("Right",this,&AMyCar::AddControllerYawInput);
	//PlayerInputComponent->BindAxis("Turn",this,&AMyCar::AddControllerYawInput);
	//PlayerInputComponent->BindAxis("LookUp",this,&AMyCar::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("RightLean",this,&AMyCar::CarDrift);
	PlayerInputComponent->BindAxis("LeftLean",this,&AMyCar::CarDrift);
	
	PlayerInputComponent->BindAction("ChangeGravity",IE_Pressed,this,&AMyCar::CarGravity);

	PlayerInputComponent->BindAction("ResetScene",IE_Pressed,this,&AMyCar::ResetScene);
	PlayerInputComponent->BindAction("Respawn",IE_Pressed,this,&AMyCar::CarRespawn);

}

void AMyCar::ForwardMovement(float axisValue)
{
	UE_LOG(LogTemp,Warning,TEXT("Text, %f"),axisValue);
	this->AddMovementInput(GetActorForwardVector() * axisValue);
}

void AMyCar::RightMovement(float axisValue)
{
	this->AddActorWorldRotation(FRotator(0, carStruct.amountRotationCar * axisValue,0));
	// const FRotator containerRotation = this->GetActorRotation();
	// this->SetActorRotation(FRotator(containerRotation.Pitch,FMath::Clamp(containerRotation.Yaw,0,carStruct.maxAmountRotationCar),containerRotation.Roll));
	//this->AddMovementInput(GetActorRightVector(),axisValue);
}

void AMyCar::CarDrift(float value)
{
	this->AddActorLocalRotation(FRotator(0,0,carStruct.amountOfLean * value));
	const FRotator containerRotation = this->GetActorRotation();
	const float rotationRoll = FMath::Clamp(containerRotation.Roll,-carStruct.maxLean,carStruct.maxLean);
	this->SetActorRotation(FRotator(containerRotation.Pitch,containerRotation.Yaw,rotationRoll));
	//this->GetCharacterMovement()->AddForce(GetActorRightVector() * (rotationRoll / carStruct.maxLean));
	//this->AddMovementInput(GetActorRightVector() * (rotationRoll / carStruct.maxLean));
}

void AMyCar::CarGravity()
{
	carStruct.isOnReverseGravity = !carStruct.isOnReverseGravity;
	this->componentMovement->GravityScale = -this->componentMovement->GravityScale;
	this->Jump();
	this->SetActorRotation(FRotator( 0,0,carStruct.isOnReverseGravity ? 180 : 0));
	//Change Car Gravity to *-1 to make it go the other way, don't forget to rotate the camera x)
}

void AMyCar::ResetScene()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void AMyCar::CarRespawn()
{
	componentMovement->Velocity = FVector::Zero();
	carStruct = FCarOld();
	APawn::SetActorLocation(middleOfTheRoad);
	APawn::SetActorRotation(FRotator::ZeroRotator);
}

void AMyCar::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	LastPosition(componentMovement->GetActorLocation(),OtherActor);
}


void AMyCar::LastPosition(FVector lastPositionReturned, AActor* roadExit)
{
	lastCarPositionOnRoad = lastPositionReturned;
	middleOfTheRoad = roadExit->GetStreamingBounds().GetCenter();
}
