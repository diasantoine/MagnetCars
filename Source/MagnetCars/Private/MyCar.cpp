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
	componentMovement->MaxAcceleration = acceleration;
	componentMovement->MaxWalkSpeed = maxSpeed;
	//componentMovement->GroundFriction = 0;
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
	PlayerInputComponent->BindAxis("Right",this,&AMyCar::RightMovement);
	PlayerInputComponent->BindAxis("Turn",this,&AMyCar::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp",this,&AMyCar::AddControllerPitchInput);
	// même problème que d'habitude, trouve un moyen que les quatres inputs viennent mettre a jour la velocity sans supp les autres inputs
	// PlayerInputComponent->BindAxis("RightLean",this,&AMyCar::CarDrift);
	// PlayerInputComponent->BindAxis("LeftLean",this,&AMyCar::CarDrift);
	PlayerInputComponent->BindAction("ChangeGravity",IE_Pressed,this,&AMyCar::CarGravity);

	PlayerInputComponent->BindAction("Respawn",IE_Pressed,this,&AMyCar::CarRespawn);
}


// {
// 	UE_LOG(LogTemp, Warning,TEXT("Mais"));
// 	UCharacterMovementComponent* ComponentMovement = GetCharacterMovement();
// 	FVector Velocity = ComponentMovement->Velocity;
// 	switch (WhichDirection)
// 	{
// 	case EWhichDirection::VerticalDirection:
// 		default:
// 		Velocity.Z = acceleration * Velocity.GetSafeNormal().Z * WhichAxis;
// 		break;
// 	case EWhichDirection::HorizontalDirection:
// 		Velocity.X = acceleration * Velocity.GetSafeNormal().X * WhichAxis;
// 		break;
// 	}
// 	ComponentMovement->Velocity = Velocity.GetSafeNormal() * FMath::Clamp(0,Velocity.Length(),maxSpeed);
// }

void AMyCar::ForwardMovement(float axisValue)
{
	this->AddMovementInput(GetActorForwardVector() * axisValue);
}

void AMyCar::RightMovement(float axisValue)
{
	this->AddMovementInput(GetActorRightVector()* axisValue);
}

void AMyCar::CarDrift(float value)
{
	
}

void AMyCar::CarGravity()
{
	isOnReverseGravity = !isOnReverseGravity;
	this->componentMovement->GravityScale = -this->componentMovement->GravityScale;
	this->Jump();
	this->SetActorRotation(FRotator( isOnReverseGravity ? 180 : 0,0,0));
	//Change Car Gravity to *-1 to make it go the other way, don't forget to rotate the camera x)
}

void AMyCar::CarRespawn()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}



// void AFASCharacter::MovementPlayer()
// {
// 	FVector VelocityPlayer = GetCharacterMovement()->Velocity;
// 	float accelVel; // Accelerated velocity in direction of movment
// 	float InputForward;
// 	float InputRight;
// 	FVector AccelDirection;
// 	if (GetCharacterMovement()->IsMovingOnGround() && !_onBunny)
// 	{
// 		// float speed = VelocityPlayer.Size();
// 		// if (speed != 0) // To avoid divide by zero errors
// 		// {
// 		// 	float drop = speed * 2 * GetWorld()->GetDeltaSeconds();
// 		// 	VelocityPlayer *= FMath::Max(speed - drop, 0.f) / speed; // Scale the velocity based on friction.
// 		// }
// 		accelVel = _fDataStruct._groundSpeed ;//* GetWorld()->GetDeltaSeconds();
// 		InputForward = InputComponent->GetAxisValue("Forward");
// 		InputRight = InputComponent->GetAxisValue("Right");
// 		AccelDirection =  GetActorForwardVector() * InputForward + GetActorRightVector() * InputRight;
// 	}
// 	else
// 	{
// 		accelVel = _fDataStruct._airAcceleration; // * GetWorld()->GetDeltaSeconds();
// 		InputForward = InputComponent->GetAxisValue("Forward");
// 		InputRight = InputComponent->GetAxisValue("Right");
// 		if (_onBunny)
// 		{
// 			if (_casualBunny)
// 			{
// 				AccelDirection = GetActorRightVector();// * InputRight;
// 			}
// 			else
// 			{
// 				AccelDirection = GetActorRightVector() * InputRight + GetActorForwardVector();
// 			}
// 		}
// 		else
// 		{
// 			AccelDirection =  GetActorForwardVector() * InputForward + GetActorRightVector() * InputRight;
// 		}
// 	}
// 	if (InputForward == 0 && InputRight == 0 && !_onJumpAuto)
// 	{
// 		
// 		//_containerVelocityBunny = 0;
// 		//_onBunny = false;
// 		//_keepBunnySpeed = false;
// 		StopBunnyHop();
// 	}
// 	if (AccelDirection.Size() > 1)
// 	{
// 		AccelDirection.Normalize();
// 	}
// 	float projVel = FVector::DotProduct(VelocityPlayer, AccelDirection); // Vector projection of Current velocity onto accelDir.
//
// 	// If necessary, truncate the accelerated velocity so the vector projection does not exceed max_velocity
// 	if(projVel + accelVel >_fDataStruct._maxSpeed)
// 		accelVel = _fDataStruct._maxSpeed - projVel;
//
// 	//FVector2D Velocity2D = FVector2D(GetCharacterMovement()->Velocity.X,GetCharacterMovement()->Velocity.Y);
// 	if (/*_keepBunnySpeed && */ !_onJumpAuto && GetCharacterMovement()->IsMovingOnGround())
// 	{
// 		_onBunny = false;
// 		StopBunnyHop();
// 		// if (!GetWorldTimerManager().TimerExists(ManagerTimeDotRotation))
// 		// {
// 		// 	GetWorldTimerManager().SetTimer(ManagerTimeDotRotation,this,&AFASCharacter::StopBunnyHop,_fDataStruct._timeBeforeBunnyStop,
// 		// 		false,_fDataStruct._timeBeforeBunnyStop);
// 		// }	
// 	}else if (GetWorldTimerManager().TimerExists(ManagerTimeDotRotation))
// 	{
// 		GetWorldTimerManager().ClearTimer(ManagerTimeDotRotation);
// 	}
// 	
// 	if (!GetCharacterMovement()->IsMovingOnGround() ||_onBunny)
// 	{
// 		_decelerationVelocityGround = 0;
// 		if (_bunnyVelocity != 0)
// 		{
// 			_bunnyVelocity = 0;
// 		}
// 		if (InputComponent->GetAxisValue("Right") != 0 && _onBunny || _onBunny && _casualBunny)
// 		{
// 			FVector2D Velocity2D = FVector2D( GetCharacterMovement()->Velocity.X,GetCharacterMovement()->Velocity.Y);
// 			GetCharacterMovement()->Velocity.X = _forwardSign * GetActorForwardVector().X * Velocity2D.Size() + AccelDirection.X * accelVel;
// 			GetCharacterMovement()->Velocity.Y = _forwardSign * GetActorForwardVector().Y * Velocity2D.Size() + AccelDirection.Y * accelVel;
// 			_containerVelocityBunny = GetCharacterMovement()->Velocity.Size();
// 			//UE_LOG(LogTemp,Warning,TEXT("%f"),_containerVelocityBunny)
// 			if (_WeaponType != Shotgun && GetCharacterMovement()->Velocity.Size() >= _fDataStruct._maxSpeed * _fDataStruct._reloadShotGunPercentagelvl1)
// 			{
// 				if (_timeBeforeReloadShotGun >= _fDataStruct._timeBeforeReloadShotGun)
// 				{
// 					TSubclassOf<AMyWeaponBehaviour>& weaponBehaviourClass = _weaponTypes[Shotgun];
// 					AMyWeaponBehaviour* weaponBehaviourObjectReload = weapons[weaponBehaviourClass];
// 					_timeBeforeReloadShotGun = 0;
// 					if (GetCharacterMovement()->Velocity.Size() >= _fDataStruct._maxSpeed * _fDataStruct._reloadShotGunPercentagelvl3)
// 					{
// 						
// 						weaponBehaviourObjectReload->Reload(_userWidgetMunition);
// 						if (_ContainerpercentageSpeedMaxSpeedShotGun != _fDataStruct._percentageSpeedMaxSpeedlvl3)
// 						{
// 							_ContainerpercentageSpeedMaxSpeedShotGun = _fDataStruct._percentageSpeedMaxSpeedlvl3;
// 						}
// 					}else if (GetCharacterMovement()->Velocity.Size() >= _fDataStruct._maxSpeed * _fDataStruct._reloadShotGunPercentagelvl2)
// 					{
// 						weaponBehaviourObjectReload->Reload(_userWidgetMunition);
// 						if (_ContainerpercentageSpeedMaxSpeedShotGun != _fDataStruct._percentageSpeedMaxSpeedlvl2 &&
// 							_ContainerpercentageSpeedMaxSpeedShotGun != _fDataStruct._percentageSpeedMaxSpeedlvl3)
// 						{
// 							_ContainerpercentageSpeedMaxSpeedShotGun = _fDataStruct._percentageSpeedMaxSpeedlvl2;
// 						}
// 					}else
// 					{
// 						weaponBehaviourObjectReload->Reload(_userWidgetMunition);
// 						if (_ContainerpercentageSpeedMaxSpeedShotGun != _fDataStruct._percentageSpeedMaxSpeedlvl2 &&
// 							_ContainerpercentageSpeedMaxSpeedShotGun != _fDataStruct._percentageSpeedMaxSpeedlvl3)
// 						{
// 							_ContainerpercentageSpeedMaxSpeedShotGun = _fDataStruct._percentageSpeedMaxSpeedlvl1;
// 						}
// 					}
// 				}else
// 				{
// 					_timeBeforeReloadShotGun += GetWorld()->GetDeltaSeconds();
// 				}
// 			}else
// 			{
// 				if (_timeBeforeReloadShotGun > 0)
// 				{
// 					_timeBeforeReloadShotGun = 0;
// 				}
// 			}
// 			if (_onRecoil)
// 			{
// 				if (_containerRecoil > 0)
// 				{
// 					_containerRecoil -= GetWorld()->GetDeltaSeconds();
// 				}
// 				else
// 				{
// 					_containerRecoil = 0;
// 					_onRecoil = false;
// 				}
// 			}
// 		}
// 		else
// 		{
// 			if (_decelerationJump)
// 			{
// 				if (_bunnyVelocity == 0)
// 				{
// 					_bunnyVelocity = GetCharacterMovement()->Velocity.Size();
// 				}
// 				_decelerationVelocityGround = _decelerationVelocityGround + GetWorld()->GetDeltaSeconds()/_fDataStruct._timeBeforeBunnyStop;
// 				if (_jumpFollowDirection)
// 				{
// 					//GetCharacterMovement()->Velocity = AccelDirection * FMath::Lerp(_bunnyVelocity,_fDataStruct._airSpeed,_decelerationVelocityGround); //accelVel;
// 					// GetCharacterMovement()->Velocity.X = AccelDirection.X * FMath::Lerp(_bunnyVelocity,_fDataStruct._airSpeed,_decelerationVelocityGround);// * accelVel;
// 					// GetCharacterMovement()->Velocity.Y = AccelDirection.Y * FMath::Lerp(_bunnyVelocity,_fDataStruct._airSpeed,_decelerationVelocityGround);
// 					FVector2D Velocity2D = FVector2D( GetCharacterMovement()->Velocity.X,GetCharacterMovement()->Velocity.Y);
// 					GetCharacterMovement()->Velocity.X = GetActorForwardVector().X * FMath::Lerp(Velocity2D.Size(),_fDataStruct._airSpeed,_decelerationVelocityGround)
// 					+ AccelDirection.X;
// 					GetCharacterMovement()->Velocity.Y = GetActorForwardVector().Y * FMath::Lerp(Velocity2D.Size(),_fDataStruct._airSpeed,_decelerationVelocityGround)
// 					+ AccelDirection.Y;
// 				}
// 				else
// 				{
// 					//GetCharacterMovement()->Velocity = AccelDirection * FMath::Lerp(_bunnyVelocity,_fDataStruct._airSpeed,_decelerationVelocityGround); //accelVel;
// 					FVector2D Velocity2D = FVector2D( GetCharacterMovement()->Velocity.X,GetCharacterMovement()->Velocity.Y);
// 					GetCharacterMovement()->Velocity.X = AccelDirection.X * FMath::Lerp(Velocity2D.Size(),_fDataStruct._airSpeed,_decelerationVelocityGround);
// 					GetCharacterMovement()->Velocity.Y = AccelDirection.Y * FMath::Lerp(Velocity2D.Size(),_fDataStruct._airSpeed,_decelerationVelocityGround);
// 				}
// 			}
// 			else
// 			{
// 				if (_jumpFollowDirection)
// 				{
// 					FVector2D Velocity2D = FVector2D( GetCharacterMovement()->Velocity.X,GetCharacterMovement()->Velocity.Y);
// 					GetCharacterMovement()->Velocity.X = GetActorForwardVector().X * Velocity2D.Size() + AccelDirection.X;
// 					GetCharacterMovement()->Velocity.Y = GetActorForwardVector().Y * Velocity2D.Size() + AccelDirection.Y;
// 					// GetCharacterMovement()->Velocity.X = AccelDirection.X * _fDataStruct._airSpeed;// * accelVel;
// 					// GetCharacterMovement()->Velocity.Y = AccelDirection.Y * _fDataStruct._airSpeed;
// 				}
// 				else
// 				{
// 					if (_onRecoil)
// 					{
// 						if (_containerRecoil > 0)
// 						{
// 							_containerRecoil -= GetWorld()->GetDeltaSeconds();
// 						}
// 						else
// 						{
// 							_containerRecoil = 0;
// 							_onRecoil = false;
// 						}
// 					}
// 					else
// 					{
// 						if (_containerVelocityBunny == 0)
// 						{
// 							GetCharacterMovement()->Velocity.X = AccelDirection.X * _fDataStruct._airSpeed;// * accelVel;
// 							GetCharacterMovement()->Velocity.Y = AccelDirection.Y * _fDataStruct._airSpeed;
// 						}
// 						else
// 						{
// 							// GetCharacterMovement()->Velocity.X += accelVel;
// 							// GetCharacterMovement()->Velocity.Y += accelVel;
// 							// GetCharacterMovement()->Velocity.X = 1 * _containerVelocityBunny;
// 							// GetCharacterMovement()->Velocity.Y = AccelDirection.Y * _containerVelocityBunny;
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}
// 	else
// 	{
// 		if (_onRecoil)
// 		{
// 			if (_containerRecoil > 0)
// 			{
// 				_containerRecoil -= GetWorld()->GetDeltaSeconds();
// 			}
// 			else
// 			{
// 				_containerRecoil = 0;
// 				_onRecoil = false;
// 			}
// 		}
// 		else
// 		{
// 			if (_keepBunnySpeed)//Todo le bunny se met en false que si je le rate, 
// 				{
// 				if (_bunnyVelocity == 0)
// 				{
// 					_bunnyVelocity = GetCharacterMovement()->Velocity.Size();
// 				}
// 				// float speed = VelocityPlayer.Size();
// 				// if (speed != 0) // To avoid divide by zero errors
// 				// {
// 				// 	float drop = speed * 2 * GetWorld()->GetDeltaSeconds();
// 				// 	VelocityPlayer *= FMath::Max(speed - drop, 0.f) / speed; // Scale the velocity based on friction.
// 				// }
// 				_decelerationVelocityGround = _decelerationVelocityGround + GetWorld()->GetDeltaSeconds()/_fDataStruct._timeBeforeBunnyStop;
// 				// float test =VelocityPlayer.Size();
// 				GetCharacterMovement()->Velocity = GetCharacterMovement()->Velocity.GetSafeNormal() * FMath::Lerp(_bunnyVelocity,_fDataStruct._groundSpeed,_decelerationVelocityGround); //accelVel;
// 				}
// 			else
// 			{
// 				if (_WeaponType != Riffle && GetCharacterMovement()->Velocity.Size() >= _fDataStruct._groundSpeed * _fDataStruct._reloadRifflePercentageSpeedlvl1)
// 				{
// 					if (_timeBeforeReloadRiffle > _fDataStruct._timeBeforeReloadRiffle)
// 					{
// 						TSubclassOf<AMyWeaponBehaviour>& weaponBehaviourClass = _weaponTypes[Riffle];
// 						AMyWeaponBehaviour* weaponBehaviourObjectReload = weapons[weaponBehaviourClass];
// 						if (GetCharacterMovement()->Velocity.Size() >= _fDataStruct._groundSpeed * _fDataStruct._reloadRifflePercentageSpeedlvl3)
// 						{
// 							_timeBeforeReloadRiffle = 0;
// 							weaponBehaviourObjectReload->Reload(_userWidgetMunition);
// 							if (_ContainerpercentageSpeedMaxSpeedRiffle != _fDataStruct._percentageSpeedMaxSpeedlvl3)
// 							{
// 								_ContainerpercentageSpeedMaxSpeedRiffle= _fDataStruct._percentageSpeedMaxSpeedlvl3;
// 							}
// 						}else if (GetCharacterMovement()->Velocity.Size() >= _fDataStruct._groundSpeed * _fDataStruct._reloadRifflePercentageSpeedlvl2)
// 						{
// 							_timeBeforeReloadRiffle = 0;
// 							weaponBehaviourObjectReload->Reload(_userWidgetMunition);
// 							if (_ContainerpercentageSpeedMaxSpeedRiffle != _fDataStruct._percentageSpeedMaxSpeedlvl3 &&
// 								_ContainerpercentageSpeedMaxSpeedRiffle != _fDataStruct._percentageSpeedMaxSpeedlvl2)
// 							{
// 								_ContainerpercentageSpeedMaxSpeedRiffle= _fDataStruct._percentageSpeedMaxSpeedlvl2;
// 							}
// 						}
// 						else
// 						{
// 							_timeBeforeReloadRiffle = 0;
// 							weaponBehaviourObjectReload->Reload(_userWidgetMunition);
// 							if (_ContainerpercentageSpeedMaxSpeedRiffle != _fDataStruct._percentageSpeedMaxSpeedlvl3 &&
// 								_ContainerpercentageSpeedMaxSpeedRiffle != _fDataStruct._percentageSpeedMaxSpeedlvl2)
// 							{
// 								_ContainerpercentageSpeedMaxSpeedRiffle= _fDataStruct._percentageSpeedMaxSpeedlvl1;
// 							}
// 						}
// 						weaponBehaviourObjectReload->_percentageSpeed = _ContainerpercentageSpeedMaxSpeedRiffle;
// 					}else
// 					{
// 						_timeBeforeReloadRiffle += GetWorld()->GetDeltaSeconds();
// 					}
// 				}else
// 				{
// 					_timeBeforeReloadRiffle = 0;
// 				}
// 				if (_bunnyVelocity == 0)
// 				{
// 					_bunnyVelocity = GetCharacterMovement()->Velocity.Size();
// 				}
// 				//UE_LOG(LogTemp,Warning,TEXT("%f"),_containerVelocityBunny)
// 				if (_bunnyVelocity != 0)
// 				{
// 					_bunnyVelocity = 0;
// 				}
// 				_containerVelocityBunny = 0;
// 				_decelerationVelocityGround = 0;
// 				GetCharacterMovement()->Velocity = accelVel * AccelDirection;
// 			}
// 		}
// 	}
// 	GetCharacterMovement()->Velocity = FMath::Clamp(GetCharacterMovement()->Velocity.Size(),0.0f,_fDataStruct._maxSpeed) * GetCharacterMovement()->Velocity.GetSafeNormal();
// }

