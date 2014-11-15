// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "Components/SpotLightComponent.h"
#include "HallwayCharacter.generated.h"

UCLASS(config=Game)
class AHallwayCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	TSubobjectPtr<class UCameraComponent> FirstPersonCameraComponent;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Flashlight)
	TSubobjectPtr<class USpotLightComponent> FlashlightComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Flashlight)
	float MaxFlashlightTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Flashlight)
	float FlashlightTimeLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Flashlight)
	bool ShouldFlashlightRunOut;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Flashlight)
	class USoundBase* FlashlightErrorSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Flashlight)
	class USoundBase* FlashlightToggleSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Character)
	class USoundBase* FootstepSound;

protected:

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	void InputCrouch();

	void InputUnCrouch();

	void ToggleFlashlight();

	void StartUse();

	void StopUse();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

	virtual void Tick(float DeltaSeconds) override;

private:
	float TimeUntilNextFootstep;

	bool FootstepRightSide;
};

