// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawnCar.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyPawnCar::AMyPawnCar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->carCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("carCollision"));
	this->carGroundCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("carGroundCollision "));
	this->springArmGroundCollision = CreateDefaultSubobject<USpringArmComponent>(TEXT("ArmCollisionGround"));
	this->SetRootComponent(carCollision);
	//this->springArmGroundCollision->SetupAttachment(this->carCollision);
	this->carGroundCollision->SetupAttachment(this->springArmGroundCollision);
}

// Called when the game starts or when spawned
void AMyPawnCar::BeginPlay()
{
	Super::BeginPlay();
	carCollision->SetLinearDamping(carStruct.groundFiction);
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
	if(carCollision == nullptr)return;
	this->carCollision->AddForce(GetActorForwardVector() * axisValue * carStruct.acceleration * this->carCollision->GetMass());
	//this->AddMovementInput(GetActorForwardVector() * axisValue * carStruct.acceleration);
	this->carCollision->ComponentVelocity.X = FMath::Clamp(this->carCollision->ComponentVelocity.X,-carStruct.maxSpeed,carStruct.maxSpeed);
	if(carStruct.isGrounded)
	{
		FlyingCar(lastZValue);
	}
	if(carStruct.isOnReverseGravity) return;
	InvertGravity();
}

void AMyPawnCar::RightMovement(float axisValue)
{
	if(carCollision == nullptr)return;
	this->carCollision->AddLocalRotation(FRotator(0,carStruct.amountRotationCar * axisValue,0));
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
	if(carCollision == nullptr)return;
	this->AddActorLocalRotation(FRotator(0,0,carStruct.amountOfLean * value));
	const FRotator containerRotation = this->GetActorRotation();
	const float rotationRoll = FMath::Clamp(containerRotation.Roll,-carStruct.maxLean,carStruct.maxLean);
	this->SetActorRotation(FRotator(containerRotation.Pitch,containerRotation.Yaw,rotationRoll));
	this->carCollision->AddForce(GetActorRightVector() * (rotationRoll / carStruct.maxLean) * carStruct.acceleration);
	UE_LOG(LogTemp,Warning,TEXT("HEY"));
	//this->GetCharacterMovement()->AddForce(GetActorRightVector() * (rotationRoll / carStruct.maxLean));
	//this->AddMovementInput(GetActorRightVector() * (rotationRoll / carStruct.maxLean));
}

void AMyPawnCar::FlyingCar(float lowestZ)
{
	if(carCollision == nullptr) return;
	FVector carLocation = this->GetActorLocation();
	carLocation.Z = lowestZ;
	this->SetActorLocation(carLocation);
}


void AMyPawnCar::CarGravity()
{
	if(carCollision == nullptr)return;
	carStruct.isOnReverseGravity = !carStruct.isOnReverseGravity;
	carCollision->SetEnableGravity(!carStruct.isOnReverseGravity);
	//this->componentMovement->GravityScale = -this->componentMovement->GravityScale;
	//this->Jump();
	this->SetActorRotation(FRotator( 0,0,carStruct.isOnReverseGravity ? 180 : 0));
	//Change Car Gravity to *-1 to make it go the other way, don't forget to rotate the camera x)
}

void AMyPawnCar::InvertGravity()
{
	this->carCollision->ComponentVelocity.Y -= GetWorld()->GetGravityZ();
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

void AMyPawnCar::LastPosition(FVector lastPositionReturned, AActor* roadExit)
{
	this->lastCarPositionOnRoad = lastPositionReturned;
	this->middleOfTheRoad = roadExit->GetStreamingBounds().GetCenter();
}

void AMyPawnCar::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	this->carStruct.isGrounded = true;
	this->lastZValue = this->GetActorLocation().Z;
}


void AMyPawnCar::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	this->carStruct.isGrounded = false;
	this->lastZValue = 0;
}

void AMyPawnCar::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	LastPosition(this->GetActorLocation(),Other);// componentMovement->GetActorLocation(),OtherActor);
}



