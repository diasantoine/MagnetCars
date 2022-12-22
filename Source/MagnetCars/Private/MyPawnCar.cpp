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
	this->CarCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("carCollision")); // Create the collision of the car, which will be the root component
	this->RaycastPosition = this->CreateDefaultSubobject<USceneComponent>("RaycastPosition");
	this->SetRootComponent(CarCollision);
	this->RaycastPosition->SetupAttachment(this->CarCollision);
	this->CarCollision->SetEnableGravity(false);// Use my gravity
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
	this->GetWorld()->GetPhysicsScene()->OnPhysSceneStep.AddUObject(this,&AMyPawnCar::PhysicalCarMovement);// Call the physical Tick to get a better physical response
}

// Called every frame
void AMyPawnCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(this->CarCollision)// For the boost
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
// Set Up Input
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if(!CodeInputEnable) return;// Disable the setup player for the network, the network has his own input
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


void AMyPawnCar::ForwardMovement(const float AxisValue)
// I need to keep this code for the moment in case the tick physics doesn't work like i would, it's the same thing as in the functionPhysical Car Movement
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
		//this->CarCollision->AddForce(GetActorForwardVector() * axisValue * CarStruct.Acceleration * this->CarCollision->GetMass());
		//FVector VelocityCar = this->CarCollision->GetComponentVelocity();
		
		ContainerForwardAxis = AxisValue * CarStruct.Acceleration * this->CarCollision->GetMass() * this->CarCollision->GetLinearDamping();// Get Axis Input
		if(this->CarStruct.IsBoosted)
		{
			this->CarStruct.ActualMaxSpeedUnderBoost = UKismetMathLibrary::FInterpTo_Constant(this->CarStruct.ActualMaxSpeedUnderBoost,this->CarStruct.MaxSpeed,this->GetWorld()->GetDeltaSeconds(),
				this->CarStruct.SpeedResetMaxSpeed);
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
		//this->CarCollision->AddForce(GetActorForwardVector() * axisValue * CarStruct.AccelerationNotGrounded * this->CarCollision->GetMass());
		//FVector VelocityCar = this->CarCollision->GetComponentVelocity();
		ContainerForwardAxis = AxisValue * CarStruct.AccelerationNotGrounded * this->CarCollision->GetMass() * this->CarCollision->GetLinearDamping();
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
// The physical ticks
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
	if(this->CarStruct.IsOnReverseGravity && !this->CarStruct.IsGrounded)
	{
		InvertGravity();
	}
	else if(!this->CarCollision->IsGravityEnabled() && !this->CarStruct.IsGrounded)
	{
		this->CarCollision->AddForce(-this->CarCollision->GetUpVector() * (CarStruct.IsGrounded ? CarStruct.CarMassGround : CarStruct.CarMassNotGrounded)
			* this->CarCollision->GetMass());// Forward
	}
	
	const FVector VelocityCar = this->CarCollision->GetPhysicsLinearVelocity();
	ContainerForwardAxis *= this->SpeedCurve->GetFloatValue(VelocityCar.Length() /(this->CarStruct.IsBoosted ? this->CarStruct.ActualMaxSpeedUnderBoost : this->CarStruct.MaxSpeed));
	// The curve is there to limit the speed of the car, by lowering the acceleration t'ill 0
	if(this->LastGroundDetected != nullptr && false)// Being Test
	{
		const FRotator RotationPlayer = this->GetActorRotation();
		const FRotator RotationForDirection = FRotator(this->LastGroundDetected->GetActorRotation().Pitch,RotationPlayer.Yaw,this->LastGroundDetected->GetActorRotation().Roll);
		this->CarCollision->AddForce(RotationForDirection.Vector() * ContainerForwardAxis);
	}
	else
	{
		this->CarCollision->AddForce(this->GetActorForwardVector() * ContainerForwardAxis);
	}
	
	//this->CarCollision->GetBodyInstance()->ClearForces(); Being Test
	//this->CarCollision->GetBodyInstance()->SetLinearVelocity(VelocityCar.GetSafeNormal() * FMath::Clamp(VelocityCar.Length(),0,CarStruct.MaxSpeed),true,true);
	/*FRigidBodyState* Test = nullptr;
	this->CarCollision->GetRigidBodyState(*Test);
	if(Test == nullptr)return;
	Test->LinVel = VelocityCar.GetSafeNormal() * FMath::Clamp(VelocityCar.Length(),0,CarStruct.MaxSpeed);*/
}



void AMyPawnCar::RightMovement(const float AxisValue)
{
	if(CarCollision == nullptr)return;
	/*this->CarCollision->GetBodyInstance()->bLockZRotation = false;
	this->CarCollision->GetBodyInstance()->SetDOFLock(EDOFMode::Default);*/
	if(CarStruct.IsGrounded)
	{
		this->AddActorLocalRotation(FRotator(0,CarStruct.AmountRotationCar * AxisValue,0));
	}
	else
	{
		this->AddActorLocalRotation(FRotator(0,CarStruct.AmountRotationCarNotGrounded * AxisValue,0));
	}
	/*this->CarCollision->GetBodyInstance()->bLockZRotation = true;
	this->CarCollision->GetBodyInstance()->SetDOFLock(EDOFMode::Default);*/
}

void AMyPawnCar::CarDrift(float value)
// This function make the static mesh rotate in yaw, not the collider it's just visual. But with the amount of lean of the vehicle some force will be added to rotate faster
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
			(CarStruct.IsGrounded ? this->CarStruct.SpeedResetLeanGrounded : this->CarStruct.SpeedResetLeanNotGrounded)));// Reset the rotation
	}
	else
	{
		/*this->CarCollision->GetBodyInstance()->bLockXRotation = false;
		this->CarCollision->GetBodyInstance()->bLockYRotation = false;
		this->CarCollision->GetBodyInstance()->SetDOFLock(EDOFMode::Default);*/
		this->TemporaryScene->AddLocalRotation(FRotator(0,0,(CarStruct.IsGrounded ? CarStruct.AmountOfLean : CarStruct.AmountOfLeanNotGrounded) * value));// Add the rotation
		/*this->CarCollision->GetBodyInstance()->bLockXRotation = true;
		this->CarCollision->GetBodyInstance()->bLockYRotation = true;
		this->CarCollision->GetBodyInstance()->SetDOFLock(EDOFMode::Default);*/
	}
	const FRotator ContainerRotation = this->TemporaryScene->GetRelativeRotation();
	const float RotationRoll = FMath::Clamp(ContainerRotation.Roll, -CarStruct.MaxLean, CarStruct.MaxLean);
	this->TemporaryScene->SetRelativeRotation(FRotator(ContainerRotation.Pitch,ContainerRotation.Yaw,RotationRoll));
	if(this->CarStruct.IsLeanCreateSlow)
	{
		if(FMath::Abs(this->TemporaryScene->GetRelativeRotation().Roll) >= this->CarStruct.AmountOfLeanToStartSlow)// Slow the speed if there is too much lean
		{
			this->SlowLeanActivate();
			this->CarCollision->AddForce(-this->CarCollision->GetForwardVector() * this->CarCollision->GetMass()
				* (this-CarStruct.IsGrounded ? this->CarStruct.LeanSlowGrounded : this->CarStruct.LeanSlowAir));
		}
	}
	if(this->CarStruct.DragWholeBodyWhenLean)
	{
		this->CarCollision->AddForce(GetActorRightVector() * (RotationRoll / CarStruct.MaxLean) * CarStruct.AccelerationLean * this->CarCollision->GetMass());// The force added
	}
}

void AMyPawnCar::FlyingCar(const FHitResult ImpactPoint)
{
	if(CarCollision == nullptr) return;
	if(this->CarCollision->ComponentVelocity.Z < 0 && false)
	{
		//const FVector Direction = -this->GetActorUpVector();
		//this->CarCollision->AddForce(Direction * GetWorld()->GetGravityZ() * MagneticForceTowardUp);// It was in case of negative Movement but for the moment it's not useful
	}
	else
	{
		const FVector Direction = this->GetActorUpVector();
		const float MassCar = this->CarCollision->GetMass();
		const float HalfSizeBoxGround = this->CarStruct.DistanceWithTheGround;
		//const UE::Math::TTransform<double> TestTransform;
		//FVector LocationCar = this->GetActorTransform().GetRelativeTransform(TestTransform).GetLocation();
		FVector LocationCar = this->GetActorLocation();// There is a lot of commentary since the code isn't perfect and it's still in progress
		//this->CarCollision->SetEnableGravity(false); If i enable the gravity back i need to know where it was affected before
		/*LocationCar += this->GetActorUpVector() * (this->CarStruct.IsOnReverseGravity ?  FVector::Distance(ImpactPoint,this->GetActorLocation() / -HalfSizeBoxGround):
			FVector::Distance(ImpactPoint,this->GetActorLocation() /HalfSizeBoxGround));*/
		//LocationCar.Z = ImpactPoint.Z + (this->CarStruct.IsOnReverseGravity ? -HalfSizeBoxGround: HalfSizeBoxGround);
		//LocationCar.X = ImpactPoint.X + (this->CarStruct.IsOnReverseGravity ? -HalfSizeBoxGround: HalfSizeBoxGround);
		/*LocationCar.Y = ImpactPoint.Y + (this->CarStruct.IsOnReverseGravity ? -HalfSizeBoxGround: HalfSizeBoxGround) -
			(this->CarStruct.IsOnReverseGravity ? -HalfSizeBoxGround: HalfSizeBoxGround) / this->GetActorRotation().Pitch / 90;*/
		//FVector LocationUpCar = this->GetActorUpVector() * this->CarStruct.DistanceWithTheGround + ImpactPoint.ImpactPoint;
		FVector LocationUpCar = this->GetActorUpVector() * this->CarStruct.DistanceWithTheGround + ImpactPoint.ImpactPoint;
		//UE_LOG(LogTemp,Warning,TEXT("%s"),*ImpactPoint.ImpactPoint.ToString());
		//LocationCar.Z = LocationUpCar.Z;
		//LocationCar.Z = ImpactPoint.ImpactPoint.Z + (this->CarStruct.IsOnReverseGravity ? -HalfSizeBoxGround: HalfSizeBoxGround);// Give the height the car should always have for flying 
		//this->SetActorLocation(LocationCar);
		this->SetActorLocation(LocationUpCar);
	}
}


void AMyPawnCar::CarGravity()
{
	if(this->CarCollision == nullptr)return;
	this->CarReverseGravity();
	/*this->CarCollision->GetBodyInstance()->bLockXRotation = false;
	this->CarCollision->GetBodyInstance()->bLockYRotation = false;
	this->CarCollision->GetBodyInstance()->SetDOFLock(EDOFMode::Default);*/
	this->CarStruct.IsOnReverseGravity = !CarStruct.IsOnReverseGravity;
	//this->CarCollision->SetEnableGravity(!CarStruct.IsOnReverseGravity); If i enable the gravity back i need to know where it was affected before
	FRotator CarRotation = this->GetActorRotation();
	CarRotation.Roll += this->CarStruct.IsOnReverseGravity ? 180 : -180;// This function invert the gravity of the player and rotate him
	this->SetActorRotation(CarRotation);
	/*this->CarCollision->GetBodyInstance()->bLockXRotation = true;
	this->CarCollision->GetBodyInstance()->bLockYRotation = true;
	this->CarCollision->GetBodyInstance()->SetDOFLock(EDOFMode::Default);*/
	if(!this->ResetGravityInstant) return;
	FVector VelocityCar = this->CarCollision->GetPhysicsLinearVelocity();
	VelocityCar.Z = 0;
	this->CarCollision->GetBodyInstance()->ClearForces();
	this->CarCollision->SetPhysicsLinearVelocity(VelocityCar);
}

void AMyPawnCar::InvertGravity() const
{
	if(this->CarCollision == nullptr)return;
	this->CarCollision->AddForce(-this->CarCollision->GetUpVector() * this->CarCollision->GetMass()
		* (CarStruct.IsGrounded ? CarStruct.CarMassGroundInversedGravity : CarStruct.CarMassNotGroundedInversedGravity));// Invert Gravity
}

void AMyPawnCar::BoostPlate(const float Boost)
// Boost Plate still in progress
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
// Reset Scene with an input
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void AMyPawnCar::CarRespawn()
// Replace the player at the start
{
	this->CarCollision->ComponentVelocity = FVector::Zero();
	this->TemporaryScene->SetRelativeRotation(FRotator::ZeroRotator);
	APawn::SetActorLocation(ResetPosition);
	APawn::SetActorRotation(FRotator::ZeroRotator);
	this->CarStruct.IsOnReverseGravity = false;
	this->CarStruct.IsGrounded = false;
}

void AMyPawnCar::LastPosition(FVector lastPositionReturned, AActor* roadExit)
// Not in use for the moment but it will be useful when the player fall
{
	/*this->LastCarPositionOnRoad = lastPositionReturned;
	this->MiddleOfTheRoad = roadExit->GetStreamingBounds().GetCenter();*/
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
		EDrawDebugTrace::ForOneFrame,Result,true,FLinearColor::Blue,FLinearColor::Red,5);*/ // Old Raycast, i need it in case i break the new one because it's in testing phase
	FRotator CarRotation = this->GetActorRotation();
	CarRotation.Roll *= (this->CarStruct.BoxFollowRotationRoll ? 1 : 0);
	CarRotation.Yaw *= (this->CarStruct.BoxFollowRotationYaw ? 1 : 0);
	CarRotation.Pitch *= (this->CarStruct.BoxFollowRotationPitch ? 1 : 0);
	// Raycast with a box to detect the ground, i prefer to do that to not have the system breaking because of some mistake in the LD
	/*const bool ResultHit = UKismetSystemLibrary::BoxTraceSingle(this, StartPosition,EndPosition,
		CarStruct.HalfSizeBoxGroundDetection,CarRotation,UEngineTypes::ConvertToTraceType(ECC_Visibility),false,ActorIgnored,
		EDrawDebugTrace::ForOneFrame,Result,true,FLinearColor::Blue,FLinearColor::Red,5);*/
	FHitResult ResultHit2;
	FHitResult ResultHit3;
	const FName TraceTag("MyTraceTag");
	this->GetWorld()->DebugDrawTraceTag = TraceTag;
	FCollisionQueryParams CollisionParams2;
	CollisionParams2.TraceTag = TraceTag;
	CollisionParams2.AddIgnoredActor(this);
	FCollisionQueryParams CollisionParams;
	CollisionParams.TraceTag = TraceTag;
	CollisionParams.AddIgnoredActor(this);
	this->GetWorld()->LineTraceSingleByChannel(ResultHit2 ,this->GetActorLocation(),
		this->GetActorLocation() + -this->GetActorUpVector() * DistanceRaycast,ECC_Visibility,
		CollisionParams,FCollisionResponseParams::DefaultResponseParam);
	this->GetWorld()->LineTraceSingleByChannel(ResultHit3 ,this->GetActorLocation(),
	this->GetActorLocation() + this->GetActorForwardVector() * DistanceRaycast * 10,ECC_Visibility,
	CollisionParams2,FCollisionResponseParams::DefaultResponseParam);
	if(ResultHit2.GetActor() == nullptr)//!ResultHit)// Doesn't detect ground
	{
		CarStruct.IsGrounded = false;
		LastGroundDetected = nullptr;
		return;
	}
	if(!this->CarStruct.IsGrounded)// Detect ground
	{
		this->CarStruct.IsGrounded = true;
		this->CarGotGrounded();
	}
	this->LastGroundDetected = ResultHit2.GetActor();
	if(!BlockSlope)// This is where i adjust the rotation of the car with the slope of the ground
	{
		/*FRotator SlopeRotation;
		SlopeRotation = DetectSlope(Result.ImpactNormal);
		FRotator NewRotationCar = this->GetActorRotation();
		NewRotationCar.Pitch =  SlopeRotation.Pitch;
		NewRotationCar.Roll =  SlopeRotation.Roll;*/
		//NewRotationCar.Yaw =  SlopeRotation.Yaw;
		FRotator NewRotationCar2 = this->GetActorRotation();
		if(ResultHit2.GetActor() != nullptr)// This is the new raycast, same function but the raycast change
		{
			FRotator SlopeRotation2;
			SlopeRotation2 = DetectSlope(ResultHit2.ImpactNormal);
			//UE_LOG(LogTemp,Warning,TEXT("Position,%s"),*ResultHit2.GetActor()->GetName());
			NewRotationCar2.Pitch =  SlopeRotation2.Pitch;
			NewRotationCar2.Roll =  SlopeRotation2.Roll;
			UE_LOG(LogTemp,Warning,TEXT("Rotation,%s"),*NewRotationCar2.ToString());
		}
		if(true)// Trying a new raycast to adjust better my car rotation, in progress and disable so you can play "normally"
		{
			FRotator NewRotation = UKismetMathLibrary::RInterpTo_Constant(this->GetActorRotation(),
		NewRotationCar2,this->GetWorld()->GetDeltaSeconds(),this->CarStruct.SpeedForSlopeAdjustement);
			this->RotateCarForSlope(NewRotation);
		}
		else
		{
			/*FRotator NewRotation = UKismetMathLibrary::RInterpTo_Constant(this->GetActorRotation(),
				NewRotationCar,this->GetWorld()->GetDeltaSeconds(),this->CarStruct.SpeedForSlopeAdjustement);// Adjust the rotation smoothly with a speed
			this->RotateCarForSlope(NewRotation);*/
		}
	}
	if(ResultHit2.GetActor() != nullptr)//Result.GetActor() == nullptr) return;// If the ground detect something which isn't an actor, it would be dangerous go further. The code would crash or be garbage since it need an actor
	FlyingCar(ResultHit2);// Update the flying car position
	/*if(Result.GetActor()->ActorHasTag(this->BoostTag) && !this->CarStruct.IsBoosted && false)// Boost Zone but still in progress
	{
		const AMyGroundBoostPlate* GroundBoostPlate = Cast<AMyGroundBoostPlate>(Result.GetActor());
		if(GroundBoostPlate == nullptr) return;
		this->BoostPlate(GroundBoostPlate->PowerBoost);
	}*/
}

FRotator AMyPawnCar::DetectSlope(const FVector FloorNormal) const
// Detect the slope of the road
{
	const FRotator CarRotation = this->GetActorRotation();
	const float AngleX = UKismetMathLibrary::MakeRotFromYZ(this->CarCollision->GetRightVector(),FloorNormal).Pitch;// Adjust the Pitch Rotation with the slope of the ground
	const float AngleY =  CarRotation.Yaw;// We don't want the car to have his yaw updated by the ground, only the player can or physical hit
	const float AngleZ = UKismetMathLibrary::MakeRotFromXZ(this->CarCollision->GetForwardVector(),FloorNormal).Roll;// Adjust the Roll Rotation with the slope of the ground
	const FRotator NewCarRotation = {AngleX,AngleY,AngleZ};
	return NewCarRotation;
}

void AMyPawnCar::RotateCarForSlope(const FRotator NewRotation)
{
	/*this->CarCollision->GetBodyInstance()->bLockXRotation = false;
	this->CarCollision->GetBodyInstance()->bLockYRotation = false;
	this->CarCollision->GetBodyInstance()->bLockZRotation = false;
	this->CarCollision->GetBodyInstance()->SetDOFLock(EDOFMode::Default);*/
	this->SetActorRotation(NewRotation);// Give the new rotation to the car, the constraint activated or deactivated is a way to force the physics behave like the Game Designer wanted
	/*this->CarCollision->GetBodyInstance()->bLockXRotation = true;
	this->CarCollision->GetBodyInstance()->bLockYRotation = true;
	this->CarCollision->GetBodyInstance()->bLockZRotation = true;
	this->CarCollision->GetBodyInstance()->SetDOFLock(EDOFMode::Default);*/
}

void AMyPawnCar::CarGotGrounded_Implementation()// Event which can be get in the Blueprint of the car, useful for sound for exemple
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
// Notify when a collision happen
{
	if(Other == nullptr)return;
	if(Other == this)return;
	UE_LOG(LogTemp,Warning,TEXT("%s"),*Other->GetName());
	if(Other->ActorHasTag(this->DecorTag))// Test the tag of the collider to choose what response it should give
	{
		this->CarCollisionWithDecor();
	}else if(Other->ActorHasTag(this->CarTag))
	{
		this->CarCollisionWithAnotherCar();
	}
}

