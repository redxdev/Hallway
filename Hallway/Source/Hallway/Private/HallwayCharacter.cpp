// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "Hallway.h"
#include "HallwayCharacter.h"
#include "HallwayProjectile.h"
#include "Animation/AnimInstance.h"

#include "Engine.h"


//////////////////////////////////////////////////////////////////////////
// AHallwayCharacter

AHallwayCharacter::AHallwayCharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Set size for collision capsule
	CapsuleComponent->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->AttachParent = CapsuleComponent;
	FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P are set in the
	// derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	// Set some options on the movement component
	CharacterMovement->GravityScale = 1.5f;
	CharacterMovement->MaxWalkSpeed = 400.f;
	CharacterMovement->MaxWalkSpeedCrouched = 200.f;
	CharacterMovement->MaxSwimSpeed = 200.f;
	CharacterMovement->MaxAcceleration = 768.f;
	CharacterMovement->NavAgentProps.bCanCrouch = true;
	CharacterMovement->bCanWalkOffLedgesWhenCrouching = true;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AHallwayCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	check(InputComponent);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	InputComponent->BindAction("Crouch", IE_Pressed, this, &AHallwayCharacter::InputCrouch);
	InputComponent->BindAction("Crouch", IE_Released, this, &AHallwayCharacter::InputUnCrouch);

	InputComponent->BindAxis("MoveForward", this, &AHallwayCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AHallwayCharacter::MoveRight);
	
	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &AHallwayCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &AHallwayCharacter::LookUpAtRate);
}

void AHallwayCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AHallwayCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AHallwayCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AHallwayCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AHallwayCharacter::InputCrouch()
{
	Crouch();
}

void AHallwayCharacter::InputUnCrouch()
{
	UnCrouch();
}