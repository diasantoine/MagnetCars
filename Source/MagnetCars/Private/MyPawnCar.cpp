// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawnCar.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyPawnCar::AMyPawnCar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->CarCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("carCollision"));
	this->CarGroundCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("carGroundCollision"));
	this->SetRootComponent(CarCollision);
	this->CarGroundCollision->SetupAttachment(this->RootComponent);
	this->CarGroundCollision->SetUsingAbsoluteRotation(true);
}

// Called when the game starts or when spawned
void AMyPawnCar::BeginPlay()
{
	Super::BeginPlay();
	CarCollision->SetLinearDamping(CarStruct.GroundFiction);
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
	PlayerInputComponent->BindAxis("Right",this,&AMyPawnCar::RightMovement);
	//PlayerInputComponent->BindAxis("Turn",this,&AMyPawnCar::AddControllerYawInput);
	//PlayerInputComponent->BindAxis("LookUp",this,&AMyCar::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("RightLean",this,&AMyPawnCar::CarDrift);
	PlayerInputComponent->BindAxis("LeftLean",this,&AMyPawnCar::CarDrift);
	
	PlayerInputComponent->BindAction("ChangeGravity",IE_Pressed,this,&AMyPawnCar::CarGravity);

	PlayerInputComponent->BindAction("ResetScene",IE_Pressed,this,&AMyPawnCar::ResetScene);
	PlayerInputComponent->BindAction("Respawn",IE_Pressed,this,&AMyPawnCar::CarRespawn);
}


void AMyPawnCar::ForwardMovement(float axisValue)
{
	if(CarCollision == nullptr)return;
	if(CarStruct.IsGrounded)
	{
		this->CarCollision->AddForce(GetActorForwardVector() * axisValue * CarStruct.Acceleration * this->CarCollision->GetMass());
		//this->AddMovementInput(GetActorForwardVector() * axisValue * carStruct.acceleration);
		this->CarCollision->ComponentVelocity.X = FMath::Clamp(this->CarCollision->ComponentVelocity.X,-CarStruct.MaxSpeed,CarStruct.MaxSpeed);
	}
	else
	{
		this->CarCollision->AddForce(GetActorForwardVector() * axisValue * CarStruct.Acceleration * this->CarCollision->GetMass());
		this->CarCollision->ComponentVelocity.X = FMath::Clamp(this->CarCollision->ComponentVelocity.X,-CarStruct.MaxSpeed,CarStruct.MaxSpeed);
	}
	if(CarStruct.IsGrounded)
	{
		FlyingCar(LastZValue);
	}
	if(!CarStruct.IsOnReverseGravity) return;
	InvertGravity();
}

void AMyPawnCar::RightMovement(float axisValue)
{
	if(CarCollision == nullptr)return;
	if(CarStruct.IsGrounded)
	{
		this->CarCollision->AddLocalRotation(FRotator(0,CarStruct.AmountRotationCar * axisValue,0));
	}
	else
	{
		this->CarCollision->AddLocalRotation(FRotator(0,CarStruct.AmountRotationCar * axisValue,0));
	}
	// FRotator rotationCar = this->carCollision->GetRelativeRotation();
	// this->carCollision->SetRelativeRotation(FRotator(rotationCar.Pitch,FMath::Clamp(rotationCar.Yaw,-carStruct.maxAmountRotationCar,carStruct.maxAmountRotationCar),rotationCar.Roll));
	//this->carCollision->AddForce(GetActorRightVector() * axisValue * carStruct.acceleration * this->carCollision->GetMass());
	//this->carCollision->AddForce(GetActorRightVector() * axisValue * carStruct.acceleration);
	//this->carCollision->ComponentVelocity.Y = FMath::Clamp(this->carCollision->ComponentVelocity.Y,-carStruct.maxSpeed,carStruct.maxSpeed);
	//this->AddActorWorldRotation(FRotator(0, carStruct.amountRotationCar * axisValue,0));
	// const FRotator containerRotation = this->GetActorRotation();
	// this->SetActorRotation(FRotator(containerRotation.Pitch,FMath::Clamp(containerRotation.Yaw,0,carStruct.maxAmountRotationCar),containerRotation.Roll));
	//this->AddMovementInput(GetActorRightVector(),axisValue);
}

void AMyPawnCar::CarDrift(float value)
{
	if(CarCollision == nullptr)return;
	this->AddActorLocalRotation(FRotator(0,0,CarStruct.AmountOfLean * value));
	const FRotator containerRotation = this->GetActorRotation();
	//const float rotationRoll = FMath::Clamp(containerRotation.Roll,-CarStruct.MaxLean,CarStruct.MaxLean);
	// this->SetActorRotation(FRotator(containerRotation.Pitch,containerRotation.Yaw,rotationRoll));
	this->CarCollision->AddForce(GetActorRightVector() * (/*rotationRoll*/ containerRotation.Roll / CarStruct.MaxLean) * CarStruct.Acceleration);
	//this->GetCharacterMovement()->AddForce(GetActorRightVector() * (rotationRoll / carStruct.maxLean));
	//this->AddMovementInput(GetActorRightVector() * (rotationRoll / carStruct.maxLean));
}

void AMyPawnCar::FlyingCar(float lowestZ)
{
	if(CarCollision == nullptr) return;
	FVector carLocation = this->GetActorLocation();
	carLocation.Z = lowestZ;
	this->SetActorLocation(carLocation);
}


void AMyPawnCar::CarGravity()
{
	if(CarCollision == nullptr)return;
	CarStruct.IsOnReverseGravity = !CarStruct.IsOnReverseGravity;
	CarCollision->SetEnableGravity(!CarStruct.IsOnReverseGravity);
	//this->componentMovement->GravityScale = -this->componentMovement->GravityScale;
	//this->Jump();
	this->SetActorRotation(FRotator( 0,0,CarStruct.IsOnReverseGravity ? 180 : 0));
	//Change Car Gravity to *-1 to make it go the other way, don't forget to rotate the camera x)
}

void AMyPawnCar::InvertGravity()
{
	UE_LOG(LogTemp,Warning,TEXT("hegbzrhb"));
	//this->CarCollision->AddForce(GetActorUpVector() * -GetWorld()->GetGravityZ());
	this->CarCollision->AddForce(this->GetActorUpVector() * GetWorld()->GetGravityZ() * GravityMultiplierWhenInversed);
}


void AMyPawnCar::ResetScene()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void AMyPawnCar::CarRespawn()
{
	//componentMovement->Velocity = FVector::Zero();
	CarStruct = FCar();
	APawn::SetActorLocation(MiddleOfTheRoad);
	APawn::SetActorRotation(FRotator::ZeroRotator);
}

void AMyPawnCar::LastPosition(FVector lastPositionReturned, AActor* roadExit)
{
	this->LastCarPositionOnRoad = lastPositionReturned;
	this->MiddleOfTheRoad = roadExit->GetStreamingBounds().GetCenter();
}

void AMyPawnCar::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	this->CarStruct.IsGrounded = true;
	this->LastZValue = this->GetActorLocation().Z;
}


void AMyPawnCar::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	this->CarStruct.IsGrounded = false;
	this->LastZValue = 0;
}

void AMyPawnCar::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	LastPosition(this->GetActorLocation(),Other);// componentMovement->GetActorLocation(),OtherActor);
}



