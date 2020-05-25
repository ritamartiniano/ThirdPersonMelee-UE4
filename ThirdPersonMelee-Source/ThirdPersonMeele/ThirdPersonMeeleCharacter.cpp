// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ThirdPersonMeeleCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/SpringArmComponent.h"
#include "Warrior_HealthComponent.h"
#include "MyAnimInstance.h"

//////////////////////////////////////////////////////////////////////////
// AThirdPersonMeeleCharacter

AThirdPersonMeeleCharacter::AThirdPersonMeeleCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	playerAttackDamage = 2;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AThirdPersonMeeleCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AThirdPersonMeeleCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AThirdPersonMeeleCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AThirdPersonMeeleCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AThirdPersonMeeleCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AThirdPersonMeeleCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AThirdPersonMeeleCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AThirdPersonMeeleCharacter::OnResetVR);

	//handle attack
	PlayerInputComponent->BindAction("MeleeHit", IE_Pressed, this, &AThirdPersonMeeleCharacter::Attack);

	//PlayerInputComponent->BindAction("SpecialAttack1", IE_Pressed, this, &AThirdPersonMeeleCharacter::)
}

void AThirdPersonMeeleCharacter::Tick(float DeltaTime)
{
   
}

void AThirdPersonMeeleCharacter::SpawnHealth()
{
	/**if (HealthPickUp)
	{
		UWorld* world = GetWorld();
		if (world)
		{
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;
			FVector projDirection = GetPlayerController()->GetActorForwardVector();

			FRotator rotator;
			
			FVector spawnLoc = GetPlayerController()->GetActorLocation() + projDirection * 500;
			world->SpawnActor<AHealthPickUp>(HealthPickUp, spawnLoc, rotator, spawnParams);
		}
	}
	**/

}

void AThirdPersonMeeleCharacter::SwordSwung()
{
	if (MeleeWeapon)
	{
		MeleeWeapon->Swing();
	}
}

void AThirdPersonMeeleCharacter::PostInitializeComponents()
{   // instantiate the melee weapon if a bp was selected

	Super::PostInitializeComponents();
	if (BP_MeleeSword)
	{   
		UE_LOG(LogTemp, Warning, TEXT("BPMeleeWeapon not null"));
		MeleeWeapon = GetWorld()->SpawnActor<AMeleeWeapon>(BP_MeleeSword, FVector(), FRotator());

		if (MeleeWeapon)
		{   
			UE_LOG(LogTemp, Warning, TEXT("MeleeWeapon not null"));
			const USkeletalMeshSocket *socket = GetMesh()->GetSocketByName(FName("WeaponHoldSocket"));
			socket->AttachActor(MeleeWeapon, GetMesh());
			MeleeWeapon ->PlayerHolder = this;
			//temporarily, the weapon's attack damage can be the same as the owner's 
			MeleeWeapon->AttackDamage = playerAttackDamage;
		}
	}
}

void AThirdPersonMeeleCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AThirdPersonMeeleCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AThirdPersonMeeleCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AThirdPersonMeeleCharacter::Attack()
{
	isAttacking = true;
	UE_LOG(LogTemp, Warning, TEXT("IsAttackig"));
	/**
	UMyAnimInstance* AnimInstanceRef = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstanceRef)
		AnimInstanceRef->Attack();
		**/
}

void AThirdPersonMeeleCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AThirdPersonMeeleCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AThirdPersonMeeleCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AThirdPersonMeeleCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
