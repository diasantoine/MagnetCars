// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawnCar.h"

#include "MyGroundBoostPlate.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

// Sets default values
AMyPawnCar::AMyPawnCar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->CarCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("carCollision")); // Create the collision of the car, which will be the root component
	this->CarCollisionUp = CreateDefaultSubobject<UBoxComponent>(TEXT("carCollisionUp"));
	this->RaycastPosition = this->CreateDefaultSubobject<USceneComponent>("RaycastPosition");
	this->SetRootComponent(CarCollision);
	this->RaycastPosition->SetupAttachment(this->CarCollision);
	this->CarCollisionUp->SetupAttachment(this->CarCollision);
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

	this->CarCollision->OnComponentBeginOverlap.AddDynamic(this,&AMyPawnCar::OverlapBegin);
	this->CarCollision->OnComponentEndOverlap.AddDynamic(this,&AMyPawnCar::AMyPawnCar::OverlapEnd);
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
			MyVelocity.X = FMath::Clamp(MyVelocity.X,-this->CarStruct.ActualMaxSpeedUnderEffect,this->CarStruct.ActualMaxSpeedUnderEffect);
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
	PlayerInputComponent->BindAxis("LookUp",this,&AMyPawnCar::UpMovement);

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
	if(this->CarStruct.IsGrounded)
	{
		ForwardAxis = AxisValue * (AxisValue >=0 ? this->CarStruct.Acceleration : this->CarStruct.AccelerationBackWard) *
			this->CarCollision->GetMass() * this->CarCollision->GetLinearDamping();// Get Axis Input
	}
	else
	{
		ForwardAxis = AxisValue * (AxisValue >=0 ? this->CarStruct.AccelerationNotGrounded : this->CarStruct.AccelerationBackWardNotGrounded) *
			this->CarCollision->GetMass() * this->CarCollision->GetLinearDamping();
	}
	//this->Server_ForwardMovement(AxisValue);
}

void AMyPawnCar::Server_ForwardMovement_Implementation(const float AxisValue)
// I need to keep this code for the moment in case the tick physics doesn't work like i would, it's the same thing as in the functionPhysical Car Movement
{
	if(CarCollision == nullptr)return;
	if(this->CarStruct.IsGrounded)
	{
		ForwardAxis = AxisValue * CarStruct.Acceleration * this->CarCollision->GetMass() * this->CarCollision->GetLinearDamping();// Get Axis Input
	}
	else
	{
		ForwardAxis = AxisValue * CarStruct.AccelerationNotGrounded * this->CarCollision->GetMass() * this->CarCollision->GetLinearDamping();
	}
}

void AMyPawnCar::PhysicalCarMovement(FPhysScene_Chaos *_PhysScene,float DeltaTime)
// The physical ticks
{
	if(this->CarCollision == nullptr)return;
	this->DetectGround();
	this->BoostSpeedBehaviour();
	this->SlowSpeedBehaviour();
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
	if(!this->CarStruct.IsGrounded)
	{
		if(this->CarStruct.IsOnReverseGravity)
		{
			this->InvertGravity();
		}
		else
		{
			this->Gravity();
		}
	}
	
	const FVector VelocityCar = this->CarCollision->GetPhysicsLinearVelocity();
	ForwardAxis *= this->SpeedCurve->GetFloatValue(VelocityCar.Length() /(this->CarStruct.IsBoosted || this->CarStruct.IsSlowed
		? this->CarStruct.ActualMaxSpeedUnderEffect : this->CarStruct.MaxSpeed));
	// The curve is there to limit the speed of the car, by lowering the acceleration t'ill 0
	if(this->LastGroundDetected != nullptr && false)// Being Test
	{
		const FRotator RotationPlayer = this->GetActorRotation();
		const FRotator RotationForDirection = FRotator(this->LastGroundDetected->GetActorRotation().Pitch,RotationPlayer.Yaw,this->LastGroundDetected->GetActorRotation().Roll);
		this->CarCollision->AddForce(RotationForDirection.Vector() * ForwardAxis);
	}
	else
	{
		this->CarCollision->AddForce(this->GetActorForwardVector() * ForwardAxis);
	}
}

void AMyPawnCar::BoostSpeedBehaviour()
{
	if(this->CarStruct.IsBoosted)
	{
		if(this->CarStruct.ActualMaxSpeedUnderEffect <= this->CarStruct.MaxSpeed)
		{
			this->CarStruct.IsBoosted = false;
			this->CarStruct.ActualMaxSpeedUnderEffect = this->CarStruct.MaxSpeed;
		}
		else
		{
			this->CarStruct.ActualMaxSpeedUnderEffect = UKismetMathLibrary::FInterpTo_Constant(this->CarStruct.ActualMaxSpeedUnderEffect,this->CarStruct.MaxSpeed,this->GetWorld()->GetDeltaSeconds(),
				this->CarStruct.SpeedResetMaxSpeedAfterBoost);
		}
	}
}

void AMyPawnCar::SlowSpeedBehaviour()
{
	if(this->CarStruct.IsSlowed)
	{
		if(this->CarStruct.ActualMaxSpeedUnderEffect <= this->CarStruct.MaxSpeed)
		{
			this->CarStruct.IsSlowed = false;
			this->CarStruct.ActualMaxSpeedUnderEffect = this->CarStruct.MaxSpeed;
		}
		else
		{
			this->CarStruct.ActualMaxSpeedUnderEffect = UKismetMathLibrary::FInterpTo_Constant(this->CarStruct.ActualMaxSpeedUnderEffect,this->CarStruct.MaxSpeed,this->GetWorld()->GetDeltaSeconds(),
				this->CarStruct.SpeedResetMaxSpeedAfterSlow);
		}
	}
}

void AMyPawnCar::RaycastOff()
{
	if(this->ContainerTimeBeforeRaycastOn >= this->CarStruct.TimeBeforeRaycastOn)
	{
		this->ContainerTimeBeforeRaycastOn = 0;
		this->CarStruct.IsRaycastActive = true;
	}
	else
	{
		this->ContainerTimeBeforeRaycastOn += this->GetWorld()->GetDeltaSeconds();
	}
}


void AMyPawnCar::RightMovement(const float AxisValue)
{
	if(CarCollision == nullptr)return;
	const FVector VelocityCar = this->CarCollision->GetPhysicsLinearVelocity();
	float AmountRotation;
	if(CarStruct.IsGrounded)
	{
		AmountRotation = CarStruct.AmountRotationCarRight * AxisValue;
		AmountRotation *= this->RotationRightCurve->GetFloatValue(VelocityCar.Length() /(this->CarStruct.IsBoosted || this->CarStruct.IsSlowed
			? this->CarStruct.ActualMaxSpeedUnderEffect : this->CarStruct.MaxSpeed));
	}
	else
	{
		AmountRotation = CarStruct.AmountRotationRightCarNotGrounded * AxisValue;
		AmountRotation *= this->RotationRightCurve->GetFloatValue(VelocityCar.Length() /(this->CarStruct.IsBoosted || this->CarStruct.IsSlowed
	? this->CarStruct.ActualMaxSpeedUnderEffect : this->CarStruct.MaxSpeed));
	}
	this->AddActorLocalRotation(FRotator(0,AmountRotation,0));
	//this->Server_RightMovement(AxisValue);
}

void AMyPawnCar::UpMovement(float AxisValue)
{
	if(CarCollision == nullptr)return;
	if(this->CarStruct.IsGrounded && !this->CarStruct.IsRotationUpActiveWhenGrounded) return;
	float AmountRotation;
	const FVector VelocityCar = this->CarCollision->GetPhysicsLinearVelocity();
	if(CarStruct.IsGrounded)
	{
		AmountRotation = CarStruct.AmountRotationCarUp * AxisValue;
		AmountRotation *= this->RotationUpCurve->GetFloatValue(VelocityCar.Length() /(this->CarStruct.IsBoosted || this->CarStruct.IsSlowed
			? this->CarStruct.ActualMaxSpeedUnderEffect : this->CarStruct.MaxSpeed));
	}
	else
	{
		AmountRotation = CarStruct.AmountRotationUpCarNotGrounded * AxisValue;
		AmountRotation *= this->RotationUpCurve->GetFloatValue(VelocityCar.Length() /(this->CarStruct.IsBoosted || this->CarStruct.IsSlowed
	? this->CarStruct.ActualMaxSpeedUnderEffect : this->CarStruct.MaxSpeed));
	}
	this->AddActorLocalRotation(FRotator(AmountRotation,0,0));
}


void AMyPawnCar::Server_RightMovement_Implementation(const float AxisValue)
{
	if(CarCollision == nullptr)return;
	const FVector VelocityCar = this->CarCollision->GetPhysicsLinearVelocity();
	float AmountRotation;
	if(CarStruct.IsGrounded)
	{
		AmountRotation = CarStruct.AmountRotationCarRight * AxisValue;
		AmountRotation *= this->RotationRightCurve->GetFloatValue(VelocityCar.Length() /(this->CarStruct.IsBoosted || this->CarStruct.IsSlowed
			? this->CarStruct.ActualMaxSpeedUnderEffect : this->CarStruct.MaxSpeed));
	}
	else
	{
		AmountRotation = CarStruct.AmountRotationRightCarNotGrounded * AxisValue;
		AmountRotation *= this->RotationRightCurve->GetFloatValue(VelocityCar.Length() /(this->CarStruct.IsBoosted || this->CarStruct.IsSlowed
	? this->CarStruct.ActualMaxSpeedUnderEffect : this->CarStruct.MaxSpeed));
	}
	this->AddActorLocalRotation(FRotator(0,AmountRotation,0));
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
		this->TemporaryScene->AddLocalRotation(FRotator(0,0,(CarStruct.IsGrounded ? CarStruct.AmountOfLean : CarStruct.AmountOfLeanNotGrounded) * value));// Add the rotation
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
	//this->Server_CarDrift(value);
}

void AMyPawnCar::Server_CarDrift_Implementation(float value)
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
		this->TemporaryScene->AddLocalRotation(FRotator(0,0,(CarStruct.IsGrounded ? CarStruct.AmountOfLean : CarStruct.AmountOfLeanNotGrounded) * value));// Add the rotation
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
		//this->CarCollision->SetEnableGravity(false); If i enable the gravity back i need to know where it was affected before
		const FVector LocationUpCar = this->GetActorUpVector() * this->CarStruct.DistanceWithTheGround + ImpactPoint.ImpactPoint;
		this->SetActorLocation(LocationUpCar);
	}
	//this->Server_FlyingCar(ImpactPoint);
}

void AMyPawnCar::Server_FlyingCar_Implementation(FHitResult ImpactPoint)
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
		//this->CarCollision->SetEnableGravity(false); If i enable the gravity back i need to know where it was affected before
		const FVector LocationUpCar = this->GetActorUpVector() * this->CarStruct.DistanceWithTheGround + ImpactPoint.ImpactPoint;
		this->SetActorLocation(LocationUpCar);
	}
}



void AMyPawnCar::CarGravity()
{
	if(this->CarCollision == nullptr)return;
	if(this->CarStruct.IsInverseGravityOnCoolDown) return;
	if(this->ContainerNumberOfGravityChanged >= this->CarStruct.NumberOfGravityChange) return;
	this->ContainerNumberOfGravityChanged++;
	this->CarStruct.IsInverseGravityOnCoolDown = true;
	this->CarReverseGravity();
	this->CarStruct.IsOnReverseGravity = !CarStruct.IsOnReverseGravity;
	//this->CarCollision->SetEnableGravity(!CarStruct.IsOnReverseGravity); If i enable the gravity back i need to know where it was affected before
	FRotator CarRotation = this->GetActorRotation();
	CarRotation.Roll += this->CarStruct.IsOnReverseGravity ? 180 : -180;// This function invert the gravity of the player and rotate him
	this->SetActorRotation(CarRotation);
	if(this->CarStruct.DoesHitPointReset)
	{
		this->LastHitPoint = FVector::Zero();
	}
	else
	{
		this->LastHitPoint = -LastHitPoint;
	}
	this->CarStruct.IsRaycastActive = false;
	this->CarStruct.IsGrounded = false;
	if(!this->CarStruct.InstantReverseGravity)
	{
		if(this->LastHitPoint != FVector::Zero())
		{
			this->CarCollision->AddForce(this->LastHitPoint * this->CarCollision->GetMass() * this->CarStruct.PowerChangeGravity);
		}
		else
		{
			this->CarCollision->AddForce(this->CarCollision->GetUpVector() * this->CarCollision->GetMass() * this->CarStruct.PowerChangeGravity);
		}
	}
	else
	{
		FVector VelocityCar = this->CarCollision->GetPhysicsLinearVelocity();
		VelocityCar.Z = 0;
		this->CarCollision->SetPhysicsLinearVelocity(VelocityCar);
		//this->Server_CarGravity();
		if(this->LastHitPoint != FVector::Zero())
		{
			this->CarCollision->AddForce(this->LastHitPoint * this->CarCollision->GetMass() * this->CarStruct.PowerChangeGravity);
		}
		else
		{
			this->CarCollision->AddForce(this->CarCollision->GetUpVector() * this->CarCollision->GetMass() * this->CarStruct.PowerChangeGravity);
		}
	}
}

void AMyPawnCar::Server_CarGravity_Implementation()
{
	if(this->CarCollision == nullptr)return;
	this->CarReverseGravity();
	this->CarStruct.IsOnReverseGravity = !CarStruct.IsOnReverseGravity;
	//this->CarCollision->SetEnableGravity(!CarStruct.IsOnReverseGravity); If i enable the gravity back i need to know where it was affected before
	FRotator CarRotation = this->GetActorRotation();
	CarRotation.Roll += this->CarStruct.IsOnReverseGravity ? 180 : -180;// This function invert the gravity of the player and rotate him
	this->SetActorRotation(CarRotation);
	if(!this->ResetGravityInstant) return;
	FVector VelocityCar = this->CarCollision->GetPhysicsLinearVelocity();
	VelocityCar.Z = 0;
	this->CarCollision->GetBodyInstance()->ClearForces();
	this->CarCollision->SetPhysicsLinearVelocity(VelocityCar);
}

void AMyPawnCar::Gravity() const
{
	if(this->CarCollision == nullptr)return;
	if(this->LastHitPoint != FVector::Zero())
	{
		this->CarCollision->AddForce(-this->LastHitPoint * this->CarCollision->GetMass() * (CarStruct.IsGrounded ? CarStruct.CarMassGround : CarStruct.CarMassNotGrounded));// Gravity
	}
	else
	{
		this->CarCollision->AddForce(-this->CarCollision->GetUpVector() * this->CarCollision->GetMass() * (CarStruct.IsGrounded ? CarStruct.CarMassGround : CarStruct.CarMassNotGrounded));// Gravity	
	}
}


void AMyPawnCar::InvertGravity() const
{
	if(this->CarCollision == nullptr)return;
	if(this->LastHitPoint != FVector::Zero())
	{
		this->CarCollision->AddForce(-this->LastHitPoint * this->CarCollision->GetMass()
			* (CarStruct.IsGrounded ? CarStruct.CarMassGroundInversedGravity : CarStruct.CarMassNotGroundedInversedGravity));// Invert Gravity
	}
	else
	{
		this->CarCollision->AddForce(-this->GetActorUpVector() * this->CarCollision->GetMass()
			* (CarStruct.IsGrounded ? CarStruct.CarMassGroundInversedGravity : CarStruct.CarMassNotGroundedInversedGravity));// Invert Gravity	
	}
}

void AMyPawnCar::InverseGravityCoolDown()
{
	if(this->ContainerTimeBeforeInverseGravityBack >= this->CarStruct.CoolDownInverseGravity)
	{
		this->CarStruct.IsInverseGravityOnCoolDown = false;
		this->ContainerTimeBeforeInverseGravityBack = 0;
	}
	else
	{
		this->ContainerTimeBeforeInverseGravityBack += this->GetWorld()->GetDeltaSeconds();
	}
}


void AMyPawnCar::BoostPlate(const float Boost, bool Forward)
// Boost Plate still in progress
{
	if(this->CarCollision == nullptr)return;
	this->CarStruct.ActualMaxSpeedUnderEffect = this->CarStruct.MaxSpeedWithBoost;
	this->CarStruct.IsBoosted = true;
	this->CarBoost();
	if(Forward)
	{
		this->CarCollision->AddForce(this->GetActorForwardVector() * Boost * this->CarCollision->GetMass());
	}
	else
	{
		this->CarCollision->AddForce(-this->GetActorForwardVector() * Boost * this->CarCollision->GetMass());
	}
	FVector VelocityCar = this->CarCollision->GetComponentVelocity();
	VelocityCar.X = FMath::Clamp(VelocityCar.X,-CarStruct.ActualMaxSpeedUnderEffect,CarStruct.ActualMaxSpeedUnderEffect);
	VelocityCar.Y = FMath::Clamp(VelocityCar.Y,-CarStruct.ActualMaxSpeedUnderEffect,CarStruct.ActualMaxSpeedUnderEffect);
	VelocityCar.Z = FMath::Clamp(VelocityCar.Z,-CarStruct.ActualMaxSpeedUnderEffect,CarStruct.ActualMaxSpeedUnderEffect);
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
	this->CarCollision->GetBodyInstance()->ClearForces();
	this->CarCollision->ComponentVelocity = FVector::Zero();
	this->CarCollision->SetPhysicsLinearVelocity(FVector::Zero());
	this->TemporaryScene->SetRelativeRotation(FRotator::ZeroRotator);
	if(this->LastCheckPointHit == nullptr)
	{
		this->SetActorLocation(this->ResetPosition);
		this->SetActorRotation(FRotator::ZeroRotator);
	}
	else
	{
		this->SetActorLocation(this->LastCheckPointHit->GetComponentLocation());
		this->SetActorRotation(this->LastCheckPointHit->GetComponentRotation());
	}
	this->CarStruct.IsOnReverseGravity = false;
	this->CarStruct.IsGrounded = false;
	this->CarStruct.ActualMaxSpeedUnderEffect = this->CarStruct.MaxSpeed;
	this->ContainerTimeBeforeRaycastOn = this->CarStruct.TimeBeforeRaycastOn;
	this->ContainerTimeBeforeInverseGravityBack = this->CarStruct.CoolDownInverseGravity;
	this->LastHitPoint = FVector::Zero();
	this->CarStruct.IsSlowed = false;
	this->CarStruct.IsBoosted = false;
	this->CarStruct.IsInverseGravityOnCoolDown = false;
	this->CarStruct.IsRaycastActive = true;
}

void AMyPawnCar::LastPosition(FVector lastPositionReturned, AActor* roadExit)
// Not in use for the moment but it will be useful when the player fall
{
	/*this->LastCarPositionOnRoad = lastPositionReturned;
	this->MiddleOfTheRoad = roadExit->GetStreamingBounds().GetCenter();*/
}

void AMyPawnCar::DetectGround()
{
	if(!this->CarStruct.IsRaycastActive)
	{
		this->RaycastOff();
		if(this->CarStruct.IsInverseGravityOnCoolDown)
		{
			this->InverseGravityCoolDown();
		}
		return;
	}
	else
	{
		if(this->CarStruct.IsInverseGravityOnCoolDown)
		{
			this->InverseGravityCoolDown();
		}
	}
	FHitResult Result;
	TArray<AActor*> ActorIgnored;
	ActorIgnored.Add(this);
	const FVector StartPosition = this->GetActorLocation() - (this->CarStruct.IsOnReverseGravity ? -1 * this->CarStruct.StartBoxGroundDetection: this->CarStruct.StartBoxGroundDetection);
	const FVector EndPosition = this->GetActorLocation()- (this->CarStruct.IsOnReverseGravity ? -1 * this->CarStruct.EndBoxGroundDetection : this->CarStruct.EndBoxGroundDetection);
	FRotator CarRotation = this->GetActorRotation();
	CarRotation.Roll *= (this->CarStruct.BoxFollowRotationRoll ? 1 : 0);
	CarRotation.Yaw *= (this->CarStruct.BoxFollowRotationYaw ? 1 : 0);
	CarRotation.Pitch *= (this->CarStruct.BoxFollowRotationPitch ? 1 : 0);
	// Raycast with a box to detect the ground, i prefer to do that to not have the system breaking because of some mistake in the LD
	const bool ResultHit = UKismetSystemLibrary::BoxTraceSingle(this, StartPosition,EndPosition,
		CarStruct.HalfSizeBoxGroundDetection,CarRotation,UEngineTypes::ConvertToTraceType(ECC_Visibility),false,ActorIgnored,
		EDrawDebugTrace::None,Result,true,FLinearColor::Blue,FLinearColor::Red,5);
	FHitResult ResultHit2;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	this->GetWorld()->LineTraceSingleByChannel(ResultHit2 ,this->RaycastPosition->GetComponentLocation(),
		this->RaycastPosition->GetComponentLocation() + -this->GetActorUpVector() * DistanceRaycast,ECC_Visibility,
		CollisionParams,FCollisionResponseParams::DefaultResponseParam);
	if(!ResultHit)// Doesn't detect ground
	{
		CarStruct.IsGrounded = false;
		LastGroundDetected = nullptr;
		return;
	}
	if(Result.GetActor() != nullptr)
	{
		if(!Result.Component->ComponentHasTag(*this->GroundTag) && !Result.Component->ComponentHasTag(this->BoostTag))
		{
			CarStruct.IsGrounded = false;
			LastGroundDetected = nullptr;
			return;
		}
	}
	if(!this->CarStruct.IsGrounded)// Detect ground
	{
		this->CarStruct.IsGrounded = true;
		this->CarGotGrounded();
	}
	this->ContainerNumberOfGravityChanged = 0;
	this->LastGroundDetected = Result.GetActor();
	if(!BlockSlope)// This is where i adjust the rotation of the car with the slope of the ground
	{
		FRotator SlopeRotation;
		SlopeRotation = DetectSlope(Result.ImpactNormal);
		FRotator NewRotationCar = this->GetActorRotation();
		NewRotationCar.Pitch =  SlopeRotation.Pitch;
		NewRotationCar.Roll =  SlopeRotation.Roll;
		FRotator NewRotationCar2 = this->GetActorRotation();
		if(ResultHit2.GetActor() != nullptr)// This is the new raycast, same function but the raycast change
		{
			if(!ResultHit2.Component->ComponentHasTag(*this->GroundTag) && !ResultHit2.Component->ComponentHasTag(this->BoostTag)) return;
			if(ArrayVerticalRaycastPosition.Num() > 0 &&  ArrayHoziontalRaycastPosition.Num() > 0 && true)
			{
				FRotator CumulVertical = FRotator::ZeroRotator;
				FRotator CumulHorizontal = FRotator::ZeroRotator;
				int NumberOfHit1 = 0;
				int NumberOfHit2 = 0;
				for (USceneComponent* Raycast : ArrayVerticalRaycastPosition)
				{
					if(this->MultipleRaycast(Raycast->GetComponentLocation(),Raycast->GetForwardVector()).GetActor() == nullptr) continue;
					FRotator Slope = DetectSlope(this->MultipleRaycast(Raycast->GetComponentLocation(),Raycast->GetForwardVector()).ImpactNormal);
					NumberOfHit1++;
					CumulVertical += DetectSlope(this->MultipleRaycast(Raycast->GetComponentLocation(),Raycast->GetForwardVector()).ImpactNormal);
				}
				for (USceneComponent* Raycast : ArrayHoziontalRaycastPosition)
				{
					if(this->MultipleRaycast(Raycast->GetComponentLocation(),Raycast->GetForwardVector()).GetActor() == nullptr) continue;
					FRotator Slope = DetectSlope(this->MultipleRaycast(Raycast->GetComponentLocation(),Raycast->GetForwardVector()).ImpactNormal);
					NumberOfHit2++;
					CumulHorizontal += DetectSlope(this->MultipleRaycast(Raycast->GetComponentLocation(),Raycast->GetForwardVector()).ImpactNormal);
				}
				this->LastHitPoint = ResultHit2.ImpactNormal;
				NewRotationCar2.Pitch =  CumulVertical.Pitch / (NumberOfHit1 == 0 ? 1 : NumberOfHit1);
				NewRotationCar2.Roll = CumulHorizontal.Roll / (NumberOfHit2 == 0 ? 1 : NumberOfHit2);
			}
			else
			{
				this->LastHitPoint = ResultHit2.ImpactNormal;
				FRotator SlopeRotation2;
				SlopeRotation2 = DetectSlope(ResultHit2.ImpactNormal);
				NewRotationCar2.Pitch =  SlopeRotation2.Pitch;
				NewRotationCar2.Roll =  SlopeRotation2.Roll;
			}
		}
		if(true)// Trying a new raycast to adjust better my car rotation, in progress and disable so you can play "normally"
		{
			FRotator NewRotation = UKismetMathLibrary::RInterpTo_Constant(this->GetActorRotation(),
		NewRotationCar2,this->GetWorld()->GetDeltaSeconds(),this->CarStruct.SpeedForSlopeAdjustement);
			this->RotateCarForSlope(NewRotation);
		}
		else
		{
			FRotator NewRotation = UKismetMathLibrary::RInterpTo_Constant(this->GetActorRotation(),
				NewRotationCar,this->GetWorld()->GetDeltaSeconds(),this->CarStruct.SpeedForSlopeAdjustement);// Adjust the rotation smoothly with a speed
			this->RotateCarForSlope(NewRotation);
		}
	}
	if(ResultHit2.GetActor() != nullptr)// If the ground detect something which isn't an actor, it would be dangerous go further. The code would crash or be garbage since it need an actor
	FlyingCar(ResultHit2);// Update the flying car position
	/*if(Result.GetComponent()->ComponentHasTag(this->BoostTag) && !this->CarStruct.IsBoosted)// Boost Zone but still in progress
	{
		const AMyGroundBoostPlate* GroundBoostPlate = Cast<AMyGroundBoostPlate>(Result.GetActor());
		if(GroundBoostPlate == nullptr) return;
		this->BoostPlate(GroundBoostPlate->PowerBoost,true);
	}*/
}

FHitResult AMyPawnCar::MultipleRaycast(FVector PositionRaycast, FVector Direction)
{
	FHitResult ResultHit2;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	this->GetWorld()->LineTraceSingleByChannel(ResultHit2 ,PositionRaycast,
		PositionRaycast + Direction * DistanceRaycast,
		ECC_Visibility,CollisionParams,FCollisionResponseParams::DefaultResponseParam);
	return ResultHit2;
}


void AMyPawnCar::Server_DetectGround_Implementation()
{
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
	this->SetActorRotation(NewRotation);// Give the new rotation to the car, the constraint activated or deactivated is a way to force the physics behave like the Game Designer wanted
	//this->Server_RotateCarForSlope(NewRotation);
}

void AMyPawnCar::Server_RotateCarForSlope_Implementation(FRotator NewRotation)
{
	this->SetActorRotation(NewRotation);// Give the new rotation to the car, the constraint activated or deactivated is a way to force the physics behave like the Game Designer wanted
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

void AMyPawnCar::CarFallOnAnotherCar_Implementation(AMyPawnCar* CarHit)
{
}

void AMyPawnCar::CarFellOnMe(AMyPawnCar* CarHitting)
{
	if(this->CarCollision == nullptr)return;
	if(CarHitting == nullptr) return;
	this->CarFellOnMeEvent();
	this->CarStruct.IsSlowed = true;
	this->CarStruct.ActualMaxSpeedUnderEffect = this->CarStruct.MaxSpeedAfterSlowFromAnotherCar;
	if(this->CarStruct.IsBoosted) this->CarStruct.IsBoosted = false;
}

void AMyPawnCar::CarFellOnMeEvent_Implementation()
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

void AMyPawnCar::ResetRotationAfterCrash()
{
	FRotator CarRotation = this->GetActorRotation();
	CarRotation.Yaw = UKismetMathLibrary::FInterpTo_Constant(CarRotation.Yaw,0,this->GetWorld()->GetDeltaSeconds(),200.f);
	this->SetActorRotation(CarRotation);
}

void AMyPawnCar::FinishLine()
{
	if(this->OnceEnd)return;
	this->OnceEnd = true;
	this->FinishLineCrossed();
}

void AMyPawnCar::FinishLineCrossed_Implementation()
{
	
}

void AMyPawnCar::HalfLineCrossed_Implementation()
{
	
}





void AMyPawnCar::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
// Notify when a collision happen
{
	if(Other == nullptr)return;
	if(Other == this)return;
	if(Other->ActorHasTag(this->DecorTag))// Test the tag of the collider to choose what response it should give
	{
		this->CarCollisionWithDecor();
	}else if(Other->ActorHasTag(this->CarTag))
	{
		this->CarCollisionWithAnotherCar();
	}
}

void AMyPawnCar::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor == nullptr)return;
	if(OtherActor->ActorHasTag(this->CarTag))
	{
		AMyPawnCar* CarHit = Cast<AMyPawnCar>(OtherActor);
		if(CarHit == nullptr) return;
		this->CarFellOnMe(CarHit);
		const float Angle = FVector::DotProduct(CarHit->GetActorForwardVector(),(this->GetActorLocation() - CarHit->GetActorLocation()).GetSafeNormal());
		if(Angle < 0.f)
		{
			CarHit->BoostPlate(CarHit->CarStruct.PowerBoost,true);
		}
		else
		{
			CarHit->BoostPlate(CarHit->CarStruct.PowerBoost,false);
		}
	}else
	{
		if(OtherComp == nullptr) return;
		if(OtherComp->ComponentHasTag(*this->CheckPointTag))
		{
			UBoxComponent* BoxCheckPoint = Cast<UBoxComponent>(OtherComp);
			if(BoxCheckPoint == nullptr) return;;
			this->LastCheckPointHit = BoxCheckPoint;
		}
		else if(OtherComp->ComponentHasTag(*this->RespawnTag))
		{
			this->CarRespawn();
		}
		else if(OtherComp->ComponentHasTag(this->BoostTag) && !this->CarStruct.IsBoosted)
		{
			const AMyPartCircuit* PartCircuit = Cast<AMyPartCircuit>(OtherActor);
			if(PartCircuit == nullptr) return;
			this->BoostPlate(PartCircuit->BoostPower,true);
		}
		else if(OtherComp->ComponentHasTag(*this->FinishLineTag))
		{
			this->FinishLine();
		}
		else if(OtherComp->ComponentHasTag(*this->LeapPassedTag))
		{
			this->NumberOfLeap = 2;
			this->HalfLineCrossed();
		}
	}
}

void AMyPawnCar::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}