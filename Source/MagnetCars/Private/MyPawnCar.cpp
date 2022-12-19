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
	this->CarCollision->SetEnableGravity(false);
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
	if(!CodeInputEnable) return;
	PlayerInputComponent->BindAxis("Forward",this,&AMyPawnCar::ForwardMovement);
	PlayerInputComponent->BindAxis("Right",this,&AMyPawnCar::RightMovement);

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
}

void AMyPawnCar::PhysicalCarMovement(FPhysScene_Chaos *_PhysScene,float DeltaTime)
{
	if(this->CarCollision == nullptr)return;
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
		if(this->CarCollision->IsGravityEnabled()) return;
		this->CarCollision->AddForce(-this->CarCollision->GetUpVector() * (CarStruct.IsGrounded ? CarStruct.CarMassGround : CarStruct.CarMassNotGrounded)
			* this->CarCollision->GetMass());
	}
	
	const FVector VelocityCar = this->CarCollision->GetPhysicsLinearVelocity();
	ContainerForwardAxis *= this->SpeedCurve->GetFloatValue(VelocityCar.Length() /(this->CarStruct.IsBoosted ? this->CarStruct.ActualMaxSpeedUnderBoost : this->CarStruct.MaxSpeed));
	if(this->LastGroundDetected != nullptr && false)
	{
		const FRotator RotationPlayer = this->GetActorRotation();
		const FRotator RotationForDirection = FRotator(this->LastGroundDetected->GetActorRotation().Pitch,RotationPlayer.Yaw,this->LastGroundDetected->GetActorRotation().Roll);
		//UE_LOG(LogTemp,Warning,TEXT("WTF DE %s"),*this->LastGroundDetected->GetActorRotation().ToString());
		this->CarCollision->AddForce(RotationForDirection.Vector() * ContainerForwardAxis);
	}
	else
	{
		this->CarCollision->AddForce(this->GetActorForwardVector() * ContainerForwardAxis);
	}
	
	//this->CarCollision->GetBodyInstance()->ClearForces();
	/*UE_LOG(LogTemp,Warning,TEXT("%f"),
		this->SpeedCurve->GetFloatValue(VelocityCar.Length() /(this->CarStruct.IsBoosted ? this->CarStruct.ActualMaxSpeedUnderBoost : this->CarStruct.MaxSpeed)));*/
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
		//UE_LOG(LogTemp,Warning,TEXT("test"));
		const FVector Direction = -this->GetActorUpVector();
		this->CarCollision->AddForce(Direction * GetWorld()->GetGravityZ() * MagneticForceTowardUp);
	}
	else
	{
		const FVector Direction = this->GetActorUpVector();
		const float MassCar = this->CarCollision->GetMass();
		const float HalfSizeBoxGround = this->CarStruct.DistanceWithTheGround;
		//this->CarCollision->SetEnableGravity(false);
		FVector LocationCar = this->GetActorLocation();
		LocationCar.Z = ImpactPoint.Z + (this->CarStruct.IsOnReverseGravity ? -HalfSizeBoxGround: HalfSizeBoxGround);
		this->SetActorLocation(LocationCar);
	}
}


void AMyPawnCar::CarGravity()
{
	if(this->CarCollision == nullptr)return;
	this->CarReverseGravity();
	this->CarCollision->GetBodyInstance()->bLockXRotation = false;
	this->CarCollision->GetBodyInstance()->bLockYRotation = false;
	this->CarCollision->GetBodyInstance()->SetDOFLock(EDOFMode::Default);
	this->CarStruct.IsOnReverseGravity = !CarStruct.IsOnReverseGravity;
	//this->CarCollision->SetEnableGravity(!CarStruct.IsOnReverseGravity);
	FRotator CarRotation = this->GetActorRotation();
	CarRotation.Roll += this->CarStruct.IsOnReverseGravity ? 180 : -180;
	this->SetActorRotation(CarRotation);
	this->CarCollision->GetBodyInstance()->bLockXRotation = true;
	this->CarCollision->GetBodyInstance()->bLockYRotation = true;
	this->CarCollision->GetBodyInstance()->SetDOFLock(EDOFMode::Default);
	if(!this->ResetGravityInstant) return;
	FVector VelocityCar = this->CarCollision->GetPhysicsLinearVelocity();
	VelocityCar.Z = 0;
	this->CarCollision->GetBodyInstance()->ClearForces();
	this->CarCollision->SetPhysicsLinearVelocity(VelocityCar);
}

void AMyPawnCar::InvertGravity()
{
	if(this->CarCollision == nullptr)return;
	this->CarCollision->AddForce(-this->CarCollision->GetUpVector() * this->CarCollision->GetMass()
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

void AMyPawnCar::DetectGround()
{
	FHitResult Result;
	TArray<AActor*> ActorIgnored;
	ActorIgnored.Add(this);
	const FVector StartPosition = this->GetActorLocation() - (this->CarStruct.IsOnReverseGravity ? -1 * this->CarStruct.StartBoxGroundDetection: this->CarStruct.StartBoxGroundDetection);
	const FVector EndPosition = this->GetActorLocation() - (this->CarStruct.IsOnReverseGravity ? -1 * this->CarStruct.EndBoxGroundDetection : this->CarStruct.EndBoxGroundDetection);
	//const FVector StartPosition = this->CarCollision->GetComponentLocation() - (this->CarStruct.IsOnReverseGravity ? -1 * this->CarStruct.StartBoxGroundDetection : this->CarStruct.StartBoxGroundDetection);
	//const FVector EndPosition = this->CarCollision->GetComponentLocation() - (this->CarStruct.IsOnReverseGravity ? -1 * this->CarStruct.EndBoxGroundDetection : this->CarStruct.EndBoxGroundDetection);
	/*const bool ResultHit = UKismetSystemLibrary::BoxTraceSingle(this, StartPosition,EndPosition,
		CarStruct.HalfSizeBoxGroundDetection,FRotator::ZeroRotator,TraceChannel,false,ActorIgnored,
		EDrawDebugTrace::ForOneFrame,Result,true,FLinearColor::Blue,FLinearColor::Red,5);*/
	FRotator CarRotation = this->GetActorRotation();
	CarRotation.Roll *= (this->CarStruct.BoxFollowRotationRoll ? 1 : 0);
	CarRotation.Yaw *= (this->CarStruct.BoxFollowRotationYaw ? 1 : 0);
	CarRotation.Pitch *= (this->CarStruct.BoxFollowRotationPitch ? 1 : 0);
	const bool ResultHit = UKismetSystemLibrary::BoxTraceSingle(this, StartPosition,EndPosition,
		CarStruct.HalfSizeBoxGroundDetection,CarRotation,UEngineTypes::ConvertToTraceType(ECC_Visibility),false,ActorIgnored,
		EDrawDebugTrace::ForOneFrame,Result,true,FLinearColor::Blue,FLinearColor::Red,5); 
	if(!ResultHit)
	{
		CarStruct.IsGrounded = false;
		LastGroundDetected = nullptr;
		return;
	}
	if(!this->CarStruct.IsGrounded)
	{
		this->CarStruct.IsGrounded = true;
		this->CarGotGrounded();
	}
	this->LastGroundDetected = Result.GetActor();
	if(!BlockSlope)
	{
		FRotator NewRotation;
		NewRotation = DetectSlope(Result.ImpactNormal);
		FRotator NewRotationCar = this->GetActorRotation();
		NewRotationCar.Pitch =  NewRotation.Pitch;
		NewRotationCar.Roll =  NewRotation.Roll;
		//UE_LOG(LogTemp,Warning,TEXT("%s"),*NewRotation.ToString());

		FRotator Test2 = UKismetMathLibrary::RInterpTo_Constant(this->GetActorRotation(),NewRotationCar,this->GetWorld()->GetDeltaSeconds(),
			this->CarStruct.SpeedForSlopeAdjustement);
		this->RotateCarForSlope(Test2);
	}
	if(Result.GetActor() == nullptr) return;
	FlyingCar(Result.ImpactPoint);
	if(Result.GetActor()->ActorHasTag(this->BoostTag) && !this->CarStruct.IsBoosted)
	{
		const AMyGroundBoostPlate* GroundBoostPlate = Cast<AMyGroundBoostPlate>(Result.GetActor());
		if(GroundBoostPlate == nullptr) return;
		this->BoostPlate(GroundBoostPlate->PowerBoost);
	}
}

FRotator AMyPawnCar::DetectSlope(FVector FloorNormal)
{
	const FRotator CarRotation = this->GetActorRotation();
	const float AngleX = UKismetMathLibrary::MakeRotFromYZ(this->CarCollision->GetRightVector(),FloorNormal).Pitch;
	const float AngleY = CarRotation.Yaw;
	const float AngleZ = UKismetMathLibrary::MakeRotFromXZ(this->CarCollision->GetForwardVector(),FloorNormal).Roll;//CarRotation.Roll;
	const FRotator NewCarRotation = {AngleX,AngleY,AngleZ};
	return NewCarRotation;
}

void AMyPawnCar::RotateCarForSlope(FRotator NewRotation)
{
	this->CarCollision->GetBodyInstance()->bLockXRotation = false;
	this->CarCollision->GetBodyInstance()->bLockYRotation = false;
	this->CarCollision->GetBodyInstance()->bLockZRotation = false;
	this->CarCollision->GetBodyInstance()->SetDOFLock(EDOFMode::Default);
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
	}
}

