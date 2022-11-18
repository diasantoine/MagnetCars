// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawnCar.h"

#include <string>

#include "Kismet/GameplayStatics.h"

// Sets default values
AMyPawnCar::AMyPawnCar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->CarCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("carCollision"));
	this->SetRootComponent(CarCollision);/*
	this->CarGroundCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("carGroundCollision"));
	this->CarGroundCollision->SetupAttachment(this->RootComponent);
	this->CarGroundCollision->SetUsingAbsoluteRotation(true);
	this->CarGroundCollision->SetUsingAbsoluteLocation(true);*/
}

// Called when the game starts or when spawned
void AMyPawnCar::BeginPlay()
{
	Super::BeginPlay();
	CarCollision->SetLinearDamping(CarStruct.GroundFriction);
}

// Called every frame
void AMyPawnCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*if(ArrayOfGround.Num() > 0)
	{
		ContainerTimeBeforeCarFall = 0;
		return;
	}
	CarFall(DeltaTime);*/
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
	DetectGround();
	if(CarStruct.IsGrounded)
	{
		this->CarPhysiqueReaction(CarStruct.PhysiqueReactionGround);
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
		this->CarCollision->SetLinearDamping(CarStruct.GroundFriction);
		//FlyingCar(LastZValue);
	}
	else
	{
		this->CarCollision->SetLinearDamping(CarStruct.AirFriction);
	}
	if(CarStruct.IsOnReverseGravity)
	{
		InvertGravity();
	}
	else
	{
		//this->CarCollision->AddForce(this->CarGroundCollision->GetUpVector() * GetWorld()->GetGravityZ() * GravityMultiplier);
		this->CarCollision->AddForce(-this->CarCollision->GetUpVector() * GravityMultiplier);
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

void AMyPawnCar::CarPhysiqueReaction(EPhysiqueReaction WhichPhysique)
{
	FBodyInstance* BodyInstance = this->CarCollision->GetBodyInstance();
	switch (WhichPhysique)
	{
	case EPhysiqueReaction::FlyingCircuitXYZ:
	default:
		BodyInstance->bLockRotation = false;
		this->CarStruct.PhysiqueReactionStatus = EPhysiqueReaction::FlyingCircuitXYZ;
		break;
	case EPhysiqueReaction::FlyingCircuitXY:
		BodyInstance->bLockRotation = false;
		BodyInstance->bLockZRotation = true;
		this->CarStruct.PhysiqueReactionStatus = EPhysiqueReaction::FlyingCircuitXY;
		break;
	case EPhysiqueReaction::FlyingCircuitXZ:
		BodyInstance->bLockRotation = false;
		BodyInstance->bLockYRotation = true;
		this->CarStruct.PhysiqueReactionStatus = EPhysiqueReaction::FlyingCircuitXZ;
		break;
	case EPhysiqueReaction::FlyingCircuitYZ:
		BodyInstance->bLockRotation = false;
		BodyInstance->bLockXRotation = true;
		this->CarStruct.PhysiqueReactionStatus = EPhysiqueReaction::FlyingCircuitYZ;
		break;
	case EPhysiqueReaction::FlyingCircuitX:
		BodyInstance->bLockRotation = true;
		BodyInstance->bLockXRotation = false;
		this->CarStruct.PhysiqueReactionStatus = EPhysiqueReaction::FlyingCircuitX;
		break;
	case EPhysiqueReaction::FlyingCircuitY:
		BodyInstance->bLockRotation = true;
		BodyInstance->bLockYRotation = false;
		this->CarStruct.PhysiqueReactionStatus = EPhysiqueReaction::FlyingCircuitY;
		break;
	case EPhysiqueReaction::FlyingCircuitZ:
		BodyInstance->bLockRotation = true;
		BodyInstance->bLockZRotation = false;
		this->CarStruct.PhysiqueReactionStatus = EPhysiqueReaction::FlyingCircuitZ;
		break;
	case EPhysiqueReaction::FlyingCircuit:
		BodyInstance->bLockRotation = true;
		this->CarStruct.PhysiqueReactionStatus = EPhysiqueReaction::FlyingCircuit;
		break;
	case EPhysiqueReaction::GroundedXYZ:
		BodyInstance->bLockRotation = false;
		this->CarStruct.PhysiqueReactionStatus = EPhysiqueReaction::GroundedXYZ;
		break;
	case EPhysiqueReaction::GroundedXY:
		BodyInstance->bLockRotation = false;
		BodyInstance->bLockZRotation = true;
		this->CarStruct.PhysiqueReactionStatus = EPhysiqueReaction::GroundedXY;
		break;
	case EPhysiqueReaction::GroundedXZ:
		BodyInstance->bLockRotation = false;
		BodyInstance->bLockYRotation = true;
		this->CarStruct.PhysiqueReactionStatus = EPhysiqueReaction::GroundedXZ;
		break;
	case EPhysiqueReaction::GroundedYZ:
		BodyInstance->bLockRotation = false;
		BodyInstance->bLockXRotation = true;
		this->CarStruct.PhysiqueReactionStatus = EPhysiqueReaction::GroundedYZ;
		break;
	case EPhysiqueReaction::GroundedX:
		BodyInstance->bLockRotation = true;
		BodyInstance->bLockXRotation = false;
		this->CarStruct.PhysiqueReactionStatus = EPhysiqueReaction::GroundedX;
		break;
	case EPhysiqueReaction::GroundedY:
		BodyInstance->bLockRotation = true;
		BodyInstance->bLockYRotation = false;
		this->CarStruct.PhysiqueReactionStatus = EPhysiqueReaction::GroundedY;
		break;
	case EPhysiqueReaction::GroundedZ:
		BodyInstance->bLockRotation = true;
		BodyInstance->bLockZRotation = false;
		this->CarStruct.PhysiqueReactionStatus = EPhysiqueReaction::GroundedZ;
		break;
	case EPhysiqueReaction::Grounded:
		BodyInstance->bLockRotation = true;
		this->CarStruct.PhysiqueReactionStatus = EPhysiqueReaction::Grounded;
		break;
	case EPhysiqueReaction::OutsideCircuit:
		BodyInstance->bLockRotation = false;
		this->CarStruct.PhysiqueReactionStatus = EPhysiqueReaction::OutsideCircuit;
		break;
	}
}


void AMyPawnCar::CarDrift(float value)
{
	if(CarCollision == nullptr)return;
	if(TemporaryScene == nullptr)return;
	if(value == 0)
	{
		//this->AddActorLocalRotation(FRotator(0,0,CarStruct.AmountOfLean * value));
		this->TemporaryScene->AddLocalRotation(FRotator(0,0,CarStruct.AmountOfLean * value));
	}
	else
	{
		//this->AddActorLocalRotation(FRotator(0,0,CarStruct.AmountOfLean * value));
		this->TemporaryScene->AddLocalRotation(FRotator(0,0,CarStruct.AmountOfLean * value));
	}
	//const FRotator containerRotation = this->GetActorRotation();
	const FRotator containerRotation = this->TemporaryScene->GetRelativeRotation();
	float RotationRoll;
	if(CarStruct.IsOnReverseGravity && false)
	{
		RotationRoll = containerRotation.Roll > 0 ?
			FMath::Clamp(containerRotation.Roll, 180 - CarStruct.MaxLean , 190) : FMath::Clamp(containerRotation.Roll, -190 , CarStruct.MaxLean - 180);
	}
	else
	{
		RotationRoll =  FMath::Clamp(containerRotation.Roll,-CarStruct.MaxLean,CarStruct.MaxLean);
	}
	//const float RotationRoll = CarStruct.IsOnReverseGravity ? FMath::Clamp(containerRotation.Roll, -180 + CarStruct.MaxLean , 180 -CarStruct.MaxLean) : FMath::Clamp(containerRotation.Roll,-CarStruct.MaxLean,CarStruct.MaxLean);
	//this->SetActorRotation(FRotator(containerRotation.Pitch,containerRotation.Yaw,RotationRoll));
	this->TemporaryScene->SetRelativeRotation(FRotator(containerRotation.Pitch,containerRotation.Yaw,RotationRoll));
	if(CarStruct.IsOnReverseGravity && false)
	{
		this->CarCollision->AddForce(GetActorRightVector() * ((RotationRoll > 0 ? RotationRoll - 180 : RotationRoll + 180) / CarStruct.MaxLean) * CarStruct.AccelerationLeanNotGrounded);
	}
	else
	{
		this->CarCollision->AddForce(GetActorRightVector() * (RotationRoll / CarStruct.MaxLean) * CarStruct.AccelerationLean);
	}
}

void AMyPawnCar::FlyingCar(float lowestZ)
{
	if(CarCollision == nullptr) return;
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("connard,%f"),lowestZ));
	}
	UE_LOG(LogTemp,Warning,TEXT("hey,%f"),lowestZ);
	FVector test = this->CarCollision->ComponentVelocity;
	this->CarCollision->AddForce(this->CarCollision->GetUpVector() * GetWorld()->GetGravityZ() * GravityMultiplier *(CarStruct.MaxDistanceWithTheGround/lowestZ)
		* (CarStruct.IsOnReverseGravity ? 1 : -1));
	//(this->GravityMultiplier*100 * lowestZ / this->CarStruct.MaxDistanceWithTheGround));
	return;
	FVector carLocation = this->GetActorLocation();
	carLocation.Z = lowestZ;
	this->SetActorLocation(carLocation);
}


void AMyPawnCar::CarGravity()
{
	if(CarCollision == nullptr)return;
	CarStruct.IsOnReverseGravity = !CarStruct.IsOnReverseGravity;
	CarCollision->SetEnableGravity(!CarStruct.IsOnReverseGravity);
	this->SetActorRotation(FRotator( 0,0,CarStruct.IsOnReverseGravity ? 180 : 0));
	if(!CarStruct.InstantReverseGravity) return;
	const float ContainerLinearDamping = this->CarCollision->GetLinearDamping();
	this->CarCollision->SetLinearDamping(5000000000);
	this->CarCollision->SetLinearDamping(ContainerLinearDamping);
	//this->TemporaryScene->SetRelativeRotation(FRotator( 0,0,CarStruct.IsOnReverseGravity ? 180 : 0));
}

void AMyPawnCar::InvertGravity()
{
	//this->CarCollision->AddForce(this->GetActorUpVector() * GetWorld()->GetGravityZ() * GravityMultiplierWhenInversed);
	this->CarCollision->AddForce(this->GetActorUpVector() * GravityMultiplierWhenInversed * GetWorld()->GetGravityZ());
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

void AMyPawnCar::CarFall(float DeltaTime)
{
	if(ContainerTimeBeforeCarFall >= TimeBeforeCarFall)
	{
		this->CarStruct.IsGrounded = false;
		this->LastZValue = 0;
		ContainerTimeBeforeCarFall = 0;
	}
	else
	{
		ContainerTimeBeforeCarFall += DeltaTime;
	}
}

void AMyPawnCar::DetectGround()
{
	const FCollisionShape Sphere =  FCollisionShape::MakeSphere(CarStruct.RadiusSphere);
	const FCollisionShape Box =  FCollisionShape::MakeBox(FVector(100,100,CarStruct.RadiusSphere));
	TArray<FHitResult> Result;
	this->GetWorld()->SweepMultiByChannel(Result,this->CarCollision->GetComponentLocation() - FVector(0,0,16),
		this->CarCollision->GetComponentLocation()  - FVector(0,0,16) - FVector(0,CarStruct.MaxDistanceWithTheGround,0),FQuat(0,0,0,0),ColllisionChannel,Box);
	if(Result.Num() == 0)
	{
		CarStruct.IsGrounded = false;
		return;
	}
	for (const auto HitResult : Result)
	{
		if(HitResult.GetActor() == this) continue;
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("connard,%s"),
*HitResult.GetActor()->GetActorNameOrLabel()));
		}
		CarStruct.IsGrounded = true;
		FlyingCar(FVector::Distance(HitResult.ImpactPoint,this->GetActorLocation()));
		return;
	}
	CarStruct.IsGrounded = false;
}


/*
void AMyPawnCar::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	this->CarStruct.IsGrounded = true;
	this->LastZValue = this->GetActorLocation().Z;
	//this->LastZValue = OtherActor->GetActorLocation().Z + CarStruct.DistanceWithTheGround;
	ArrayOfGround.Add(OtherActor);
	UE_LOG(LogTemp,Warning,TEXT("start,%s"),*OtherActor->GetActorNameOrLabel());
}


 void AMyPawnCar::NotifyActorEndOverlap(AActor* OtherActor)
 {
 	Super::NotifyActorEndOverlap(OtherActor);
	if(!ArrayOfGround.Contains(OtherActor)) return;
	ArrayOfGround.Remove(OtherActor);
	if(ArrayOfGround.Num()>0) return;
 	this->CarStruct.IsGrounded = false;
 	this->LastZValue = 0;
	UE_LOG(LogTemp,Warning,TEXT("end,%s"),*OtherActor->GetActorNameOrLabel());

 }

void AMyPawnCar::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	LastPosition(this->GetActorLocation(),Other);// componentMovement->GetActorLocation(),OtherActor);
}
*/

