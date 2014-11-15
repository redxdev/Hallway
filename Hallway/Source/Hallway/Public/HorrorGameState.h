// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "GameplayEvent.h"
#include "HorrorGameState.generated.h"


UCLASS()
class HALLWAY_API AHorrorGameState : public AGameState
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Gameplay")
	TArray<AGameplayEvent*> Events;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	TArray<class USoundBase*> Sounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float EventTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Gameplay")
	float TimeUntilNextEvent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay")
	float TimeUntilNextSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay")
	bool EventTimerRunning;

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	bool CallRandomEvent();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	bool CallRandomSound();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	bool AddGameplayEvent(AGameplayEvent* Actor);

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void ContinueEventTimer(float Multiplier = 1.f);

public:
	virtual void Tick(float DeltaTime) override;
};
