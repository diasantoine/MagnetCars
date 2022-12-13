// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawnCar.h"

#include "MyGroundBoostPlate.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AMyPawnCar::AMyPawnCar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->CarCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("carCollision"));
	this->SetRootComponent(CarCollision);
}

// Called when the game starts or when spawned
void AMyPawnCar::BeginPlay()
{
	Super::BeginPlay();
	this->ContainerAcceleration = CarStruct.Acceleration;
	this->Tags.Add(this->CarTag);
	if(this->CarStruct.IsGrounded)
	{
		this->CarCollision->SetLinearDamping(CarStruct.GroundFriction);
		this->CarCollision->SetAngularDamping(CarStruct.AngularGroundFriction);
	}
	else
	{
		this->CarCollision->SetLinearDamping(CarStruct.AirFriction);
		this->CarCollision->SetAngularDamping(CarStruct.AngularAirFriction);
	}
	this->GetWorld()->GetPhysicsScene()->OnPhysSceneStep.AddUObject(this,&AMyPawnCar::PhysicalCarMovement);
	//UE_LOG(LogTemp,Warning,TEXT("%s"),*this->Tags[0].ToString());
}

// Called every frame
void AMyPawnCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(this->CarCollision)
	{
		FVector MyVelocity = this->CarCollision->GetPhysicsLinearVelocity();
		if(this->CarStruct.IsBoosted)
		{
			MyVelocity.X = FMath::Clamp(MyVelocity.X,-this->CarStruct.ActualMaxSpeedUnderBoost,this->CarStruct.ActualMaxSpeedUnderBoost);
		}
		else
		{
			MyVelocity.X = FMath::Clamp(MyVelocity.X,-this->CarStruct.MaxSpeed,this->CarStruct.MaxSpeed);
		}
		this->CarCollision->SetPhysicsLinearVelocity(MyVelocity);
	}
}

// Called to bind functionality to input
void AMyPawnCar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Forward",this,&AMyPawnCar::ForwardMovement);
	PlayerInputComponent->BindAxis("Right",this,&AMyPawnCar::RightMovement);
	//PlayerInputComponent->BindAxis("Turn",this,&AMyPawnCar::AddControllerYawInput);
	//PlayerInputComponent->BindAxis("LookUp",this,&AMyCar::AddControllerPitchInput);

	if(Keyboard)
	{
		PlayerInputComponent->BindAxis("RightLean",this,&AMyPawnCar::CarDrift);
	}
	PlayerInputComponent->BindAxis("LeftLean",this,&AMyPawnCar::CarDrift);
	
	PlayerInputComponent->BindAction("ChangeGravity",IE_Pressed,this,&AMyPawnCar::CarGravity);

	PlayerInputComponent->BindAction("ResetScene",IE_Pressed,this,&AMyPawnCar::ResetScene);
	PlayerInputComponent->BindAction("Respawn",IE_Pressed,this,&AMyPawnCar::CarRespawn);
}


void AMyPawnCar::ForwardMovement(float axisValue)
{
	if(CarCollision == nullptr)return;
	DetectGround();
	if(this->CarStruct.IsBoosted)
	{
		if(this->CarStruct.ActualMaxSpeedUnderBoost <= this->CarStruct.MaxSpeed)
		{
			this->CarStruct.IsBoosted = false;
			this->CarStruct.ActualMaxSpeedUnderBoost = this->CarStruct.MaxSpeed;
		}
		/*if(this->CarCollision->GetComponentVelocity().X >= 0)
		{
			if(this->CarCollision->GetComponentVelocity().X < this->CarStruct.MaxSpeed)
			{
				this->CarStruct.IsBoosted = false;
			}
		}
		else
		{
			if(this->CarCollision->GetComponentVelocity().X > -this->CarStruct.MaxSpeed)
			{
				this->CarStruct.IsBoosted = false;
			}
		}*/
	}
	if(this->CarStruct.IsGrounded)
	{
		//UE_LOG(LogTemp,Warning,TEXT("Act %f, MaxBoost %f"), this->CarStruct.ActualMaxSpeedUnderBoost,this->CarStruct.MaxSpeedWithBoost);
		ContainerForwardAxis = axisValue * CarStruct.Acceleration * this->CarCollision->GetMass() * this->CarCollision->GetLinearDamping();
		//this->CarCollision->AddForce(GetActorForwardVector() * axisValue * CarStruct.Acceleration * this->CarCollision->GetMass());
		//FVector VelocityCar = this->CarCollision->GetComponentVelocity();
		if(this->CarStruct.IsBoosted)
		{
			this->CarStruct.ActualMaxSpeedUnderBoost = UKismetMathLibrary::FInterpTo_Constant(this->CarStruct.ActualMaxSpeedUnderBoost,this->CarStruct.MaxSpeed,this->GetWorld()->GetDeltaSeconds(),
				this->CarStruct.SpeedResetMaxSpeed);
			//UE_LOG(LogTemp,Warning,TEXT("Act %f, MaxBoost %f"), this->CarStruct.ActualMaxSpeedUnderBoost,this->CarStruct.MaxSpeedWithBoost);
			/*
			VelocityCar.X = UKismetMathLibrary::FInterpTo_Constant(FMath::Clamp(VelocityCar.X,-CarStruct.MaxSpeedWithBoost,CarStruct.MaxSpeedWithBoost),
				FMath::Clamp(VelocityCar.X,-CarStruct.MaxSpeed,CarStruct.MaxSpeed),this->GetWorld()->GetDeltaSeconds(),this->CarStruct.SpeedResetMaxSpeed);
			VelocityCar.Y = UKismetMathLibrary::FInterpTo_Constant(FMath::Clamp(VelocityCar.Y,-CarStruct.MaxSpeedWithBoost,CarStruct.MaxSpeedWithBoost),
				FMath::Clamp(VelocityCar.Y,-CarStruct.MaxSpeed,CarStruct.MaxSpeed),this->GetWorld()->GetDeltaSeconds(),this->CarStruct.SpeedResetMaxSpeed);
			VelocityCar.Z = UKismetMathLibrary::FInterpTo_Constant(FMath::Clamp(VelocityCar.Z,-CarStruct.MaxSpeedWithBoost,CarStruct.MaxSpeedWithBoost),
				FMath::Clamp(VelocityCar.Z,-CarStruct.MaxSpeed,CarStruct.MaxSpeed),this->GetWorld()->GetDeltaSeconds(),this->CarStruct.SpeedResetMaxSpeed);*/
			/*VelocityCar.X = FMath::Clamp(VelocityCar.X,-CarStruct.ActualMaxSpeedUnderBoost,CarStruct.ActualMaxSpeedUnderBoost);
			VelocityCar.Y = FMath::Clamp(VelocityCar.Y,-CarStruct.ActualMaxSpeedUnderBoost,CarStruct.ActualMaxSpeedUnderBoost);
			VelocityCar.Z = FMath::Clamp(VelocityCar.Z,-CarStruct.ActualMaxSpeedUnderBoost,CarStruct.ActualMaxSpeedUnderBoost);*/
		}
		else
		{
			/*VelocityCar.X = FMath::Clamp(VelocityCar.X,-CarStruct.MaxSpeed,CarStruct.MaxSpeed);
			VelocityCar.Y = FMath::Clamp(VelocityCar.Y,-CarStruct.MaxSpeed,CarStruct.MaxSpeed);
			VelocityCar.Z = FMath::Clamp(VelocityCar.Z,-CarStruct.MaxSpeed,CarStruct.MaxSpeed);*/
		}
		//this->CarCollision->SetPhysicsLinearVelocity(VelocityCar);
		//this->CarCollision->SetPhysicsLinearVelocity(VelocityCar.GetSafeNormal() * FMath::Clamp(VelocityCar.Length(),0,CarStruct.MaxSpeed));
	}
	else
	{

		ContainerForwardAxis = axisValue * CarStruct.AccelerationNotGrounded * this->CarCollision->GetMass() * this->CarCollision->GetLinearDamping();
		//this->CarCollision->AddForce(GetActorForwardVector() * axisValue * CarStruct.AccelerationNotGrounded * this->CarCollision->GetMass());
		//FVector VelocityCar = this->CarCollision->GetComponentVelocity();
		if(this->CarStruct.IsBoosted)
		{
			this->CarStruct.ActualMaxSpeedUnderBoost = UKismetMathLibrary::FInterpTo_Constant(this->CarStruct.ActualMaxSpeedUnderBoost,this->CarStruct.MaxSpeed,this->GetWorld()->GetDeltaSeconds(),
				this->CarStruct.SpeedResetMaxSpeed);/*
			VelocityCar.X = UKismetMathLibrary::FInterpTo_Constant(FMath::Clamp(VelocityCar.X,-CarStruct.MaxSpeedWithBoost,CarStruct.MaxSpeedWithBoost),
				FMath::Clamp(VelocityCar.X,-CarStruct.MaxSpeed,CarStruct.MaxSpeed),this->GetWorld()->GetDeltaSeconds(),this->CarStruct.SpeedResetMaxSpeed);
			VelocityCar.Y = UKismetMathLibrary::FInterpTo_Constant(FMath::Clamp(VelocityCar.Y,-CarStruct.MaxSpeedWithBoost,CarStruct.MaxSpeedWithBoost),
				FMath::Clamp(VelocityCar.Y,-CarStruct.MaxSpeed,CarStruct.MaxSpeed),this->GetWorld()->GetDeltaSeconds(),this->CarStruct.SpeedResetMaxSpeed);
			VelocityCar.Z = UKismetMathLibrary::FInterpTo_Constant(FMath::Clamp(VelocityCar.Z,-CarStruct.MaxSpeedWithBoost,CarStruct.MaxSpeedWithBoost),
				FMath::Clamp(VelocityCar.Z,-CarStruct.MaxSpeed,CarStruct.MaxSpeed),this->GetWorld()->GetDeltaSeconds(),this->CarStruct.SpeedResetMaxSpeed);*/
			//VelocityCar.X = FMath::Clamp(VelocityCar.X,-CarStruct.ActualMaxSpeedUnderBoost,CarStruct.ActualMaxSpeedUnderBoost);
			//VelocityCar.Y = FMath::Clamp(VelocityCar.Y,-CarStruct.ActualMaxSpeedUnderBoost,CarStruct.ActualMaxSpeedUnderBoost);
			//VelocityCar.Z = FMath::Clamp(VelocityCar.Z,-CarStruct.ActualMaxSpeedUnderBoost,CarStruct.ActualMaxSpeedUnderBoost);
		}
		else
		{
			//VelocityCar.X = FMath::Clamp(VelocityCar.X,-CarStruct.MaxSpeed,CarStruct.MaxSpeed);
			//VelocityCar.Y = FMath::Clamp(VelocityCar.Y,-CarStruct.MaxSpeed,CarStruct.MaxSpeed);
			//VelocityCar.Z = FMath::Clamp(VelocityCar.Z,-CarStruct.MaxSpeed,CarStruct.MaxSpeed);
		}
		//this->CarCollision->SetPhysicsLinearVelocity(VelocityCar);
	}
	
	if(CarStruct.IsGrounded)
	{
		this->CarCollision->SetLinearDamping(CarStruct.GroundFriction);
		this->CarCollision->SetAngularDamping(CarStruct.AngularGroundFriction);
	}
	else
	{
		this->CarCollision->SetLinearDamping(CarStruct.AirFriction);
		this->CarCollision->SetAngularDamping(CarStruct.AngularAirFriction);
	}
	if(CarStruct.IsOnReverseGravity)
	{
		InvertGravity();
	}
	else
	{
		if(!this->CarCollision->IsGravityEnabled()) return;
		this->CarCollision->AddForce(-this->CarCollision->GetUpVector() * (CarStruct.IsGrounded ? CarStruct.CarMassGround : CarStruct.CarMassNotGrounded)
			* this->CarCollision->GetMass());
	}
}

void AMyPawnCar::PhysicalCarMovement(FPhysScene_Chaos *_PhysScene,float DeltaTime)
{
	if(this->CarCollision == nullptr)return;
	
	const FVector VelocityCar = this->CarCollision->GetPhysicsLinearVelocity();
	//this->CarCollision->GetBodyInstance()->ClearForces();
	ContainerForwardAxis *= this->SpeedCurve->GetFloatValue(VelocityCar.Length() /(this->CarStruct.IsBoosted ? this->CarStruct.ActualMaxSpeedUnderBoost : this->CarStruct.MaxSpeed));
	/*UE_LOG(LogTemp,Warning,TEXT("%f"),
		this->SpeedCurve->GetFloatValue(VelocityCar.Length() /(this->CarStruct.IsBoosted ? this->CarStruct.ActualMaxSpeedUnderBoost : this->CarStruct.MaxSpeed)));*/
	this->CarCollision->AddForce(GetActorForwardVector() * ContainerForwardAxis);
	//this->CarCollision->GetBodyInstance()->SetLinearVelocity(VelocityCar.GetSafeNormal() * FMath::Clamp(VelocityCar.Length(),0,CarStruct.MaxSpeed),true,true);
	/*FRigidBodyState* Test = nullptr;
	this->CarCollision->GetRigidBodyState(*Test);
	if(Test == nullptr)return;
	Test->LinVel = VelocityCar.GetSafeNormal() * FMath::Clamp(VelocityCar.Length(),0,CarStruct.MaxSpeed);*/
}



void AMyPawnCar::RightMovement(float axisValue)
{
	if(CarCollision == nullptr)return;
	this->CarCollision->GetBodyInstance()->bLockZRotation = false;
	this->CarCollision->GetBodyInstance()->SetDOFLock(EDOFMode::Default);
	if(CarStruct.IsGrounded)
	{
		this->AddActorLocalRotation(FRotator(0,CarStruct.AmountRotationCar * axisValue,0));
	}
	else
	{
		this->AddActorLocalRotation(FRotator(0,CarStruct.AmountRotationCarNotGrounded * axisValue,0));
	}
	this->CarCollision->GetBodyInstance()->bLockZRotation = true;
	this->CarCollision->GetBodyInstance()->SetDOFLock(EDOFMode::Default);
}

void AMyPawnCar::CarPhysiqueReaction(EPhysiqueReaction WhichPhysique)
{
	return;
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
		BodyInstance->bLockXRotation = true;
		BodyInstance->bLockYRotation = true;
		BodyInstance->bLockZRotation = true;
		this->CarStruct.PhysiqueReactionStatus = EPhysiqueReaction::Grounded;
		break;
	case EPhysiqueReaction::OutsideCircuit:
		UE_LOG(LogTemp,Warning,TEXT("Does this works?"));
		BodyInstance->bLockXRotation = false;
		BodyInstance->bLockYRotation = false;
		BodyInstance->bLockZRotation = false;
		this->CarStruct.PhysiqueReactionStatus = EPhysiqueReaction::OutsideCircuit;
		break;
	}
}


void AMyPawnCar::CarDrift(float value)
{
	if(CarCollision == nullptr)return;
	if(TemporaryScene == nullptr)return;
	if(CarStruct.IsLeanCreateRotation)
	{
		this->AddActorLocalRotation(FRotator(0,CarStruct.AmountOfRotationWithLean *
			(this->TemporaryScene->GetRelativeRotation().Roll / CarStruct.MaxLean),0));
	}
	if(value == 0)
	{
		if(this->TemporaryScene->GetRelativeRotation().Roll == 0) return;
		this->TemporaryScene->SetRelativeRotation(UKismetMathLibrary::RInterpTo_Constant(this->TemporaryScene->GetRelativeRotation(),
			FRotator(0,0,0),this->GetWorld()->GetDeltaSeconds(),
			(CarStruct.IsGrounded ? this->CarStruct.SpeedResetLeanGrounded : this->CarStruct.SpeedResetLeanNotGrounded)));
		/*this->TemporaryScene->AddLocalRotation(FRotator(0,0,(CarStruct.IsGrounded ? CarStruct.AmountOfLean : CarStruct.AmountOfLeanNotGrounded) *
			(this->TemporaryScene->GetRelativeRotation().Roll > 0 ? -1 : 1)));*/
	}
	else
	{
		this->CarCollision->GetBodyInstance()->bLockXRotation = false;
		this->CarCollision->GetBodyInstance()->bLockYRotation = false;
		this->CarCollision->GetBodyInstance()->SetDOFLock(EDOFMode::Default);
		this->TemporaryScene->AddLocalRotation(FRotator(0,0,(CarStruct.IsGrounded ? CarStruct.AmountOfLean : CarStruct.AmountOfLeanNotGrounded) * value));
		this->CarCollision->GetBodyInstance()->bLockXRotation = true;
		this->CarCollision->GetBodyInstance()->bLockYRotation = true;
		this->CarCollision->GetBodyInstance()->SetDOFLock(EDOFMode::Default);
	}
	const FRotator ContainerRotation = this->TemporaryScene->GetRelativeRotation();
	const float RotationRoll = FMath::Clamp(ContainerRotation.Roll, -CarStruct.MaxLean, CarStruct.MaxLean);
	this->TemporaryScene->SetRelativeRotation(FRotator(ContainerRotation.Pitch,ContainerRotation.Yaw,RotationRoll));
	if(this->CarStruct.IsLeanCreateSlow)
	{
		if(FMath::Abs(this->TemporaryScene->GetRelativeRotation().Roll) >= this->CarStruct.AmountOfLeanToStartSlow)
		{
			this->SlowLeanActivate();
			this->CarCollision->AddForce(-this->CarCollision->GetForwardVector() * this->CarCollision->GetMass()
				* (this-CarStruct.IsGrounded ? this->CarStruct.LeanSlowGrounded : this->CarStruct.LeanSlowAir));
		}
	}
	if(this->CarStruct.DragWholeBodyWhenLean)
	{
		this->CarCollision->AddForce(GetActorRightVector() * (RotationRoll / CarStruct.MaxLean) * CarStruct.AccelerationLean * this->CarCollision->GetMass());
	}
	else
	{
			
	}
}

void AMyPawnCar::CarIncline()
{
	FHitResult Result;
	TArray<AActor*> ActorIgnored;
	ActorIgnored.Add(this);
	const FVector StartPosition = this->CarCollision->GetComponentLocation() - (this->CarStruct.IsOnReverseGravity ? -1 * this->CarStruct.StartBoxGroundDetection : this->CarStruct.StartBoxGroundDetection);
	const FVector EndPosition = this->CarCollision->GetComponentLocation() - (this->CarStruct.IsOnReverseGravity ? -1 * this->CarStruct.EndBoxGroundDetection : this->CarStruct.EndBoxGroundDetection);
	const bool ResultHit = UKismetSystemLibrary::BoxTraceSingle(this, StartPosition,EndPosition,
		CarStruct.HalfSizeBoxGroundDetection,FRotator::ZeroRotator,TraceChannel,false,ActorIgnored,
		EDrawDebugTrace::ForOneFrame,Result,true,FLinearColor::Blue,FLinearColor::Red,5);
	if(ResultHit)
	{
	}
}

void AMyPawnCar::FlyingCar(FVector ImpactPoint)
{
	if(CarCollision == nullptr) return;
	if(!first)
	{
		Velocity = this->CarCollision->ComponentVelocity;
		first = true;
	}
	if(this->CarCollision->ComponentVelocity.Z < 0)
	{
		const FVector Direction = -this->GetActorUpVector();
		this->CarCollision->AddForce(Direction * GetWorld()->GetGravityZ() * MagneticForceTowardUp);
	}
	else
	{
		const FVector Direction = this->GetActorUpVector();
		const float MassCar = this->CarCollision->GetMass();
		const float HalfSizeBoxGround = CarStruct.HalfSizeBoxGroundDetection.Z * 1.5f;
		//UE_LOG(LogTemp,Warning,TEXT("LowestZ %f , HalfSize %f"), lowestZ, HalfSizeBoxGround);
		//UE_LOG(LogTemp,Warning,TEXT("LowestZ %f , HalfSize %f"), ImpactPoint.Z, HalfSizeBoxGround);
		this->CarCollision->SetEnableGravity(false);
		FVector LocationCar = this->GetActorLocation();
		LocationCar.Z = HalfSizeBoxGround + ImpactPoint.Z;
		this->SetActorLocation(LocationCar);
		/*if(FMath::IsNearlyEqual(lowestZ,HalfSizeBoxGround,20.f))
		{
			UE_LOG(LogTemp,Warning,TEXT("LowestZ %f , HalfSize %f"), lowestZ, HalfSizeBoxGround);
			this->CarCollision->SetEnableGravity(false);
			FVector LocationCar = this->GetActorLocation();
			LocationCar.Z = TestZ;
			this->SetActorLocation(LocationCar);
		}
		else if(lowestZ - HalfSizeBoxGround < -50.f)
		{
			this->CarCollision->SetEnableGravity(true);
			this->CarCollision->AddForce(Direction * -GetWorld()->GetGravityZ() * MassCar * MagneticForceTowardUp);
			TestZ = this->GetActorLocation().Z;
		}
		else
		{
			this->CarCollision->SetEnableGravity(true);
			TestZ = this->GetActorLocation().Z;
		}*/
		//this->CarCollision->AddForce(Direction * -GetWorld()->GetGravityZ() * MassCar * MagneticForceTowardUp * (CarStruct.HalfSizeBoxGroundDetection.Z / lowestZ));
		/*if(lowestZ  - CarStruct.HalfSizeBoxGroundDetection.Z >= 0)
		{
			this->CarCollision->AddForce(Direction * -GetWorld()->GetGravityZ() * MassCar / MagneticForceTowardGround);
		}
		else
		{
			this->CarCollision->AddForce(Direction * -GetWorld()->GetGravityZ() * MassCar * MagneticForceTowardUp * (CarStruct.HalfSizeBoxGroundDetection.Z / lowestZ));
		}*/
	}
}


void AMyPawnCar::CarGravity()
{
	if(this->CarCollision == nullptr)return;
	this->CarCollision->GetBodyInstance()->bLockXRotation = false;
	this->CarCollision->GetBodyInstance()->bLockYRotation = false;
	this->CarCollision->GetBodyInstance()->SetDOFLock(EDOFMode::Default);
	this->CarStruct.IsOnReverseGravity = !CarStruct.IsOnReverseGravity;
	this->CarCollision->SetEnableGravity(!CarStruct.IsOnReverseGravity);
	FRotator CarRotation = this->GetActorRotation();
	CarRotation.Roll = this->CarStruct.IsOnReverseGravity ? 180 : 0;
	this->SetActorRotation(CarRotation);
	this->CarCollision->GetBodyInstance()->bLockXRotation = true;
	this->CarCollision->GetBodyInstance()->bLockYRotation = true;
	this->CarCollision->GetBodyInstance()->SetDOFLock(EDOFMode::Default);
	if(!this->CarStruct.InstantReverseGravity) return;
}

void AMyPawnCar::InvertGravity()
{
	if(this->CarCollision == nullptr)return;
	this->CarReverseGravity();
	this->CarCollision->AddForce(this->CarCollision->GetUpVector() * this->CarCollision->GetMass() * GetWorld()->GetGravityZ()
		* (CarStruct.IsGrounded ? CarStruct.CarMassGroundInversedGravity : CarStruct.CarMassNotGroundedInversedGravity));
}

void AMyPawnCar::BoostPlate(float Boost)
{
	if(this->CarCollision == nullptr)return;
	this->CarStruct.ActualMaxSpeedUnderBoost = this->CarStruct.MaxSpeedWithBoost;
	this->CarStruct.IsBoosted = true;
	this->CarBoost();
	this->CarCollision->AddForce(GetActorForwardVector() * Boost * this->CarCollision->GetMass());
	FVector VelocityCar = this->CarCollision->GetComponentVelocity();
	VelocityCar.X = FMath::Clamp(VelocityCar.X,-CarStruct.ActualMaxSpeedUnderBoost,CarStruct.ActualMaxSpeedUnderBoost);
	VelocityCar.Y = FMath::Clamp(VelocityCar.Y,-CarStruct.ActualMaxSpeedUnderBoost,CarStruct.ActualMaxSpeedUnderBoost);
	VelocityCar.Z = FMath::Clamp(VelocityCar.Z,-CarStruct.ActualMaxSpeedUnderBoost,CarStruct.ActualMaxSpeedUnderBoost);
	this->CarCollision->SetPhysicsLinearVelocity(VelocityCar);
}



void AMyPawnCar::ResetScene()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void AMyPawnCar::CarRespawn()
{
	this->CarCollision->ComponentVelocity = FVector::Zero();
	this->TemporaryScene->SetRelativeRotation(FRotator::ZeroRotator);
	APawn::SetActorLocation(ResetPosition);
	APawn::SetActorRotation(FRotator::ZeroRotator);
	this->CarStruct.IsOnReverseGravity = false;
	this->CarStruct.IsGrounded = false;
}

void AMyPawnCar::LastPosition(FVector lastPositionReturned, AActor* roadExit)
{
	this->LastCarPositionOnRoad = lastPositionReturned;
	this->MiddleOfTheRoad = roadExit->GetStreamingBounds().GetCenter();
}

/*void AMyPawnCar::CarFall(float DeltaTime)
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
}*/

void AMyPawnCar::DetectGround()
{
	FHitResult Result;
	TArray<AActor*> ActorIgnored;
	ActorIgnored.Add(this);
	const FVector StartPosition = this->CarCollision->GetComponentLocation() - (this->CarStruct.IsOnReverseGravity ? -1 * this->CarStruct.StartBoxGroundDetection : this->CarStruct.StartBoxGroundDetection);
	const FVector EndPosition = this->CarCollision->GetComponentLocation() - (this->CarStruct.IsOnReverseGravity ? -1 * this->CarStruct.EndBoxGroundDetection : this->CarStruct.EndBoxGroundDetection);
	const bool ResultHit = UKismetSystemLibrary::BoxTraceSingle(this, StartPosition,EndPosition,
		CarStruct.HalfSizeBoxGroundDetection,FRotator::ZeroRotator,TraceChannel,false,ActorIgnored,
		EDrawDebugTrace::ForOneFrame,Result,true,FLinearColor::Blue,FLinearColor::Red,5); 
	if(!ResultHit)
	{
		CarStruct.IsGrounded = false;
		LastActorHit = nullptr;
		if(!this->CarStruct.IsOnReverseGravity)
		this->CarCollision->SetEnableGravity(true);
		return;
	}
	if(!this->CarStruct.IsGrounded)
	{
		this->CarStruct.IsGrounded = true;
		this->CarGotGrounded();
	}
	//DetectSlope((Result.Location - this->CarCollision->GetUpVector()).GetSafeNormal());
	//DetectSlope(Result.ImpactNormal);
	if(!BlockSlope)
	{
		/*FRotator test2;
		FHitResult A;
		for (const auto RaycastVertical : this->ArrayRaycastVerticalCarAngle)
		{
			this->GetWorld()->LineTraceSingleByChannel(A,RaycastVertical->GetComponentLocation(),-RaycastVertical->GetUpVector(),
				ECollisionChannel::ECC_Visibility);
			test2 = DetectSlope(A.ImpactNormal);
			//test2 = DetectSlope((Result.ImpactPoint - RaycastVertical->GetComponentLocation()).GetSafeNormal());
			break;
		}*/
		FRotator test;
		test = DetectSlope(Result.ImpactNormal);
		FRotator NewRotationCar = this->GetActorRotation();
		NewRotationCar.Pitch =  test.Pitch;
		NewRotationCar.Roll =  test.Roll;
		//NewRotationCar.Pitch =  (FMath::Abs(test.Pitch) > this->CarStruct.MinSlopeCar) ? test.Pitch : 0;
		//NewRotationCar.Roll =  (FMath::Abs(test.Roll) > this->CarStruct.MinSlopeCar) ? test.Roll : 0;
		FRotator Test2 = UKismetMathLibrary::RInterpTo_Constant(this->GetActorRotation(),NewRotationCar,this->GetWorld()->GetDeltaSeconds(),
			this->CarStruct.SpeedForSlopeAdjustement);
		//UE_LOG(LogTemp,Warning,TEXT("Yaw %f, Yaw %f"),Test2.Yaw,this->GetActorRotation().Yaw);
		this->RotateCarForSlope(Test2);
		/*
		if(FMath::Abs(test.Pitch) > this->CarStruct.MinSlopeCar)
		{
			FRotator NewRotationCar = this->GetActorRotation();
			NewRotationCar.Pitch = test.Pitch;
			NewRotationCar.Roll = test.Roll;
			FRotator Test2 = UKismetMathLibrary::RInterpTo(this->GetActorRotation(),NewRotationCar,this->GetWorld()->GetDeltaSeconds(),
				this->CarStruct.SpeedForSlopeAdjustement);
			UE_LOG(LogTemp,Warning,TEXT("Yaw %f, Yaw %f"),Test2.Yaw,this->GetActorRotation().Yaw);
			this->RotateCarForSlope(Test2);
		}
		else
		{
			FRotator NewRotationCar = this->GetActorRotation();
			NewRotationCar.Pitch = 0;
			NewRotationCar.Roll = 0;
			FRotator Test2 = UKismetMathLibrary::RInterpTo(this->GetActorRotation(),NewRotationCar,this->GetWorld()->GetDeltaSeconds(),
				this->CarStruct.SpeedForSlopeAdjustement);
			this->RotateCarForSlope(Test2);
		}*/
		//DetectSlope((Result.ImpactPoint - this->ArrayRaycastVerticalCarAngle[0]->GetComponentLocation()).GetSafeNormal());
		//DetectSlope((Result.ImpactPoint - this->ArrayRaycastVerticalCarAngle[1]->GetComponentLocation()).GetSafeNormal());
		//UE_LOG(LogTemp,Warning,TEXT("Vector normal,%f %f %f"), Result.Normal.X, Result.Normal.Y, Result.Normal.Z);
		/*DetectSlope((Result.Location - this->ArrayRaycastVerticalCarAngle[0]->GetComponentLocation()).GetSafeNormal());
		DetectSlope((Result.Location - this->ArrayRaycastVerticalCarAngle[1]->GetComponentLocation()).GetSafeNormal());*/	
	}
	if(Result.GetActor() == nullptr) return;
	FlyingCar(Result.ImpactPoint);
	if(Result.GetActor()->ActorHasTag(this->BoostTag) && !this->CarStruct.IsBoosted)
	{
		const AMyGroundBoostPlate* GroundBoostPlate = Cast<AMyGroundBoostPlate>(Result.GetActor());
		if(GroundBoostPlate == nullptr) return;
		this->BoostPlate(GroundBoostPlate->PowerBoost);
	}
/*	if(LastActorHit == nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("%s"),*Result.GetActor()->GetActorNameOrLabel())
		LastActorHit = Result.GetActor();
		FlyingCar(Result.ImpactPoint);
	}else if(LastActorHit != Result.GetActor())
	{
		UE_LOG(LogTemp,Warning,TEXT("%s"),*Result.GetActor()->GetActorNameOrLabel())
		LastActorHit = Result.GetActor();
		FlyingCar(Result.ImpactPoint);
	}*/
	//FlyingCar(FVector::Distance(Result.ImpactPoint,this->GetActorLocation()));
}

FRotator AMyPawnCar::DetectSlope(FVector FloorNormal)
{
	//const float AngleX = UKismetMathLibrary::DegAcos(FVector::DotProduct(this->CarCollision->GetForwardVector(),FloorNormal));
	const FRotator CarRotation = this->GetActorRotation();
	const float AngleX = UKismetMathLibrary::MakeRotFromYZ(this->CarCollision->GetRightVector(),FloorNormal).Pitch;
	const float AngleY = CarRotation.Yaw;
	const float AngleZ = UKismetMathLibrary::MakeRotFromXZ(this->CarCollision->GetForwardVector(),FloorNormal).Roll;//CarRotation.Roll;
	const FRotator NewCarRotation = {AngleX,AngleY,AngleZ};
	return NewCarRotation;
	//UE_LOG(LogTemp,Warning,TEXT("AngleFloor,%f %f %f"), NewCarRotation.Pitch, NewCarRotation.Yaw, NewCarRotation.Roll);
}

void AMyPawnCar::RotateCarForSlope(FRotator NewRotation)
{
	this->CarCollision->GetBodyInstance()->bLockXRotation = false;
	this->CarCollision->GetBodyInstance()->bLockYRotation = false;
	this->CarCollision->GetBodyInstance()->bLockZRotation = false;
	this->CarCollision->GetBodyInstance()->SetDOFLock(EDOFMode::Default);
	//FRotator CarRotation = this->GetActorRotation();
	//CarRotation.Pitch = AngleX - 90;
	//this->SetActorRotation(CarRotation);
	this->SetActorRotation(NewRotation);
	this->CarCollision->GetBodyInstance()->bLockXRotation = true;
	this->CarCollision->GetBodyInstance()->bLockYRotation = true;
	this->CarCollision->GetBodyInstance()->bLockZRotation = true;
	this->CarCollision->GetBodyInstance()->SetDOFLock(EDOFMode::Default);
}

void AMyPawnCar::CarGotGrounded_Implementation()
{
	
}

void AMyPawnCar::CarReverseGravity_Implementation()
{
	
}

void AMyPawnCar::SlowLeanActivate_Implementation()
{
	
}

void AMyPawnCar::CarFallOnAnotherCar_Implementation()
{
	
}

void AMyPawnCar::CarCollisionWithDecor_Implementation()
{
	
}

void AMyPawnCar::CarCollisionWithAnotherCar_Implementation()
{
	
}

void AMyPawnCar::CarBoost_Implementation()
{
	
}

void AMyPawnCar::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	if(Other == nullptr)return;
	if(Other == this)return;
	if(Other->ActorHasTag(this->DecorTag))
	{
		this->CarCollisionWithDecor();
	}else if(Other->ActorHasTag(this->CarTag))
	{
		this->CarCollisionWithAnotherCar();
	}/*else if(Other->ActorHasTag(this->BoostTag))
	{
		const AMyGroundBoostPlate* GroundBoostPlate = Cast<AMyGroundBoostPlate>(Other);
		if(GroundBoostPlate == nullptr) return;
		this->BoostPlate(GroundBoostPlate->PowerBoost);
	}*/
}

