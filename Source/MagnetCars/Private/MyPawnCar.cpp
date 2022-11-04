// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawnCar.h"

#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyPawnCar::AMyPawnCar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	boxCollision = Cast<UBoxComponent>(this->GetRootComponent());
}

// Called when the game starts or when spawned
void AMyPawnCar::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyPawnCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPawnCar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Forward",this,&AMyPawnCar::ForwardMovement);
	PlayerInputComponent->BindAxis("Right",this,&APawn::AddControllerYawInput);
	//PlayerInputComponent->BindAxis("Turn",this,&AMyCar::AddControllerYawInput);
	//PlayerInputComponent->BindAxis("LookUp",this,&AMyCar::AddControllerPitchInput);

	// PlayerInputComponent->BindAxis("RightLean",this,&AMyPawnCar::CarDrift);
	// PlayerInputComponent->BindAxis("LeftLean",this,&AMyPawnCar::CarDrift);
	
	PlayerInputComponent->BindAction("ChangeGravity",IE_Pressed,this,&AMyPawnCar::CarGravity);

	PlayerInputComponent->BindAction("ResetScene",IE_Pressed,this,&AMyPawnCar::ResetScene);
	PlayerInputComponent->BindAction("Respawn",IE_Pressed,this,&AMyPawnCar::CarRespawn);
}


void AMyPawnCar::ForwardMovement(float axisValue)
{
	UE_LOG(LogTemp,Warning,TEXT("MERDE, %f"),axisValue);
	this->boxCollision->AddForce(GetActorForwardVector() * axisValue * carStruct.acceleration);
	//this->AddMovementInput(GetActorForwardVector() * axisValue * carStruct.acceleration);
	this->boxCollision->ComponentVelocity.X = FMath::Clamp(this->boxCollision->ComponentVelocity.X,-carStruct.maxSpeed,carStruct.maxSpeed);
	if(carStruct.isOnReverseGravity) return;
	InvertGravity();
}

void AMyPawnCar::RightMovement(float axisValue)
{
	this->boxCollision->AddForce(GetActorRightVector() * axisValue * carStruct.acceleration);
	//this->boxCollision->AddForce(GetActorRightVector() * axisValue * carStruct.acceleration);
	this->boxCollision->ComponentVelocity.Y = FMath::Clamp(this->boxCollision->ComponentVelocity.Y,-carStruct.maxSpeed,carStruct.maxSpeed);
	//this->AddActorWorldRotation(FRotator(0, carStruct.amountRotationCar * axisValue,0));
	// const FRotator containerRotation = this->GetActorRotation();
	// this->SetActorRotation(FRotator(containerRotation.Pitch,FMath::Clamp(containerRotation.Yaw,0,carStruct.maxAmountRotationCar),containerRotation.Roll));
	//this->AddMovementInput(GetActorRightVector(),axisValue);
}

void AMyPawnCar::CarDrift(float value)
{
	this->AddActorLocalRotation(FRotator(0,0,carStruct.amountOfLean * value));
	const FRotator containerRotation = this->GetActorRotation();
	const float rotationRoll = FMath::Clamp(containerRotation.Roll,-carStruct.maxLean,carStruct.maxLean);
	this->SetActorRotation(FRotator(containerRotation.Pitch,containerRotation.Yaw,rotationRoll));
	this->boxCollision->AddForce(GetActorRightVector() * (rotationRoll / carStruct.maxLean));
	//this->GetCharacterMovement()->AddForce(GetActorRightVector() * (rotationRoll / carStruct.maxLean));
	//this->AddMovementInput(GetActorRightVector() * (rotationRoll / carStruct.maxLean));
}

void AMyPawnCar::CarGravity()
{
	carStruct.isOnReverseGravity = !carStruct.isOnReverseGravity;
	boxCollision->SetEnableGravity(carStruct.isOnReverseGravity);
	//this->componentMovement->GravityScale = -this->componentMovement->GravityScale;
	//this->Jump();
	this->SetActorRotation(FRotator( carStruct.isOnReverseGravity ? 180 : 0,0,0));
	//Change Car Gravity to *-1 to make it go the other way, don't forget to rotate the camera x)
}

void AMyPawnCar::InvertGravity()
{
	this->boxCollision->ComponentVelocity.Y -= GetWorld()->GetGravityZ();
}


void AMyPawnCar::ResetScene()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void AMyPawnCar::CarRespawn()
{
	//componentMovement->Velocity = FVector::Zero();
	carStruct = FCar();
	APawn::SetActorLocation(middleOfTheRoad);
	APawn::SetActorRotation(FRotator::ZeroRotator);
}

void AMyPawnCar::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	LastPosition(this->GetActorLocation(),OtherActor);// componentMovement->GetActorLocation(),OtherActor);
}


void AMyPawnCar::LastPosition(FVector lastPositionReturned, AActor* roadExit)
{
	lastCarPositionOnRoad = lastPositionReturned;
	middleOfTheRoad = roadExit->GetStreamingBounds().GetCenter();
}
