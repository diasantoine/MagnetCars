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
	this->CarGroundCollision->SetUsingAbsoluteLocation(true);
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
		this->CarCollision->AddForce(GetActorForwardVector() * axisValue * CarStruct.AccelerationNotGrounded * this->CarCollision->GetMass());
		this->CarCollision->ComponentVelocity.X = FMath::Clamp(this->CarCollision->ComponentVelocity.X,-CarStruct.MaxSpeed,CarStruct.MaxSpeed);
	}
	
	if(CarStruct.IsGrounded)
	{
		FlyingCar(LastZValue);
	}
	if(CarStruct.IsOnReverseGravity)
	{
		InvertGravity();
	}
	else
	{
		this->CarCollision->AddForce(this->GetActorUpVector() * GetWorld()->GetGravityZ() * GravityMultiplier);
	}
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
		this->CarCollision->AddLocalRotation(FRotator(0,CarStruct.AmountRotationCarNotGrounded * axisValue,0));
	}
}

void AMyPawnCar::CarDrift(float value)
{
	if(CarCollision == nullptr)return;
	this->AddActorLocalRotation(FRotator(0,0,CarStruct.AmountOfLean * value));
	const FRotator containerRotation = this->GetActorRotation();
	float RotationRoll;
	if(CarStruct.IsOnReverseGravity)
	{
		RotationRoll = containerRotation.Roll > 0 ?
			FMath::Clamp(containerRotation.Roll, 180 - CarStruct.MaxLean , 190) : FMath::Clamp(containerRotation.Roll, -190 , CarStruct.MaxLean - 180);
	}
	else
	{
		RotationRoll =  FMath::Clamp(containerRotation.Roll,-CarStruct.MaxLean,CarStruct.MaxLean);
	}
	//const float RotationRoll = CarStruct.IsOnReverseGravity ? FMath::Clamp(containerRotation.Roll, -180 + CarStruct.MaxLean , 180 -CarStruct.MaxLean) : FMath::Clamp(containerRotation.Roll,-CarStruct.MaxLean,CarStruct.MaxLean);
	this->SetActorRotation(FRotator(containerRotation.Pitch,containerRotation.Yaw,RotationRoll));
	//this->CarCollision->ComponentVelocity = this->CarCollision->ComponentVelocity.Length() * (this->CarCollision->ComponentVelocity.GetSafeNormal() * GetActorRightVector());
	//this->CarCollision->AddForce(GetActorRightVector() * -value * (RotationRoll / CarStruct.MaxLean) * CarStruct.Acceleration * 50);
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
	UE_LOG(LogTemp,Warning,TEXT("hey"));
}


/*void AMyPawnCar::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	this->CarStruct.IsGrounded = false;
	this->LastZValue = 0;
}
*/
void AMyPawnCar::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	LastPosition(this->GetActorLocation(),Other);// componentMovement->GetActorLocation(),OtherActor);
}



